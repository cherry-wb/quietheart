#!/usr/bin/python
import sys
import re

import urllib
import urllib2

from BeautifulSoup import BeautifulSoup


def getFormHtml(url,name):
    request = urllib2.Request(url)
    try:
        res = urllib2.urlopen(request)
        page_src = res.read()
        soup = BeautifulSoup(page_src)
    except IOError, e:
        print "It looks like the username or password is wrong."
        print e
        sys.exit(1)
    pattern = re.compile(r".*(<form name=.*?</form>).*",re.S)
    content = pattern.match(page_src).group(1)
    return content

def getTaglist(content):
    soupForm = BeautifulSoup(content)
    allElements = soupForm.form.findAll()

    supportTagNameList = [ "input", "select" ]

    tagList = []
    number = 1
    for e in allElements:
        tagName = e.name
        if(not tagName in supportTagNameList):
            number += 1
            continue

        attrName = e.get("name", "")
        searchResult = [x for x in tagList if (x.get("name", "") == attrName)]
        if(len(searchResult) > 0):
            number += 1
            continue
        tagList.append(e)
    return tagList


def fixHtml(content):
    content = content.replace("\r", "")
    content = content.replace("\n", "")

    pattern = r"<script.*?</script>"
    content = re.sub(pattern, "", content)

    return content

def fixHtmlForm(content):

    content = content.replace("\r", "")
    content = content.replace("\n", "")

    pattern = r"<script.*?</script>"
    content = re.sub(pattern, "", content)

    pattern = r"<!--.*?-->"
    content = re.sub(pattern, "", content)
    return content


dhcpContent = r'''<form>
                    <p>We recommend that you keep the current default LAN IP Address of the 
                        Broadband Modem. Any changes made to the LAN IP Address will reset some of the other settings on the modem. Do not proceed without 
                    understanding the technical impact of changing these settings.</p>
                    <p><strong>1. To make changes, enter the new IP Address or Subnet Mask of your Broadband Modem below. </strong></p>
                    <table width="309" border="0" cellspacing="0" cellpadding="0">
                        <tbody><tr>
                            <td>&nbsp;&nbsp;&nbsp;Modem IP Address: </td>
                            <td><input name="ethIpAddress" id="ethIpAddress" type="text" maxlength="15"></td>
                        </tr>
                        <tr>
                            <td>&nbsp;&nbsp;&nbsp;Modem Subnet Mask:</td>
                            <td><input name="ethSubnetMask" id="ethSubnetMask" type="text" maxlength="15"></td>
                        </tr>
                    </tbody></table>
                    <p>&nbsp;</p>
                    <p><strong>2. Click "Apply and Reboot" to save your changes.</strong></p>
                    <p><a href="#" id="applyandreboot_btn" class="btn" onclick="onApply()"></a></p>
<!-- -------------------------------------------- -->
                    <p>&nbsp;</p>
                    <p>Your  modem will automatically assign an IP Address to each device
                  in your   network. </p>
                    <p><strong>1. Set the DHCP server state. </strong></p>
                    <table border="0" cellpadding="0" cellspacing="0">
                                <tbody><tr>
                                        <td width="110">&nbsp;&nbsp;&nbsp;DHCP Server:</td>
                                        <td width="87"><input name="dhcp_server" id="dhcp_server_on" type="radio" value="dhcp_server_on" checked="checked" onclick="dhcpServerClick()">      Enable</td>
                                        <td width="165"><input name="dhcp_server" id="dhcp_server_off" type="radio" value="dhcp_server_off" onclick="dhcpServerClick()">      Disable</td>
                            </tr>
                        </tbody></table>
                    <p>&nbsp;</p>
                    <div id="step1_disabled" class="greyed_out" style="display:none;">
                            <p><strong>2. Set the IP addressing values. </strong></p>
                    <table border="0" cellspacing="0" cellpadding="0">
                        <tbody><tr>
                            <td width="150">&nbsp;&nbsp;&nbsp;Beginning IP Address:</td>
                            <td><input type="text" disabled="disabled" class="greyed_out_textfield"></td>
                        </tr>
                            <tr><td width="150">&nbsp;&nbsp;&nbsp;Ending IP Address: </td>
                            <td><input type="text" disabled="disabled" class="greyed_out_textfield"></td>
                        </tr>
                        <tr>
                            <td width="150">&nbsp;&nbsp;&nbsp;Subnet Mask: </td>
                            <td><input type="text" disabled="disabled" class="greyed_out_textfield"></td>
                        </tr>
                    </tbody></table>
                    <p>&nbsp;</p>
                    <p><strong>3. Set the DHCP server lease time. </strong></p>
                    <table border="0" cellspacing="0" cellpadding="0">
                        <tbody><tr>
                            <td width="177" nowrap="nowrap">&nbsp;&nbsp;&nbsp;DHCP Server Lease Time:</td>
                            <td width="97" nowrap="nowrap"><input type="text" disabled="disabled" class="greyed_out_textfield" size="5">                        Day(s)</td>
                        <td width="90" nowrap="nowrap"><input type="text" disabled="disabled" class="greyed_out_textfield" size="5">                          Hours</td>
                        <td width="136"><input type="text" disabled="disabled" class="greyed_out_textfield" size="5">
                          Minutes</td>
                        </tr>
                    </tbody></table>
                    <p>&nbsp;</p>
                    <p><strong>4. Set the DNS values. </strong></p>
                    <table border="0" cellpadding="0" cellspacing="0">
                        <tbody><tr>
                            <td width="90">&nbsp;&nbsp;&nbsp;DNS:</td>
                            <td width="82"><input type="radio" disabled="disabled" value="radiobutton">Dynamic</td>
                        <td width="100"><input type="radio" disabled="disabled" class="greyed_out_radio" value="radiobutton">Static</td>
                        </tr>
                    </tbody></table>
                    <table border="0" cellspacing="0" cellpadding="0">
                        <tbody><tr>
                            <td width="150">DNS Server 1:</td>
                            <td><input type="text" disabled="disabled" class="greyed_out_textfield"></td>
                        </tr>
                        <tr>
                            <td width="150">DNS Server 2: </td>
                            <td><input type="text" disabled="disabled" class="greyed_out_textfield"></td>
                        </tr>
                    </tbody></table>
                    </div>
                    <div id="step1_enabled">
                    <p><strong>2. Set the IP addressing values. </strong></p>
                    <table border="0" cellspacing="0" cellpadding="0">
                        <tbody><tr>
                            <td width="150">&nbsp;&nbsp;&nbsp;Beginning IP Address:</td>
                            <td><input name="dhcpEthStart" id="dhcpEthStart" type="text" maxlength="15"></td>
                        </tr>
                        <tr>
                            <td width="150">&nbsp;&nbsp;&nbsp;Ending IP Address: </td>
                            <td><input name="dhcpEthEnd" id="dhcpEthEnd" type="text" maxlength="15"></td>
                        </tr>
                        <tr>
                            <td width="150">&nbsp;&nbsp;&nbsp;Subnet Mask: </td>
                            <td><input name="dhcpSubnetMask" id="dhcpSubnetMask" type="text" maxlength="15"></td>
                        </tr>
                    </tbody></table>
                    <p>&nbsp;</p>
                    <p><strong>3. Set the DHCP server lease time. </strong></p>
                    <table border="0" cellspacing="0" cellpadding="0">
                        <tbody><tr>
                            <td width="177" nowrap="nowrap">&nbsp;&nbsp;&nbsp;DHCP Server Lease Time:</td>
                            <td width="97" nowrap="nowrap"><input type="text" name="day" id="day" size="5" maxlength="5">                        Day(s)</td>
                            <td width="90" nowrap="nowrap"><input type="text" name="hour" id="hour" size="5" maxlength="5">                          Hours</td>
                            <td width="136"><input type="text" name="minute" id="minute" size="5" maxlength="5">                          Minutes</td>
                        </tr>
                    </tbody></table>
                    <p>&nbsp;</p>
                    <p><strong>4. Set the DNS values. </strong></p>
                    <table border="0" cellpadding="0" cellspacing="0">
                        <tbody><tr>
                            <td width="90">&nbsp;&nbsp;&nbsp;DNS:</td>
                            <td width="82"><input name="dns" type="radio" id="dns_dynamic" value="dns_dynamic" checked="checked" onclick="radioClick()">                        Dynamic</td>
                            <td width="100"><input name="dns" type="radio" id="dns_static" value="dns_static" onclick="radioClick()">                        Static</td>
                    </tr>
                    </tbody></table>
                    <table border="0" cellspacing="0" cellpadding="0">
                        <tbody><tr>
                            <td width="150">&nbsp;&nbsp;&nbsp;DNS Server 1:</td>
                            <td><input name="dnsPrimary" id="dnsPrimary" type="text" maxlength="15"></td>
                        </tr>
                        <tr>
                            <td width="150">&nbsp;&nbsp;&nbsp;DNS Server 2: </td>
                            <td><input name="dnsSecondary" id="dnsSecondary" type="text" maxlength="15"></td>
                        </tr>
                    </tbody></table>
                </div>
                <p>&nbsp;</p>
                <p><strong>5. Click "Apply" to save your changes.</strong></p>
                <p><a href="#" id="apply_btn" class="btn" onclick="onApply2()"></a></p>
<!-- -------------------------------------------- -->
                </form>'''
