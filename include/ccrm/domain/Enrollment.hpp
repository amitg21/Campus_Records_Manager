#pragma once
#include <string>
#include <optional>
#include "ccrm/domain/Grade.hpp"

namespace ccrm::domain {

class Enrollment {
public:
    Enrollment(std::string studentId, std::string courseCode)
        : studentId_(std::move(studentId)), courseCode_(std::move(courseCode)) {}

    const std::string& studentId() const { return studentId_; }
    const std::string& courseCode() const { return courseCode_; }

    bool hasGrade() const { return grade_.has_value(); }
    Grade grade() const { return *grade_; }
    void assignGrade(Grade g) { grade_ = g; }

private:
    std::string studentId_;
    std::string courseCode_;
    std::optional<Grade> grade_; // Java would likely use a nullable Grade field
};

} // namespace ccrm::domain
