# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 17)

# Set the project name
project (finance_manager_server)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
        app/main.cpp
        src/hello.cpp
)
# Find Boost package (you can specify components here if you want to limit which parts of Boost are found)
find_package(Boost REQUIRED COMPONENTS system)

# Add an executable with the above sources
add_executable(finance_manager_server ${SOURCES})

# Link Boost libraries (system is needed for Boost.Asio)
target_link_libraries(finance_manager_server Boost::system)

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(finance_manager_server
        PRIVATE
        ${PROJECT_SOURCE_DIR}/inc
)
