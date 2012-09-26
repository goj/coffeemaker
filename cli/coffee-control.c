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

int main(int argc, char **argv)
{
    usb_dev_handle *handle;

    if (argc != 2) {
        usage(argv[0]);
        return 0;
    }

    usb_init();
    handle = coffeemaker_connect();
    if (!handle) {
        fprintf(stderr, "Could not connect to the coffeemaker.\n");
        exit(1);
    }

    if (strcasecmp(argv[1], "status") == 0) {
        time_t ts = coffeemaker_status(handle);
        if (ts < 0) {
            fprintf(stderr, "Error: got bad number of status bytes: %d\n", (int)-ts);
            coffeemaker_disconnect(handle);
            exit(1);
        } else if (ts) {
            char *time_str = ctime(&ts);
            printf("Coffee maker is on since %s (Unix timestamp: %u)\n", time_str, (unsigned)ts);
        } else {
            printf("Coffee maker is off\n");
        }
    } else if (strcasecmp(argv[1], "on") == 0) {
        coffeemaker_on(handle);
    } else if (strcasecmp(argv[1], "off") == 0) {
        coffeemaker_off(handle);
    } else if(strcasecmp(argv[1], "debug") == 0) {
        coffeemaker_debug(handle);
    } else{
        usage(argv[0]);
        exit(1);
    }
    coffeemaker_disconnect(handle);
    return 0;
}
