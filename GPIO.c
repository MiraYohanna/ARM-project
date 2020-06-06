#include "GPIO.h"
#include "DIO_REG.h"

volatile int* Lock_reg[6]={GPIO_PORTA_LOCK_REG,
													GPIO_PORTB_LOCK_REG,
													GPIO_PORTC_LOCK_REG,
													GPIO_PORTD_LOCK_REG,
													GPIO_PORTE_LOCK_REG,
													GPIO_PORTF_LOCK_REG};

volatile int* Commit_reg[6]={GPIO_PORTA_CR_REG,
														GPIO_PORTB_CR_REG,
														GPIO_PORTC_CR_REG,
														GPIO_PORTD_CR_REG,
														GPIO_PORTE_CR_REG,
													  GPIO_PORTF_CR_REG};

														

volatile int* DigitalEnable [6]={GPIO_PORTA_DEN_REG,
																GPIO_PORTB_DEN_REG,
																GPIO_PORTC_DEN_REG,
																GPIO_PORTD_DEN_REG,
																GPIO_PORTE_DEN_REG,
															  GPIO_PORTF_DEN_REG};	

volatile int* AlternativeFunction [6]={GPIO_PORTA_AFSEL_REG,
																		 GPIO_PORTB_AFSEL_REG,
																		 GPIO_PORTC_AFSEL_REG,
																		 GPIO_PORTD_AFSEL_REG,
																		 GPIO_PORTE_AFSEL_REG,
																		 GPIO_PORTF_AFSEL_REG};
		
																		 
volatile int* PortControl [6]={GPIO_PORTA_PCTL_REG,
															GPIO_PORTB_PCTL_REG,
															GPIO_PORTC_PCTL_REG,
															GPIO_PORTD_PCTL_REG,
															GPIO_PORTE_PCTL_REG,
															GPIO_PORTF_PCTL_REG};
							
volatile int* AnalogMode [6]= {GPIO_PORTA_AMSEL_REG,
													 GPIO_PORTB_AMSEL_REG,
													 GPIO_PORTC_AMSEL_REG,
													 GPIO_PORTD_AMSEL_REG,
													 GPIO_PORTE_AMSEL_REG,
													 GPIO_PORTF_AMSEL_REG};		

volatile int* Pull_up_registers[6]={GPIO_PORTA_PUR_REG,
																		GPIO_PORTB_PUR_REG,
																		GPIO_PORTC_PUR_REG,
																		GPIO_PORTD_PUR_REG,
																		GPIO_PORTE_PUR_REG,
																		GPIO_PORTF_PUR_REG};
volatile int* Pull_down_registers[6]={GPIO_PORTA_PDR_REG,
																		GPIO_PORTB_PDR_REG,
																		GPIO_PORTC_PDR_REG,
																		GPIO_PORTD_PDR_REG,
																		GPIO_PORTE_PDR_REG,
																		GPIO_PORTF_PDR_REG};

volatile int* Data_Registers[6]= {GPIO_PORTA_DATA_REG,
																	GPIO_PORTB_DATA_REG,
																	GPIO_PORTC_DATA_REG,
																	GPIO_PORTD_DATA_REG,
																	GPIO_PORTE_DATA_REG,
																	GPIO_PORTF_DATA_REG};

volatile int* Direction_Registers[6]={GPIO_PORTA_DIR_REG,
																			GPIO_PORTB_DIR_REG,
																			GPIO_PORTC_DIR_REG,
																			GPIO_PORTD_DIR_REG,
																			GPIO_PORTE_DIR_REG,
																			GPIO_PORTF_DIR_REG};

																			
void DIO_PORT_Init(int port)
	{ 
		
		
		*SYSCTL_RCGCGPIO_REG |= (1<<port);    // connecting the clock 
		                                // we do that to save the previous data in this reg and to shift the 1 to the req pin only
		
		*Lock_reg[port]= 0x4C4F434B;  // unlocking single port
													
		
		*Commit_reg[port]=0xFF;       //commiting all pins of the selected port
		
														
		*DigitalEnable[port]= 0xFF;   // enable digital mode for all pins of selected port 
																
		
																
		*AlternativeFunction[port]= 0x00;    //NO alternative functions only I/O
																		 
		*PortControl[port]= 0x0000;           //knt bahot fi rakm al fn lw fi 

		
		*AnalogMode[port]= 0x00;      // no analog mode 
															
																	
																
	}
	void DIO_Pull_Pin_Up(int port,int pin)
	{
		*Pull_up_registers[port] |= (1<<pin);
		
		
	}
	
	void DIO_Pull_Pin_Down(int port,int pin)
	{
		*Pull_down_registers[port] |= (1<<pin);
			
	}
	
	void DIO_Set_Port_Value(int port, int data)
	{
		*Data_Registers[port]= data;
	}
	
	void DIO_Set_Port_Direction(int port, int direction)
	{
		*Direction_Registers[port]=direction;
	}
	
	void DIO_Set_Pin_Value(int port, int pin, int value )
	{
		if(value==1)
		{
			*Data_Registers[port] |=(1<<pin);
		
		}else if (value==0)
		{
			*Data_Registers[port] &= ~(1<<pin);
		}
	}
	
	void DIO_Set_Pin_Direction(int port,int pin,int direction)
	{
		if(direction==1)
		{
			*Direction_Registers[port] |=(1<<pin);
		
		}else if (direction==0)
		{
			*Direction_Registers[port] &= ~(1<<pin);
		}
	}
	int DIO_Get_Pin_Value(int port,int pin)
	{
		int value=((*Data_Registers[port]) >> (pin)) & 0x01;
	  return value;
	}
	