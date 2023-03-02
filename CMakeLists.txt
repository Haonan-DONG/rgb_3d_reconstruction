PROJECT(rgb_reconstruction)

CMAKE_MINIMUM_REQUIRED(VERSION 3.20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

FIND_PACKAGE(CUDA)
if(CUDA_FOUND)
		ENABLE_LANGUAGE(CUDA)
		# CUDA-11.x can not be compiled using C++14 standard on Windows
		string(REGEX MATCH "^[0-9]+" CUDA_MAJOR ${CMAKE_CUDA_COMPILER_VERSION})
		if(${CUDA_MAJOR} GREATER 10 AND CMAKE_CXX_COMPILER MATCHES "MSVC" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "19.29")
			message("Working around windows build failure with visual studio. Visual studio 16.10 introduced a compiler bug with compilng CUDA code with C++14. Set the cuda standard to 17 as a workaround.")
			set(CMAKE_CUDA_STANDARD 17)
		endif()
		if(NOT OpenMVS_MAX_CUDA_COMPATIBILITY)
			if(NOT DEFINED CMAKE_CUDA_ARCHITECTURES)
				SET(CMAKE_CUDA_ARCHITECTURES 75)
			endif()
		else()
			# Build for maximum compatibility
			# https://arnon.dk/matching-sm-architectures-arch-and-gencode-for-various-nvidia-cards/

			# Extract list of arch and gencodes
			EXECUTE_PROCESS(COMMAND "${CMAKE_CUDA_COMPILER}" --list-gpu-arch 
				OUTPUT_VARIABLE LIST_GPU_ARCH 
				ERROR_QUIET)
			STRING(REPLACE "\r" "" LIST_GPU_ARCH ${LIST_GPU_ARCH})
			STRING(REPLACE "\n" ";" LIST_GPU_ARCH ${LIST_GPU_ARCH})

			EXECUTE_PROCESS(COMMAND "${CMAKE_CUDA_COMPILER}" --list-gpu-code 
				OUTPUT_VARIABLE LIST_GPU_CODE 
				ERROR_QUIET)
			STRING(REPLACE "\r" "" LIST_GPU_CODE ${LIST_GPU_CODE})
			STRING(REPLACE "\n" ";" LIST_GPU_CODE ${LIST_GPU_CODE})

			LIST(GET LIST_GPU_CODE 0 TARGET_GPU_CODE)
			SET(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -arch=${TARGET_GPU_CODE}")

			SET(IDX 0)
			foreach(GPU_ARCH ${LIST_GPU_ARCH})
				LIST(GET LIST_GPU_CODE ${IDX} GPU_CODE)
				SET(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -gencode=arch=${GPU_ARCH},code=${GPU_CODE}")
				MATH(EXPR IDX "${IDX}+1")
			endforeach()
			MESSAGE("-- Set CUDA flags: " ${CMAKE_CUDA_FLAGS})
		endif()
		SET(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} --expt-relaxed-constexpr")
		INCLUDE_DIRECTORIES(${CUDA_INCLUDE_DIRS})
		LIST(APPEND OpenMVS_DEFINITIONS -D_USE_CUDA)
		SET(_USE_CUDA TRUE)
	else()
		SET(CUDA_CUDA_LIBRARY "")
		MESSAGE("-- Can't find CUDA. Continuing without it.")
	endif()


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

SET(EIGEN3_INCLUDE_DIR "/home/mvs18/envir/include/eigen3")
FIND_PACKAGE(Eigen3 REQUIRED)
if(EIGEN3_FOUND)
	LIST(APPEND OpenMVS_EXTRA_INCLUDES ${EIGEN3_INCLUDE_DIR})
	INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})
	LIST(APPEND OpenMVS_DEFINITIONS -D_USE_EIGEN)
	ADD_DEFINITIONS(${EIGEN3_DEFINITIONS})
	SET(_USE_EIGEN TRUE)
	MESSAGE(STATUS "Eigen ${EIGEN3_VERSION} found (include: ${EIGEN3_INCLUDE_DIR})")
endif()

# Link COLMAP
set(COLMAP_DIR "/third_party/colmap/install/share/colmap")

find_package(COLMAP REQUIRED)
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