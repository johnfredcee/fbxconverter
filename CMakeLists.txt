cmake_minimum_required(VERSION 3.4.1)

project(FbxConverter)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

message(STATUS "CMAKE_SYSTEM_INFO_FILE = ${CMAKE_SYSTEM_INFO_FILE}")
message(STATUS "CMAKE_SYSTEM_NAME = ${CMAKE_SYSTEM_NAME}")
message(STATUS "CMAKE_SYSTEM_PROCESSOR = ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "CMAKE_SYSTEM = ${CMAKE_SYSTEM}")
message(STATUS "CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_BINARY_DIR = ${CMAKE_BINARY_DIR}")

find_package(wxWidgets REQUIRED core base adv propgrid)
include(${wxWidgets_USE_FILE})

set(FBXSDK_ROOT "" CACHE PATH "Root of FBX SDK on disk")

foreach (FBXSDK_VERSION "2019.2")
  find_package(FBX)
  if (FBXSDK_FOUND)
    break()
  endif()
endforeach(FBXSDK_VERSION)
if (NOT FBXSDK_FOUND)
  message(FATAL_ERROR
    "Can't find FBX SDK."
 )
endif()

set( default_cmake_args
	 -G "Visual Studio 15 2017 Win64"
	 -B${BUILD_FOLDER_SUFFIX} "-H." )


file(
    GLOB
    fbxconverter_source
    ${CMAKE_SOURCE_DIR}/*.cpp
)

add_executable(
    FbxConverter WIN32 
	${fbxconverter_source}
)

target_include_directories(
    FbxConverter
    PUBLIC
    ${CMAKE_SOURCE_DIR}/generated
	${FBXSDK_INCLUDE_DIR}
)
set (CMAKE_CXX_STANDARD 14)

set(CONFIGURATION_SUFFIX "/$(Configuration)")

# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_CRT_SECURE_NO_WARNINGS")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -D_CRT_SECURE_NO_WARNINGS")


# this will suffice for now; don't really care about 32-bit
set(LIBXML2_INCLUDE_DIRS ${FBXSDK_INCLUDE_DIR})
set(LIBXML2_LIBRARIES ${FBXSDK_ROOT}/lib/vs2017/x64/release/libxml2-md.lib)
set(LIBXML2_LIBRARIES_DEBUG ${FBXSDK_ROOT}/lib/vs2017/x64/debug/libxml2-md.lib)
if (NOT LIBXML2_INCLUDE_DIRS OR NOT LIBXML2_LIBRARIES)
	message(FATAL_ERROR "Cannot find libxml2.lib in the expected location.")
endif()

set(ZLIB_INCLUDE_DIRS ${FBXSDK_INCLUDE_DIR})
set(ZLIB_LIBRARIES ${FBXSDK_ROOT}/lib/vs2017/x64/release/zlib-md.lib)
set(ZLIB_LIBRARIES_DEBUG ${FBXSDK_ROOT}/lib/vs2017/x64/debug/zlib-md.lib)
if (NOT ZLIB_LIBRARIES)
	message(FATAL_ERROR "Cannot find zlib.lib in the expected location.")
endif()

set(
	third_party_libs
	${wxWidgets_LIBRARIES}
	debug ${LIBXML2_LIBRARIES_DEBUG}
	optimized ${LIBXML2_LIBRARIES}
	debug ${ZLIB_LIBRARIES_DEBUG}
	optimized ${ZLIB_LIBRARIES}
	winmm.lib
	imm32.lib
	version.lib
)

target_link_libraries(
    FbxConverter
    debug ${FBXSDK_LIBRARY_DEBUG}
    optimized ${FBXSDK_LIBRARY}
    ${third_party_libs}
)

link_directories(
	FbxConverter
)

set_target_properties(
    FbxConverter
    PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY
    "$(OutDir)"
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(PREDEFINED_TARGETS_FOLDER "CustomTargets")