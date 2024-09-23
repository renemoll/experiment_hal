
add_library(stm32_cmsis
	OBJECT
		"${CMAKE_SOURCE_DIR}/external/cmsis_device_f7/Source/Templates/gcc/startup_stm32f767xx.s"
		"${CMAKE_SOURCE_DIR}/external/cmsis_device_f7/Source/Templates/system_stm32f7xx.c"
)
target_include_directories(stm32_cmsis
	PUBLIC
		"${CMAKE_SOURCE_DIR}/external/cmsis_device_f7/Include"
)
target_link_libraries(stm32_cmsis
	PUBLIC
		cmsis
)


add_library(stm32_ll
	STATIC
		"${CMAKE_SOURCE_DIR}/external/stm32f7/Src/stm32f7xx_ll_gpio.c"
		"${CMAKE_SOURCE_DIR}/external/stm32f7/Src/stm32f7xx_ll_pwr.c"
		"${CMAKE_SOURCE_DIR}/external/stm32f7/Src/stm32f7xx_ll_rcc.c"
		"${CMAKE_SOURCE_DIR}/external/stm32f7/Src/stm32f7xx_ll_utils.c"
)
target_include_directories(stm32_ll
	PUBLIC
		"${CMAKE_SOURCE_DIR}/external/stm32f7/Inc"
)
target_compile_definitions(stm32_ll
	PUBLIC
		USE_FULL_LL_DRIVER
)
# todo: think of an alternative to INTERFACE here (these leak to other targets...)
target_compile_options(stm32_ll
	INTERFACE
		$<$<COMPILE_LANGUAGE:CXX>:-Wno-volatile>
		$<$<COMPILE_LANGUAGE:CXX>:-Wno-useless-cast>
		-Wno-unused-parameter
		$<$<COMPILE_LANGUAGE:CXX>:-Wno-old-style-cast>
		-Wno-pedantic
		$<$<COMPILE_LANGUAGE:CXX>:-Wno-sign-conversion>
)
target_link_libraries(stm32_ll
	PUBLIC
		stm32_cmsis
)
