//
// Created by KHML on 2019-07-29.
//

#include <sys/socket.h>
#include <iostream>

#include "Server.hpp"
#include "Connector.hpp"


namespace sockNet
{
    EndPoint::EndPoint(const int clientSockfd, ::socklen_t len) :
            connector(::accept(clientSockfd, (struct ::sockaddr *) &fromAddr, &len))
    {
        if (connector.isConnected())
            connectingFlg = true;
        else
            errors.emplace_back("accept Error");
    }

    EndPoint::EndPoint(const EndPoint& orig) : connector(orig.connector), fromAddr(orig.fromAddr),
                                               connectingFlg(orig.connectingFlg)
    {}

    EndPoint::~EndPoint()
    {
        terminate();
    }

    bool EndPoint::isConnecting()
    {
        return connectingFlg;
    }

    void EndPoint::terminate()
    {
        if (isConnecting())
            connector.terminate();
        connectingFlg = false;
    }

    std::string EndPoint::receive(const size_t bufferSize)
    {
        std::string message;
        ssize_t recv_size = connector.receive(message, bufferSize);

        if (recv_size <= 0)
        {
            if (recv_size < 0)
                errors.emplace_back("socket recv Error");
            terminate();
        }

        return message;
    }

    void EndPoint::send(const std::string& message)
    {
        if (connector.send(message) < 0)
            errors.emplace_back("socket write error");
    }

    Server::Server(const ushort portNumber)
    {
        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            errors.emplace_back("socket Error");
            connectingFlg = false;
        }

        addr.sin_family = AF_INET;
        addr.sin_port = htons (portNumber);
        addr.sin_addr.s_addr = INADDR_ANY;

        if (bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) < 0)
            errors.emplace_back("bind Error");
    }

    Server::~Server()
    {
        terminate();
    }

    bool Server::isSocketOpen()
    {
        return connectingFlg;
    }

    void Server::terminate()
    {
        if (isSocketOpen())
            close(sockfd);
        connectingFlg = false;
    }

    EndPoint Server::listen()
    {
        if (::listen(sockfd, SOMAXCONN) < 0)
        {
            errors.emplace_back("listen Error");
            connectingFlg = false;
        }

        socklen_t len = sizeof(addr);

        EndPoint endPoint(sockfd, len);
        return endPoint;
    }

}
