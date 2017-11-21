// Last modified by Terence on 6 OCT 2015
// Use semaphore technique to synchronize the threads and process when accessing 
// the same share memory. This can avoid race condition
#ifndef __SHM_MODULE_H__
#define __SHM_MODULE_H__

#include "stdlib.h"
#include "stdio.h"
#include "fcntl.h"
#include "sys/mman.h"
#include "sys/stat.h"
#include "unistd.h"
#include "sys/types.h" 
#include "semaphore.h"
#include "errno.h"
#include "string.h"
#include "timer.h"

//! create the share memory segment 
/*! 
	Creat a share memoey section as a file descriptor.  
	input: file name for the file descriptor. 
	output: int **shm_buf; start position of the share memory. 
	return -1 if error occured.
	return 1 if ok.
*/

//New type union for semaphore and unsigned char
union SEM_UC_POINTER{
	sem_t *sem;
	unsigned char *uc;
};

int shm_create(unsigned char **shm_buf, const char *filename, const int shm_size);
//! Link the share memory segment to file descriptor
/*! 
	Link a share memoey section as a file descriptor.  
	input: file name for the file descriptor. 
	output: int **shm_buf; start position of the share memory. 
	return -1 if error occured.
	return 1 if ok.
*/
void shm_lock_init(unsigned char *shm_buf, const int shm_size); // Jason added 20150122

int shm_link(unsigned char **shm_buf, const char *filename, const int shm_size);
//! read the content from the share memory and put it into rbuf
/*!
	input:
		*shm_buf: 	pointer to the share memory buffer
		shm_size: 	full size of share memory data
		start: 		startig index, 0...inf
		length: 	length of memory segment to read
	
	output:
		*rbuf: 		pointer to recieving buffer
*/
void shm_read(unsigned char *rbuf, unsigned char *shm_buf, const int shm_size, const int start, const int lengthl, int mode=0); // default value=0;
//! write the content from the wbuf into shm_buf
/*!
	input:
		*wbuf: 	pointer to the share memory buffer
		shm_size: 	full size of share memory data
		start: 		startig index, 0...inf
		length: 	length of memory segment to read

	output:
		*shm_buf: 	pointer to share memory
*/
void shm_write(unsigned char *shm_buf, unsigned char *wbuf, const int shm_size, const int start, const int length, int mode=0);


//! Remove the share memory 
void shm_destroy(unsigned char **shm_buf, const char *filename, const int shm_size);


#endif

