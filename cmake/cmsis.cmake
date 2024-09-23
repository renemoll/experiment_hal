	
add_library(cmsis INTERFACE)
target_include_directories(cmsis
	INTERFACE
		"${CMAKE_SOURCE_DIR}/external/cmsis6/CMSIS/Core/Include"
)
