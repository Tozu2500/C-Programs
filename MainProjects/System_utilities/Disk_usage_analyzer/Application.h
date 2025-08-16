#ifndef APPLICATION_H
#define APPLICATION_H

#include "DiskScanner.h"
#include "TerminalUI.h"
#include "FileInfo.h"
#include <string>
#include <memory>

class Application {
public:
    Application();
    ~Application();

    int run(int argc, char* argv[]);
    void showMainMenu();
    void scanDirectory();
    void selectDrive();
    void customPath();
    void exitApplication();

private:
    void displayWelcome();
    void displayDrives();
    std::string getValidPath();
    void performScan(const std::string& path);
    void handleScanProgress(const std::string& currentFile, int filesProcessed);
    bool checkPath(const std::string& path);

    std::unique_ptr<DiskScanner> scanner;
    std::unique_ptr<TerminalUI> ui;
    bool running;
    bool scanInProgress;
};

#endif // APPLICATION_H