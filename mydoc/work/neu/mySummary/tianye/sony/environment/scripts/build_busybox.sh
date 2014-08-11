#!/bin/bash



########Notation for development#########
#Not build busybox as hardlinks because make_base_rootfs copy more than one time made size bigger.
#we will change softlink to hardlink at the final phase of make rootfs.
#########################################

########Global Variables#########
DIABLO_CROSS_TOP=$2
WORK_SPACE=$3
TMP_FS_DIR=$4

#XXX Here DIABLO_KERNEL_SRC defined in top env.mk is not very right.
DIABLO_KERNEL_SRC=$5
echo "DIABLO_CROSS_TOP------------------>$DIABLO_CROSS_TOP"
echo "WORK_SPACE------------------>$WORK_SPACE"


#XXX To be modified.
__cross_build_path=$DIABLO_CROSS_TOP/arm/cross
__cross_target_path=$DIABLO_CROSS_TOP/arm/target/arm
#__cross_build_path=${DIABLO_CROSS_TOP}

__install_dir=_install
__initrd_image=ramdisk

__tmp_fs_path=$TMP_FS_DIR
#__tmp_fs_path=$(pwd)/tempdir

__extra_dir=extra

#available value:nfs|initrd
__rootfs_type=nfs

#XXX Where is the build kernel???
__kernel_obj_path=${DIABLO_KERNEL_SRC}

############Functions############
check_errors()
{
	[ -d $__cross_build_path/devel/bin ] ||
	{
		echo "No cross build tools."
		exit 1
	}
}

clean_build_files()
{
	echo "Removing previous busybox build files."
	[ -d ./busybox-1.4.2 ] && rm -rf ./busybox-1.4.2
}

clean_rootfs_files()
{
	echo "Removing previous busybox rootfs dirs."
	#Check carefully at first, or it may ruin your system.
	if [ -d $__tmp_fs_path ]
	then
		rm -rf $__tmp_fs_path
	else
		echo "Havn't find previous rootfs"
	fi
	#[ -d $__tmp_fs_path/bin ] && 
	#{
	#	echo 
	#	if [ -f $__tmp_fs_path/bin/busybox ]
	#	then
	#		rm -rf $__tmp_fs_path
	#	else
	#		echo "Make sure your path run for $0 is right!"
	#		exit 1
	#	fi
	#} 
	#[ -d $__tmp_fs_path/sbin ] && rm -rf $__tmp_fs_path/sbin
	#[ -d $__tmp_fs_path/usr ] && rm -rf $__tmp_fs_path/usr
	#[ -d $__tmp_fs_path/dev ] && rm -rf $__tmp_fs_path/dev
	#[ -d $__tmp_fs_path/etc ] && rm -rf $__tmp_fs_path/etc
	#[ -d $__tmp_fs_path/lib ] && rm -rf $__tmp_fs_path/lib
	#[ -d $__tmp_fs_path/proc ] && rm -rf $__tmp_fs_path/proc
	#[ -d $__tmp_fs_path/root ] && rm -rf $__tmp_fs_path/root
	#[ -d $__tmp_fs_path/sys ] && rm -rf $__tmp_fs_path/sys
	#[ -d $__tmp_fs_path/devel ] && rm -rf $__tmp_fs_path/devel
}

clean_up()
{
	case $1 in
	"build" )
		clean_build_files
		;;
	"rootfs" )
		clean_rootfs_files
		;;
	"all" )
		clean_build_files
		clean_rootfs_files
		;;
	*)
		;;
	esac
}

build_busybox()
{
	echo "Patching busybox."
	tar xjf busybox-1.4.2.tar.bz2
	sh busybox-patches/patch.sh ./busybox-1.4.2
	#XXX To be improved. Copy our own custom config for build busybox.
	cp ./$__extra_dir/busybox_config/dotconfig.$__rootfs_type ./busybox-1.4.2/.config
	cd busybox-1.4.2
	echo "Building busybox."
	make
	echo "Installing busybox."
	make install

	__tmp=$?
	cd $OLDPWD
	[ $__tmp -eq 0 ] ||return $__tmp
}

