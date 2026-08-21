#pragma once
#include "ccrm/service/CourseService.hpp"

namespace ccrm::cli {

class CourseMenu {
public:
    void run();

private:
    void listAllFlow();
    void addCourseFlow();
    void searchByDepartmentFlow();

    service::CourseService courseService_;
};

} // namespace ccrm::cli
