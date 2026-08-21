#pragma once
#include <filesystem>
#include <cstdint>

namespace ccrm::util {

class RecursiveFileUtils {
public:
    // Recursion over std::filesystem, replacing Java's NIO.2 walk.
    static std::uintmax_t calculateDirectorySize(const std::filesystem::path& dir);

    // Demonstrates control flow: bitwise operators + a labeled break.
    // C++ has no `label:` + `break label;` like Java; the standard
    // replacement is `goto` to a label placed right after the loop nest
    // (the one broadly-accepted legitimate use of goto in C++).
    static void demoControlFlow();
};

} // namespace ccrm::util
