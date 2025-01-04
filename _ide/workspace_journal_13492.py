# 2025-01-04T14:28:42.448065200
import vitis

client = vitis.create_client()
client.set_workspace(path="Zynq-7007S-Pan-Tompkins")

platform = client.get_component(name="Zynq-7007S-Pan-Tompkins")
status = platform.build()

comp = client.get_component(name="Zynq-7007S-Pan-Tompkins-App")
comp.build()

client.delete_component(name="Zynq-7007S-Pan-Tompkins-App")

comp = client.create_app_component(name="Zynq-7007S-Pan-Tompkins_App",platform = "$COMPONENT_LOCATION/../Zynq-7007S-Pan-Tompkins/export/Zynq-7007S-Pan-Tompkins/Zynq-7007S-Pan-Tompkins.xpfm",domain = "standalone_ps7_cortexa9_0")

status = platform.build()

comp = client.get_component(name="Zynq-7007S-Pan-Tompkins_App")
comp.build()

client.delete_component(name="Zynq-7007S-Pan-Tompkins_App")

comp = client.create_app_component(name="Zynq-7007S-Pan-Tompkins_App",platform = "$COMPONENT_LOCATION/../Zynq-7007S-Pan-Tompkins/export/Zynq-7007S-Pan-Tompkins/Zynq-7007S-Pan-Tompkins.xpfm",domain = "standalone_ps7_cortexa9_0",template = "hello_world")

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = comp.clean()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

vitis.dispose()

