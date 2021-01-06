cmake_minimum_required(VERSION 3.7)
project(untitled6)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS -pthread)

add_executable(untitled6 main.cpp klient/klient.cpp klient/klient.h server/Server.cpp server/Server.h menu/Menu.cpp menu/Menu.h tabulka/Tabulka.cpp tabulka/Tabulka.h User/User.cpp User/User.h klient/mainKlient.cpp server/mainServer.cpp klient/PrekladacKlient.cpp klient/PrekladacKlient.h)