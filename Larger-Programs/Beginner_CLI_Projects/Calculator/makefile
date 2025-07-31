CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET = calculator.exe
SOURCES = main.cpp calculator.cpp expression_parser.cpp ui_handler.cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = calculator.h expression_parser.h ui_handler.h

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q *.o $(TARGET) 2>nul || true

rebuild: clean all

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean rebuild runs