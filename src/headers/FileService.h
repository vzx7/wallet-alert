//
// Created by zx on 1/26/22.
//

#ifndef WALLET_ALERT_FILESERVICE_H
#define WALLET_ALERT_FILESERVICE_H
#include <iostream>
#include <fstream>
using namespace std;


class FileService {
private:
    string _resourceDir;
    string _path;
public:
    ifstream file;
    FileService(string fileName);
    string readFile(unsigned int countLine = 1);
    void removeFile(string fileName);
    void openFile();
    void closeFile();
};


#endif //WALLET_ALERT_FILESERVICE_H
