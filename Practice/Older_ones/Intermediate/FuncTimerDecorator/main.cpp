#include <iostream>
#include <chrono>
#include <functional>
#include <thread>
#include <vector>
#include <type_traits>  // for std::is_void_v, std::invoke_result_t

// Template function to measure execution time
template<typename Func, typename... Args>
auto measureTime(Func func, Args&&... args) {
    auto start = std::chrono::high_resolution_clock::now();

    if constexpr (std::is_void_v<std::invoke_result_t<Func, Args...>>) {
        // Case: function returns void
        func(std::forward<Args>(args)...);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Execution time: " << duration.count() << " ms\n";
    } else {
        // Case: function returns a value
        auto result = func(std::forward<Args>(args)...);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Execution time: " << duration.count() << " ms\n";
        return result;
    }
}

// Example functions to test
int add(int a, int b) {
    return a + b;
}

void simulateWork(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

long long sumLargeVector(size_t n) {
    std::vector<int> v(n, 1);
    long long sum = 0;
    for (auto x : v) sum += x;
    return sum;
}

int main() {
    std::cout << "Testing add function:\n";
    int result = measureTime(add, 5, 7);
    std::cout << "Result: " << result << "\n\n";

    std::cout << "Testing simulateWork (sleep 500 ms):\n";
    measureTime(simulateWork, 500);
    std::cout << "\n";
    
    std::cout << "Testing sumLargeVector (10 million elements):\n";
    long long total = measureTime(sumLargeVector, 10'000'000);
    std::cout << "Sum: " << total << "\n";

    return 0;
}
