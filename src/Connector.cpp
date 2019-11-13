//
// Created by KHML on 2019-07-29.
//

#include <unistd.h>
#include <sys/socket.h>

#include "Connector.hpp"

using std::string;

namespace sockNet
{
    int closeSocket(int sockfd)
    {
        return close(sockfd);
    }

    Connector::Connector(int sockfd) : sockfd(sockfd)
    {}

    Connector::Connector(const Connector &orig) : sockfd(orig.sockfd)
    {}


    Connector::~Connector()
    {}

    ssize_t Connector::writeMessage(const string& message)
    {
        return write(sockfd, message.c_str(), (size_t) sizeof(char) * message.size());
    }

    ssize_t Connector::readMessage(string &message, const size_t bufferSize)
    {
        char *buf = new char[bufferSize];
        size_t bufSize = sizeof(char) * bufferSize;
        memset(buf, 0, bufSize);

        ssize_t recv_size = recv(sockfd, buf, bufSize, 0);

        message = string(buf);

        delete[] buf;
        return recv_size;
    }

    int Connector::terminate()
    {
        if (isConnected())
            closeValue = closeSocket(sockfd);

        return closeValue;
    }

    bool Connector::isConnected()
    {
        return connectingFlg;
    }
};