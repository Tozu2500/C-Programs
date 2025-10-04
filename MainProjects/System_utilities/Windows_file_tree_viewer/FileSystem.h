#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <windows.h>
#include <string>
#include <vector>
#include <ctime>

struct FileEntry {
    std::wstring name;
    std::wstring fullPath;
    bool isDirectory;
    DWORD attributes;
    ULONGLONG size;
    FILETIME creationTime;
    FILETIME lastAccessTime;
    FILETIME lastWriteTime;
    int depth;
    bool isExpanded;
    bool isHidden;
    bool isSystem;
    bool isReadOnly;
    bool isArchive;
    std::vector<FileEntry*> children;
    FileEntry* parent;

    FileEntry();
    ~FileEntry();
    void addChild(FileEntry* child);
    void removeChild(FileEntry* child);
    void clearChildren();
    std::wstring getFormattedSize() const;
    std::wstring getFormattedDate(const FILETIME& ft) const;
    std::wstring getAttributeString() const;
    bool hasChildren() const;
    int getChildCount() const;
    int getTotalFileCount() const;
    int getTotalDirCount() const;
    ULONGLONG getTotalSize() const;
};

class FileSystemScanner {
private:
    bool includeHidden;
    bool includeSystem;
    std::vector<std::wstring> extensionFilter;
    ULONGLONG maxFileSize;
    ULONGLONG minFileSize;
    bool sortByName;
    bool sortBySize;
    bool sortByDate;
    bool sortDescending;
    int maxDepth;

    void scanDirectoryRecursive(FileEntry* parent, const std::wstring& path, int currentDepth);
    bool shouldIncludeFile(const WIN32_FIND_DATAW& findData) const;
    bool matchesExtensionFilter(const std::wstring& filename) const;
    void sortEntries(std::vector<FileEntry*>& entries);

public:
    FileSystemScanner();
    ~FileSystemScanner();

    void setIncludeHidden(bool include);
    void setIncludeSystem(bool include);
    void setExtensionFilter(const std::vector<std::wstring>& extensions);
    void setSizeFilter(ULONGLONG minSize, ULONGLONG maxSize);
    void setSortMode(bool byName, bool bySize, bool byDate, bool descending);
    void setMaxDepth(int depth);

    FileEntry* scanDirectory(const std::wstring& path);
    FileEntry* scanDirectory(const std::wstring& path, int depth);
    void rescanDirectory(FileEntry* entry);

    std::vector<std::wstring> getAvailableDrives() const;
    bool isValidPath(const std::wstring& path) const;
    std::wstring getCurrentDirectory() const;
    bool setCurrentDirectory(const std::wstring& path);
};

class FileSystemCache {
private:
    struct CacheEntry {
        std::wstring path;
        FileEntry* entry;
        time_t timestamp;
        bool isDirty;
    };

    std::vector<CacheEntry> cache;
    size_t maxCacheSize;
    time_t cacheTimeout;

    void removeOldestEntry();
    int findCacheEntry(const std::wstring& path) const;

public:
    FileSystemCache();
    ~FileSystemCache();

    void setMaxCacheSize(size_t size);
    void setCacheTimeout(time_t timeout);

    void addToCache(const std::wstring& path, FileEntry* entry);
    FileEntry* getFromCache(const std::wstring& path);
    void removeFromCache(const std::wstring& path);
    void clearCache();
    void markDirty(const std::wstring& path);
    void isCached(const std::wstring& path) const;
    size_t getCacheSize() const;
};

#endif // FileSystem.h