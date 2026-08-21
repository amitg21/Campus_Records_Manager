cmake_minimum_required(VERSION 3.16)
project(CCRM_CPP CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug) # keep assert() active, like Java's -ea flag
endif()

file(GLOB_RECURSE CCRM_SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(ccrm ${CCRM_SOURCES})
target_include_directories(ccrm PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_compile_options(ccrm PRIVATE -Wall -Wextra)

# IDEs (CLion, Visual Studio, etc.) commonly run the built executable with
# its working directory set to the build folder (e.g. cmake-build-debug),
# not the project root -- so relative paths like "data/students.csv" won't
# resolve unless data/ lives next to the .exe too. Copy it there on every
# build, and make sure backups/ exists, so the app works no matter where
# the IDE launches it from.
add_custom_command(TARGET ccrm POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/data" "$<TARGET_FILE_DIR:ccrm>/data"
    COMMAND ${CMAKE_COMMAND} -E make_directory
            "$<TARGET_FILE_DIR:ccrm>/backups"
    COMMENT "Copying data/ and creating backups/ next to the built executable"
)
