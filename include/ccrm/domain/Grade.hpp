#pragma once
#include <string>
#include <array>

namespace ccrm::domain {

// Java's `enum Grade { S(10), A(9), ... }` gives each constant a field.
// A plain C++11 `enum class` can't carry data or methods by itself, so we
// pair it with a small lookup table + free functions. (An alternative
// idiomatic approach would be a class with static const instances; this
// version keeps the enum's compactness while still attaching data.)
enum class Grade {
    S, A, B, C, D, E, F
};

constexpr std::array<Grade, 7> kAllGrades = {
    Grade::S, Grade::A, Grade::B, Grade::C, Grade::D, Grade::E, Grade::F
};

double gradePoints(Grade g);      // GPA points, e.g. S=10.0, A=9.0 ... F=0.0
std::string gradeToString(Grade g);
Grade gradeFromMarks(double marks); // convenience: marks -> letter grade

} // namespace ccrm::domain
