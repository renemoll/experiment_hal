
add_library(system
	STATIC
		# reset_handler.s
		timeout.cpp
		vector_table.cpp
)
target_include_directories(system
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}
)
target_link_libraries(system
	PRIVATE
		bob_interface
		# stm32_hal
)
