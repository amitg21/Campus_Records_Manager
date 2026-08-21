#include "ccrm/cli/CourseMenu.hpp"
#include "ccrm/domain/Course.hpp"
#include <iostream>
#include <limits>

namespace ccrm::cli {

void CourseMenu::run() {
    bool inMenu = true;
    while (inMenu) {
        std::cout << "\n-- Manage Courses --\n"
                     "1. List All Courses\n"
                     "2. Add Course\n"
                     "3. Search Courses (by department)\n"
                     "0. Back\n> ";
        int choice = 0;
        if (!(std::cin >> choice)) { inMenu = false; break; } // EOF: unwind this submenu
        switch (choice) {
            case 1: listAllFlow(); break;
            case 2: addCourseFlow(); break;
            case 3: searchByDepartmentFlow(); break;
            case 0: inMenu = false; break;
            default: std::cout << "Invalid option.\n";
        }
    }
}

void CourseMenu::listAllFlow() {
    const auto& courses = courseService_.all();
    if (courses.empty()) { std::cout << "No courses yet.\n"; return; }
    for (const auto& c : courses) std::cout << c->toString() << "\n";
}

void CourseMenu::addCourseFlow() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string dept, title, semesterStr;
    int number = 0, credits = 0;
    std::cout << "Department: "; std::getline(std::cin, dept);
    std::cout << "Course number: "; std::cin >> number;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Title: "; std::getline(std::cin, title);
    std::cout << "Credits: "; std::cin >> credits;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Semester (SPRING/SUMMER/FALL/WINTER): "; std::getline(std::cin, semesterStr);

    try {
        auto course = domain::Course::Builder()
            .setCode(domain::CourseCode(dept, number))
            .setTitle(title)
            .setCredits(credits)
            .setSemester(domain::semesterFromString(semesterStr))
            .setDepartment(dept)
            .build();
        courseService_.addCourse(std::move(course));
        std::cout << "Course added.\n";
    } catch (const std::exception& e) {
        std::cout << "Could not add course: " << e.what() << "\n";
    }
}

void CourseMenu::searchByDepartmentFlow() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string dept;
    std::cout << "Department: "; std::getline(std::cin, dept);
    auto results = courseService_.byDepartment(dept);
    if (results.empty()) { std::cout << "No matches.\n"; return; }
    for (const auto& c : results) std::cout << c->toString() << "\n";
}

} // namespace ccrm::cli
