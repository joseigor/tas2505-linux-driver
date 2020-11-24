#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(.gnu.linkonce.this_module) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section(__versions) = {
	{ 0x2774637b, "module_layout" },
	{ 0xfeb69c94, "i2c_del_driver" },
	{ 0xd788fdd0, "i2c_register_driver" },
	{ 0x516d8768, "_dev_err" },
	{ 0xb4c04f3d, "devm_snd_soc_register_component" },
	{ 0xbc256660, "__devm_regmap_init_i2c" },
	{ 0x21b71147, "devm_kmalloc" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

MODULE_INFO(depends, "");

MODULE_ALIAS("of:N*T*Cti,tas2505");
MODULE_ALIAS("of:N*T*Cti,tas2505C*");

MODULE_INFO(srcversion, "7E1CA372C69BEC746E18CF4");