wirelessBasicContent = r'''<form name="mainform" action="wirelesssetup_basicsettings.wl" method="GET" onsubmit="return do_apply();">
        <input type="hidden" name="wlRadio" value="1" id="uiPostAPEnabled">
        <input type="hidden" name="wlChannel_wl0v0" value="0" id="uiPostChannel">
        <input type="hidden" name="wlSsid_wl0v0" value="" id="uiPostSSID">
        <input type="hidden" name="wlAuthMode_wl0v0" value="open" id="uiPostAuthMode">
        <input type="hidden" name="wlWep_wl0v0" value="disabled" id="uiPostWepEnabled">

        <input type="hidden" name="wlKeyBit_wl0v0" value="0" id="uiPostKeyBit">
        <input type="hidden" name="wlKeyIndex_wl0v0" value="1" id="uiPostKeyId">
        <input type="hidden" name="wlKeyIndex_wl0v0" value="1" id="uiPostKey128Id">
        <input type="hidden" name="wlKey1_wl0v0" value="873804900AAFE7ABAFE6233342" id="uiPostKeyValue1">
        <input type="hidden" name="wlKey1_wl0v0" value="873804900AAFE7ABAFE6233342" id="uiPostKey128Value1">
        <input type="hidden" name="wlKey2_wl0v0" value="873805000AAFD7ABAFD6233341" id="uiPostKeyValue2">
        <input type="hidden" name="wlKey2_wl0v0" value="873805000AAFD7ABAFD6233341" id="uiPostKey128Value2">
        <input type="hidden" name="wlKey3_wl0v0" value="873805100AAFC7ABAFC6233340" id="uiPostKeyValue3">
        <input type="hidden" name="wlKey3_wl0v0" value="873805100AAFC7ABAFC6233340" id="uiPostKey128Value3">
        <input type="hidden" name="wlKey4_wl0v0" value="873805200AAFB7ABAFB6233339" id="uiPostKeyValue4">
        <input type="hidden" name="wlKey4_wl0v0" value="873805200AAFB7ABAFB6233339" id="uiPostKey128Value4">
        
        <input type="hidden" name="wlDefaultKeyFlagWep64Bit" value="1" id="uiPostDefaultKeyFlagWep64Bit">
        <input type="hidden" name="wlDefaultKeyWep64Bit" value="AAFE7ABAFE" id="uiPostDefaultKeyWep64Bit">
        <input type="hidden" name="wlDefaultKeyFlagWep128Bit" value="1" id="uiPostDefaultKeyFlagWep128Bit">
        <input type="hidden" name="wlDefaultKeyWep128Bit" value="" id="uiPostDefaultKeyWep128Bit">
        <!--psk-->
        <input type="hidden" name="wlDefaultKeyFlagPsk" value="14" id="uiPostDefaultKeyFlagPsk">
        <!--input type="hidden" name="wlDefaultKeyPsk" value="" id="uiPostDefaultKeyPsk"-->
        <input type="hidden" name="wlDefaultKeyPsk0" value="HBJFBRW6THN6S3X9" id="uiPostDefaultKeyPsk">

        <input type="hidden" name="wlWpaPsk_wl0v0" value="HBJFBRW6THN6S3X9" id="uiPostPskValue">
        <!--wpa-->
        <input type="hidden" name="wlRadiusServerIP_wl0v0" value="0.0.0.0" id="uiPostServerIp">
        <input type="hidden" name="wlRadiusPort_wl0v0" value="1812" id="uiPostPort">
        <input type="hidden" name="wlRadiusKey_wl0v0" value="" id="uiPostKey">
        <input type="hidden" name="wlWpaGtkRekey_wl0v0" value="0" id="uiPostGroupInterval">

        <input type="hidden" name="needthankyou" value="1">
                    <div class="stepWrapper_header"></div>
                    <div class="stepWrapper">
                        <p align="center"><input type="button" value="  Run Wireless Wizard  " onclick="btnRunWlWizard()" class="SRButton1"> </p>
                        <p><strong>1. Set the wireless radio state.</strong></p>
                        <table>
                            <tbody><tr>
                                <td width="150">
                                    Wireless Radio:
                                </td>
                                <td><input name="wireless_onoff" id="id_wl_on" type="radio" value="on" onclick="onClickAPEnable();" checked="checked">
                                    Enable </td>
                                <td><input name="wireless_onoff" id="id_wl_off" type="radio" value="off" onclick="onClickAPEnable();">
                                    Disable </td>
                            </tr>
                        </tbody></table>
                    </div>
                    <div class="stepWrapper_footer"></div>
                    <div class="stepWrapper_header"></div>
                    <div class="stepWrapper">
                        <p><strong>2. Change the network name (optional).</strong></p>
                        <table>
                            <tbody><tr>
                                <td width="150">Network Name:</td>
                                <td>
                                    <input name="ssid" id="id_ssid" type="text" size="25" maxlength="32" style="margin:auto auto auto auto; line-height:12px;" onchange="onSSIDKeyUp('id_ssid', 32);">
                                </td>
                            </tr>
                        </tbody></table>
                    </div>
                    <div class="stepWrapper_footer"></div>
                    <div class="stepWrapper_header"></div>
                    <div class="stepWrapper">
                        <p><strong>3. Change network channel</strong></p>
                        <p>Channel provides the ability to change the wireless channel the AP uses to connect with client devices.</p>
                        <table>
                            <tbody><tr>
                                <td width="150">Channel:</td>
                                <td>
                                    <select name="wlChannel" id="id_channel" onchange="onChangeChannel();">
                               <!-- <option selected="selected">Auto Detect </option>
                                <option>1 </option>
                                <option>2 </option>
                                <option>3 </option>
                                <option>4 </option>
                                <option>5 </option>
                                <option>6 </option>
                                <option>7 </option>
                                <option>8 </option>
                                <option>9 </option>
                                <option>10 </option>
                                <option>11 </option>
                                -->
                                    <option value="0">Auto Detect</option><option value="1">1</option><option value="2">2</option><option value="3">3</option><option value="4">4</option><option value="5">5</option><option value="6">6</option><option value="7">7</option><option value="8">8</option><option value="9">9</option><option value="10">10</option><option value="11">11</option></select>
                                </td>
                            </tr>
                        </tbody></table>
                    </div>
                    <div class="stepWrapper_footer"></div>
                    <div class="stepWrapper_header"></div>
                    <div class="stepWrapper">
                        <p><strong>4. Wireless WPA/WPA2 Security</strong></p>
                        <p>We recommend using WPA/WPA2 Security because it encrypts your wireless traffic.</p>
                        <table>
                            <tbody><tr>
                                <td width="150"><input name="wpa_onoff" id="id_wpa_on" type="radio" value="on" checked="checked" onclick="onSelectSecurity();">WPA/WPA2</td>
                                <td><input name="wpa_onoff" id="id_wpa_off" type="radio" value="off" onclick="onSelectSecurity();">off</td>
                            </tr>
                        </tbody></table>
                    </div>
                    <div class="stepWrapper_footer"></div>
                    <div class="stepWrapper_header"></div>
                    <div class="stepWrapper">
                        <p><strong>5. Select WPA/WPA2 PSK</strong></p>
                        <p><strong>Note:</strong> To create a Pre-Shared Key, enter at least eight (8) alphanumeric charaters in the test boxabove. Make sure that all of your wireless-enabled devices support WPA and know the Pre-Shared Key (PSK) to join the network.</p>
                        <table>
                            <tbody><tr>
                                <td>
                                    <input name="psk" id="id_psk" type="text" size="25" maxlength="63" style="margin:auto auto auto auto; line-height:12px;" disabled="">
                                </td>
                                <td> Pre-Shared Key (PSK) for Home Network</td>
                            </tr>
                        </tbody></table>
                    </div>
                    <div class="stepWrapper_footer"></div>
                    <div class="stepWrapper_header"></div>
                    <div class="stepWrapper">
                        <p><strong>6. Write down the wireless settings.  The settings below are
                            required to
                    configure  wireless clients.</strong></p>
                <table border="0" cellpadding="0" cellspacing="0" class="defaultstyle_left" id="wl_settings_tb" style="margin:10px auto 0 auto;">
                    <tbody><tr>
                        <th width="47">&nbsp;</th>
                        <th width="191"><div align="left" nowrap="">Wireless Parameter</div></th>
                        <th width="198"><div align="left">Setting</div></th>
                    </tr>
                    <!-- wireless on/off -->
                    <tr>
                        <td align="left">&nbsp;</td>
                        <td><div align="left">Wireless Radio:</div></td>
                        <td align="left"><span id="id_wlsetting_onoff">ON</span></td>
                    </tr>
                    <!-- SSID -->
                    <tr>
                        <td>&nbsp;</td>
                        <td><div align="left">Network Name:</div></td>
                        <td align="left"><span id="id_wlsetting_ssid">zfhyurxsmd</span></td>
                    </tr>
                    <!-- 
                    <tr>
                        <td><img src="../_images/h_wirelesssetup_wep.png" width="45" height="45" /></td>
                        <td>
                                Security Type:
                            </td>
                        <td>
                                </a>WPA2-Personal
                            </td>
                    </tr>
                    <tr>
                        <td><img src="../_images/h_wirelesssetup_wep.png" width="45" height="45" /></td>
                        <td>
                                Security Key/Passphrase:
                            </td>
                        <td>
                                </a>123ac234bca451b6a3c34bfd34
                            </td>
                    </tr>
                    <tr>
                        <td colspan="3"><a href="#" class="btn print_btn float_right"></a>
                        </td>
                    </tr>
                    -->
                <tr><td align="left"></td><td align="left"><div align="left">Security Type:</div></td><td align="left"><span class="status_text_r">OFF</span></td></tr><tr><td align="right"></td><td align="right"></td><td align="right"><div align="right"><p><a href="" id="print_btn" onclick="printdiv('print_div');" class="btn"></a></p></div></td></tr></tbody></table>
            </div>
            <div class="stepWrapper_footer"></div>
  <!--SCRIPT LANGUAGE="JavaScript">
            
  </SCRIPT-->

    <div id="print_div" style="display:none;">
                <table id="wl_print_tb" border="1" cellspacing="3">
                    <tbody>
                    <tr>
                        <th width="47">&nbsp;</th>
                        <th width="191"><div nowrap="" align="center">Wireless Parameter</div></th>
                        <th width="198"><div align="center">Setting</div></th>
                    </tr>
                    <tr>
                        <td align="left">&nbsp;</td>
                        <td><div align="left">Wireless Radio:</div></td>
                        <td align="left"><span id="id_wlsetting_onoff_p">ON</span></td>
                    </tr>
                    <tr>
                        <td>&nbsp;</td>
                        <td><div align="left">Network Name:</div></td>
                        <td align="left"><span id="id_wlsetting_ssid_p">zfhyurxsmd</span></td>
                    </tr>
                </tbody></table>
    </div>
            <div class="stepWrapper_header"></div>
            <div class="stepWrapper">
                <p><strong>7. Click "Apply" to save your changes.</strong></p>
                <p><a href="#" id="apply_btn" onclick="do_apply();" class="btn"></a></p>
            </div>
            <div class="stepWrapper_footer"></div>
      </form>'''
