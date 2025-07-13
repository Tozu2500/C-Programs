#ifndef NETWORKSPEEDTESTER_H
#define NETWORKSPEEDTESTER_H

#include <string>
#include <vector>
#include <chrono>
#include <memory>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#endif

struct TestResult {
    double downloadSpeed;
    double uploadSpeed;
    double latency;
    bool success;
    std::string error;
};

struct TestServer {
    std::string url;
    std::string host;
    int port;
    std::string path;
};

class NetworkSpeedTester {
private:
    std::vector<TestServer> testServers;
    int timeout;
    bool wsaInitialized;

    // Helper methods
    bool initializeWinsock();
    void cleanupWinsock();
    bool parseUrl(const std::string& url, TestServer& server);
    std::string createHttpRequest(const std::string& host, const std::string& path, const std::string& method = "GET", size_t contentLength = 0);
    bool sendHttpRequest(const std::string& host, int port, const std::string& request, std::string& response);
    double measureLatency(const std::string& host, int port);
    double measureDownloadSpeed(const TestServer& server);
    double measureUploadSpeed(const TestServer& server);
    std::string generateRandomData(size_t size);

public:
    NetworkSpeedTester();
    ~NetworkSpeedTester();

    // Config
    void addTestServer(const std::string& url);
    void setTimeout(int timeoutMs);
    void setDefaultServers();

    // Testing methods
    TestResult runSpeedTest();
    TestResult runLatencyTest();
    TestResult runDownloadTest();
    TestResult runUploadTest();

    // Utility methods
    void printResults(const TestResult& result);
    std::string formatSpeed(double speedMbps);
    std::string formatLatency(double latencyMs);
};

#endif // NETWORKSPEEDTESTER_H
