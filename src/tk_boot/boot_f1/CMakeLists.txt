target_sources_ifdef(CONFIG_BOOT_F1 
    ${ELF} 
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/test_boot_f1.c
)
