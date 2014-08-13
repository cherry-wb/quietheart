cmd_/root/buildTmp/versionupgrade/sfmemdual_drv/sfmem.o :=  arm-sony-linux-gnueabi-dev-gcc -Wp,-MD,/root/buildTmp/versionupgrade/sfmemdual_drv/.sfmem.o.d  -nostdinc -isystem /usr/local/scel8.0/arm/cross/devel/bin/../../../target/arm/devel/usr/lib/include -Iinclude -Iinclude2 -I/root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include -I/root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include -include include/linux/autoconf.h   -I/root/buildTmp/versionupgrade/sfmemdual_drv -D__KERNEL__ -mlittle-endian   -I/root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/mach-diablo/include -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -fno-delete-null-pointer-checks -Os -marm -fno-omit-frame-pointer -mapcs -mno-sched-prolog -mabi=aapcs-linux -mno-thumb-interwork -D__LINUX_ARM_ARCH__=6 -march=armv6k -mtune=arm1136j-s -msoft-float -Uarm   -I/root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/KMC -Wframe-larger-than=1024 -fno-stack-protector -fno-omit-frame-pointer -fno-optimize-sibling-calls -g -Wdeclaration-after-statement -Wno-pointer-sign -fwrapv -fno-dwarf2-cfi-asm  -DMODULE -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(sfmem)"  -D"KBUILD_MODNAME=KBUILD_STR(sfmem)"  -c -o /root/buildTmp/versionupgrade/sfmemdual_drv/.tmp_sfmem.o /root/buildTmp/versionupgrade/sfmemdual_drv/sfmem.c

