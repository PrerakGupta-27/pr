#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/pid.h>

struct task_struct *get_task_struct_by_pid(pid_t pid) {
    struct task_struct *task;

    rcu_read_lock();
    task = find_task_by_vpid(pid);
    if (task) {
        get_task_struct(task);
    }
    rcu_read_unlock();

    return task;
}

void print_process_info(struct task_struct *task) {
    printk(KERN_INFO "Process name: %s\n", task->comm);
    printk(KERN_INFO "Process ID: %d\n", task->pid);
    printk(KERN_INFO "Process state: %ld\n", task->state);
    printk(KERN_INFO "Process priority: %d\n", task->prio);
}

static int __init my_module_init(void) {
    pid_t pid = 1; // Replace 1 with the desired PID
    struct task_struct *task = get_task_struct_by_pid(pid);
    if (task) {
        print_process_info(task);
        put_task_struct(task);
    } else {
        printk(KERN_ERR "Failed to get task struct for PID %d\n", pid);
    }
    return 0;
}

static void __exit my_module_exit(void) {
    printk(KERN_INFO "Exiting kernel module\n");
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Kernel module to print process information");

make
sudo insmod my_module.ko
