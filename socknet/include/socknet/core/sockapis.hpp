//
// Created by KHML on 2020/07/28.
//

#ifndef SOCKNET_SOCKAPIS_HPP
#define SOCKNET_SOCKAPIS_HPP

#include <netinet/in.h>
#include <cstddef>
#include <string>

namespace socknet
{
    namespace core
    {
        struct ::sockaddr_in createAddr(uint16_t portNumber);

        struct ::sockaddr_in createAddr(uint16_t portNumber, const std::string& address);

        void setSockaddr(struct ::sockaddr_in& addr, uint16_t port);

        void setSockaddr(struct ::sockaddr_in& addr, uint16_t port, const std::string& address);

        int createSocket();

        int bindSocket(const int& sockfd, const struct ::sockaddr_in& addr);

        int bindSocket(const int& sockfd, uint16_t portNumber);

        int bindSocket(const int& sockfd, struct ::sockaddr_in& addr, uint16_t portNumber);

        int listenSocket(const int& sockfd);

        int acceptSocket(const int& sockfd, struct ::sockaddr_in& clientAddr);

        int connectSocket(const int& sockfd, const struct ::sockaddr_in& addr);

        int connectSocket(const int& sockfd, const std::string& address, uint16_t port);

        int connectSocket(const int& sockfd, struct ::sockaddr_in& addr, const std::string& address, uint16_t port);

        int waitConnection(const int& sockfd, struct ::sockaddr_in& clientAddr);

        ssize_t send(const int& sockfd, const std::string& message);

        ssize_t receive(const int& sockfd, std::string& message, size_t bufferSize);

        int closeSocket(const int& sockfd);
    }
}

#endif //SOCKNET_SOCKAPIS_HPP
