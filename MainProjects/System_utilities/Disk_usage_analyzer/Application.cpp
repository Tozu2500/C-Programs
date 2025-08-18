#include "Application.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <thread>
#include <chrono>
#include <iomanip>

Application::Application() : running(true), scanInProgress(false) {
    scanner = std::make_unique<DiskScanner>();
    ui = std::make_unique<TerminalUI>();
}

Application::~Application() = default;

int Application::run(int argc, char* argv[]) {
    displayWelcome();

    if (argc > 1) {
        std::string path = argv[1];
        if (checkPath(path)) {
            performScan(path);
            ui->run();
            return 0;
        } else {
            std::cout << "Invalid path: " << path << std::endl;
            std::cout << "Press any key to continue to main menu...";
            _getch();
        }
    }

    while (running) {
        showMainMenu();
    }

    return 0;
}

void Application::displayWelcome() {
    ui->clearScreen();
    std::cout << "╔════════════════════════════════════════════════════════════╗\n";
    std::cout << "║                    DISK USAGE ANALYZER                     ║\n";
    std::cout << "║                         Version 1.0                        ║\n";
    std::cout << "╚════════════════════════════════════════════════════════════╝\n\n";
    std::cout << "A powerful terminal-based tool for analyzing disk usage\n";
    std::cout << "and identifying space-consuming files and directories.\n\n";
}

void Application::showMainMenu() {
    ui->clearScreen();
    displayWelcome();

    std::cout << "Main Menu:\n";
    std::cout << "═════════════════════════════════════════════════════════════\n";
    std::cout << "1. Scan Available Drives\n";
    std::cout << "2. Scan a Custom directory path\n";
    std::cout << "3. Quick scan current directory\n";
    std::cout << "4. Help\n";
    std::cout << "5. About\n";
    std::cout << "6. Exit\n";
    std::cout << "═════════════════════════════════════════════════════════════\n";
    std::cout << "Please select an option (1-6): ";

    char choice = _getch();
    std::cout << choice << std::endl;

    switch (choice) {
        case '1':
            selectDrive();
            break;
        case '2':
            customPath();
            break;
        case '3':
            performScan(".");
            ui->run();
            break;
        case '4':
            ui->showHelp();
            break;
        case '5':
            ui->showAbout();
            break;
        case '6':
            exitApplication();
            break;
        default:
            std::cout << "Invalid option, try again\n";
            std::cout << "Press any key to continue...";
            _getch();
            break;
    }
}

void Application::selectDrive() {
    ui->clearScreen();
    displayWelcome();

    auto drives = DiskScanner::getAvailableDrives();

    if (drives.empty()) {
        std::cout << "No drives available for scanning.\n";
        std::cout << "Press any key to return to the main menu...";
        _getch();
        return;
    }

    displayDrives();

    std::cout << "\nAvailable drives.\n";
    std::cout << "=======================================================\n";

    for (size_t i = 0; i < drives.size(); i++) {
        std::cout << (i + 1) << ". Drive" << drives[i] << "\\";

        std::string drivePath = drives[i] + "\\";
        ULARGE_INTEGER freeBytesAvailable, totalNumberOfBytes, totalNumberOfFreeBytes;

        if (GetDiskFreeSpaceExA(drivePath.c_str(), &freeBytesAvailable, &totalNumberOfBytes, &totalNumberOfFreeBytes)) {
            double totalGB = totalNumberOfBytes.QuadPart / (1024.0 * 1024.0 * 1024.0);
            double freeGB = totalNumberOfFreeBytes.QuadPart / (1024.0 * 1024.0 * 1024.0);
            double usedGB = totalGB - freeGB;

            std::cout << " [" << std::fixed << std::setprecision(1) << usedGB << " GB used / " << totalGB << " GB total]";
        }
        std::cout << std::endl;
    }

    std::cout << (drives.size() + 1) << ". Return to main menu\n";
    std::cout << "=======================================================\n";
    std::cout << "Please select a drive (1-" << (drives.size() + 1) << "): ";

    char choice = _getch();
    std::cout << choice << std::endl;

    int selection = choice - '1';

    if (selection >= 0 && selection < static_cast<int>(drives.size())) {
        std::string drivePath = drives[selection] + "\\";
        performScan(drivePath);
        ui->run();
    } else if (selection == static_cast<int>(drives.size())) {
        return;
    } else {
        std::cout << "Invalid selection. Press any key to continue...";
        _getch();
        selectDrive();
    }
}

