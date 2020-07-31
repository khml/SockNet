//
// Created by KHML on 2019-07-29.
//

#include <unistd.h>
#include <sys/socket.h>
#include <cstring>

#include <socknet/utilities.hpp>
#include <socknet/connector.hpp>

namespace sockNet
{
    Connector::Connector(const int sockfd) :sockfd(sockfd)
    {}

    Connector::Connector(const Connector& orig) :sockfd(orig.sockfd)
    {}

    Connector::~Connector()
    = default;

    ssize_t Connector::send(const std::string& message) const
    {
        return ::write(sockfd, message.c_str(), (size_t) sizeof(char) * message.size());
    }

    ssize_t Connector::receive(std::string& message, const size_t bufferSize) const
    {
        char* buf = new char[bufferSize];
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

    bool Connector::isConnected() const
    {
        return connectingFlg;
    }
};