#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

// called when module is loaded
// static indicates there's no need to export the function beyond the file level scope

static int hello_init(void)
{
	// printk is kernel's logging mechanism
	printk(KERN_DEBUG "Hello world!\n");
	return 0;
}

// invoked when module is removed from memory
// usually clean up stuff done here
// if compiled into the kernel this function wouldn't be included as it wouldn't need to be invoked and could not be removed from memory
static void hello_exit(void)
{
	printk(KERN_ALERT "Bye bye!\n");
}

module_init(hello_init); // module_ are macros
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SHAKESPEAR");
MODULE_DESCRIPTION("A Hello, World Module");
