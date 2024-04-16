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

    gpio_export(396);
    gpio_set_dir(396, "out");
    gpio_export(392);
    gpio_set_dir(392, "out");
    gpio_export(255);
    gpio_set_dir(255, "out");
    gpio_export(429);
    gpio_set_dir(429, "out");

    int input = 0;

    printf("%d %s %s %s\n", argc, argv[1], argv[2],argv[3]);
    printf("\n%s => %d %s\n", argv[1], argv[1][3] - '0', argv[2]);

    int k = strlen(argv[1]);

    if ( atoi(argv[3])== 0 )
    {
        printf("mode time: %d\n", atoi(argv[3]) );

        for (int i = 3; i < k; i += 5)
        {
            int number = argv[1][i] - '0';

            if (number == 1)
            {
                number = 396;
            }
            else if (number == 2)
            {
                number = 392;
            }
            else if (number == 3)
            {
                number = 255;
            }
            else if (number == 4)
            {
                number = 429;
            }

            if (strcmp(argv[2], "on") == 0 || strcmp(argv[2], "on,") == 0)
            {
                input = 1;
            }

            else if (strcmp(argv[2], "off") == 0)
            {
                input = 2;
            }

            printf("\n%d , %d\n", number, input);
            // std::cout << "輸入1為out 255 pin15 == 1 \n2 is close\n";
            // std::cin >> input;
            if (input == 1)
            {
                // gpio_export(number);
                // gpio_set_dir(number, "out");
                gpio_export(number);
                gpio_set_dir(number, "out");
                gpio_set_value(number, 1);
            }
            else if (input == 2)
            {
                gpio_export(number);
                gpio_set_dir(number, "out");
                gpio_set_value(number, 0);
                gpio_unexport(number);
                // gpio_unexport(number);
            }
        }
    }
    else
    {
        printf("mode time: %d\n", atoi(argv[3]));

        for (int i = 0; i < atoi(argv[3]); i++)
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
