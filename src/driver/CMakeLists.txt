target_sources(${ELF} PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/drv_sysclock.c
	    # ${CMAKE_CURRENT_SOURCE_DIR}/drv_usart.c
		${CMAKE_CURRENT_SOURCE_DIR}/drv_gpio.c
)
