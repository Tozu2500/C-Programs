#ifndef DISKSCANNER_H
#define DISKSCANNER_H

#include "FileInfo.h"
#include <string>
#include <functional>

class DiskScanner {
public:
    DiskScanner();

    FileInfo scanDirectory(const std::string& path);
    void setProgressCallback(std::function<void(const std::string&, int)> callback);
    void cancelScan();
    bool isCancelled() const;
    static std::vector<std::string> getAvailableDrives();

private:
    uint64_t scanDirectoryRecursive(const std::string& path, FileInfo& dirInfo, int depth = 0);
    bool shouldSkipDirectory(const std::string& path);
    std::function<void(const std::string&, int)> progressCallback;
    bool cancelled;
    int filesScanned;

    static const int MAX_DEPTH = 50; // Prevents excessive recursion
    static const int PROGRESS_UPDATE_INTERVAL = 100; // Update progress every 100ms
};

#endif // DISKSCANNER_H