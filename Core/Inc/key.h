#ifndef __KEY_H__
#define __KEY_H__
#include "main.h"





#define FUN_KEY_VALUE()                                 HAL_GPIO_ReadPin(INPUT_KEY_FUN_GPIO_Port ,INPUT_KEY_FUN_Pin )

#define CONFIRM_KEY_VALUE()                             HAL_GPIO_ReadPin(INPUT_KEY_CONFIRM_GPIO_Port,INPUT_KEY_CONFIRM_Pin)

#define KEY_FUN_CONFIRM_LED_SetHigh()   			  	HAL_GPIO_WritePin(FUN_CONFIRM_LED_GPIO_Port, FUN_CONFIRM_LED_Pin, GPIO_PIN_SET)
#define KEY_FUN_CONFIRM_LED_SetLow()     				HAL_GPIO_WritePin(FUN_CONFIRM_LED_GPIO_Port, FUN_CONFIRM_LED_Pin, GPIO_PIN_RESET)







#define		_KEY_ALL_OFF				 0XFF

//normal times be pressed key
#define		_KEY_POWER     		0x01  //key power
#define		_KEY_MODE     		0x02  //key mode
#define		_KEY_DEC     			0x04  //key dec
#define		_KEY_ADD     			0x08  //key add



//long times be pressed
#define		_KEY_CONT_1_POWER     	     0x81    //??????--???
#define	   KEY_CONFIRM_MODE   		     0x82    //??????--???
#define		_KEY_CONT_3_DEC    	         0x84    //?????? ?????
#define		_KEY_CONT_4_ADD     	     0x88    //??? --?????

#define KEY0_PRES 	0x01
#define KEY1_PRES	0x02
#define KEY2_PRES	0x04
#define WKUP_PRES   0x08



#define HIGH_LEVEL                   1  /* 根据原理图设计，KEY1按下时引脚为低电平，所以这里设置为0 */


typedef enum
{
  KEY_UP   = 1,
  KEY_DOWN = 0,
}KEYState_TypeDef;




typedef  struct  _state_
{
 unsigned char         read;
 unsigned char         buffer;
 unsigned long          value;
 unsigned char        off_time;
 unsigned long        on_time;

 enum{
  start  = 0,
  first  = 1,
  second = 2,
  cont   = 3,
  end    = 4,
  finish = 5,
 }state;
}key_types;




uint8_t KEY_Scan(void);










#endif 



