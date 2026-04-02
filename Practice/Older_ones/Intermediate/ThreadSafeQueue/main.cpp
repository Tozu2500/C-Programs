/*
    Thread-Safe queue

    Implementing a thread-safe queue using mutex and condition variables.
    Includes: enqueue, dequeue, and size operations.
*/
#include <queue>
#include <mutex>
#include <condition_variable>
#include <optional>
#include <thread>
#include <iostream>
#include <vector>
#include <chrono>

template<typename T>
class ThreadSafeQueue {
    std::queue<T> queue_;
    mutable std::mutex mutex_;
    std::condition_variable cond_var_;

public:
    void enqueue(T item) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(std::move(item));
        cond_var_.notify_one();
    }

    // Blocking dequeue
    T dequeue() {
        std::unique_lock<std::mutex> lock(mutex_);
        cond_var_.wait(lock, [this] { return !queue_.empty(); });
        T item = std::move(queue_.front());
        queue_.pop();
        return item;
    }

    // Non-blocking dequeue
    std::optional<T> try_dequeue() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (queue_.empty()) {
            return std::nullopt;
        }
        T item = std::move(queue_.front());
        queue_.pop();
        return item;
    }

    size_t size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }
};

// Little testing ground
int main() {
    ThreadSafeQueue<int> tsq;

    // Producer thread
    std::thread producer([&tsq]() {
        for (int i = 1; i <= 5; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            tsq.enqueue(i);
            std::cout << "Produced: " << i << std::endl;
        }
    });

    // Consumer thread (blocking)
    std::thread consumer([&tsq]() {
        for (int i = 1; i <= 5; ++i) {
            int item = tsq.dequeue();
            std::cout << "Consumed (blocking): " << item << std::endl;
        }
    });

    producer.join();
    consumer.join();

    // Try non-blocking dequeue
    std::cout << "Trying non-blocking dequeue..." << std::endl;
    auto result = tsq.try_dequeue();
    if (result) {
        std::cout << "Dequeued (non-blocking): " << *result << std::endl;
    } else {
        std::cout << "Queue was empty (non-blocking)" << std::endl;
    }

    return 0;
}