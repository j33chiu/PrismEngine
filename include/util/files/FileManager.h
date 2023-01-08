#pragma once

#include <fstream>
#include <string>

namespace prism {

class FileManager {
public:
    ~FileManager() = default;
    static std::string readFile(std::string fileName);
    static void writeFile(std::string fileName, std::string contents);

private:
    std::string defaultLocation = "testLocation";
};

}