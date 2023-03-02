PROJECT(rgb_reconstruction)

CMAKE_MINIMUM_REQUIRED(VERSION 3.20)

find_package(COLMAP REQUIRED)
# or to require a specific version: find_package(COLMAP 3.4 REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

FIND_PACKAGE(OpenCV REQUIRED)
if(OpenCV_FOUND)
	LIST(APPEND OpenMVS_EXTRA_INCLUDES ${OpenCV_INCLUDE_DIRS})
	INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
	ADD_DEFINITIONS(${OpenCV_DEFINITIONS})
	SET(_USE_OPENCV TRUE)
	MESSAGE(STATUS "OpenCV ${OpenCV_VERSION} found (include: ${OpenCV_INCLUDE_DIRS})")
else()
	MESSAGE("-- Can't find OpenCV. Please specify OpenCV directory using OpenCV_DIR variable")
endif()

# Link COLMAP
set(COLMAP_DIR "/third_party/colmap/install/share/colmap")
include_directories(${COLMAP_INCLUDE_DIRS})
link_directories(${COLMAP_LINK_DIRS})

# Link OpenMVS
set(OpenMVS_DIR "/third_party/openMVS/install/")
find_package(OpenMVS)
if(OpenMVS_FOUND)
    message("Found OpenMVS")
	include_directories(${OpenMVS_INCLUDE_DIRS})
	add_definitions(${OpenMVS_DEFINITIONS})
endif()

add_executable(exe src/exe/exe.cc)
target_link_libraries(exe ${COLMAP_LIBRARIES} OpenMVS::MVS)