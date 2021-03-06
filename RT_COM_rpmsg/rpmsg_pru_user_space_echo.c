/*
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *	* Redistributions of source code must retain the above copyright
 *	  notice, this list of conditions and the following disclaimer.
 *
 *	* Redistributions in binary form must reproduce the above copyright
 *	  notice, this list of conditions and the following disclaimer in the
 *	  documentation and/or other materials provided with the
 *	  distribution.
 *
 *	* Neither the name of Texas Instruments Incorporated nor the names of
 *	  its contributors may be used to endorse or promote products derived
 *	  from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/poll.h>
#include "realtime.h"
#include "timer.h"

// char readBuf[MAX_BUFFER_SIZE];

#define NUM_MESSAGES		100
#define DEVICE_NAME		"/dev/rpmsg_pru30"

#define MY_PRIORITY 99 /*! we use 49 as the PRREMPT_RT use 50
                            as the priority of kernel tasklets
                            and interrupt handler by default */
#define TxSize 160	//!< transmission data frame size is 160 bytes

#define RxSize 64	//!< recieved data frame size is 64 bytes      
int main(void)
{
	static struct timespec t1,t2,ton,toff;
	float tdiff;
	struct pollfd pollfds[1];
	int i=0,j;
	int result = 0;

	unsigned char Txbuf[TxSize];	// 160!< define Tx data buffer, CHECK! what Ready_buf does
	unsigned char Rxbuf[RxSize];	// 64!< define Rx data buffer, CHECK! what Rxbuf does
	ton=tic();
	make_realtime(getpid(), MY_PRIORITY);
	/* Open the rpmsg_pru character device file */
	pollfds[0].fd = open(DEVICE_NAME, O_RDWR);

	/*
	 * If the RPMsg channel doesn't exist yet the character device
	 * won't either.
	 * Make sure the PRU firmware is loaded and that the rpmsg_pru
	 * module is inserted.
	 */
	if (pollfds[0].fd < 0) {
		printf("Failed to open %s\n", DEVICE_NAME);
		return -1;
	}

	/* The RPMsg channel exists and the character device is opened */
	printf("Opened %s, sending %d messages\n\n", DEVICE_NAME, NUM_MESSAGES);

//	for(i=0;i<1000;i++)
	//{
	while(1){
				t1=tic();
				result = write(pollfds[0].fd, "hello world!", 13);
				t2=toc(t1,&tdiff);
				// printf("write_cost_time is %f\n",tdiff);
				t1=tic();
				result = read(pollfds[0].fd, Rxbuf, RxSize);
				t2=toc(t1,&tdiff);
				// printf("read_cost_time is %f\n",tdiff);
				if (result > 0)
					{

					if(Rxbuf[RxSize-1]!=255)
						{
						// printf("Message %d received from PRU:\n\n", i);
						for(j=0;j<RxSize;j++)
							printf("--%d",Rxbuf[j]);
						printf("\n");
						}
					}
	}

	toc(ton,&tdiff);
	printf("whole_process_cost %f\n",tdiff);
	/* Received all the messages the example is complete */
	printf("Received %d messages, closing %s\n", NUM_MESSAGES, DEVICE_NAME);

	/* Close the rpmsg_pru character device file */
	close(pollfds[0].fd);
	
	return 0;
}

