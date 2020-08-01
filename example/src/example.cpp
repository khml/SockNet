//
// Created by KHML
//

#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>

#include <socknet/socknet.hpp>

using std::string;

#define BUFFER_SIZE 1024

void server();

void client();

void bothMode();

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        bothMode();
        return 0;
    }

    string mode;
    mode = argv[1];

    if (mode == "server")
        server();
    else if (mode == "client")
        client();
    else
        std::cerr << "unexpected error." << std::endl;

    return 0;
}

void server()
{
    socknet::Server server(1234);
    socknet::EndPoint endPoint = server.listen();

    while (true)
    {
        auto message = endPoint.receive(BUFFER_SIZE);
        if (!endPoint.isConnecting())
            break;
        std::cout << "server::receive : " << message << std::endl;

        string sendMessage("Message::");
        for (int i = 0; i < std::stoi(message); i++)
            sendMessage += "Hello";

        endPoint.send(sendMessage);
        std::cout << "server::send    : " << sendMessage << std::endl;
    }

    endPoint.terminate();
    server.terminate();
}

void client()
{
    string address = "127.0.0.1";
    socknet::Client client(address, 1234);
    client.connect();

    string message;
    for (int i = 0; i < 10; i++)
    {
        message = std::to_string(i);
        std::cout << "client::send    : " << i << std::endl;
        client.send(message);
        message = client.receive(BUFFER_SIZE);
        std::cout << "client::receive : " << message << std::endl;
        sleep(1);
    }

    client.terminate();
}

void bothMode()
{
    std::thread serverThread(server);
    std::thread clientThread(client);

    serverThread.join();
    clientThread.join();
}
