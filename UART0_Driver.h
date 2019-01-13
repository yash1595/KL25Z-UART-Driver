/*
 * Uart0_Init.h
 *
 *  Created on: Nov 7, 2018
 *      Author: yashm
 */
#include "MKL25Z4.h"
#include "enums.h"

#include <string.h>
#define DLY 100000

#ifndef INCLUDE_HEADERS_UART0_INIT_H_
#define INCLUDE_HEADERS_UART0_INIT_H_

UART0_Type* _UART0 = UART0;
SIM_Type* _SIM = SIM;
PORT_Type* _PORTA = PORTA;
#define TERM_PORT_NUM	0
#define MUX_UART0		(0x00000100)
#define	_PORTA_PCR1	(*((uint32_t*)0x40049004))
#define	_PORTA_PCR2	(*((uint32_t*)0x40049008))

errtype (*ptr[6]) (char , uint32_t );                                           //Defines array of function pointers.

uint32_t characters[256]={0};
uint8_t i=0,entered=0;

void uart0_pinset()                                                             //Sets the PORTA pins with suitable MUX values for UART0.
{
	SIM_SCGC5  |= SIM_SCGC5_PORTA_MASK;

	PORTA_PCR1 |= PORT_PCR_MUX(2);
	PORTA_PCR2 |= PORT_PCR_MUX(2);

}


void uart0_init ()                                                              //Initializes UART0's clock and baud.
{
	  uint8_t i=0;
    uint32_t osr_val = 0;
    uint32_t sbr_val = 0;

    SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;

    // Disable UART0 before changing registers
    UART0_C2 &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK);

    SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);
    SIM_SOPT2 &= ~SIM_SOPT2_PLLFLLSEL_MASK;
    //SIM_SOPT2 |= (SIM_SOPT2_UART0SRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);

    osr_val = 0x04;
    sbr_val = 0X0222;

    UART0_BDH = UART0_BDH_SBR(((sbr_val & 0x1F00) >> 8));
    UART0_BDL = (uint8_t)(sbr_val & UART0_BDL_SBR_MASK);

    UART0_C1 = 0;
    UART0_C2 = 0;
    UART0_C2 |= (UART0_C2_TE_MASK);

    UART0_C3 = 0;

    UART0_C4 = UART0_C4_OSR(osr_val-1);

    UART0_C5  = UART0_C5_BOTHEDGE_MASK;

    UART0_C2 |= UART_C2_RIE_MASK;

    UART0_C2 |= (UART0_C2_RE_MASK );


}

char uart0_getchar ()                                                     //Waits for a character to be received on uart0.
{
      /* Wait until character has been received */
      while (!(UART0_S1 & UART0_S1_RDRF_MASK));

      /* Return the 8-bit data from the receiver */
      return UART0_D;
}

uint32_t uart0_strtoint()                                                 //Converts string to integer for calculations.
{
	//char received[15];
	char ch=0;
	//char temp=0;
	uint32_t value=0;
	int STAT=-1;
	uint32_t i=0,j=0;
	ch=uart0_getchar();
	if(type==TYPE)if(ch<'0'||ch>'9')return -1;                             //If the input is not a number returns an error.
	//else if(ch>index||Cyc)
	uart0_putchar(ch);
	//received[0] = uart0_getchar();
	//ch = uart0_getchar();
	if(type==TYPE)value=value*10+(ch-'0');                                 //Converts char to int.
	while (ch!=13)
			{
				 //i+=1;
				 ch = (char)uart0_getchar();
				 if(ch==13)break;
				 if(type==TYPE)if(ch<'0'||ch>'9')return -1;
				 uart0_putchar(ch);//ch = (char)uart0_getchar();
				 value=value*10+(ch-'0');
			}
				return value;//value;

}

void uart0_putchar (char ch)                                            //Puts character on uart.
{
      while(!(UART0_S1 & UART0_S1_TDRE_MASK));

      UART0_D = (uint8_t)ch;
   

 }

void uart0_putstr(const uint8_t *str)                                  //Puts string for display on UART0.

{
    while(*str != '\0')uart0_putchar(*str++);

}

