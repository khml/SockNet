//
// Created by KHML on 2020/07/28.
//

#ifndef SOCKNET_CONNETION_HPP
#define SOCKNET_CONNETION_HPP

#include <netinet/in.h>
#include <vector>

#include <socknet/core/connector.hpp>

namespace socknet
{
    class Connection
    {
    public:
        Connection(int clientSockfd, ::socklen_t len);

        Connection(const Connection& orig);

        virtual ~Connection();

        std::string receive(size_t bufferSize);

        void send(const std::string& message);

        std::vector<std::string> errors;

        void terminate();

        bool isConnecting() const;

    private:
        core::Connector connector;
        ::sockaddr_in fromAddr{};
    };
}

#endif //SOCKNET_CONNETION_HPP
