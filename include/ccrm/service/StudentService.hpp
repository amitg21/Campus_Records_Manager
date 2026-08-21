#pragma once
#include <memory>
#include <vector>
#include <optional>
#include "ccrm/domain/Student.hpp"
#include "ccrm/interfaces/Interfaces.hpp"

namespace ccrm::service {

class StudentService : public interfaces::Searchable<std::shared_ptr<domain::Student>> {
public:
    std::shared_ptr<domain::Student> addStudent(
        const std::string& id, const std::string& name, const std::string& email,
        const std::string& regNo, std::chrono::year_month_day dob);

    std::optional<std::shared_ptr<domain::Student>> findById(const std::string& id) const;
    const std::vector<std::shared_ptr<domain::Student>>& all() const;

    // Searchable<T> implementation: substring match against name or regNo.
    std::vector<std::shared_ptr<domain::Student>> search(const std::string& query) const override;

    void listAll() const; // enhanced-for equivalent (range-based for)
};

} // namespace ccrm::service
