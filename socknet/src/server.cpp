//
// Created by KHML on 2019-07-29.
//

#include <sys/socket.h>

#include <socknet/server.hpp>
#include <socknet/connector.hpp>

namespace sockNet
{
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

        if (bind(sockfd, (struct sockaddr*) &addr, sizeof(addr)) < 0)
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
