""" 
Wi-Fi Utilities.
"""

from scripts.utils.adb import Adb

import time
#
#  Exception classes
#

class WirelessError(RuntimeError):
    pass

class WifiError(WirelessError):
    pass

class WpaCliError(WifiError):
    pass


OPEN="open"
WEP="wep"
WPA="wpa"
WPA2="wpa2"
WPA2_TKIP="wpa2-tkip"
WPA_AES="wpa-aes"
valid_smethods=(OPEN, WEP, WPA, WPA2, WPA2_TKIP, WPA_AES)

#  Values for hotspot used in verify_connection
SPONSORED="sponsored"
UNSPONSORED="unsponsored"
NOT_HOTSPOT = "not_hotspot"

adb = Adb()

def wpa_cli(command, raise_failures=True):
    """utility function to get current wpa state"""

    output= adb.adb_shell ("%s %s" % (wpa_cli, command))
    if len(output) == 0:
        raise WpaCliError("wpa_cli %s returned no output" % command)

    answer = output[1]

    if raise_failures and (answer == "FAIL\n"):
        raise WpaCliError("wpa_cli command failed")

    return output

def get_current_state():
    """utility function to get current wpa state"""

    output = wpa_cli("status")
    for line in output:
        if line.startswith('wpa_state'):
            state = line.split('=')[1].strip()
            break

    return state

def enable_profile(ssid):
    """Enable the specified profile"""

    network_number = find_profile(ssid)
    if network_number is None:
        raise WifiError("enable_profile:  %s not found" % ssid)

    wpa_cli("enable_network %d" % network_number)

    print("enable_profile:  %s enabled" % ssid)

def enable_all_profiles():
    """Enable all profiles"""

    #  Find the highest network number.
    max_network_number = get_highest_network_number()
    if max_network_number is None:
        print("enable-all-profiles:  No profiles to enable")
        return

    #  Enable every network in the range.  Ignore errors (which could
    #  be holes in the sequence due to already-deleted networks).
    enabled_count = 0
    
    for network_number in range (max_network_number):
        try:
            wpa_cli ("enable_network %d" % network_number)
        except WpaCliError:
            pass
        else:
            enabled_count += 1

    if enabled_count == 1:
        print ("enable-all-profiles:  1 profile enabled")
    else:
        print ("enable-all-profiles:  %d profiles enabled" % enabled_count)


def get_highest_network_number():
    """utility function which returns the max number of profile count"""

    #  Find the highest network number.
    #  Not the same as the network count since there can be missing
    #  numbers.
    output = wpa_cli("list_networks")
    tab = output[-1].find('\t')
    try:
        max_network_number = int(output[-1][:tab]) + 1
    except ValueError:
        max_network_number = None
    return max_network_number

def verify_state_value(state):
    """verifies is the specified state is valid"""

    valid_states = ('CONNECTED','READY', 'PENDING', 'CONNECTED_LOCAL', 'NA', 'COMPLETED',
                    'DISCONNECTED', 'SCANNING', 'ASSOCIATING', 'ASSOCIATED', 'INACTIVE',
                    'AUTHENTICATING', '4WAY_HANDSHAKE', 'GROUP_HANDSHAKE')

    #  For compatability with the eInk version of wifitest we accept
    #  wifid states and map them to corresponding wpa_supplicant states
    map_states = {'CONNECTED':'COMPLETED', 'PENDING':'SCANNING',
        'READY':'DISCONNECTED', 'NA':'INACTIVE', 'CONNECTED_LOCAL':'COMPLETED'}

    if state in valid_states:
        if map_states.has_key(state):
            state = map_states[state]
        return state
    else:
        raise ValueError, \
         'verify-state-value:  specified state %s is not valid; expecting one of %s' \
            % (state, valid_states)

