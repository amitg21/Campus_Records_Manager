#pragma once
#include <string>
#include <filesystem>

namespace ccrm::config {

// Design Pattern: Singleton.
// Java typically does this with a private constructor + static getInstance()
// holding a static field. The idiomatic modern C++ equivalent is the
// "Meyers singleton": a function-local static, which the C++11 standard
// guarantees is initialized exactly once, thread-safely, on first use.
class AppConfig {
public:
    static AppConfig& instance() {
        static AppConfig inst; // constructed once, on first call
        return inst;
    }

    // Not copyable/movable -- a singleton shouldn't be duplicated.
    AppConfig(const AppConfig&) = delete;
    AppConfig& operator=(const AppConfig&) = delete;

    std::filesystem::path dataDirectory() const { return dataDir_; }
    std::filesystem::path backupDirectory() const { return backupDir_; }
    int maxCreditsPerSemester() const { return maxCreditsPerSemester_; }

private:
    AppConfig() = default;

    std::filesystem::path dataDir_ = "data";
    std::filesystem::path backupDir_ = "backups";
    int maxCreditsPerSemester_ = 24;
};

} // namespace ccrm::config
