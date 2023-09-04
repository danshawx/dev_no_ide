
cmake_minimum_required(VERSION 3.0)
project(bms_demo)

# include extension command file
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/extensions.cmake)
# include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/exdefinition.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/kconfig.cmake)

set(ELF ${PROJECT_NAME}.elf)
enable_language(ASM)
set(STARTUP_FILE "startup_stm32g0b1vetx.s")

add_executable(${ELF} "")

target_sources(${ELF}
  PRIVATE
      src/main.c
      ${STARTUP_FILE}
  )

# target_sources_ifdef()

add_subdirectory(stm32g0-ll)
add_subdirectory(src/app)
add_subdirectory(src/service)
add_subdirectory(src/driver)
# add_subdirectory(src/tk_boot)

# if (CONFIG_BOOT_BOOT_F1)
# add_subdirectory(src/tk_boot/boot_f1)
# endif()

# if (CONFIG_BOOT_BOOT_F2)
# add_subdirectory(src/tk_boot/boot_f2)
# endif()
# add_subdirectory(src/tk_log)

add_subdirectory_ifdef(CONFIG_BOOTLOADER src/tk_boot)
add_subdirectory_ifdef(CONFIG_BOOT_F1 src/tk_boot/boot_f1)
add_subdirectory_ifdef(CONFIG_BOOT_F2 src/tk_boot/boot_f2)
add_subdirectory_ifdef(CONFIG_TK_LOG src/tk_log)


# add_executable(${ELF} ${STARTUP_FILE}
#   src/main.c)

# target_include_directories(${ELF} 
#   PUBLIC 
#     inc)



target_include_directories(${ELF} 
  PUBLIC 
  src
  stm32g0-ll
  "${PROJECT_SOURCE_DIR}/src/driver"
  "${PROJECT_SOURCE_DIR}/src/app"
  "${PROJECT_SOURCE_DIR}/src/tk_boot"
  "${PROJECT_SOURCE_DIR}/src/tk_boot/boot_f1"
  "${PROJECT_SOURCE_DIR}/src/tk_log"
  # src/app
  "${PROJECT_SOURCE_DIR}/src/service"
  "${PROJECT_SOURCE_DIR}/build"
  )

  target_include_directories(ll
  PUBLIC 
  src
  "${PROJECT_SOURCE_DIR}/src/app"
  # "${PROJECT_SOURCE_DIR}/driver"
  # "${PROJECT_SOURCE_DIR}/tk_boot"
  # "${PROJECT_SOURCE_DIR}/tk_log"
  src/service)
  
  # target_include_directories(ll PRIVATE 
  # ${CMAKE_CURRENT_SOURCE_DIR}
  # )

# include_directories(src
#   stm32g0-ll
#   src/app
#   src/service)

target_link_libraries(${ELF} PUBLIC ll)

add_custom_command(
  TARGET ${ELF} POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -O ihex "${ELF}" "${PROJECT_NAME}.hex"
  COMMAND ${CMAKE_OBJCOPY} -O binary -S -g "${ELF}" "${PROJECT_NAME}.bin"
)

set_target_properties(
  ${ELF}
  PROPERTIES
  LINK_FLAGS
  "-T${PROJECT_SOURCE_DIR}/STM32G0B1VETX_FLASH.ld \
   -mthumb -mcpu=cortex-m0plus \
   -Wl,--gc-sections \
   -static --specs=nano.specs -mfloat-abi=soft \
   -Wl,-Map=${PROJECT_NAME}.map")

target_compile_options(${ELF} PUBLIC
  -Wall 
  -g 
  -std=gnu99 
  -Os
  -mthumb
  -mcpu=cortex-m0plus
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
  -specs=nosys.specs)

file(COPY
  openocd.cfg
  DESTINATION
  ${CMAKE_BINARY_DIR})
