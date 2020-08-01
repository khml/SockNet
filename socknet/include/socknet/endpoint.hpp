//
// Created by KHML on 2020/07/28.
//

#ifndef SOCKNET_ENDPOINT_HPP
#define SOCKNET_ENDPOINT_HPP

#include <netinet/in.h>
#include <vector>

#include <socknet/connector.hpp>

namespace sockNet
{
    class EndPoint
    {
    public:
        EndPoint(int clientSockfd, ::socklen_t len);

        EndPoint(const EndPoint& orig);

        virtual ~EndPoint();

        std::string receive(size_t bufferSize);

        void send(const std::string& message);

        std::vector<std::string> errors;

        void terminate();

        bool isConnecting() const;

    private:
        Connector connector;
        ::sockaddr_in fromAddr{};
    };
}

#endif //SOCKNET_ENDPOINT_HPP
