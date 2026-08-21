#include "ccrm/domain/Course.hpp"
#include <cassert>
#include <sstream>

namespace ccrm::domain {

std::string Course::toString() const {
    std::ostringstream oss;
    oss << code_.toString() << " - " << title_
        << " (" << credits_ << " cr, " << semesterToString(semester_) << ")";
    return oss.str();
}

Course Course::Builder::build() const {
    assert(code_.has_value() && "Course code must be set");
    assert(credits_ > 0 && credits_ <= 6 && "Credits must be in range 1..6");
    return Course(*code_, title_, credits_, semester_, department_);
}

} // namespace ccrm::domain
