#ifndef _GPIO_H
#define _GPIO_H



//Ports
#define Port_A 0
#define Port_B 1
#define Port_C 2
#define Port_D 3
#define Port_E 4
#define Port_F 5

//Pins
#define Pin_0 0
#define Pin_1 1
#define Pin_2 2
#define Pin_3 3
#define Pin_4 4
#define Pin_5 5
#define Pin_6 6
#define Pin_7 7

// PIN Directions 
#define INPUT  0
#define OUTPUT 1

// PIN Value Options 
#define HIGH   1
#define LOW    0



void DIO_PORT_Init(int port);
void DIO_Pull_Pin_Up(int port,int pin);
void DIO_Pull_Pin_Down(int port,int pin);
void DIO_Set_Port_Value(int port, int data);
void DIO_Set_Port_Direction(int port, int direction);
void DIO_Set_Pin_Value(int port, int pin, int value );
void DIO_Set_Pin_Direction(int port,int pin,int direction);
int DIO_Get_Pin_Value(int port,int pin);


#endif


