""" 
Tate device, it implements DutBase interface.
"""

from base import DutBase

import subprocess
import sys
import os
class Tate(DutBase):
    def __init__(self,mac):
        pass

    def connectAp(self, ssid, key):
        s_fname = sys.path[0]
        scripts_dir = s_fname + os.sep + "scripts"
        if scripts_dir.find("scripts") != -1:
            while os.path.basename(scripts_dir) != "scripts":
                scripts_dir = os.path.dirname(scripts_dir)
        else:
            print "Path error, not in 'scripts'."
            exit(1)

        scripts_dut = scripts_dir + os.sep + "dut"
        try:
            adb_cmd = "adb push " + scripts_dut + os.sep + "connect_ap.sh /data"
            subprocess.check_output(adb_cmd, shell = True)
            adb_cmd = "adb shell chmod 777 /data/connect_ap.sh"
            subprocess.check_output(adb_cmd, shell = True)
            adb_cmd = "adb shell /data/connect_ap.sh \\\'\\\"" + ssid + "\\\"\\\' \\\'\\\"" + key + "\\\"\\\'"
            output = subprocess.check_output(adb_cmd, shell = True)
            print "Tate, adb shell data_connect_ap>", output
        except subprocess.CalledProcessError:
            print 'Tate, Error'

if __name__ == '__main__':
    tate = Tate()
    tate.connectAp("Cisco34585", "12345678")
