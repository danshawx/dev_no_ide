# TK_LOG

This is TK_LOG version 1.0.0

TK_LOG is a debug print tool base [SEGGER_RTT](https://www.segger.com/products/debug-probes/j-link/technology/about-real-time-transfer/). It supports a wide range of CPUs and architectures that can use J-LINK. It provides four different levels printout and enable or disable timestamp.

## Requirements
J-LINK and J-LINK RTT Viewer

## Interface(tk_log_config.h)

### enable or disable debug print
* enable: uncomment macro of LOG_FUN_ENABLE
* disable: comment macro of LOG_FUN_ENABLE

### enable or disable timestamp
* enable: set log_timestamp_enabled 1
* disable: set log_timestamp_enabled 0

### api
- LOG_INF
- LOG_WARNING
- LOG_ERROR
- LOG_DEBUG
  
### check get systick funtion
use your get systick funtion to replace drv_systick

## Running





