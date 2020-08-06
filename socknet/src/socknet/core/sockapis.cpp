//
// Created by KHML on 2020/07/28.
//

#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <stdexcept>

#include <socknet/core/sockapis.hpp>

namespace socknet
{
    namespace core
    {
        int createSocket()
        {
            return ::socket(AF_INET, SOCK_STREAM, 0);
        }

        ::sockaddr_in createAddr(const uint16_t portNumber)
        {
            struct ::sockaddr_in addr{};
            bindPort(addr, portNumber);
            return addr;
        }

        void bindPort(sockaddr_in& addr, const uint16_t portNumber)
        {
            addr.sin_family = AF_INET;
            addr.sin_port = htons(portNumber);
            addr.sin_addr.s_addr = INADDR_ANY;
        }

        int bindSocket(const int& sockfd, const sockaddr_in& addr)
        {
            return ::bind(sockfd, (struct sockaddr*) &addr, sizeof(addr));
        }

        int bindSocket(const int& sockfd, uint16_t portNumber)
        {
            struct ::sockaddr_in addr = createAddr(portNumber);
            return bindSocket(sockfd, addr);
        }

        int bindSocket(const int& sockfd, sockaddr_in& addr, const uint16_t portNumber)
        {
            (void) bindPort(addr, portNumber);
            return bindSocket(sockfd, addr);
        }

        int listenSocket(const int& sockfd)
        {
            return ::listen(sockfd, SOMAXCONN);
        }

        int acceptSocket(const int& sockfd, sockaddr_in& clientAddr)
        {
            ::socklen_t clientAddrSize = sizeof(clientAddr);
            return ::accept(sockfd, (struct ::sockaddr*) &clientAddr, &clientAddrSize);
        }

        int waitConnection(const int& sockfd, sockaddr_in& clientAddr)
        {
            if (listenSocket(sockfd) < 0)
                throw std::runtime_error("listen socket error");
            return acceptSocket(sockfd, clientAddr);
        }

        ssize_t send(const int& sockfd, const std::string& message)
        {
            return ::write(sockfd, message.c_str(), (size_t) sizeof(char) * message.size());
        }

        ssize_t receive(const int& sockfd, std::string& message, const size_t bufferSize)
        {
            char* buf = new char[bufferSize];
            size_t bufSize = sizeof(char) * bufferSize;
            std::memset(buf, 0, bufSize);

            ssize_t recv_size = ::recv(sockfd, buf, bufSize, 0);

            message = std::string(buf);

            delete[] buf;
            return recv_size;
        }

        int closeSocket(const int& sockfd)
        {
            return ::close(sockfd);
        }
    }
}
