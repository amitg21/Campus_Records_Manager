#include "ccrm/util/RecursiveFileUtils.hpp"
#include <iostream>

namespace ccrm::util {

namespace fs = std::filesystem;

std::uintmax_t RecursiveFileUtils::calculateDirectorySize(const fs::path& dir) {
    std::uintmax_t total = 0;
    if (!fs::exists(dir)) return 0;

    for (const auto& entry : fs::directory_iterator(dir)) {
        if (entry.is_directory()) {
            total += calculateDirectorySize(entry.path()); // recursion
        } else if (entry.is_regular_file()) {
            total += entry.file_size();
        }
    }
    return total;
}

void RecursiveFileUtils::demoControlFlow() {
    // Bitwise operator demo.
    int flagsA = 0b1010;
    int flagsB = 0b0110;
    std::cout << "AND: " << (flagsA & flagsB)
              << " OR: " << (flagsA | flagsB)
              << " XOR: " << (flagsA ^ flagsB)
              << " NOT A: " << (~flagsA)
              << " A<<1: " << (flagsA << 1) << "\n";

    // Java: outer: for (...) { for (...) { if (cond) break outer; } }
    // C++: no labeled break, so goto a label after the loop nest.
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (i * j > 6) {
                std::cout << "Breaking out at i=" << i << ", j=" << j << "\n";
                goto after_loops;
            }
        }
    }
after_loops:
    std::cout << "Exited nested loop.\n";
}

} // namespace ccrm::util
