
target_sources_ifdef(CONFIG_BOOTLOADER 
    ${ELF} 
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/test_boot.c
)