wirelessRadioContent = r'''<form name="mainform" action="wirelesssetup_radiosetup.wl" method="GET" onsubmit="return do_apply();">
                <input type="hidden" name="wlgMode" value="0" id="uiPostbgMode">
                <input type="hidden" name="wlNmode" value="off" id="uiPostnMode">
                <input type="hidden" name="wlNReqd" value="0" id="uiPostnReqd">
                <input type="hidden" name="wlNBwCap" value="0" id="uiPostnBwCap">
                <input type="hidden" name="wlNCtrlsb" value="0" id="uiPostnCtrlsb">
                <input type="hidden" name="wlAmpdu" value="auto" id="uiPostampdu">
                <input type="hidden" name="wlAmsdu" value="0" id="uiPostamsdu">
                <input type="hidden" name="wlChannel" value="0" id="uiPostChannel">
                <input type="hidden" name="wlTxPwrPcnt" value="100" id="uiPostTxPwrPcnt">
         <input type="hidden" name="needthankyou" value="1">
               <div class="stepWrapper_header"></div>
               <div class="stepWrapper"> 
                <p><strong>1. Select channel.</strong></p>
                <table>
                    <tbody><tr>
                        <td width="150"><label for="channel">Channel:</label>
                        </td>
                        <td><select name="wlChannel0" id="id_channel" onchange="onChangeChannel();">
                               <!-- <option selected="selected">Auto Detect </option>
                                <option>1 </option>
                                <option>2 </option>
                                <option>3 </option>
                                <option>4 </option>
                                <option>5 </option>
                                <option>6 </option>
                                <option>7 </option>
                                <option>8 </option>
                                <option>9 </option>
                                <option>10 </option>
                                <option>11 </option>
                                -->
                            <option value="0">Auto Detect</option><option value="1">1</option><option value="2">2</option><option value="3">3</option><option value="4">4</option><option value="5">5</option><option value="6">6</option><option value="7">7</option><option value="8">8</option><option value="9">9</option><option value="10">10</option><option value="11">11</option></select>
                        </td>
                    </tr>
                </tbody></table>
                </div>
                <div class="stepWrapper_footer"></div>
                <div class="stepWrapper_header"></div>
                <div class="stepWrapper">
                <p><strong>2. Select wireless power level.</strong></p>
                <table>
                    <tbody><tr>
                        <td width="150"><label for="power_level">Wireless Power Level:</label>
                        </td>
                        <td><select name="power_level" id="id_power_level" onchange="onChangeTxPower();">
                                <option selected="selected">100% </option>
                                <option>90% </option>
                                <option>80% </option>
                                <option>70% </option>
                                <option>60% </option>
                                <option>50% </option>
                                <option>40% </option>
                                <option>30% </option>
                                <option>20% </option>
                                <option>10% </option>
                            </select>
                        </td>
                    </tr>
                </tbody></table>
               </div>
                <div class="stepWrapper_footer"></div>
                <div class="stepWrapper_header"></div>
               <div class="stepWrapper">
                <p><strong>3. Select mode.</strong></p>
                <table>
                    <tbody><tr>
                        <td width="150"><label for="80211bg_mode">802.11 Mode:</label>
                        </td>
                        <td><select name="80211bg_mode" id="id_80211bg_mode" onchange="onSelectGmode();">
                               <option id="id_bgn" onclick="onSelectGmode();">802.11b or 802.11g or 802.11n Mode</option>
                               <option id="id_ng" onclick="onSelectGmode();">802.11g or 802.11n </option>
                               <option id="id_n" onclick="onSelectGmode();">802.11n Only </option>
                               <option id="id_bg" onclick="onSelectGmode();">802.11b or 802.11g </option>
                               <option id="id_g" onclick="onSelectGmode();">802.11g Only </option>
                               <option id="id_b" onclick="onSelectGmode();">802.11b Only </option>
                            </select>
                        </td>
                    </tr>
                </tbody></table>
                </div>
                    <div class="stepWrapper_footer"></div>
                <div id="non_nmode_group" style="display: block; ">
                    <div class="stepWrapper_header"></div>
                    <div class="stepWrapper">
                    <p><strong>4. Click "Apply" to save your changes.</strong></p>
                    <p><a href="#" id="apply_btn" class="btn" onclick="do_apply();"></a></p>
                    </div>
                    <div class="stepWrapper_footer"></div>
                </div>
                <div id="nmode_group" style="display: none; ">
                <!--
                    <div class="stepWrapper_header"></div>
                <div class="stepWrapper">
                    <p><strong>4. Select number of spacial streams.</strong></p>
                    <table>
                        <tr>
                            <td width="150">Spacial Streams: </td>
                            <td><select name="spatial_streams" id="id_spatial_streams">
                                    <option selected="selected">Auto Detect </option>
                                    <option>2</option>
                                    <option>1</option>
                                </select>
                            </td>
                        </tr>
                   </table>
                   </div>
                    <div class="stepWrapper_footer"></div>
                   -->
                    <div class="stepWrapper_header"></div>
                   <div class="stepWrapper">
                    <p><strong>4. Select channel width.</strong></p>
                    <table>
                        <tbody><tr>
                            <td width="150">Channel Width: </td>
                            <td width="125"><input type="radio" name="channel_width" id="id_channel_width_20" chechked="CHECKED" onclick="onSelectBwcap();" disabled="">
                                20 Mhz </td>
                            <td><input type="radio" name="channel_width" id="id_channel_width_40" onclick="onSelectBwcap();" disabled="">
                                40 Mhz </td>
                        </tr>
                    </tbody></table>
                    </div>
                    <div class="stepWrapper_footer"></div>
                    <div class="stepWrapper_header"></div>
                    <div class="stepWrapper">
                    <p><strong>5. Select channel control if 40 Mhz channel width selected in
                        step 4.</strong></p>
                    <table>
                        <tbody><tr>
                            <td width="150">Channel Control 40
                                Mhz: </td>
                            <td><select name="control_channel" id="id_control_channel" onchange="onSelectNctrlsb();" disabled="">
                                    <option value="0" id="id_None">None </option>
                                    <option value="-1" id="id_Lower">Lower</option>
                                    <option value="1" id="id_Upper">Upper</option>
                                </select>
                            </td>
                        </tr>
                    </tbody></table>
                   </div>
                    <div class="stepWrapper_footer"></div>
                    <div class="stepWrapper_header"></div>
                
                   <div class="stepWrapper">
                    <p><strong>6. Set the  MSDU aggregation state.</strong></p>
                    <table>
                        <tbody><tr>
                            <td width="150">MSDU Aggregation: </td>
                            <td width="125"><input type="radio" name="msdu_agg" id="id_msdu_agg_on" onclick="checked" onchange="onSelectAmsdu();" disabled="">
                                Enable </td>
                            <td><input type="radio" name="msdu_agg" id="id_msdu_agg_off" onclick="onSelectAmsdu();" disabled="">
                                Disable </td>
                        </tr>
                    </tbody></table>
                   </div>
                    <div class="stepWrapper_footer"></div>
                    <div class="stepWrapper_header"></div>
                   <div class="stepWrapper">
                    <p><strong>7. Set the MPDU aggregation state.</strong></p>
                    <table>
                        <tbody><tr>
                            <td width="150">MPDU Aggregation: </td>
                            <td width="125"><input type="radio" name="mpdu_agg" id="id_mpdu_agg_on" chechked="checked" onclick="onSelectAmpdu();" disabled="">
                                Enable </td>
                            <td><input type="radio" name="mpdu_agg" id="id_mpdu_agg_off" onclick="onSelectAmpdu();" disabled="">
                                Disable </td>
                        </tr>
                    </tbody></table>
                    </div>
                    <div class="stepWrapper_footer"></div>
                    <div class="stepWrapper_header"></div>
                    <!--
                    <div class="stepWrapper">
                    <p><strong>8. Set the MIMO power save state.</strong></p>
                    <table>
                        <tr>
                            <td width="150">MIMO Power Save: </td>
                            <td width="125"><input name="MIMO" id="radio3" type="radio" value="on" checked="checked" />
                                Enable </td>
                            <td><input name="wireless_on" id="radio4" type="radio" value="off" />
                                Disable </td>
                        </tr>
                    </table>
                    </div>
                    -->
                    <div class="stepWrapper">
                    <p><strong>8. Click "Apply" to save your changes.</strong></p>
                    <p><a href="#" id="apply_btn" class="btn" onclick="do_apply();"></a></p>
                    </div>
                    <div class="stepWrapper_footer"></div>
                </div>
                </form>'''
