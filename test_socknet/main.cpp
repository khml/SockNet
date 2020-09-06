//
// Created by KHML on 2020/08/09.
//
#include <arpa/inet.h>

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <socknet/core/sockapis.hpp>

static const uint PORT = 1234;

TEST(TestCoreSockapis, createAddr)
{
    struct ::sockaddr_in addr = socknet::core::createAddr(PORT);
    EXPECT_EQ(addr.sin_family, AF_INET);
    EXPECT_EQ(addr.sin_addr.s_addr, INADDR_ANY);
    EXPECT_EQ(addr.sin_port, htons(PORT));

    const std::string address = "127.0.0.1";
    addr = socknet::core::createAddr(PORT, address);
    EXPECT_EQ(addr.sin_family, AF_INET);
    EXPECT_EQ(addr.sin_port, htons(PORT));
    EXPECT_EQ(addr.sin_addr.s_addr, ::inet_addr(address.c_str()));
}

TEST(TestCoreSockapis, setSockaddr)
{
    struct ::sockaddr_in addr1{};
    socknet::core::setSockaddr(addr1, PORT);
    EXPECT_EQ(addr1.sin_family, AF_INET);
    EXPECT_EQ(addr1.sin_addr.s_addr, INADDR_ANY);
    EXPECT_EQ(addr1.sin_port, htons(PORT));

    struct ::sockaddr_in addr2{};
    const std::string address = "127.0.0.1";
    socknet::core::setSockaddr(addr2, PORT, address);
    EXPECT_EQ(addr2.sin_family, AF_INET);
    EXPECT_EQ(addr2.sin_port, htons(PORT));
    EXPECT_EQ(addr2.sin_addr.s_addr, ::inet_addr(address.c_str()));
}

TEST(TestCoreSockapis, createSocket)
{
    int sockfd = socknet::core::createSocket();
    EXPECT_GE(sockfd, 0);
    ::close(sockfd);
}