#pragma once
#include <stdexcept>
#include <string>

namespace ccrm::exceptions {

// Base for all CCRM-specific exceptions, mirroring a common Java pattern
// of a project-level checked/unchecked exception base class.
class CcrmException : public std::runtime_error {
public:
    explicit CcrmException(const std::string& message) : std::runtime_error(message) {}
};

class DuplicateEnrollmentException : public CcrmException {
public:
    DuplicateEnrollmentException(const std::string& studentId, const std::string& courseCode)
        : CcrmException("Student '" + studentId + "' is already enrolled in course '" +
                         courseCode + "'") {}
};

class StudentNotFoundException : public CcrmException {
public:
    explicit StudentNotFoundException(const std::string& id)
        : CcrmException("No student found with id '" + id + "'") {}
};

class CourseNotFoundException : public CcrmException {
public:
    explicit CourseNotFoundException(const std::string& code)
        : CcrmException("No course found with code '" + code + "'") {}
};

} // namespace ccrm::exceptions
