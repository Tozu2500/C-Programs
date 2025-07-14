#include "NetworkSpeedTester.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <random>
#include <thread>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#define SOCKET int
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket close
#endif

NetworkSpeedTester::NetworkSpeedTester(const std::string& server, int port)
    : testServer(server), testPort(port), testDataSize(1024 * 1024), timeoutSeconds(10) {
        initializeWinsock();
}

NetworkSpeedTester::~NetworkSpeedTester() {
    cleanupWinsock();
}

bool NetworkSpeedTester::initializeWinsock() {
#ifdef _WIN32
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    return result == 0;
#else
    return true;
#endif
}

void NetworkSpeedTester::cleanupWinsock() {
#ifdef _WIN32
    WSACleanup();
#endif
}

void NetworkSpeedTester::setTestServer(const std::string& server) {
    testServer = server;
}

void NetworkSpeedTester::setTestPort(int port) {
    testPort = port;
}

void NetworkSpeedTester::setTestDataSize(size_t size) {
    testDataSize = size;
}

void NetworkSpeedTester::setTimeout(int seconds) {
    timeoutSeconds = seconds;
}

SpeedTestResult NetworkSpeedTester::runFullTest() {
    SpeedTestResult result;
    result.success = true;
    result.errorMessage = "";

    std::cout << "Starting network speed test...\n";
    std::cout << "Test server: " << testServer << ":" << testPort << "\n\n";

    // Latency test
    std::cout << "Testing latency..." << std::endl;
    result.latency = measureLatency(testServer, testPort);
    if (result.latency < 0) {
        result.success = false;
        result.errorMessage = "Failed to measure latency";
        return result;
    }

    // Test download speed
    std::cout << "Testing download speed..." << std::endl;
    result.downloadSpeed = measureDownloadSpeed(testServer, testPort);
    if (result.downloadSpeed < 0) {
        result.success = false;
        result.errorMessage = "Failed to measure download speed";
        return result;
    }

    // Test upload speed
    std::cout << "Testing upload speed..." << std::endl;
    result.uploadSpeed = measureUploadSpeed(testServer, testPort);
    if (result.uploadSpeed < 0) {
        result.success = false;
        result.errorMessage = "Failed to measure upload speed";
        return result;
    }

    return result;
}

double NetworkSpeedTester::measureLatency(const std::string& host, int port) {
    const int numPings = 5;
    double totalLatency = 0.0;
    int successfulPings = 0;

    for (int i = 0; i < numPings; i++) {
        auto start = std::chrono::high_resolution_clock::now();

        SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == INVALID_SOCKET) {
            continue;
        }

        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);

        struct hostent* he = gethostbyname(host.c_str());
        if (he == nullptr) {
            closesocket(sock);
            continue;
        }

        addr.sin_addr = *((struct in_addr*)he->h_addr);

        if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
            closesocket(sock);
            continue;
        }

        auto end = std::chrono::high_resolution_clock::now();
        double latency = std::chrono::duration<double, std::milli>(end - start).count();
        totalLatency += latency;
        successfulPings++;

        closesocket(sock);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return successfulPings > 0 ? totalLatency / successfulPings : -1.0;
}

double NetworkSpeedTester::measureDownloadSpeed(const std::string& host, int port) {
    auto start = std::chrono::high_resolution_clock::now();

    // Downloading a test file from httpbin.org of one MB
    std::vector<char> data = downloadData(host, port, "/bytes/1048576"); // ONE MB

    auto end = std::chrono::high_resolution_clock::now();

    if (data.empty()) {
        return -1.0;
    }

    double duration = std::chrono::duration<double>(end - start).count();
    double bytesPerSecond = data.size() / duration;
    double mbps = (bytesPerSecond * 8) / (1024 * 1024); // Conversion to MBs

    return mbps;
}

double NetworkSpeedTester::measureUploadSpeed(const std::string& host, int port) {
    std::string testData = generateTestData(testDataSize);

    auto start = std::chrono::high_resolution_clock::now();

    bool success = uploadData(host, port, testData);

    auto end = std::chrono::high_resolution_clock::now();

    if (!success) {
        return -1.0;
    }

    double duration = std::chrono::duration<double>(end - start).count();
    double bytesPerSecond = testData.size() / duration;
    double mbps = (bytesPerSecond * 8) / (1024 * 1024); // Conversion to MBs

    return mbps;
}

