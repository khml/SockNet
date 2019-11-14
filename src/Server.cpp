//
// Created by KHML on 2019-07-29.
//

#include <sys/socket.h>
#include <iostream>

#include "Server.hpp"
#include "Connector.hpp"

using std::cerr;
using std::endl;

using std::string;

namespace sockNet
{
    EndPoint::EndPoint(int clientSockfd, socklen_t len) :
            connector(accept(clientSockfd, (struct sockaddr *) &fromAddr, &len))
    {
        if (connector.isConnected())
        {
            connectingFlg = true;
        } else
            cerr << "accept Error" << endl;
    }

    EndPoint::EndPoint(const EndPoint &orig) : connector(orig.connector), connectingFlg(orig.connectingFlg),
                                               fromAddr(orig.fromAddr)
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

    string EndPoint::receiveMessage(const size_t bufferSize)
    {
        string message;
        ssize_t recv_size = connector.readMessage(message, bufferSize);

        if (recv_size <= 0)
        {
            if (recv_size < 0)
                cerr << "socket recv Error" << endl;
            terminate();
        }

        return message;
    }

    void EndPoint::sendMessage(string message)
    {
        if (connector.writeMessage(message) < 0)
            cerr << "socket write error" << endl;
    }

    Server::Server(const ushort portNumber)
    {
        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            cerr << "socket Error" << endl;
            connectingFlg = false;
        }

        addr.sin_family = AF_INET;
        addr.sin_port = htons (portNumber);
        addr.sin_addr.s_addr = INADDR_ANY;

        if (bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) < 0)
        {
            cerr << "bind Error" << endl;
        }
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
            closeSocket(sockfd);
        connectingFlg = false;
    }

    EndPoint Server::listenForAccess()
    {
        if (listen(sockfd, SOMAXCONN) < 0)
        {
            cerr << "listen Error" << endl;
            connectingFlg = false;
        }

        socklen_t len = sizeof(addr);

        EndPoint endPoint(sockfd, len);
        return endPoint;
    }

}
