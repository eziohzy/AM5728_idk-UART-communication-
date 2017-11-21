#ifndef __SET_BAUD_H__
#define __SET_BAUD_H__

#include <stdio.h>
#include <stdlib.h>
#include <termio.h>
#include <fcntl.h>
#include <err.h>
#include <linux/serial.h>

int set_baud(int fd, int rate);

#endif