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
        ::sockaddr_in createAddr(const uint16_t port)
        {
            struct ::sockaddr_in addr{};
            setSockaddr(addr, port);
            return addr;
        }

        ::sockaddr_in createAddr(const uint16_t port, const std::string& address)
        {
            struct ::sockaddr_in addr{};
            setSockaddr(addr, port, address);
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

        int bindSocket(const int& sockfd, uint16_t port)
        {
            struct ::sockaddr_in addr = createAddr(port);
            return bindSocket(sockfd, addr);
        }

        int bindSocket(const int& sockfd, sockaddr_in& addr, const uint16_t port)
        {
            (void) setSockaddr(addr, port);
            return bindSocket(sockfd, addr);
        }

        int listenSocket(const int& sockfd)
        {
            return ::listen(sockfd, SOMAXCONN);
        }

        int acceptSocket(const int& sockfd, sockaddr_in& addr)
        {
            ::socklen_t dstAddrSize = sizeof(addr);
            return ::accept(sockfd, (struct ::sockaddr*) &addr, &dstAddrSize);
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

        int waitConnection(const int& sockfd, sockaddr_in& addr)
        {
            if (listenSocket(sockfd) < 0)
                throw std::runtime_error("listen socket error");
            return acceptSocket(sockfd, addr);
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

        std::string receive(const int& sockfd)
        {
            static size_t bufferSize = 1024;

            std::string result;

            char* buf = new char[bufferSize];
            const size_t bufSize = sizeof(char) * bufferSize;
            std::memset(buf, 0, bufSize);

            while (::recv(sockfd, buf, bufSize, 0) > 0)
            {
                result += std::string(buf);
                std::memset(buf, 0, bufSize);
            }

            return result;
        }

        int closeSocket(const int& sockfd)
        {
            return ::close(sockfd);
        }

        std::string bindError(::errno_t error)
        {
            switch (error)
            {
                case EACCES:
                    return "The requested address is protected, and the current user has inadequate permission to access it.A component of the path prefix does not allow searching or the node's parent directory denies write permission.";
                case EADDRINUSE:
                    return "The specified address is already in use.";
                case EADDRNOTAVAIL:
                    return "The specified address is not available from the local machine.";
                case EAFNOSUPPORT:
                    return "address is not valid for the address family of socket.";
                case EBADF:
                    return "socket is not a valid file descriptor.";
                case EDESTADDRREQ:
                    return "socket is a null pointer.";
                case EFAULT:
                    return "The address parameter is not in a valid part of the user address space.";
                case EINVAL:
                    return "socket is already bound to an address and the protocol does not support binding to a new address.  Alternatively, socket may have been shut down.";
                case ENOTSOCK:
                    return "socket does not refer to a socket.";
                case EOPNOTSUPP:
                    return "socket is not of a type that can be bound to an address.";
                case EEXIST:
                    return "A file already exists at the pathname.  unlink(2) it first.";
                case EIO:
                    return "An I/O error occurred while making the directory entry or allocating the inode";
                case EISDIR:
                    return "An empty pathname was specified.";
                case ELOOP:
                    return "Too many symbolic links were encountered in translating the pathname.  This is taken to be indicative of a looping symbolic link.";
                case ENAMETOOLONG:
                    return "A component of a pathname exceeded {NAME_MAX} characters, or an entire path name exceeded {PATH_MAX} characters.";
                case ENOENT:
                    return "A component of the path name does not refer to an existing file.";
                case ENOTDIR:
                    return "A component of the path prefix is not a directory.";
                case EROFS:
                    return "The name would reside on a read-only file system.";
                default:
                    return "Unknown Error";
            }
        }
    }
}
