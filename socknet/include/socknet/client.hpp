//
// Created by KHML on 2019-07-29.
//

#ifndef SOCKNET_CLIENT_HPP
#define SOCKNET_CLIENT_HPP

#include <string>
#include <vector>

#include <socknet/core/connector.hpp>

namespace socknet
{
    class Client
    {
    public:
        Client(std::string address, uint16_t portNumber);

        virtual ~Client();

        bool connect();

        void terminate();

        void send(const std::string& message);

        std::string receive(size_t bufferSize);

        std::vector<std::string> errors;

        bool isConnecting() const;

    private:
        core::Connector connector;
        const std::string address;
        const unsigned short portNumber;
    };

}

#endif //SOCKNET_CLIENT_HPP
