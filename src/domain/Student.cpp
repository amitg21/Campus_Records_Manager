#include "ccrm/domain/Student.hpp"
#include <algorithm>
#include <sstream>

namespace ccrm::domain {

Student::Student(std::string id, std::string name, std::string email,
                  std::string regNo, std::chrono::year_month_day dob)
    : Person(std::move(id), std::move(name), std::move(email)), // == super(name, email)
      regNo_(std::move(regNo)), dob_(dob) {}

void Student::enroll(const std::string& courseCode) {
    enrolledCourses_.push_back(courseCode);
}

void Student::unenroll(const std::string& courseCode) {
    enrolledCourses_.erase(
        std::remove(enrolledCourses_.begin(), enrolledCourses_.end(), courseCode),
        enrolledCourses_.end());
}

std::string Student::getProfile() const {
    std::ostringstream oss;
    oss << "Student " << name() << " (" << regNo_ << ") <" << email() << ">"
        << " - " << enrolledCourses_.size() << " course(s) enrolled";
    return oss.str();
}

std::string Student::toString() const {
    return "Student{id=" + id() + ", regNo=" + regNo_ + ", name=" + name() + "}";
}

} // namespace ccrm::domain
