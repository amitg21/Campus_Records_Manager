#pragma once
#include "ccrm/domain/Person.hpp"
#include <chrono>
#include <vector>
#include <string>

namespace ccrm::domain {

// Inheritance: Student "extends" Person by public inheritance.
class Student : public Person {
public:
    Student(std::string id, std::string name, std::string email,
            std::string regNo, std::chrono::year_month_day dob);

    // Constructor in inheritance: calls Person's constructor,
    // the equivalent of Java's `super(name, email)`.
    // (See .cpp: Student(...) : Person(id, name, email) { ... })

    const std::string& regNo() const { return regNo_; }
    const std::chrono::year_month_day& dob() const { return dob_; }

    void enroll(const std::string& courseCode);
    void unenroll(const std::string& courseCode);
    const std::vector<std::string>& enrolledCourseCodes() const { return enrolledCourses_; }

    // Overriding: Student supplies concrete versions of Person's
    // pure-virtual getProfile(), plus its own toString().
    std::string getProfile() const override;
    std::string toString() const override;

private:
    std::string regNo_;
    std::chrono::year_month_day dob_;
    std::vector<std::string> enrolledCourses_;
};

} // namespace ccrm::domain
