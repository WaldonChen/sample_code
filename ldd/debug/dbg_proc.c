#include <linux/module.h>
#include <linux/init.h>




static int __init dbg_proc_init(void)
{

	return 0;
}

static void __exit dbg_proc_exit(void)
{

}

module_init(dbg_proc_init);
module_exit(dbg_proc_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Waldon Chen");
