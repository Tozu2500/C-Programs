# Makefile for Expense Tracker
# Compatible with MSYS2/MinGW-w64 and traditional Unix make

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = expense_tracker
SRCDIR = .
OBJDIR = .

# Source files
SOURCES = main.cpp Utils.cpp Transaction.cpp Account.cpp Goal.cpp AppState.cpp Reports.cpp CLI.cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = Utils.h Transaction.h Account.h Goal.h AppState.h Reports.h CLI.h

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files to object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJECTS) $(TARGET) $(TARGET).exe

# Clean and rebuild
rebuild: clean all

# Debug build
debug: CXXFLAGS = -std=c++17 -Wall -Wextra -g -DDEBUG
debug: clean $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Install (copy to a bin directory if needed)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/ 2>/dev/null || echo "Install target requires admin privileges"

# Show help
help:
	@echo "Available targets:"
	@echo "  all     - Build the expense tracker (default)"
	@echo "  clean   - Remove object files and executable"
	@echo "  rebuild - Clean and build"
	@echo "  debug   - Build with debug symbols"
	@echo "  run     - Build and run the program"
	@echo "  install - Install to /usr/local/bin"
	@echo "  help    - Show this help message"

# Declare phony targets
.PHONY: all clean rebuild debug run install help