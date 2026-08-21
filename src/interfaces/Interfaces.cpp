#include "ccrm/interfaces/Interfaces.hpp"
#include <iostream>

namespace ccrm::interfaces {

void LoggableEntity::log(const std::string& message) const {
    std::cout << "[LOG] " << label << ": " << message << "\n";
}

void ArchivableEntity::archive() const {
    std::cout << "[ARCHIVE] " << label << " has been archived.\n";
}

} // namespace ccrm::interfaces