def wait_for_state(state, max_wait_seconds=180, ssid=None):
    """waits to get specified wifi state for the specified timeout"""

    #  state can be a string or a sequence (assumed if not a string)
    try:
        len(state)
    except TypeError:
        raise ValueError(
            "state parameter must be either string or sequence; found %s" \
                % state)

    if type(state) is str:
        state = verify_state_value(state)
    else:
        state = list(state)
        for i in range(len(state)):
            state[i] = verify_state_value(state[i])

    previous_state = ""

    # get the current wifi state and compare with the specified one
    for i in range(int(max_wait_seconds)):
        curr_state = get_current_state()
        if curr_state in state:
            if curr_state == 'COMPLETED' and ssid:
                curr_ssid = get_current_ssid()
                if curr_ssid == ssid:
                    print ("wait_for_state: already %s with %s ssid" % (state, ssid))
                    break
                else:
                    if curr_state != previous_state:
                        print ("wait_for_state: found %s to %s, waiting to connect with %s" \
                            % (curr_state, curr_ssid, ssid))
                        previous_state = curr_state

                    time.sleep(1)
            else:
                print ("wait_for_state: %s state found as expected" % \
                        curr_state)
                break
        else:
            if curr_state != previous_state:
                print ("wait_for_state: found current state %s; waiting for %s" % \
                        (curr_state, state))
                previous_state = curr_state

            time.sleep(1)

    else:
        if get_current_state() not in state:
            raise WifiError, \
              'wait_for_state: timed out waiting for %s state after waiting for %s seconds' \
                % (state, max_wait_seconds)
        elif ssid and get_current_ssid() != ssid:
            raise WifiError, \
               'wait_for_state: time out waiting for %s with %s after %s seconds' \
                            % (state, ssid, max_wait_seconds)
        else:
            if curr_state != previous_state:
                print ("wait_for_state: found %s to %s, waiting to connect with %s" \
                        % (state, curr_ssid, ssid))
                previous_state = curr_state

def add_profile(ssid, smethod, password=None, expect_failure=False,
    omit_smethod=False, hidden=False):
    """Add a profile to the configured list"""

    #  NOTE:  When you add, delete, or alter the variables being set
    #  for a given security method, be sure to keep the variable
    #  "expectations" in verify_profile in sync.

    #  internal method to set a network parameter
    #  This is defined internally because we want to use the
    #  add_profile local variable, network_number, without having to
    #  pass it every time.
    def set_network(keyword, value):

        wpa_cli("set_network %d %s %s" % (network_number, keyword, value))

    #  Validate parameters
    if smethod not in valid_smethods:
        raise ValueError(
            "add_profile:  %s is not a valid smethod; should be one of %s" % \
            (smethod, valid_smethods))

    if smethod == OPEN:
        if password is not None:
            raise ValueError("add_profile:  password not used with smethod=OPEN")
    else:
        if password is None:
            raise ValueError("add_profile:  password is required unless smethod=OPEN")

    network_added = False

    try:
        #  If ssid already specified, reuse that entry, otherwise create
        #  a new network entry
        network_number = find_profile(ssid)

        if network_number is None:
            stdout = wpa_cli("add_network")
            network_number = int(stdout[1])
            network_added = True

        set_network("ssid", cli_quoted_string(ssid))
        set_network("group", quoted_string("CCMP TKIP WEP40 WEP104"))

        if hidden:
            set_network("scan_ssid", "1")

        if smethod.startswith(WPA):
            set_network("key_mgmt", "WPA-PSK")
            set_network("proto", quoted_string("WPA RSN"))
            set_network("pairwise", quoted_string("CCMP TKIP"))
            try:
                set_network("psk", hex_or_string(password, (64,)))
            except WifitestError:
                raise ValueError ("add_profile:  Invalid WPA password")
        else:
            set_network("key_mgmt", "NONE")

        if smethod.startswith(WEP):
            set_network("wep_key0",  hex_or_string(password, (10, 26)))
            set_network("wep_tx_keyidx", 0)

        verify_profile (ssid, smethod)
        enable_profile (ssid)

    #  For any error remove the entry if we created it
    except:
        if network_added:
            wpa_cli("remove_network %d" % network_number)

        if expect_failure:
            log(TINFO, "add_profile: %s failed as expected" % ssid)
            return
        else:
            raise
    else:
        if expect_failure:
            raise WifitestError(
                "add_profile:  expecting failure; didn't see one")

        else:
            log(TINFO, "add_profile:  %s added successfully" % ssid)
            return
