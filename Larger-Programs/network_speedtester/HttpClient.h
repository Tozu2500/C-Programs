#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <string>
#include <vector>
#include <chrono>

struct TestResult {
    double downloadSpeed;
    double uploadSpeed;
    double latency;
    bool success;
    std::string error;
};

class HttpClient {
private:
    std::string userAgent;
    int timeout;

    // Helpers
    size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* data);
    size_t ReadCallback(void* ptr, size_t size, size_t nmemb, std::string* data);

public:
    HttpClient();
    ~HttpClient();

    // Config
    void setTimeout(int seconds);
    void setUserAgent(const std::string& agent);

    // Network ops
    std::string get(const std::string& url);
    std::string post(const std::string& url, const std::string& data);

    // Speed testing functions
    double measureDownloadSpeed(const std::string& url, int durationSeconds = 10);
    double measureUploadSpeed(const std::string& url, int durationSeconds = 10);
    double measureLatency(const std::string& url, int attempts = 5);

    // Util
    bool isConnected();
    std::vector<std::string> getDefaultTestServers();
};

#endif // HTTP_CLIENT_H
