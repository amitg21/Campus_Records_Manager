#pragma once
#include <filesystem>
#include <string>
#include <vector>

namespace ccrm::service {

class FileService {
public:
    // Java: Files.lines(path) streamed, and try-with-resources for the writer.
    // C++: std::ifstream/std::ofstream; RAII closes the file automatically
    // when the stream goes out of scope, so no explicit "try-with-resources"
    // construct is needed at all.
    void importStudents(const std::filesystem::path& csvPath);
    void importCourses(const std::filesystem::path& csvPath);

    void exportStudents(const std::filesystem::path& csvPath) const;
    void exportCourses(const std::filesystem::path& csvPath) const;

private:
    static std::vector<std::string> splitCsvLine(const std::string& line);
};

} // namespace ccrm::service
