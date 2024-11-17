#include "Server.h"

// Constructor to initialize the server
Server::Server(uint16_t port) : running(false) {
    if (SDLNet_Init() < 0) {
        throw std::runtime_error("Failed to initialize SDL_net: " + std::string(SDLNet_GetError()));
    }

    if (SDLNet_ResolveHost(&ip, nullptr, port) < 0) {
        SDLNet_Quit();
        throw std::runtime_error("Failed to resolve host: " + std::string(SDLNet_GetError()));
    }

    serverSocket = SDLNet_TCP_Open(&ip);
    if (!serverSocket) {
        SDLNet_Quit();
        throw std::runtime_error("Failed to open server socket: " + std::string(SDLNet_GetError()));
    }

    running = true;
    std::cout << "Server started on port " << port << std::endl;
}

// Destructor to clean up resources
Server::~Server() {
    running = false;

    for (auto& client : clients) {
        SDLNet_TCP_Close(client);
    }

    SDLNet_TCP_Close(serverSocket);
    SDLNet_Quit();
    std::cout << "Server stopped." << std::endl;
}

// Accept new client connections
void Server::acceptClients() {
    while (running) {
        TCPsocket newClient = SDLNet_TCP_Accept(serverSocket);
        if (newClient) {
            clients.push_back(newClient);
            std::cout << "New client connected!" << std::endl;
        }

        // Allow other threads to run
        SDL_Delay(10);
    }
}

// Broadcast a message to all connected clients
void Server::broadcastMessage(const std::string& message) {
    std::lock_guard<std::mutex> lock(clientsMutex);

    auto it = clients.begin();
    while (it != clients.end()) {
        if (SDLNet_TCP_Send(*it, message.c_str(), message.size() + 1) < static_cast<int>(message.size() + 1)) {
            std::cout << "Client disconnected during broadcast." << std::endl;
            SDLNet_TCP_Close(*it);
            it = clients.erase(it); // Remove disconnected client
        } else {
            ++it;
        }
    }
}

// Main server loop
void Server::run() {
    std::thread acceptThread(&Server::acceptClients, this);

    std::cout << "Server running. Type 'exit' to stop." << std::endl;

    std::string input;
    while (running) {
        std::getline(std::cin, input);
        if (input == "exit") {
            running = false;
        } else {
            broadcastMessage(input);
        }
    }

    acceptThread.join(); // Wait for the client acceptance thread to finish
}
