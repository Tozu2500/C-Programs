#include <iostream>
#include <string>
#include <cstddef>

// ============================================================================
// PROBLEM 8: Memory Pool Allocator
// ============================================================================

template<typename T, size_t PoolSize>
class MemoryPool {
    struct Block {
        alignas(T) char storage[sizeof(T)];
        Block* next;
        
        T* as_T() { return reinterpret_cast<T*>(storage); }
    };

    Block pool[PoolSize];
    Block* freeList;

public:
    MemoryPool() {
        freeList = &pool[0];
        for (size_t i = 0; i < PoolSize - 1; ++i) {
            pool[i].next = &pool[i + 1];
        }
        pool[PoolSize - 1].next = nullptr;
    }

    ~MemoryPool() {
        // Destructor for memory pool - no cleanup needed as objects
        // should be explicitly destroyed before deallocation
    }

    T* allocate() {
        if (!freeList)
            return nullptr; // pool exhausted

        Block* block = freeList;
        freeList = freeList->next;
        return block->as_T();
    }

    void deallocate(T* ptr) {
        Block* block = reinterpret_cast<Block*>(
            reinterpret_cast<char*>(ptr) - offsetof(Block, storage)
        );
        block->next = freeList;
        freeList = block;
    }
};

// ============================================================================
// MAIN FUNCTION TO TEST THE MEMORY POOL
// ============================================================================

struct MyObject {
    int id;
    std::string name;

    MyObject(int i, std::string n) : id(i), name(std::move(n)) {
        std::cout << "Constructed MyObject(" << id << ", " << name << ")\n";
    }
    ~MyObject() {
        std::cout << "Destructed MyObject(" << id << ", " << name << ")\n";
    }
};

int main() {
    MemoryPool<MyObject, 3> pool;

    // Allocate three objects
    MyObject* a = new (pool.allocate()) MyObject(1, "Alpha");
    MyObject* b = new (pool.allocate()) MyObject(2, "Bravo");
    MyObject* c = new (pool.allocate()) MyObject(3, "Charlie");

    // Try to allocate beyond the pool capacity
    MyObject* d = pool.allocate();
    if (!d)
        std::cout << "Pool exhausted! No more memory available.\n";

    // Use the objects
    std::cout << "Using objects: "
              << a->name << ", " << b->name << ", " << c->name << "\n";

    // Manually call destructors before returning memory to pool
    a->~MyObject();
    pool.deallocate(a);

    b->~MyObject();
    pool.deallocate(b);

    c->~MyObject();
    pool.deallocate(c);

    // Now allocation works again after deallocation
    MyObject* e = new (pool.allocate()) MyObject(4, "Delta");
    e->~MyObject();
    pool.deallocate(e);

    return 0;
}
