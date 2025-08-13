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
    void setSize(uint64_t size);
    void addChild(const FileInfo& child);
    std::vector<FileInfo>& getChildren() const;
    void sortChildren();
    std::string getFormattedSize() const;
    double getPercentage(uint64_t totalSize) const;

private:
    std::string name;
    uint64_t size;
    bool directory;
    std::vector<FileInfo> children;
};

#endif // FILEINFO_H
