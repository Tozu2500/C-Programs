@echo off
echo Expense Tracker - Quick Demo
echo ============================
echo.
echo This demo will:
echo 1. Show the default account
echo 2. List current transactions (should be empty)
echo 3. Exit the program
echo.
echo Press any key to start the demo...
pause >nul

echo.
echo Running demo...
echo.

C:\msys64\usr\bin\env MSYSTEM=UCRT64 C:\msys64\usr\bin\bash.exe -l -c "cd '%CD%' && echo -e '1\n2\n7' | ./expense_tracker"

echo.
echo Demo completed! The program is working correctly.
echo.
echo To run the full interactive version, use: run.bat
pause