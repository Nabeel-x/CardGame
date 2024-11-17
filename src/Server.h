#ifndef SERVER_H_
#define SERVER_H_
#include <iostream>
#include <SDL2/SDL_net.h>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

class Server {
private:
    IPaddress ip;                         // IP address of the server
    TCPsocket serverSocket;               // Server socket
    std::vector<TCPsocket> clients;       // List of connected clients
    std::mutex clientsMutex;              // Mutex to protect access to the clients vector
    bool running;                         // Server running state

    void acceptClients();                 // Method to accept new client connections

public:
    Server(uint16_t port);                // Constructor to initialize the server
    ~Server();                            // Destructor to clean up resources

    void broadcastMessage(const std::string& message);  // Send a message to all connected clients
    void run();                           // Main server loop
};

#endif // SERVER_H_
