//
// Created by KHML on 2019-07-29.
//

#include <sys/socket.h>

#include <socknet/core/sockapis.hpp>
#include <socknet/server.hpp>

namespace socknet
{
    Server::Server(const uint16_t portNumber) :sockfd(core::createSocket())
    {
        if (sockfd < 0)
        {
            errors.emplace_back("socket Error");
            connectingFlg = false;
        }

        core::setSockaddr(addr, portNumber);

        if (core::bindSocket(sockfd, addr) < 0)
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
        if (core::listenSocket(sockfd) < 0)
        {
            errors.emplace_back("listen Error");
            connectingFlg = false;
        }

        Connection connection(sockfd);
        return connection;
    }

}
