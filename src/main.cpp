#include "ftp_server.h"
#include <iostream>

int main() {
    // ���� ���� �� ���� ����� (����� 54000)
    int port = 54000;
    
    // ����� � ����� �� FTPServer
    FTPServer server(port);
    
    // ����� ����
    server.start();

    return 0;
}
