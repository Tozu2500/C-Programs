/*
    LRU Cache

    Implementing an LRU (Least Recently Used) cache.
    Use: unordered_map and doubly linked list for O(1) operations.
*/
#include <iostream>
#include <unordered_map>
#include <list>
#include <string>

template<typename Key, typename Value>
class LRUCache {
    size_t capacity_;
    std::list<std::pair<Key, Value>> items_;
    std::unordered_map<Key, typename std::list<std::pair<Key, Value>>::iterator> cache_;

public:
    explicit LRUCache(size_t capacity) : capacity_(capacity) {}

    Value* get(const Key& key) {
        auto it = cache_.find(key);
        if (it == cache_.end()) {
            return nullptr;  // Not found
        }

        // Moving the accessed item to front (most recently used)
        items_.splice(items_.begin(), items_, it->second);
        return &it->second->second;
    }

    void put(const Key& key, const Value& value) {
        auto it = cache_.find(key);

        if (it != cache_.end()) {
            // Key exists -- update value and move to front
            it->second->second = value;
            items_.splice(items_.begin(), items_, it->second);
            return;
        }

        // If cache full - remove least recently used (back)
        if (items_.size() == capacity_) {
            auto last = items_.back();
            cache_.erase(last.first);
            items_.pop_back();
        }

        // Insert new item at front
        items_.emplace_front(key, value);
        cache_[key] = items_.begin();
    }

    void display() const {
        std::cout << "Cache state (most recent -> least): ";
        for (const auto& [key, val] : items_) {
            std::cout << "(" << key << ":" << val << ") ";
        }
        std::cout << "\n";
    }
};

int main() {
    LRUCache<int, std::string> cache(3);

    std::cout << "Adding elements:\n";
    cache.put(1, "One");
    cache.put(2, "Two");
    cache.put(3, "Three");
    cache.display();

    std::cout << "\nAccess key 2:\n";
    if (auto val = cache.get(2)) {
        std::cout << "Got: " << *val << "\n";
    } else {
        std::cout << "Key not found!\n";
    }
    cache.display();

    std::cout << "\nInsert key 4 (should evict least recently used key 1):\n";
    cache.put(4, "Four");
    cache.display();

    std::cout << "\nTry accessing evicted key 1:\n";
    if (auto val = cache.get(1)) {
        std::cout << "Got: " << *val << "\n";
    } else {
        std::cout << "Key 1 not found (evicted)\n";
    }

    std::cout << "\nUpdate key 2:\n";
    cache.put(2, "Two updated");
    cache.display();

    std::cout << "\nAdd key 5 (should evict key 3):\n";
    cache.put(5, "Five");
    cache.display();

    return 0;
}