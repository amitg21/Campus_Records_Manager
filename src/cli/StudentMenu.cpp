#include "ccrm/cli/StudentMenu.hpp"
#include <iostream>
#include <limits>

namespace ccrm::cli {

void StudentMenu::run() {
    bool inMenu = true;
    while (inMenu) { // Java's `while` loop menu
        std::cout << "\n-- Manage Students --\n"
                     "1. List All Students\n"
                     "2. Add Student\n"
                     "3. Search Students\n"
                     "0. Back\n> ";
        int choice = 0;
        if (!(std::cin >> choice)) { inMenu = false; break; } // EOF: unwind this submenu

        // Java's enhanced switch (`case 1 -> ...`) maps to a plain switch here.
        switch (choice) {
            case 1: listAllFlow(); break;
            case 2: addStudentFlow(); break;
            case 3: searchFlow(); break;
            case 0: inMenu = false; break;
            default: std::cout << "Invalid option.\n";
        }
    }
}

void StudentMenu::listAllFlow() {
    // Enhanced-for demonstration, same as Java's StudentMenu listing loop.
    const auto& students = studentService_.all();
    if (students.empty()) { std::cout << "No students yet.\n"; return; }
    for (const auto& s : students) {
        std::cout << s->toString() << "\n";
    }
}

void StudentMenu::addStudentFlow() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string id, name, email, regNo, dob;
    std::cout << "ID: "; std::getline(std::cin, id);
    std::cout << "Name: "; std::getline(std::cin, name);
    std::cout << "Email: "; std::getline(std::cin, email);
    std::cout << "Reg No: "; std::getline(std::cin, regNo);
    std::cout << "DOB (YYYY-MM-DD): "; std::getline(std::cin, dob);

    try {
        int y = std::stoi(dob.substr(0, 4));
        unsigned m = static_cast<unsigned>(std::stoi(dob.substr(5, 2)));
        unsigned d = static_cast<unsigned>(std::stoi(dob.substr(8, 2)));
        studentService_.addStudent(id, name, email, regNo,
            std::chrono::year_month_day{std::chrono::year{y}, std::chrono::month{m}, std::chrono::day{d}});
        std::cout << "Student added.\n";
    } catch (const std::exception& e) {
        std::cout << "Could not add student: " << e.what() << "\n";
    }
}

void StudentMenu::searchFlow() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string query;
    std::cout << "Search query: "; std::getline(std::cin, query);
    auto results = studentService_.search(query);
    if (results.empty()) { std::cout << "No matches.\n"; return; }
    for (const auto& s : results) std::cout << s->toString() << "\n";
}

} // namespace ccrm::cli
