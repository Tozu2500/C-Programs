#include "NetworkSpeedTester.h"
#include <iostream>
#include <string>

void printMenu() {
    std::cout << "\n --- Network speed tester --- " << std::endl;
    std::cout << "1. Run full speed test" << std::endl;
    std::cout << "2. Test download speed" << std::endl;
    std::cout << "3. Test upload speed" << std::endl;
    std::cout << "4. Test latency" << std::endl;
    std::cout << "5. Change test server" << std::endl;
    std::cout << "6. Change test data size" << std::endl;
    std::cout << "0. Exit program" << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout << "Choose an option: ";
}

int main() {
    NetworkSpeedTester tester;
    std::string input;
    int choice;

    std::cout << "Windows network speed tester 1.0" << std::endl;
    std::cout << "=====================================" << std::endl;

    while (true) {
        printMenu();
        std::getline(std::cin, input);

        try {
            choice = std::stoi(input);
        } catch (const std::exception&) {
            std::cout << "Invalid input. Choose a valid option." << std::endl;
            continue;
        }

        switch (choice) {
            case 1: {
                SpeedTestResult result = tester.runFullTest();
                tester.printResults(result);
                break;
            }
            case 2: {
                std::cout << "Testing download speed..." << std::endl;
                double downloadSpeed = tester.testDownloadSpeed();
                if (downloadSpeed > 0) {
                    std::cout << "Download speed: " << tester.formatSpeed(downloadSpeed) << std::endl;
                } else {
                    std::cout << "Download speed test failed" << std::endl;
                }
                break;
            }
            case 3: {
                std::cout << "Testing upload speed..." << std::endl;
                double uploadSpeed = tester.testUploadSpeed();
                if (uploadSpeed > 0) {
                    std::cout << "Upload speed: " << tester.formatSpeed(uploadSpeed) << std::endl;
                } else {
                    std::cout << "Upload speed test failed" << std::endl;
                }
                break;
            }
            case 4: {
                std::cout << "Testing latency..." << std::endl;
                double latency = tester.testLatency();
                if (latency > 0) {
                    std::cout << "Latency: " << latency << " ms" << std::endl;
                } else {
                    std::cout << "Latency test failed" << std::endl;
                }
                break;
            }
            case 5: {
                std::cout << "Enter new server address (e.g., httpbin.org): ";
                std::string server;
                std::getline(std::cin, server);
                if (!server.empty()) {
                    tester.setTestServer(server);
                    std::cout << "Test server changed to: " << server << std::endl;
                }
                break;
            }
            case 6: {
                std::cout << "Enter test data size in bytes (e.g., 1048576 for 1Mb): ";
                std::string sizeStr;
                std::getline(std::cin, sizeStr);
                try {
                    size_t size = std::stoull(sizeStr);
                    tester.setTestDataSize(size);
                    std::cout << "Test data size changed to: " << size << " bytes" << std::endl;
                } catch (const std::exception&) {
                    std::cout << "Invalid size format" << std::endl;
                }
                break;
            }
            case 0:
                std::cout << "Exiting... Thank you for using the program!" << std::endl;
                return 0;
            default:
                std::cout << "Invalid option. Choose something between 0-8" << std::endl;
                break;
        }
    }

    return 0;
}