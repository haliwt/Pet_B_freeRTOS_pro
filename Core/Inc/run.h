#ifndef __RUN_H__
#define __RUN_H__
#include "main.h"


typedef enum {
    KEY_FUNCTION_ITEM=0x01,
	KEY_CONFIRM_ITEM=0x02


}key_item;


typedef enum{

   key_confirm_disable,
   key_confirm_enable

}key_confirm_state;


typedef struct _touchpad_t{

   //smg
   uint8_t gTimer_smg;
   uint8_t decate_temp_value;
   uint8_t uint_tem_value;
   uint8_t decimal_point_temp_value;
   uint8_t  temperature_value;
   uint8_t temperature_decimal_point_value;
   uint8_t read_key_value;
   uint8_t run_process_tag;
   uint8_t keep_heat_flag;

 
   //display net temperatur degree
   uint8_t read_ntc_display_integer_value;
   uint8_t read_ntc_display_decimals_value;
   uint8_t gTimer_read_adc;
   uint8_t gTimer_display;
   uint8_t gTimer_select_fun;
   uint8_t confirm_key_select_item_fan;
   uint8_t confirm_key_select_item_tape;
   uint8_t confirm_key_select_item_sterilization;
   uint8_t confirm_key_select_item_keep_heat;
   uint8_t confirm_key_select_item_add_dec;
   uint8_t gTimer_keep_heat_fun;
  
   uint8_t keep_heat_run_flag;
   uint8_t keep_heat_fun_digital_numbers;
   uint8_t gTimer_exit_keey_heat_fun;
   uint8_t key_confirm_enable ;
  


   uint8_t power_on_times;
   uint8_t temperature_rectify_value;
   uint8_t temp_degree;
   uint8_t keep_heat_temperature_value_low;
   
   
   

	//taouchpad
	 int8_t digital_numbers;
	 uint16_t ntc_voltage_value;



}touchpad_t;


extern touchpad_t tpd_t;



void Run_InputKey_Model(uint8_t keyvalue);

void Run_BoardCommand_Handler(void);
void Run_Display_Handler(void);



#endif 



