#pragma once
#include "ccrm/domain/Grade.hpp"

namespace ccrm::service {

class ReportService {
public:
    // Java: courses.stream().map(...).collect(groupingBy(...))
    // C++: build the equivalent with STL algorithms + std::map, or with
    // C++20 ranges (see the .cpp for both, commented).
    void printGpaDistribution() const;

    // Anonymous inner class comparator -> a C++ lambda passed to std::sort.
    void printStudentsRankedByGpa() const;
};

} // namespace ccrm::service
