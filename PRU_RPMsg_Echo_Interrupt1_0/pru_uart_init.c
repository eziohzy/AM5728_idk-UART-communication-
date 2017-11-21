#include "pru_uart_init.h"

#define UART_PRU_INTERRUPT 6

void pru_uart_initialize()
{
	/*Over-Sampling mode select,0:16x 1:13x*/
	CT_UART.MDR = 0;

	/*Most-significant bits and least-significant bits of
	 *16-bit divisor for generation of the baud clock
	 */
	CT_UART.DLH = 0;
	CT_UART.DLL = 0x00000002;

	/*Interrupt enable register.[0-3]
	 *1:enable interrupt 0:disable interrupt
	 *7:enable data available,transmitter empty,line status interrupt
	 */
	CT_UART.IER = 0x00000007;

	/*1:FIFO mode 0:Non-FIFO mode*/
//	CT_UART.IIR_FCR_bit.FCR_FIFOEN = 0x1;

	//tx_trig= 16   rx_trig=16
	CT_UART.IIR_FCR = 0x00000047;
	/*1:Clear receiver FIFO and reset FIFO counter*/
//	CT_UART.IIR_FCR_bit.FCR_RXCLR = 0x1;
	/*1:Clear transmitter FIFO and reset FIFO counter*/
//	CT_UART.IIR_FCR_bit.FCR_TXCLR = 0x1;
	/*DMA MODE1 is disabled*/
//	CT_UART.IIR_FCR_bit.FCR_DMAMODE1 = 0x0;
	/*Receiver FIFO trigger level.	When trigger level is reached,data-ready
	 *interrupt is generated.0:1 byte 1:4 bytes 2:8 bytes
	 *3:14 bytes*/
//	CT_UART.IIR_FCR_bit.FCR_RXFIFTL = 0x2;

	/*Line control register*/
	CT_UART.LCR = 0x00000003;

	/*Modem control register
	 *autoflow control is disabled,loop back mode is enabled
	 *RTS is disabled */
	CT_UART.MCR = 0x00000000;
	
	/*Free-running mode is enabled*/
	CT_UART.PWREMU_MGMT_bit.FREE = 0x1;
	/*Receiver is enabled*/
	CT_UART.PWREMU_MGMT_bit.URRST = 0x1;
	/*Transmitter is enabled*/
	CT_UART.PWREMU_MGMT_bit.UTRST = 0x1;




}

/*
void pru_uart_interrupt_init()
{
	CT_INTC.SIPR0 = 0xFFFFFFFF;
	CT_INTC.SITR0 = 0x00000000;
	CT_INTC.CMR1 = 0x01000101;
	CT_INTC.HMR0 = 0x03020100;

	CT_INTC.SECR0 = 0xFFFFFFFF;
	CT_INTC.SECR1 = 0xFFFFFFFF;

	CT_INTC.EISR = UART_PRU_INTERRUPT;
	CT_INTC.HIEISR = 0;
	CT_INTC.GER = 0x00000001;

	CT_UART.IER = 0x00000007;
}
*/

uint16_t pru_uart_write( unsigned char *Txbuf , uint16_t TxSize)
{
	uint16_t i,j;

	for(i = 0;i < TxSize; i=i+16)
	{
		for(j = 0;j < 16;j++)
			CT_UART.RBR_THR_bit.DATA = Txbuf[i+j];
		while(CT_UART.LSR_bit.THRE == 0);
	}
	return 0;
}

uint16_t pru_uart_read(unsigned char *Rxbuf, uint16_t RxSize)
{
	uint16_t i;

//	while((CT_UART.IIR_FCR_bit.IIR_IPEND == 1) || (CT_UART.IIR_FCR_bit.IIR_INTID != 0x2) )
//	{}
//	for(j=0; j < RxSize/8 ; j++){
//		while((CT_UART.IIR_FCR_bit.IIR_IPEND == 1) || (CT_UART.IIR_FCR_bit.IIR_INTID != 0x2) )
//		{}
//	while((CT_UART.IIR_FCR_bit.IIR_INTID != 0x2) )
//	{}
//	while(CT_UART.LSR_bit.DR == 0)
//	{}



			for(i = 0; i < RxSize ; i++)
			{
				while(CT_UART.LSR_bit.DR == 0);

				Rxbuf[i] = CT_UART.RBR_THR_bit.DATA;
			}//?

//		k=k+8;

//	}
	return 0;
}


