#ifndef __NTC_H_
#define __NTC_H_
#include "main.h"

typedef enum{
   decimals,
   integer

}read_ntc_value;


void Read_NTC_Temperature_Power_On(void);

void Read_NTC_Temperature_Value_Handler(void);




#endif 
