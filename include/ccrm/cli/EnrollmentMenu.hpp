#pragma once
#include "ccrm/service/EnrollmentService.hpp"

namespace ccrm::cli {

class EnrollmentMenu {
public:
    void run();

private:
    void enrollFlow();
    void assignGradeFlow();
    void gpaFlow();

    service::EnrollmentService enrollmentService_;
};

} // namespace ccrm::cli
