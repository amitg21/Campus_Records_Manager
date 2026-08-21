#include "ccrm/service/FileService.hpp"
#include "ccrm/config/DataStore.hpp"
#include "ccrm/domain/Course.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

namespace ccrm::service {

namespace fs = std::filesystem;
using config::DataStore;

// Java: line.split(","). C++ has no built-in split, so a small helper
// using std::stringstream + std::getline fills that one gap.
std::vector<std::string> FileService::splitCsvLine(const std::string& line) {
    std::vector<std::string> fields;
    std::stringstream ss(line);
    std::string field;
    while (std::getline(ss, field, ',')) {
        fields.push_back(field);
    }
    return fields;
}

static std::chrono::year_month_day parseDate(const std::string& iso) {
    // Expects YYYY-MM-DD.
    int y = std::stoi(iso.substr(0, 4));
    unsigned m = static_cast<unsigned>(std::stoi(iso.substr(5, 2)));
    unsigned d = static_cast<unsigned>(std::stoi(iso.substr(8, 2)));
    return std::chrono::year_month_day{std::chrono::year{y}, std::chrono::month{m}, std::chrono::day{d}};
}

static std::string formatDate(const std::chrono::year_month_day& ymd) {
    std::ostringstream oss;
    oss << static_cast<int>(ymd.year()) << "-"
        << (static_cast<unsigned>(ymd.month()) < 10 ? "0" : "") << static_cast<unsigned>(ymd.month()) << "-"
        << (static_cast<unsigned>(ymd.day()) < 10 ? "0" : "") << static_cast<unsigned>(ymd.day());
    return oss.str();
}

void FileService::importStudents(const fs::path& csvPath) {
    std::ifstream in(csvPath); // RAII: closes automatically at scope exit
    if (!in) {
        std::cerr << "Could not open " << csvPath << " (skipping student import)\n";
        return;
    }
    std::string line;
    while (std::getline(in, line)) { // Files.lines() streaming equivalent
        if (line.empty()) continue;
        auto f = splitCsvLine(line);
        if (f.size() < 5) continue;
        try {
            DataStore::instance().students.push_back(
                std::make_shared<domain::Student>(f[0], f[1], f[2], f[3], parseDate(f[4])));
        } catch (const std::exception& e) {
            std::cerr << "Skipping malformed student row: " << line << " (" << e.what() << ")\n";
        }
    }
}

void FileService::importCourses(const fs::path& csvPath) {
    std::ifstream in(csvPath);
    if (!in) {
        std::cerr << "Could not open " << csvPath << " (skipping course import)\n";
        return;
    }
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        auto f = splitCsvLine(line); // dept,number,title,credits,semester
        if (f.size() < 5) continue;
        try {
            auto course = domain::Course::Builder()
                .setCode(domain::CourseCode(f[0], std::stoi(f[1])))
                .setTitle(f[2])
                .setCredits(std::stoi(f[3]))
                .setSemester(domain::semesterFromString(f[4]))
                .setDepartment(f[0])
                .build();
            DataStore::instance().courses.push_back(std::make_shared<domain::Course>(std::move(course)));
        } catch (const std::exception& e) {
            std::cerr << "Skipping malformed course row: " << line << " (" << e.what() << ")\n";
        }
    }
}

void FileService::exportStudents(const fs::path& csvPath) const {
    std::ofstream out(csvPath);
    for (const auto& s : DataStore::instance().students) {
        out << s->id() << "," << s->name() << "," << s->email() << ","
            << s->regNo() << "," << formatDate(s->dob()) << "\n";
    }
}

void FileService::exportCourses(const fs::path& csvPath) const {
    std::ofstream out(csvPath);
    for (const auto& c : DataStore::instance().courses) {
        out << c->code().department() << "," << c->code().number() << ","
            << c->title() << "," << c->credits() << "," << semesterToString(c->semester()) << "\n";
    }
}

} // namespace ccrm::service
