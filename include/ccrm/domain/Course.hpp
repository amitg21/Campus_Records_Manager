#pragma once
#include <string>
#include <optional>
#include "ccrm/domain/CourseCode.hpp"
#include "ccrm/domain/Semester.hpp"

namespace ccrm::domain {

// Course itself stays a plain value class; construction is funneled
// through the nested Builder below (Design Pattern: Builder).
class Course {
public:
    class Builder; // fwd-declare the nested builder

    const CourseCode& code() const { return code_; }
    const std::string& title() const { return title_; }
    int credits() const { return credits_; }
    Semester semester() const { return semester_; }
    const std::string& department() const { return department_; }

    std::string toString() const;

private:
    // Only Builder can construct a Course, enforcing validated creation.
    Course(CourseCode code, std::string title, int credits,
           Semester semester, std::string department)
        : code_(std::move(code)), title_(std::move(title)), credits_(credits),
          semester_(semester), department_(std::move(department)) {}

    CourseCode code_;
    std::string title_;
    int credits_;
    Semester semester_;
    std::string department_;
};

// Static nested class, same role as Java's `Course.Builder`.
class Course::Builder {
public:
    Builder& setCode(CourseCode code) { code_.emplace(std::move(code)); return *this; }
    Builder& setTitle(std::string title) { title_ = std::move(title); return *this; }
    Builder& setCredits(int credits) { credits_ = credits; return *this; }
    Builder& setSemester(Semester semester) { semester_ = semester; return *this; }
    Builder& setDepartment(std::string department) { department_ = std::move(department); return *this; }

    // Java used `assert` here (enabled via -ea). We use <cassert>'s assert(),
    // which is likewise only active in non-NDEBUG (debug) builds.
    Course build() const;

private:
    std::optional<CourseCode> code_;
    std::string title_;
    int credits_ = 0;
    Semester semester_ = Semester::FALL;
    std::string department_;
};

} // namespace ccrm::domain
