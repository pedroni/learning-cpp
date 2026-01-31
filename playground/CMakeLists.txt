cmake_minimum_required(VERSION 4.2)

project(DvdScreensaver)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find raylib using pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(RAYLIB REQUIRED raylib)

# Get all cpp files
file(GLOB SOURCES "*.cpp"  "src/*.cpp")

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link raylib with explicit library paths
target_link_libraries(${PROJECT_NAME} ${RAYLIB_LDFLAGS})
target_include_directories(${PROJECT_NAME} PRIVATE ${RAYLIB_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src)
target_compile_options(${PROJECT_NAME} PRIVATE ${RAYLIB_CFLAGS_OTHER})
