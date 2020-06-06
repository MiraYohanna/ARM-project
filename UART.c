#include "stdint.h"
#include "BIT_MATH.h"
#include "tm4c123gh6pm.h"
#include "GPIO.h"
#include "UART.h"


	void UART_Init(void)
	{
		SYSCTL_RCGCUART_R |=0X01; //use port B as UART -->UART1
		SYSCTL_RCGCGPIO_R |=0X01;  //Connect the clock to port B
		UART0_CTL_R &= ~0X001;  //disable the UART -->clearing the first bit only wl ba2y zai mahoma 
		UART0_IBRD_R =104;    //clk divisor=16000000/(16*9600)
		UART0_FBRD_R=11;      //(0.166667*64)+0.5
		UART0_LCRH_R =0X0070;   //default number of stop bits stop, 8-bit data length, enable fifo 
		UART0_CTL_R = 0X0301;  //enable the uart after finishing configuration
		GPIO_PORTA_AFSEL_R |= 0X03; //UART function for pin 0 and 1
		GPIO_PORTA_PCTL_R |=1;  //set bit 0 (first 4 bits responsible for fn of pb0)
		GPIO_PORTA_PCTL_R |=(1<<4);  //set bit 4 (second 4 bits responsible for fn of pb1)
		GPIO_PORTA_DEN_R |=0X03; //PIN 0 AND 1 are digital enabled
		GPIO_PORTA_AMSEL_R &=~0X03; //Analog mode is diabled for PIN 0 AND 1
		
	}
	void UART_Tx (char character) //transmission function
	{
		while(GET_BIT(UART0_FR_R,5)==1) // TXFF=1, FIFO buffer at transmitter is full,can't transmit any new character
		{}
		UART0_DR_R=character; //writing data
			
	}
	char UART_Rx (void)  //recieving function
	{
		char character;
		while(GET_BIT(UART0_FR_R,4)==1) //RXFE=1, FIFO buffer at reciever is empty, nothing to read 
		{}
		 character=UART0_DR_R; //reading data
			return character;
	}
	
	
	char UART_Read (void)  //recieving function
	{
		char character;
		if(GET_BIT(UART0_FR_R,4)==0) //RXFE=1, FIFO buffer at reciever is full, data is ready
		{character=UART0_DR_R; //reading data
			return character;
		}
		 character='*'; //no read data
			return character;
	}
	void UART_Tx_string (char* word) //transmission function
	{
		int i=0;
		while(word[i]!='\0')
		{
			UART_Tx(word[i]);
			i++;
		}
		
	}