hiddenContent = r'''<form name="mainform" action="wirelesssetup_multiplessid.wl" method="GET" onsubmit="return do_apply();">


        <input type="hidden" name="wlRadio" value="1" id="uiPostAPEnabled">
       
        <input type="hidden" name="wlEnbl_wl0v0" value="1" id="uiPostAPEnabled_0">
        <input type="hidden" name="wlSsid_wl0v0" value="" id="uiPostSSID_0">
        <input type="hidden" name="wlHide_wl0v0" value="0" id="uiPostHiddenSSID_0">
        <input type="hidden" name="enblDhcpSrv0" value="1" id="uiPostDhcpEnbl_0" disabled="">
        <input type="hidden" name="dhcpSubnetMask0" value="255.255.255.0" id="uiPostDhcpSubnetMask_0" disabled="">
        <input type="hidden" name="ethIpAddress0" value="10.126.1.29" id="uiPostEthIpAddress_0" disabled="">
        <input type="hidden" name="wlBrName_wl0v0" value="br0" id="uiPostwlBrName_0">

        <input type="hidden" name="wlEnbl_wl0v1" value="0" id="uiPostAPEnabled_1">
        <input type="hidden" name="wlSsid_wl0v1" value="" id="uiPostSSID_1">
        <input type="hidden" name="wlHide_wl0v1" value="0" id="uiPostHiddenSSID_1">
        <input type="hidden" name="enblDhcpSrv1" value="0" id="uiPostDhcpEnbl_1">
        <input type="hidden" name="dhcpEthStart1" value="192.168.1.2" id="uiPostDhcpStart_1">
        <input type="hidden" name="dhcpEthEnd1" value="192.168.1.254" id="uiPostDhcpEnd_1">
        <input type="hidden" name="dhcpSubnetMask1" value="255.255.255.0" id="uiPostDhcpSubnetMask_1">
        <input type="hidden" name="ethIpAddress1" value="192.168.1.1" id="uiPostEthIpAddress_1">
        <input type="hidden" name="wlBrName_wl0v1" value="br0" id="uiPostwlBrName_1">

        <input type="hidden" name="wlEnbl_wl0v2" value="0" id="uiPostAPEnabled_2">
        <input type="hidden" name="wlSsid_wl0v2" value="" id="uiPostSSID_2">
        <input type="hidden" name="wlHide_wl0v2" value="0" id="uiPostHiddenSSID_2">
        <input type="hidden" name="enblDhcpSrv2" value="0" id="uiPostDhcpEnbl_2">
        <input type="hidden" name="dhcpEthStart2" value="192.168.1.2" id="uiPostDhcpStart_2">
        <input type="hidden" name="dhcpEthEnd2" value="192.168.1.254" id="uiPostDhcpEnd_2">
        <input type="hidden" name="ethIpAddress2" value="192.168.1.1" id="uiPostEthIpAddress_2">
        <input type="hidden" name="dhcpSubnetMask2" value="255.255.255.0" id="uiPostDhcpSubnetMask_2">
        <input type="hidden" name="wlBrName_wl0v2" value="br0" id="uiPostwlBrName_2">

        <input type="hidden" name="wlEnbl_wl0v3" value="0" id="uiPostAPEnabled_3">
        <input type="hidden" name="wlSsid_wl0v3" value="" id="uiPostSSID_3">
        <input type="hidden" name="wlHide_wl0v3" value="0" id="uiPostHiddenSSID_3">
        <input type="hidden" name="enblDhcpSrv3" value="0" id="uiPostDhcpEnbl_3">
        <input type="hidden" name="dhcpEthStart3" value="192.168.1.2" id="uiPostDhcpStart_3">
        <input type="hidden" name="dhcpEthEnd3" value="192.168.1.254" id="uiPostDhcpEnd_3">
        <input type="hidden" name="ethIpAddress3" value="192.168.1.1" id="uiPostEthIpAddress_3">
        <input type="hidden" name="dhcpSubnetMask3" value="255.255.255.0" id="uiPostDhcpSubnetMask_3">
        <input type="hidden" name="wlBrName_wl0v3" value="br0" id="uiPostwlBrName_3">
        <input type="hidden" name="wlSsidIdx" value="" id="uiPostSsidIdx">
  
    <input type="hidden" name="needthankyou" value="1">
            <div class="stepWrapper_header"></div>
            <div class="stepWrapper">
            <p><strong>1. Select the SSID (Network Name).</strong></p>
            <table>
                <tbody><tr>
                    <td width="150"><label for="ssid">SSID:</label></td>
                    <td> 
                        <select name="ssid" id="id_ssid" onchange="onSelectSSID();">
                            <option id="id_ssid_0" value="SSID0" selected="selected">zfhyurxsmd</option>
                            <option id="id_ssid_1" value="SSID1">NSJQN1</option>
                            <option id="id_ssid_2" value="SSID2">NSJQN2</option>
                            <option id="id_ssid_3" value="SSID3">NSJQN3</option>
                        </select>
                    </td>
                </tr>
            </tbody></table>                
            </div>
            <div class="stepWrapper_footer"></div>

            <div id="ssid_default" style="display: block; ">
                <div class="stepWrapper_header"></div>
                <div class="stepWrapper">
                <p><strong>2. Set SSID broadcast.</strong></p>
                <table>
                    <tbody><tr>
                        <td width="150">SSID Broadcast:</td>
                        <td width="130"><label><input name="ssid_mode" id="id_mode_bcast" type="radio" value="enable" checked="checked" onclick="onSelectMode();"> Broadcast SSID</label></td>
                        <td><label><input name="ssid_mode" id="id_mode_hide" type="radio" value="disable" onclick="onSelectMode();"> Hide SSID</label></td>
                    </tr>
                </tbody></table>                    
                </div>
                <div class="stepWrapper_footer"></div>
                <div class="stepWrapper_header"></div>
                <div class="stepWrapper">
                <p><strong>3. Enter an SSID network name. </strong></p>                    
                <table>
                    <tbody><tr>
                        <td width="150"><label for="default_ssid_network_name">Network Name:</label></td>
                        <td><input name="ssid_name" id="id_ssid_name_default" type="text" size="35" maxlength="32" onchange="onInputSsidName();"></td>
                    </tr>
                </tbody></table>
                </div>
                <div class="stepWrapper_footer"></div>
                <div class="stepWrapper_header"></div>
                <div class="stepWrapper">
                <p><strong>4. Click "Apply" to save your changes.</strong></p>
                 <p><a href="#" id="apply_btn" class="btn" onclick="do_apply();"></a></p>
                </div>
                <div class="stepWrapper_footer"></div>
            </div>
                <div id="ssid_2thru4" style="display: none; ">
                    <div class="stepWrapper_header"></div>
                    <div class="stepWrapper">
                    <p><strong>2. Set  SSID state.</strong></p>
                    <table>
                        <tbody><tr>
                            <td width="150"><label for="ssid">SSID State:</label></td>
                            <td width="130"><label><input name="ssid_state" id="id_ssid_enable" type="radio" value="enable" checked="checked" onclick="onSelectSSIDState();"> Enable SSID</label></td>
                            <td><label><input name="ssid_state" id="id_ssid_disable" type="radio" value="disable" onclick="onSelectSSIDState();"> Disable SSID</label></td>
                        </tr>
                    </tbody></table>
                    </div>
                    <div class="stepWrapper_footer"></div>
                    <div class="stepWrapper_header"></div>
                    <div class="stepWrapper">
                    <p><strong>3. Set SSID broadcast.</strong></p>
                    <table>
                    <tbody><tr>
                        <td width="150">SSID Broadcast:</td>
                        <td width="130"><label><input name="ssid_mode" id="id_mode_bcast_3" type="radio" value="enable" checked="checked" onclick="onSelectMode();"> Broadcast SSID</label></td>
                        <td><label><input name="ssid_mode" id="id_mode_hide_3" type="radio" value="disable" onclick="onSelectMode();"> Hide SSID</label></td>
                    </tr>
                    </tbody></table>                
                    </div>
                    <div class="stepWrapper_footer"></div>
                    <div class="stepWrapper_header"></div>
                    <div class="stepWrapper">
                    <p><strong>4. Set the SSID network name. </strong></p>
                    <table>
                        <tbody><tr>
                            <td width="150"><label for="ssid_network_name">Network Name:</label></td>
                            <td><input name="ssid_name" id="id_ssid_name" type="text" size="35" maxlength="32" onchange="onInputSsidName();" disabled=""></td>
                        </tr>
                    </tbody></table>
                    </div>
                    <div class="stepWrapper_footer"></div>
                    <!--
                    <div class="stepWrapper_header"></div>
                    <div class="stepWrapper">
                    <p><strong>5. Set Maximum Bandwidth Usage. </strong></p>
                    <table>
                        <tr>
                            <td width="150"><label for="ssid_network_max">SSID Bandwidth Usage:</label></td>
                            <td><input id="ssid_network_max" type="text" size="10" /> Kbps</td>
                        </tr>
                    </table>                
                    </div>
                    <div class="stepWrapper_footer"></div>
                    -->
                    <div class="stepWrapper_header"></div>
                    <div class="stepWrapper">
                    <p><strong>5. Set SSID in Separate Subnet.</strong></p>
                    <table>
                        <tbody><tr>
                            <td colspan="2">SSID Subnet:</td>
                            <td><label><input name="ssid_subnet_enabled" id="id_ssid_subnet_enable" type="radio" value="enable" onclick="onSelectSSIDSubnet();" checked="checked"> Enable</label> 
                            <label><input name="ssid_subnet_enabled" id="id_ssid_subnet_disable" type="radio" value="disable" onclick="onSelectSSIDSubnet();">
                             Disable</label></td>
                        </tr>
                        <tr>
                            <td>&nbsp;</td>
                            <td>DHCP Start Address:</td>
                            <td><input name="dhcp_start_address" id="id_dhcp_start_address" type="text" size="30"></td>
                        </tr>
                        <tr>
                            <td>&nbsp;</td>
                            <td>DHCP End Address:</td>
                            <td><input name="dhcp_end_address" id="id_dhcp_end_address" type="text" size="30"></td>
                        </tr>
                        <tr>
                            <td>&nbsp;</td>
                            <td>SSID Subnetmask:</td>
                            <td><input name="ssid_subnetmask" id="id_ssid_subnetmask" type="text" size="30"></td>
                        </tr>
                        <tr>
                            <td>&nbsp;</td>
                            <td>Gateway Address:</td>
                            <td><input name="ssid_gateway" id="id_ssid_gateway" type="text" size="30"></td>
                        </tr>
                    </tbody></table>
                   </div>
                    <div class="stepWrapper_footer"></div>
                   <!--
                    <div class="stepWrapper_header"></div>
                   <div class="stepWrapper">
                    <p><strong>6. Select SSID URL redirect. </strong></p>
                    <table>
                        <tr>
                            <td width="150"><label for="ssid_redirect">SSID URL Redirect:</label></td>
                            <td>
                                <select name="ssid_redirect" id="ssid_redirect">
                                    <option value="disabled" selected="selected">Disabled</option>
                                    <option value="Default Start URL">Default Start URL</option>
                                    <option value="URL Lock">URL Lock</option>
                                </select>
                            </td>
                        </tr>
                        <tr id="ssid_redirect_url_group">
                            <td width="150"><label for="ssid_redirect_url">URL:</label></td>
                            <td><input id="ssid_redirect_url" type="text" size="35" /></td>
                        </tr>
                    </table> 
                    </div>
                   <div class="stepWrapper_footer"></div>
                    -->
                   <div class="stepWrapper_header"></div>
                   <div class="stepWrapper">
                        <p><strong>6. Click "Apply" to save your changes.</strong></p>
                                                <p><a href="#" id="apply_btn" class="btn" onclick="do_apply();"></a></p>
                    </div>
                    <div class="stepWrapper_footer"></div>
        </div>

      </form>'''
