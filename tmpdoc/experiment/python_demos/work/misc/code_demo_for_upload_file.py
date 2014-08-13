# Copyright (c) 2011-2012 lab126.com
# See COPYING for details.
import base64
import urllib2
import itertools
import mimetools
import mimetypes

from core import WifiTerms
from core.ap.base2.ap import ApBase
from core.utils.exceptions import ACSValueError
from core.db.provider import Provider
from core.driver.log import LevelLog
from core.utils.ap_utils import ApUtils

class CISCO_BASE_POST(ApBase):

    def __init__(self, model):
        ApBase.__init__(self, model)

        self.tag    = self.__class__.__name__
        self.logger = LevelLog(self.tag)
        self.apUtils       = ApUtils()

        self.band   = WifiTerms.BAND_2G

        user, password, lan_ip = Provider.getInstance().getApLogin(model)
        if( user == None or lan_ip == None):
            raise Exception("NOT find lan_ip for %s" % (model))
        setattr(self, 'user', user)
        setattr(self, 'password', password)
        setattr(self, 'lan_ip', lan_ip)

        #Use wepConverted to indicate that password converted from 5/13 bits,
        #in case getSecurity return wrong result if converted.
        #deprecated
        self.wepConverted2G = False
        self.wepConverted5G = False


    def connect(self):
        self.logger.enter("connect enter.")
        self.getDriver().connect(self.lan_ip, self.user, self.password)
        self.logger.leave("connnect leave.")


    def disconnect(self):
        self.logger.enter("disconnect enter.")
        self.disconnectCallback()
        self.getDriver().disconnect()
        self.logger.leave("disconnect leave.")


    def setBand(self, band):
        self.logger.enter('setBand band=%s' % band)
        if band not in ( WifiTerms.BAND_2G, WifiTerms.BAND_5G ):
            self.logger.leave('setBand leave EXPT')
            raise ACSValueError(' NotSupportBand_%s' % band)
        self.band = band
        self.logger.leave('setBand leave.')


    def getBand(self):
        self.logger.debug('getBand return = "%s"' % self.band)
        return self.band


    def setWirelessMode(self, mode):
        self.logger.enter('setWirelessMode. mode=%s' % mode)

        config = None
        if self.band == WifiTerms.BAND_2G:
            config = self._setWirelessMode2G(mode)

        elif self.band == WifiTerms.BAND_5G:
            config = self._setWirelessMode5G(mode)

        else:
            self.logger.leave('setWirelessMode leave EXPT')
            raise ACSValueError("invalid band:'%s'" % self.band)

        self.logger.leave('setWirelessMode.')
        return config


    def _setWirelessMode2G(self, mode):
        config = self.getLocalConfig('setWirelessMode')
        configItem = self.getModel().getWirelessMode2G(mode)
        config.setWirelessMode(configItem)
        return config


    def _setWirelessMode5G(self, mode):
        config = self.getLocalConfig('setWirelessMode')
        configItem = self.getModel().getWirelessMode5G(mode)
        config.setWirelessMode(configItem)
        return config


    def getWirelessMode(self):
        self.logger.enter('getWirelessMode enter.')

        term = None
        if self.band == WifiTerms.BAND_2G:
            term = self._getWirelessMode2G()

        elif self.band == WifiTerms.BAND_5G:
            term = self._getWirelessMode5G()
        else:
            self.logger.leave('getWirelessMode leave EXPT')
            raise ACSValueError("invalid band:'%s'" % self.band)

        self.logger.leave('getWirelessMode leave. return="%s"' % (term))
        return term


    def _getWirelessMode2G(self):
        wirelessMode2gItem = self.getModel().getWirelessMode2G(None)
        term = self.getWifiTermByModel("getWirelessMode", "setWirelessMode", wirelessMode2gItem)
        return term


    def _getWirelessMode5G(self):
        wirelessMode5gItem = self.getModel().getWirelessMode5G(None)
        term = self.getWifiTermByModel("getWirelessMode", "setWirelessMode", wirelessMode5gItem)
        return term


    def getRemoteWirelessMode(self):
        self.logger.enter('getRemoteWirelessMode enter.')

        term = None
        if self.band == WifiTerms.BAND_2G:
            term = self._getRemoteWirelessMode2G()

        elif self.band == WifiTerms.BAND_5G:
            term = self._getRemoteWirelessMode5G()
        else:
            self.logger.leave('getRemoteWirelessMode leave EXPT')
            raise ACSValueError("invalid band:'%s'" % self.band)

        self.logger.leave('getRemoteWirelessMode leave. return="%s"' % (term))
        return term


    def _getRemoteWirelessMode2G(self):
        wirelessMode2gItem = self.getModel().getWirelessMode2G(None)
        term = self.getRemoteWifiTermByModel("getWirelessMode", wirelessMode2gItem)
        return term


    def _getRemoteWirelessMode5G(self):
        wirelessMode5gItem = self.getModel().getWirelessMode5G(None)
        term = self.getRemoteWifiTermByModel("getWirelessMode", wirelessMode5gItem)
        return term


    def setChannelWidth(self, channelWidth):
        self.logger.enter('setChannelWidth. width=%s' % channelWidth)

        config = None
        if self.band == WifiTerms.BAND_2G:
            config = self._setChannelWidth2G(channelWidth)
        elif self.band == WifiTerms.BAND_5G:
            config = self._setChannelWidth5G(channelWidth)
        else:
            self.logger.leave('setChannelWidth leave EXPT')
            raise ACSValueError("invalid parameter for band:'%s'." % (self.band))

        self.logger.leave('setChannelWidth leave.')
        return config


    def _setChannelWidth2G(self, channelWidth):
        config = None
        wirelessMode = self._getWirelessMode2G()
        if (wirelessMode == WifiTerms.WIRELESS_MODE_N \
                or wirelessMode == WifiTerms.WIRELESS_MODE_MIXED \
                or wirelessMode == WifiTerms.WIRELESS_MODE_GN):
            config = self._setNChannelWidth(channelWidth)

        else:
            config = self._setChannelWidth(channelWidth)

        return config


    def _setChannelWidth5G(self, channelWidth):
        config = None
        wirelessMode = self._getWirelessMode5G()

        if (wirelessMode == WifiTerms.WIRELESS_MODE_N \
                or wirelessMode == WifiTerms.WIRELESS_MODE_MIXED):
            config = self._setNChannelWidth(channelWidth)

        else:
            config = self._setChannelWidth(channelWidth)

        return config


    def _setNChannelWidth(self, channelWidth):
        config = self.getLocalConfig('setChannelWidth')
        if self.band == WifiTerms.BAND_2G:
            configItem = self.getModel().getNChannelWidth2G(channelWidth)
            config.setChannelWidth(configItem)

        elif self.band == WifiTerms.BAND_5G:
            configItem = self.getModel().getNChannelWidth5G(channelWidth)
            config.setChannelWidth(configItem)

        else:
            raise ACSValueError("invalid parameter for band:'%s'." % (self.band))

        return config


    def _setChannelWidth(self, channelWidth):
        config = self.getLocalConfig('setChannelWidth')
        if self.band == WifiTerms.BAND_2G:
            configItem = self.getModel().getChannelWidth2G(channelWidth)
            config.setChannelWidth(configItem)

        elif self.band == WifiTerms.BAND_5G:
            configItem = self.getModel().getChannelWidth5G(channelWidth)
            config.setChannelWidth(configItem)

        else:
            raise ACSValueError("invalid parameter for band:'%s'." % (self.band))

        return config


    def getChannelWidth(self):
        self.logger.enter('getChannelWidth enter.')

        term =None
        if self.band == WifiTerms.BAND_2G:
            term = self._getChannelWidth2G()

        elif self.band == WifiTerms.BAND_5G:
            term = self._getChannelWidth5G()

        else:
            self.logger.leave('getChannelWidth leave EXPT')
            raise ACSValueError("invalid band:'%s'" % self.band)

        self.logger.leave('getChannelWidth leave. return="%s"' % term)
        return term


    def _getChannelWidth2G(self):
        term = None
        wirelessMode = self._getWirelessMode2G()

        if (wirelessMode == WifiTerms.WIRELESS_MODE_N \
                or wirelessMode == WifiTerms.WIRELESS_MODE_MIXED \
                or wirelessMode == WifiTerms.WIRELESS_MODE_GN):
            term = self._getNChannelWidth2G()

        elif wirelessMode == WifiTerms.WIRELESS_MODE_D:
            #Some cisco ap (e.g. e1000) with disable mode can have N channelwith item, some don't (e.g. e3000),
            #so we treate disable as N mode channelwidth because it contains the NonN item.
            term = self._getNChannelWidth2G()

        else:
            term = self._getNonNChannelWidth2G()

        return term


    def _getChannelWidth5G(self):
        term = None
        wirelessMode = self._getWirelessMode5G()

        if (wirelessMode == WifiTerms.WIRELESS_MODE_N \
                or wirelessMode == WifiTerms.WIRELESS_MODE_MIXED):
            term = self._getNChannelWidth5G()

        elif wirelessMode == WifiTerms.WIRELESS_MODE_D:
            #In case some cisco ap with disable mode can have N channelwith item, some don't as 2g mode,
            #so we treate disable as N mode channelwidth because it contains the NonN item.
            term = self._getNChannelWidth5G()

        else:
            term = self._getNonNChannelWidth5G()

        return term


    def _getNChannelWidth2G(self):
        channelwidth2gItem = self.getModel().getNChannelWidth2G(None)
        term = self.getWifiTermByModel("getChannelWidth", "setChannelWidth", channelwidth2gItem)

        return term


    def _getNChannelWidth5G(self):
        channelWidth5gItem = self.getModel().getNChannelWidth5G(None)
        term = self.getWifiTermByModel("getWirelessMode", "setWirelessMode", channelWidth5gItem)

        return term


    def _getNonNChannelWidth2G(self):
        channelwidth2gItem = self.getModel().getChannelWidth2G(None)
        term = self.getWifiTermByModel("getChannelWidth", "setChannelWidth", channelwidth2gItem)

        return term


    def _getNonNChannelWidth5G(self):
        channelWidth5gItem = self.getModel().getChannelWidth5G(None)
        term = self.getWifiTermByModel("getWirelessMode", "setWirelessMode", channelWidth5gItem)

        return term


    def setChannel(self, channel):
        self.logger.enter('setChannel. channel=%s' % channel)

        config = None
        if self.band == WifiTerms.BAND_2G:
            config = self._setChannel2G(channel)

        elif self.band == WifiTerms.BAND_5G:
            config = self._setChannel5G(channel)

        else:
            self.logger.leave('setChannel leave EXPT')
            raise ACSValueError("invalid band:'%s'" % self.band)

        self.logger.leave('setChannel leave.')
        return config


    def _setChannel2G(self, channel):
        config = self.getLocalConfig('setChannel')

        configItem = self.getModel().getChannel2G(channel)
        config.setChannel(configItem)

        return config


    def _setChannel5G(self, channel):
        config = self.getLocalConfig('setChannel')

        configItem = self.getModel().getChannel5G(channel)
        config.setChannel(configItem)

        return config


    def getChannel(self):
        self.logger.enter('getChannel enter.')

        term = None
        if self.band == WifiTerms.BAND_2G:
            term = self._getChannel2G()

        elif self.band == WifiTerms.BAND_5G:
            term = self._getChannel5G()

        else:
            self.logger.leave('getChannel leave EXPT')
            raise ACSValueError("invalid band:'%s'" % self.band)

        self.logger.leave('getChannel leave. return="%s"' % term)
        return term


    def _getChannel2G(self):
        channel2gItem = self.getModel().getChannel2G(None)
        term = self.getWifiTermByModel("getChannel", "setChannel", channel2gItem)
        return term


    def _getChannel5G(self):
        channel5gItem = self.getModel().getChannel5G(None)
        term = self.getWifiTermByModel("getChannel", "setChannel", channel5gItem)
        return term


    def setDHCP(self, cmd):
        self.logger.enter('setDHCP cmd=%s' % cmd)

        config = self.getLocalConfig('setDHCP')
        configItem = self.getModel().getDHCP(cmd)
        config.setDHCP(configItem)

        self.logger.leave('setDHCP leave')
        return config


    def getDHCP(self):
        self.logger.enter('getDHCP enter.')

        dhcpItem = self.getModel().getDHCP(None)
        term = self.getWifiTermByModel("getDHCP", "setDHCP", dhcpItem)

        self.logger.leave("getDHCP leave. return '%s'" % (term))
        return term


    def setRadio(self, cmd):
        self.logger.enter('setRadio enter. cmd=%s' % cmd)

        config = None
        if self.band == WifiTerms.BAND_2G:
            config = self._setRadio2G(cmd)

        elif self.band == WifiTerms.BAND_5G:
            config = self._setRadio5G(cmd)

        else:
            self.logger.leave('setRadio leave EXPT')
            raise ACSValueError("invalid band:'%s'" % self.band)

        self.logger.leave('setRadio leave. cmd=%s' % cmd)
        return config


    def _setRadio2G(self, cmd):
        if( cmd == WifiTerms.ENABLED ):
            config = self._setWirelessMode2G(WifiTerms.WIRELESS_MODE_MIXED)

        else:
            config = self._setWirelessMode2G(WifiTerms.WIRELESS_MODE_D)

        return config


    def _setRadio5G(self, cmd):
        if( cmd == WifiTerms.ENABLED ):
            config = self._setWirelessMode5G(WifiTerms.WIRELESS_MODE_MIXED)

        else:
            config = self._setWirelessMode5G(WifiTerms.WIRELESS_MODE_D)

        return config


    def getRadio(self):
        self.logger.enter('getRadio enter.')

        radioStatus = None
        if self.band == WifiTerms.BAND_2G:
            radioStatus = self._getRadio2G()

        elif self.band == WifiTerms.BAND_5G:
            radioStatus = self._getRadio5G()

        else:
            self.logger.leave('getRadio leave EXPT')
            raise ACSValueError("invalid band:'%s'" % self.band)

        self.logger.leave('getRadio leave. return="%s"' % radioStatus)
        return radioStatus


    def _getRadio2G(self):
        wirelessMode = self._getWirelessMode2G()
        if( wirelessMode is None ):
            raise Exception("can not get wirelessMode.")

        radioStatus = WifiTerms.DISABLED
        if( wirelessMode != WifiTerms.WIRELESS_MODE_D ):
            radioStatus = WifiTerms.ENABLED

        return radioStatus


    def _getRadio5G(self):
        wirelessMode = self._getWirelessMode5G()
        if( wirelessMode is None ):
            raise Exception("can not get wirelessMode.")

        radioStatus = WifiTerms.DISABLED
        if( wirelessMode != WifiTerms.WIRELESS_MODE_D ):
            radioStatus = WifiTerms.ENABLED

        return radioStatus


    def setSSID(self, ssid):
        self.logger.enter('setSSID: "%s"' % ssid)

        config = self.getLocalConfig('setSSID')
        if self.band == WifiTerms.BAND_2G:
            config = self._setSSID2G(ssid)

        elif self.band == WifiTerms.BAND_5G:
            config = self._setSSID5G(ssid)

        else:
            self.logger.leave('setSSID leave EXPT')
            raise ACSValueError("invalid band:'%s'" % self.band)

        self.logger.leave('setSSID leave')
        return config


    def _setSSID2G(self, ssid):
        config = self.getLocalConfig('setSSID')
        ssid = self.getModel().getSSID2G(ssid)
        config.setSSID(ssid)
        return config


    def _setSSID5G(self, ssid):
        config = self.getLocalConfig('setSSID')
        ssid = self.getModel().getSSID5G(ssid)
        config.setSSID(ssid)
        return config


    def getSSID(self):
        self.logger.enter('getSSID')

        term = None
        if self.band == WifiTerms.BAND_2G:
            term = self._getSSID2G()

        elif self.band == WifiTerms.BAND_5G:
            term = self._getSSID5G()

        else:
            self.logger.leave('getSSID leave EXPT')
            raise ACSValueError("invalid band:'%s'" % self.band)

        self.logger.leave('getSSID. return="%s"' % term)
        return term


    def _getSSID2G(self):
        ssid2gItem = self.getModel().getSSID2G(None)
        term = self.getWifiTermByModel("getSSID", "setSSID", ssid2gItem)
        return term


    def _getSSID5G(self):
        ssid5gItem = self.getModel().getSSID5G(None)
        term = self.getWifiTermByModel("getSSID", "setSSID", ssid5gItem)
        return term


    def setSecurity(self, securityTerm, encryptionTerm, passwordTerm):
        self.logger.enter('setSecurity securityTerm=%s encryptionTerm=%s passwordTerm=%s' % (securityTerm, encryptionTerm, passwordTerm))

        config = None
        if self.band == WifiTerms.BAND_2G:
            config = self._setSecurity2G(securityTerm, encryptionTerm, passwordTerm)

        elif self.band == WifiTerms.BAND_5G:
            config = self._setSecurity5G(securityTerm, encryptionTerm, passwordTerm)

        else:
            self.logger.leave('setSecurity leave EXPT')
            raise ACSValueError("invalid band:'%s'" % self.band)

        self.logger.leave('setSecurity leave')
        return config


    def _setSecurity2G(self, securityTerm, encryptionTerm, passwordTerm):
        if( WifiTerms.SECURITY_WEP == securityTerm ):
            config = self._setSecurityWEP2G(securityTerm , encryptionTerm , passwordTerm)

        elif( securityTerm == WifiTerms.SECURITY_WPA):
            config = self._setSecurityWPA2G(securityTerm , encryptionTerm , passwordTerm)

        elif( securityTerm == WifiTerms.SECURITY_WPA2 ):
            config = self._setSecurityWPA22G(securityTerm , encryptionTerm , passwordTerm)

        elif( securityTerm == WifiTerms.SECURITY_WPA2_WPA):
            config = self._setSecurityWPA2WPA2G(securityTerm , encryptionTerm , passwordTerm)

        elif( securityTerm == WifiTerms.SECURITY_D):
            config = self._setSecurityDisable2G(securityTerm)

        else:
            raise ACSValueError("Not support securityTerm mode: '%s', only support:'%s' " % (securityTerm, [
                                 WifiTerms.SECURITY_WEP,
                                 WifiTerms.SECURITY_WPA,
                                 WifiTerms.SECURITY_WPA2,
                                 WifiTerms.SECURITY_WPA2_WPA, ]))

        return config


    def _setSecurity5G(self, securityTerm, encryptionTerm, passwordTerm):
        if( WifiTerms.SECURITY_WEP == securityTerm ):
            config = self._setSecurityWEP5G(securityTerm , encryptionTerm , passwordTerm)

        elif( securityTerm == WifiTerms.SECURITY_WPA):
            config = self._setSecurityWPA5G(securityTerm , encryptionTerm , passwordTerm)

        elif( securityTerm == WifiTerms.SECURITY_WPA2 ):
            config = self._setSecurityWPA25G(securityTerm , encryptionTerm , passwordTerm)

        elif( securityTerm == WifiTerms.SECURITY_WPA2_WPA):
            config = self._setSecurityWPA2WPA5G(securityTerm , encryptionTerm , passwordTerm)

        elif( securityTerm == WifiTerms.SECURITY_D):
            config = self._setSecurityDisable5G(securityTerm)

        else:
            raise ACSValueError("Not support securityTerm mode: '%s', only support:'%s' " % (securityTerm, [
                                 WifiTerms.SECURITY_WEP,
                                 WifiTerms.SECURITY_WPA,
                                 WifiTerms.SECURITY_WPA2,
                                 WifiTerms.SECURITY_WPA2_WPA, ]))

        return config


    def _setSecurityDisable2G(self, security):
        wirelessMode = self._getWirelessMode2G()

        if wirelessMode == WifiTerms.WIRELESS_MODE_N:
            securityItem = self.getModel().getNSecurity2G(security)

        else :
            securityItem = self.getModel().getSecurity2G(security)

        config = self.getLocalConfig('setSecurity')
        config.setSecurity(securityItem, None, None)
        return config


    def _setSecurityDisable5G(self, security):
        wirelessMode = self._getWirelessMode5G()

        if wirelessMode == WifiTerms.WIRELESS_MODE_N:
            securityItem = self.getModel().getNSecurity5G(security)

        else :
            securityItem = self.getModel().getSecurity5G(security)

        config = self.getLocalConfig('setSecurity')
        config.setSecurity(securityItem, None, None)
        return config


    def _setSecurityWEP2G(self, security, encryption, password):
        wirelessMode = self._getWirelessMode2G()
        self.wepConverted2G = False
        if (encryption == WifiTerms.ENCRYPTION_WEP64 and len(password) == 5) \
            or (encryption == WifiTerms.ENCRYPTION_WEP128 and len(password) == 13):
            convertedPassword = self.apUtils.convertHex(password)
            self.logger.debug('convert wep key %s to %s as cisco ap cannot use ascii wep key.' % (password, convertedPassword))
            password = convertedPassword
            self.wepConverted2G = True

        if wirelessMode == WifiTerms.WIRELESS_MODE_N:
            securityItem = self.getModel().getNSecurity2G(security)
            encryptionItem, passwordItem = self.getModel().getWEPSecurityInfo2G(encryption, password)

        else:
            securityItem = self.getModel().getSecurity2G(security)
            encryptionItem, passwordItem = self.getModel().getWEPSecurityInfo2G(encryption, password)

        config = self.getLocalConfig('setSecurity')
        config.setSecurity(securityItem, encryptionItem, passwordItem)

        return config


    def _setSecurityWEP5G(self, security, encryption, password):
        wirelessMode = self._getWirelessMode5G()
        self.wepConverted5G = False
        if (encryption == WifiTerms.ENCRYPTION_WEP64 and len(password) == 5) \
            or (encryption == WifiTerms.ENCRYPTION_WEP128 and len(password) == 13):
            convertedPassword = self.apUtils.convertHex(password)
            self.logger.debug('convert wep key %s to %s as cisco ap cannot use ascii wep key.' % (password, convertedPassword))
            password = convertedPassword
            self.wepConverted5G = True

        if wirelessMode == WifiTerms.WIRELESS_MODE_N:
            securityItem = self.getModel().getNSecurity5G(security)
            encryptionItem, passwordItem = self.getModel().getWEPSecurityInfo5G(encryption, password)

        else:
            securityItem = self.getModel().getSecurity5G(security)
            encryptionItem, passwordItem = self.getModel().getWEPSecurityInfo5G(encryption, password)

        config = self.getLocalConfig('setSecurity')
        config.setSecurity(securityItem, encryptionItem, passwordItem)

        return config


    def _setSecurityWPA2G(self, security, encryption, password):
        wirelessMode = self._getWirelessMode2G()

        if wirelessMode == WifiTerms.WIRELESS_MODE_N:
            securityItem = self.getModel().getNSecurity2G(security)
            encryptionItem, passwordItem = self.getModel().getWPASecurityInfo2G(encryption, password)

        else:
            securityItem = self.getModel().getSecurity2G(security)
            encryptionItem, passwordItem = self.getModel().getWPASecurityInfo2G(encryption, password)

        config = self.getLocalConfig('setSecurity')
        config.setSecurity(securityItem, encryptionItem, passwordItem)

        return config


    def _setSecurityWPA5G(self, security, encryption, password):
        wirelessMode = self._getWirelessMode5G()

        if wirelessMode == WifiTerms.WIRELESS_MODE_N:
            securityItem = self.getModel().getNSecurity5G(security)
            encryptionItem, passwordItem = self.getModel().getWPASecurityInfo5G(encryption, password)

        else:
            securityItem = self.getModel().getSecurity5G(security)
            encryptionItem, passwordItem = self.getModel().getWPASecurityInfo5G(encryption, password)

        config = self.getLocalConfig('setSecurity')
        config.setSecurity(securityItem, encryptionItem, passwordItem)

        return config


    def _setSecurityWPA22G(self, security, encryption, password):
        wirelessMode = self._getWirelessMode2G()

        if wirelessMode == WifiTerms.WIRELESS_MODE_N:
            securityItem = self.getModel().getNSecurity2G(security)
            encryptionItem, passwordItem = self.getModel().getWPA2SecurityInfo2G(encryption, password)

        else:
            securityItem = self.getModel().getSecurity2G(security)
            encryptionItem, passwordItem = self.getModel().getWPA2SecurityInfo2G(encryption, password)

        config = self.getLocalConfig('setSecurity')
        config.setSecurity(securityItem, encryptionItem, passwordItem)

        return config


    def _setSecurityWPA25G(self, security, encryption, password):
        wirelessMode = self._getWirelessMode5G()

        if wirelessMode == WifiTerms.WIRELESS_MODE_N:
            securityItem = self.getModel().getNSecurity5G(security)
            encryptionItem, passwordItem = self.getModel().getWPA2SecurityInfo5G(encryption, password)

        else:
            securityItem = self.getModel().getSecurity5G(security)
            encryptionItem, passwordItem = self.getModel().getWPA2SecurityInfo5G(encryption, password)

        config = self.getLocalConfig('setSecurity')
        config.setSecurity(securityItem, encryptionItem, passwordItem)

        return config


    def _setSecurityWPA2WPA2G(self, security, encryption, password):
        wirelessMode = self._getWirelessMode2G()

        if wirelessMode == WifiTerms.WIRELESS_MODE_N:
            securityItem = self.getModel().getNSecurity2G(security)
            encryptionItem, passwordItem = self.getModel().getWPA2WPASecurityInfo2G(encryption, password)

        else:
            securityItem = self.getModel().getSecurity2G(security)
            encryptionItem, passwordItem = self.getModel().getWPA2WPASecurityInfo2G(encryption, password)

        config = self.getLocalConfig('setSecurity')
        config.setSecurity(securityItem, encryptionItem, passwordItem)

        return config


    def _setSecurityWPA2WPA5G(self, security, encryption, password):
        wirelessMode = self._getWirelessMode5G()

        if wirelessMode == WifiTerms.WIRELESS_MODE_N:
            securityItem = self.getModel().getNSecurity5G(security)
            encryptionItem, passwordItem = self.getModel().getWPA2WPASecurityInfo5G(encryption, password)

        else:
            securityItem = self.getModel().getSecurity5G(security)
            encryptionItem, passwordItem = self.getModel().getWPA2WPASecurityInfo5G(encryption, password)

        config = self.getLocalConfig('setSecurity')
        config.setSecurity(securityItem, encryptionItem, passwordItem)

        return config


    def getSecurity(self):
        self.logger.enter('getSecurity enter.')

        if self.band == WifiTerms.BAND_2G:
            securityTerm, encryptionTerm , passwordTerm = self._getSecurity2G()
        elif self.band == WifiTerms.BAND_5G:
            securityTerm, encryptionTerm , passwordTerm = self._getSecurity5G()

        else:
            self.logger.leave('getSecurity leave EXPT')
            raise ACSValueError("invalid band:'%s'" % self.band)

        self.logger.leave('getSecurity leave. security:%s, encryptionTerm:%s, passwordTerm:%s'
                          % (securityTerm, encryptionTerm, passwordTerm))
        return (securityTerm , encryptionTerm , passwordTerm)


    def _getSecurity2G(self):
        wirelessMode = self._getWirelessMode2G()

        if wirelessMode == WifiTerms.WIRELESS_MODE_N:
            securityItem = self.getModel().getNSecurity2G(None)
            securityTerm  = self.getWifiTermByModel("getSecurity", "setSecurity", securityItem)
            encryptionTerm , passwordTerm = self._getEncryptionInfo2G(securityTerm)

        else:
            securityItem = self.getModel().getSecurity2G(None)
            securityTerm  = self.getWifiTermByModel("getSecurity", "setSecurity", securityItem)
            encryptionTerm , passwordTerm = self._getEncryptionInfo2G(securityTerm)

        return (securityTerm , encryptionTerm , passwordTerm)


    def _getSecurity5G(self):
        wirelessMode = self._getWirelessMode5G()

        if wirelessMode == WifiTerms.WIRELESS_MODE_N:
            securityItem = self.getModel().getNSecurity5G(None)
            securityTerm  = self.getWifiTermByModel("getSecurity", "setSecurity", securityItem)
            encryptionTerm , passwordTerm = self._getEncryptionInfo5G(securityTerm)

        else:
            securityItem = self.getModel().getSecurity5G(None)
            securityTerm  = self.getWifiTermByModel("getSecurity", "setSecurity", securityItem)
            encryptionTerm , passwordTerm = self._getEncryptionInfo5G(securityTerm)

        return (securityTerm , encryptionTerm , passwordTerm)


    def _getEncryptionInfo2G(self, securityTerm):
        if( securityTerm == WifiTerms.SECURITY_WEP ):
            encryptionItem, passwordItem = self.getModel().getWEPSecurityInfo2G(None, None)
            encryptionTerm = self.getWifiTermByModel("getSecurity", "setSecurity", encryptionItem)
            passwordTerm   = self.getWifiTermByModel("getSecurity", "setSecurity", passwordItem)
            return (encryptionTerm, passwordTerm)

        elif( securityTerm == WifiTerms.SECURITY_WPA ):
            encryptionItem, passwordItem = self.getModel().getWPASecurityInfo2G(None, None)
            if encryptionItem is not None:
                encryptionTerm = self.getWifiTermByModel("getSecurity", "setSecurity", encryptionItem)
                passwordTerm   = self.getWifiTermByModel("getSecurity", "setSecurity", passwordItem)
                return ( encryptionTerm , passwordTerm)
            else:
                passwordTerm   = self.getWifiTermByModel("getSecurity", "setSecurity", passwordItem)
                return ( None , passwordTerm)

        elif( securityTerm == WifiTerms.SECURITY_WPA2 ):
            encryptionItem, passwordItem = self.getModel().getWPA2SecurityInfo2G(None, None)
            if encryptionItem is not None:
                encryptionTerm = self.getWifiTermByModel("getSecurity", "setSecurity", encryptionItem)
                passwordTerm   = self.getWifiTermByModel("getSecurity", "setSecurity", passwordItem)
                return ( encryptionTerm , passwordTerm)
            else:
                passwordTerm   = self.getWifiTermByModel("getSecurity", "setSecurity", passwordItem)
                return ( None , passwordTerm)

        elif( securityTerm == WifiTerms.SECURITY_WPA2_WPA ):
            encryptionItem, passwordItem = self.getModel().getWPA2WPASecurityInfo2G(None, None)
            if encryptionItem is not None:
                encryptionTerm = self.getWifiTermByModel("getSecurity", "setSecurity", encryptionItem)
                passwordTerm   = self.getWifiTermByModel("getSecurity", "setSecurity", passwordItem)
                return ( encryptionTerm , passwordTerm)
            else:
                passwordTerm   = self.getWifiTermByModel("getSecurity", "setSecurity", passwordItem)
                return ( None , passwordTerm)

        elif( securityTerm == WifiTerms.SECURITY_D ):
            return (None , None)

        else:
            raise Exception("error: securityTerm:'%s'" % (securityTerm))


    def _getEncryptionInfo5G(self, securityTerm):

        if( securityTerm == WifiTerms.SECURITY_WEP ):
            encryptionItem, passwordItem = self.getModel().getWEPSecurityInfo5G(None, None)
            encryptionTerm = self.getWifiTermByModel("getSecurity", "setSecurity", encryptionItem)
            passwordTerm   = self.getWifiTermByModel("getSecurity", "setSecurity", passwordItem)
            return (encryptionTerm, passwordTerm)

        elif( securityTerm == WifiTerms.SECURITY_WPA ):
            encryptionItem, passwordItem = self.getModel().getWPASecurityInfo5G(None, None)
            if encryptionItem is not None:
                encryptionTerm = self.getWifiTermByModel("getSecurity", "setSecurity", encryptionItem)
                passwordTerm   = self.getWifiTermByModel("getSecurity", "setSecurity", passwordItem)
                return (encryptionTerm, passwordTerm)
            else:
                passwordTerm   = self.getWifiTermByModel("getSecurity", "setSecurity", passwordItem)
                return (None, passwordTerm)

        elif( securityTerm == WifiTerms.SECURITY_WPA2 ):
            encryptionItem, passwordItem = self.getModel().getWPA2SecurityInfo5G(None, None)
            if encryptionItem is not None:
                encryptionTerm = self.getWifiTermByModel("getSecurity", "setSecurity", encryptionItem)
                passwordTerm   = self.getWifiTermByModel("getSecurity", "setSecurity", passwordItem)
                return (encryptionTerm, passwordTerm)
            else:
                passwordTerm   = self.getWifiTermByModel("getSecurity", "setSecurity", passwordItem)
                return (None, passwordTerm)

        elif( securityTerm == WifiTerms.SECURITY_WPA2_WPA ):
            encryptionItem, passwordItem = self.getModel().getWPA2WPASecurityInfo5G(None, None)
            if encryptionItem is not None:
                encryptionTerm = self.getWifiTermByModel("getSecurity", "setSecurity", encryptionItem)
                passwordTerm   = self.getWifiTermByModel("getSecurity", "setSecurity", passwordItem)
                return (encryptionTerm, passwordTerm)
            else:
                passwordTerm   = self.getWifiTermByModel("getSecurity", "setSecurity", passwordItem)
                return (None, passwordTerm)

        elif( securityTerm == WifiTerms.SECURITY_D ):
            return (None , None)

        else:
            raise Exception("error: securityTerm:'%s'." % (securityTerm))


    def getRemoteSecurity(self):
        self.logger.enter('getSecurity enter.')

        if self.band == WifiTerms.BAND_2G:
            securityTerm, encryptionTerm , passwordTerm = self._getRemoteSecurity2G()
        elif self.band == WifiTerms.BAND_5G:
            securityTerm, encryptionTerm , passwordTerm = self._getRemoteSecurity5G()

        else:
            self.logger.leave('getSecurity leave EXPT')
            raise ACSValueError("invalid band:'%s'" % self.band)

        self.logger.leave('getSecurity leave. security:%s, encryptionTerm:%s, passwordTerm:%s'
                          % (securityTerm, encryptionTerm, passwordTerm))
        return (securityTerm , encryptionTerm , passwordTerm)


    def _getRemoteSecurity2G(self):
        wirelessMode = self._getRemoteWirelessMode2G()

        if wirelessMode == WifiTerms.WIRELESS_MODE_N:
            securityItem = self.getModel().getNSecurity2G(None)
            securityTerm  = self.getRemoteWifiTermByModel("getSecurity", securityItem)
            encryptionTerm , passwordTerm = self._getRemoteEncryptionInfo2G(securityTerm)

        else:
            securityItem = self.getModel().getSecurity2G(None)
            securityTerm  = self.getRemoteWifiTermByModel("getSecurity", securityItem)
            encryptionTerm , passwordTerm = self._getRemoteEncryptionInfo2G(securityTerm)

        return (securityTerm , encryptionTerm , passwordTerm)


    def _getRemoteSecurity5G(self):
        wirelessMode = self._getRemoteWirelessMode5G()

        if wirelessMode == WifiTerms.WIRELESS_MODE_N:
            securityItem = self.getModel().getNSecurity5G(None)
            securityTerm  = self.getRemoteWifiTermByModel("getSecurity", securityItem)
            encryptionTerm , passwordTerm = self._getRemoteEncryptionInfo5G(securityTerm)

        else:
            securityItem = self.getModel().getSecurity5G(None)
            securityTerm  = self.getRemoteWifiTermByModel("getSecurity", securityItem)
            encryptionTerm , passwordTerm = self._getRemoteEncryptionInfo5G(securityTerm)

        return (securityTerm , encryptionTerm , passwordTerm)


    def _getRemoteEncryptionInfo2G(self, securityTerm):
        if( securityTerm == WifiTerms.SECURITY_WEP ):
            encryptionItem, passwordItem = self.getModel().getWEPSecurityInfo2G(None, None)
            encryptionTerm = self.getRemoteWifiTermByModel("getSecurity", encryptionItem)
            passwordTerm   = self.getRemoteWifiTermByModel("getSecurity", passwordItem)
            return (encryptionTerm, passwordTerm)

        elif( securityTerm == WifiTerms.SECURITY_WPA ):
            encryptionItem, passwordItem = self.getModel().getWPASecurityInfo2G(None, None)
            if encryptionItem is not None:
                encryptionTerm = self.getRemoteWifiTermByModel("getSecurity", encryptionItem)
                passwordTerm   = self.getRemoteWifiTermByModel("getSecurity", passwordItem)
                return ( encryptionTerm , passwordTerm)
            else:
                passwordTerm   = self.getRemoteWifiTermByModel("getSecurity", passwordItem)
                return ( None , passwordTerm)

        elif( securityTerm == WifiTerms.SECURITY_WPA2 ):
            encryptionItem, passwordItem = self.getModel().getWPA2SecurityInfo2G(None, None)
            if encryptionItem is not None:
                encryptionTerm = self.getRemoteWifiTermByModel("getSecurity", encryptionItem)
                passwordTerm   = self.getRemoteWifiTermByModel("getSecurity", passwordItem)
                return ( encryptionTerm , passwordTerm)
            else:
                passwordTerm   = self.getRemoteWifiTermByModel("getSecurity", passwordItem)
                return ( None , passwordTerm)

        elif( securityTerm == WifiTerms.SECURITY_WPA2_WPA ):
            encryptionItem, passwordItem = self.getModel().getWPA2WPASecurityInfo2G(None, None)
            if encryptionItem is not None:
                encryptionTerm = self.getRemoteWifiTermByModel("getSecurity", encryptionItem)
                passwordTerm   = self.getRemoteWifiTermByModel("getSecurity", passwordItem)
                return ( encryptionTerm , passwordTerm)
            else:
                passwordTerm   = self.getRemoteWifiTermByModel("getSecurity", passwordItem)
                return ( None , passwordTerm)

        elif( securityTerm == WifiTerms.SECURITY_D ):
            return (None , None)

        else:
            raise Exception("error: securityTerm:'%s'" % (securityTerm))


    def _getRemoteEncryptionInfo5G(self, securityTerm):
        if( securityTerm == WifiTerms.SECURITY_WEP ):
            encryptionItem, passwordItem = self.getModel().getWEPSecurityInfo5G(None, None)
            encryptionTerm = self.getRemoteWifiTermByModel("getSecurity", encryptionItem)
            passwordTerm   = self.getRemoteWifiTermByModel("getSecurity", passwordItem)
            return (encryptionTerm, passwordTerm)

        elif( securityTerm == WifiTerms.SECURITY_WPA ):
            encryptionItem, passwordItem = self.getModel().getWPASecurityInfo5G(None, None)
            if encryptionItem is not None:
                encryptionTerm = self.getRemoteWifiTermByModel("getSecurity", encryptionItem)
                passwordTerm   = self.getRemoteWifiTermByModel("getSecurity", passwordItem)
                return (encryptionTerm, passwordTerm)
            else:
                passwordTerm   = self.getRemoteWifiTermByModel("getSecurity", passwordItem)
                return (None, passwordTerm)

        elif( securityTerm == WifiTerms.SECURITY_WPA2 ):
            encryptionItem, passwordItem = self.getModel().getWPA2SecurityInfo5G(None, None)
            if encryptionItem is not None:
                encryptionTerm = self.getRemoteWifiTermByModel("getSecurity", encryptionItem)
                passwordTerm   = self.getRemoteWifiTermByModel("getSecurity", passwordItem)
                return (encryptionTerm, passwordTerm)
            else:
                passwordTerm   = self.getRemoteWifiTermByModel("getSecurity", passwordItem)
                return (None, passwordTerm)

        elif( securityTerm == WifiTerms.SECURITY_WPA2_WPA ):
            encryptionItem, passwordItem = self.getModel().getWPA2WPASecurityInfo5G(None, None)
            if encryptionItem is not None:
                encryptionTerm = self.getRemoteWifiTermByModel("getSecurity", encryptionItem)
                passwordTerm   = self.getRemoteWifiTermByModel("getSecurity", passwordItem)
                return (encryptionTerm, passwordTerm)
            else:
                passwordTerm   = self.getRemoteWifiTermByModel("getSecurity", passwordItem)
                return (None, passwordTerm)

        elif( securityTerm == WifiTerms.SECURITY_D ):
            return (None , None)

        else:
            raise Exception("error: securityTerm:'%s'." % (securityTerm))


    def setTxRate(self, txRate):
        self.logger.debug(" setTxRate: '%s'" % (txRate))
        wirelessMode = self.getWirelessMode()

        if WifiTerms.WIRELESS_MODE_D == wirelessMode:
            return self._setDModeTxRate(txRate)

        elif wirelessMode == WifiTerms.WIRELESS_MODE_N:
            return self._setNModeTxRate(txRate)

        elif wirelessMode == WifiTerms.WIRELESS_MODE_MIXED:
            return self._setMixedModeTxRate(txRate)

        elif self.band == WifiTerms.BAND_2G \
                        and wirelessMode == WifiTerms.WIRELESS_MODE_B:
            return self._setBModeTxRate(txRate)

        elif self.band == WifiTerms.BAND_2G \
                        and wirelessMode == WifiTerms.WIRELESS_MODE_G:
            return self._setGModeTxRate(txRate)

        elif self.band == WifiTerms.BAND_2G \
                        and wirelessMode == WifiTerms.WIRELESS_MODE_BG:
            return self._setBGModeTxRate(txRate)

        elif self.band == WifiTerms.BAND_5G \
                        and wirelessMode == WifiTerms.WIRELESS_MODE_A:
            return self._setAModeTxRate(txRate)

        else:
            raise ACSValueError("Invalid band:'%s', txRate:'%s'" % (self.band, txRate))


    def _setDModeTxRate(self, txRate):
        raise ACSValueError("Cann't set txrate while wireless mode is:'%s'" % WifiTerms.WIRELESS_MODE_D)


    def _setBModeTxRate(self, txRate):
        config = self.getLocalConfig('setTxRate')
        bItem = self.getModel().getBTxRate2G(txRate)
        config.setTxRate(bItem)
        return config

    def _setGModeTxRate(self, txRate):
        config = self.getLocalConfig('setTxRate')
        gItem = self.getModel().getGTxRate2G(txRate)
        config.setTxRate(gItem)
        return config


    def _setBGModeTxRate(self, txRate):
        config = self.getLocalConfig('setTxRate')
        bgItem = self.getModel().getBGTxRate2G(txRate)
        config.setTxRate(bgItem)
        return config


    def _setAModeTxRate(self, txRate):
        config = self.getLocalConfig('setTxRate')
        aItem = self.getModel().getATxRate5G(txRate)
        config.setTxRate(aItem)
        return config


    def _setNModeTxRate(self, txRate):
        channelWidth = self.getChannelWidth()
        config = self.getLocalConfig('setTxRate')

        if self.band == WifiTerms.BAND_2G \
                      and channelWidth == WifiTerms.CHANNEL_WIDTH_20:
            nItem = self.getModel().getN20TxRate2G(txRate)
            config.setTxRate(nItem)
            return config

        elif self.band == WifiTerms.BAND_2G \
                        and channelWidth == WifiTerms.CHANNEL_WIDTH_40:
            nItem = self.getModel().getN40TxRate2G(txRate)
            config.setTxRate(nItem)
            return config

        elif self.band == WifiTerms.BAND_2G \
                        and channelWidth == WifiTerms.CHANNEL_WIDTH_A:
            nItem = self.getModel().getN40TxRate2G(txRate)
            config.setTxRate(nItem)
            return config

        elif self.band == WifiTerms.BAND_5G \
                        and channelWidth == WifiTerms.CHANNEL_WIDTH_20:
            nItem = self.getModel().getN20TxRate5G(txRate)
            config.setTxRate(nItem)
            return config

        elif self.band == WifiTerms.BAND_5G \
                        and channelWidth == WifiTerms.CHANNEL_WIDTH_40:
            nItem = self.getModel().getN40TxRate5G(txRate)
            config.setTxRate(nItem)
            return config

        elif self.band == WifiTerms.BAND_5G \
                        and channelWidth == WifiTerms.CHANNEL_WIDTH_A:
            nItem = self.getModel().getN40TxRate5G(txRate)
            config.setTxRate(nItem)
            return config

        else:
            raise ACSValueError("Invalid band:'%s', and channelWidth:'%s'" % (self.band, channelWidth))


    def _setMixedModeTxRate(self, txRate):
        channelWidth = self.getChannelWidth()
        config = self.getLocalConfig('setTxRate')

        if self.band == WifiTerms.BAND_2G \
                      and channelWidth == WifiTerms.CHANNEL_WIDTH_20:
            (nonNItem, nItem) = self.getModel().getMixed20TxRate2G(txRate)

            if nonNItem != None: config.setTxRate(nonNItem)
            if nItem != None: config.setTxRate(nItem)

            return config

        elif self.band == WifiTerms.BAND_2G \
                        and channelWidth == WifiTerms.CHANNEL_WIDTH_40:
            (nonNItem, nItem) = self.getModel().getMixed40TxRate2G(txRate)

            if nonNItem != None: config.setTxRate(nonNItem)
            if nItem != None: config.setTxRate(nItem)

            return config

        elif self.band == WifiTerms.BAND_2G \
                        and channelWidth == WifiTerms.CHANNEL_WIDTH_A:
            (nonNItem, nItem) = self.getModel().getMixed40TxRate2G(txRate)

            if nonNItem != None: config.setTxRate(nonNItem)
            if nItem != None: config.setTxRate(nItem)

            return config

        elif self.band == WifiTerms.BAND_5G \
                        and channelWidth == WifiTerms.CHANNEL_WIDTH_20:
            (nonNItem, nItem) = self.getModel().getMixed20TxRate5G(txRate)

            if nonNItem != None: config.setTxRate(nonNItem)
            if nItem != None: config.setTxRate(nItem)

            return config

        elif self.band == WifiTerms.BAND_5G \
                        and channelWidth == WifiTerms.CHANNEL_WIDTH_40:
            (nonNItem, nItem) = self.getModel().getMixed40TxRate5G(txRate)

            if nonNItem != None: config.setTxRate(nonNItem)
            if nItem != None: config.setTxRate(nItem)

            return config

        elif self.band == WifiTerms.BAND_5G \
                        and channelWidth == WifiTerms.CHANNEL_WIDTH_A:
            (nonNItem, nItem) = self.getModel().getMixed40TxRate5G(txRate)

            if nonNItem != None: config.setTxRate(nonNItem)
            if nItem != None: config.setTxRate(nItem)

            return config

        else:
            raise ACSValueError("Invalid band:'%s'" % self.band)


    def getTxRate(self):
        self.logger.enter("getTxRate")
        wirelessMode = self.getWirelessMode()
        retValue = None

        if WifiTerms.WIRELESS_MODE_D == wirelessMode:
            raise ACSValueError("Cann't set txrate while wireless mode is:'%s'" % wirelessMode)

        elif wirelessMode == WifiTerms.WIRELESS_MODE_N:
            retValue = self._getNModeTxRate()

        elif wirelessMode == WifiTerms.WIRELESS_MODE_MIXED:
            retValue = self._getMixedModeTxRate()

        elif self.band == WifiTerms.BAND_2G \
                        and wirelessMode == WifiTerms.WIRELESS_MODE_B:
            retValue = self._getBModeTxRate()

        elif self.band == WifiTerms.BAND_2G \
                        and wirelessMode == WifiTerms.WIRELESS_MODE_G:
            retValue = self._getGModeTxRate()

        elif self.band == WifiTerms.BAND_2G \
                        and wirelessMode == WifiTerms.WIRELESS_MODE_BG:
            retValue = self._getBGModeTxRate()

        elif self.band == WifiTerms.BAND_5G \
                        and wirelessMode == WifiTerms.WIRELESS_MODE_A:
            retValue = self._getAModeTxRate()

        self.logger.leave(' getTxRate return ="%s"' % retValue)
        return retValue


    def _getDModeTxRate(self):
        raise ACSValueError("Cann't set txrate while wireless mode is:'%s'" % WifiTerms.WIRELESS_MODE_D)


    def _getBModeTxRate(self):
        bItem = self.getModel().getBTxRate2G(None)
        return self.getWifiTermByModel("getTxRate", "setTxRate", bItem)


    def _getGModeTxRate(self):
        gItem = self.getModel().getGTxRate2G(None)
        return self.getWifiTermByModel("getTxRate", "setTxRate", gItem)

    def _getBGModeTxRate(self):
        bgItem = self.getModel().getBGTxRate2G(None)
        return self.getWifiTermByModel("getTxRate", "setTxRate", bgItem)


    def _getAModeTxRate(self):
        aItem = self.getModel().getATxRate5G(None)
        return self.getWifiTermByModel("getTxRate", "setTxRate", aItem)


    def _getNModeTxRate(self):
        channelWidth = self.getChannelWidth()
        retValue = None

        if self.band == WifiTerms.BAND_2G \
                      and channelWidth == WifiTerms.CHANNEL_WIDTH_20:
            nItem = self.getModel().getN20TxRate2G(None)
            retValue = self.getWifiTermByModel("getTxRate", "setTxRate", nItem)

        elif self.band == WifiTerms.BAND_2G \
                        and channelWidth == WifiTerms.CHANNEL_WIDTH_40:
            nItem = self.getModel().getN40TxRate2G(None)
            retValue = self.getWifiTermByModel("getTxRate", "setTxRate", nItem)

        elif self.band == WifiTerms.BAND_2G \
                        and channelWidth == WifiTerms.CHANNEL_WIDTH_A:
            nItem = self.getModel().getN40TxRate2G(None)
            retValue = self.getWifiTermByModel("getTxRate", "setTxRate", nItem)

        elif self.band == WifiTerms.BAND_5G \
                        and channelWidth == WifiTerms.CHANNEL_WIDTH_20:
            nItem = self.getModel().getN20TxRate5G(None)
            retValue = self.getWifiTermByModel("getTxRate", "setTxRate", nItem)

        elif self.band == WifiTerms.BAND_5G \
                        and channelWidth == WifiTerms.CHANNEL_WIDTH_40:
            nItem = self.getModel().getN40TxRate5G(None)
            retValue = self.getWifiTermByModel("getTxRate", "setTxRate", nItem)

        elif self.band == WifiTerms.BAND_5G \
                        and channelWidth == WifiTerms.CHANNEL_WIDTH_A:
            nItem = self.getModel().getN40TxRate5G(None)
            retValue = self.getWifiTermByModel("getTxRate", "setTxRate", nItem)

        return retValue


    def _getMixedModeTxRate(self):
        #TODO How to return txRate while in Mixed rate. Current return N mode rate first.
        channelWidth = self.getChannelWidth()
        retValue = None

        if self.band == WifiTerms.BAND_2G \
                      and channelWidth == WifiTerms.CHANNEL_WIDTH_20:
            nonNItem,nItem = self.getModel().getMixed20TxRate2G(None)

            nonNValue = self.getWifiTermByModel("getTxRate", "setTxRate", nonNItem)
            nValue = self.getWifiTermByModel("getTxRate", "setTxRate", nItem)
            if nValue != WifiTerms.DATA_RATE_A:
                retValue = nValue

            elif nonNValue != WifiTerms.DATA_RATE_A:
                retValue = nonNValue

            else:
                retValue = WifiTerms.DATA_RATE_A

        elif self.band == WifiTerms.BAND_2G \
                        and channelWidth == WifiTerms.CHANNEL_WIDTH_40:
            nonNItem,nItem = self.getModel().getMixed40TxRate2G(None)

            nonNValue = self.getWifiTermByModel("getTxRate", "setTxRate", nonNItem)
            nValue = self.getWifiTermByModel("getTxRate", "setTxRate", nItem)
            if nValue != WifiTerms.DATA_RATE_A:
                retValue = nValue

            elif nonNValue != WifiTerms.DATA_RATE_A:
                retValue = nonNValue

            else:
                retValue = WifiTerms.DATA_RATE_A

        elif self.band == WifiTerms.BAND_2G \
                        and channelWidth == WifiTerms.CHANNEL_WIDTH_A:
            nonNItem,nItem = self.getModel().getMixed40TxRate2G(None)

            nonNValue = self.getWifiTermByModel("getTxRate", "setTxRate", nonNItem)
            nValue = self.getWifiTermByModel("getTxRate", "setTxRate", nItem)
            if nValue != WifiTerms.DATA_RATE_A:
                retValue = nValue

            elif nonNValue != WifiTerms.DATA_RATE_A:
                retValue = nonNValue

            else:
                retValue = WifiTerms.DATA_RATE_A

        elif self.band == WifiTerms.BAND_5G \
                        and channelWidth == WifiTerms.CHANNEL_WIDTH_20:
            nonNItem,nItem = self.getModel().getMixed20TxRate5G(None)

            nonNValue = self.getWifiTermByModel("getTxRate", "setTxRate", nonNItem)
            nValue = self.getWifiTermByModel("getTxRate", "setTxRate", nItem)
            if nValue != WifiTerms.DATA_RATE_A:
                retValue = nValue

            elif nonNValue != WifiTerms.DATA_RATE_A:
                retValue = nonNValue

            else:
                retValue = WifiTerms.DATA_RATE_A

        elif self.band == WifiTerms.BAND_5G \
                        and channelWidth == WifiTerms.CHANNEL_WIDTH_40:
            nonNItem,nItem = self.getModel().getMixed40TxRate5G(None)

            nonNValue = self.getWifiTermByModel("getTxRate", "setTxRate", nonNItem)
            nValue = self.getWifiTermByModel("getTxRate", "setTxRate", nItem)
            if nValue != WifiTerms.DATA_RATE_A:
                retValue = nValue

            elif nonNValue != WifiTerms.DATA_RATE_A:
                retValue = nonNValue

            else:
                retValue = WifiTerms.DATA_RATE_A

        elif self.band == WifiTerms.BAND_5G \
                        and channelWidth == WifiTerms.CHANNEL_WIDTH_A:
            nonNItem,nItem = self.getModel().getMixed40TxRate5G(None)

            nonNValue = self.getWifiTermByModel("getTxRate", "setTxRate", nonNItem)
            nValue = self.getWifiTermByModel("getTxRate", "setTxRate", nItem)
            if nValue != WifiTerms.DATA_RATE_A:
                retValue = nValue

            elif nonNValue != WifiTerms.DATA_RATE_A:
                retValue = nonNValue

            else:
                retValue = WifiTerms.DATA_RATE_A

        else:
            raise ACSValueError("invalid band:'%s'" % self.band)

        return retValue


    def setHidden(self, hidden):
        self.logger.enter("setHidden: '%s'" % (hidden))

        config = None
        if self.band == WifiTerms.BAND_2G:
            config = self._setHidden2G(hidden)

        elif self.band == WifiTerms.BAND_5G:
            config = self._setHidden5G(hidden)

        else:
            raise ACSValueError("invalid band:'%s'" % self.band)

        self.logger.leave("setHidden leave")
        return config


    def _setHidden2G(self, hidden):
        config = self.getLocalConfig('setHidden')
        configItem = self.getModel().getHidden2G(hidden)
        config.setHidden(configItem)

        return config


    def _setHidden5G(self, hidden):
        config = self.getLocalConfig('setHidden')
        configItem = self.getModel().getHidden5G(hidden)
        config.setHidden(configItem)

        return config


    def getHidden(self):
        self.logger.enter("getHidden")

        term = None
        if self.band == WifiTerms.BAND_2G:
            term = self._getHidden2G()

        elif self.band == WifiTerms.BAND_5G:
            term = self._getHidden5G()

        else:
            raise ACSValueError("invalid band:'%s'" % self.band)

        self.logger.leave('getHidden return ="%s"' % term)
        return term


    def _getHidden2G(self):
        hiddenItem2g = self.getModel().getHidden2G(None)
        term = self.getWifiTermByModel("getHidden", "setHidden", hiddenItem2g)
        return term


    def _getHidden5G(self):
        hiddenItem5g = self.getModel().getHidden5G(None)
        term = self.getWifiTermByModel("getHidden", "setHidden", hiddenItem5g)
        return term


    def getRemoteConfig(self, configName):
        config = self.getConfig(configName)
        config.clear()
        self.getDriver().loadConfig(self.lan_ip, self.user, self.password, config)
        return config


    def getLocalConfig(self, configName):
        config = self.getConfig(configName)
        self.logger.debug("checking %s. loaded:%d" % (config.getName(), config.isLoaded()))
        if( not config.isLoaded() ):
            self.getDriver().loadConfig(self.lan_ip, self.user, self.password, config)
        return config


    def getRemoteWifiTermByModel(self, getConfigName, configItem):
        config = self.getRemoteConfig(getConfigName)
        configItem.reloadData(config)
        term = configItem.getWifiTerm()

        if( (term is None) and (configItem.getKey() is not None)):
            raise Exception("can not get wifiTerm for '%s' by '%s'" %(configItem, getConfigName))

        return term


    def getWifiTermByModel(self, getConfigName, setConfigName, configItem):
        config = self.getLocalConfig(setConfigName)
        configItem.reloadData(config)
        term = configItem.getWifiTerm()
        if(term is not None):
            return term
        self.logger.debug("can not get wifiTerm for '%s' by '%s', try to get from remote." %(configItem, setConfigName))
        term = self.getRemoteWifiTermByModel(getConfigName, configItem)

        return term


    # abstract method
    def isDualBand(self):
        raise NotImplementedError("abstract")


    def getDriver(self):
        raise NotImplementedError("abstract")


    def commit(self, always = False):
        raise NotImplementedError("abstract")


    def updateConfig(self, config):
        raise NotImplementedError("abstract")


    def getConfig(self, configName):
        raise NotImplementedError("abstract")


    def disconnectCallback(self):
        raise NotImplementedError("abstract")


    def getModel(self):
        raise NotImplementedError("abstract")


    def reboot(self):
        raise NotImplementedError("abstract")


    # abstract method


    def isAlive(self):
        self.logger.enter("isAlive enter.")
        status = True
        authHeader = "Basic %s" % base64.encodestring('%s:%s' % (self.user, self.password))[:-1]
        try:
            request = urllib2.Request('http://'+self.lan_ip)
            request.add_header("Authorization", authHeader)
            urllib2.urlopen(request)
            status = True
        except Exception, e:
            #In fact the message here should be: "<urlopen error [Errno 113] No route to host>".
            self.logger.debug("Exception message in isAlive : %s" % str(e))
            status = False
        self.logger.leave("isAlive leave with: %s." % status)
        return status


    class ResetForm(object):
        def __init__(self, ap, formUrl):
            self.ap = ap
            self.url = str('http://'+ self.ap.lan_ip+'/' + formUrl)
            self.boundary = mimetools.choose_boundary()
            self.partBoundary = '--' + self.boundary
            self.parts = []
            self.contentDisposition = 'form-data'

        def addField(self, fieldName, fieldValue):
            fieldInfo = [(fieldName, fieldValue)]
            self.parts.extend(
                [ self.partBoundary,
                  'Content-Disposition: form-data; name="%s"' % name,
                  '',
                  value,
                ]
                for name, value in fieldInfo
                )

        def addFile(self, fieldName, fileName):
            contentType = (mimetypes.guess_type(fileName)[0] or 'application/octet-stream')
            fileContent = open(fileName, "rb").read()
            fileInfo = [(fieldName, fileName, contentType, fileContent)]
            self.parts.extend([
                self.partBoundary,
                'Content-Disposition: %s; name="%s"; filename="%s"' % (self.contentDisposition, name, fname),
                'Content-Type: %s' %ctype,
                '',
                fbody,
                ]
                for name,fname,ctype,fbody in fileInfo
                )

        def submit(self):
            request = urllib2.Request(self.url)

            #Body content.
            flattened = list(itertools.chain(*self.parts))
            flattened.append('--' + self.boundary + '--')
            flattened.append('')
            body = str('\r\n'.join(flattened))
            request.add_data(body)

            #Header content.
            authheader = "Basic %s" % base64.encodestring('%s:%s' % (self.ap.user, self.ap.password))[:-1]
            headerType = 'multipart/form-data; boundary=%s' % self.boundary
            request.add_header('Authorization', authheader)
            request.add_header('Content-type', headerType)
            request.add_header('Content-length', len(body))

            #Post body and header.
            try:
                urllib2.urlopen(request)
            except IOError, e:
                errMsg = str(e)
                self.logger.debug(errMsg)


    def reset(self):
        self.logger.enter("reset enter.")

        resetForm = CISCO_BASE_POST.ResetForm(self, "restore.cgi")

        fieldName = "restore"
        fileName = Provider.getInstance().getApFactoryConfig(self.model)
        resetForm.addFile(fieldName, fileName)

        resetForm.submit()

        self.apUtils.busyWait(45)

        self.logger.leave("reset leave.")
