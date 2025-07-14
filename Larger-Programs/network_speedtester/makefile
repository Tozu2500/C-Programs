# Makefile for Network Speed Tester

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
LDFLAGS = -lws2_32

TARGET = NetworkSpeedTester.exe
SOURCES = main.cpp NetworkSpeedTester.cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = NetworkSpeedTester.h

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q *.o $(TARGET) 2>nul || true

install: $(TARGET)
	copy $(TARGET) C:\Windows\System32\

.PHONY: run
run: $(TARGET)
	./$(TARGET)

# Debug build
debug: CXXFLAGS += -g -DDEBUG
debug: clean $(TARGET)

# Release build  
release: CXXFLAGS += -DNDEBUG
release: clean $(TARGET)