void Application::displayDrives() {
    auto drives = DiskScanner::getAvailableDrives();

    std::cout << "Drive Information:\n";
    std::cout << "=======================================================\n";

    for (const auto& drive : drives) {
        std::string drivePath = drive + "\\";
        UINT driveType = GetDriveTypeA(drivePath.c_str());

        std::cout << "Drive " << drive << ": ";

        switch (driveType) {
            case DRIVE_FIXED:
                std::cout << "Fixed Drive (Hard Disk)";
                break;
            case DRIVE_REMOVABLE:
                std::cout << "Removable Drive";
                break;
            case DRIVE_REMOTE:
                std::cout << "Network Drive";
                break;
            case DRIVE_CDROM:
                std::cout << "CD-ROM Drive";
                break;
            case DRIVE_RAMDISK:
                std::cout << "RAM Disk";
                break;
            default:
                std::cout << "Unknown Drive Type";
                break;
        }

        char volumeName[MAX_PATH];
        char fileSystemName[MAX_PATH];
        DWORD serialNumber, maxComponentLength, fileSystemFlags;

        if (GetVolumeInformationA(drivePath.c_str(), volumeName, MAX_PATH,
    &serialNumber, &maxComponentLength, &fileSystemFlags, fileSystemName, MAX_PATH)) {
        if (strlen(volumeName) > 0) {
            std::cout << " - " << volumeName;
        }
        std::cout << " (" << fileSystemName << ")";
    }

    std::cout << std::endl;
    }
    std::cout << "=======================================================\n";
}

void Application::customPath() {
    ui->clearScreen();
    displayWelcome();

    std::cout << "Custom Directory Scan:\n";
    std::cout << "============================================\n";
    std::cout << "Enter the full path to the directory you want to scan:\n";
    std::cout << "Examples:\n";
    std::cout << "  C:\\Users\\Username\\Documents\n";
    std::cout << "  D:\\Projects\n";
    std::cout << "  .\\ (current directory)\n";
    std::cout << " ..\\ (parent directory)\n\n";
    std::cout << "Path: ";

    std::string path = getValidPath();

    if (path.empty()) {
        std::cout << "Operation cancelled.\n";
        std::cout << "Press any key to return to main menu...";
        _getch();
        return;
    }

    if (checkPath(path)) {
        performScan(path);
        ui->run();
    } else {
        std::cout << "Invalid or inaccessible path: " << path << std::endl;
        std::cout << "Press any key to return to main menu...";
        _getch();
    }
}

std::string Application::getValidPath() {
    std::string path;
    std::getline(std::cin, path);

    if (path.empty()) {
        return "";
    }

    if (path == "." || path == ".\\") {
        char currentDir[MAX_PATH];
        GetCurrentDirectoryA(MAX_PATH, currentDir);
        return std::string(currentDir);
    }

    if (path == ".." || path == "..\\") {
        char currentDir[MAX_PATH];
        GetCurrentDirectoryA(MAX_PATH, currentDir);
        std::string current(currentDir);
        size_t lastBackslash = current.find_last_of("\\");
        if (lastBackslash != std::string::npos) {
            return current.substr(0, lastBackslash);
        }
    }

    return path;
}

bool Application::checkPath(const std::string& path) {
    DWORD attributes = GetFileAttributesA(path.c_str());
    return (attributes != INVALID_FILE_ATTRIBUTES &&
        (attributes & FILE_ATTRIBUTE_DIRECTORY));
}

void Application::performScan(const std::string& path) {
    ui->clearScreen();
    displayWelcome();

    std::cout << "Preparing to scan: " << path << std::endl;
    std::cout << "This may take some time depending on the size of the directory...\n\n";
    std::cout << "Press ESC at any time to cancel\n";
    std::cout << "====================================================\n\n";

    scanInProgress = true;

    scanner->setProgressCallback([this](const std::string& currentFile, int filesProcessed) {
        this->handleScanProgress(currentFile, filesProcessed);
    });

    auto startTime = std::chrono::high_resolution_clock::now();

    std::thread scanThread([this, path]() {
        FileInfo result = scanner->scanDirectory(path);

        if (!scanner->isCancelled()) {
            ui->displayFileList(result);
        }

        scanInProgress = false;
    });

    while (scanInProgress) {
        if (_kbhit()) {
            int key = _getch();
            if (key == 27) {
                scanner->cancelScan();
                std::cout << "\nScan cancelled by user.\n";
                std::cout << "Press any key to continue to main menu...";
                _getch();
                break;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    scanThread.join();

    if (!scanner->isCancelled()) {
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);

        ui->clearScreen();
        std::cout << "Scan completed successfully!\n";
        std::cout << "Time elapsed: " << duration.count() << " seconds\n";
        std::cout << "Press any key to view the results...";
        _getch();
    }
}

void Application::handleScanProgress(const std::string& currentFile, int filesProcessed) {
    if (filesProcessed % 50 == 0) {
        ui->showProgressBar(currentFile, filesProcessed);
    }
}

void Application::exitApplication() {
    ui->clearScreen();
    std::cout << "Thank you for using the disk usage analyzer\n";
    std::cout << "Goodbye!\n";
    running = false;
}