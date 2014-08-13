#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
};

static const struct modversion_info ____versions[]
__attribute_used__
__attribute__((section("__versions"))) = {
	{ 0x89e24b9c, "struct_module" },
	{ 0x1bcd461f, "_spin_lock" },
	{ 0x5e22fdec, "cdev_add" },
	{ 0xd2248aac, "cdev_init" },
	{ 0x19070091, "kmem_cache_alloc" },
	{ 0xab978df6, "malloc_sizes" },
	{ 0x29537c9e, "alloc_chrdev_region" },
	{ 0x1b7d4074, "printk" },
	{ 0x7485e15e, "unregister_chrdev_region" },
	{ 0x37a0cba, "kfree" },
	{ 0x70ecc9b2, "cdev_del" },
};

static const char __module_depends[]
__attribute_used__
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "CD4909EBE348DB7768A8507");
