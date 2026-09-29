#CLK
set_property IOSTANDARD LVDS [get_ports diff_clock_rtl_0_clk_p] 
set_property PACKAGE_PIN H9 [get_ports diff_clock_rtl_0_clk_p]

#rst
set_property IOSTANDARD LVCMOS33 [get_ports reset_rtl_0] 
set_property PACKAGE_PIN AD18 [get_ports reset_rtl_0]

#LEDS
set_property -dict {PACKAGE_PIN AJ14 IOSTANDARD LVCMOS33} [get_ports {LED_tri_io[0]}]
set_property -dict {PACKAGE_PIN AJ13 IOSTANDARD LVCMOS33} [get_ports {LED_tri_io[1]}]
set_property -dict {PACKAGE_PIN AE13 IOSTANDARD LVCMOS33} [get_ports {LED_tri_io[2]}]
set_property -dict {PACKAGE_PIN AF13 IOSTANDARD LVCMOS33} [get_ports {LED_tri_io[3]}]

#BUTTONS

#BTN_STARTPAUSE
set_property -dict {PACKAGE_PIN AD13 IOSTANDARD LVCMOS33} [get_ports {BTN_tri_io[0]}] 
#BTN_SPEEDUP
set_property -dict {PACKAGE_PIN AB12 IOSTANDARD LVCMOS33} [get_ports {BTN_tri_io[1]}] 
#BTN_SLOWDOWN
set_property -dict {PACKAGE_PIN AC12 IOSTANDARD LVCMOS33} [get_ports {BTN_tri_io[2]}]
#BTN_DIR 
set_property -dict {PACKAGE_PIN AB17 IOSTANDARD LVCMOS33} [get_ports {BTN_tri_io[3]}] 