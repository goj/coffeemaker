/* 
 * This code is based on hid-custom-rq example by Christian Starkjohann from V-USB samples.
 * Copyright: (c) 2008 by OBJECTIVE DEVELOPMENT Software GmbH (hid-custom-rq)
 * Copyright: (c) 2012 by Krzysztof Goj (later changes)
 * License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
 */

#define RELAY_PORT_DDR        DDRB
#define RELAY_PORT_OUTPUT     PORTB
#define RELAY_BIT             0

#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>  /* for sei() */
#include <util/delay.h>     /* for _delay_ms() */

#include <avr/pgmspace.h>   /* required by usbdrv.h */

#include "usbdrv.h"
#include "oddebug.h"        /* This is also an example for using debug macros */
#include "requests.h"       /* The custom request numbers we use */

/* ------------------------------------------------------------------------- */
/* ----------------------------- USB interface ----------------------------- */
/* ------------------------------------------------------------------------- */

const PROGMEM char usbHidReportDescriptor[22] = {    /* USB report descriptor */
    0x06, 0x00, 0xff,              // USAGE_PAGE (Generic Desktop)
    0x09, 0x01,                    // USAGE (Vendor Usage 1)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x09, 0x00,                    //   USAGE (Undefined)
    0xb2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)
    0xc0                           // END_COLLECTION
};
/* The descriptor above is a dummy only, it silences the drivers. The report
 * it describes consists of one byte of undefined data.
 * We don't transfer our data through HID reports, we use custom requests
 * instead.
 */

#define ON_SINCE_SIZE 4

uchar on_since[ON_SINCE_SIZE];
char *last_error = "no error";

/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */

usbMsgLen_t usbFunctionSetup(uchar data[8])
{
    usbRequest_t    *rq = (void *)data;
    static char dataBuffer[100];
    int size;
    char *status;
    /* default for not implemented requests: return no data back to host */
    if((rq->bmRequestType & USBRQ_TYPE_MASK) != USBRQ_TYPE_VENDOR)
        return 0;
    switch (rq->bRequest) {
        case REQ_GET_STATUS:
            usbMsgPtr = on_since;
            return ON_SINCE_SIZE;
        case REQ_COFFEE_OFF:
            RELAY_PORT_OUTPUT &= ~(_BV(RELAY_BIT));
            memset(on_since, 0, ON_SINCE_SIZE);
            return 0;
        case REQ_COFFEE_ON:
            RELAY_PORT_OUTPUT |= _BV(RELAY_BIT);
            return USB_NO_MSG; /* read on_since TS in usbFunctionWrite */
        case REQ_DEBUG:
            status = (RELAY_PORT_OUTPUT & _BV(RELAY_BIT)) ? "ON" : "OFF";
            size = sprintf(dataBuffer,
                           "Coffee machine is %s\n"
                           "On since: %02hhx:%02hhx:%02hhx:%02hhx\n"
                           "Last error: %s\n",
                           status,
                           on_since[0], on_since[1], on_since[2], on_since[3],
                           last_error);
            usbMsgPtr = (uchar*) dataBuffer;
            return size + 1;
        default:
            return 0;
    }
}


uchar usbFunctionWrite(uchar *data, uchar len)
{
    if (len != 4) {
        last_error = "bad length";
        return 0;
    }
    memcpy(on_since, data, ON_SINCE_SIZE);
    return 1;
}

/* ------------------------------------------------------------------------- */

int __attribute__((noreturn)) main(void)
{
uchar   i;

    wdt_enable(WDTO_1S);
    /* Even if you don't use the watchdog, turn it off here. On newer devices,
     * the status of the watchdog (on/off, period) is PRESERVED OVER RESET!
     */
    /* RESET status: all port bits are inputs without pull-up.
     * That's the way we need D+ and D-. Therefore we don't need any
     * additional hardware initialization.
     */
    usbInit();
    usbDeviceDisconnect();  /* enforce re-enumeration, do this while interrupts are disabled! */
    i = 0;
    while(--i) {             /* fake USB disconnect for > 250 ms */
        wdt_reset();
        _delay_ms(1);
    }
    usbDeviceConnect();

    // set output ports
    RELAY_PORT_DDR |= _BV(RELAY_BIT); /* magnet bit is an output bit */

    sei();

    for(;;) {                /* main event loop */
        wdt_reset();
        usbPoll();
    }
}

/* ------------------------------------------------------------------------- */
