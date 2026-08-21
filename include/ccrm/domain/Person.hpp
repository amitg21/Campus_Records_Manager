#pragma once
#include <string>

namespace ccrm::domain {

// Abstract base class -> demonstrates Abstraction + Encapsulation.
// Java's Person was an abstract class with an abstract getProfile().
// In C++ that's a pure virtual function, and we add a virtual destructor
// (Java doesn't need this because of the GC; C++ needs it so that
// `delete basePtr` on a polymorphic object cleans up correctly).
class Person {
public:
    Person(std::string id, std::string name, std::string email);
    virtual ~Person() = default;

    // Encapsulation: private data, public accessors.
    const std::string& id() const { return id_; }
    const std::string& name() const { return name_; }
    const std::string& email() const { return email_; }

    void setName(const std::string& name) { name_ = name; }
    void setEmail(const std::string& email) { email_ = email; }

    // Abstraction: subclasses must supply their own profile description.
    virtual std::string getProfile() const = 0;

    // Overridable, like Java's toString().
    virtual std::string toString() const;

private:
    std::string id_;
    std::string name_;
    std::string email_;
};

} // namespace ccrm::domain