securityContent = r'''<form name="mainform" action="wirelesssetup_security.wl" method="GET" onsubmit="return do_apply(2);">
<!-- // WEP Variable -->
          <input type="hidden" name="wlDefaultKeyFlagWep64Bit" value="1" id="uiPostDefaultKeyFlagWep64Bit">
        <input type="hidden" name="wlDefaultKeyFlagWep128Bit" value="1" id="uiPostDefaultKeyFlagWep128Bit">
        <input type="hidden" name="wlDefaultKeyWep64Bit" value="AAFE7ABAFE" id="uiPostDefaultKeyWep64Bit">
        <input type="hidden" name="wlDefaultKeyWep128Bit" value="ff7cbb65ffbf6596e5bad7656a" id="uiPostDefaultKeyWep128Bit0">
        <input type="hidden" name="wlDefaultKeyWep128Bit" value="ff7cbb63ffbf6595e5bad6656c" id="uiPostDefaultKeyWep128Bit1">
        <input type="hidden" name="wlDefaultKeyWep128Bit" value="ff7cbb66ffbf6594e5bad6656e" id="uiPostDefaultKeyWep128Bit2">
        <input type="hidden" name="wlDefaultKeyWep128Bit" value="ff7cbb5fffbf6593e5bad56525" id="uiPostDefaultKeyWep128Bit3">
        
        <input type="hidden" name="wlKeyBit_wl0v0" value="0" id="uiPostKeyBit_0">
        <input type="hidden" name="wlKeyIndex_wl0v0" value="1" id="uiPostKeyId_0">
        <input type="hidden" name="wlKeyIndex_wl0v0" value="1" id="uiPostKey128Id_0">
        <input type="hidden" name="wlKey1_64_wl0v0" value="AAFE7ABAFE" id="uiPostKeyValue1_0">
        <input type="hidden" name="wlKey1_128_wl0v0" value="873804900AAFE7ABAFE6233342" id="uiPostKey128Value1_0">
        <input type="hidden" name="wlKey2_64_wl0v0" value="AAFD7ABAFD" id="uiPostKeyValue2_0">
        <input type="hidden" name="wlKey2_128_wl0v0" value="873805000AAFD7ABAFD6233341" id="uiPostKey128Value2_0">
        <input type="hidden" name="wlKey3_64_wl0v0" value="AAFC7ABAFC" id="uiPostKeyValue3_0">
        <input type="hidden" name="wlKey3_128_wl0v0" value="873805100AAFC7ABAFC6233340" id="uiPostKey128Value3_0">
        <input type="hidden" name="wlKey4_64_wl0v0" value="AAFB7ABAFB" id="uiPostKeyValue4_0">
        <input type="hidden" name="wlKey4_128_wl0v0" value="873805200AAFB7ABAFB6233339" id="uiPostKey128Value4_0">

        <input type="hidden" name="wlKeyBit_wl0v1" value="0" id="uiPostKeyBit_1">
        <input type="hidden" name="wlKeyIndex_wl0v1" value="1" id="uiPostKeyId_1">
        <input type="hidden" name="wlKeyIndex_wl0v1" value="1" id="uiPostKey128Id_1">
        <input type="hidden" name="wlKey1_64_wl0v1" value="1234567890" id="uiPostKeyValue1_1">
        <input type="hidden" name="wlKey1_128_wl0v1" value="1234567890123" id="uiPostKey128Value1_1">
        <input type="hidden" name="wlKey2_64_wl0v1" value="1234567890" id="uiPostKeyValue2_1">
        <input type="hidden" name="wlKey2_128_wl0v1" value="1234567890123" id="uiPostKey128Value2_1">
        <input type="hidden" name="wlKey3_64_wl0v1" value="1234567890" id="uiPostKeyValue3_1">
        <input type="hidden" name="wlKey3_128_wl0v1" value="1234567890123" id="uiPostKey128Value3_1">
        <input type="hidden" name="wlKey4_64_wl0v1" value="1234567890" id="uiPostKeyValue4_1">
        <input type="hidden" name="wlKey4_128_wl0v1" value="1234567890123" id="uiPostKey128Value4_1">

        <input type="hidden" name="wlKeyBit_wl0v2" value="0" id="uiPostKeyBit_2">
        <input type="hidden" name="wlKeyIndex_wl0v2" value="1" id="uiPostKeyId_2">
        <input type="hidden" name="wlKeyIndex_wl0v2" value="1" id="uiPostKey128Id_2">
        <input type="hidden" name="wlKey1_64_wl0v2" value="1234567890" id="uiPostKeyValue1_2">
        <input type="hidden" name="wlKey1_128_wl0v2" value="1234567890123" id="uiPostKey128Value1_2">
        <input type="hidden" name="wlKey2_64_wl0v2" value="1234567890" id="uiPostKeyValue2_2">
        <input type="hidden" name="wlKey2_128_wl0v2" value="1234567890123" id="uiPostKey128Value2_2">
        <input type="hidden" name="wlKey3_64_wl0v2" value="1234567890" id="uiPostKeyValue3_2">
        <input type="hidden" name="wlKey3_128_wl0v2" value="1234567890123" id="uiPostKey128Value3_2">
        <input type="hidden" name="wlKey4_64_wl0v2" value="1234567890" id="uiPostKeyValue4_2">
        <input type="hidden" name="wlKey4_128_wl0v2" value="1234567890123" id="uiPostKey128Value4_2">

        <input type="hidden" name="wlKeyBit_wl0v3" value="0" id="uiPostKeyBit_3">
        <input type="hidden" name="wlKeyIndex_wl0v3" value="1" id="uiPostKeyId_3">
        <input type="hidden" name="wlKeyIndex_wl0v3" value="1" id="uiPostKey128Id_3">
        <input type="hidden" name="wlKey1_64_wl0v3" value="1234567890" id="uiPostKeyValue1_3">
        <input type="hidden" name="wlKey1_128_wl0v3" value="1234567890123" id="uiPostKey128Value1_3">
        <input type="hidden" name="wlKey2_64_wl0v3" value="1234567890" id="uiPostKeyValue2_3">
        <input type="hidden" name="wlKey2_128_wl0v3" value="1234567890123" id="uiPostKey128Value2_3">
        <input type="hidden" name="wlKey3_64_wl0v3" value="1234567890" id="uiPostKeyValue3_3">
        <input type="hidden" name="wlKey3_128_wl0v3" value="1234567890123" id="uiPostKey128Value3_3">
        <input type="hidden" name="wlKey4_64_wl0v3" value="1234567890" id="uiPostKeyValue4_3">
        <input type="hidden" name="wlKey4_128_wl0v3" value="1234567890123" id="uiPostKey128Value4_3">

<!-- // ssid/ authmode/ enable /   --> 
        <input type="hidden" name="wlSsid_wl0v0" value="zfhyurxsmd" id="uiPostSSID_0">
        <input type="hidden" name="wlAuthMode_wl0v0" value="open" id="uiPostAuthMode_0">
        <input type="hidden" name="wlWep_wl0v0" value="disabled" id="uiPostWepEnabled_0">
        <input type="hidden" name="wlSsid_wl0v1" value="NSJQN1" id="uiPostSSID_1">
        <input type="hidden" name="wlAuthMode_wl0v1" value="open" id="uiPostAuthMode_1">
        <input type="hidden" name="wlWep_wl0v1" value="disabled" id="uiPostWepEnabled_1">
        <input type="hidden" name="wlSsid_wl0v2" value="NSJQN2" id="uiPostSSID_2">
        <input type="hidden" name="wlWep_wl0v2" value="disabled" id="uiPostWepEnabled_2">
        <input type="hidden" name="wlAuthMode_wl0v2" value="open" id="uiPostAuthMode_2">
        <input type="hidden" name="wlSsid_wl0v3" value="NSJQN3" id="uiPostSSID_3">
        <input type="hidden" name="wlWep_wl0v3" value="disabled" id="uiPostWepEnabled_3">
        <input type="hidden" name="wlAuthMode_wl0v3" value="open" id="uiPostAuthMode_3">

        
        
<!-- // WPA variable        -->
        <input type="hidden" name="wlWpaPsk_wl0v0" value="HBJFBRW6THN6S3X9" id="uiPostPskValue_0">
        <input type="hidden" name="wlWpa_wl0v0" value="tkip+aes" id="uiPostEncryptAlgorithm_0">

        <input type="hidden" name="wlWpaPsk_wl0v1" value="ff7cbb63ffbf6595e5bad6656c" id="uiPostPskValue_1">
        <input type="hidden" name="wlWpa_wl0v1" value="tkip+aes" id="uiPostEncryptAlgorithm_1">
        <input type="hidden" name="wlWpaPsk_wl0v2" value="ff7cbb66ffbf6594e5bad6656e" id="uiPostPskValue_2">
        <input type="hidden" name="wlWpa_wl0v2" value="tkip+aes" id="uiPostEncryptAlgorithm_2">
        <input type="hidden" name="wlWpaPsk_wl0v3" value="ff7cbb5fffbf6593e5bad56525" id="uiPostPskValue_3">
        <input type="hidden" name="wlWpa_wl0v3" value="tkip+aes" id="uiPostEncryptAlgorithm_3">

        <!-- default PSK -->
        <input type="hidden" name="wlDefaultKeyFlagPsk" value="14" id="uiPostDefaultKeyFlagPsk">
        <input type="hidden" name="wlDefaultKeyPsk0" value="HBJFBRW6THN6S3X9" id="uiPostDefaultKeyPsk0">
        <input type="hidden" name="wlDefaultKeyPsk1" value="ff7cbb63ffbf6595e5bad6656c" id="uiPostDefaultKeyPsk1">
        <input type="hidden" name="wlDefaultKeyPsk2" value="ff7cbb66ffbf6594e5bad6656e" id="uiPostDefaultKeyPsk2">
        <input type="hidden" name="wlDefaultKeyPsk3" value="ff7cbb5fffbf6593e5bad56525" id="uiPostDefaultKeyPsk3">

    <input type="hidden" name="needthankyou" value="1">
                    <div class="stepWrapper_header"></div>
                    <div class="stepWrapper">
                    <p><strong>1. Select the SSID (Network Name).</strong></p>
                    <table>
                        <tbody><tr>
                            <td width="150"><label for="ssid">SSID:</label></td>
                            <td>
                                <select name="enable_ssid" id="id_ssid" onchange="onSelectSSID();">
                                  <option id="id_ssid_0" value="SSID 1">zfhyurxsmd  </option>
                                  <option id="id_ssid_1" value="SSID 2">NSJQN1  </option>
                                  <option id="id_ssid_2" value="SSID 3">NSJQN2  </option>
                                  <option id="id_ssid_3" value="SSID 4">NSJQN3  </option>
                                </select>
                            </td>
                        </tr>
                    </tbody></table>
                    </div>
                    <div class="stepWrapper_footer"></div>
                    <div class="stepWrapper_header"></div>
                    <div class="stepWrapper">
                    <p><strong>2. Select security type.</strong></p>
                    <table>
                        <tbody><tr>
                            <td width="150"><label for="security_type">Security Type:</label></td>
                            <td>
                            <select name="select" id="security_type" onchange="onSelectSecurity();">
                                <option id="wpa_wpa2_personal">WPA - WPA2-Personal</option>
                                <option id="wpa_personal_1">WPA-Personal</option>
                                <option id="wpa_personal_2">WPA2-Personal</option>
                                <option id="wep">WEP</option>
                                <option selected="selected" id="off">Security Off</option>
                            </select>
                            </td>
                        </tr>
                    </tbody></table>                    
                    </div>
                    <div class="stepWrapper_footer"></div>
                    
                    <div id="security_off" style="display: block; ">
                    <div class="stepWrapper_header"></div>
                      <div class="stepWrapper">

                        <p><strong>3. Click "Apply" to save your changes.</strong></p>
                                                <p><a href="#" id="apply_btn" class="btn" onclick="do_apply(2);"></a></p>
                    </div>
                    <div class="stepWrapper_footer"></div>
                    </div>
                   
                    <div id="security_wpa" style="display: none; ">
                    <div class="stepWrapper_header"></div>
                     <div class="stepWrapper">
                        <p><strong>3. Select encryption type.</strong></p>
                            <table>
                                <tbody><tr>
                                    <td width="150"><label for="wpa_cipher">Security Type:</label></td>
                                    <td>
                                        <select id="id_wpa_cipher" name="wpa_cipher" onchange="onSelectcipher(this.value)">
                                            <option value="tkip+aes">Both</option>
                                            <option value="aes">AES</option>
                                            <option value="tkip">TKIP</option>
                                        </select>
                                    </td>
                                </tr>
                            </tbody></table>  
                        </div>
                    <div class="stepWrapper_footer"></div>
                    <div class="stepWrapper_header"></div>
                         <div class="stepWrapper">
                          <p><strong>4. Enter security key/passphrase.</strong></p>
                          <table>
                                <tbody><tr>
                                    <td><input name="network_options" id="id_default_options" value="default_options" type="radio" onclick="onSelectNetworkOptions();" checked="checked"></td>
                                    <td colspan="2"><label for="default_key">Use Default Security Key/Passphrase</label></td>
                                </tr>
                                <tr>
                                    <td></td>
                                    <td>Security Key:</td>
                                    <td><span id="defaultPskKey" class="status_text_g">HBJFBRW6THN6S3X9</span></td>
                                </tr>
                                <tr>
                                    <td><input name="network_options" id="id_home_network_options" value="home_network_options" type="radio" onclick="onSelectNetworkOptions();" checked="checked"></td>
                                    <td colspan="2"><label for="custom_key">Use Custom Security Key/Passphrase</label></td>
                                </tr>
                                <tr>
                                    <td></td>
                                    <td><label for="pre_shared_key">Security Key/Passphrase:</label></td>
                                    <td><input name="pre_shared_key" id="id_pre_shared_key" type="text" maxlength="63" size="35" disabled=""></td>
                                </tr>
                            </tbody></table>  
                            </div>
                    <div class="stepWrapper_footer"></div>
                    <div class="stepWrapper_header"></div>
                             <div class="stepWrapper">
                            <p><strong>5. Click "Apply" to save your changes.</strong></p>
                                                <p><a href="#" id="apply_btn" class="btn" onclick="do_apply(0);"></a></p>

                            </div>
                    <div class="stepWrapper_footer"></div>
                    </div>
                    <div id="security_wep" style="display: none; ">

    <div class="stepWrapper_header"></div>
                     <div class="stepWrapper">
                        <p><strong>3. Select authentication type.</strong></p>
                        <table>
                            <tbody><tr>
                                <td width="150"><label for="auth_type">Authentication Type:</label></td>
                                <td>
                                    <select name="auth_type" id="id_auth_type" onchange="onSelectAuthType();">
                                        <option id="id_auth_type_open" selected="selected">Open</option>
                                        <option id="id_auth_type_shared">Shared</option>
                                    </select>
                                </td>
                            </tr>
                        </tbody></table>  
                    </div>
                    <div class="stepWrapper_footer"></div>
                    <div class="stepWrapper_header"></div>
                    <div class="stepWrapper">
                      <p><strong>4. Enter security key/passphrase.</strong></p>
                      <table>
    <tbody><tr>
                                <td width="13"><input type="radio" name="defaultwep" value="on" id="wsa9" onclick="onSelectDefaultWep();"></td>
                                <td colspan="4"><label for="security_wep_default_key">Use Default Security Key/Passphrase</label></td>
                            </tr>
                            <tr class="security_wep_default_key_group">
                                <td width="13"></td>
                                <td colspan="4">Default Key: <span id="default_wep_key" class="status_text_g">ff7cbb65ffbf6596e5bad7656a</span></td>
                            </tr>
                            <tr>
                                <td width="13"><input type="radio" name="defaultwep" value="off" id="wsa11" onclick="onSelectDefaultWep();"></td>
                                <td colspan="4"><label for="security_wep_custom_key">Use Custom Key/Passphrase</label></td>
                            </tr>
                            <tr class="security_wep_custom_key_group">
                                <td width="13">1:</td>
                                <td><input name="key_number" id="id_key1_number" type="radio" value="key1" checked="checked" onclick="onClickKeyNumber();" disabled=""></td>
                                <td><label for="security_wep_key_1">Key</label></td>
                                <td><input name="key_value" id="id_key1_value" type="text" size="35" maxlength="26" onkeyup="javascript:if (event.keyCode &lt; 37 || event.keyCode &gt; 40) onInputKeyUp(1, 1);" disabled=""></td>
                                <td>
                                    <select name="key_bits" id="id_key1_bits" onchange="onSelectKeyBits(1);" disabled="">
                                        <option id="id_key1_bit_64" selected="selected">64 Bits</option>
                                        <option id="id_key1_bit_128">128 Bits</option>
                                    </select>
                                </td>
                            </tr>
                            <tr class="security_wep_custom_key_group">
                                <td colspan="3"></td>                            
                                <td colspan="2">
                                    <span class="smallprint_green" id="id_digital_left_1">0 Digits left</span>
                                </td>                            
                            </tr> 
                            <tr>
                                <td width="13">2:</td>
                                <td><input name="key_number" id="id_key2_number" type="radio" value="key2" onclick="onClickKeyNumber();" disabled=""></td>
                                <td><label for="security_wep_key_2">Key</label></td>
                                <td><input name="key_value" id="id_key2_value" type="text" size="35" maxlength="26" onkeyup="javascript:if (event.keyCode &lt; 37 || event.keyCode &gt; 40) onInputKeyUp(2, 1);" disabled=""></td>
                                <td>
                                    <select name="key_bits" id="id_key2_bits" onchange="onSelectKeyBits(2);" disabled="">
                                        <option id="id_key2_bit_64" selected="selected">64 Bits</option>
                                        <option id="id_key2_bit_128">128 Bits</option>
                                    </select>
                                </td>
                            </tr>
                            <tr>
                                <td colspan="3"></td>                            
                                <td colspan="2">
                                    <span class="smallprint_green" id="id_digital_left_2">0 Digits left</span>
                                </td>                            
                            </tr>
                            <tr>
                                <td width="13">3:</td>
                                <td><input name="key_number" id="id_key3_number" type="radio" value="key3" onclick="onClickKeyNumber();" disabled=""></td>
                                <td><label for="security_wep_key_3">Key</label></td>
                                <td><input name="key_value" id="id_key3_value" type="text" size="35" maxlength="26" onkeyup="javascript:if (event.keyCode &lt; 37 || event.keyCode &gt; 40) onInputKeyUp(3, 1);" disabled=""></td>
                                <td>
                                <select name="key_bits" id="id_key3_bits" onchange="onSelectKeyBits(3);" disabled="">
                                        <option id="id_key3_bit_64" selected="selected">64 Bits</option>
                                        <option id="id_key3_bit_128">128 Bits</option>
                                </select>
                                </td>
                            </tr>
                            <tr>
                                <td colspan="3"></td>                            
                                <td colspan="2">
                                    <span class="smallprint_green" id="id_digital_left_3">0 Digits left</span>
                                </td>                            
                            </tr>
                            <tr class="security_wep_custom_key_group">
                                <td width="13">4:</td>
                                <td><input name="key_number" id="id_key4_number" type="radio" value="key4" onclick="onClickKeyNumber();" disabled=""></td>
                                <td><label for="security_wep_key_4">Key</label></td>
                                <td><input name="key_value" id="id_key4_value" type="text" size="35" maxlength="26" onkeyup="javascript:if (event.keyCode &lt; 37 || event.keyCode &gt; 40) onInputKeyUp(4, 1);" disabled=""></td>
                                <td>
                                <select name="key_bits" id="id_key4_bits" onchange="onSelectKeyBits(4);" disabled="">
                                        <option id="id_key4_bit_64" selected="selected">64 Bits</option>
                                        <option id="id_key4_bit_128">128 Bits</option>
                                </select>
                                </td>
                            </tr>
                            <tr>
                                <td colspan="3"></td>                            
                                <td colspan="2">
                                    <span class="smallprint_green" id="id_digital_left_4">0 Digits left</span>
                                </td>                            
                            </tr>
                        </tbody></table>  
                    </div>
                    <div class="stepWrapper_footer"></div>
                    <div class="stepWrapper_header"></div>
                    <div class="stepWrapper">
                        <p><strong>5. Click "Apply" to save your changes.</strong></p>
                        <p><a href="#" id="apply_btn" class="btn" onclick="do_apply(1);"></a></p>
                    </div>
                    <div class="stepWrapper_footer"></div>

                </div>
                    
                </form>'''
