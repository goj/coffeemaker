#include <stdio.h>
#include <string.h>
#include "coffeemaker.h"

#define STATUS_FILE "/tmp/coffeemaker-status"
time_t read_status();
void save_status(time_t status);

void coffemaker_init_usb() {
}

usb_dev_handle* coffeemaker_connect() {
    return (usb_dev_handle*) 0xC0FFEE;
}

time_t coffeemaker_status(usb_dev_handle* hndl) {
    return read_status();
}

time_t coffeemaker_on(usb_dev_handle* hndl) {
    time_t status = time(NULL);
    save_status(status);
    return status;
}

void coffeemaker_off(usb_dev_handle* hndl) {
    save_status(0);
}

void coffeemaker_debug(usb_dev_handle* hndl, char* buf, int buf_size) {
    strcpy(buf, "fake debug info");
}

void coffeemaker_disconnect(usb_dev_handle* hndl) {
}

void save_status(time_t status) {
    FILE* f = fopen(STATUS_FILE, "w");
    fprintf(f, "%d\n", (int) status);
}

time_t read_status() {
    time_t status;
    FILE* f = fopen(STATUS_FILE, "r");
    fscanf(f, "%d", &status);
    return status;
}
