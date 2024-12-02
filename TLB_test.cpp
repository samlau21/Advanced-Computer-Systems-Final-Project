#include <iostream>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <unistd.h>

const int PAGE_SIZE = 248*1024; // 4KB page size
const int NUM_PAGES = 16*1024; // Number of pages to access

int main() {
    int *array = new int[NUM_PAGES * PAGE_SIZE / sizeof(int)];

    // Warm-up to allocate pages
    for (int i = 0; i < NUM_PAGES; ++i) {
        array[i * PAGE_SIZE / sizeof(int)] = 1;
    }

    // Measure access time with TLB misses
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM_PAGES; ++i) {
        volatile int temp = array[(i * PAGE_SIZE / sizeof(int)) % (NUM_PAGES * PAGE_SIZE / sizeof(int))];
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;

    std::cout << "Time taken: " << diff.count() << " seconds" << std::endl;

    delete[] array;
    return 0;
}
