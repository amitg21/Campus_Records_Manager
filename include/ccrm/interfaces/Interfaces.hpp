#pragma once
#include <string>
#include <vector>

namespace ccrm::interfaces {

// Searchable<T>: Java's interface with a generic search method becomes a
// C++ abstract base class template with a pure virtual function.
template <typename T>
class Searchable {
public:
    virtual ~Searchable() = default;
    virtual std::vector<T> search(const std::string& query) const = 0;
};

// Loggable / Archivable: two independent abstract interfaces.
class Loggable {
public:
    virtual ~Loggable() = default;
    virtual void log(const std::string& message) const = 0;
};

class Archivable {
public:
    virtual ~Archivable() = default;
    virtual void archive() const = 0;
};

// --- Diamond problem demo -------------------------------------------------
// In Java, a class implementing both Loggable and Archivable never hits a
// diamond, because Java interfaces can't share state and default-method
// conflicts must be resolved explicitly by the implementing class.
//
// C++ *can* form a real diamond: if both Loggable and Archivable derived
// from a common base with shared data, a class inheriting both would get
// two copies of that base unless the inheritance is `virtual`. We
// demonstrate that here with a shared `Nameable` base.
class Nameable {
public:
    virtual ~Nameable() = default;
    std::string label;
};

// Without `virtual` inheritance, LoggableEntity and ArchivableEntity would
// each carry their own Nameable subobject, and a class inheriting both
// would be ambiguous (the actual "diamond problem"). Virtual inheritance
// collapses them back into a single shared subobject.
class LoggableEntity : public virtual Nameable, public Loggable {
public:
    void log(const std::string& message) const override;
};

class ArchivableEntity : public virtual Nameable, public Archivable {
public:
    void archive() const override;
};

// This class is "forced" to deal with the diamond: because both parents
// virtually inherit Nameable, there's exactly one `label` member here,
// and both log() and archive() are inherited without ambiguity.
class LoggedArchivableRecord : public LoggableEntity, public ArchivableEntity {
public:
    explicit LoggedArchivableRecord(std::string name) { label = std::move(name); }
};

} // namespace ccrm::interfaces
