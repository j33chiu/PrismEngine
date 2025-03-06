#include "util/files/FileManager.h"
#include "logger/Logger.h"
#include "core/Exception.h"

// stage stb implementation here ONCE. can be moved to PrismInit for global engine use
#define STB_IMAGE_IMPLEMENTATION
#include "util/files/stb_image.h"

namespace prism {

FileManager FileManager::getInstance() {
    static FileManager instance = FileManager();
    return instance;
}

FileManager::FileManager() {
    std::error_code e;
    location = std::filesystem::current_path(e);
    if (e) {
        isValid = false;
        Logger::error("FileManager()", e.message());
    } else {
        isValid = true;
        Logger::debug("FileManager()", location);
    }
}

bool FileManager::setLocation(std::filesystem::path filePath) {
    std::error_code e;
    // try to set current path
    std::filesystem::current_path(filePath, e);
    if (e) {
        Logger::error("FileManager::setLocation()", e.message());
        return false;
    }

    // set location to current path
    location = std::filesystem::current_path(e);
    if (e) {
        isValid = false;
        Logger::error("FileManager()", e.message());
        return false;
    } else {
        isValid = true;
        Logger::debug("FileManager()", location);
        return true;
    }
}

bool FileManager::contains(std::filesystem::path subPath) {
    std::error_code e;
    bool out = std::filesystem::exists(location/subPath, e);
    if (e) {
        Logger::error("FileManager::exists()", e.message());
        return out;
    }
    return out;
}

std::vector<std::filesystem::path> FileManager::listSubFolders() {
    std::vector<std::filesystem::path> folders;
    for (const auto& entry : std::filesystem::directory_iterator(location)) {
        if (entry.is_directory()) {
            folders.emplace_back(entry);
            Logger::debug("FileManager::subFolders()", entry);
        }
    }
    return folders;
}

std::vector<std::filesystem::path> FileManager::listFiles() {
    std::vector<std::filesystem::path> files;
    for (const auto& entry : std::filesystem::directory_iterator(location)) {
        if (entry.is_regular_file()) {
            files.emplace_back(entry);
            Logger::debug("FileManager::listFiles()", entry);
        }
    }
    return files;
}

bool FileManager::mkdir(std::filesystem::path directoryName) {
    std::error_code e;
    bool out = std::filesystem::create_directory(directoryName, e);
    if (e) {
        Logger::error("FileManager::mkdir()", e.message());
        return out;
    }
    return out;
}

bool FileManager::cd(std::filesystem::path subPath) {
    // ".." case: // TODO: allow for more complex "../../<dir>" examples
    if (subPath.generic_string() == "..") {
        return setLocation(location.parent_path());
    }

    // other cases:
    if (contains(subPath) && std::filesystem::is_directory(subPath)) {
        return setLocation(subPath);
    }
    return false;
}

std::filesystem::path FileManager::getLocation() {
    return location;
}

std::tuple<std::vector<std::byte>, 
           std::uint32_t, 
           std::uint32_t, 
           std::uint8_t> FileManager::parseImage(std::filesystem::path imagePath, bool flipOnLoad) 
{
    std::vector<char> data = readFileBytes(imagePath);
    int width = 0;
    int height = 0;
    int channels = 0;

    stbi_set_flip_vertically_on_load(flipOnLoad);

    unsigned char* rawDataStart = stbi_load_from_memory(reinterpret_cast<const stbi_uc *>(data.data()),
                                                    static_cast<int>(data.size()),
                                                    &width,
                                                    &height,
                                                    &channels,
                                                    0);

    if (!rawDataStart || (channels == 0)) 
        throw prism::Exception("failed to load image data");

    std::byte* rawDataStartBytes = reinterpret_cast<std::byte*>(rawDataStart);

    const int rawDataSize = width * height * channels;

    std::byte* rawDataEndBytes = rawDataStartBytes + rawDataSize;

    std::vector<std::byte> out(rawDataSize);

    out.assign(rawDataStartBytes, rawDataEndBytes);

    return std::make_tuple(
        std::move(out), static_cast<std::uint32_t>(width), static_cast<std::uint32_t>(height), static_cast<std::uint8_t>(channels));
}

std::string FileManager::readFile(std::filesystem::path fileName) {
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

std::string FileManager::readFileString(std::filesystem::path fileName) {
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
	return "";
}

std::vector<char> FileManager::readFileBytes(std::filesystem::path fileName) {
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
    return {};
}

void FileManager::writeFile(std::filesystem::path fileName, std::string contents) {
    
}

}