
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("semaphore");
char k_buff[50]="this is kernel";
struct semaphore sem_dev;
/*srction for addition start
/
*function declaration of add functionality/
int open_add(struct inode *inode, struct file *file_op_add);
int release_add(struct inode *inode, struct file *file_op_add);
ssize_t write_add(struct file *file_op_add,const char __user *u_buff,size_t count,loff_t *offp );
ssize_t read_add(struct file *file_op_add,char __user *u_buff, size_t count, loff_t *offp);
static int add_result;
// for storing the result of addition
/add operation structure/
struct file_operations fop_add=
{
.owner = THIS_MODULE,
.open = open_add,
.read = read_add,
.write = write_add,
.release = release_add,
};/add open function defination/
int open_add(struct inode *inode, struct file *file_op_add)
{
printk("AddDev is using MyCalDriver\n");
return 0;
}
/add read function defination that read the user data/
ssize_t read_add(struct file *file_op_add,char __user *u_buff,size_t count,loff_t *offp)
{
int result;
ssize_t retval;
if(down_interruptible(&sem_dev))
{
return -ERESTARTSYS;
}
result = copy_to_user((char*)u_buff,(char *)k_buff,sizeof(k_buff));
up(&sem_dev);
if(result == 0)
{
printk(KERN_ALERT"copy to user successfull % d data written \n",sizeof(k_buff));retval = sizeof(k_buff);
return count;
}
else
{
printk(KERN_ALERT"ERROR writting data to user\n");
retval = -EFAULT;
return retval;
}
}