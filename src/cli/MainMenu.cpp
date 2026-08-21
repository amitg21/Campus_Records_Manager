#include "ccrm/cli/MainMenu.hpp"
#include "ccrm/cli/StudentMenu.hpp"
#include "ccrm/cli/CourseMenu.hpp"
#include "ccrm/cli/EnrollmentMenu.hpp"
#include "ccrm/service/FileService.hpp"
#include "ccrm/service/BackupService.hpp"
#include "ccrm/service/ReportService.hpp"
#include "ccrm/util/RecursiveFileUtils.hpp"
#include "ccrm/config/AppConfig.hpp"
#include <iostream>
#include <limits>

namespace ccrm::cli {

using config::AppConfig;

void MainMenu::loadInitialData() {
    service::FileService fileService;
    fileService.importStudents(AppConfig::instance().dataDirectory() / "students.csv");
    fileService.importCourses(AppConfig::instance().dataDirectory() / "courses.csv");
    std::cout << "Loaded initial data from " << AppConfig::instance().dataDirectory() << "\n";
}

void MainMenu::run() {
    loadInitialData();

    bool running = true;
    while (running) { // Java's `while` loop main menu
        std::cout << "\n===== Campus Course & Records Manager (C++ port) =====\n"
                     "1. Manage Students\n"
                     "2. Manage Courses\n"
                     "3. Manage Enrollment & Grades\n"
                     "4. Data Utilities\n"
                     "5. View Reports\n"
                     "0. Exit\n> ";
        int choice = 0;
        if (!(std::cin >> choice)) {
            running = false; // EOF or bad input on the stream: exit cleanly
            break;
        }

        // Java's enhanced `switch (choice) { case 1 -> ...; }`
        switch (choice) {
            case 1: { StudentMenu().run(); break; }
            case 2: { CourseMenu().run(); break; }
            case 3: { EnrollmentMenu().run(); break; }
            case 4: { dataUtilitiesFlow(); break; }
            case 5: { reportsFlow(); break; }
            case 0: { running = false; std::cout << "Goodbye.\n"; break; }
            default: std::cout << "Invalid option.\n";
        }
    }
}

void MainMenu::dataUtilitiesFlow() {
    bool inMenu = true;
    while (inMenu) {
        std::cout << "\n-- Data Utilities --\n"
                     "1. Import All Data\n"
                     "2. Export All Data\n"
                     "3. Create a Backup\n"
                     "4. Show Backup Directory Size\n"
                     "5. Run Control-Flow Demo (bitwise + labeled break)\n"
                     "0. Back\n> ";
        int choice = 0;
        if (!(std::cin >> choice)) { inMenu = false; break; } // EOF: unwind this submenu

        service::FileService fileService;
        service::BackupService backupService;

        switch (choice) {
            case 1:
                loadInitialData();
                break;
            case 2:
                fileService.exportStudents(config::AppConfig::instance().dataDirectory() / "students.csv");
                fileService.exportCourses(config::AppConfig::instance().dataDirectory() / "courses.csv");
                std::cout << "Data exported.\n";
                break;
            case 3:
                backupService.createBackup(config::AppConfig::instance().dataDirectory(),
                                            config::AppConfig::instance().backupDirectory());
                break;
            case 4: {
                auto size = util::RecursiveFileUtils::calculateDirectorySize(
                    config::AppConfig::instance().backupDirectory());
                std::cout << "Backup directory size: " << size << " bytes\n";
                break;
            }
            case 5:
                util::RecursiveFileUtils::demoControlFlow();
                break;
            case 0: inMenu = false; break;
            default: std::cout << "Invalid option.\n";
        }
    }
}

void MainMenu::reportsFlow() {
    service::ReportService reportService;
    reportService.printGpaDistribution();
    reportService.printStudentsRankedByGpa();
}

} // namespace ccrm::cli
