#ifndef SPEED_TESTER_H
#define SPEED_TESTER_H

#include "HttpClient.h"
#include <string>
#include <vector>
#include <memory>

class SpeedTester {
private:
    std::unique_ptr<HttpClient> httpClient;
    std::vector<std::string> testServers;
    std::string currentServer;

    int downloadDuration;
    int uploadDuration;
    int latencyAttempts;

    std::string selectBestServer();
    std::string formatSpeed(double speedMbps);
    std::string formatLatency(double latencyMs);
    void printProgress(const std::string& testName, int progress);

public:
    SpeedTester();
    ~SpeedTester();

    // Config
    void addTestServer(const std::string& server);
    void setTestDuration(int downloadSec, int uploadSec);
    void setLatencyAttempts(int attempts);

    // Main test methods
    TestResult runSpeedTest();
    TestResult runSpeedTest(const std::string& server);

    // Individual tests
    double testDownloadSpeed();
    double testUploadSpeed();
    double testLatency();

    // Utils
    void printResults(const TestResult& result);
    std::string getServerInfo();
    bool checkConnectivity();
};

#endif // SPEED_TESTER_H