#include "ccrm/service/EnrollmentService.hpp"
#include "ccrm/config/DataStore.hpp"
#include "ccrm/exceptions/Exceptions.hpp"
#include <algorithm>
#include <numeric>

namespace ccrm::service {

using config::DataStore;
using exceptions::DuplicateEnrollmentException;

void EnrollmentService::enroll(const std::string& studentId, const std::string& courseCode) {
    auto& enrollments = DataStore::instance().enrollments;
    bool already = std::any_of(enrollments.begin(), enrollments.end(), [&](const auto& e) {
        return e.studentId() == studentId && e.courseCode() == courseCode;
    });
    if (already) {
        throw DuplicateEnrollmentException(studentId, courseCode); // custom exception
    }
    enrollments.emplace_back(studentId, courseCode);
}

void EnrollmentService::assignGrade(const std::string& studentId, const std::string& courseCode,
                                     domain::Grade grade) {
    auto& enrollments = DataStore::instance().enrollments;
    auto it = std::find_if(enrollments.begin(), enrollments.end(), [&](auto& e) {
        return e.studentId() == studentId && e.courseCode() == courseCode;
    });
    if (it != enrollments.end()) {
        it->assignGrade(grade);
    }
}

double EnrollmentService::computeGpa(const std::string& studentId) const {
    const auto& enrollments = DataStore::instance().enrollments;
    const auto& courses = DataStore::instance().courses;

    double weightedSum = 0.0;
    int totalCredits = 0;

    for (const auto& e : enrollments) {
        if (e.studentId() != studentId || !e.hasGrade()) continue;
        auto courseIt = std::find_if(courses.begin(), courses.end(), [&](const auto& c) {
            return c->code().toString() == e.courseCode();
        });
        if (courseIt == courses.end()) continue;
        int credits = (*courseIt)->credits();
        weightedSum += domain::gradePoints(e.grade()) * credits;
        totalCredits += credits;
    }
    return totalCredits == 0 ? 0.0 : weightedSum / totalCredits;
}

} // namespace ccrm::service
