
add_executable(02_gpio_ll
	main.cpp
)
target_link_libraries(02_gpio_ll
	PRIVATE
		system
		bob_interface
		stm32_ll
)
set(LINKER_SCRIPTS
		${PROJECT_SOURCE_DIR}/linkerscripts/stm32f7/memory.ld
		${PROJECT_SOURCE_DIR}/linkerscripts/stm32f7/sections.ld
)
bob_firmware_image(02_gpio_ll)
