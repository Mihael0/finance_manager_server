# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)

# Set the project name
project (finance_manager_server)

# Specify the include directory where libxl headers are located
include_directories("/home/mihael/opt/libxl-lin-4.5.1/include_cpp")

# Specify the library directory where libxl library files are located
link_directories("/home/mihael/opt/libxl-lin-4.5.1/lib64")

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
        app/main.cpp
        src/hello.cpp
        src/NetworkManager.cpp
)
# Find Boost package (you can specify components here if you want to limit which parts of Boost are found)
find_package(Boost REQUIRED COMPONENTS system)

## Find Boost package (you can specify components here if you want to limit which parts of Boost are found)
#find_package(Boost REQUIRED COMPONENTS bind)

# Add an executable with the above sources
add_executable(finance_manager_server ${SOURCES})

# Find Boost package with filesystem
find_package(Boost REQUIRED COMPONENTS system filesystem)

# Link Boost libraries (system and filesystem are needed)
target_link_libraries(finance_manager_server Boost::system Boost::filesystem)
# Link Boost libraries (system is needed for Boost.Asio)
target_link_libraries(finance_manager_server Boost::system)
## Link Boost libraries (bind is required by the TCP server)
#target_link_libraries(finance_manager_server Boost::bind)
# The file name is libxl.so. CMAKE when searching for SHARED libraries looks for lib<PassedArugment>.dl/so
# So, if you pass libxl it searches for liblibxl.
target_link_libraries(finance_manager_server xl)

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(finance_manager_server
        PRIVATE
        ${PROJECT_SOURCE_DIR}/inc
)
