@echo off
REM Build script for Expense Tracker using MSYS2/MinGW-w64
REM This script compiles the C++ expense tracker application

echo Building Expense Tracker...

REM Check if MSYS2 is available
if not exist "C:\msys64\usr\bin\bash.exe" (
    echo Error: MSYS2 not found at C:\msys64\
    echo Please install MSYS2 from https://www.msys2.org/
    pause
    exit /b 1
)

REM Clean previous build files
echo Cleaning previous build files...
del /q *.o >nul 2>&1
del /q expense_tracker.exe >nul 2>&1

REM Compile the project
echo Compiling source files...
C:\msys64\usr\bin\env MSYSTEM=UCRT64 C:\msys64\usr\bin\bash.exe -l -c "cd '%CD%' && g++ -std=c++17 -Wall -Wextra -O2 -c *.cpp"

if errorlevel 1 (
    echo Compilation failed!
    pause
    exit /b 1
)

echo Linking executable...
C:\msys64\usr\bin\env MSYSTEM=UCRT64 C:\msys64\usr\bin\bash.exe -l -c "cd '%CD%' && g++ -std=c++17 -Wall -Wextra -O2 -o expense_tracker *.o"

if errorlevel 1 (
    echo Linking failed!
    pause
    exit /b 1
)

echo Build successful! Executable created: expense_tracker.exe
echo.
echo To run the program:
echo   1. Through MSYS2: ./expense_tracker
echo   2. Or use the run.bat script
echo.
pause