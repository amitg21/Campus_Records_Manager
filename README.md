# CCRM (C++ port)

A C++20 port of [amitg21/CCRM](https://github.com/amitg21/CCRM) — a console-based
Campus Course & Records Manager. The original is Java SE; this is a restructured
C++ rewrite that keeps the same features and design patterns but uses idiomatic
modern C++ instead of literal line-by-line translation.

## Build & run

```bash
g++ -std=c++20 -Wall -Wextra -Iinclude $(find src -name '*.cpp') -o ccrm
./ccrm
```

Or with CMake:

```bash
mkdir build && cd build
cmake ..
cmake --build .
./ccrm
```

Run from the project root so the relative `data/` and `backups/` paths resolve.
Debug builds (the CMake default) keep `assert()` active, the equivalent of Java's
`-ea` flag for the `Course::Builder` credit-range check.

### Running from an IDE (CLion, Visual Studio, etc.)

IDEs typically launch the built `.exe` with its working directory set to the
build folder (e.g. `cmake-build-debug`), not the project root — so a relative
path like `data\students.csv` won't resolve and you'll see
`Could not open "data\students.csv" (skipping student import)`.

`CMakeLists.txt` handles this automatically: every build copies `data/` next
to the compiled executable and creates `backups/` there too, so it works
regardless of where the IDE runs it from. If you already built once before
this was added, just re-run Build (or reconfigure the CMake project) so the
new post-build copy step executes.

## What changed vs. the Java version, and why

| Concept | Java | C++ (this port) |
|---|---|---|
| Packages | `edu.ccrm.cli`, etc. | Namespaces: `ccrm::cli`, `ccrm::domain`, ... |
| Abstraction | abstract class + abstract method | abstract base class + pure virtual function (`= 0`), with a `virtual` destructor since C++ has no GC |
| Interfaces | `interface Searchable<T>` | abstract class template with pure virtual methods |
| Diamond problem | avoided by design (Java interfaces can't multiply-inherit state) | *demonstrated on purpose* — `Nameable` is shared via `virtual` inheritance so `LoggedArchivableRecord` (which inherits both `LoggableEntity` and `ArchivableEntity`) gets one subobject, not two. See `interfaces/Interfaces.hpp`. |
| Object lifetime | garbage collected | RAII: `std::shared_ptr` for shared domain objects, stack/value types elsewhere; destructors run deterministically |
| try-with-resources | needed for file handles | not needed — `std::ifstream`/`std::ofstream` close automatically via RAII when they go out of scope |
| Builder pattern | `Course.Builder` static nested class | `Course::Builder` nested class; `CourseCode` is immutable (`const` fields) so the builder holds it in a `std::optional` and uses `emplace()` rather than assignment |
| Singleton | private constructor + static field | Meyers singleton: function-local `static` (thread-safe, lazy, C++11-guaranteed) |
| Streams / `groupingBy` | `Stream.collect(groupingBy(...))` | manual loop into a `std::map`, or STL `<algorithm>` (`std::copy_if`, `std::sort` with a lambda instead of an anonymous `Comparator`) |
| `NIO.2` (`Path`, `Files`) | `java.nio.file` | `std::filesystem` (`create_directories`, `copy`, `directory_iterator`) |
| `LocalDateTime` | `java.time` | `std::chrono` (+ `<ctime>` for the backup-folder timestamp) |
| Labeled `break` | `outer: for(...) { break outer; }` | no direct equivalent; uses `goto` to a label after the loop nest (the one broadly-accepted legitimate C++ use of `goto`) |
| `line.split(",")` | built into `String` | no built-in split; small helper using `std::stringstream` + `std::getline` |
| Enum with fields | `enum Grade { S(10), A(9), ... }` | `enum class Grade` + free functions/lookup table, since C++11 `enum class` can't carry data directly |

## Layout

```
include/ccrm/       headers, mirrors src/
src/domain/          Person, Student, Course(+Builder), CourseCode, Grade, Semester, Enrollment
src/interfaces/       Searchable<T>, Loggable, Archivable, diamond-inheritance demo
src/exceptions/       (header-only) custom exception hierarchy
src/service/          StudentService, CourseService, EnrollmentService, ReportService, FileService, BackupService
src/util/             RecursiveFileUtils (recursion, bitwise ops, goto-based labeled break)
src/config/           AppConfig, DataStore (singletons)
src/cli/              MainMenu, StudentMenu, CourseMenu, EnrollmentMenu
src/main.cpp
data/                 sample students.csv / courses.csv
backups/              created at runtime by the backup feature
```

## Known simplifications

- CSV parsing is intentionally simple (no quoted-field/embedded-comma support) —
  matching the original's `line.split(",")` approach.
- The Java version's `RecursiveFileUtils.calculateDirectorySize` is ported directly;
  symlink cycles aren't specially handled (same as the original).
- Menu input parsing uses `std::cin >>` / `std::getline`, which is intentionally
  minimal — no input-validation library, matching the console-app scope of the original.
