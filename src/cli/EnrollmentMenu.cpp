#include "ccrm/cli/EnrollmentMenu.hpp"
#include "ccrm/exceptions/Exceptions.hpp"
#include <iostream>
#include <limits>

namespace ccrm::cli {

void EnrollmentMenu::run() {
    bool inMenu = true;
    while (inMenu) {
        std::cout << "\n-- Manage Enrollment & Grades --\n"
                     "1. Enroll Student in Course\n"
                     "2. Assign Grade\n"
                     "3. Compute GPA\n"
                     "0. Back\n> ";
        int choice = 0;
        if (!(std::cin >> choice)) { inMenu = false; break; } // EOF: unwind this submenu
        switch (choice) {
            case 1: enrollFlow(); break;
            case 2: assignGradeFlow(); break;
            case 3: gpaFlow(); break;
            case 0: inMenu = false; break;
            default: std::cout << "Invalid option.\n";
        }
    }
}

void EnrollmentMenu::enrollFlow() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string studentId, courseCode;
    std::cout << "Student ID: "; std::getline(std::cin, studentId);
    std::cout << "Course code: "; std::getline(std::cin, courseCode);

    // try / multi-catch equivalent to Java's custom-exception handling.
    try {
        enrollmentService_.enroll(studentId, courseCode);
        std::cout << "Enrolled.\n";
    } catch (const exceptions::DuplicateEnrollmentException& e) {
        std::cout << "Enrollment failed: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cout << "Unexpected error: " << e.what() << "\n";
    }
}

void EnrollmentMenu::assignGradeFlow() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string studentId, courseCode, gradeStr;
    std::cout << "Student ID: "; std::getline(std::cin, studentId);
    std::cout << "Course code: "; std::getline(std::cin, courseCode);
    std::cout << "Grade (S/A/B/C/D/E/F): "; std::getline(std::cin, gradeStr);

    domain::Grade grade;
    if (gradeStr == "S") grade = domain::Grade::S;
    else if (gradeStr == "A") grade = domain::Grade::A;
    else if (gradeStr == "B") grade = domain::Grade::B;
    else if (gradeStr == "C") grade = domain::Grade::C;
    else if (gradeStr == "D") grade = domain::Grade::D;
    else if (gradeStr == "E") grade = domain::Grade::E;
    else grade = domain::Grade::F;

    enrollmentService_.assignGrade(studentId, courseCode, grade);
    std::cout << "Grade recorded.\n";
}

void EnrollmentMenu::gpaFlow() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string studentId;
    std::cout << "Student ID: "; std::getline(std::cin, studentId);
    std::cout << "GPA: " << enrollmentService_.computeGpa(studentId) << "\n";
}

} // namespace ccrm::cli
