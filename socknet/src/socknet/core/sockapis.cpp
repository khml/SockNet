//
// Created by KHML on 2020/07/28.
//

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <stdexcept>

#include <socknet/core/sockapis.hpp>

namespace socknet
{
    namespace core
    {
        ::sockaddr_in createAddr(const uint16_t portNumber)
        {
            struct ::sockaddr_in addr{};
            setSockaddr(addr, portNumber);
            return addr;
        }

        ::sockaddr_in createAddr(const uint16_t portNumber, const std::string& address)
        {
            struct ::sockaddr_in addr{};
            setSockaddr(addr, portNumber, address);
            return addr;
        }

        void setSockaddr(sockaddr_in& addr, uint16_t port)
        {
            addr.sin_family = AF_INET;
            addr.sin_port = htons(port);
            addr.sin_addr.s_addr = INADDR_ANY;
        }

        void setSockaddr(sockaddr_in& addr, uint16_t port, const std::string& address)
        {
            addr.sin_family = AF_INET;
            addr.sin_port = htons(port);
            addr.sin_addr.s_addr = ::inet_addr(address.c_str());
        }

        int createSocket()
        {
            return ::socket(AF_INET, SOCK_STREAM, 0);
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
            (void) setSockaddr(addr, portNumber);
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

        int connectSocket(const int& sockfd, const sockaddr_in& addr)
        {
            return ::connect(sockfd, (struct ::sockaddr*) &addr, sizeof(struct ::sockaddr_in));
        }

        int connectSocket(const int& sockfd, const std::string& address, const uint16_t port)
        {
            struct ::sockaddr_in addr{};
            setSockaddr(addr, port, address);
            return connectSocket(sockfd, addr);
        }

        int connectSocket(const int& sockfd, sockaddr_in& addr, const std::string& address, uint16_t port)
        {
            setSockaddr(addr, port, address);
            return connectSocket(sockfd, addr);
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
