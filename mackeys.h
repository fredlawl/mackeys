#define LOG_PREFIX "mackeys: "

#define mackeys_printk(level, fmt, arg...)	\
	printk(level LOG_PREFIX fmt "\n", ##arg)

#define mackeys_info(fmt, arg...)	\
	printk(KERN_INFO LOG_PREFIX fmt "\n", ##arg)

#define mackeys_err(fmt, arg...)	\
	printk(KERN_ERR LOG_PREFIX fmt "\n", ##arg)
