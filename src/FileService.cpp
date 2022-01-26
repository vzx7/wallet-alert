//
// Created by zx on 1/26/22.
//

#include "headers/FileService.h"

FileService::FileService(string fileName) {
    string homeDir;
    try {
        homeDir = getenv("HOME");
    } catch(const char *msg) {
        throw "HOME DIR NO FOUND...";
    }
    _resourceDir = homeDir + "/wallet_alert/resources/";
    _path = _resourceDir + fileName;
}

void FileService::openFile() {
    file.open(_path);
    if (!file)
    {
        throw "ERROR: The file was not opened!";
    }
}

string FileService::readFile(unsigned int countLine) {
    openFile();
    string lines;
    unsigned int i = 0;
    while (i < countLine) {
        string line;
        getline(file, line);
        cout << line << "  " << _path << endl;
        lines += line;
        i++;
    }

    return lines;
}

void FileService::removeFile(string fileName) {
    string filePath = _resourceDir + fileName;
    if (remove(filePath.c_str()) != 0)
    {
        throw "ERROR: Файл содержащий PID не был удален!";
    }
}

void FileService::closeFile() {
    file.close();
}



