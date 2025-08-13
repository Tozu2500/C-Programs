#include "FileInfo.h"
#include <algorithm>
#include <sstream>
#include <iomanip>

FileInfo::FileInfo() : name(""), size(0), directory(false) {}

FileInfo::FileInfo(const std::string& name, uint64_t size, bool isDirectory)
    : name(name), size(size), directory(isDirectory) {}

std::string FileInfo::getName() const {
    return name;
}

uint64_t FileInfo::getSize() const {
    return size;
}

bool FileInfo::isDirectory() const {
    return directory;
}

void FileInfo::setSize(uint64_t size) {
    this->size = size;
}

void FileInfo::addChild(const FileInfo& child) {
    children.push_back(child);
}

std::vector<FileInfo>& FileInfo::getChildren() {
    return children;
}

const std::vector<FileInfo>& FileInfo::getChildren() const {
    return children;
}

void FileInfo::sortChildren() {
    std::sort(children.begin(), children.end(),
        [](const FileInfo& a, const FileInfo& b) {
            return a.getSize() > b.getSize();
        });
}

std::string FileInfo::getFormattedSize() const {
    std::stringstream ss;
    double displaySize = static_cast<double>(size);

    if (displaySize >= 1024.0 * 1024.0 * 1024.0) {
        displaySize /= (1024.0 * 1024.0 * 1024.0);
        ss << std::fixed << std::setprecision(2) << displaySize << " GB";
    } else if (displaySize >= 1024.0 * 1024.0) {
        displaySize /= (1024.0 * 1024.0);
        ss << std::fixed << std::setprecision(2) << displaySize << " MB";
    } else if (displaySize >= 1024.0) {
        displaySize /= 1024.0;
        ss << std::fixed << std::setprecision(2) << displaySize << " KB";
    } else {
        ss << size << " B";
    }

    return ss.str();
}

double FileInfo::getPercentage(uint64_t totalSize) const {
    if (totalSize == 0) return 0.0;
    return (static_cast<double>(size) / static_cast<double>(totalSize)) * 100.0;
}