#pragma once
#include <string>

namespace ccrm::domain {

enum class Semester { SPRING, SUMMER, FALL, WINTER };

std::string semesterToString(Semester s);
Semester semesterFromString(const std::string& s);

} // namespace ccrm::domain
