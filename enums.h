/*
 * enums.h
 *
 *  Created on: Nov 17, 2018
 *      Author: yashm
 */
#include <stdio.h>
#ifndef INCLUDE_HEADERS_ENUMS_H_
#define INCLUDE_HEADERS_ENUMS_H_
typedef enum{Buffer_Full,Success,BuffAllocationError,CycBuffAllocationError,FreeingError,FreedCycBuffs,DataDeletionError,InvalidInput}errtype;
typedef enum{TSI,TYPE}inputMode;
typedef enum{BLOCKING, NONBLOCKING}processtype;
typedef enum{CLEAR,SET,FULL}display_flag;
display_flag flag=0;
char* errtypes[]={"\nBuffer Full\n","\nSuccess\n","\nBuffer Allocation Error\n","\nCyclic Buffer Allocation Error\n","\nFreeing Error\n","\nFreed Cyclic Buffers\n","\nError Deleting Data\n","\nInvalid Input\n"};
char* functions[]={"alloc\r","add\r","disp\r","free\r","del\r"};
void uart0_putchar(char);
inputMode InputModeSelect(char*);
errtype ring_t_init(char,uint32_t);
errtype AddDataCycBuff(char ,uint32_t);
errtype DelDataCycBuff(char ,uint32_t);
errtype DisplayCycBuff(char ,uint32_t);
errtype DisplayAllBuffers(char , uint32_t);
errtype Allocate(char,uint32_t);
errtype FreeMem(char,uint32_t);
//void fibonacci(void);
void Delay_ms(uint32_t);
typedef struct{
    char* buffer;
    uint32_t Ini;
    uint32_t Outi;
    uint32_t length;
}ring_t;
uint8_t count = 0;
inputMode type=-1;
int8_t index=-1;
processtype mode=-1;
errtype status=-1;
errtype stat = -1;
char str[10];
#define	BUFFSIZE	3
ring_t* CycBuffs[BUFFSIZE]={NULL};
int8_t allocate_flag=1;

#define NO_TOUCH                 0
#define SLIDER_LENGTH           40 //LENGTH in mm
#define TOTAL_ELECTRODE          2
 #define RED_LED 18
 #define GREEN_LED 19
 #define BLUE_LED 1
 #define GPIO_PIN(x) ((1) << (x)) // Macro to manipulate a specific pin
#define NO_TOUCH                 0
#define SLIDER_LENGTH           40 //LENGTH in mm
#define TOTAL_ELECTRODE          2
 #define SLIDER_LENGTH 40



#define THRESHOLD	100

#define TSI0a        0
#define TSI1         1
#define TSI2         2
#define TSI3         3
#define TSI4         4
#define TSI5         5
#define TSI6         6
#define TSI7         7
#define TSI8         8
#define TSI9         9
#define TSI10        10
#define TSI11        11
#define TSI12        12
#define TSI13        13
#define TSI14        14
#define TSI15        15

/*Chose the correct TSI channel for the electrode number*/
#define ELECTRODE0   TSI9
#define ELECTRODE1   TSI10
#define ELECTRODE2   TSI0a
#define ELECTRODE3   TSI1
#define ELECTRODE4   TSI2
#define ELECTRODE5   TSI3
#define ELECTRODE6   TSI4
#define ELECTRODE7   TSI5
#define ELECTRODE8   TSI6
#define ELECTRODE9   TSI7
#define ELECTRODE10  TSI8
#define ELECTRODE11  TSI11
#define ELECTRODE12  TSI12
#define ELECTRODE13  TSI13
#define ELECTRODE14  TSI14
#define ELECTRODE15  TSI15

#define THRESHOLD0   100
#define THRESHOLD1   100
#define THRESHOLD2   100
#define THRESHOLD3   100
#define THRESHOLD4   100
#define THRESHOLD5   100
#define THRESHOLD6   100
#define THRESHOLD7   100
#define THRESHOLD8   100
#define THRESHOLD9   100
#define THRESHOLD10   100
#define THRESHOLD11   100
#define THRESHOLD12   100
#define THRESHOLD13   100
#define THRESHOLD14   100
#define THRESHOLD15   100

typedef enum{PRESS, NOTPRESS}escape;

escape press = NOTPRESS;

static uint8_t SliderDistancePosition[2] = {NO_TOUCH,NO_TOUCH};
static uint8_t SliderPercentagePosition[2] = {NO_TOUCH,NO_TOUCH};

static uint8_t total_electrode = TOTAL_ELECTRODE;
static uint8_t elec_array[16]={    ELECTRODE0,ELECTRODE1,ELECTRODE2,ELECTRODE3,ELECTRODE4,ELECTRODE5,
                                                                ELECTRODE6,ELECTRODE7,ELECTRODE8,ELECTRODE9,ELECTRODE10,ELECTRODE11,
                                                                ELECTRODE12,ELECTRODE13,ELECTRODE14,ELECTRODE15};
static uint16_t gu16TSICount[16];
static uint16_t gu16Baseline[16];
static uint16_t gu16Threshold[16]={THRESHOLD0,THRESHOLD1,THRESHOLD2,THRESHOLD3,THRESHOLD4,THRESHOLD5,
                                THRESHOLD6,THRESHOLD7,THRESHOLD8,THRESHOLD9,THRESHOLD10,THRESHOLD11,
                                THRESHOLD12,THRESHOLD13,THRESHOLD14,THRESHOLD15};
static uint16_t gu16Delta[16];
static uint8_t ongoing_elec;

static uint8_t end_flag = 1;


unsigned short absolutePercentagePosition = NO_TOUCH;
unsigned short baselineValue[2];
unsigned short currentElectrode;
char* calls[]={"Allocate\n","Delete\n","Display\n","Blocking\n","Non-blocking\n"};
char* circular_buffer_func[]={"Add Data\n","Delete Data\n","Display\n"};
volatile uint8_t absoluteDistancePosition = NO_TOUCH;
volatile uint8_t deltaResult[2]={0};
#endif /* INCLUDE_HEADERS_ENUMS_H_ */
