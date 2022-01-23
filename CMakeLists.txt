cmake_minimum_required(VERSION 3.21)
project(wallet_alert)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/enums)
include_directories(src/headers)
include_directories(src/interfaces)

add_executable(wallet_alert
        src/enums/bc_type.cc
        src/headers/mailer.h
        src/headers/timer.h
        src/interfaces/message.cc
        src/analyzer.cpp
        src/bc_service.cpp
        src/db_service.cpp
        src/mailer.cpp
        src/main.cpp
        src/process.cpp
        src/worker.cpp)
