#include <linux/module.h>
#include <linux/init.h>

#include <linux/proc_fs.h>
#include <linux/seq_file.h>	// for seq_file
#include <linux/fs.h>		// for file_operations

static char *PROC_FILE_NAME = "dbgseq";

#define DBG_ARRAY_SIZE 5
static char *array[DBG_ARRAY_SIZE] = {
	"Hello world!\n",
	"What's your name?\n",
	"How are you?\n",
	"Do you hear the people sing?\n",
	"Singing the song of angrey mem.\n",
};

static void *dbg_seq_start(struct seq_file *sfile, loff_t *pos)
{
	if (*pos < DBG_ARRAY_SIZE)
	{
		return array + *pos;
	}
	return NULL; 
}

static void *dbg_seq_next(struct seq_file *sfile, void *v, loff_t *pos)
{
	(*pos)++;
	if (*pos < DBG_ARRAY_SIZE)
	{
		return array + *pos;
	}
	return NULL;
}

static void dbg_seq_stop(struct seq_file *sfile, void *v)
{

}

static int dbg_seq_show(struct seq_file *sfile, void *v)
{
	char **val = (char **)(v);

	seq_printf(sfile, "%s", *val);

	return 0;
}

static struct seq_operations dbg_seq_ops = {
	.start = dbg_seq_start,
	.next = dbg_seq_next,
	.stop = dbg_seq_stop,
	.show = dbg_seq_show
};

static int dbg_proc_open(struct inode *inode, struct file *filp)
{
	return seq_open(filp, &dbg_seq_ops);
}

static struct file_operations dbg_proc_ops = {
	.owner = THIS_MODULE,
	.open = dbg_proc_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = seq_release
};

static int __init dbg_init(void)
{
	struct proc_dir_entry *entry;

	entry = create_proc_entry(PROC_FILE_NAME, 0, NULL);
	if (entry)
	{
		entry->proc_fops = &dbg_proc_ops;
	}
	
	return 0;
}

static void __exit dbg_exit(void)
{
	remove_proc_entry(PROC_FILE_NAME, NULL /* parent dir */);
}

module_init(dbg_init);
module_exit(dbg_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Waldon Chen");
