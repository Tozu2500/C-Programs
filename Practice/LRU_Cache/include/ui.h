#ifndef UI_H
#define UI_H

#include "lru_cache.h"

void runMainLoop();

int showWelcomeScreen();

int showMainMenu(const LRUCache& cache);

void showCacheState(const LRUCache& cache);

void handleGet(LRUCache& cache);

void handlePut(LRUCache& cache);

void handleRemove(LRUCache& cache);

void handleClear(LRUCache& cache);

#endif // UI_H