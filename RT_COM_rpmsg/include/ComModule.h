/*!
	This module is an extension of USBCom module for providing 
	more robust and realtime read/write process. 

	This module includes data checking and error handling method 
	for the commucication link.

	please see: DataPackStruct.c USBCom.c for more detail.

	Company: PI Electronic (H.K.) Ltd
	Author : Terence
	Date: 13 Jan 2015
*/
#ifndef __COMMODULE_H__
#define __COMMODULE_H__

#include "stdlib.h"
#include "stdio.h"
#include "realtime.h"	//!< nanosleep()
#include "POSIX_USBcom.h"	
#include "timer.h"		//!< tic(), toc()
#include "DataPacketStruct.h"

#define NANODELAY 650000		//!< Duration of inactive RTS 

//! New struct contains all the flags for software controls 
struct CM_FLAGS {
	int dcflag;		//!< data corruption flag
	int errflag;	//!< error occurrence flag
	int errcount;	//!< error counter
	unsigned int ts_cur;		//!< current time stamp 
	unsigned int ts_pre;		//!< previous time stamp for sucessful read data
	unsigned int ts_dif;		//!< consecutive data time difference
	unsigned int ts_lcur;		//!< consecutive data time difference feedbacked to dsp from 0 to 255 
	int toflag;		//!< timeout flag
	int lbcount;	//!< line break counter
	unsigned int loopcount;	//!< loop counter
	int rscount;	//!< resume counter
	int txerrcount;  //!< write error occurrence flag 

};


//! New type for return Message  
typedef enum {			RX_OK, 		//!< Recieve Sucessfully
				TX_OK, 		//!< Transmit Sucessfully
				RX_TIMEOUT,	//!< USB Read Timeout  
				TX_SKIP, 	//!< Skip writing
				DATA_CORUP,	//!< Receive data corrupted
				DEV_DISCON,	//!< Device disconnet
				LINE_BROKEN,	//!< Line broken error
				TX_INCOMP
} ERR_MSG;

//! Display the buffer content
void dispuchar(unsigned char *buf, int bufSize);
//! Display the float type data 
void dispfloat(float *data, int dof);

//! Initiallize the USB port and all the signal flags
/*!
	input: 
		device: port no.
		buadrate: buadrate of transmission
		fsignal: signal flags
*/
int ComInitialization( const char *device,int buadrate, struct CM_FLAGS *fsignal);
//! Recieving Module
/*!sss
	input:
		ft: FTDI device handler
		RxSize: Size of Rx data, must be 64 bytes
	output:
		Rxbuf: unsigned char from DSP
	in&out:
		fsignal: signal flags
	return:
		status of read process,
		please see enum ERR_MSG in ComModule.h 
*/
ERR_MSG ComRead(unsigned char *Rxbuf, int ft, int RxSize, struct CM_FLAGS *fsignal);
//! Transmission Module 
/*!
	input:
		ft: FTDI device handler
		TxSize: Size of Rx data, must be 160 bytes
		Txbuf: unsigned char dat sent to DSP
	in&out:
		fsignal: signal flags
	return:
		status of write process,
		please see enum ERR_MSG in ComModule.h 
*/
ERR_MSG ComWrite(int ft, unsigned char *Txbuf, int TxSize, struct CM_FLAGS *fsignal);

//! Close the USB port
void ComTermination(int ft, struct CM_FLAGS *fsignal);

#endif