cmake_minimum_required(VERSION 3.0)
project(demo)

# include extension command file
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/extensions.cmake)
# include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/exdefinition.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/kconfig.cmake)

set(ELF ${PROJECT_NAME}.elf)

enable_language(ASM)
set(STARTUP_FILE "startup_stm32g474retx.s")

add_executable(${ELF} "")

target_sources(${ELF}
  PRIVATE
      src/main.c
      ${STARTUP_FILE}
  )

add_subdirectory(stm32g4_ll)
add_subdirectory(src/app)
add_subdirectory(src/driver)
add_subdirectory(src/kernel)

add_subdirectory_ifdef(CONFIG_BOOTLOADER ${CMAKE_CURRENT_SOURCE_DIR}/src/tk_boot)
add_subdirectory_ifdef(CONFIG_TK_LOG ${CMAKE_CURRENT_SOURCE_DIR}/src/tk_log)

# add_executable(${ELF} ${STARTUP_FILE}
#   src/main.c
#   src/system_stm32g4xx.c)
  
# target_include_directories(${ELF} PUBLIC inc)

target_include_directories(${ELF} 
  PUBLIC
  src 
  src/app
  src/driver
  src/kernel
  srec/tool_chain
  stm32g4_ll/inc)

target_include_directories_ifdef(CONFIG_BOOTLOADER
  ${ELF} 
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/tk_boot
)

target_include_directories_ifdef(CONFIG_BOOT_F1
  ${ELF} 
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/tk_boot/boot_f1
)

target_include_directories_ifdef(CONFIG_BOOT_F2
  ${ELF} 
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/tk_boot/boot_f2
)

target_include_directories_ifdef(CONFIG_TK_LOG
  ${ELF} 
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/tk_log
)

target_link_libraries(${ELF} ll )

add_custom_command(
  TARGET ${ELF} POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -O ihex "${ELF}" "${PROJECT_NAME}.hex"
  COMMAND ${CMAKE_OBJCOPY} -O binary -S -g "${ELF}" "${PROJECT_NAME}.bin"
)


set_target_properties(
  ${ELF}
  PROPERTIES
  LINK_FLAGS
  "-T${PROJECT_SOURCE_DIR}/STM32G474RETX_FLASH.ld \
   -mthumb -mcpu=cortex-m4 \
   -Wl,--gc-sections \
   -Wl,--no-warn-rwx-segments \
   -Wl,-Map=${PROJECT_NAME}.map")

target_compile_options(${ELF} PUBLIC
  -Wall 
  -g 
  -std=gnu99 
  -Os
  -mthumb
  -mcpu=cortex-m4
  -mfloat-abi=soft
  -mlittle-endian
  -ffunction-sections 
  -fdata-sections
  -Werror 
  -Wstrict-prototypes 
  -Warray-bounds 
  -fno-strict-aliasing 
  -Wno-unused-const-variable 
  -specs=nano.specs 
  -specs=nosys.specs
  )

  # --no-warn-rwx-segments

file(COPY
  openocd.cfg
  DESTINATION
  ${CMAKE_BINARY_DIR})
