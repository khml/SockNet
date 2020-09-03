//
// Created by KHML on 2020/08/09.
//
#include <arpa/inet.h>

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <socknet/core/sockapis.hpp>

TEST(TestCoreSockapis, createAddr)
{
    const uint16_t port = 1234;
    struct ::sockaddr_in addr = socknet::core::createAddr(port);
    EXPECT_EQ(addr.sin_family, AF_INET);
    EXPECT_EQ(addr.sin_addr.s_addr, INADDR_ANY);
    EXPECT_EQ(addr.sin_port, htons(port));

    const std::string address = "127.0.0.1";
    addr = socknet::core::createAddr(port, address);
    EXPECT_EQ(addr.sin_family, AF_INET);
    EXPECT_EQ(addr.sin_port, htons(port));
    EXPECT_EQ(addr.sin_addr.s_addr, ::inet_addr(address.c_str()));
}

TEST(TestCoreSockapis, setSockaddr)
{
    const uint16_t port = 1234;
    struct ::sockaddr_in addr1{};
    socknet::core::setSockaddr(addr1, port);
    EXPECT_EQ(addr1.sin_family, AF_INET);
    EXPECT_EQ(addr1.sin_addr.s_addr, INADDR_ANY);
    EXPECT_EQ(addr1.sin_port, htons(port));

    struct ::sockaddr_in addr2{};
    const std::string address = "127.0.0.1";
    socknet::core::setSockaddr(addr2, port, address);
    EXPECT_EQ(addr2.sin_family, AF_INET);
    EXPECT_EQ(addr2.sin_port, htons(port));
    EXPECT_EQ(addr2.sin_addr.s_addr, ::inet_addr(address.c_str()));
}

TEST(TestCoreSockapis, createSocket)
{
    int sockfd = socknet::core::createSocket();
    EXPECT_GT(sockfd, 1);
    ::close(sockfd);
}