#pragma once
#include <filesystem>

namespace ccrm::service {

class BackupService {
public:
    // Java: Files.createDirectories(), Files.copy(), LocalDateTime for the
    // timestamped folder name. C++17 <filesystem> covers the first two
    // directly; <chrono> (C++20) covers the timestamp.
    std::filesystem::path createBackup(const std::filesystem::path& sourceDir,
                                        const std::filesystem::path& backupRoot) const;
};

} // namespace ccrm::service
