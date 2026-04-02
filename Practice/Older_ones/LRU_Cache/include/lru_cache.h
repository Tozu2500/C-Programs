#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <unordered_map>
#include <list>
#include <string>
#include <optional>
#include <vector>

// Struct which represents one item stored in the cache
struct CacheEntry {
    std::string key;  // The lookup identifier
    std::string value;  // The data stored under that key
};

// A log entry created every time an item is removed from the cache
struct EvictionRecord {
    std::string key;  // Which key was removed
    std::string value;  // What value it held before removing
};

class LRUCache {
public:
    // Capacity must be >= 1. If 0 is passed, defaults to 1.
    explicit LRUCache(int capacity);

    // Try to retrieve a value from the cache by its key
    std::optional<std::string> get(const std::string& key);

    // Insert or update a key-value pair in the cache
    void put(const std::string& key, const std::string& value);

    // Manually delete a specific key from the cache.
    // Returns true if the key was found and removed and false if it did not exist.
    bool remove(const std::string& key);

    // Remove all of the items from the cache -- capacity stays same, only data is wiped
    void clear();

    // Change the minimum capacity of the cache
    void resize(int newCapacity);

    // Read only information about the cache state
    int getCapacity() const;  // Max items allowed
    int getSize() const;  // Current number of items stored
    bool isEmpty() const;  // True if no items are stored
    bool isFull() const;  // True if size == capacity

    // Returns all cache items in order from most recently used to least recently used
    std::vector<CacheEntry> getOrderedItems() const;

    // Returns a history of all evictions (removals) that have occurred
    const std::vector<EvictionRecord>& getEvictionLog() const;

    // Statistics to measure cache effectiveness
    int getHitCount() const;
    int getMissCount() const;
    double getHitRate() const;

    // Zero out hit/miss counters, but keep stored data
    void resetStats();

private:
    int capacity_;
    std::list<CacheEntry> cacheList_;
    std::unordered_map<std::string, std::list<CacheEntry>::iterator> cacheMap_;

    // Stats counters
    int hitCount_;
    int missCount_;

    // History of all evictions
    std::vector<EvictionRecord> evictionLog_;

    // Internal helper - moves an existing node to the front of the list, marking it as the most recently used item
    void moveToFront(std::list<CacheEntry>::iterator it);

    // Internal helper - removes the item at the back of the list (least recently used), logs it and cleans up the map entry
    void evictLRU();
};

#endif  // LRU_CACHE_H