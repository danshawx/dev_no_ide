#ifndef __TK_LOG_CONFIG_H__
#define __TK_LOG_CONFIG_H__

#include "ignore.h"

#define LOG_FUN_ENABLE


#ifdef LOG_FUN_ENABLE
#include "SEGGER_RTT.h"
#include "tk_log.h"

#define LOG_LEVEL_OFF      0
#define LOG_LEVEL_ERROR    1
#define LOG_LEVEL_WARNING  2
#define LOG_LEVEL_INFO     3
#define LOG_LEVEL_DEBUG    4

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_DEBUG
#endif

int log_timestamp_enabled(int level);

#define log_timestamp_enabled(x) 1

#define CONFIG_LOG_TERMINAL_INDEX   0

#if LOG_LEVEL >= LOG_LEVEL_ERROR
// #define LOG_ERROR(...)  SEGGER_RTT_printf(CONFIG_LOG_TERMINAL_INDEX, RTT_CTRL_TEXT_RED __VA_ARGS__)
#define LOG_ERROR_TIMESTAMP(tag, fmt, ...) SEGGER_RTT_printf(CONFIG_LOG_TERMINAL_INDEX, "[%s] " fmt, tag, ##__VA_ARGS__)
#define LOG_ERROR(...)                                                                \
{                                                                                     \
    if (log_timestamp_enabled(LOG_LEVEL_ERROR))                                       \
    {                                                                                 \
        time_to_timestamp();                                                          \
        LOG_DEBUG_TIMESTAMP(timestaptemp, RTT_CTRL_TEXT_RED __VA_ARGS__);             \
    }                                                                                 \
    else                                                                              \
    {                                                                                 \
        SEGGER_RTT_printf(CONFIG_LOG_TERMINAL_INDEX,  RTT_CTRL_TEXT_RED __VA_ARGS__); \
    }                                                                                 \
}
#else
#define LOG_ERROR(...) IGNORE(__VA_ARGS__)
#endif

#if LOG_LEVEL >= LOG_LEVEL_WARNING
#define LOG_WARNING_TIMESTAMP(tag, fmt, ...) SEGGER_RTT_printf(CONFIG_LOG_TERMINAL_INDEX, "[%s] " fmt, tag, ##__VA_ARGS__)
#define LOG_WARNING(...)                                                                \
{                                                                                     \
    if (log_timestamp_enabled(LOG_LEVEL_WARNING))                                       \
    {                                                                                 \
        time_to_timestamp();                                                          \
        LOG_DEBUG_TIMESTAMP(timestaptemp, RTT_CTRL_TEXT_GREEN __VA_ARGS__);             \
    }                                                                                 \
    else                                                                              \
    {                                                                                 \
        SEGGER_RTT_printf(CONFIG_LOG_TERMINAL_INDEX,  RTT_CTRL_TEXT_GREEN __VA_ARGS__); \
    }                                                                                 \
}
#else
#define LOG_WARNING(...) IGNORE(__VA_ARGS__)
#endif

#if LOG_LEVEL >= LOG_LEVEL_INFO
// #define LOG_INF(...) SEGGER_RTT_printf(CONFIG_LOG_TERMINAL_INDEX,  RTT_CTRL_RESET __VA_ARGS__)
#define LOG_INF_TIMESTAMP(tag, fmt, ...) SEGGER_RTT_printf(CONFIG_LOG_TERMINAL_INDEX, "[%s] " fmt, tag, ##__VA_ARGS__)
#define LOG_INF(...)                                                     \
{                                                                        \
    if (log_timestamp_enabled(LOG_LEVEL_INFO))                           \
    {                                                                    \
        time_to_timestamp();                                             \
        LOG_DEBUG_TIMESTAMP(timestaptemp, RTT_CTRL_RESET __VA_ARGS__);   \
    }                                                                              \
    else                                                                           \
    {                                                                              \
        SEGGER_RTT_printf(CONFIG_LOG_TERMINAL_INDEX,  RTT_CTRL_RESET __VA_ARGS__); \
    }                                                 \
}
#else
#define LOG_INF(...) IGNORE(__VA_ARGS__)
#endif

#if LOG_LEVEL >= LOG_LEVEL_DEBUG
//#define LOG_DEBUG(...)    SEGGER_RTT_printf(CONFIG_LOG_TERMINAL_INDEX, "[ERR] " ,##__VA_ARGS__)
#define LOG_DEBUG_TIMESTAMP(tag, fmt, ...)    SEGGER_RTT_printf(CONFIG_LOG_TERMINAL_INDEX, "[%s] " fmt, tag, ##__VA_ARGS__)
#define LOG_DEBUG(...)                               \
{                                                    \
    if (log_timestamp_enabled(LOG_LEVEL_DEBUG))      \
    {                                                \
        time_to_timestamp();                         \
        LOG_DEBUG_TIMESTAMP(timestaptemp, RTT_CTRL_RESET __VA_ARGS__);   \
    }                                                \
    else                                             \
    {                                                \
        SEGGER_RTT_printf(CONFIG_LOG_TERMINAL_INDEX,  RTT_CTRL_RESET __VA_ARGS__);\
    }                                                 \
}
#else
#define LOG_DEBUG(...) IGNORE(__VA_ARGS__)
#endif

// #define LOG_INF(...)    SEGGER_RTT_printf(CONFIG_LOG_TERMINAL_INDEX,  RTT_CTRL_RESET __VA_ARGS__)
// #define LOG_ERROR(...)    SEGGER_RTT_printf(CONFIG_LOG_TERMINAL_INDEX, RTT_CTRL_TEXT_RED __VA_ARGS__)

#else
#define LOG_INF(...)    IGNORE(__VA_ARGS__)
#define LOG_WARNING(...) IGNORE(__VA_ARGS__)
#define LOG_ERROR(...)  IGNORE(__VA_ARGS__)
#define LOG_DEBUG(...)  IGNORE(__VA_ARGS__)

#endif

#endif

