//
// Created by KHML on 2019-07-29.
//

#include <utility>

#include <socknet/core/sockapis.hpp>
#include <socknet/core/connector.hpp>
#include <socknet/client.hpp>

namespace socknet
{
    Client::Client(std::string address, const uint16_t portNumber) :
        connector(core::createSocket()), address(std::move(address)), portNumber(portNumber)
    {}

    Client::~Client()
    = default;

    bool Client::connect()
    {
        struct ::sockaddr_in addr = core::createAddr(portNumber, address);

        if (core::connectSocket(connector.sockfd, addr) < 0)
            terminate();

        if (!connector.isConnected())
            errors.emplace_back("socket Error");

        return isConnecting();
    }

    void Client::terminate()
    {
        if (!isConnecting())
            return;

        connector.terminate();
    }

    bool Client::isConnecting() const
    {
        return connector.isConnected();
    }

    void Client::send(const std::string& message)
    {
        if (connector.send(message) < 0)
        {
            errors.emplace_back("socket write error");
            terminate();
        }
    }

    std::string Client::receive(const size_t bufferSize)
    {
        std::string message;
        ::ssize_t recv_size = connector.receive(message, bufferSize);

        if (recv_size <= 0)
        {
            if (recv_size < 0)
                errors.emplace_back("socket recv err");
            terminate();
        }

        return message;
    }

}