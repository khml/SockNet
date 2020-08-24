//
// Created by KHML on 2019-07-29.
//

#include <unistd.h>
#include <sys/socket.h>
#include <cstring>

#include <socknet/core/sockapis.hpp>
#include <socknet/core/connector.hpp>

namespace socknet
{
    namespace core
    {
        Connector::Connector(const int sockfd) :sockfd(sockfd)
        {}

        Connector::Connector(const Connector& orig) :sockfd(orig.sockfd)
        {}

        Connector::~Connector()
        {
            terminate();
        }

        ssize_t Connector::send(const std::string& message)
        {
            ssize_t write_size = ::write(sockfd, message.c_str(), (size_t) sizeof(char) * message.size());

            if (write_size < 0)
                connectingFlg = false;

            return write_size;
        }

        ssize_t Connector::receive(std::string& message, const size_t bufferSize)
        {
            char* buf = new char[bufferSize];
            size_t bufSize = sizeof(char) * bufferSize;
            std::memset(buf, 0, bufSize);

            ssize_t recv_size = ::recv(sockfd, buf, bufSize, 0);
            if (recv_size < 0)
                connectingFlg = false;

            message = std::string(buf);

            delete[] buf;
            return recv_size;
        }

        int Connector::terminate()
        {
            if (!isConnected())
                return closeValue;

            closeValue = core::closeSocket(sockfd);
            connectingFlg = false;

            return closeValue;
        }

        bool Connector::isConnected() const
        {
            return connectingFlg;
        }
    }
}