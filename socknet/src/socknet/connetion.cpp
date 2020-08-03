//
// Created by KHML on 2020/07/28.
//

#include <socknet/connetion.hpp>

namespace socknet
{
    Connection::Connection(const int sockfdListened) :clientAddrSize(sizeof(clientAddr)),
        connector(::accept(sockfdListened, (struct ::sockaddr*) &clientAddr, &clientAddrSize))
    {
        if (!connector.isConnected())
            errors.emplace_back("accept Error");
    }

    Connection::Connection(const Connection& orig) :clientAddrSize(orig.clientAddrSize), clientAddr(orig.clientAddr),
        connector(orig.connector)
    {}

    Connection::~Connection()
    {
        terminate();
    }

    bool Connection::isConnecting() const
    {
        return connector.isConnected();
    }

    void Connection::terminate()
    {
        if (isConnecting())
            connector.terminate();
    }

    std::string Connection::receive(const size_t bufferSize)
    {
        std::string message;
        ssize_t recv_size = connector.receive(message, bufferSize);

        if (recv_size <= 0)
        {
            if (recv_size < 0)
                errors.emplace_back("socket recv Error");
            terminate();
        }

        return message;
    }

    void Connection::send(const std::string& message)
    {
        if (connector.send(message) < 0)
            errors.emplace_back("socket write error");
    }
}
