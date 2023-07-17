#include "run.h"
#include "key.h"
#include "led.h"
#include "ntc.h"
#include "FreeRTOS.h"
#include "task.h"
#include "tm1650.h"
#include "smg.h"


touchpad_t tpd_t;
uint8_t led_on_of_number;


/***********************************************************
	*
	*Function Name: void Run_InputKey_Model(uint8_t keyvalue)
	*Function: parse of input key value
	*Input Ref: input key of value 
	*Retrun Ref:NO
	*
***********************************************************/
void Run_InputKey_Model(uint8_t keyvalue)
{
   
    static uint8_t confirm_flag;
    switch(tpd_t.read_key_value){
			
	

		case FUNCTION_KEY_PRES: //FUN

         

	    if(tpd_t.keep_heat_fun_digital_numbers ==1){
              tpd_t.gTimer_keep_heat_fun=0;
               tpd_t.gTimer_select_fun=0;
              tpd_t.gTimer_exit_keey_heat_fun=0;
              
			  tpd_t.digital_numbers++; //scope : 0~40度
			  if(tpd_t.digital_numbers>40) tpd_t.digital_numbers=0;
	
			   tpd_t.run_process_tag= KEY_FUNCTION_ITEM;
              

		}
		else{

	     tpd_t.run_process_tag= KEY_FUNCTION_ITEM;
	     if(led_on_of_number == KEEP_HEAT_LED)led_on_of_number =0;
	     led_on_of_number++;
		 led_t.gTimer_flicker=0;
		 tpd_t.gTimer_select_fun=0;
		   
		  
		}
		break;
	
		case CONFIRM_KEY_PRES: //CONFIRM_KEY
		  

		if(tpd_t.keep_heat_fun_digital_numbers ==1){
              tpd_t.gTimer_keep_heat_fun=0;
             tpd_t.gTimer_select_fun=0;
              tpd_t.gTimer_exit_keey_heat_fun=0;
			  tpd_t.digital_numbers--; //scope : 0~40度--; //scope : 0 ~40 degree
			  if(tpd_t.digital_numbers < 0)  tpd_t.digital_numbers=40; //scope : 0~80度=80;
			
              tpd_t.run_process_tag= KEY_FUNCTION_ITEM;
              
			  
		}
		else{
        
		        tpd_t.run_process_tag= KEY_CONFIRM_ITEM;
           }
	
		break;

		case KEY_LONG_PRES_CONFIRM_MODE : //long key
            if(led_on_of_number == KEEP_HEAT_LED){
               tpd_t.gTimer_exit_keey_heat_fun =0;
              if(tpd_t.keep_heat_fun_digital_numbers==1){
                tpd_t.confirm_key_select_item_keep_heat = keep_heat_enable; 
    
    			tpd_t.keep_heat_fun_digital_numbers=0;
                KEEP_HEAT_LED_ON();
                ADD_DEC_LED_OFF();
                KEY_FUN_CONFIRM_LED_SetLow();
    			tpd_t.run_process_tag= KEY_NULL ;//KEY_CONFIRM_ITEM;
                
            }

            }

		break;

	    
		}

}

/***********************************************************
	*
	*Function Name: void Run_BoardCommand_Handler(void)
	*Function: contiunce of process 
	*Input Ref: NO
	*Retrun Ref:NO
	*
***********************************************************/
void Run_BoardCommand_Handler(void)
{

     static uint8_t keep_heat_confirm;
	 switch(tpd_t.run_process_tag){
         

	 case KEY_FUNCTION_ITEM:
	   if(tpd_t.keep_heat_fun_digital_numbers ==1){
           Run_Keep_Heat_Setup_Digital_Numbers();

        }

       Led_Display_Content_Fun(led_on_of_number);
       

     break;

	 case KEY_CONFIRM_ITEM:

       Key_Confirm_Handler(led_on_of_number);
	 

	 break;

	
     }

}


void Run_Display_Handler(void)
{

    static uint8_t first_power_on;

	switch(tpd_t.keep_heat_fun_digital_numbers){

	  case 0:
		
	if(tpd_t.gTimer_read_adc >12 || tpd_t.power_on_times < 50){
	  tpd_t.gTimer_read_adc =0;
      if(tpd_t.power_on_times < 10){
           Read_NTC_Temperature_Power_On();
      }
	  else	
	      Read_NTC_Temperature_Value_Handler();
    }
	
	if(tpd_t.gTimer_display > 6 || tpd_t.power_on_times < 50){
      tpd_t.gTimer_display=0; 
	  tpd_t.power_on_times++;
        
         Smg_Display_Temp_Degree_Handler();
        
    }

	if(first_power_on==0){
		first_power_on++;
       KEY_FUN_CONFIRM_LED_SetLow();

	}

    break;

	case 1:
      Run_Keep_Heat_Setup_Digital_Numbers();
			

	break;
   }

}



