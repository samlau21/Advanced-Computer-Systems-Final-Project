#include <iostream>
#include <chrono>
#include <vector>

// Latency Benchmark
constexpr size_t L1_SIZE = 32 * 1024;
constexpr size_t L2_SIZE = 4 * 1024 * 1024;
constexpr size_t STEP = 64;

void measure_latency(size_t array_size) {
    std::vector<size_t> data(array_size / sizeof(size_t));
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] = (i + STEP) % data.size();
    }

    volatile size_t idx = 0;
    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < 100000000; ++i) {
        idx = data[idx];
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Latency - Size: " << array_size / 1024 << " KB, Time: " << duration.count() << " sec\n";
}

// Bandwidth Benchmark
constexpr size_t ARRAY_SIZE = 512 * 1024 * 1024;  // Increase array size to 512MB

void measure_bandwidth() {
    std::vector<char> data(ARRAY_SIZE);

// Warm-up loop to load data into cache
for (size_t i = 0; i < data.size(); ++i) {
    data[i] = i % 256;
}

auto start = std::chrono::high_resolution_clock::now();

// Repeat loop to accumulate measurable time
for (size_t repeat = 0; repeat < 100; ++repeat) {  // Repeat the loop many times
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] = i % 256;
    }
}

auto end = std::chrono::high_resolution_clock::now();
std::chrono::duration<double> duration = end - start;

std::cout << "Time: " << duration.count() << " sec, Bandwidth: "
          << ((ARRAY_SIZE * 100) / (duration.count() * 1e9)) << " GB/s\n"; // Note: Multiply by repeat count
}


int main() {
    // Run Latency Benchmarks
    measure_latency(24*1024*1024);  
    measure_latency(8*1024*1024);
    measure_latency(16*1024);

    // Run Bandwidth Benchmark
    measure_bandwidth();

    return 0;
}
