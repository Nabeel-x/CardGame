#include "Client.h"
#include <iostream>
#include <stdexcept>

// Constructor to initialize client connection
Client::Client(const std::string& host, uint16_t port) : running(false) {
    if (SDLNet_Init() < 0) {
        throw std::runtime_error("Failed to initialize SDL_net: " + std::string(SDLNet_GetError()));
    }

    if (SDLNet_ResolveHost(&ip, host.c_str(), port) < 0) {
        SDLNet_Quit();
        throw std::runtime_error("Failed to resolve host: " + std::string(SDLNet_GetError()));
    }

    socket = SDLNet_TCP_Open(&ip);
    if (!socket) {
        SDLNet_Quit();
        throw std::runtime_error("Failed to open client socket: " + std::string(SDLNet_GetError()));
    }

    running = true;
    std::cout << "Connected to server at " << host << ":" << port << std::endl;
}

// Destructor to clean up resources
Client::~Client() {
    running = false;
    if (socket) {
        SDLNet_TCP_Close(socket);
    }
    SDLNet_Quit();
    std::cout << "Client disconnected." << std::endl;
}

// Receive messages from the server
void Client::receiveMessages() {
    char buffer[512];

    while (running) {
        int result = SDLNet_TCP_Recv(socket, buffer, sizeof(buffer));
        if (result > 0) {
            std::cout << "Server: " << std::string(buffer) << std::endl;
        } else if (result == 0) {
            std::cout << "Disconnected from server." << std::endl;
            running = false; // Stop running if the server disconnects
        } else {
            // Handle errors gracefully
            std::cerr << "Error receiving data: " << SDLNet_GetError() << std::endl;
            running = false;
        }
    }
}

// Send a message to the server
void Client::sendMessage(const std::string& message) {
    if (SDLNet_TCP_Send(socket, message.c_str(), message.size() + 1) < static_cast<int>(message.size() + 1)) {
        std::cerr << "Failed to send message: " << SDLNet_GetError() << std::endl;
    }
}

// Main client loop

void Client::run() {
    std::thread receiveThread(&Client::receiveMessages, this);

    std::cout << "Client running. Type 'exit' to disconnect." << std::endl;

    std::string input;
    while (running) {
        std::getline(std::cin, input);
        if (input == "exit") {
            running = false;
        } else {
            sendMessage(input);
        }
    }

    receiveThread.join(); // Wait for the receive thread to finish
}
