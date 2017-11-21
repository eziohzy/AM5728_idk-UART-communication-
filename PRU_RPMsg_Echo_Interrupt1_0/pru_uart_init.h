#include <pru_uart.h>
#include <pru_intc.h>
#include <stdint.h>

void pru_uart_initialize();

uint16_t pru_uart_write(unsigned char *Txbuf , uint16_t TxSize);
uint16_t pru_uart_read(unsigned char *Rxbuf, uint16_t RxSize);

