#!/bin/bash

if [ ! "$UID" = "0" ]; then
    echo Please running using root user.
    exit 1
fi

SERVER=10.1.10.100

wget -q --no-proxy http://$SERVER/setup/sources.list  -O /etc/apt/sources.list
wget -q --no-proxy http://$SERVER/setup/repo          -O /usr/local/bin/repo
chmod a+x /usr/local/bin/repo

if ! apt-get update; then
    echo apt update failed.
    read
    apt-get update
fi

apt-get -y install `wget -q -O- --no-proxy http://$SERVER/setup/pkglist`
apt-get -y purge linux-image-2.6.38-8-generic linux-headers-2.6.38-8-generic linux-headers-2.6.38-8

echo 'SUBSYSTEM=="usb", SYSFS{idVendor}=="0451", MODE="0666"' >  /etc/udev/rules.d/51-android.rules
echo 'SUBSYSTEM=="usb", SYSFS{idVendor}=="1949", MODE="0666"' >> /etc/udev/rules.d/51-android.rules

echo "Installing compile tools"
mkdir -p /opt/CodeSourcery /disk/CodeSourcery
wget -q -O- --no-proxy http://$SERVER/setup/arm-2010q1-202-arm-none-linux-gnueabi-i686-pc-linux-gnu.tar.bz2 | tar xj -C /opt/CodeSourcery
ln -s /opt/CodeSourcery/arm-2010q1 /disk/CodeSourcery/Sourcery_G++_Lite

dpkg-reconfigure dash
