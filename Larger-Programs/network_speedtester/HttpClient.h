#pragma once

#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#include <winhttp.h>
#endif

class HttpClient {
public:
    HttpClient();
    ~HttpClient();

    void setTimeout(int seconds);
    void setUserAgent(const std::string& agent);

    std::string get(const std::string& url);
    std::string post(const std::string& url, const std::string& data);

    double measureDownloadSpeed(const std::string& url, int durationSeconds = 10);
    double measureUploadSpeed(const std::string& url, int durationSeconds = 10);
    double measureLatency(const std::string& url, int attempts = 5);

    bool isConnected();
    std::vector<std::string> getDefaultTestServers();

private:
    std::string userAgent;
    int timeout;

#ifdef _WIN32
    HINTERNET hSession;

    bool initializeWinHTTP();
    void cleanupWinHTTP();
    void configureProxy();
#endif
};
