#include "ccrm/service/CourseService.hpp"
#include "ccrm/config/DataStore.hpp"
#include <algorithm>

namespace ccrm::service {

using config::DataStore;

std::shared_ptr<domain::Course> CourseService::addCourse(domain::Course course) {
    auto ptr = std::make_shared<domain::Course>(std::move(course));
    DataStore::instance().courses.push_back(ptr);
    return ptr;
}

std::optional<std::shared_ptr<domain::Course>> CourseService::findByCode(const std::string& code) const {
    const auto& courses = DataStore::instance().courses;
    auto it = std::find_if(courses.begin(), courses.end(),
                            [&](const auto& c) { return c->code().toString() == code; });
    if (it == courses.end()) return std::nullopt;
    return *it;
}

const std::vector<std::shared_ptr<domain::Course>>& CourseService::all() const {
    return DataStore::instance().courses;
}

std::vector<std::shared_ptr<domain::Course>> CourseService::search(const std::string& query) const {
    return filter([&](const domain::Course& c) {
        return c.title().find(query) != std::string::npos ||
               c.code().toString().find(query) != std::string::npos;
    });
}

std::vector<std::shared_ptr<domain::Course>> CourseService::filter(
    const std::function<bool(const domain::Course&)>& predicate) const {
    std::vector<std::shared_ptr<domain::Course>> results;
    std::copy_if(DataStore::instance().courses.begin(), DataStore::instance().courses.end(),
                 std::back_inserter(results),
                 [&](const auto& c) { return predicate(*c); });
    return results;
}

std::vector<std::shared_ptr<domain::Course>> CourseService::byDepartment(const std::string& dept) const {
    // Lambda predicate, same idea as the Java version's `.filter(c -> ...)`.
    return filter([&](const domain::Course& c) { return c.department() == dept; });
}

} // namespace ccrm::service
