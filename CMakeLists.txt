cmake_minimum_required(VERSION 3.7)
project(untitled6)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled6 main.cpp client/Client.cpp client/Client.h server/Server.cpp server/Server.h menu/Menu.cpp menu/Menu.h tabulka/Tabulka.cpp tabulka/Tabulka.h)