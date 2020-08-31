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
