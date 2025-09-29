#include "AppState.h"
#include "CLI.h"
#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    AppState state;
    state.accounts["Default"] = Account("Default", 0.0);
    state.load();
    cout << "Expense tracker, data file: data_store.txt" << "\n";
    main_loop(state);
    return 0;
}