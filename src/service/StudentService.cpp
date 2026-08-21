#include "ccrm/service/StudentService.hpp"
#include "ccrm/config/DataStore.hpp"
#include <algorithm>
#include <iostream>

namespace ccrm::service {

using config::DataStore;

std::shared_ptr<domain::Student> StudentService::addStudent(
    const std::string& id, const std::string& name, const std::string& email,
    const std::string& regNo, std::chrono::year_month_day dob) {
    auto student = std::make_shared<domain::Student>(id, name, email, regNo, dob);
    DataStore::instance().students.push_back(student);
    return student;
}

std::optional<std::shared_ptr<domain::Student>> StudentService::findById(const std::string& id) const {
    const auto& students = DataStore::instance().students;
    auto it = std::find_if(students.begin(), students.end(),
                            [&](const auto& s) { return s->id() == id; });
    if (it == students.end()) return std::nullopt;
    return *it;
}

const std::vector<std::shared_ptr<domain::Student>>& StudentService::all() const {
    return DataStore::instance().students;
}

std::vector<std::shared_ptr<domain::Student>> StudentService::search(const std::string& query) const {
    std::vector<std::shared_ptr<domain::Student>> results;
    for (const auto& s : DataStore::instance().students) { // enhanced-for
        if (s->name().find(query) != std::string::npos ||
            s->regNo().find(query) != std::string::npos) {
            results.push_back(s);
        }
    }
    return results;
}

void StudentService::listAll() const {
    for (const auto& s : DataStore::instance().students) { // enhanced-for
        std::cout << s->getProfile() << "\n";
    }
}

} // namespace ccrm::service
