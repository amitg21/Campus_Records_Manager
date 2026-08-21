#include "ccrm/service/BackupService.hpp"
#include <chrono>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <iostream>

namespace ccrm::service {

namespace fs = std::filesystem;

static std::string timestampNow() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tmBuf{};
#if defined(_WIN32)
    localtime_s(&tmBuf, &t);
#else
    localtime_r(&t, &tmBuf);
#endif
    std::ostringstream oss;
    oss << std::put_time(&tmBuf, "%Y%m%d_%H%M%S");
    return oss.str();
}

fs::path BackupService::createBackup(const fs::path& sourceDir, const fs::path& backupRoot) const {
    fs::path target = backupRoot / ("backup_" + timestampNow());
    fs::create_directories(target); // Files.createDirectories()

    if (fs::exists(sourceDir)) {
        for (const auto& entry : fs::directory_iterator(sourceDir)) {
            fs::copy(entry.path(), target / entry.path().filename(),
                      fs::copy_options::overwrite_existing); // Files.copy()
        }
    }
    std::cout << "Backup created at " << target << "\n";
    return target;
}

} // namespace ccrm::service
