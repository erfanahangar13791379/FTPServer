#include "ftp_server.h"
#include <iostream>
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;

#pragma comment(lib, "ws2_32.lib")  // ·Ì‰ò ò—œ‰ ò «»Œ«‰ÂùÌ winsock

FTPServer::FTPServer(int port) : port(port) {
    // —«Âù«‰œ«“Ì Winsock
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // «ÌÃ«œ ”Êò  ”—Ê—
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    //  ‰ŸÌ„ ¬œ—” ”—Ê—
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    // « ’«· ”Êò  »Â ¬œ—”
    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));

    // êÊ‘ œ«œ‰ »Â « ’«·« 
    listen(serverSocket, SOMAXCONN);

    std::cout << "Server started on port " << port << std::endl;
}

void FTPServer::start() {
    while (true) {
        sockaddr_in clientAddr;
        int clientSize = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientSize);
        
        // „œÌ—Ì  Â— ò·«Ì‰  œ— Ìò —‘ ÂùÌ ÃœÌœ (thread)
        handleClient(clientSocket);
    }
}

void FTPServer::handleClient(int clientSocket) {
    std::string command = receiveMessage(clientSocket);
    if (command == "UPLOAD") {
        std::string filename = receiveMessage(clientSocket);
        uploadFile(clientSocket, filename);
    } else if (command == "DOWNLOAD") {
        std::string filename = receiveMessage(clientSocket);
        downloadFile(clientSocket, filename);
    } else if (command == "DELETE") {
        std::string filename = receiveMessage(clientSocket);
        deleteFile(clientSocket, filename);
    } else if (command == "SEARCH") {
        std::string filename = receiveMessage(clientSocket);
        searchFile(clientSocket, filename);
    } else if (command == "LIST") {
        listFiles(clientSocket);
    }
    closesocket(clientSocket);
}

void FTPServer::uploadFile(int clientSocket, const std::string& filename) {
    std::ofstream outFile(filename, std::ios::binary);
    char buffer[1024];
    int bytesRead;
    while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        outFile.write(buffer, bytesRead);
    }
    outFile.close();
    sendMessage(clientSocket, "File uploaded successfully.");
}

void FTPServer::downloadFile(int clientSocket, const std::string& filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        sendMessage(clientSocket, "File not found.");
        return;
    }

    char buffer[1024];
    while (inFile.read(buffer, sizeof(buffer))) {
        send(clientSocket, buffer, sizeof(buffer), 0);
    }
    inFile.close();
    sendMessage(clientSocket, "File downloaded successfully.");
}

void FTPServer::deleteFile(int clientSocket, const std::string& filename) {
    if (fs::remove(filename)) {
        sendMessage(clientSocket, "File deleted successfully.");
    } else {
        sendMessage(clientSocket, "File not found.");
    }
}

void FTPServer::searchFile(int clientSocket, const std::string& filename) {
    if (fs::exists(filename)) {
        sendMessage(clientSocket, "File found.");
    } else {
        sendMessage(clientSocket, "File not found.");
    }
}

void FTPServer::listFiles(int clientSocket) {
    std::string fileList;
    for (const auto& entry : fs::directory_iterator(".")) {
        fileList += entry.path().string() + "\n";
    }
    sendMessage(clientSocket, fileList);
}

void FTPServer::sendMessage(int clientSocket, const std::string& message) {
    send(clientSocket, message.c_str(), message.size(), 0);
}

std::string FTPServer::receiveMessage(int clientSocket) {
    char buffer[1024];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    return std::string(buffer, bytesReceived);
}
