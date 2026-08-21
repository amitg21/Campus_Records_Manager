#pragma once
#include "ccrm/domain/Enrollment.hpp"
#include "ccrm/domain/Grade.hpp"
#include <string>

namespace ccrm::service {

class EnrollmentService {
public:
    // Throws exceptions::DuplicateEnrollmentException if already enrolled.
    void enroll(const std::string& studentId, const std::string& courseCode);
    void assignGrade(const std::string& studentId, const std::string& courseCode, domain::Grade grade);

    double computeGpa(const std::string& studentId) const;
};

} // namespace ccrm::service
