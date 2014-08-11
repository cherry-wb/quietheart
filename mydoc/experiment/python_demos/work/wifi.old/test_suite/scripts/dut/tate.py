""" 
Tate device, it implements DutBase interface.
"""
from base import DutBase
from scripts.utils.adb import Adb

import subprocess
import time
import sys
import os

class Tate(DutBase):

    def __init__(self, mac):
        self.mac = mac
        self.adb = Adb()
    
    def __getScriptsPath(self):
        '''
        get shell scripts path
        '''
        s_fname = sys.path[0]
        scripts_dir = s_fname + os.sep + "scripts"
        if scripts_dir.find("scripts") != -1:
            while os.path.basename(scripts_dir) != "scripts":
                scripts_dir = os.path.dirname(scripts_dir)
        else:
            print "Path error, not in 'scripts'."
            exit(1)
        scripts_dut = scripts_dir + os.sep + "dut"
        return scripts_dut
    
    def __pushScript(self, fname):
        '''
        push shell scripts
        '''
        scripts_dut = self.__getScriptsPath()
        self.adb.adb_shell("mkdir -p /data/ApInteropTest")
        self.adb.run_cmd("push" + ' ' + scripts_dut + os.sep + fname + " /data/ApInteropTest")
        self.adb.adb_shell("chmod 777 /data/ApInteropTest/" + fname)
        
    def __check_wlan_driver(self):
        '''
        check wifi driver status
        '''
        output = self.adb.adb_shell("getprop wlan.driver.status");
        if output.find("ok") != -1:
            # If the property says the driver is loaded, check to
            # make sure that the property setting isn't just left
            # over from a previous manual shutdown or a runtime
            # crash.
            output = self.adb.adb_shell("lsmod");
            if output.find("bcmdhd") != -1:
                return 1
            else:
                return 0
        elif output.find("unloaded") != -1:
            return 0
        # wlan.driver.status is null from factory
        return 0
            
    def setDefaults(self, params):
        pass 

    def loadDriver(self):
        '''
        load wlan driver
        '''
        if (self.__check_wlan_driver()) == 0:
            self.adb.adb_shell("insmod /system/lib/modules/bcmdhd.ko \"dhd_msg_level=1 firmware_path=/system/etc/wifi/firmware.bin nvram_path=/system/etc/wifi/nvram.txt\"")        
            output = self.adb.adb_shell("lsmod");
            if output.find("bcmdhd") != -1:
                print "Successfully insmod bcmdhd"
            else:
                print "Fail to insmod bcmdhd"
                return

            self.adb.adb_shell("setprop wlan.driver.status ok")    
            # wait at most 20 seconds for completion    
            for i in range(1, 20):
                time.sleep(1)
                print "sleep 1 ......"+ str(i)
                output = self.adb.adb_shell("getprop wlan.driver.status")
                if output.find("ok") != -1:
                    print "Succefully Set wlan.driver.status to ok"
                    break;
            else:
                print "Fail to set wlan.driver.status to ok"
        else:
            print "Wifi driver has been already loaded"

    def unloadDriver(self):
        '''
        unload wlan driver
        '''
        if (self.__check_wlan_driver()) == 1:
            self.adb.adb_shell("rmmod bcmdhd.ko")
            self.adb.adb_shell("setprop wlan.driver.status unloaded")
            # wait at most 10 seconds for completion    
            for i in range(1, 10):
                print "sleep 1 ......" + str(i)
                time.sleep(1)
                output = self.adb.adb_shell("getprop wlan.driver.status")
                if output.find("unloaded") != -1:
                    print "Succefully Set wlan.driver.status to unloaded"
                    break
            else:
                print "Fail to set wlan.driver.status to unloaded"
            
        else:
            print "Wifi driver has been already unloaded"

    def startSupplicant(self):
        '''
        start wpa_supplicant
        '''
        output = self.adb.adb_shell("getprop init.svc.wpa_supplicant")
        if output.find("running") != -1:
            print "wpa_supplicant is already running"            
        else:
            print "wpa_supplicant is not running"
            self.adb.adb_shell("setprop ctl.start \"wpa_supplicant:-iwlan0 -c/data/misc/wifi/wpa_supplicant.conf\"")
            # wait at most 20 seconds for completion
            for i in range(1, 20):
                print "sleep 1 ......" + str(i)
                time.sleep(1)
                output = self.adb.adb_shell("getprop init.svc.wpa_supplicant")
                if output.find("running") != -1:
                    print "Successfully start wpa_supplicant"
                    break
            else:
                print "Fail to start wpa_supplicant"
 
    def stopSupplicant(self):
        '''
        stop wpa_supplicant
        '''
        output = self.adb.adb_shell("getprop init.svc.wpa_supplicant")
        if output.find("running") == -1:
            print "wpa_supplicant is already stopped" 
        else:
            print "wpa_supplicant is running"
            self.adb.adb_shell("setprop ctl.stop wpa_supplicant")
            # wait at most 5 seconds for completion
            for i in range(1, 5):
                print "sleep 1......" + str(i)
                time.sleep(1)
                output = self.adb.adb_shell("getprop init.svc.wpa_supplicant")
                if output.find("stopped") != -1:
                    print "Succesfully stop wpa_supplicant"
                    break
            else:
                print "Fail to stop wpa_supplicant"

    def connectAp(self, ap):
        '''
        connect to a AP
        '''
        print ap.vendor
        ssid = ap.ssid2g
        key = ap.passphrase5g
        
        try:
            self.__pushScript("connect_ap.sh")
            adb_cmd = "adb shell /data/ApInteropTest/connect_ap.sh \\\'\\\"" + ssid + "\\\"\\\' \\\'\\\"" + key + "\\\"\\\'"
            output = subprocess.check_output(adb_cmd, shell = True)
            print "Tate, adb shell data_connect_ap>", output
        except subprocess.CalledProcessError:
            print 'Tate, Error'
            
    def disconnectAp(self):
        '''
        disconnect from a AP
        '''
        output = self.adb.adb_shell("wpa_cli disconnect | busybox grep OK")
        if output.find("OK") != 0:
            print "Successfully Disconnect."
        else :
            print "Fail to Disconnect."       
                     
    def pingTest(self):
        '''
        ping a server
        '''
        self.adb.adb_shell("ping -c 4 10.1.10.100")

