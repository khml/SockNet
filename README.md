# SockNet
SockNet is tiny C++ socket wrapper.

# Install

```
$ git clone https://github.com/khml/SockNet.git
$ cd SockNet
$ mkdir build && cd build
$ cmake ../
$ make
$ make install
```


# Sample code
```
#include <iostream>
#include <string>
#include <unistd.h>

#include <SockNet/Server.hpp>
#include <SockNet/Client.hpp>

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
    EndPoint endPoint = server.listenForAccess();

    while (true)
    {
        auto message = endPoint.receiveMessage(BUFFER_SIZE);
        if (!endPoint.isConnecting())
            break;
        cerr << "receive :: " << message << endl;

        string sendMessage("Message::");
        for (int i = 0; i < std::stoi(message); i++)
            sendMessage += "Hello";

        endPoint.sendMessage(sendMessage);
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
    client.getConnect();

    string message;
    for (int i = 0; i < 10; i++)
    {
        message = std::to_string(i);
        cerr << "send : " << i << endl;
        client.sendMessage(message);
        message = client.receiveMessage(BUFFER_SIZE);
        cerr << "receive : " << message << endl;
        sleep(1);
    }

    client.terminate();
    return 0;
}
```