def connect(ssid=None, max_wait_seconds=180, mode='always', hotspot=None,
    force_disconnect=False, expect_failure=False, check_disconnect=False,
    expected_reason=None):
    """Connect to a wifi device"""

    if mode !='always':
        raise ValueError, 'connect: Only always mode is supported currently'

    #  check the connection status
    state = get_current_state()
    if state == 'COMPLETED':
        if force_disconnect:
            disconnect()
        else:
            if not ssid:
                print ("connect: Already connected")
                return
            else:
                return verify_connection (ssid)

    try:
        #  If SSID is not passed, enable all profiles and just use
        #  wpa_cli scan which will connect with first available
        #  network 

        if not ssid:

            #  Loop through all profiles and enable them
            max_network_number = get_highest_network_number()
            if max_network_number is None:
                raise WifiError, "connect: No profile to connect"

            enable_all_profiles()

            print ("connect: Attempting connection to any available AP")
            wpa_cli("scan")

        else:
            #  use select_network which enables only given profile and connects to it
            network_number = find_profile(ssid)
            if network_number is None:
                raise WifiError("connect:  profile for %s not found" % ssid)

            print ("connect: Attempting connection to %s" % ssid)
            wpa_cli("select_network %d" % network_number)


        #  Wait to get connected for max_wait_seconds.
        wait_for_state('COMPLETED', max_wait_seconds)

        if ssid:
            connected_ssid = get_current_ssid()
            if connected_ssid != ssid:
                raise WifiError, "connect: Connection established to %s, \
                    expecting to connect to %s" % (connected_ssid, ssid)

            print ("connect: Connection established to %s" % connected_ssid)
            
            enable_all_profiles()
        else:
            connected_ssid = None
            
        verify_connection(connected_ssid, hotspot=hotspot)

    except WirelessError, e:
        if expect_failure:
            print (e)
            print ("connect: connect failed as expected")
            return
        else:
            raise
    else:
        if expect_failure:
            raise WifiError(
                "connect:  expecting failure; didn't see one")

def disconnect(max_wait_seconds=180):
    """Disconnec the current wifi connection"""

    curr_state = get_current_state()

    if (curr_state == "DISCONNECTED") or (curr_state == "INACTIVE"):
        print ("disconnect:  Already in %s state" % curr_state)
        return

    #  as the supplicant is also controlled by native wifiManager,
    #  using disable_network instead of disconnect.
    max_network_number = get_highest_network_number()

    if max_network_number is None:
        raise WifiError, "disconnect: No profiles configured"

    #  Disable every network in the range.  Ignore errors (which could
    #  be holes in the sequence due to already-deleted networks).
    for network_number in range (max_network_number):
        wpa_cli ("disable_network %d" % network_number, raise_failures=False)

    #  Wait to get disconnected for max_wait_seconds.
    wait_for_state(('DISCONNECTED', 'INACTIVE'), max_wait_seconds)
    verify_disconnect()

def verify_state(state):
    """Verifies that the state of the wi-fi system is as specified"""

    #  state can be a string or a sequence (assumed if not a string)
    try:
        len(state)
    except TypeError:
        raise ValueError(
            "state parameter must be either string or sequence; found %s" \
                % state)

    if type(state) is str:
        state = verify_state_value(state)
    else:
        state = list(state)
        for i in range(len(state)):
            state[i] = verify_state_value(state[i])

    #  get the current wifi state and compare with the specificed one
    curr_state = get_current_state()
    if curr_state in state:
        print ("verify_state: found wifi state %s as expected" % curr_state)
    else:
        raise WifiError, \
        'verify_state: current state %s does not match with expected %s' \
            % (curr_state, state)

