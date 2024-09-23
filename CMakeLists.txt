cmake_minimum_required(VERSION 3.21.0)
cmake_policy(VERSION 3.21)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

#
# [BOB] This is needed right here to download the toolchain files
#       before they are used within a project.
#
list(PREPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(Bob REQUIRED)

project(libhal
	VERSION
		0.1.0
	LANGUAGES
		CXX C ASM
)

if (PROJECT_IS_TOP_LEVEL)
	set(CMAKE_C_STANDARD 17)
	set(CMAKE_C_STANDARD_REQUIRED On)
	set(CMAKE_C_EXTENSIONS Off)
	set(CMAKE_CXX_STANDARD 20)
	set(CMAKE_CXX_STANDARD_REQUIRED On)
	set(CMAKE_CXX_EXTENSIONS Off)

	#
	# [BOB] Configure the build
	#
	# Todo: only set BOB_USE_RTTI for specific targets
	#
	set(BOB_USE_RTTI Off)
	set(BOB_USER_VERSION_HEADER "${CMAKE_CURRENT_LIST_DIR}/cmake/version.in.h")
	include(bob)

	add_compile_definitions(STM32F767xx)
endif()

if (CMAKE_CROSSCOMPILING)
	include(cmsis)
	include(stm32)
endif()

#
# Build the project
#
if (PROJECT_IS_TOP_LEVEL)
	add_subdirectory(experiments)
endif()
