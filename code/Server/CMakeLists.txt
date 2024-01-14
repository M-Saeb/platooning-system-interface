# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# Configuring VCPKG
set(CMAKE_TOOLCHAIN_FILE "C:\\Users\\Moham\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file")

project(MyProject)

add_executable(
    my_executable main.cpp
    common/point.cpp
    common/vehicles/vehicle.cpp
    common/vehicles/MasterVehicle.cpp
    common/vehicles/SlaveVehicle.cpp
    common/trip/trip.cpp
    common/server/server.cpp
)

# spdlog
find_package(spdlog CONFIG REQUIRED)
target_link_libraries(my_executable PRIVATE spdlog::spdlog)

# Find and link against pthread
find_package(Threads REQUIRED)
target_link_libraries(my_executable PRIVATE Threads::Threads)