make_base_rootfs()
{
	echo "Constructing base rootfs."
	cd busybox-1.4.2
	#
	echo "Making new rootfs dirs."
	mkdir -p $__tmp_fs_path
	#bin
	cp -a $__install_dir/bin $__tmp_fs_path/

	#sbin
	cp -a $__install_dir/sbin $__tmp_fs_path/
	cp -a ../$__extra_dir/sbin/init.$__rootfs_type $__tmp_fs_path/sbin/init
	#modify by chengmao
	chmod +x $__tmp_fs_path/sbin/init
	
	#usr
	cp -a $__install_dir/usr $__tmp_fs_path/
	
	#dev
	mkdir $__tmp_fs_path/dev

	#mnt
	mkdir $__tmp_fs_path/mnt
	
	#etc
	mkdir $__tmp_fs_path/etc
	ln -s /opt/sony/etc/hosts $__tmp_fs_path/etc/hosts
#added-Start by yandongdong for diablo_ssh_pppd
	ln -s /opt/sony/etc/group $__tmp_fs_path/etc/group
        ln -s /opt/sony/etc/passwd $__tmp_fs_path/etc/passwd
        ln -s /opt/sony/etc/ppp $__tmp_fs_path/etc/ppp
#added-Start by yandongdong for diablo_ssh_pppd
 
#added-Start by yandongdong for diablo_ssh_pppd
	##mkdir /devel/etc
	mkdir -p $__tmp_fs_path/var
        mkdir -p $__tmp_fs_path/devel/etc/ssh
        mkdir -p $__tmp_fs_path/devel/usr/bin/
#added-End by yandongdong for diablo_ssh_pppd

        #opt/sony
        mkdir $__tmp_fs_path/opt
        mkdir $__tmp_fs_path/opt/sony
        mkdir $__tmp_fs_path/opt/sony/bin
        mkdir $__tmp_fs_path/opt/sony/data
#		mkdir $__tmp_fs_path/opt/sony/sbin
#       mkdir $__tmp_fs_path/opt/sony/lib
        mkdir $__tmp_fs_path/opt/sony/etc
		mkdir $__tmp_fs_path/opt/sony/modules
		mkdir $__tmp_fs_path/opt/sony/verup
		
	    #opt/oss
        mkdir $__tmp_fs_path/opt/oss
        mkdir $__tmp_fs_path/opt/oss/bin
        mkdir $__tmp_fs_path/opt/oss/sbin
        mkdir $__tmp_fs_path/opt/oss/etc
        mkdir $__tmp_fs_path/opt/oss/lib
		
		cp -a ../$__extra_dir/etc/rc.local $__tmp_fs_path/opt/sony/etc/
		cp -a ../$__extra_dir/etc/mkdevnod.sh $__tmp_fs_path/opt/sony/etc/
		cp -a ../$__extra_dir/etc/change_ip.sh $__tmp_fs_path/opt/sony/etc/
		cp -a ../$__extra_dir/verup/* $__tmp_fs_path/opt/sony/verup/
		cp -a ../$__extra_dir/sbin/make_node.sh $__tmp_fs_path/opt/sony/bin
		cp -a ../$__extra_dir/sbin/phyadr $__tmp_fs_path/opt/sony/bin
		cp -a ../$__extra_dir/sbin/usbHostTestMode $__tmp_fs_path/opt/sony/bin
		cp -a ../$__extra_dir/sbin/pciehTestModeEnable $__tmp_fs_path/opt/sony/bin
		cp -a ../$__extra_dir/sbin/usbPort1_Port2Test $__tmp_fs_path/opt/sony/bin
		cp -a ../$__extra_dir/sbin/viewlog $__tmp_fs_path/opt/sony/bin
		cp -a ../$__extra_dir/sbin/nvm-debug $__tmp_fs_path/opt/sony/bin/

		mkdir $__tmp_fs_path/opt/sony/var
		mkdir $__tmp_fs_path/opt/sony/cache
#added-Start by yandongdong for diablo_ssh_pppd
		cp -a ../$__extra_dir/etc/ssh/* $__tmp_fs_path/devel/etc/ssh/
		cp ../$__extra_dir/etc/passwd $__tmp_fs_path/opt/sony/etc/
		cp ../$__extra_dir/etc/group $__tmp_fs_path/opt/sony/etc/
		cp -a ../$__extra_dir/sbin/openssh $__tmp_fs_path/opt/oss/sbin
		cp ../$__extra_dir/sbin/start_service.sh $__tmp_fs_path/opt/sony/bin
		cp -a ../$__extra_dir/etc/ppp/ $__tmp_fs_path/opt/oss/etc/
		cp $__cross_target_path/devel/usr/bin/ssh $__tmp_fs_path/devel/usr/bin
#added-End by yandongdong for diablo_ssh_pppd

       	cat >> $__tmp_fs_path/opt/sony/etc/hosts << EOF
# Do not remove the following line, or various programs
# that require network functionality will fail.
127.0.0.1          localhost.localdomain localhost
10.1.1.254         pc
10.1.1.226         emma
10.1.1.227         diablo
::1                localhost6.localdomain6 localhost6
EOF

	#lib
#XXX not use libsony* library
	mkdir $__tmp_fs_path/lib
#	cp $__cross_target_path/lib/libsonypthread.so $__tmp_fs_path/lib
#	cp $__cross_target_path/lib/libsonydl.so $__tmp_fs_path/lib
#	cp $__cross_target_path/lib/libsonyrt.so $__tmp_fs_path/lib
#	cp $__cross_target_path/lib/libsonyc.so $__tmp_fs_path/lib
#	cp $__cross_target_path/lib/libsonygcc_s.so.1 $__tmp_fs_path/lib
#	cp $__cross_target_path/lib/libsonyld.so $__tmp_fs_path/lib
#add by chengmao for eu11
#	cp $__cross_target_path/lib/libsonystdc++.so.6 $__tmp_fs_path/lib
#	cp $__cross_target_path/usr/lib/libexpat.so.1 $__tmp_fs_path/lib
#	cp $__cross_target_path/lib/libsonym.so $__tmp_fs_path/lib
#add end
	#proc
	mkdir $__tmp_fs_path/proc
	
	#root
	mkdir $__tmp_fs_path/root
	cp -a ../$__extra_dir/root/.ssh $__tmp_fs_path/root

	#sys
	mkdir $__tmp_fs_path/sys

	#Use for nfs rootfs
	##usr/bin
	cp $__cross_target_path/devel/sbin/dosfsck $__tmp_fs_path/opt/oss/bin
	cp $__cross_target_path/tool/usr/bin/gdb $__tmp_fs_path/opt/oss/bin
	cp $__cross_target_path/tool/usr/bin/gdbserver $__tmp_fs_path/opt/oss/bin
	cp $__cross_target_path/tool/usr/bin/gprof $__tmp_fs_path/opt/oss/bin
	cp $__cross_target_path/devel/usr/bin/ftp $__tmp_fs_path/opt/oss/bin
	cp $__cross_target_path/devel/usr/bin/scp $__tmp_fs_path/opt/oss/bin
	cp $__cross_target_path/devel/usr/bin/btrace $__tmp_fs_path/opt/oss/bin
	cp $__cross_target_path/devel/usr/bin/ssh $__tmp_fs_path/opt/oss/bin
	cp $__cross_target_path/devel/usr/bin/lsz $__tmp_fs_path/opt/oss/bin
	cp $__cross_target_path/devel/usr/bin/lrz $__tmp_fs_path/opt/oss/bin
	cp $__cross_target_path/devel/sbin/mkdosfs $__tmp_fs_path/bin
	ln -s /bin/mkdosfs $__tmp_fs_path/sbin/mkfs.vfat

#added-Start by yandongdong for diablo_ssh_pppd	
	##usr/sbin
	cp $__cross_target_path/devel/usr/sbin/pppd $__tmp_fs_path/opt/oss/sbin
	cp $__cross_target_path/devel/usr/sbin/pppdump $__tmp_fs_path/opt/oss/sbin
	cp $__cross_target_path/devel/usr/sbin/pppoe-discovery $__tmp_fs_path/opt/oss/sbin
	cp $__cross_target_path/devel/usr/sbin/pppstats $__tmp_fs_path/opt/oss/sbin
	cp $__cross_target_path/devel/usr/sbin/sshd $__tmp_fs_path/opt/oss/sbin
	cp $__cross_target_path/devel/usr/bin/ssh-add $__tmp_fs_path/opt/oss/sbin
	cp $__cross_target_path/devel/usr/bin/ssh-agent $__tmp_fs_path/opt/oss/sbin
	cp $__cross_target_path/devel/usr/bin/ssh-keygen $__tmp_fs_path/opt/oss/sbin
	cp $__cross_target_path/devel/usr/bin/ssh-keyscan $__tmp_fs_path/opt/oss/sbin
#added-End by yandongdong for diablo_ssh_pppd

	##devel
	mkdir -p $__tmp_fs_path/devel/lib
	cp $__cross_target_path/devel/lib/ld-linux.so.3 $__tmp_fs_path/devel/lib
	cp $__cross_target_path/devel/lib/libc.so.6 $__tmp_fs_path/opt/oss/lib
	cp $__cross_target_path/devel/lib/libm.so.6 $__tmp_fs_path/opt/oss/lib
	cp $__cross_target_path/devel/lib/libdl.so.2 $__tmp_fs_path/opt/oss/lib
	cp $__cross_target_path/devel/usr/lib/libgcc_s.so.1 $__tmp_fs_path/opt/oss/lib
	cp $__cross_target_path/devel/usr/lib/libexpat.so.1 $__tmp_fs_path/opt/oss/lib
	cp $__cross_target_path/devel/usr/lib/libstdc++.so.6 $__tmp_fs_path/opt/oss/lib
	cp $__cross_target_path/devel/lib/libpthread.so.0 $__tmp_fs_path/opt/oss/lib
	cp $__cross_target_path/devel/lib/librt.so.1 $__tmp_fs_path/opt/oss/lib

#lib added by yandongdong for diablo_ssh_pppd
	cp $__cross_target_path/devel/lib/libcrypt.so.1 $__tmp_fs_path/opt/oss/lib
	cp $__cross_target_path/devel/lib/libutil.so.1 $__tmp_fs_path/opt/oss/lib
	cp $__cross_target_path/devel/lib/libnsl.so.1 $__tmp_fs_path/opt/oss/lib
	cp $__cross_target_path/devel/lib/libresolv.so.2 $__tmp_fs_path/opt/oss/lib
	cp $__cross_target_path/devel/lib/libnss_files.so.2 $__tmp_fs_path/opt/oss/lib
	cp $__cross_target_path/devel/lib/libpthread.so.0  $__tmp_fs_path/opt/oss/lib
	cp $__cross_target_path/devel/lib/libwrap.so.0 $__tmp_fs_path/opt/oss/lib
	cp $__cross_target_path/devel/usr/lib/libncurses.so.5 $__tmp_fs_path/opt/oss/lib
	cp $__cross_target_path/devel/usr/lib/libz.so.1 $__tmp_fs_path/opt/oss/lib
	cp $__cross_target_path/devel/usr/lib/libcrypto.so.0.9.8 $__tmp_fs_path/opt/oss/lib
	cp $__cross_target_path/devel/usr/lib/libssp.so.0 $__tmp_fs_path/opt/oss/lib
	cp $__cross_target_path/devel/usr/lib/libstdc++.so.6 $__tmp_fs_path/opt/oss/lib
	cp $__cross_target_path/devel/usr/lib/libexpat.so.1 $__tmp_fs_path/opt/oss/lib
	cp $__cross_target_path/devel/usr/lib/libfuse.so.2 $__tmp_fs_path/opt/oss/lib
	cp $__cross_target_path/devel/usr/lib/libl10n.so.7.0 $__tmp_fs_path/opt/oss/lib
	cp $__cross_target_path/devel/usr/lib/libpam.so.0 $__tmp_fs_path/opt/oss/lib

	##strip *.so*
	$__cross_target_path/../../cross/devel/bin/arm-sony-linux-gnueabi-dev-strip `find $__tmp_fs_path/ -name *.so*`

	__tmp=$?
	cd $OLDPWD
	[ $__tmp -eq 0 ] ||return $__tmp
}

make_cpio_initfs()
{
	echo "Making cpio initrd image."
	cd $__tmp_fs_path
	find . | cpio --quiet -c -o | gzip -9 -n > ../$__initrd_image.img
	cd $OLDPWD
}

install_extra_files()
{
	echo "Install extra files."

	[ -d $__tmp_fs_path ] || 
	{
		echo "No Base rootfs before."
		exit 1
	}
#copy_files
#XXX To be improved. Kernel modules.
	[ -d $__kernel_obj_path ] &&
	{
		[ -f $__kernel_obj_path/drivers/usb/gadget/g_file_storage.ko ] &&
		cp $__kernel_obj_path/drivers/usb/gadget/g_file_storage.ko $__tmp_fs_path/opt/sony/modules
		[ -f $__kernel_obj_path/drivers/block/ub.ko ] &&
		cp $__kernel_obj_path/drivers/block/ub.ko $__tmp_fs_path/opt/sony/modules
		[ -f $__kernel_obj_path/arch/arm/mach-diablo/avp13/umscdev/umscdev.ko ] &&
		cp $__kernel_obj_path/arch/arm/mach-diablo/avp13/umscdev/umscdev.ko $__tmp_fs_path/opt/sony/modules
		[ -f $__kernel_obj_path/arch/arm/mach-diablo/avp13/umscdev/umsbdev.ko ] &&
		cp $__kernel_obj_path/arch/arm/mach-diablo/avp13/umscdev/umsbdev.ko $__tmp_fs_path/opt/sony/modules
		cp $__kernel_obj_path/arch/arm/mach-diablo/avp13/umscdev/umsbdev.ko $__tmp_fs_path/lib
		[ -f $__kernel_obj_path/drivers/sxs_tk1/sxs_tk1.ko ] &&
		cp $__kernel_obj_path/drivers/sxs_tk1/sxs_tk1.ko $__tmp_fs_path/opt/sony/modules
		[ -f $__kernel_obj_path/drivers/sxs_tk1_blk/sxs_tk1_blk.ko ] &&
		cp $__kernel_obj_path/drivers/sxs_tk1_blk/sxs_tk1_blk.ko $__tmp_fs_path/opt/sony/modules
	} ||
	{
		echo "Warning: Can't find the kernel build before!!!."
	}

	#find $__tmp_fs_path -name \.svn |xargs rm -rf
	mkdir -p $__tmp_fs_path/tmp/
	#mkdir -p $__tmp_fs_path/SlotA:

#Some extra process for release.
	[ $1 = "release" ] &&
	{
#		#make_initfs_img
		make_cpio_initfs
	} || :
	return $?
}

##########Main function##########
#XXX To be improved
export PATH=$__cross_build_path/devel/bin:${PATH//\/usr\/local\/arm-sony-linux-gnueabi\/devel\/bin:/}

#Check error
check_errors

case $1 in
"release" )
	__rootfs_type=initrd
	;;
"develop" )
	__rootfs_type=nfs
	;;
"clean" )
	clean_up all
	exit $?
	;;
* );;
esac

#Clean previous build files
clean_up build

#Build the busybox
build_busybox

#Clean previous rootfs dirs
clean_up rootfs

#Make a simple rootfs based on installed busybox, and your build environment.
make_base_rootfs

#Install extra files.
install_extra_files $1
