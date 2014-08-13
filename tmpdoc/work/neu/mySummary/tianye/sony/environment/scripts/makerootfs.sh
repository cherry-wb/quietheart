#!/bin/bash
########Notation for development#########
#This script is made by Neusoft.
#1, Comment with "#XXX" needs to be improved in the future.
#2, If you "cd" to some path in sub_function, you must "cd OLDPWD" before return.
#########################################

########Global Variables#########
#This value can be "develop" or "release" now.
#XXX To be improved for some related name. e.g. busybox config file name etc.
__build_mode=develop
#__build_mode=release

#XXX Is it needed? if compress the ramdisk.img set it to y,or set it to n
__image_compress=n

#XXX For time to see how long it needed to build.
__build_start_time="00:00:00"
__build_end_time="00:00:00"

# As if current dir is "makerootfs"
__prj_path=$(cd $(dirname $0)/../;pwd)
__release_dir=$(basename $(cd $(dirname $0);pwd))
__build_path=$__prj_path/diablo/diabloMainCpu/build/
__target_path=$__prj_path/$__release_dir/target
__rootfs_path=$__target_path/$__build_mode
__rootfs_dir=rootfs_$(date +%F)
__initrd_image=ramdisk
__busybox_dir=busybox-dev
__cross_build_path=/usr/local/arm-sony-linux-gnueabi

#XXX Temp dir for making rootfs
export __tmp_fs_path=$__prj_path/$__release_dir/tempFs

############Functions############
show_help()
{
	echo "Help info:"
	echo "========================="
	echo "Usage:$0 [busybox[ release |develop] |build[ release |develop]"
	echo "                        |rootfs |develop |release |all |clean]"
	echo ""
	echo "Example:"
	echo "0,Show help info:"
	echo "$0"
	echo ""
	echo "1,Clean up all intermediate files:"
	echo "$0 clean"
	echo "Note: This will clean up all the previous intermediate files."
	echo ""
	echo "2,Build and make rootfs for release and develop:"
	echo "$0 all"
	echo "Note: This likes \"$0 release && $0 develop\" below but save more time as it based on previous build."
	echo ""
	echo "3,Build busybox for develop only:"
	echo "$0 busybox develop"
	echo "Note: This build busybox for develop.The \"develop\" parameter can be omitted."
	echo ""
	echo "4,Build busybox for release only:"
	echo "$0 busybox release"
	echo "Note: This build busybox for release."
	echo ""
	echo "5,Build the application \"diablo.bin\" and prepare rootfs type for release:"
	echo "$0 build release"
	echo "Note: This will build \"diablo.bin\", and made following \"$0 rootfs\" for \"release\"."
	echo "      This command build only the latest changed files."
	echo "      You must make sure that the busybox has been built for \"release\"."
	echo ""
	echo "6,Build the application \"diablo.bin\" and prepare rootfs type for develop:"
	echo "$0 build develop"
	echo "Note: This will build \"diablo.bin\", and made following \"$0 rootfs\" for \"develop\"."
	echo "      This command build only the latest changed files."
	echo "      You must make sure that the busybox has been built for \"develop\"."
	echo "      The parameter \"develop\" can be omitted."
	echo ""
	echo "7,Make rootfs only:"
	echo "$0 rootfs"
	echo "Note: Must run it after \"$0 busybox[ develop |release]\" and \"$0 build[ develop |release]\""
	echo ""
	echo "8,Build and make rootfs for development:"
	echo "$0 develop"
	echo "Note: This can automatically clean previous results and do the following:"
	echo "a)build the busybox"
	echo "b)build the application diablo.bin"
	echo "c)make the final (nfs)rootfs for development in $__target_path/develop."
	echo ""
	echo "9,Build and make rootfs for release:"
	echo "$0 release"
	echo "Note: This can automatically clean previous results and do the following:"
	echo "a)build the busybox"
	echo "b)build the application diablo.bin"
	echo "c)make the final (initrd)rootfs for release in $__target_path/release."
	echo ""
	echo "Note: You must be 'root' and it's best to run this script in where it stays."
	echo "========================="
	exit 1
}

