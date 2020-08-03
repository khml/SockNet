//
// Created by KHML on 2019-07-29.
//

#include <sys/socket.h>

#include <socknet/core/utilities.hpp>
#include <socknet/server.hpp>

namespace socknet
{
    Server::Server(const uint16_t portNumber) :sockfd(socket(AF_INET, SOCK_STREAM, 0))
    {
        if (sockfd < 0)
        {
            errors.emplace_back("socket Error");
            connectingFlg = false;
        }

        addr.sin_family = AF_INET;
        addr.sin_port = htons(portNumber);
        addr.sin_addr.s_addr = INADDR_ANY;

        if (bind(sockfd, (struct sockaddr*) &addr, sizeof(addr)) < 0)
            errors.emplace_back("bind Error");
    }

    Server::~Server()
    {
        terminate();
    }

    bool Server::isSocketOpened() const
    {
        return connectingFlg;
    }

    void Server::terminate()
    {
        if (isSocketOpened())
            core::closeSocket(sockfd);
        connectingFlg = false;
    }

    Connection Server::listen()
    {
        if (::listen(sockfd, SOMAXCONN) < 0)
        {
            errors.emplace_back("listen Error");
            connectingFlg = false;
        }

        Connection endPoint(sockfd);
        return endPoint;
    }

}
