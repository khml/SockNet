//
// Created by KHML on 2019-07-29.
//

#ifndef SOCKNET_SERVER_HPP
#define SOCKNET_SERVER_HPP


#include <netinet/in.h>
#include <string>
#include <vector>

#include "Connector.hpp"

namespace sockNet
{
    class EndPoint
    {
    public:
        EndPoint(int clientSockfd, ::socklen_t len);

        EndPoint(const EndPoint &orig);

        virtual ~EndPoint();

        std::string receive(size_t bufferSize);

        void send(const std::string& message);

        std::vector<std::string> errors;

        void terminate();

        bool isConnecting();

    protected:
        Connector connector;
        ::sockaddr_in fromAddr;
        bool connectingFlg;
    };

    class Server
    {
    public:
        Server(ushort portNumber);

        ~Server();

        EndPoint listen();

        void terminate();

        bool isSocketOpen();

        std::vector<std::string> errors;

    protected:
        int sockfd;
        ::sockaddr_in addr;
        bool connectingFlg = false;
    };

}


#endif //SOCKNET_SERVER_HPP
