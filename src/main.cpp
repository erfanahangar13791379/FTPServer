#include "ftp_server.h"
#include <iostream>

int main() {
    // æÑÊ ÓÑæÑ ÑÇ ãÔÎÕ ãí˜äíã (ãËáÇğ 54000)
    int port = 54000;
    
    // ÇíÌÇÏ í˜ äãæäå ÇÒ FTPServer
    FTPServer server(port);
    
    // ÇÌÑÇí ÓÑæÑ
    server.start();

    return 0;
}
