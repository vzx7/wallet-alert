cmake_minimum_required(VERSION 3.21)
project(wallet_alert)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/enums)
include_directories(src/headers)
include_directories(src/interfaces)

add_executable(wallet_alert
        src/headers/Mailer.h
        src/headers/Timer.h
        src/Analyzer.cpp
        src/Mailer.cpp
        src/main.cpp
        src/Process.cpp
        src/Worker.cpp src/Wallet.cpp src/headers/BcType.h src/headers/constants.h src/headers/BigInt.h src/BigInt.cpp src/FileService.cpp src/headers/FileService.h src/headers/WalletData.h)


