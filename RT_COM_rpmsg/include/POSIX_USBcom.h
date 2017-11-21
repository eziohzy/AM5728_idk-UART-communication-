#ifndef __POSIX_USBCOM_H__
#define __POSIX_USBCOM_H__

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/time.h>
#include "set_baud.h"

void closeUSBserial(int ft);
int openUSBserial(const char *device);
void setBAUDRATE(int ft, int baudrate);
void fcRTSCTS(int ft, int en);
int setRTS(int ft, int level);
int USBWrite(int ft, unsigned char *Txbuf, int TxSize);
int USBRead(int ft, unsigned char *Rxbuf, int RxSize);
void clearUSBbuf(int ft,int RoW);
#endif
