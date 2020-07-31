//
// Created by KHML on 2020/07/28.
//

#include <unistd.h>

#include <socknet/utilities.hpp>

namespace sockNet
{
    int close(const int sockfd)
    {
        return ::close(sockfd);
    }
}
