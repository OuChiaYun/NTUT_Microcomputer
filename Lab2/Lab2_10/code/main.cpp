#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>

int gpio_export(unsigned int gpio)
{
    int fd, len;
    char buf[64];

    fd = open("/sys/class/gpio/export", O_WRONLY);
    if (fd < 0)
    {
        perror("gpio/export");
        return fd;
    }

    len = snprintf(buf, sizeof(buf), "%d", gpio);
    write(fd, buf, len);
    close(fd);
    return 0;
}

int gpio_unexport(unsigned int gpio)
{
    int fd, len;
    char buf[64];

    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if (fd < 0)
    {
        perror("gpio/unexport");
        return fd;
    }
    len = snprintf(buf, sizeof(buf), "%d", gpio);
    write(fd, buf, len);
    close(fd);
    return 0;
}

int gpio_set_dir(unsigned int gpio, std::string dirStatus)
{
    int fd;
    char buf[64];

    snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/direction", gpio);

    fd = open(buf, O_WRONLY);

    if (fd < 0)
    {
        perror("gpio/direction");
        return fd;
    }

    if (dirStatus == "out")
    {
        write(fd, "out", 4);
    }
    else
    {
        write(fd, "in", 3);
    }

    close(fd);
    return 0;
}
int gpio_set_value(unsigned int gpio, int value)
{
    int fd;
    char buf[64];

    snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/value", gpio);

    fd = open(buf, O_WRONLY);

    if (fd < 0)
    {
        perror("gpio/set-value");
        return fd;
    }

    if (value == 0)
    {
        write(fd, "0", 2);
    }
    else
    {
        write(fd, "1", 2);
    }

    close(fd);
    return 0;
}
int main(int argc, char *argv[])
{
    int input = 0;
    int number = argv[1][3] - '0';

    if (strcmp(argv[1], "Mode_Shine") == 0)
    {
        for (int i = 0; i < 5; i++)
        {
            gpio_export(396);
            gpio_set_dir(396, "out");
            gpio_set_value(396, 1);
            gpio_export(392);
            gpio_set_dir(392, "out");
            gpio_set_value(392, 1);

            sleep(2);
            gpio_set_value(396, 0);
            gpio_unexport(396);
            gpio_set_value(392, 0);
            gpio_unexport(392);

            gpio_export(255);
            gpio_set_dir(255, "out");
            gpio_set_value(255, 1);
            gpio_export(429);
            gpio_set_dir(429, "out");
            gpio_set_value(429, 1);

            sleep(2);
            gpio_set_value(255, 0);
            gpio_unexport(255);
            gpio_set_value(429, 0);
            gpio_unexport(429);
        }
    }
    return 0;
}
