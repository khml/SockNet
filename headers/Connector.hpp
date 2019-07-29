//
// Created by KHML on 2019-07-29.
//

#ifndef SOCKNET_CONNECTOR_HPP
#define SOCKNET_CONNECTOR_HPP


#include <cstddef>
#include <string>

namespace sockNet
{
    int closeSocket(int sockfd);

    class Connector
    {
    public:
        Connector(int sockfd);

        Connector(const Connector &orig);

        virtual ~Connector();

        const int sockfd;

        ssize_t writeMessage(const std::string& message);

        ssize_t readMessage(std::string &message, size_t bufferSize);

        int terminate();

        bool isConnected();

    protected:
        bool connectingFlg = true;
        int closeValue = 0;
    };
}


#endif //SOCKNET_CONNECTOR_HPP
