//
// Created by KHML on 2019-07-29.
//

#include <unistd.h>
#include <sys/socket.h>
#include <cstring>

#include "Connector.hpp"


namespace sockNet
{
    int close(const int sockfd)
    {
        return ::close(sockfd);
    }

    Connector::Connector(const int sockfd) : sockfd(sockfd)
    {}

    Connector::Connector(const Connector &orig) : sockfd(orig.sockfd)
    {}


    Connector::~Connector()
    {}

    ssize_t Connector::send(const std::string& message)
    {
        return ::write(sockfd, message.c_str(), (size_t) sizeof(char) * message.size());
    }

    ssize_t Connector::receive(const std::string& message, const size_t bufferSize)
    {
        char *buf = new char[bufferSize];
        size_t bufSize = sizeof(char) * bufferSize;
        std::memset(buf, 0, bufSize);

        ssize_t recv_size = ::recv(sockfd, buf, bufSize, 0);

        message = std::string(buf);

        delete[] buf;
        return recv_size;
    }

    int Connector::terminate()
    {
        if (isConnected())
            closeValue = close(sockfd);

        return closeValue;
    }

    bool Connector::isConnected()
    {
        return connectingFlg;
    }
};