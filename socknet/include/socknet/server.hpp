//
// Created by KHML on 2019-07-29.
//

#ifndef SOCKNET_SERVER_HPP
#define SOCKNET_SERVER_HPP

#include <netinet/in.h>
#include <string>
#include <vector>

#include <socknet/endpoint.hpp>

namespace sockNet
{
    class Server
    {
    public:
        explicit Server(ushort portNumber);

        ~Server();

        EndPoint listen();

        void terminate();

        bool isSocketOpen() const;

        std::vector<std::string> errors;

    protected:
        int sockfd;
        ::sockaddr_in addr{};
        bool connectingFlg = false;
    };

}

#endif //SOCKNET_SERVER_HPP
