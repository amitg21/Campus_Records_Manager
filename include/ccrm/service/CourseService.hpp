#pragma once
#include <memory>
#include <vector>
#include <optional>
#include <functional>
#include "ccrm/domain/Course.hpp"
#include "ccrm/interfaces/Interfaces.hpp"

namespace ccrm::service {

class CourseService : public interfaces::Searchable<std::shared_ptr<domain::Course>> {
public:
    std::shared_ptr<domain::Course> addCourse(domain::Course course);

    std::optional<std::shared_ptr<domain::Course>> findByCode(const std::string& code) const;
    const std::vector<std::shared_ptr<domain::Course>>& all() const;

    std::vector<std::shared_ptr<domain::Course>> search(const std::string& query) const override;

    // Functional interfaces & lambdas: filter by an arbitrary predicate,
    // mirroring Java's `CourseService` using lambda predicates in .filter().
    std::vector<std::shared_ptr<domain::Course>> filter(
        const std::function<bool(const domain::Course&)>& predicate) const;

    std::vector<std::shared_ptr<domain::Course>> byDepartment(const std::string& dept) const;
};

} // namespace ccrm::service
