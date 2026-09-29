# 2026-09-29T18:51:45.710778400
import vitis

client = vitis.create_client()
client.set_workspace(path="LED_Zynq")

platform = client.create_platform_component(name = "platform",hw_design = "$COMPONENT_LOCATION/../../../LED_PS/design_1_wrapper_vitis.xsa",os = "standalone",cpu = "ps7_cortexa9_0",domain_name = "standalone_ps7_cortexa9_0",compiler = "gcc")

platform = client.get_component(name="platform")
status = platform.build()

comp = client.create_app_component(name="app_component",platform = "$COMPONENT_LOCATION/../platform/export/platform/platform.xpfm",domain = "standalone_ps7_cortexa9_0")

comp = client.get_component(name="app_component")
status = comp.import_files(from_loc="", files=["I:\Xilinx_Projects\git clones\FPGA\lesson_10\Example\vitis\LED_AXI_GPIO_Zynq\app_component\src\main_combined.c"], is_skip_copy_sources = False)

status = platform.build()

comp = client.get_component(name="app_component")
comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

vitis.dispose()

vitis.dispose()

