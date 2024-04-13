#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#define MAJOR_NUM 60
#define MODULE_NAME "demo"

static int iCount = 0;
static char userChar[100];
static char st[3];

int gpio_export(char gpio[10])
{
    struct file *fd;

    loff_t pos = 0;

    fd = filp_open("/sys/class/gpio/export", O_WRONLY, 0);
    if (fd < 0)
    {
        printk("error !");
        return 0;
    }

    vfs_write(fd, gpio, strlen(gpio), &pos);
    filp_close(fd, NULL);
    return 0;
}

int gpio_unexport(char gpio[10])
{
    struct file *fd;

    loff_t pos = 0;
    fd = filp_open("/sys/class/gpio/unexport", O_WRONLY, 0);
    if (fd < 0)
    {
        printk("gpio/unexport");
        return 0;
    }
    vfs_write(fd, gpio, strlen(gpio), &pos);
    filp_close(fd, NULL);
    return 0;
}

int gpio_set_dir(char gpio[10])
{
    struct file *fd;

    char buf[64];
    loff_t pos = 0;
    snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%s/direction", gpio);

    fd = filp_open(buf, O_WRONLY, 0);

    if (fd < 0)
    {
        printk("gpio/direction");
        return 0;
    }

    vfs_write(fd, "out", strlen("out"), &pos);
    filp_close(fd, NULL);
    return 0;
}

int gpio_set_value(char gpio[10], char value[2])
{
    struct file *fd;
    char buf[64];
    loff_t pos = 0;
    snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%s/value", gpio);

    fd = filp_open(buf, O_WRONLY, 0);

    if (fd < 0)
    {
        printk("gpio/set-value");
        return 0;
    }
    vfs_write(fd, value, strlen(value), &pos);
    filp_close(fd, NULL);
    return 0;
}

char *gpio_get_value(char gpio[10])
{
    struct file *fd;

    char buf[64];

    loff_t pos = 0;
    char value[2] = {'0', '\0'};

    snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%s/value", gpio);

    fd = filp_open(buf, O_RDONLY, 0);

    if (fd < 0)
    {
        printk("gpio/set-value");
        return 0;
    }

    vfs_read(fd, value, 1, &pos);
    st[0] = value[0];

    filp_close(fd, NULL);
}

static ssize_t drv_read(struct file *filp, char *buf, size_t count, loff_t *ppos)
{
    printk("Read: %s", "Enter Read function\n");
    // printk("cw%s ", st);
    copy_to_user((void *)buf, st, 1);
    return count;
}

static ssize_t drv_write(struct file *filp, const char *buf, size_t count, loff_t *ppos)
{

    char gpio[10] = {0};
    char value[2] = {'0', '\0'};

    mm_segment_t old_fs;

    printk("Write: %s", "Enter Write function\n");

    copy_from_user(userChar, buf, count);
    userChar[count - 1] = '\0';

    strncpy(gpio, userChar, 3);
    value[0] = userChar[3];

    old_fs = get_fs();
    set_fs(get_ds());

    if (value[0] == '1')
    {

        gpio_set_dir(gpio);
        gpio_set_value(gpio, value);
    }
    else if (value[0] == '0')
    {

        gpio_set_dir(gpio);
        gpio_set_value(gpio, value);
    }
    else
    {

        gpio_get_value(gpio);
    }

    set_fs(old_fs);

    return count;
}

long drv_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    printk("I/O Control: %s", "Enter I/O Control function\n");
    return 0;
}

static int drv_open(struct inode *inode, struct file *filp)
{
    printk("Open: %s", "Enter Open function\n");

    return 0;
}

static int drv_release(struct inode *inode, struct file *filp)
{

    printk("Release: %s", "Enter Release function\n");
    return 0;
}

struct file_operations drv_fops =
    {
        read : drv_read,
        write : drv_write,
        unlocked_ioctl : drv_ioctl,
        open : drv_open,
        release : drv_release,

    };

static int demo_init(void)
{

    if (register_chrdev(MAJOR_NUM, "demo", &drv_fops) < 0)
    {
        printk("<1>%s: can't get major %d\n", MODULE_NAME, MAJOR_NUM);
        return (-EBUSY);
    }

    printk("<1>%s: started\n", MODULE_NAME);

    mm_segment_t old_fs;

    char gpio[10][10] = {"392", "397", "481", "398","389","388"};


    old_fs = get_fs();
    set_fs(get_ds());

    gpio_export(gpio[0]);
    gpio_export(gpio[1]);
    gpio_export(gpio[2]);
    gpio_export(gpio[3]);
    gpio_export(gpio[4]);
    gpio_export(gpio[5]);
    st[0] = '0';
    st[1] = '\0';

    set_fs(old_fs);

    return 0;
}

static void demo_exit(void)
{
    mm_segment_t old_fs;

    unregister_chrdev(MAJOR_NUM, "demo");
    printk("<1>%s removed\n", MODULE_NAME);
}

module_init(demo_init);
module_exit(demo_exit);
MODULE_LICENSE("GPL");


