//
// Created by KHML on 2020/07/28.
//

#include <unistd.h>

#include <socknet/core/utilities.hpp>

namespace socknet
{
    namespace core
    {
        int closeSocket(const int sockfd)
        {
            return ::close(sockfd);
        }
    }
}
