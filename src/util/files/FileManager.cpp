#include "util/files/FileManager.h"
#include "logger/Logger.h"

namespace prism {

std::string FileManager::readFile(std::string fileName) {
    std::ifstream file(fileName);
    if (file) {
        std::string contents;
        std::string line;
        while(std::getline(file, line)) {
            contents.append(line);
        }

        return contents;
    }
    return "";
}

void FileManager::writeFile(std::string fileName, std::string contents) {
    
}

}