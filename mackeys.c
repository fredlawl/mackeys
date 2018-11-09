#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include "mackeys.h"

MODULE_AUTHOR("Frederick Lawler");
MODULE_DESCRIPTION("Remaps keyboard keys to model after useful MacOS key bindings.");
MODULE_LICENSE("MIT");
//MODULE_SUPPORTED_DEVICE("<insert keyboard>");

static int __init init_mackeys(void)
{
	mackeys_info("Module installed");
	return 0;
}

static void __exit cleanup_mackeys(void)
{
	mackeys_info("Module removed");
}

module_init(init_mackeys);
module_exit(cleanup_mackeys);
