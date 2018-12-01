#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include "mackeys.h"

static int __init mackeys_init(void)
{
	mackeys_info("Module installed");
	return 0;
}
module_init(mackeys_init);

static void __exit mackeys_exit(void)
{
	mackeys_info("Module removed");
}
module_exit(mackeys_exit);

MODULE_AUTHOR("Frederick Lawler <fred@fredlawl.com>");
MODULE_DESCRIPTION("Remaps keyboard keys to model after useful MacOS key bindings.");
MODULE_LICENSE("GPL v2");
