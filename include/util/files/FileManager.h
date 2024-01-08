#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace prism {

class FileManager {
public:
    ~FileManager() = default;
    static void setLocation(std::string filePath);
    static std::string getLocation();
    static std::string readFile(std::string fileName);
    static std::string readFileString(std::string fileName);
    static std::vector<char> readFileBytes(std::string fileName);
    static void writeFile(std::string fileName, std::string contents);

private:
    FileManager();
    static std::string location;
};

}