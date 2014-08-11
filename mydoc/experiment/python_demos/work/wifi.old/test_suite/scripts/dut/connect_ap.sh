#!/system/bin/sh

/system/bin/wpa_cli -iwlan0 scan
/system/bin/wpa_cli -iwlan0 scan_result
/system/bin/wpa_cli -iwlan0 add_network
#set the ssid for connection AP
echo $1
/system/bin/wpa_cli -iwlan0 set_network 0 ssid $1
/system/bin/wpa_cli -iwlan0 set_network 0 key_mgmt WPA-PSK
#set the password
echo $2
/system/bin/wpa_cli -iwlan0 set_network 0 psk $2
/system/bin/wpa_cli -iwlan0 set_network 0 pairwise TKIP
/system/bin/wpa_cli -iwlan0 set_network 0 group TKIP
/system/bin/wpa_cli -iwlan0 enable_network 0

#dhcp and wait for obtaining the IP address
for vari in 1 2 3
do
    sleep 2
    dhcpcd wlan0
    if [ $? == 0 ]; then
        break
    fi

    if [ vari == 3 ]; then
        echo "dhcpcd wlan0 failed"
        exit 1
    fi
done

