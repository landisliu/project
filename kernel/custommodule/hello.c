#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>
#include<linux/kernel.h>
#include<linux/sched.h>
#include<linux/version.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<asm/current.h>
#define ARRAYSIZE 10
static char *whom ="world";
static int howmany = 1;
static int narr;
int myarr[ARRAYSIZE];
module_param(whom,charp,S_IRUGO);
MODULE_PARM_DESC(whom,"name of the user");
module_param_array(myarr,int,&narr,S_IRUGO);
MODULE_PARM_DESC(myarr,"an array description");
module_param(howmany,int,S_IRUGO);
MODULE_PARM_DESC(howmany,"count of users");

static int __init hello_init(void)
{
	
	int i;
	printk(KERN_ALERT "Hello,World %s,%d\n",whom,howmany);
	for(i=0;i<narr;i++)
	{
		printk("item %d:\t %d\n",i,myarr[i]);
 
	}
	printk("current process id %d,current process name %s\n",current->pid,current->comm);
	return 0;
}
static void __exit hello_exit(void)
{
	printk(KERN_ALERT "Goodbye,world\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("landis");
MODULE_DESCRIPTION("This is the first module i made. It is like a simple Hello world,so don't laugh at me, you'll see me later.");
MODULE_VERSION("0.0.1");
MODULE_ALIAS("Hello Basic");
//EXPORT_SYMBOL(name);
//EXPORT_SYMBOL_GPL(name);


