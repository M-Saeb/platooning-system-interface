cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(cmake_and_cuda LANGUAGES CXX CUDA)
 

# Configuring VCPKG
set(CMAKE_TOOLCHAIN_FILE "C:\\Users\\Moham\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file")

include(CTest)
 
# add_library(particles STATIC
#   randomize.cpp
#   randomize.h
#   particle.cu
#   particle.h
#   v3.cu
#   v3.h
#   )
 
add_executable(
    my_executable
    main.cu
)

# Request that particles be built with -std=c++11
# As this is a public compile feature anything that links to 
# particles will also build with -std=c++11
target_compile_features(my_executable PUBLIC cxx_std_11)
 
# We need to explicitly state that we need all CUDA files in the 
# particle library to be built with -dc as the member functions 
# could be called by other libraries and executables
set_target_properties( my_executable
                       PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
 
# add_executable(particle_test test.cu)
 
set_property(TARGET my_executable 
             PROPERTY CUDA_SEPARABLE_COMPILATION ON)
# target_link_libraries(my_executable PRIVATE particles)
 
if(APPLE)
  # We need to add the path to the driver (libcuda.dylib) as an rpath, 
  # so that the static cuda runtime can find it at runtime.
  set_property(TARGET my_executable
               PROPERTY
               BUILD_RPATH ${CMAKE_CUDA_IMPLICIT_LINK_DIRECTORIES})
endif()


# # spdlog
# find_package(spdlog CONFIG REQUIRED)
# target_link_libraries(my_executable PRIVATE spdlog::spdlog)
