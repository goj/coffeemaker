#ifndef LIBCOFFEEMAKER_H_DHLAZNOI
#define LIBCOFFEEMAKER_H_DHLAZNOI

#include <time.h>
#include <usb.h>

void coffemaker_init_usb();
usb_dev_handle* coffeemaker_connect();
time_t coffeemaker_status(usb_dev_handle*);
time_t coffeemaker_on(usb_dev_handle*);
void coffeemaker_off(usb_dev_handle*);
void coffeemaker_debug(usb_dev_handle*, char*, int);
void coffeemaker_disconnect(usb_dev_handle*);

#endif /* end of include guard: LIBCOFFEEMAKER_H_DHLAZNOI */

