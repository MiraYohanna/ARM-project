#include "stdint.h"
#include "tm4c123gh6pm.h"
#include "BIT_MATH.h"
#include "GPIO.h"
#include "UART.h"
#include "KPAD_int.h"
#define FREE '0'
#define OCCUPIED '1'
#define CLEANING '2'

void SystemInit(){};
	
	int main()
	{
		
		char password[4];
		char room_password[4];
		char room_number;  
		int i;
		int flag= 0;
		
		/* red led --> occupied
			 green led --> cleaning
			 blue led --> free
		   solenoid valve is connected to pin 5 in port f
		   high --> open
		   low --> locked
		*/
		UART_Init();
		DIO_PORT_Init(Port_F); //for leds
		DIO_PORT_Init(Port_B); //for keypad
		DIO_Set_Port_Direction(Port_B,0x0f);
		// assigning 3 leds as output
		DIO_Set_Pin_Direction(Port_F,Pin_1,OUTPUT);
		DIO_Set_Pin_Direction(Port_F,Pin_2,OUTPUT);
		DIO_Set_Pin_Direction(Port_F,Pin_3,OUTPUT);
		// solenoid key pin
		DIO_Set_Pin_Direction(Port_F,Pin_5,OUTPUT);
		KPAD_VidInit();
		UART_Tx_string("Please enter the room number");
		room_number = UART_Rx();
		UART_Tx_string("To set password press 1 ");

		while(1)
		{
			char status;
			char key;

			

			if(room_number=='5')
			{	

				status=UART_Read();
				if(status!='*')
				{

					switch(status)
				{
					case OCCUPIED:             //room is occupied 
								UART_Tx_string("Please enter the room Password");
							for(i=0;i<4;i++)     // setting your password 
							{
								
								password[i]=UART_Rx();
								UART_Tx(password[i]);
							}
							GPIO_PORTF_DATA_R=0X00;
							DIO_Set_Pin_Value(Port_F,Pin_5,LOW);
							DIO_Set_Pin_Value(Port_F,Pin_1,HIGH);			//red led is on
							UART_Tx_string("Password is set sucesfully");
							break;
					case CLEANING:           //room is in cleaning status
							GPIO_PORTF_DATA_R=0X00;
							DIO_Set_Pin_Value(Port_F,Pin_5,HIGH); //the selonoid valve is open
							DIO_Set_Pin_Value(Port_F,Pin_3,HIGH);			//green led is on
							break;
					case FREE:         //room is free(checking out)
							GPIO_PORTF_DATA_R=0X00;
							DIO_Set_Pin_Value(Port_F,Pin_5,LOW); //the selonoid valve is always closed
							DIO_Set_Pin_Value(Port_F,Pin_2,HIGH);			//blue led is on
							break;
								
				}
				
				}
					
			}
			


			
			
			
			key = KPAD_u8GetKeyPressed();
				
			if(key !='z')
				{
					UART_Tx(key);
					room_password[0]=key;
					key = 'z';
					for(i=1;i<4;i++)
					{
						while(key =='z')
						{
							key = KPAD_u8GetKeyPressed();
						}
						UART_Tx(key);
	
		 				room_password[i]=key;
						key = 'z';
					}
					for(i=0;i<4;i++)
					{
						if(password[i]!=room_password[i])
						{
							flag=1;
							break;
						}
					}
					if(flag==1) //wrong password
					{
						GPIO_PORTF_DATA_R=0X00;
						DIO_Set_Pin_Value(Port_F,Pin_5,LOW);
						DIO_Set_Pin_Value(Port_F,Pin_1,HIGH);
					}
					else if(flag==0)   //right password
					{
						GPIO_PORTF_DATA_R=0X00;
						DIO_Set_Pin_Value(Port_F,Pin_5,HIGH);
						DIO_Set_Pin_Value(Port_F,Pin_3,HIGH);
						UART_Tx_string("Room unlocked!");

						
					}
					
				}
		}
				
	}
				
	