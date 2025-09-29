cmake_minimum_required(VERSION 3.16)
project(BlackHoleSFML)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML REQUIRED sfml-all)

add_executable(BlackHoleSFML src/main.cpp)

target_include_directories(BlackHoleSFML PRIVATE ${SFML_INCLUDE_DIRS})
target_link_directories(BlackHoleSFML PRIVATE ${SFML_LIBRARY_DIRS})

target_link_libraries(BlackHoleSFML PRIVATE ${SFML_LIBRARIES})

target_compile_options(BlackHoleSFML PRIVATE ${SFML_CFLAGS_OTHER})

if(WIN32)
    add_custom_command(
        TARGET BlackHoleSFML
        COMMENT "Copy SFML binaries"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
            $<TARGET_FILE_DIR:sfml-system>
            $<TARGET_FILE_DIR:BlackHoleSFML>
        VERBATIM)
endif()