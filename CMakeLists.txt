cmake_minimum_required(VERSION 3.10)
project(FTPServer)

set(CMAKE_CXX_STANDARD 17)

add_executable(ftp_server src/main.cpp src/ftp_server.cpp)
