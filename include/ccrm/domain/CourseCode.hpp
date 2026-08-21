#pragma once
#include <string>

namespace ccrm::domain {

// Immutable value type: every field is const and set only via the
// constructor's initializer list, mirroring Java's `final` fields.
class CourseCode {
public:
    CourseCode(std::string department, int number)
        : department_(std::move(department)), number_(number) {}

    const std::string& department() const { return department_; }
    int number() const { return number_; }

    std::string toString() const { return department_ + std::to_string(number_); }

    bool operator==(const CourseCode& other) const {
        return department_ == other.department_ && number_ == other.number_;
    }
    bool operator<(const CourseCode& other) const {
        if (department_ != other.department_) return department_ < other.department_;
        return number_ < other.number_;
    }

private:
    const std::string department_;
    const int number_;
};

} // namespace ccrm::domain