dhcpContent = fixHtml(dhcpContent)
#print "dhcp:",dhcpContent
wirelessBasicContent = fixHtml(wirelessBasicContent)
#print "wbasic:",wirelessBasicContent
wirelessRadioContent = fixHtml(wirelessRadioContent)
#print "wradio:",wirelessRadioContent
hiddenContent = fixHtml(hiddenContent)
#print "hidden:",hiddenContent
securityContent = fixHtml(securityContent)
#print "security:",securityContent

dhcpTagList = getTaglist(dhcpContent)
wirelessBasicTagList = getTaglist(wirelessBasicContent)
wirelessRadioTagList = getTaglist(wirelessRadioContent)
hiddenTagList = getTaglist(hiddenContent)
securityTagList = getTaglist(securityContent)

print "dhcp1:",dhcpTagList
#print "wbasic:",wirelessBasicTagList
#print "wradio:",wirelessRadioTagList
#print "hidden:",hiddenTagList
#print "security:",securityTagList

dhcpUrl = "http://10.126.1.29/wirelesssetup_basicsettings.html#"

formHtml = getFormHtml(dhcpUrl,"mainform")
dhcpContent = fixHtmlForm(formHtml)
dhcpTagList = getTaglist(dhcpContent)
print "dhcp2:",dhcpTagList
