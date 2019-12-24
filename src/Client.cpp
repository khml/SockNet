//
// Created by KHML on 2019-07-29.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "Connector.hpp"
#include "Client.hpp"

using std::string;

namespace sockNet
{
    Client::Client(string address, unsigned short portNumber) : address(address), portNumber(portNumber),
                                                                connector(socket(AF_INET, SOCK_STREAM, 0))
    {
        if (connector.isConnected())
            connectingFlg = true;
        else
        {
            connectingFlg = false;
            errors.emplace_back("socket Error");
        }

    }

    Client::~Client()
    {}

    bool Client::connect()
    {
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons (portNumber);
        addr.sin_addr.s_addr = ::inet_addr(address.c_str());

        if (::connect(connector.sockfd, (struct ::sockaddr *) &addr, sizeof(struct ::sockaddr_in)) < 0)
            terminate();

        return isConnecting();
    }

    void Client::terminate()
    {
        if (!isConnecting())
            return;

        connector.terminate();
        connectingFlg = false;
    }

    bool Client::isConnecting()
    {
        return connectingFlg;
    }

    void Client::send(const string& message)
    {
        if (connector.send(message) < 0)
        {
            errors.emplace_back("socket write error");
            terminate();
        }
    }

    string Client::receive(size_t bufferSize)
    {
        string message;
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