#ifndef CLIENT_H
#define CLIENT_H

#include <SDL2/SDL_net.h>
#include <string>
#include <thread>

class Client {
private:
    IPaddress ip;                         // IP address of the server
    TCPsocket socket;                     // Client socket
    bool running;                         // Client running state

    void receiveMessages();               // Method to handle incoming messages from the server

public:
    Client(const std::string& host, uint16_t port);  // Constructor to initialize client connection
    ~Client();                            // Destructor to clean up resources

    void sendMessage(const std::string& message);    // Send a message to the server
    void run();                           // Main client loop
};

#endif // CLIENT_H