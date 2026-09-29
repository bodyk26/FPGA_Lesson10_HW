# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "I:\\Xilinx_Projects\\Lesson_10\\Vitis\\LED_Zynq\\platform\\ps7_cortexa9_0\\standalone_ps7_cortexa9_0\\bsp\\include\\sleep.h"
  "I:\\Xilinx_Projects\\Lesson_10\\Vitis\\LED_Zynq\\platform\\ps7_cortexa9_0\\standalone_ps7_cortexa9_0\\bsp\\include\\xiltimer.h"
  "I:\\Xilinx_Projects\\Lesson_10\\Vitis\\LED_Zynq\\platform\\ps7_cortexa9_0\\standalone_ps7_cortexa9_0\\bsp\\include\\xtimer_config.h"
  "I:\\Xilinx_Projects\\Lesson_10\\Vitis\\LED_Zynq\\platform\\ps7_cortexa9_0\\standalone_ps7_cortexa9_0\\bsp\\lib\\libxiltimer.a"
  )
endif()
