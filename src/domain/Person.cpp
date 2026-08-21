#include "ccrm/domain/Person.hpp"

namespace ccrm::domain {

Person::Person(std::string id, std::string name, std::string email)
    : id_(std::move(id)), name_(std::move(name)), email_(std::move(email)) {}

std::string Person::toString() const {
    return "Person{id=" + id_ + ", name=" + name_ + ", email=" + email_ + "}";
}

} // namespace ccrm::domain
