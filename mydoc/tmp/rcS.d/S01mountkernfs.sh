#! /bin/sh
### BEGIN INIT INFO
# Provides:          mountkernfs
# Required-Start:
# Required-Stop:
# Default-Start:     S
# Default-Stop:
# Short-Description: Mount kernel virtual file systems.
# Description:       Mount initial set of virtual filesystems the kernel
#                    provides and that are required by everything.
### END INIT INFO

PATH=/lib/init:/sbin:/bin

. /lib/lsb/init-functions
. /lib/init/mount-functions.sh

do_start () {
	#
	# Mount proc filesystem on /proc
	#
	domount proc "" /proc -onodev,noexec,nosuid

	#
	# Mount sysfs on /sys
	#
	domount sysfs "" /sys -onodev,noexec,nosuid

	# Mount /var/run and /var/lock as tmpfs.
	domount tmpfs "" /var/run -omode=0755,nodev,noexec,nosuid
	domount tmpfs "" /var/lock -omode=1777,nodev,noexec,nosuid

	# Mount spufs, if Cell Broadband processor is detected
	if mountpoint -q /proc && grep -qs '^cpu.*Cell' /proc/cpuinfo; then
		mkdir -p /spu
		domount spufs "" /spu -ogid=spu
	fi

	# Propagate files from the initramfs to our new /var/run.
	for file in /dev/.initramfs/varrun/*; do
		[ -e "$file" ] || continue
		cp -a "$file" "/var/run/${x#/dev/.initramfs/varrun/}"
	done

	if [ ! -d /var/run/sendsigs.omit.d/ ]; then
		mkdir /var/run/sendsigs.omit.d/
	fi
}

case "$1" in
  "")
	echo "Warning: mountvirtfs should be called with the 'start' argument." >&2
	do_start
	;;
  start)
	do_start
	;;
  restart|reload|force-reload)
	echo "Error: argument '$1' not supported" >&2
	exit 3
	;;
  stop)
	# No-op
	;;
  *)
	echo "Usage: mountvirtfs [start|stop]" >&2
	exit 3
	;;
esac
