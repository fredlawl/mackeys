#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <asm/io.h>

#include "mackeys.h"

#define KBD_IRQ             1       /* IRQ number for keyboard (i8042) */
#define KBD_DATA_REG        0x60    /* I/O port for keyboard data */
#define KBD_SCANCODE_MASK   0x7f
#define KBD_STATUS_MASK     0x80

const char *map_tbl[] = {
	"{ NOT USED }",
	"Esc", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=",
	"BS", "TAB", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "[",
	"]", "RET", "CTRL", "A", "S", "D", "F", "G", "H", "J", "K", "L", ";",
	"‘", "`", "(LEFT) SHIFT", "\\", "Z", "X", "C", "V", "B", "N", "M", ",",
	".", "/", "(RIGHT) SHIFT", "{ NOT USED }", "ALT", "SPACE BAR",
	"CAPS LOCK", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9",
	"F10", "{ NOT USED }", "{ NOT USED }", "HOME", "UP ARROW",
	"{ NOT USED }", "KEYPAD -", "LEFT ARROW", "{ NOT USED }", "RIGHT ARROW",
	"KEYPAD +", "{ NOT USED }", "DOWN ARROW", "{ NOT USED }", "INSERT",
	"DEL", "{ NOT USED }", "{ NOT USED }", "ISO KEY", "UNDO", "HELP",
	"KEYPAD (", "KEYPAD /", "KEYPAD *", "KEYPAD *", "KEYPAD 7", "KEYPAD 8",
	"KEYPAD 9", "KEYPAD 4", "KEYPAD 5", "KEYPAD 6", "KEYPAD 1", "KEYPAD 2",
	"KEYPAD 3", "KEYPAD 0", "KEYPAD .", "KEYPAD ENTER"
};

const int map_tbl_len = sizeof(map_tbl) / sizeof(const char*);

static irqreturn_t kbd2_isr(int irq, void *dev_id)
{
	char scancode;
	int mapped_key_code;

	scancode = inb(KBD_DATA_REG);
	mapped_key_code = (int) scancode & KBD_SCANCODE_MASK;

	if (mapped_key_code > map_tbl_len)
		return IRQ_HANDLED;

	/**
	 * NOTE: i/o ops take a lot of time thus must be
	 * avoided in HW ISRs
	 */
	mackeys_info("Scan Code %x: %s %s",
		mapped_key_code,
		map_tbl[mapped_key_code],
		scancode & KBD_STATUS_MASK ? "Released" : "Pressed");

	return IRQ_HANDLED;
}


static int __init mackeys_init(void)
{
	mackeys_info("Module installed");
	return request_irq(KBD_IRQ, kbd2_isr, IRQF_SHARED, "kbd2", (void *)kbd2_isr);
}
module_init(mackeys_init);

static void __exit mackeys_exit(void)
{
	free_irq(KBD_IRQ, (void *)kbd2_isr);
	mackeys_info("Module removed");
}
module_exit(mackeys_exit);

MODULE_AUTHOR("Frederick Lawler <fred@fredlawl.com>");
MODULE_DESCRIPTION("Remaps keyboard keys to model after useful MacOS key bindings.");
MODULE_LICENSE("GPL v2");
