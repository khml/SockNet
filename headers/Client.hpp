//
// Created by KHML on 2019-07-29.
//

#ifndef SOCKNET_CLIENT_HPP
#define SOCKNET_CLIENT_HPP

#include <string>

#include "Connector.hpp"

namespace sockNet
{
    class Client
    {
    public:
        Client(std::string address, unsigned short portNumber);

        virtual ~Client();

        bool getConnect();

        void terminate();

        void sendMessage(const std::string& message);

        std::string receiveMessage(size_t bufferSize);

        bool isConnecting();

    protected:
        Connector connector;
        const std::string address;
        const unsigned short portNumber;
        bool connectingFlg;
    };

}


#endif //SOCKNET_CLIENT_HPP
