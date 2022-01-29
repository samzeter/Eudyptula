/*
* helloworld.c
*/
#include <linux/module.h>     /* Needed by all modules */
#include <linux/kernel.h>     /* Needed for KERN_INFO */
#include <linux/init.h>       /* Needed for the macros */


static int hello_init(void)
{
	pr_debug("Hello World!\n");
	return 0;
}

static void hello_exit(void)
{
	pr_debug("See you later.\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("7c1caf2f50d1");
MODULE_DESCRIPTION("Just a module");
