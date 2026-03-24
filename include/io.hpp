#ifndef IO__HPP
#define IO__HPP
#include <fstream>

class FileManager {
    // private itens
    private:
        std::ifstream inFile;
        std::ofstream outFile;
    
    // public itens
    public:
    FileManager(); // constructor
    ~FileManager(); // destructor

    bool openForReading(std::string fileName);
    bool openForWriting(std::string fileName);
    void closeFiles();

    bool writeLine(std::string text);
    bool readLine(std::string &text);
};

#endif