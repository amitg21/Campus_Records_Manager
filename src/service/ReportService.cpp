#include "ccrm/service/ReportService.hpp"
#include "ccrm/service/EnrollmentService.hpp"
#include "ccrm/config/DataStore.hpp"
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>

namespace ccrm::service {

using config::DataStore;

void ReportService::printGpaDistribution() const {
    // Java's Stream API `.collect(groupingBy(...))` becomes: compute each
    // student's GPA, then bucket the results into a std::map keyed by
    // rounded GPA band.
    EnrollmentService enrollmentService;
    std::map<int, int> bandCounts; // GPA band (0-10) -> count of students

    for (const auto& s : DataStore::instance().students) {
        double gpa = enrollmentService.computeGpa(s->id());
        int band = static_cast<int>(gpa); // groupingBy(Math.floor(gpa))
        ++bandCounts[band];
    }

    std::cout << "GPA distribution:\n";
    for (const auto& [band, count] : bandCounts) {
        std::cout << "  [" << band << "-" << band + 1 << "): " << count << " student(s)\n";
    }
}

void ReportService::printStudentsRankedByGpa() const {
    EnrollmentService enrollmentService;
    std::vector<std::pair<std::string, double>> ranked;
    for (const auto& s : DataStore::instance().students) {
        ranked.emplace_back(s->name(), enrollmentService.computeGpa(s->id()));
    }

    // Java: Collections.sort(list, new Comparator<>() { ... });  (anonymous inner class)
    // C++: pass a lambda directly to std::sort -- functionally the same idea,
    // just without needing a named/anonymous class to carry the comparison.
    std::sort(ranked.begin(), ranked.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });

    std::cout << "Students ranked by GPA:\n";
    for (const auto& [name, gpa] : ranked) {
        std::cout << "  " << name << ": " << gpa << "\n";
    }
}

} // namespace ccrm::service
