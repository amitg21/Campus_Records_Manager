#include "ccrm/domain/Grade.hpp"

namespace ccrm::domain {

double gradePoints(Grade g) {
    switch (g) {
        case Grade::S: return 10.0;
        case Grade::A: return 9.0;
        case Grade::B: return 8.0;
        case Grade::C: return 7.0;
        case Grade::D: return 6.0;
        case Grade::E: return 5.0;
        case Grade::F: return 0.0;
    }
    return 0.0;
}

std::string gradeToString(Grade g) {
    switch (g) {
        case Grade::S: return "S";
        case Grade::A: return "A";
        case Grade::B: return "B";
        case Grade::C: return "C";
        case Grade::D: return "D";
        case Grade::E: return "E";
        case Grade::F: return "F";
    }
    return "?";
}

Grade gradeFromMarks(double marks) {
    if (marks >= 95) return Grade::S;
    if (marks >= 85) return Grade::A;
    if (marks >= 75) return Grade::B;
    if (marks >= 65) return Grade::C;
    if (marks >= 55) return Grade::D;
    if (marks >= 40) return Grade::E;
    return Grade::F;
}

} // namespace ccrm::domain
