#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <fstream>
#include <string>
#include <vector>

#include <filesystem>

namespace prism {

class FileManager {
public:
    ~FileManager() = default;
    static FileManager getInstance();
    bool setLocation(std::filesystem::path filePath);
    bool contains(std::filesystem::path subPath);
    std::vector<std::filesystem::path> listSubFolders();
    std::vector<std::filesystem::path> listFiles();
    bool mkdir(std::filesystem::path directoryName);
    bool cd(std::filesystem::path subPath);

    std::filesystem::path getLocation();
    std::tuple<std::vector<std::byte>, 
               std::uint32_t, 
               std::uint32_t, 
               std::uint8_t> parseImage(std::filesystem::path imagePath, bool flipOnLoad = true);

    std::string readFile(std::filesystem::path fileName);
    std::string readFileString(std::filesystem::path fileName);
    std::vector<char> readFileBytes(std::filesystem::path fileName);
    void writeFile(std::filesystem::path fileName, std::string contents);

private:
    FileManager();

    std::filesystem::path location;
    bool isValid = false;
};

}

#endif