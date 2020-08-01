//
// Created by KHML on 2019-07-29.
//

#ifndef SOCKNET_SERVER_HPP
#define SOCKNET_SERVER_HPP

#include <netinet/in.h>
#include <string>
#include <vector>

#include <socknet/connetion.hpp>

namespace socknet
{
    class Server
    {
    public:
        explicit Server(uint16_t portNumber);

        ~Server();

        Connection listen();

        void terminate();

        bool isSocketOpened() const;

        std::vector<std::string> errors;

    private:
        const int sockfd;
        ::sockaddr_in addr{};
        bool connectingFlg = false;
    };

}

#endif //SOCKNET_SERVER_HPP
