/**
 * @file socknet/core/sockapis.hpp
 * @brief socket API module
 * @date  2020/07/28 Created on
 * @author KHML
 */

#ifndef SOCKNET_SOCKAPIS_HPP
#define SOCKNET_SOCKAPIS_HPP

#include <errno.h>
#include <netinet/in.h>
#include <cstddef>
#include <string>

namespace socknet
{
    namespace core
    {
        /**
         * createAddr(uint16_t port)
         * @brief create ::sockaddr_in instance and set port number
         * @param port
         * @return ::sockaddr_in
         * @sa setSockaddr(struct ::sockaddr_in& addr, uint16_t port)
         * @detail create ::sockaddr_in instance and set port number.
         *         sin_family = AF_INET
         *         sin_addr.s_addr = INADDR_ANY
         */
        struct ::sockaddr_in createAddr(uint16_t port);

        /**
         * createAddr(uint16_t port, const std::string& address)
         * @brief create ::sockaddr_in instance, set port number and address
         * @param port
         * @param address
         * @return ::sockaddr_in
         * @sa setSockaddr(struct ::sockaddr_in& addr, uint16_t port, const std::string& address)
         * @detail create ::sockaddr_in instance and set port number.
         *         sin_family = AF_INET
         *         sin_addr.s_addr = ::inet_addr(address.c_str())
         */
        struct ::sockaddr_in createAddr(uint16_t port, const std::string& address);

        /**
         * setSockaddr(struct ::sockaddr_in& addr, uint16_t port)
         * @brief setting ::sockaddr_in#sin_port to given port number
         * @param port
         * @return ::sockaddr_in
         * @detail setting ::sockaddr_in#sin_port to given port number.
         *         sin_family = AF_INET
         *         sin_addr.s_addr = INADDR_ANY
         */
        void setSockaddr(struct ::sockaddr_in& addr, uint16_t port);

        /**
         * setSockaddr(struct ::sockaddr_in& addr, uint16_t port, const std::string& address)
         * @brief setting port number and address
         * @param port
         * @param address
         * @return ::sockaddr_in
         * @detail setting ::sockaddr_in#sin_port to given port number.
         *         sin_family = AF_INET
         *         sin_addr.s_addr = ::inet_addr(address.c_str())
         */
        void setSockaddr(struct ::sockaddr_in& addr, uint16_t port, const std::string& address);

        /**
         * createSocket()
         * @brief call socket function
         * @return sockfd
         * @detail ::socket(AF_INET, SOCK_STREAM, 0)
         */
        int createSocket();

        /**
         * bindSocket(const int& sockfd, const struct ::sockaddr_in& addr)
         * @brief call bind function
         * @param sockfd - srcSockfd
         * @param addr - srcAddr
         * @return bind result
         * @detail ::bind(sockfd, (struct sockaddr*) &addr, sizeof(addr))
         */
        int bindSocket(const int& sockfd, const struct ::sockaddr_in& addr);

        /**
         * bindSocket(const int& sockfd, uint16_t port)
         * @brief call bind function
         * @param sockfd - srcSockfd
         * @param port
         * @return bind result
         * @sa bindSocket(const int& sockfd, const struct ::sockaddr_in& addr)
         * @sa struct ::sockaddr_in createAddr(uint16_t port)
         */
        int bindSocket(const int& sockfd, uint16_t port);

        /**
         * bindSocket(const int& sockfd, struct ::sockaddr_in& addr, uint16_t port)
         * @brief call bind function
         * @param sockfd - srcSockfd
         * @param addr - srcAddr
         * @param port
         * @return bind result
         * @sa bindSocket(const int& sockfd, const struct ::sockaddr_in& addr)
         * @sa setSockaddr(struct ::sockaddr_in& addr, uint16_t port)
         */
        int bindSocket(const int& sockfd, struct ::sockaddr_in& addr, uint16_t port);

        /**
         * listenSocket(const int& sockfd)
         * @brief call listen function
         * @param sockfd - srcSockfd
         * @return listen result
         * @details ::listen(sockfd, SOMAXCONN)
         */
        int listenSocket(const int& sockfd);

        /**
         * acceptSocket(const int& sockfd, struct ::sockaddr_in& dstAddr)
         * @brief call accept function
         * @param sockfd - srcSockfd
         * @param addr - dstAddr
         * @return dstSockfd
         */
        int acceptSocket(const int& sockfd, struct ::sockaddr_in& addr);

        /**
         * connectSocket(const int& sockfd, const struct ::sockaddr_in& addr)
         * @brief connect result
         * @param sockfd
         * @param addr
         * @return connect result
         * @details ::connect(sockfd, (struct ::sockaddr*) &addr, sizeof(struct ::sockaddr_in)
         */
        int connectSocket(const int& sockfd, const struct ::sockaddr_in& addr);

        /**
         * connectSocket(const int& sockfd, const std::string& address, uint16_t port)
         * @brief connect result
         * @param sockfd - srcSockfd
         * @param address - dstAddress
         * @param port
         * @return connect result
         * @sa connectSocket(const int& sockfd, const struct ::sockaddr_in& addr)
         */
        int connectSocket(const int& sockfd, const std::string& address, uint16_t port);

        /**
         * connectSocket(const int& sockfd, struct ::sockaddr_in& addr, const std::string& address, uint16_t port)
         * @brief connect result
         * @param sockfd - srcSockfd
         * @param addr - srcAddr
         * @param address - dstAddr
         * @param port
         * @return connect result
         * @sa connectSocket(const int& sockfd, const struct ::sockaddr_in& addr)
         */
        int connectSocket(const int& sockfd, struct ::sockaddr_in& addr, const std::string& address, uint16_t port);

        /**
         * waitConnection(const int& sockfd, struct ::sockaddr_in& clientAddr)
         * @brief listen and accept socket
         * @param sockfd -srcSockfd
         * @param addr - dstAddr
         * @return dstSockfd
         * @sa listenSocket(const int& sockfd)
         * @sa acceptSocket(const int& sockfd, struct ::sockaddr_in& dstAddr)
         * @details listen and accept socket. if listen result < 0, throw runtime error
         */
        int waitConnection(const int& sockfd, struct ::sockaddr_in& addr);

        /**
         * send(const int& sockfd, const std::string& message)
         * @brief call write function, send message
         * @param sockfd
         * @param message
         * @return write result
         * @details ::write(sockfd, message.c_str(), (size_t) sizeof(char) * message.size())
         */
        ssize_t send(const int& sockfd, const std::string& message);

        /**
         * receive(const int& sockfd, std::string& message, size_t bufferSize)
         * @brief call recv function
         * @param sockfd
         * @param message
         * @param bufferSize
         * @return recv result
         */
        ssize_t receive(const int& sockfd, std::string& message, size_t bufferSize);

        /**
         * receive(const int& sockfd
         * @brief receive message
         * @param sockfd
         * @return recieved message
         */
        std::string receive(const int& sockfd);

        /**
         * closeSocket(const int& sockfd)
         * @brief close socket
         * @param sockfd
         * @return close result
         * @details ::close(sockfd)
         */
        int closeSocket(const int& sockfd);

        std::string bindError(::errno_t error);
    }
}

#endif //SOCKNET_SOCKAPIS_HPP