deps_/root/buildTmp/versionupgrade/sfmemdual_drv/sfmem.o := \
  /root/buildTmp/versionupgrade/sfmemdual_drv/sfmem.c \
    $(wildcard include/config/sfmem/debug.h) \
    $(wildcard include/config/avp17/support.h) \
    $(wildcard include/config/dual/flash.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/kernel.h \
    $(wildcard include/config/lbd.h) \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/spinlock/sleep.h) \
    $(wildcard include/config/debug/preempt.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/panic.h) \
    $(wildcard include/config/full/panic.h) \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/printk/func.h) \
    $(wildcard include/config/avp17/nath.h) \
    $(wildcard include/config/preempt/rt.h) \
    $(wildcard include/config/dynamic/printk/debug.h) \
    $(wildcard include/config/ring/buffer.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/snsc.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
  /usr/local/scel8.0/arm/cross/devel/bin/../../../target/arm/devel/usr/lib/include/stdarg.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/linkage.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/compiler.h \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/compiler-gcc.h \
    $(wildcard include/config/measure/inlines.h) \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/compiler-gcc4.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/linkage.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/stddef.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/types.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/asm-generic/int-ll64.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/posix_types.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/posix_types.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/bitops.h \
    $(wildcard include/config/generic/find/first/bit.h) \
    $(wildcard include/config/generic/find/last/bit.h) \
    $(wildcard include/config/generic/find/next/bit.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/bitops.h \
    $(wildcard include/config/smp.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/system.h \
    $(wildcard include/config/cpu/xsc3.h) \
    $(wildcard include/config/arch/has/barriers.h) \
    $(wildcard include/config/snsc/disable/want/interrupts/on/ctxsw.h) \
    $(wildcard include/config/cpu/sa1100.h) \
    $(wildcard include/config/cpu/sa110.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/irqflags.h \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/snsc/lite/irqsoff.h) \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/snsc/lite/preemptoff.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
    $(wildcard include/config/x86.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/typecheck.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/irqflags.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/ptrace.h \
    $(wildcard include/config/cpu/endian/be8.h) \
    $(wildcard include/config/arm/thumb.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/hwcap.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/outercache.h \
    $(wildcard include/config/outer/cache/sync.h) \
    $(wildcard include/config/outer/cache.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/memory.h \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/ej/split/pagetable.h) \
    $(wildcard include/config/page/offset.h) \
    $(wildcard include/config/dram/size.h) \
    $(wildcard include/config/dram/base.h) \
    $(wildcard include/config/cpu/afe.h) \
    $(wildcard include/config/zone/dma.h) \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/sparsemem.h) \
    $(wildcard include/config/arch/populates/node/map.h) \
    $(wildcard include/config/have/arch/early/pfn/to/nid.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/const.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/mach-diablo/include/mach/memory.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/sizes.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/asm-generic/memory_model.h \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/sparsemem/vmemmap.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/asm-generic/cmpxchg-local.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/asm-generic/cmpxchg.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/asm-generic/bitops/non-atomic.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/asm-generic/bitops/fls64.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/asm-generic/bitops/sched.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/asm-generic/bitops/hweight.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/asm-generic/bitops/lock.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/ratelimit.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/param.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/param.h \
    $(wildcard include/config/hz.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/dynamic_printk.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/byteorder.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/byteorder/little_endian.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/swab.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/swab.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/byteorder/generic.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/debug/bugverbose.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/asm-generic/bug.h \
    $(wildcard include/config/generic/bug.h) \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/module.h \
    $(wildcard include/config/lkm/elf/hash.h) \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/unused/symbols.h) \
    $(wildcard include/config/kallsyms.h) \
    $(wildcard include/config/markers/struct.h) \
    $(wildcard include/config/tracepoints/struct.h) \
    $(wildcard include/config/module/unload.h) \
    $(wildcard include/config/snsc/ssboot.h) \
    $(wildcard include/config/snsc/prelinko.h) \
    $(wildcard include/config/sysfs.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/list.h \
    $(wildcard include/config/debug/list.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/poison.h \
    $(wildcard include/config/illegal/pointer/value.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/prefetch.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/processor.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/cache.h \
    $(wildcard include/config/arm/l1/cache/shift.h) \
    $(wildcard include/config/aeabi.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/stat.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/stat.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/time.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/cache.h \
    $(wildcard include/config/arch/has/cache/line/size.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/seqlock.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/pickop.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/spinlock.h \
    $(wildcard include/config/generic/lockbreak.h) \
    $(wildcard include/config/debug/spinlock.h) \
    $(wildcard include/config/preempt.h) \
    $(wildcard include/config/debug/lock/alloc.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/preempt.h \
    $(wildcard include/config/preempt/notifiers.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/thread_info.h \
    $(wildcard include/config/compat.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/thread_info.h \
    $(wildcard include/config/snsc/debug/stack/limit.h) \
    $(wildcard include/config/snsc/debug/stack/limit/manual.h) \
    $(wildcard include/config/snsc/debug/stack/limit/bytes.h) \
    $(wildcard include/config/arm/thumbee.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/fpstate.h \
    $(wildcard include/config/vfpv3.h) \
    $(wildcard include/config/iwmmxt.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/page.h \
    $(wildcard include/config/cpu/copy/v3.h) \
    $(wildcard include/config/cpu/copy/v4wt.h) \
    $(wildcard include/config/cpu/copy/v4wb.h) \
    $(wildcard include/config/cpu/copy/feroceon.h) \
    $(wildcard include/config/cpu/xscale.h) \
    $(wildcard include/config/cpu/copy/v6.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/glue.h \
    $(wildcard include/config/cpu/arm610.h) \
    $(wildcard include/config/cpu/arm710.h) \
    $(wildcard include/config/cpu/abrt/lv4t.h) \
    $(wildcard include/config/cpu/abrt/ev4.h) \
    $(wildcard include/config/cpu/abrt/ev4t.h) \
    $(wildcard include/config/cpu/abrt/ev5tj.h) \
    $(wildcard include/config/cpu/abrt/ev5t.h) \
    $(wildcard include/config/cpu/abrt/ev6.h) \
    $(wildcard include/config/cpu/abrt/ev7.h) \
    $(wildcard include/config/cpu/pabrt/legacy.h) \
    $(wildcard include/config/cpu/pabrt/v6.h) \
    $(wildcard include/config/cpu/pabrt/v7.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/asm-generic/page.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/domain.h \
    $(wildcard include/config/io/36.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/stringify.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/bottom_half.h \
    $(wildcard include/config/preempt/hardirqs.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/spinlock_types.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/spinlock_types_up.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/lockdep.h \
    $(wildcard include/config/lockdep.h) \
    $(wildcard include/config/lock/stat.h) \
    $(wildcard include/config/lock/stat/histogram.h) \
    $(wildcard include/config/generic/hardirqs.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/spinlock_up.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/rt_lock.h \
    $(wildcard include/config/debug/rt/mutexes.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/rtmutex.h \
    $(wildcard include/config/rt/mutexes.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/plist.h \
    $(wildcard include/config/debug/pi/list.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/atomic.h \
    $(wildcard include/config/arm/errata/351422.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/asm-generic/atomic.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/spinlock_api_up.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/math64.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/div64.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/kmod.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/gfp.h \
    $(wildcard include/config/kmemcheck.h) \
    $(wildcard include/config/snsc/use/node/order.h) \
    $(wildcard include/config/snsc/thread/rss.h) \
    $(wildcard include/config/zone/dma32.h) \
    $(wildcard include/config/highmem.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/mmzone.h \
    $(wildcard include/config/force/max/zoneorder.h) \
    $(wildcard include/config/unevictable/lru.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/snsc/kswapd/variable/def/priority.h) \
    $(wildcard include/config/snsc/kswapd/dynamic/def/priority.h) \
    $(wildcard include/config/snsc/kswapd/def/priority.h) \
    $(wildcard include/config/flat/node/mem/map.h) \
    $(wildcard include/config/cgroup/mem/res/ctlr.h) \
    $(wildcard include/config/have/memory/present.h) \
    $(wildcard include/config/need/node/memmap/size.h) \
    $(wildcard include/config/need/multiple/nodes.h) \
    $(wildcard include/config/snsc/section/nr/out/of/page/flag.h) \
    $(wildcard include/config/sparsemem/extreme.h) \
    $(wildcard include/config/nodes/span/other/nodes.h) \
    $(wildcard include/config/holes/in/zone.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/wait.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/current.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/threads.h \
    $(wildcard include/config/nr/cpus.h) \
    $(wildcard include/config/base/small.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/numa.h \
    $(wildcard include/config/nodes/shift.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/init.h \
    $(wildcard include/config/snsc/deferred/initcalls.h) \
    $(wildcard include/config/snsc/boot/time.h) \
    $(wildcard include/config/hotplug.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/kmc/kmc.h \
    $(wildcard include/config/kmc/patch.h) \
    $(wildcard include/config/kmc/linux/profile.h) \
    $(wildcard include/config/kmc/eventtracker/support.h) \
    $(wildcard include/config/kmc/module/debug/new.h) \
    $(wildcard include/config/kmc/patch/struct.h) \
    $(wildcard include/config/kmc/module/auto.h) \
    $(wildcard include/config/kmc/ice/chk/mod/deb.h) \
    $(wildcard include/config/kmc/partner/collect/thread/off.h) \
    $(wildcard include/config/kmc/partner/virtual/ice/off.h) \
    $(wildcard include/config/kmc/trace/ext/off.h) \
    $(wildcard include/config/mn10300.h) \
    $(wildcard include/config/kmc/partner/available/off.h) \
    $(wildcard include/config/arm.h) \
    $(wildcard include/config/cpu/v6.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/kmc/__brk_code.h \
    $(wildcard include/config/cpu/v7.h) \
    $(wildcard include/config/mips.h) \
    $(wildcard include/config/cpu/tx49xx.h) \
    $(wildcard include/config/cpu/sh4.h) \
    $(wildcard include/config/cpu/sh3.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/nodemask.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/bitmap.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/string.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/pageblock-flags.h \
    $(wildcard include/config/hugetlb/page.h) \
    $(wildcard include/config/hugetlb/page/size/variable.h) \
    $(wildcard include/config/section/nr/out/of/page/flag.h) \
  include/linux/bounds.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/memory_hotplug.h \
    $(wildcard include/config/have/arch/nodedata/extension.h) \
    $(wildcard include/config/memory/hotremove.h) \
    $(wildcard include/config/snsc/memplug/verbose.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/notifier.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/errno.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/errno.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/asm-generic/errno.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/asm-generic/errno-base.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/mutex.h \
    $(wildcard include/config/debug/mutexes.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/rwsem.h \
    $(wildcard include/config/rwsem/generic/spinlock.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/rwsem-spinlock.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/srcu.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/topology.h \
    $(wildcard include/config/sched/smt.h) \
    $(wildcard include/config/sched/mc.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/cpumask.h \
    $(wildcard include/config/disable/obsolete/cpumask/functions.h) \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/cpumask/offstack.h) \
    $(wildcard include/config/debug/per/cpu/maps.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/smp.h \
    $(wildcard include/config/use/generic/smp/helpers.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/topology.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/asm-generic/topology.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/elf.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/elf-em.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/elf.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/user.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/kobject.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/sysfs.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/kref.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/moduleparam.h \
    $(wildcard include/config/alpha.h) \
    $(wildcard include/config/ia64.h) \
    $(wildcard include/config/ppc64.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/immediate.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/marker.h \
    $(wildcard include/config/markers.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/ltt-channels.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/limits.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/tracepoint.h \
    $(wildcard include/config/tracepoints.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/rcupdate.h \
    $(wildcard include/config/ej/rcu/sony.h) \
    $(wildcard include/config/ej/rcu/sony/batch/mode.h) \
    $(wildcard include/config/no/hz.h) \
    $(wildcard include/config/classic/rcu.h) \
    $(wildcard include/config/tree/rcu.h) \
    $(wildcard include/config/preempt/rcu.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/completion.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/rcuclassic.h \
    $(wildcard include/config/rcu/cpu/stall/detector.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/local.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/asm-generic/local.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/percpu.h \
    $(wildcard include/config/have/dynamic/per/cpu/area.h) \
    $(wildcard include/config/debug/kmemleak.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/slab.h \
    $(wildcard include/config/slab/debug.h) \
    $(wildcard include/config/debug/objects.h) \
    $(wildcard include/config/debug/slab/account.h) \
    $(wildcard include/config/slub.h) \
    $(wildcard include/config/slob.h) \
    $(wildcard include/config/debug/slab.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/slub_def.h \
    $(wildcard include/config/slub/stats.h) \
    $(wildcard include/config/slub/debug.h) \
    $(wildcard include/config/kmemtrace.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/workqueue.h \
    $(wildcard include/config/ej/on/each/cpu/threaded.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/timer.h \
    $(wildcard include/config/timer/stats.h) \
    $(wildcard include/config/debug/objects/timers.h) \
    $(wildcard include/config/preempt/softirqs.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/ktime.h \
    $(wildcard include/config/ktime/scalar.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/jiffies.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/timex.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/timex.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/mach-diablo/include/mach/timex.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/debugobjects.h \
    $(wildcard include/config/debug/objects/free.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/kmemleak.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/trace/kmemtrace.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/pfn.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/percpu.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/asm-generic/percpu.h \
    $(wildcard include/config/have/setup/per/cpu/area.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/module.h \
    $(wildcard include/config/arm/unwind.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/fs.h \
    $(wildcard include/config/dnotify.h) \
    $(wildcard include/config/quota.h) \
    $(wildcard include/config/inotify.h) \
    $(wildcard include/config/security.h) \
    $(wildcard include/config/epoll.h) \
    $(wildcard include/config/debug/writecount.h) \
    $(wildcard include/config/file/locking.h) \
    $(wildcard include/config/snsc/fs/fat/batch/sync.h) \
    $(wildcard include/config/auditsyscall.h) \
    $(wildcard include/config/block.h) \
    $(wildcard include/config/fs/xip.h) \
    $(wildcard include/config/migration.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/ioctl.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/ioctl.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/asm-generic/ioctl.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/kdev_t.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/dcache.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/rculist.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/path.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/radix-tree.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/prio_tree.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/pid.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/capability.h \
    $(wildcard include/config/security/file/capabilities.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/semaphore.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/fiemap.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/quota.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/dqblk_xfs.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/dqblk_v1.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/dqblk_v2.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/dqblk_qtree.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/nfs_fs_i.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/nfs.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/sunrpc/msg_prot.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/fcntl.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/fcntl.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/asm-generic/fcntl.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/err.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/cdev.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/delay.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/delay.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/io.h \
    $(wildcard include/config/arch/emxx.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/mach-diablo/include/mach/io.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/mach-diablo/include/mach/hardware.h \
    $(wildcard include/config/mach/avp13.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/mach-diablo/include/mach/pci.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/mach-diablo/include/mach/vic.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/mach-diablo/include/mach/timer.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/mach-diablo/include/mach/uart.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/uaccess.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/mach-diablo/include/mach/gpio.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/interrupt.h \
    $(wildcard include/config/net.h) \
    $(wildcard include/config/ej/load/balance/in/timer/softirq.h) \
    $(wildcard include/config/generic/irq/probe.h) \
    $(wildcard include/config/proc/fs.h) \
    $(wildcard include/config/debug/shirq.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/irqreturn.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/irqnr.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/hardirq.h \
    $(wildcard include/config/virt/cpu/accounting.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/smp_lock.h \
    $(wildcard include/config/lock/kernel.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/sched.h \
    $(wildcard include/config/sched/debug.h) \
    $(wildcard include/config/x86/local/apic.h) \
    $(wildcard include/config/ej/simplify/sched.h) \
    $(wildcard include/config/detect/softlockup.h) \
    $(wildcard include/config/detect/hung/task.h) \
    $(wildcard include/config/core/dump/default/elf/headers.h) \
    $(wildcard include/config/bsd/process/acct.h) \
    $(wildcard include/config/taskstats.h) \
    $(wildcard include/config/audit.h) \
    $(wildcard include/config/inotify/user.h) \
    $(wildcard include/config/posix/mqueue.h) \
    $(wildcard include/config/keys.h) \
    $(wildcard include/config/user/sched.h) \
    $(wildcard include/config/schedstats.h) \
    $(wildcard include/config/task/delay/acct.h) \
    $(wildcard include/config/fair/group/sched.h) \
    $(wildcard include/config/rt/group/sched.h) \
    $(wildcard include/config/blk/dev/io/trace.h) \
    $(wildcard include/config/x86/ptrace/bts.h) \
    $(wildcard include/config/sysvipc.h) \
    $(wildcard include/config/debug/psrwlock.h) \
    $(wildcard include/config/task/xacct.h) \
    $(wildcard include/config/cpusets.h) \
    $(wildcard include/config/cgroups.h) \
    $(wildcard include/config/futex.h) \
    $(wildcard include/config/fault/injection.h) \
    $(wildcard include/config/latencytop.h) \
    $(wildcard include/config/function/graph/tracer.h) \
    $(wildcard include/config/snsc/save/affinity.h) \
    $(wildcard include/config/max/user/rt/prio.h) \
    $(wildcard include/config/have/unstable/sched/clock.h) \
    $(wildcard include/config/debug/stack/usage.h) \
    $(wildcard include/config/preempt/bkl.h) \
    $(wildcard include/config/group/sched.h) \
    $(wildcard include/config/mm/owner.h) \
    $(wildcard include/config/snsc/set/thread/priority.h) \
    $(wildcard include/config/snsc/migration/disable/enable/inline.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/rbtree.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/mm_types.h \
    $(wildcard include/config/split/ptlock/cpus.h) \
    $(wildcard include/config/mmu/notifier.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/auxvec.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/auxvec.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/mmu.h \
    $(wildcard include/config/cpu/has/asid.h) \
    $(wildcard include/config/ej/simple/asid.h) \
    $(wildcard include/config/ej/max/concurrent/255.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/cputime.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/asm-generic/cputime.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/sem.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/ipc.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/ipcbuf.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/sembuf.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/signal.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/signal.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/asm-generic/signal.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/sigcontext.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/siginfo.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/asm-generic/siginfo.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/fs_struct.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/perf_counter.h \
    $(wildcard include/config/bits.h) \
    $(wildcard include/config/shift.h) \
    $(wildcard include/config/mask.h) \
    $(wildcard include/config/perf/counters.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/hrtimer.h \
    $(wildcard include/config/high/res/timers.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/proportions.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/percpu_counter.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/seccomp.h \
    $(wildcard include/config/seccomp.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/resource.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/resource.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/asm-generic/resource.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/task_io_accounting.h \
    $(wildcard include/config/task/io/accounting.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/latencytop.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/cred.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/key.h \
    $(wildcard include/config/sysctl.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/sysctl.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/securebits.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/aio.h \
    $(wildcard include/config/aio.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/aio_abi.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/uio.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/ftrace_irq.h \
    $(wildcard include/config/ftrace/nmi/enter.h) \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/hardirq.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/include/asm/irq.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/arch/arm/mach-diablo/include/mach/irqs.h \
  /root/buildTmp/eu11_environment/IA/C16/PFXBase_C16_Must/Operatingsystems/CELinux/Diablo/kernel/scel-8.0/Kernel/include/linux/irq_cpustat.h \

/root/buildTmp/versionupgrade/sfmemdual_drv/sfmem.o: $(deps_/root/buildTmp/versionupgrade/sfmemdual_drv/sfmem.o)

$(deps_/root/buildTmp/versionupgrade/sfmemdual_drv/sfmem.o):
