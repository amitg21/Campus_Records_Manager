#include "ccrm/domain/Semester.hpp"
#include <stdexcept>

namespace ccrm::domain {

std::string semesterToString(Semester s) {
    switch (s) {
        case Semester::SPRING: return "SPRING";
        case Semester::SUMMER: return "SUMMER";
        case Semester::FALL:   return "FALL";
        case Semester::WINTER: return "WINTER";
    }
    return "?";
}

Semester semesterFromString(const std::string& s) {
    if (s == "SPRING") return Semester::SPRING;
    if (s == "SUMMER") return Semester::SUMMER;
    if (s == "FALL")   return Semester::FALL;
    if (s == "WINTER") return Semester::WINTER;
    throw std::invalid_argument("Unknown semester: " + s);
}

} // namespace ccrm::domain
