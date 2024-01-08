#include "util/files/FileManager.h"
#include "logger/Logger.h"

namespace prism {

void FileManager::setLocation(std::string filePath) {
    location = filePath;
}

std::string FileManager::getLocation() {
    return location;
}

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

std::string FileManager::readFileString(std::string fileName) {
    std::ifstream in(fileName, std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return (contents);
	}
	throw(errno);
}

std::vector<char> FileManager::readFileBytes(std::string fileName) {
    std::ifstream in(fileName, std::ios::binary|std::ios::ate);
    if (in) {
        std::ifstream::pos_type pos = in.tellg();

        if (pos == 0) {
            return std::vector<char>{};
        }

        std::vector<char> contents(pos);

        in.seekg(0, std::ios::beg);
        in.read(&contents[0], pos);

        return contents;
    }
    throw(errno);
}

void FileManager::writeFile(std::string fileName, std::string contents) {
    
}

}