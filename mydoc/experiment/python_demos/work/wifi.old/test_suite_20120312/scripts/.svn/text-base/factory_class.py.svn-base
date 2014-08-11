#from ap.ap_classes import *
#from dut.dut_classes import *
from ap.base import *
from ap.cisco_e3000 import *
from ap.cisco_e3200 import *
from ap.cisco_wrt54gl import *
from dut.base import *
from dut.tate import *
from lib.db_api import database as db

class FactoryScenario:
    ''' used to generate action sequence with ap/device objects and its actions.

        '''
    obj = {}
    vendor_class={
        "ap:cisco:e3000":"CiscoE3000",
        "ap:cisco:e3200":"CiscoE3200",
        "ap:cisco:wrt54gl":"CiscoWRT54GL",
        "device:tate":"Tate",
    }

    def instance(self, scenario):
        ''' get the factory object instance.

            instance the factory object only once; if haven't been instanced, instance it by action; if no action, return -1.'''
        vendor = ""
        if hasattr(scenario,'m_vendor'):
            vendor = scenario.m_vendor
        else:
            vendor = "ap:cisco:e3000"
        
        if hasattr(scenario,'m_mac'):
            mac = scenario.m_mac
        else:
            mac = "68:7F:74:C5:CA:82"

        if not FactoryScenario.obj.has_key(vendor):
            if not FactoryScenario.vendor_class.has_key(vendor):
                print "vendor not support!"
                return None
            else:
                obj_class = FactoryScenario.vendor_class[vendor]
                exec 'FactoryScenario.obj["'+vendor+'"]='+obj_class+'(mac)'
                db.getDefaults(FactoryScenario.obj[vendor], vendor)
        return  FactoryScenario.obj[vendor]

    def set_action(self, a):
        self.m_action = a