errtype uart0_getstr(void)                                            //Receives string from the terminal and calls the appropriate function.
{
	char received[8]={0};
	errtype status=-1;
	int STAT=-1;
	int8_t i=0,j=0;
	uint32_t k=0;

					char ch=0;
					ch=uart0_getchar();

					for(i=0;i<6;i++)
					{
						if(ch==i+'0')
							{
								allocate_flag=i;
								status=(*ptr[i])(0,0);
								uart0_putstr(errtypes[status]);
								return Success;
							}

					}
						return InvalidInput;
}

void display_character_count(void)                                    //Displays the characters entered during Nonblocking and their count.
{//disable_irq(12);
uint32_t rev=0;
uint32_t num,count;
volatile uint32_t k,z;
uart0_putchar('\n');
 for(k=32;k<256;k++){
   //k=97;
	 if(characters[k]>0){
	Delay_ms(1);
    count=0;
    if ((UART0_S1&UART_S1_TDRE_MASK)||(UART0_S1&UART_S1_TC_MASK))UART0_D = ((char)k);
    Delay_ms(1);
    if ((UART0_S1&UART_S1_TDRE_MASK)||(UART0_S1&UART_S1_TC_MASK))UART0_D = ((char)45);
    num = characters[(uint32_t)k];
    if(num==0)
    	{
    	Delay_ms(1);
    	if ((UART0_S1&UART_S1_TDRE_MASK)||(UART0_S1&UART_S1_TC_MASK))UART0_D = ((char)'0');
    	Delay_ms(1);
    	if ((UART0_S1&UART_S1_TDRE_MASK)||(UART0_S1&UART_S1_TC_MASK))UART0_D = 13;
    	continue;
    	}
    while(num>0)
    {
        rev=rev*10+(num%10);
        num=num/10;
        count+=1;
    }
   while(rev>0)
   {
   	if ((UART0_S1&UART_S1_TDRE_MASK)||(UART0_S1&UART_S1_TC_MASK))
  		{
   		    UART0_D = (char)(rev%10 +'0');
   	         rev=rev/10;
   	         count--;
   		}
   }

    while(count!=0)
    	{
       		if ((UART0_S1&UART_S1_TDRE_MASK)||(UART0_S1&UART_S1_TC_MASK))
        		{
         			UART0_D = (char)(0+'0');
         			count--;
         		}
    	}
    Delay_ms(1);
    if ((UART0_S1&UART_S1_TDRE_MASK)||(UART0_S1&UART_S1_TC_MASK))UART0_D = 13;

 }
 	 }
 	 uart0_putstr("Fibonacci Series:");for(z=0;z<100;z++){uart0_inttostr(_fibonacci[z]);uart0_putchar(32);} //Displays the fibonacci series in the idle state.

  }

void UART0_IRQHandler (void)
{
  char c = 0;
  int result=-1;
  uint8_t io=0;
  if (UART0_S1&UART_S1_RDRF_MASK)
  {
    c = UART0_D;
    if(mode==BLOCKING){                                                               //Uses the enter key to select which function is to be selected.
    if(c==13)
    	{
    		uart0_putstr("Selected:");
    		uart0_putstr(functions[count]);
    	    uart0_putchar('\n');
    	    disable_irq(12);
    	    result = (*ptr[count]) (0,0);
    	    uart0_putstr(errtypes[result]);
    	    enable_irq(12);
    	}
    }
	if(mode==NONBLOCKING){                                                             //Uses 'ESC' to indicate display of report or displays the report when buffer is full.
    if(c == 27)
        {
        	flag=SET;
        }
        stat=AddDataCycBuff(c,0);
        if(flag==FULL){flag=SET;uart0_putstr(errtypes[status]);}
    }

  }
}
void uart0_inttostr(uint32_t num)                                                    //Converts integers to string for display.
{	uint32_t rev=0,count=0;
	while(num>0)
	{
	rev=rev*10+(num%10);
	num=num/10;
	count+=1;
	}
	while(rev>0)
	{
	uart0_putchar(rev%10 +'0');
	rev=rev/10;
	count--;
	}
	while(count!=0)
	{
	  if ((UART0_S1&UART_S1_TDRE_MASK)||(UART0_S1&UART_S1_TC_MASK))
	  {
	       uart0_putchar(0+'0');
	       count--;
	  }
	}
}
void ISR(void)
{
	UART0_IRQHandler();
}



#endif /* INCLUDE_HEADERS_UART0_INIT_H_ */
