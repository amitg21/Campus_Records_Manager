#pragma once
#include <vector>
#include <memory>
#include "ccrm/domain/Student.hpp"
#include "ccrm/domain/Course.hpp"
#include "ccrm/domain/Enrollment.hpp"

namespace ccrm::config {

// Second Singleton: the in-memory "database" of the app.
// Uses shared_ptr rather than Java-style raw references so ownership is
// explicit and lifetime is managed automatically (RAII) instead of relying
// on garbage collection.
class DataStore {
public:
    static DataStore& instance() {
        static DataStore inst;
        return inst;
    }

    DataStore(const DataStore&) = delete;
    DataStore& operator=(const DataStore&) = delete;

    std::vector<std::shared_ptr<domain::Student>> students;
    std::vector<std::shared_ptr<domain::Course>> courses;
    std::vector<domain::Enrollment> enrollments;

private:
    DataStore() = default;
};

} // namespace ccrm::config
