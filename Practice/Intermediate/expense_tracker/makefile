CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

SRC = main.cpp Utils.cpp Transaction.cpp Account.cpp Goal.cpp AppState.cpp Reports.cpp CLI.cpp
OBJ = $(SRC:.cpp=.o)

all: expense_tracker

expense_tracker: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJ) expense_tracker