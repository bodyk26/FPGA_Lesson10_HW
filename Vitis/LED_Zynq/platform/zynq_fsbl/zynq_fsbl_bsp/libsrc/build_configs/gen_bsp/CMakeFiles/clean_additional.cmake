# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "I:\\Xilinx_Projects\\Lesson_10\\Vitis\\LED_Zynq\\platform\\zynq_fsbl\\zynq_fsbl_bsp\\include\\diskio.h"
  "I:\\Xilinx_Projects\\Lesson_10\\Vitis\\LED_Zynq\\platform\\zynq_fsbl\\zynq_fsbl_bsp\\include\\ff.h"
  "I:\\Xilinx_Projects\\Lesson_10\\Vitis\\LED_Zynq\\platform\\zynq_fsbl\\zynq_fsbl_bsp\\include\\ffconf.h"
  "I:\\Xilinx_Projects\\Lesson_10\\Vitis\\LED_Zynq\\platform\\zynq_fsbl\\zynq_fsbl_bsp\\include\\sleep.h"
  "I:\\Xilinx_Projects\\Lesson_10\\Vitis\\LED_Zynq\\platform\\zynq_fsbl\\zynq_fsbl_bsp\\include\\xilffs.h"
  "I:\\Xilinx_Projects\\Lesson_10\\Vitis\\LED_Zynq\\platform\\zynq_fsbl\\zynq_fsbl_bsp\\include\\xilffs_config.h"
  "I:\\Xilinx_Projects\\Lesson_10\\Vitis\\LED_Zynq\\platform\\zynq_fsbl\\zynq_fsbl_bsp\\include\\xilrsa.h"
  "I:\\Xilinx_Projects\\Lesson_10\\Vitis\\LED_Zynq\\platform\\zynq_fsbl\\zynq_fsbl_bsp\\include\\xiltimer.h"
  "I:\\Xilinx_Projects\\Lesson_10\\Vitis\\LED_Zynq\\platform\\zynq_fsbl\\zynq_fsbl_bsp\\include\\xtimer_config.h"
  "I:\\Xilinx_Projects\\Lesson_10\\Vitis\\LED_Zynq\\platform\\zynq_fsbl\\zynq_fsbl_bsp\\lib\\libxilffs.a"
  "I:\\Xilinx_Projects\\Lesson_10\\Vitis\\LED_Zynq\\platform\\zynq_fsbl\\zynq_fsbl_bsp\\lib\\libxilrsa.a"
  "I:\\Xilinx_Projects\\Lesson_10\\Vitis\\LED_Zynq\\platform\\zynq_fsbl\\zynq_fsbl_bsp\\lib\\libxiltimer.a"
  )
endif()
