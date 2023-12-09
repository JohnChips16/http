#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

const int BUFFER_SIZE = 1024;

void handleRequest(int clientSocket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead = read(clientSocket, buffer, sizeof(buffer) - 1);

    if (bytesRead > 0) {
        buffer[bytesRead] = '\0';  // Null-terminate the received data

        // Print the HTTP request
        std::cout << "Received HTTP Request:\n" << buffer << std::endl;

        // Send a simple HTTP response
        const char* response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "\r\n"
            "Hello, this is a HTTP server in C++!";
        write(clientSocket, response, strlen(response));
    }

    // Close the client socket
    close(clientSocket);
}

void startHttpServer(int port) {
    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error creating socket\n";
        return;
    }

    // Set up server address structure
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    // Bind the socket to the specified port
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Error binding socket\n";
        close(serverSocket);
        return;
    }

    // Listen for incoming connections
    if (listen(serverSocket, 10) == -1) {
        std::cerr << "Error listening for connections\n";
        close(serverSocket);
        return;
    }

    std::cout << "Server is listening on port " << port << "...\n";

    while (true) {
        // Accept a connection
        sockaddr_in clientAddress;
        socklen_t clientAddressLength = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);

        if (clientSocket == -1) {
            std::cerr << "Error accepting connection\n";
            continue;
        }

        // Handle the HTTP request in a separate function
        handleRequest(clientSocket);
    }

    // Close the server socket (never reached in this example)
    close(serverSocket);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port>\n";
        return 1;
    }

    try {
        int port = std::stoi(argv[1]);
        startHttpServer(port);
    } catch (const std::exception& e) {
        std::cerr << "Error parsing port: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
