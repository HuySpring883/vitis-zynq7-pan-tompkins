# 2025-01-04T14:27:06.591634400
import vitis

client = vitis.create_client()
client.set_workspace(path="Zynq-7007S-Pan-Tompkins")

vitis.dispose()

