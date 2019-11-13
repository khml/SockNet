//
// Created by KHML on 2019-07-29.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

#include "Client.hpp"
#include "Connector.hpp"

using std::cerr;
using std::endl;
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
            cerr << "socket Error" << endl;
        }

    }

    Client::~Client()
    {}

    bool Client::getConnect()
    {
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons (portNumber);
        addr.sin_addr.s_addr = inet_addr(address.c_str());

        if (connect(connector.sockfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_in)) < 0)
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

    void Client::sendMessage(const string& message)
    {
        if (connector.writeMessage(message) < 0)
        {
            cerr << "socket write err" << endl;
            terminate();
        }
    }

    string Client::receiveMessage(const size_t bufferSize)
    {
        string message;
        ssize_t recv_size = connector.readMessage(message, bufferSize);

        if (recv_size <= 0)
        {
            if (recv_size < 0)
                cerr << "socket recv err" << endl;
            terminate();
        }

        return message;
    }

}