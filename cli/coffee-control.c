/* Hugely refactored code from hid-custom-rq example by Christian Starkjohann */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "coffeemaker.h"

static void usage(char *name)
{
    fprintf(stderr, "usage:\n");
    fprintf(stderr, "  %s status ... get the device status\n", name);
    fprintf(stderr, "  %s on ....... turn on the coffee machine\n", name);
    fprintf(stderr, "  %s off ...... turn off the coffee machine\n", name);
    fprintf(stderr, "  %s debug .... print debug info\n", name);
}

void print_status(time_t ts) {
    if (ts < 0) {
        printf("ERROR got bad number of status bytes: %d\n", (unsigned)-ts);
    } else if (ts) {
        struct tm time;
        const int buf_size = 256;
        char buf[buf_size];
        localtime_r(&ts, &time);
        strftime(buf, buf_size, "%F %T", &time);
        printf("ON since %u (%s)\n", (unsigned)ts, buf);
    } else {
        printf("OFF\n");
    }
}

int main(int argc, char **argv)
{
    usb_dev_handle *handle;

    if (argc != 2) {
        usage(argv[0]);
        return 0;
    }

    tzset();
    usb_init();
    handle = coffeemaker_connect();
    if (!handle) {
        printf("DISCONNECTED\n");
        exit(1);
    }

    if (strcasecmp(argv[1], "status") == 0) {
        time_t ts = coffeemaker_status(handle);
        print_status(ts);
        if (ts < 0) {
            coffeemaker_disconnect(handle);
            exit(1);
        }
    } else if (strcasecmp(argv[1], "on") == 0) {
        time_t ts = coffeemaker_on(handle);
        print_status(ts);
    } else if (strcasecmp(argv[1], "off") == 0) {
        coffeemaker_off(handle);
        print_status(0);
    } else if(strcasecmp(argv[1], "debug") == 0) {
        const int buf_size = 256;
        char buf[buf_size];
        coffeemaker_debug(handle, buf, buf_size);
        puts(buf);
    } else{
        usage(argv[0]);
        exit(1);
    }
    coffeemaker_disconnect(handle);
    return 0;
}
