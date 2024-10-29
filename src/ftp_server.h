#ifndef FTP_SERVER_H
#define FTP_SERVER_H

#include <string>

// ˜ÊÇÈÎÇäå Winsock ÈÑÇí ÈÑäÇãåäæíÓí Óæ˜Ê ÏÑ æíäÏæÒ
#include <winsock2.h>

// ÊÚÑíİ ˜áÇÓ FTPServer
class FTPServer {
public:
    FTPServer(int port);  // ÓÇÒäÏå ÓÑæÑ
    void start();  // ÔÑæÚ Èå ˜ÇÑ ÓÑæÑ
    void handleClient(int clientSocket);  // ãÏíÑíÊ ÇÊÕÇá í˜ ˜áÇíäÊ

    // ÊæÇÈÚ ãÎÊáİ ÈÑÇí ÚãáíÇÊ FTP
    void uploadFile(int clientSocket, const std::string& filename);
    void downloadFile(int clientSocket, const std::string& filename);
    void deleteFile(int clientSocket, const std::string& filename);
    void searchFile(int clientSocket, const std::string& filename);
    void listFiles(int clientSocket);

private:
    int serverSocket;  // Óæ˜Ê ÓÑæÑ
    int port;  // æÑÊ ÓÑæÑ
    void sendMessage(int clientSocket, const std::string& message);  // ÇÑÓÇá íÇã Èå ˜áÇíäÊ
    std::string receiveMessage(int clientSocket);  // ÏÑíÇİÊ íÇã ÇÒ ˜áÇíäÊ
};

#endif
