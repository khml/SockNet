//
// Created by KHML on 2020/08/09.
//
#include <arpa/inet.h>
#include <chrono>
#include <thread>

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <socknet/core/sockapis.hpp>

static const uint PORT = 1234;
static const char* ADDREESS = "127.0.0.1";

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
    const std::string address(ADDREESS);
    socknet::core::setSockaddr(addr2, PORT, address);
    EXPECT_EQ(addr2.sin_family, AF_INET);
    EXPECT_EQ(addr2.sin_port, htons(PORT));
    EXPECT_EQ(addr2.sin_addr.s_addr, ::inet_addr(ADDREESS));
}

TEST(TestCoreSockapis, createSocket)
{
    int sockfd = socknet::core::createSocket();
    EXPECT_GE(sockfd, 0);
    ::close(sockfd);
}

TEST(TestCoreSockapis, bindSocket)
{
    // bindSocket(const int& sockfd, const struct ::sockaddr_in& addr)
    int sockfd = socknet::core::createSocket();
    ASSERT_GT(sockfd, 0);

    struct ::sockaddr_in addr = socknet::core::createAddr(PORT);
    EXPECT_EQ(addr.sin_family, AF_INET);
    EXPECT_EQ(addr.sin_addr.s_addr, INADDR_ANY);
    EXPECT_EQ(addr.sin_port, htons(PORT));

    int bindResult = socknet::core::bindSocket(sockfd, addr);
    EXPECT_GE(bindResult, 0);
    ::close(sockfd);

    //bindSocket(const int& sockfd, uint16_t port)
    sockfd = socknet::core::createSocket();
    ASSERT_GE(sockfd, 0);

    bindResult = socknet::core::bindSocket(sockfd, PORT);
    EXPECT_GE(bindResult, 0);
    ::close(sockfd);

    //bindSocket(const int& sockfd, struct ::sockaddr_in& addr, uint16_t port)
    sockfd = socknet::core::createSocket();
    ASSERT_GE(sockfd, 0);

    addr = ::sockaddr_in{};

    bindResult = socknet::core::bindSocket(sockfd, addr, PORT);
    EXPECT_GE(bindResult, 0);
    EXPECT_EQ(addr.sin_family, AF_INET);
    EXPECT_EQ(addr.sin_addr.s_addr, INADDR_ANY);
    EXPECT_EQ(addr.sin_port, htons(PORT));
    ::close(sockfd);
}

TEST(TestCoreSockapis, listenSocket)
{
    //server
    auto server = [](){
        int sockfd = socknet::core::createSocket();
        ASSERT_GT(sockfd, 0);

        struct ::sockaddr_in addr = socknet::core::createAddr(PORT);
        EXPECT_EQ(addr.sin_family, AF_INET);
        EXPECT_EQ(addr.sin_addr.s_addr, INADDR_ANY);
        EXPECT_EQ(addr.sin_port, htons(PORT));

        int bindResult = socknet::core::bindSocket(sockfd, addr);
        ASSERT_GE(bindResult, 0);

        int listenResult = socknet::core::listenSocket(sockfd);
        ASSERT_GE(listenResult, 0);

        struct ::sockaddr_in dstAddr{};
        ::socklen_t dstAddrSize = sizeof(dstAddr);
        int dstSockfd = ::accept(sockfd, (struct ::sockaddr*) &dstAddr, &dstAddrSize);
        ::close(sockfd);
        ::close(dstSockfd);
    };
    std::thread serverThread(server);

    // clientThread
    auto client = []()
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        int sockfdClient = socknet::core::createSocket();
        ASSERT_GT(sockfdClient, 0);

        const std::string address(ADDREESS);
        struct ::sockaddr_in addrClient = socknet::core::createAddr(PORT, address);
        EXPECT_EQ(addrClient.sin_family, AF_INET);
        EXPECT_EQ(addrClient.sin_port, htons(PORT));
        EXPECT_EQ(addrClient.sin_addr.s_addr, ::inet_addr(ADDREESS));

        int connectResult = ::connect(sockfdClient, (struct ::sockaddr*) &addrClient, sizeof(struct ::sockaddr_in));
        ASSERT_GE(connectResult, 0);
        ::close(connectResult);
    };
    std::thread clientThread(client);


    // server side join
    serverThread.join();
    clientThread.join();
}
