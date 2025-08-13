#include "DiskScanner.h"
#include <windows.h>
#include <iostream>
#include <sstream>
#include <algorithm>

DiskScanner::DiskScanner() : cancelled(false), filesScanned(0) {}

FileInfo DiskScanner::scanDirectory(const std::string& path) {
    cancelled = false;
    filesScanned = 0;

    FileInfo rootInfo(path, 0, true);
    uint64_t totalSize = scanDirectoryRecursive(path, rootInfo);
    rootInfo.setSize(totalSize);
    rootInfo.sortChildren();

    return rootInfo;
}

uint64_t DiskScanner::scanDirectoryRecursive(const std::string& path, FileInfo& dirInfo, int depth) {
    if (cancelled || depth > MAX_DEPTH) {
        return 0;
    }

    std::string searchPath = path;
    if (searchPath.back() != '\\') {
        searchPath += "\\";
    }
    searchPath += "*";

    WIN32_FIND_DATAA findData;
    HANDLE hFind = FindFirstFileA(searchPath.c_str(), &findData);

    if (hFind == INVALID_HANDLE_VALUE) {
        return 0;
    }

    uint64_t totalSize = 0;

    do {
        if (cancelled) break;

        std::string fileName = findData.cFileName;
        if (fileName == "." || fileName == "..") {
            continue; // Skip current and parent directory entries
        }

        std::string fullPath = path;
        if (fullPath.back() != '\\') {
            fullPath += "\\";
        }
        fullPath += fileName;

        if (shouldSkipDirectory(fullPath)) {
            continue; // Skip directories that shouldn't be scanned
        }

        bool isDirectory = (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
        uint64_t fileSize = 0;

        if (isDirectory) {
            FileInfo childDir(fileName, 0, true);
            fileSize = scanDirectoryRecursive(fullPath, childDir, depth + 1);
            childDir.setSize(fileSize);
            childDir.sortChildren();
            dirInfo.addChild(childDir);
        } else {
            LARGE_INTEGER size;
            size.LowPart = findData.nFileSizeLow;
            size.HighPart = findData.nFileSizeHigh;
            fileSize = size.QuadPart;

            FileInfo childFile(fileName, fileSize, false);
            dirInfo.addChild(childFile);
        }

        totalSize += fileSize;
        filesScanned++;

        if (progressCallback && filesScanned % PROGRESS_UPDATE_INTERVAL == 0) {
            progressCallback(fullPath, filesScanned);
        }

    } while (FindNextFileA(hFind, &findData) != 0);

    FindClose(hFind);
    return totalSize;
}

bool DiskScanner::shouldSkipDirectory(const std::string& path) {
    DWORD attributes = GetFileAttributesA(path.c_str());
    if (attributes == INVALID_FILE_ATTRIBUTES) {
        return true;
    }

    if (attributes & FILE_ATTRIBUTE_SYSTEM) {
        return true; // Skip system directories
    }

    std::string lowerPath = path;
    std::transform(lowerPath.begin(), lowerPath.end(), lowerPath.begin(), ::tolower);

    if (lowerPath.find("\\system volume information") != std::string::npos ||
        lowerPath.find("\\$recycle.bin") != std::string::npos ||
        lowerPath.find("\\pagefile.sys") != std::string::npos ||
        lowerPath.find("\\hiberfil.sys") != std::string::npos) {
            return true; // Skip known system directories
        }
    
    return false; // Directory is not skipped
}

void DiskScanner::setProgressCallback(std::function<void(const std::string&, int)> callback) {
    progressCallback = callback;
}

void DiskScanner::cancelScan() {
    cancelled = true;
}

bool DiskScanner::isCancelled() const {
    return cancelled;
}

std::vector<std::string> DiskScanner::getAvailableDrives() {
    std::vector<std::string> drives;
    DWORD drivesMask = GetLogicalDrives();

    for (int i = 0; i < 26; i++) {
        if (drivesMask & (1 << i)) {
            char driveLetter = 'A' + i;
            std::string drive = std::string(1, driveLetter) + ":";

            UINT driveType = GetDriveTypeA((drive + "\\").c_str());
            if (driveType == DRIVE_FIXED || driveType == DRIVE_REMOVABLE) {
                drives.push_back(drive);
            }
        }
    }
    return drives;
}