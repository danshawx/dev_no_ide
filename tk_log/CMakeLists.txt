target_sources(${ELF} PRIVATE
		   ${CMAKE_CURRENT_SOURCE_DIR}/SEGGER_RTT_printf.c
           ${CMAKE_CURRENT_SOURCE_DIR}/SEGGER_RTT.c
           ${CMAKE_CURRENT_SOURCE_DIR}/tk_log.c
)