std::string NetworkSpeedTester::generateTestData(size_t size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);

    std::string data;
    data.reserve(size);

    for (size_t i = 0; i < size; i++) {
        data += static_cast<char>(dis(gen));
    }

    return data;
}

std::vector<char> NetworkSpeedTester::downloadData(const std::string& host, int port, const std::string& path) {
    std::vector<char> result;

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        return result;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    struct hostent* he = gethostbyname(host.c_str());
    if (he == nullptr) {
        closesocket(sock);
        return result;
    }

    addr.sin_addr = *((struct in_addr*)he->h_addr);

    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        closesocket(sock);
        return result;
    }

    // Send HTTP GET request
    std::ostringstream request;
    request << "GET " << path << " HTTP/1.1\r\n";
    request << "Host: " << host << "\r\n";
    request << "Connection: close\r\n\r\n";

    std::string requestStr = request.str();
    send(sock, requestStr.c_str(), requestStr.length(), 0);

    // Read response
    char buffer[4096];
    bool headersParsed = false;
    std::string headers;

    while (true) {
        int bytesReceived = recv(sock, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            break;
        }
        
        if (!headersParsed) {
            headers.append(buffer, bytesReceived);
            size_t headerEnd = headers.find("\r\n\r\n");
            if (headerEnd != std::string::npos) {
                headersParsed = true;
                size_t bodyStart = headerEnd + 4;
                if (bodyStart < headers.length()) {
                    result.insert(result.end(), 
                                headers.begin() + bodyStart, 
                                headers.end());
                }
            }
        } else {
            result.insert(result.end(), buffer, buffer + bytesReceived);
        }
    }
    
    closesocket(sock);
    return result;
}

bool NetworkSpeedTester::uploadData(const std::string& host, int port, const std::string& data) {
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        return false;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

   struct hostent* he = gethostbyname(host.c_str());
    if (he == nullptr) {
        closesocket(sock);
        return false;
    }

    addr.sin_addr = *((struct in_addr*)he->h_addr);

    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        closesocket(sock);
        return false;
    }

    // Sending HTTP POST request
    std::ostringstream request;
    request << "POST /post HTTP/1.1\r\n";
    request << "Host: " << host << "\r\n";
    request << "Content-Type: application/octet-stream\r\n";
    request << "Content-Length: " << data.length() << "\r\n";
    request << "Connection: close\r\n\r\n";
    request << data;

    std::string requestStr = request.str();
    int totalSent = 0;
    int totalSize = requestStr.length();

    while (totalSent < totalSize) {
        int sent = send(sock, requestStr.c_str() + totalSent, totalSize - totalSent, 0);
        if (sent == SOCKET_ERROR) {
            closesocket(sock);
            return false;
        }
        totalSent += sent;
    }

    closesocket(sock);
    return true;
}

double NetworkSpeedTester::testDownloadSpeed() {
    return measureDownloadSpeed(testServer, testPort);
}

double NetworkSpeedTester::testUploadSpeed() {
    return measureUploadSpeed(testServer, testPort);
}

double NetworkSpeedTester::testLatency() {
    return measureLatency(testServer, testPort);
}

std::string NetworkSpeedTester::formatSpeed(double speedMbps) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << speedMbps << " Mbps";
    return oss.str();
}

void NetworkSpeedTester::printResults(const SpeedTestResult& result) {
    std::cout << "\n--- Network speed test results" << std::endl;
    if (result.success) {
        std::cout << "Latency: " << std::fixed << std::setprecision(2) << result.latency << " ms" << std::endl;
        std::cout << "Download speed: " << formatSpeed(result.downloadSpeed) << std::endl;
        std::cout << "Upload speed: " << formatSpeed(result.uploadSpeed) << std::endl;
    } else {
        std::cout << "Test failed: " << result.errorMessage << std::endl;
    }
    std::cout << "=================================" << std::endl;
}