#ifndef _UART_H
#define _UART_H

void UART_Init(void);
void UART_Tx (char character);
char UART_Rx (void);
char UART_Read (void);
void UART_Tx_string (char* word);


#endif
