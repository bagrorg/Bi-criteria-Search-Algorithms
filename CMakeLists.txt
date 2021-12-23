cmake_minimum_required(VERSION 3.16)
project(search_algorithms)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
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
                              Algorithm/DummyAlgorithm.cpp
                              Service/Graph.hpp
                              Service/Graph.cpp
                              Service/Node.hpp
                              Service/Node.cpp
                              Containers/Closed.hpp
                              Containers/Open.hpp
                              Containers/MapClosed.hpp
                              Containers/MapClosed.cpp
                              Containers/MapSetOpen.hpp
                              Containers/MapSetOpen.cpp
                              Service/PairHash.hpp
                              Algorithm/PPA.hpp
                              Algorithm/PPA.cpp
                              Service/PPF.hpp
                              Service/PPF.cpp
                              Containers/PPFOpen.hpp
                              Containers/SimplePPFOpen.cpp
                              Containers/SimplePPFOpen.hpp
                              Service/AlgorithmState.cpp
                              Service/AlgorithmState.hpp
                              Algorithm/BOA.hpp
                              Algorithm/BOA.cpp
                              Service/BOANode.hpp
                              Service/BOANode.cpp
                              Service/HeuristicFunction.hpp
                              Service/HeuristicFunction.cpp)

target_link_libraries(main LINK_PUBLIC ${Boost_LIBRARIES} )