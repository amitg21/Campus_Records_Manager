#pragma once
#include "ccrm/service/StudentService.hpp"

namespace ccrm::cli {

class StudentMenu {
public:
    void run();

private:
    void addStudentFlow();
    void listAllFlow();
    void searchFlow();

    service::StudentService studentService_;
};

} // namespace ccrm::cli
