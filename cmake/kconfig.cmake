
set(KCONFIG_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/Kconfig)
set(DOTCONFIG ${CMAKE_CURRENT_SOURCE_DIR}/build/config_out.config)
set(AUTOCONF_H ${CMAKE_CURRENT_SOURCE_DIR}/build/header.h)
set(PARSED_KCONFIG_SOURCES_TXT ${CMAKE_CURRENT_SOURCE_DIR}/build/kconfig_out.txt)
set(input_configs ${CMAKE_CURRENT_SOURCE_DIR}/prj.conf)

execute_process(
    COMMAND ${PYTHON_EXECUTABLE}
    # SHIELD_AS_LIST=${SHIELD_AS_LIST_ESCAPED_COMMAND}
    # ${PYTHON_EXECUTABLE}
    ${CMAKE_CURRENT_SOURCE_DIR}/scripts/kconfig/kconfig.py
    # --zephyr-base=${ZEPHYR_BASE}
    ${input_configs_are_handwritten}
    ${KCONFIG_ROOT}
    ${DOTCONFIG}
    ${AUTOCONF_H}
    ${PARSED_KCONFIG_SOURCES_TXT}
    ${input_configs}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    # The working directory is set to the app dir such that the user
    # can use relative paths in CONF_FILE, e.g. CONF_FILE=nrf5.conf
    RESULT_VARIABLE ret
    )
  if(NOT "${ret}" STREQUAL "0")
    message(FATAL_ERROR "command failed with return code: ${ret}")
  endif()

set_ifndef(KCONFIG_NAMESPACE "CONFIG")

import_kconfig(${KCONFIG_NAMESPACE} ${DOTCONFIG})

#   file(STRINGS ${PARSED_KCONFIG_SOURCES_TXT} PARSED_KCONFIG_SOURCES_LIST)
