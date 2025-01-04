# 2025-01-04T15:23:02.612845300
import vitis

client = vitis.create_client()
client.set_workspace(path="Zynq-7007S-Pan-Tompkins")

vitis.dispose()

