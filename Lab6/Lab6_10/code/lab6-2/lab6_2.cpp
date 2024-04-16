#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <map>
#include <string>

using namespace std;

void setGPIO(unsigned int gpio, string status,string LED)
{
    int g[4] = {396, 392, 255, 429};

    FILE *io = fopen("/dev/demo", "w+");
    if (io == NULL)
    {
        perror("gpio error");
        return;
    }

    char buf[10] = {'0'};
    if (status == "on")
    {
        strcpy(buf, (to_string(gpio) + "1").c_str());
        fwrite(buf, sizeof(buf), 1, io);
    }
    else if (status == "off")
    {
        strcpy(buf, (to_string(gpio) + "0").c_str());
        fwrite(buf, sizeof(buf), 1, io);
    }
    else if (status == "state")
    {
        strcpy(buf, (to_string(gpio) + "2").c_str());
        fwrite(buf, sizeof(buf), 1, io);
        fread(buf, sizeof(buf), 1, io);
        printf("input : %d\n%s (GPIO=%d) Status: %c\n", gpio,LED.c_str(), gpio,buf[0]);
    }

    fclose(io);
    return;
}

int main(int argc, char *argv[])
{

    unsigned int gpio = 0;

    if (strcmp(argv[1], "LED1") == 0)
    {
        gpio = 396;
        if (argc == 3)
        {
            setGPIO(gpio, argv[2],argv[1]);
        }
        else
        {
            setGPIO(gpio, "state",argv[1]);
        }
    }

    if (strcmp(argv[1], "LED2") == 0)
    {
        gpio = 392;
        if (argc == 3)
        {
            setGPIO(gpio, argv[2],argv[1]);
        }
        else
        {
            setGPIO(gpio, "state",argv[1]);
        }
    }

    if (strcmp(argv[1], "LED3") == 0)
    {
        gpio = 255;
        if (argc == 3)
        {
            setGPIO(gpio, argv[2],argv[1]);
        }
        else
        {
            setGPIO(gpio, "state",argv[1]);
        }
    }
    if (strcmp(argv[1], "LED4") == 0)
    {
        gpio = 429;
        if (argc == 3)
        {

            setGPIO(gpio, argv[2],argv[1]);
        }
        else
        {
            setGPIO(gpio, "state",argv[1]);
        }
    }

    return 0;
}
