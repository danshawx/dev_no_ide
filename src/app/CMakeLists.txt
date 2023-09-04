# option(USE_TEST "Test option" OFF)

# if (USE_TEST)
#   target_compile_definitions(${ELF} PRIVATE "USE_TEST")
# endif()


target_sources(${ELF} PRIVATE
	       ${CMAKE_CURRENT_SOURCE_DIR}/led.c
	       ${CMAKE_CURRENT_SOURCE_DIR}/stm32g0xx_it.c
)
