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
        explicit Connection(int sockfdListened);

        Connection(const Connection& orig);

        virtual ~Connection();

        std::string receive(size_t bufferSize);

        void send(const std::string& message);

        std::vector<std::string> errors;

        void terminate();

        bool isConnecting() const;

    private:
        ::sockaddr_in dstAddr{};
        core::Connector connector;
    };
}

#endif //SOCKNET_CONNETION_HPP
