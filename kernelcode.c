#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/sched/signal.h>

void print_process_info(struct task_struct *task) {
    printk(KERN_INFO "Process name: %s\n", task->comm);
    printk(KERN_INFO "Process ID: %d\n", task->pid);
    printk(KERN_INFO "User ID: %d\n", task->cred->uid.val);
    printk(KERN_INFO "Group ID: %d\n", task->group_leader->pid);
}

int my_module_init(void) {
    pid_t pid = 1; // Replace 1 with the desired PID
    struct task_struct *task;
    for_each_process(task){
        if (task->pid==pid) {
            print_process_info(task);
        }
    } 
    return 0;
}

void my_module_exit(void) {
    printk(KERN_INFO "Exiting kernel module\n");
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Kernel module to print process information");
