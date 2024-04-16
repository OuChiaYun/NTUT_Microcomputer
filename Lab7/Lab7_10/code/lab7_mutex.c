#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

pthread_mutex_t mutex;

int sum = 0;
char counter[5] = {'0', '0', '0', '0', '0'};
char mm[5][5] = {"396", "392", "255", "429"};
int n = 0;

int gpio_export(char gpio[10])
{
    int fd, len;
    char buf[64];

    fd = open("/sys/class/gpio/export", 1);
    if (fd < 0)
    {
        perror("gpio/export");
        return fd;
    }

    len = snprintf(buf, sizeof(buf), "%s", gpio);
    write(fd, buf, len);
    close(fd);
    return 0;
}

int gpio_unexport(char gpio[10])
{
    int fd, len;
    char buf[64];

    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if (fd < 0)
    {
        perror("gpio/unexport");
        return fd;
    }
    len = snprintf(buf, sizeof(buf), "%s", gpio);
    write(fd, buf, len);
    close(fd);
    return 0;
}

int gpio_set_dir(char gpio[10])
{
    int fd;
    char buf[64];

    snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%s/direction", gpio);

    fd = open(buf, 1);

    if (fd < 0)
    {
        perror("gpio/direction");
        return fd;
    }

    write(fd, "out", 4);

    close(fd);
    return 0;
}

int gpio_set_value(char gpio[10], int value)
{
    int fd;
    char buf[64];

    snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%s/value", gpio);

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

void *thread_run(void *arg)
{

    int i = 0;
    for (int i = 0; i < 2; i++)
    {
        pthread_mutex_lock(&mutex);
        sum = sum + 1;
        for (int j = 0; j < 4; j++)
        {
            if (counter[j] == '1')
            {
                printf("GPIO: %s status: 1\n", mm[j]);
                gpio_set_value(mm[j], 1);
                counter[j] = '0';
            }
            else
            {
                printf("GPIO: %s status: 0\n", mm[j]);
                gpio_set_value(mm[j], 0);
                counter[j] = '1';
            }
        }
        printf("\n");
        sleep(1);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    gpio_export("396");
    gpio_export("392");
    gpio_export("255");
    gpio_export("429");

    gpio_set_dir("396");
    gpio_set_dir("392");
    gpio_set_dir("255");
    gpio_set_dir("429");

    n = 0;

    for (int i = 0; i < 4; i++)
    {
        counter[i] = argv[1][i];
    }

    n = argv[2][0] - '0';

    pthread_t thread[10];

    pthread_mutex_init(&mutex, 0);

    for (int i = 0; i < n; i++)
    {
        pthread_create(&thread[i], NULL, thread_run, 0);
    }

    for (int i = 0; i < n; i++)
    {
        pthread_join(thread[i], 0);
    }

    printf("sum : %d\n", sum);

    gpio_set_value("396", 0);
    gpio_set_value("392", 0);
    gpio_set_value("255", 0);
    gpio_set_value("429", 0);

    gpio_unexport("396");
    gpio_unexport("392");
    gpio_unexport("255");
    gpio_unexport("429");

    return 0;
}
