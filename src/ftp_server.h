#ifndef FTP_SERVER_H
#define FTP_SERVER_H

#include <string>

// �������� Winsock ���� ����������� ��� �� ������
#include <winsock2.h>

// ����� ���� FTPServer
class FTPServer {
public:
    FTPServer(int port);  // ������ ����
    void start();  // ���� �� ��� ����
    void handleClient(int clientSocket);  // ������ ����� � ������

    // ����� ����� ���� ������ FTP
    void uploadFile(int clientSocket, const std::string& filename);
    void downloadFile(int clientSocket, const std::string& filename);
    void deleteFile(int clientSocket, const std::string& filename);
    void searchFile(int clientSocket, const std::string& filename);
    void listFiles(int clientSocket);

private:
    int serverSocket;  // ��� ����
    int port;  // ���� ����
    void sendMessage(int clientSocket, const std::string& message);  // ����� ���� �� ������
    std::string receiveMessage(int clientSocket);  // ������ ���� �� ������
};

#endif
