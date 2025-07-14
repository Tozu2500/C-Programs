#ifndef NETWORK_SPEED_TESTER_H
#define NETWORK_SPEED_TESTER_H

#include <string>
#include <vector>
#include <chrono>

struct SpeedTestResult {
    double downloadSpeed;
    double uploadSpeed;
    double latency;
    bool success;
    std::string errorMessage;
};

class NetworkSpeedTester {
private:
    std::string testServer;
    int testPort;
    size_t testDataSize;
    int timeoutSeconds;

    // Helpers
    bool initializeWinsock();
    void cleanupWinsock();
    double measureLatency(const std::string& host, int port);
    double measureDownloadSpeed(const std::string& host, int port);
    double measureUploadSpeed(const std::string& host, int port);
    std::string generateTestData(size_t size);
    std::vector<char> downloadData(const std::string& host, int port, const std::string& path);
    bool uploadData(const std::string& host, int port, const std::string& data);

public:
    NetworkSpeedTester(const std::string& server = "httpbin.org", int port = 80);
    ~NetworkSpeedTester();

    // Config methods
    void setTestServer(const std::string& server);
    void setTestPort(int port);
    void setTestDataSize(size_t size);
    void setTimeout(int seconds);

    // Main testing methods
    SpeedTestResult runFullTest();
    double testDownloadSpeed();
    double testUploadSpeed();
    double testLatency();

    // Utils
    std::string formatSpeed(double speedMbps);
    void printResults(const SpeedTestResult& result);
};

#endif // NETWORK_SPEED_TESTER_H
