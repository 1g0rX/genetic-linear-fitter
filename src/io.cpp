#include "../include/io.hpp"

FileManager::FileManager() {}

FileManager::~FileManager() {
    closeFiles();
}

bool FileManager::openForWriting(std::string fileName) {
    outFile.open(fileName);
    return outFile.is_open();
}

bool FileManager::openForReading(std::string fileName) {
    inFile.open(fileName);
    return inFile.is_open();
}

void FileManager::closeFiles() {
    if (outFile.is_open()) {
        outFile.close();
    }
    if (inFile.is_open()) {
        inFile.close();
    }
}

bool FileManager::writeLine(std::string text) {
    if (outFile.is_open()) {
        outFile << text << std::endl;
        return true;
    }
    return false;
}

bool FileManager::readLine(std::string &text) {
    if (inFile.is_open() && std::getline(inFile, text)) {
        return true;
    }
    return false;
}