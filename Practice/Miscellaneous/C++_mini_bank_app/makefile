# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -pedantic

# Target executable
TARGET = banking_app

# Source files
SOURCES = Main.cpp Account.cpp Bank.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Header files
HEADERS = Account.h bank.h

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "Build successful! Run with: ./$(TARGET)"

# Compile source files to object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "Clean complete!"

# Rebuild everything
rebuild: clean all

# Run the application
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean rebuild run