def verify_disconnect():
    """Verify if the current state is disconnected"""

    #  Check current wifi state and raise failure if connected
    verify_state(('DISCONNECTED', 'INACTIVE'))

def find_profile(essid):
    """Return the index number of the specified profile, or None if not found"""

    output_list = show_profile(essid, brief=True)

    if len(output_list) == 0:
        return None

    tab = output_list[0].find('\t')

    return int(output_list[0][:tab])

def show_profile(essid=None, brief=False):
    """List profile(s) for specified device or all devices"""

    output_list = []

    if essid is None or brief:
        stdout = wpa_cli("list_networks")

        for line in stdout:
            if essid is None or "\t%s\t" % essid in line:
                output_list.append(line.strip())

    else: #  essid was specified
        network_number = find_profile(essid)
        if network_number is None:
            raise WifiError('show_profile:  ESSID "%s" was not found' % essid)

        for field in ("ssid", "scan_ssid", "key_mgmt", "pairwise", "group",
            "psk", "eap", "identity", "password", "ca_cert", "client_cert",
            "private_key", "private_key_passwd", "phase1", "ca_cert2",
            "client_cert2", "private_key2", "private_key2_passwd", "wep_key0",
            "wep_tx_keyidx", "proto", ):
            stdout = wpa_cli ("get_network %d %s" % (network_number, field),
                raise_failures=False)

            answer = stdout[1]

            if answer == "FAIL\n":  continue

            output_list.append("%20s = %s" % (field, answer))

    return output_list

def verify_ssid(ssid):
    """Make sure specified SSID is present and marked current"""

    output = show_profile(ssid, brief=True)

    if (output is None) or (len(output) < 1):
            raise WifiError("verify-ssid:  profile for %s was not found" \
            % ssid)

    if "[CURRENT]"in output[0]:
        print("verify-ssid:  %s is connected" % ssid)
    else:
        raise WifiError("verify-ssid:  %s is not connected" % ssid)

def convert_ip(instring):
    """Converts a numeric-format IP address as displayed in /proc/net/route

    For example this would convert "0101A8C0" to "192.168.1.1"
    """

    outstring = ""

    for n in range(6, -1, -2):
        outstring += "%d" % int(instring[n:n+2], 16)
        if n:
            outstring += "."

    return outstring

def get_ip():
    """utility function to get current IP address"""

    #  get dhcp information
    dhcp_lines = adb.adb_shell ("getprop")

    curr_ip = find_value (dhcp_lines, "ipaddress").strip('[]')
    return curr_ip

def get_current_ssid():
    """utility function to get current ssid"""

    ssid = None
    output = wpa_cli("status")
    for line in output:
        if line.startswith('wpa_state'):
            state = line.split('=')[1].strip()
            break
    if state == 'COMPLETED':
        for line in output:
            if line.startswith('ssid'):
                ssid = line.split('=')[1].strip()
                break
    return ssid


def scan(skip_scan=False):
    """Return one or all profiles"""

    if skip_scan:
        print("Scan:  Skipping scan - returning existing scan list")
    else:
        print("Scan:  Running scan")
        wpa_cli("scan")

    stdout = wpa_cli("scan_results")

    output_list = []

    for line in stdout:
        output_list.append(line.strip())

    return output_list

