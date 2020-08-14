#include <linux/kernel.h> /* We're doing kernel work */
#include <linux/module.h> /* Specifically, a module */
#include <syscall.h> /* The list of system calls */
#include <linux/sched.h>
extern void *sys_call_table[];
int uid;
asmlinkage int (*original_call)(const char *, int, int);
asmlinkage int our_sys_open(const char *filename, int flags, int mode)
{
int i = 0;
char ch;
/* Check if this is the user we're spying on */
if (uid == current->uid) { /* current->uid is the uid of the user who
ran the process which called the system
call we got */
/* Report the file, if relevant */
printk("Opened file: ");
do {
ch = get_user(filename+i);
i + + ;
printk("%c", ch);
} while (ch != 0);
p r i n t k ( " \ n " ) ;
}
/* Call the original sys_open - otherwise, we lose the ability to open
* files */
return original_call(filename, flags, mode);
}
/* Initialize the module - replace the system call */
int init_module()
{
/* Warning - too late for it now, but maybe for next time... */
printk("I'm dangerous. I hope you did a sync before you insmod'ed me.\n");
printk("My counterpart, cleapup_module(), is even more dangerous. If\n");
printk("you value your file system, it will be \"sync; rmmod\" \n");
printk("when you remove it.\n");
/* Keep a pointer to the original function in original_call, and
* then replace the system call in the system call table with
* our_sys_open */
original_call = sys_call_table[__NR_open];
sys_call_table[__NR_open] = our_sys_open;
/* To get the address of the function for system call foo, go to
* sys_call_table[__NR_foo]. */
return 0;
}
/* Cleanup - unregister the appropriate file from /proc */
void cleanup_module()
{
/* Return the system call back to normal */
if (sys_call_table[__NR_open] != our_sys_open) {
printk("Somebody else also played with the open system call\n");
printk("The system may be left in an unstable state.\n");
}
sys_call_table[__NR_open] = original_call;
}
