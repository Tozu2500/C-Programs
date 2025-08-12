#ifndef FILEINFO_H
#define FILEINFO_H

#include <string>
#include <vector>
#include <cstdint>

class FileInfo {
public:
    FileInfo();
    FileInfo(const std::string& name, uint64_t size, bool isDirectory);

    std::string getName() const;
    uint64_t getSize() const;
    bool isDirectory() const;
};

#endif // FILEINFO_H