def verify_connection(ssid, my_ip=None, mask=None,
    gateway=None):

    #  First confirm wifi state is connected
    verify_state('COMPLETED')

    #  Verify SSID
    if ssid is not None:
        verify_ssid (ssid)

    #  Get routing information for future use
    print ("verify-connection:  Waiting for route table to populate")
    for i in range(30):
        route_lines = read_file("/proc/net/route")

        #  Get number of routes
        route_count = len(route_lines) - 1
        
        if route_count > 0:
            print ("verify-connection:  %d entries in routing table" \
                % route_count)
            break
        time.sleep(1)
    else:
        raise WifiError(
            "verify-connection:  No entries in route table after 30 seconds")

    #  Verify SSID one more time
    #  It sometimes changes if the routing tables were not set
    if ssid is not None:
        verify_ssid(ssid)
    
    #  get dhcp information for future use
    dhcp_lines = adb.adb_shell("getprop")

    #  Find first wildcard character in my_ip
    if my_ip is None:
        star = -1
    else:
        star = my_ip.find("*")

    #  Verify the IP address
    #  Check dhcp info if not a specific address
    if star >= 0:
        dhcp_ip = find_value (dhcp_lines, "ipaddress")

        #  Now we must find the non-wild-card part of the IP
        #  This assumes wild cards are at the end
        ip_start = my_ip[:star]
        if ip_start in dhcp_ip:
            print("verify-connection:  Found IP address, %s, in dhcp info" \
                    % dhcp_ip)
        else:
            raise WifiError(
                "verify-connection:  Expecting IP address, %s, found %s in dhcp info" % \
                    (my_ip, dhcp_ip))


    #  Verify mask
    if mask is not None:
        #  check the dhcp info
        if star >= 0:
            dhcp_mask = find_value (dhcp_lines, "mask")
            if mask in dhcp_mask:
                print ("verify-connection:  Found mask, %s, in dhcp info" \
                    % mask)
            else:
                raise WifiError(
               "verify-connection:  Expecting mask, %s, found %s in dhcp info" \
                    % (mask, dhcp_mask))

        #  Check routing table
        for line in route_lines:
            words = line.split()
            if words[2] == "00000000":
                found_mask = convert_ip(words[7])
                
                if found_mask == mask:
                    print ("verify-connection:  Found mask, %s, in routing table" \
                            % mask)
                    break
        else:
            raise WifiError(
            "verify-connection:  Couldn't find mask, %s, in routing table" \
                % mask)

    #  Verify gateway
    if gateway is not None:
        #  check the dhcp info
        if star >= 0:
            dhcp_gateway = find_value (dhcp_lines, "gateway")
            if gateway in dhcp_gateway:
                print ("verify-connection:  Found gateway, %s, in dhcp info" \
                        % gateway)
            else:
                raise WifiError(
            "verify-connection:  Expecting gateway, %s, found %s in dhcp info" \
                    % (gateway, dhcp_gateway))

        #  Check routing table
        for line in route_lines:
            words = line.split()
            try:
                found_gateway = convert_ip(words[2])
            except ValueError:
                continue
                
            if found_gateway == gateway:
                print ("verify-connection:  Found gateway, %s, in routing table" \
                    % gateway)
                break
        else:
            raise WifiError(
         "verify-connection:  Couldn't find gateway, %s, in routing table" \
                    % gateway)
def verify_profile(ssid, smethod, expect_failure=False):
    """Verify a profile in the configured list"""

    #  Validate parameters
    if smethod not in valid_smethods:
        raise ValueError(
            "verify_profile:  %s is not a valid smethod; should be one of %s" % \
            (smethod, valid_smethods))

    try:
        network_number = find_profile(ssid)

        if network_number is None:
            raise WifiError ("verify_profile:  %s not found" % ssid)

        #  This data structure gives expected values for eacy security
        #  method.  (We only use the first three letters because wpa
        #  is the same as wpa2 which is the same as wpa2-tkip (at
        #  least for now).  NOTE:  This structure should be kept in
        #  sync with the logic of add_profile in terms of which
        #  variables are set for which security method.
        expectations = {
            OPEN[:3] : {
                "psk"      : "FAIL",
                "key_mgmt" : "NONE",
                "wep_key0" : "FAIL",
                },
            WEP : {
                "psk"      : "FAIL",
                "key_mgmt" : "NONE",
                "wep_key0" : "*",
                },
            WPA : {
                "psk"      : "*",
                "key_mgmt" : "WPA-PSK",
                "wep_key0" : "FAIL",
                },
            }

        #  Find the one dictionary for the smethod we expect
        expectation = expectations[smethod[:3]]

        #  Loop through each key (variable) to make sure it has the
        #  expected value
        for key in expectation.keys():
            output = wpa_cli ("get_network %d %s" % (network_number, key),
                raise_failures=False)

        if expectation[key] not in output[1]:
            raise WifiError(
                "verify_profile:  For smethod %s, expecting %s=%s, found %s" % \
                (smethod, key, expectation[key], output[1]))

    except WifiError, e:
        if expect_failure:
            print (e)
            print ("Profile verification for %s failed as expected" \
                % ssid)
            return
        else:
            raise
    else:
        if expect_failure:
            raise WifiError(
                "verify_profile:  expecting failure, didn't see one")
        else:
            print("verify_profile:  %s verified" % ssid)
            return

