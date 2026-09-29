# 2026-09-29T23:22:33.636095600
import vitis

client = vitis.create_client()
client.set_workspace(path="LED_Zynq")

platform = client.get_component(name="platform")
status = platform.build()

comp = client.get_component(name="app_component")
comp.build()

vitis.dispose()

vitis.dispose()

