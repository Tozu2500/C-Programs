#include "ThreadSafeQueue.cpp"

int main() {
    ThreadSafeQueue<int> q;

    std::thread producer([&]() {
        for (int i = 1; i <= 5; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            q.push(i);
            std::cout << "Produced: " << i << "\n";
        }
    });

    std::thread consumer([&]() {
        for (int i = 1; i <= 5; ++i) {
            int value;
            q.wait_and_pop(value);
            std::cout << "Consumed: " << value << "\n";
        }
    });

    producer.join();
    consumer.join();

    return 0;
}