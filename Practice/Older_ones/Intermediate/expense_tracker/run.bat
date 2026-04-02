@echo off
REM Run script for Expense Tracker
REM This script runs the expense tracker through MSYS2 environment

if not exist "expense_tracker.exe" (
    echo Error: expense_tracker.exe not found!
    echo Please run build.bat first to compile the program.
    pause
    exit /b 1
)

if not exist "C:\msys64\usr\bin\bash.exe" (
    echo Error: MSYS2 not found at C:\msys64\
    echo Please install MSYS2 from https://www.msys2.org/
    pause
    exit /b 1
)

echo Starting Expense Tracker...
echo Press Ctrl+C to exit if needed.
echo.
C:\msys64\usr\bin\env MSYSTEM=UCRT64 C:\msys64\usr\bin\bash.exe -l -c "cd '%CD%' && ./expense_tracker"

echo.
echo Expense Tracker has exited.
pause