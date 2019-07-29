//
// Created by KHML on 2019-07-29.
//

#ifndef SOCKNET_SERVER_HPP
#define SOCKNET_SERVER_HPP


#include <netinet/in.h>
#include <string>

#include "Connector.hpp"

namespace sockNet
{
    class EndPoint
    {
    public:
        EndPoint(int clientSockfd, socklen_t len);

        EndPoint(const EndPoint &orig);

        virtual ~EndPoint();

        std::string receiveMessage(size_t bufferSize);

        void sendMessage(std::string message);

        void terminate();

        bool isConnecting();

    protected:
        Connector connector;
        sockaddr_in fromAddr;
        bool connectingFlg;
    };

    class Server
    {
    public:
        Server(ushort portNumber);

        ~Server();

        EndPoint listenForAccess();

        void terminate();

        bool isSocketOpen();

    protected:
        int sockfd;
        sockaddr_in addr;
        bool connectingFlg;
    };

}


#endif //SOCKNET_SERVER_HPP
