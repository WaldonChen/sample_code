#include <linux/module.h>
#include <linux/init.h>

#include <linux/proc_fs.h>	// for /proc

static char *PROC_FILE_NAME = "driver/dbg_proc";

int dbg_proc_read_proc(char *page, char **start, off_t off,
		int count, int *eof, void *data)
{

}

static int __init dbg_proc_init(void)
{
	create_proc_entry(PROC_FILE_NAME, 0 /* defult mode */,
			NULL, dbg_proc_read_proc, NULL /* client data */);
	
	return 0;
}

static void __exit dbg_proc_exit(void)
{
	remove_proc_entry(PROC_FILE_NAME, NULL /* parent dir */);
}

module_init(dbg_proc_init);
module_exit(dbg_proc_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Waldon Chen");
