
# Note: has to be defiend here as it needs the hal_conf header...
add_library(stm32_hal
	STATIC
		"${PROJECT_SOURCE_DIR}/external/stm32f7/Src/stm32f7xx_hal.c"
		"${PROJECT_SOURCE_DIR}/external/stm32f7/Src/stm32f7xx_hal_cortex.c"
		"${PROJECT_SOURCE_DIR}/external/stm32f7/Src/stm32f7xx_hal_gpio.c"
		"${PROJECT_SOURCE_DIR}/external/stm32f7/Src/stm32f7xx_hal_pwr.c"
		"${PROJECT_SOURCE_DIR}/external/stm32f7/Src/stm32f7xx_hal_pwr_ex.c"
		"${PROJECT_SOURCE_DIR}/external/stm32f7/Src/stm32f7xx_hal_rcc.c"
)
target_include_directories(stm32_hal
	PUBLIC
		"${PROJECT_SOURCE_DIR}/external/stm32f7/Inc"
		${CMAKE_CURRENT_LIST_DIR}
)
target_compile_definitions(stm32_hal
	PUBLIC
		# USE_FULL_LL_DRIVER
)
# todo: think of an alternative to INTERFACE here (these leak to other targets...)
target_compile_options(stm32_hal
	INTERFACE
		$<$<COMPILE_LANGUAGE:CXX>:-Wno-volatile>
		$<$<COMPILE_LANGUAGE:CXX>:-Wno-useless-cast>
		-Wno-unused-parameter
		$<$<COMPILE_LANGUAGE:CXX>:-Wno-old-style-cast>
		-Wno-pedantic
		$<$<COMPILE_LANGUAGE:CXX>:-Wno-sign-conversion>
)
target_link_libraries(stm32_hal
	PUBLIC
		stm32_cmsis
)


add_executable(01_gpio_hal
	main.cpp
)
target_include_directories(01_gpio_hal
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}
)
target_link_libraries(01_gpio_hal
	PRIVATE
		system
		bob_interface
		stm32_hal
)
set(LINKER_SCRIPTS
		${PROJECT_SOURCE_DIR}/linkerscripts/stm32f7/memory.ld
		${PROJECT_SOURCE_DIR}/linkerscripts/stm32f7/sections.ld
)
bob_firmware_image(01_gpio_hal)
