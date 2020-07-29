//
// Created by KHML
//

#include <iostream>
#include <string>
#include <unistd.h>

#include <socknet/server.hpp>
#include <socknet/client.hpp>

using std::string;
using std::cerr;
using std::endl;
using sockNet::Server;
using sockNet::Client;
using sockNet::EndPoint;

#define BUFFER_SIZE 1024

int server();

int client();


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "please select mode. server or client" << endl;
        exit(0);
    }

    string mode;
    mode = argv[1];

    if (mode == "server")
        server();
    else if (mode == "client")
        client();
    else
        cerr << "not exist such a mode " << mode << endl;

    return 0;
}

int server()
{
    Server server(1234);
    EndPoint endPoint = server.listen();

    while (true)
    {
        auto message = endPoint.receive(BUFFER_SIZE);
        if (!endPoint.isConnecting())
            break;
        cerr << "receive :: " << message << endl;

        string sendMessage("Message::");
        for (int i = 0; i < std::stoi(message); i++)
            sendMessage += "Hello";

        endPoint.send(sendMessage);
        cerr << "send :: " << sendMessage << endl;
    }

    endPoint.terminate();
    server.terminate();
    return 0;
}

int client()
{
    string address = "127.0.0.1";
    Client client(address, 1234);
    client.connect();

    string message;
    for (int i = 0; i < 10; i++)
    {
        message = std::to_string(i);
        cerr << "send : " << i << endl;
        client.send(message);
        message = client.receive(BUFFER_SIZE);
        cerr << "receive : " << message << endl;
        sleep(1);
    }

    client.terminate();
    return 0;
}
