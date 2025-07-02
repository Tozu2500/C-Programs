# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = taskmanager
SRCDIR = .
OBJDIR = obj

# Source files
SOURCES = main.cpp Task.cpp TaskManager.cpp
OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)

# Default target
all: $(TARGET)

# Create target executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)
	@echo "Build complete! Run with: ./$(TARGET)"

# Compile source files to object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Dependencies
$(OBJDIR)/main.o: main.cpp Task.h TaskManager.h
$(OBJDIR)/Task.o: Task.cpp Task.h
$(OBJDIR)/TaskManager.o: TaskManager.cpp TaskManager.h Task.h

# Clean build files
clean:
	rm -rf $(OBJDIR) $(TARGET)
	@echo "Clean complete!"

# Install (copy to /usr/local/bin)
install: $(TARGET)
	sudo cp $(TARGET) /usr/local/bin/
	@echo "Installed to /usr/local/bin/$(TARGET)"

# Uninstall
uninstall:
	sudo rm -f /usr/local/bin/$(TARGET)
	@echo "Uninstalled $(TARGET)"

# Debug build
debug: CXXFLAGS += -g -DDEBUG
debug: clean $(TARGET)

# Release build
release: CXXFLAGS += -DNDEBUG
release: clean $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Show help
help:
	@echo "Available targets:"
	@echo "  all      - Build the program (default)"
	@echo "  clean    - Remove build files"
	@echo "  debug    - Build with debug symbols"
	@echo "  release  - Build optimized release version"
	@echo "  run      - Build and run the program"
	@echo "  install  - Install to /usr/local/bin"
	@echo "  uninstall- Remove from /usr/local/bin"
	@echo "  help     - Show this help message"

# Declare phony targets
.PHONY: all clean debug release run install uninstall help