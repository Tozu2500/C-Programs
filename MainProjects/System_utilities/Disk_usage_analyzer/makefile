CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -static-libgcc -static-libstdc++
LDFLAGS = -static
TARGET = DiskAnalyzer.exe
OBJDIR = obj
SRCDIR = .

SOURCES = main.cpp FileInfo.cpp DiskScanner.cpp TerminalUI.cpp Application.cpp
OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)
HEADERS = FileInfo.h DiskScanner.h TerminalUI.h Application.h

.PHONY: all clean debug release install uninstall help

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(OBJDIR)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)
	@echo "Build completed successfully!"
	@echo "Executable: $(TARGET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

debug: CXXFLAGS += -DDEBUG -g -O0
debug: $(TARGET)
	@echo "Debug build completed!"

release: CXXFLAGS += -DRELEASE -DNDEBUG -O3
release: $(TARGET)
	@echo "Release build completed!"

clean:
	@if exist $(OBJDIR) rmdir /s /q $(OBJDIR)
	@if exist $(TARGET) del $(TARGET)
	@if exist *.exe del *.exe
	@echo "Clean completed!"

install: $(TARGET)
	@if not exist "%PROGRAMFILES%\DiskAnalyzer" mkdir "%PROGRAMFILES%\DiskAnalyzer"
	copy $(TARGET) "%PROGRAMFILES%\DiskAnalyzer\"
	copy README.md "%PROGRAMFILES%\DiskAnalyzer\"
	@echo "Installation completed to %PROGRAMFILES%\DiskAnalyzer"
	@echo "Add the installation directory to your PATH to use from anywhere"

uninstall:
	@if exist "%PROGRAMFILES%\DiskAnalyzer" rmdir /s /q "%PROGRAMFILES%\DiskAnalyzer"
	@echo "Uninstall completed!"

test: $(TARGET)
	@echo "Running basic functionality test..."
	@echo "Testing help command:"
	echo h | $(TARGET)
	@echo "Test completed!"

package: release
	@if not exist "dist" mkdir dist
	copy $(TARGET) dist\
	copy README.md dist\
	copy Makefile dist\
	copy *.h dist\
	copy *.cpp dist\
	@echo "Package created in dist\ directory"

run: $(TARGET)
	@echo "Starting Disk Usage Analyzer..."
	.\$(TARGET)

help:
	@echo "Available targets:"
	@echo "  all       - Build the application (default)"
	@echo "  debug     - Build with debug information"
	@echo "  release   - Build optimized release version"
	@echo "  clean     - Remove all build files"
	@echo "  install   - Install to Program Files"
	@echo "  uninstall - Remove from Program Files"
	@echo "  test      - Run basic functionality test"
	@echo "  package   - Create distribution package"
	@echo "  run       - Build and run the application"
	@echo "  help      - Show this help message"
	@echo ""
	@echo "Compiler: $(CXX)"
	@echo "Flags: $(CXXFLAGS)"
	@echo "Target: $(TARGET)"