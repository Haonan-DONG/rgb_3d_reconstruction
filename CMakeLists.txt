PROJECT(rgb_reconstruction)

CMAKE_MINIMUM_REQUIRED(VERSION 3.20)

find_package(COLMAP REQUIRED)
# or to require a specific version: find_package(COLMAP 3.4 REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(COLMAP_DIR "/third_party/colmap/install/share/colmap")

include_directories(${COLMAP_INCLUDE_DIRS})
link_directories(${COLMAP_LINK_DIRS})

add_executable(exe src/exe/exe.cc)
target_link_libraries(exe ${COLMAP_LIBRARIES})