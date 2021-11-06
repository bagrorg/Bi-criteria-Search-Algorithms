cmake_minimum_required(VERSION 3.18)
project(search_algorithms)

find_package( Boost 1.40 COMPONENTS program_options REQUIRED )
include_directories( ${Boost_INCLUDE_DIR} )

include_directories(${CMAKE_HOME_DIRECTORY})

add_executable(main main.cpp Service/Measurements.cpp
                              Service/Measurements.hpp
                              Service/Options.hpp
                              Service/Options.cpp
                              Algorithm/Algorithm.hpp
                              Service/AlgorithmSet.hpp
                              Service/AlgorithmSet.cpp
                              Algorithm/DummyAlgorithm.hpp
                              Algorithm/DummyAlgorithm.cpp)

target_link_libraries(main LINK_PUBLIC ${Boost_LIBRARIES} )