check_errors()
{
	#echo "Checking errors."
	echo ""
	local __real_mode
	if [ $# -eq 0 ]
	then
		[ -d $__cross_build_path/bin ] ||
		{
			echo "No cross build tools."
			exit 1
		}
	fi

	[ $1 ] && [ $1 = "build_mode" ] &&
	{
		#XXX To be improved. Currently, assume "statically" busybox used for release.
		file $__tmp_fs_path/bin/busybox |grep -q statically
		[ $? -eq 0 ] && __real_mode="release" || __real_mode="develop"
		if [ $__build_mode = $__real_mode ]
		then
			return 0
		else
			echo "Error: Last real mode is \"$__real_mode\" but your set the mode to \"$__build_mode\""
			echo "       You should run :\"$0 build $__real_mode\" instead."
			return 1
		fi
	}
}

adjust_mode()
{
		local __real_mode
		[ -f $__tmp_fs_path/bin/busybox ] || return 1
		#XXX To be improved. Currently, assume "statically" busybox used for release.
		file $__tmp_fs_path/bin/busybox |grep -q statically
		[ $? -eq 0 ] && __real_mode="release" || __real_mode="develop"
		set_mode $__real_mode
		return $?
}

switch_mode()
{
		local __switch_mode
		[ -f $__tmp_fs_path/bin/busybox ] || return 1
		#XXX To be improved. Currently, assume "dynamically" busybox used for develop.
		file $__tmp_fs_path/bin/busybox |grep -q dynamically
		[ $? -eq 0 ] && __switch_mode="release" || __switch_mode="develop"
		set_mode $__switch_mode
		return $?
}

build_busybox()
{
	echo "Building busybox."
	echo "================"

	cd $__prj_path/$__busybox_dir
	./build_busybox.sh $1
	local __tmp_return=$?
	cd $OLDPWD
	echo "Build busybox end."
	echo "================"
	return $__tmp_return
}

build_src()
{
	echo "Building src."
	echo "================"

	cd $__build_path

	#build from beginning
	echo "Building."
	[ $1 ] && [ $1 = "depend" ] && ./build.sh depend
	./build.sh
	local __tmp_return=$?

	cd $OLDPWD
	echo "Build src end!"
	echo "================"
	return $__tmp_return
}

copy_files()
{
	echo "Copying files."
	local __code_dir=diablo
	for __file in $(ls $__tmp_fs_path)
	do
		#echo "copying $__file to $__rootfs_path/$__rootfs_dir"
		mkdir -p $__rootfs_path/$__rootfs_dir
		cp -a $__tmp_fs_path/$__file $_
	done
	echo "Copying diablo.bin"
	mkdir -p $__rootfs_path/$__rootfs_dir/$__code_dir/diabloMainCpu/
	cp $__code_dir/diabloMainCpu/build/diablo.bin $_

	#XXX To be improved. Dynamic link for oswrapper or not?
	#cp $__code_dir/diabloMainCpu/osWrapper/lib*.so $__rootfs_path/$__rootfs_dir/usr/lib/

	find $__rootfs_path/$__rootfs_dir -name \.svn |xargs rm -rf
	mkdir -p $__rootfs_path/$__rootfs_dir/tmp/
	mkdir -p $__rootfs_path/$__rootfs_dir/SlotA:
	return $?
}

strip_bins()
{
	echo "Stripping bins."
	for __file in $(ls \
	$__rootfs_path/$__rootfs_dir/lib/* \
	$__rootfs_path/$__rootfs_dir/diablo/diabloMainCpu/*)
	#$__rootfs_path/$__rootfs_dir/bin/* \
	#$__rootfs_path/$__rootfs_dir/sbin/* \
	#$__rootfs_path/$__rootfs_dir/usr/lib/* \
	#$__rootfs_path/$__rootfs_dir/usr/bin/* \
	#$__rootfs_path/$__rootfs_dir/usr/sbin/* \
	do
		file $__file | grep -q ELF && arm-sony-linux-gnueabi-strip $__file
	done

	arm-sony-linux-gnueabi-objcopy -R .comment $__rootfs_path/$__rootfs_dir/diablo/diabloMainCpu/diablo.bin

	local __tmp_return=$?
	
	#Note:Compress and will decompress into memory when system boot
	#delete for no tar diablo.bin{
	#echo "Compressing diablo.bin."
	#cd $__rootfs_path/$__rootfs_dir/diablo/diabloMainCpu/
	#tar -czvf diablo.bin.tgz diablo.bin
	#__tmp_return=$?
	#rm diablo.bin
	#cd $__OLDPWD
	#delete for no tar diablo.bin}

	#gzexe can compress the diablo.bin to 4m,but run time more longer

	return $__tmp_return
}

change_links_test()
{
	echo "Change links."
}

change_links()
{
#This function used to change softlink to hardlink to reduce size.
#Note:Not directly build busybox with hardlink because it is more complicated for makerootfs scripts.
	for __file in $(ls $1)
	do
		[ -L $1/$__file ] && 
		{
			local __realfile=$(readlink $1/$__file)
			rm $1/$__file
			ln $1/$__realfile $1/$__file
		}
	done
	return $?
}

#XXX Is it needed?(replaced with change_links?)
remove_liblinks()
{
	for __file in $(ls $1)
	do
		[ -L $1/$__file ] && 
		{
			local __realfile=$(readlink $1/$__file)
			rm $1/$__file
			ln $1/$__realfile $1/$__file
		}
	done

	#for __file in $(ls $1/lib*.so.*)
	#do
	#	mv $__file ${__file/.so.*/.so}
	#done
}

make_dev_nodes()
{
	echo "Making device nodes."

	[ $UID -eq 0 ] ||
	{
		echo "Making rootfs failed, can't make device nodes, because current user isn't root."
		exit 1
	}
	mknod $1/dev/null c 1 3 
	mknod $1/dev/ttyS0 c 4 64
	mknod $1/dev/ram1 b 1 1 
	#mknod $1/dev/sxs_blk0 b 288 1
	mknod $1/dev/sxs_blk0 c 288 0
	#mknod $1/dev/console c 5 1
	mknod $1/dev/diablo_self_diagnose c 236 0
	mknod $1/dev/debugDriver c 237 0
	mknod $1/dev/sysconif c 238 0
	mknod $1/dev/vrefDriver c 239 0
	mknod $1/dev/avselDriver c 240 0
	mknod $1/dev/diablo_bsif c 241 0
	mknod $1/dev/torino c 242 0
	mknod $1/dev/gpio_hlc c 243 0
	mknod $1/dev/hfdma_dev c 244 0
	mknod $1/dev/memoryDriver c 245 0
	mknod $1/dev/avp13_sync c 246 0
	mknod $1/dev/diablo_cmn_debug c 247 0
	mknod $1/dev/lpcm c 248 0
	mknod $1/dev/expcd c 249 0
	mknod $1/dev/ddvcd c 250 0
	mknod $1/dev/sfmem c 251 0
	mknod $1/dev/dsphost c 252 0
	mknod $1/dev/cpu1Driver c 255 0
	mknod $1/dev/umsc0 c 260 0
	mknod $1/dev/umsc1 c 260 1
	mknod $1/dev/CodecSimulatorDrv c 261 0
}

make_rootfs()
{
	echo "Making rootfs."
	echo "================"

	cd $__prj_path/
#XXX To be improved this path used currently for test.
	[ -f $__build_path/diablo.bin ] || 
	{
		echo "No Build before."
		exit 1
	}
	echo "Removing earlier install."
#XXX To be improved: Maybe will make a backup instead of "rm" if for convenience.
	[ -d $__rootfs_path ] && rm -rf $__rootfs_path
	copy_files
	[ $1 = "release" ] &&
	{
		strip_bins
		change_links $__rootfs_path/$__rootfs_dir/bin
		change_links $__rootfs_path/$__rootfs_dir/sbin
		change_links $__rootfs_path/$__rootfs_dir/usr/bin
		#change_links $__rootfs_path/$__rootfs_dir/usr/sbin
	
		#remove_liblinks $__rootfs_path/$__rootfs_dir/usr/lib
		remove_liblinks $__rootfs_path/$__rootfs_dir/lib
	
		make_dev_nodes $__rootfs_path/$__rootfs_dir
	
		#make_initfs_img
		make_cpio_initfs
	}

#XXX To be improved. Don't "cd $OLDPWD" to match the previous "cd"??
	cd $__rootfs_path/
	echo "Packing rootfs to $__rootfs_dir.tbz"
	tar -cjf $__rootfs_dir.tbz $__rootfs_dir
	local __tmp_return=$?
	cd $OLDPWD

	echo "Make rootfs end."
	echo "================"
	return $__tmp_return
}

make_cpio_initfs()
{
	echo "Making cpio initrd image."
	cd $__rootfs_path/$__rootfs_dir

	if [ $__image_compress = "y" ]
	then
		find . | cpio --quiet -c -o | gzip -9 -n > ../$__initrd_image.img
	elif [ $__image_compress = "n" ]
	then
		find . | cpio --quiet -c -o > ../$__initrd_image.img
	fi
	cd $OLDPWD
}

make_initfs_img()
{
	echo "Making initrd image."
	local __tmp_return=1
	[ $UID -eq 0 ] ||
	{
		echo "Making initrd image failed, user not root."
		return $__tmp_return
	}
	[ $UID -eq 0 ] &&
	{
		mknod $__rootfs_path/$__rootfs_dir/dev/ram0 b 1 0
		mknod $__rootfs_path/$__rootfs_dir/dev/ram1 b 1 1

		dd if=/dev/zero of=$__rootfs_path/$__initrd_image bs=1M count=16
		/sbin/mkfs.ext2 -m0 $__rootfs_path/$__initrd_image
		mkdir $__rootfs_path/tmpmnt
		mount -o loop $__rootfs_path/$__initrd_image $_
		cp -a $__rootfs_path/$__rootfs_dir/* $_
		umount $_
		rm -r $_
		cd $__rootfs_path
		gzip -v9 $__initrd_image && mv $_.gz $_.img
		__tmp_return=$?
		cd $OLDPWD
		return $__tmp_return
   }
}

#XXX To be improved for running clean_up in proper place especially "busybox" and "rootfs".
clean_up()
{
	local __tmp_return=$?
	case $1 in
	"busybox" )
		cd $__prj_path/$__busybox_dir
		echo "Cleaning busybox files."
		./build_busybox.sh clean
		__tmp_return = $?
		cd $OLDPWD
		;;
	"build" )
		cd $__build_path
		echo "Cleaning earlier build files."
		./build.sh clean
		__tmp_return = $?
		cd $OLDPWD
		;;
	"rootfs" )
		echo "Removing earlier rootfs install."
		[ -d $__target_path ] && rm -rf $__target_path
		__tmp_return = $?
		;;
	"all" )
		echo "Cleaning busybox files."
		cd $__prj_path/$__busybox_dir
		./build_busybox.sh clean
		cd $OLDPWD
		echo "Cleaning earlier build files."
		cd $__build_path
		./build.sh clean
		cd $OLDPWD
		echo "Removing earlier rootfs install."
		[ -d $__target_path ] && rm -rf $__target_path
		[ -d $__tmp_fs_path ] && rm -rf $__tmp_fs_path
		__tmp_return=$?
		;;
	*)
		echo "Error usage: what parameter?"
		;;
	esac
	return $__tmp_return
}

set_mode()
{
	__build_mode=$1
	__rootfs_path=$__target_path/$__build_mode
}

##########Main function##########
#XXX To be improved for the following:
#(1)Should we declare the environment?
#(2)Should we add a "clean" option?

#XXX Time test
__build_start_time=$(date +%H:%M:%S)

export PATH=$__cross_build_path/bin:${PATH//\/usr\/local\/arm-sony-linux-gnueabi\/bin:/}


#XXX To be improved. Change to script directory in case some wrongs.(should delete this if sure no problem)
cd $__prj_path/$__release_dir
cd $__prj_path/$__release_dir

#Error use
[ $# -ne 0 ] && [ $# -ne 1 ] && [ $# -ne 2 ] && show_help

#Error check 
check_errors

case $1 in
"busybox" )
	echo "Build busybox only!"
	[ $2 ] && 
	{
		set_mode $2
	} 
	#XXX To be improved. Value of __build_mode fixed?
	[ $__build_mode = "develop" ] || [ $__build_mode = "release" ] &&
	{
		echo "Build mode is $__build_mode"
		build_busybox $__build_mode
	} ||
	{
		echo "Parameter \"$__build_mode\" unknowned."
		show_help
		exit 1
	}
	exit $?
	;;
"build" )
	echo "Build app only!"
	[ $2 ] && 
	{
		set_mode $2
	} 
	#XXX To be improved. Value of __build_mode fixed?this $2 parameter is only for remark, it has no use!!!
	[ $__build_mode = "develop" ] || [ $__build_mode = "release" ] &&
	{
		echo "Build mode is $__build_mode"
		check_errors build_mode || exit 1
		build_src
	} ||
	{
		echo "Parameter \"$__build_mode\" unknowned."
		show_help
		exit 1
	}
	;;
"rootfs" )
	echo "Make rootfs only!"
	adjust_mode
	make_rootfs $__build_mode
	;;
"develop" )
	clean_up all
	echo "Build and make rootfs for development."
	set_mode develop
	build_busybox $__build_mode && build_src depend && make_rootfs $__build_mode
	;;
"release" )
	clean_up all
	echo "Build and make rootfs for release."
	set_mode release
	build_busybox $__build_mode && build_src depend && make_rootfs $__build_mode
	;;
"all" )
	echo "Build and make rootfs for release and development ."
	#XXX To be improved following:
	#(1) switch_mode with "||" test has effect?
	#(2) Here release before develop,for default $buildmode of the "rootfs" option is "develop" ok?.

	echo "Making image for all......"
	adjust_mode &&
	{
		build_src && make_rootfs $__build_mode
	} ||
	{
		#For the first time without previous build result.
		set_mode release
		build_busybox $__build_mode && build_src depend && make_rootfs $__build_mode
	}
	echo "Image for $__build_mode has been made!"
	echo ""
	switch_mode || set_mode develop
	build_busybox $__build_mode && make_rootfs $__build_mode
	echo "Image for $__build_mode has been made!"
	echo ""
	;;
"clean" )
	echo "Clean all......"
	clean_up all
	;;
* )
	#Default action
	show_help
	;;
esac

__tmp_return=$?

#XXX Time test
__build_end_time=$(date +%H:%M:%S)
echo "Running time is between $__build_start_time --- $__build_end_time."

exit $__tmp_return
