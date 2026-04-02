#include "AppState.h"
#include "CLI.h"
#include <iostream>
using namespace std;

int main()
{
    // Removed I/O optimizations that can cause issues on Windows
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
    try {
        AppState state;
        state.accounts["Default"] = Account("Default", 0.0);
        state.load();
        cout << "Expense Tracker (modular). Data file: data_store.txt" << "\n";
        main_loop(state);
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        return 1;
    }
    catch (...) {
        cout << "Unknown error occurred." << endl;
        return 1;
    }
    
    return 0;
}