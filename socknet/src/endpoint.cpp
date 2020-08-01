//
// Created by KHML on 2020/07/28.
//

#include <socknet/endpoint.hpp>

namespace socknet
{
    EndPoint::EndPoint(const int clientSockfd, ::socklen_t len) :
        connector(::accept(clientSockfd, (struct ::sockaddr*) &fromAddr, &len))
    {
        if (!connector.isConnected())
            errors.emplace_back("accept Error");
    }

    EndPoint::EndPoint(const EndPoint& orig) :connector(orig.connector), fromAddr(orig.fromAddr)
    {}

    EndPoint::~EndPoint()
    {
        terminate();
    }

    bool EndPoint::isConnecting() const
    {
        return connector.isConnected();
    }

    void EndPoint::terminate()
    {
        if (isConnecting())
            connector.terminate();
    }

    std::string EndPoint::receive(const size_t bufferSize)
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

    void EndPoint::send(const std::string& message)
    {
        if (connector.send(message) < 0)
            errors.emplace_back("socket write error");
    }
}
