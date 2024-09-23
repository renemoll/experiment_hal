
add_executable(05_oop_template
	main.cpp
)

target_link_libraries(05_oop_template
	PRIVATE
		system
		bob_interface
		stm32_hal
)