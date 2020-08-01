//
// Created by KHML on 2019-07-29.
//

#ifndef SOCKNET_CONNECTOR_HPP
#define SOCKNET_CONNECTOR_HPP

#include <cstddef>
#include <string>

namespace socknet
{
    class Connector
    {
    public:
        explicit Connector(int sockfd);

        Connector(const Connector& orig);

        virtual ~Connector();

        const int sockfd;

        ssize_t send(const std::string& message) const;

        ssize_t receive(std::string& message, size_t bufferSize) const;

        int terminate();

        bool isConnected() const;

    private:
        bool connectingFlg = true;
        int closeValue{0};
    };
}

#endif //SOCKNET_CONNECTOR_HPP
