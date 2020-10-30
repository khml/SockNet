//
// Created by KHML on 2019-07-29.
//

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
            ssize_t write_size = core::send(sockfd, message);
            if (write_size < 0)
                connectingFlg = false;
            return write_size;
        }

        ssize_t Connector::receive(std::string& message, const size_t bufferSize)
        {
            ssize_t recv_size = core::receive(sockfd, message, bufferSize);
            if (recv_size < 0)
                connectingFlg = false;
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