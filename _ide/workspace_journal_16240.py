# 2025-01-02T21:58:17.698963300
import vitis

client = vitis.create_client()
client.set_workspace(path="Zynq-7007S-Pan-Tompkins")

platform = client.create_platform_component(name = "Zynq-7007S-Pan-Tompkins",hw_design = "$COMPONENT_LOCATION/../design_PS_wrapper.xsa",os = "standalone",cpu = "ps7_cortexa9_0",domain_name = "standalone_ps7_cortexa9_0")

platform = client.get_component(name="Zynq-7007S-Pan-Tompkins")
domain = platform.get_domain(name="standalone_ps7_cortexa9_0")

status = domain.set_config(option = "os", param = "standalone_stdin", value = "ps7_coresight_comp_0")

status = domain.set_config(option = "os", param = "standalone_stdout", value = "ps7_coresight_comp_0")

status = platform.build()

comp = client.create_app_component(name="Zynq-7007S-Pan-Tompkins-App",platform = "$COMPONENT_LOCATION/../Zynq-7007S-Pan-Tompkins/export/Zynq-7007S-Pan-Tompkins/Zynq-7007S-Pan-Tompkins.xpfm",domain = "standalone_ps7_cortexa9_0")

status = platform.build()

comp = client.get_component(name="Zynq-7007S-Pan-Tompkins-App")
comp.build()

status = comp.clean()

status = platform.build()

comp.build()

client.delete_component(name="Zynq-7007S-Pan-Tompkins-App")

comp = client.create_app_component(name="Zynq-7007S-Pan-Tompkins-App",platform = "$COMPONENT_LOCATION/../Zynq-7007S-Pan-Tompkins/export/Zynq-7007S-Pan-Tompkins/Zynq-7007S-Pan-Tompkins.xpfm",domain = "standalone_ps7_cortexa9_0",template = "hello_world")

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

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

vitis.dispose()