def delete_profile(ssid):
    """Delete the specified profile"""

    network_number = find_profile(ssid)
    if network_number is None:
        raise WifiError("delete_profile:  %s not found" % ssid)

    wpa_cli("remove_network %d" % network_number)

    print("delete_profile:  %s deleted" % ssid)

def delete_all_profiles():
    """Delete all profiles"""

    #  Find the highest network number.
    max_network_number = get_highest_network_number()
    if max_network_number is None:
        print("delete-all-profiles:  No profiles to delete")
        return

    #  Delete every network in the range.  Ignore errors (which could
    #  be holes in the sequence due to already-deleted networks).
    network_count = 0
    
    for network_number in range (max_network_number):
        try:
            wpa_cli("remove_network %d" % network_number)
        except WpaCliError:
            pass
        else:
            network_count += 1

    if network_count == 1:
        print ("delete-all-profiles:  1 profile deleted")
    else:
        print ("delete-all-profiles:  %d profiles deleted" % network_count)



def cli_quoted_string(value):
    """This will return a string with the necessary quotes to pass to
    wpa_cli.  The string must be enclosed in double quotes, and that in
    turn must be enclosed in single quotes."""

    return """'"%s"'""" % value

def quoted_string(value):
    """this will put quotes around a string"""

    return '"%s"' % value

def hex_or_string(value, length_list):
    """Internal function to determine if a value is a valid hexadecimal number

    Note that length_list must actually be a sequence of possible valid lengths

    If the value is a valid hexadecimal string, then the original string is
    returned.  Otherwise the original string is enclosed in quotes and returned.

    """

    try:
        #  See if it's a valid hex value
        int(value, 16)
    except ValueError:
        return cli_quoted_string(value)

    #  See if it's a valid length
    if len(value) in length_list:
        return value
    else:
        return cli_quoted_string(value)

def read_file(filename):
    """Reads a file and returns the lines of the file as a sequence"""

    myfile = file(filename)
    try:
        lines = myfile.readlines()
    finally:
        myfile.close()

    return lines

def find_value(lines, key):
    "Find a value (assumed to be second word of a line)"

    for line in lines:
        if key in line:
            return line.split()[1]

    #  If we get this far we didn't find a match
    raise WifiError ("Couldn't find %s" % key)

class WifiHelper:
    def wpa_cli(self, command, raise_failures=True):        
        wpa_cli(command, raise_failures=True)
        
    def add_profile(self, ssid, smethod, password=None, expect_failure=False,
                    omit_smethod=False, hidden=False):
        add_profile(ssid, smethod, password, expect_failure,
                    omit_smethod, hidden)
        
    def connect(self, ssid=None, max_wait_seconds=180, mode='always', hotspot=None,
                force_disconnect=False, expect_failure=False, check_disconnect=False,
                expected_reason=None):
        connect(self, ssid, max_wait_seconds, mode, hotspot,
                force_disconnect, expect_failure, check_disconnect,
                expected_reason)
        
    


