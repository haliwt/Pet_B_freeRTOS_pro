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
   
    switch(tpd_t.read_key_value){
			
	

		case FUNCTION_KEY_PRES: //FUN

         

	    if(tpd_t.keep_heat_fun_digital_numbers ==1){
              tpd_t.gTimer_keep_heat_fun=0;
               tpd_t.gTimer_select_fun=0;
              tpd_t.gTimer_exit_keey_heat_fun=0;
              if(tpd_t.digital_numbers==0)tpd_t.digital_numbers=20;
              else
			    tpd_t.digital_numbers++; //scope : 0~40度
			  if(tpd_t.digital_numbers>25) tpd_t.digital_numbers=20;
	
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
              
			  if(tpd_t.digital_numbers ==0)tpd_t.digital_numbers=20;
              else
                tpd_t.digital_numbers--; //scope : 0~40度--; //scope : 0 ~40 degree
			  if(tpd_t.digital_numbers < 20)  tpd_t.digital_numbers=25; //scope : 0~80度=80;
			
              tpd_t.run_process_tag= KEY_FUNCTION_ITEM;
             
              
			  
		}
		else{
               if(tpd_t.key_confirm_enable ==key_confirm_enable){
		            tpd_t.run_process_tag= KEY_CONFIRM_ITEM;

                }
               else{ //display setup keep heat temperature value 
                 
                    if(tpd_t.confirm_key_select_item_keep_heat == keep_heat_enable){
                      
                        
                          tpd_t.run_process_tag= DISPLAY_KEEP_HEAT_TEMP_VALUE;
                          tpd_t.gTimer_display =0;
      

                    }

               }
           }
	
		break;

		case KEY_LONG_PRES_CONFIRM_MODE : //long key
            if(led_on_of_number == KEEP_HEAT_LED ){
               tpd_t.gTimer_exit_keey_heat_fun =0;
               tpd_t.key_confirm_enable =key_confirm_disable;
              if(tpd_t.keep_heat_fun_digital_numbers==1){
                tpd_t.confirm_key_select_item_keep_heat = keep_heat_enable; 
                if(tpd_t.digital_numbers ==0)tpd_t.digital_numbers=20;
                
    			tpd_t.keep_heat_fun_digital_numbers=0;
                KEEP_HEAT_LED_ON();
                ADD_DEC_LED_OFF();
                KEY_FUN_CONFIRM_LED_SetLow();
                RELAY_D_SetHigh();
    			tpd_t.run_process_tag= DISPLAY_KEEP_HEAT_TEMP_VALUE ;//KEY_CONFIRM_ITEM;
    			tpd_t.gTimer_display=0;
    			
                
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

 
	 switch(tpd_t.run_process_tag){
         

	 case KEY_FUNCTION_ITEM:
	   if(tpd_t.keep_heat_fun_digital_numbers ==1){
        
           Run_Keep_Heat_Setup_Digital_Numbers();
        //   Keep_heat_SetUp_Led_Filcker();
           

        }
       else
         Led_Display_Content_Fun(led_on_of_number);
       

     break;

	 case KEY_CONFIRM_ITEM:

       Key_Confirm_Handler(led_on_of_number);
	 

	 break;

     case DISPLAY_KEEP_HEAT_TEMP_VALUE:

        if(tpd_t.gTimer_display < 3 &&  tpd_t.confirm_key_select_item_keep_heat == keep_heat_enable){
           
            
        
            Run_Display_Keep_Heat_Temperature_Vaule();
      
        }
        else{

            tpd_t.run_process_tag= KEY_NULL ;

        }



  

     break;

	
     }
     
     if(tpd_t.gTimer_exit_keey_heat_fun > 7 &&  tpd_t.keep_heat_fun_digital_numbers==1 ){
  
        tpd_t.keep_heat_fun_digital_numbers=0;
     
        ADD_DEC_LED_OFF();
        KEY_FUN_CONFIRM_LED_SetLow();
        if(tpd_t.confirm_key_select_item_keep_heat == keep_heat_enable){
              ADD_DEC_LED_OFF();
              KEEP_HEAT_LED_ON();
              RELAY_D_SetHigh();


        }
        else{
            ADD_DEC_LED_OFF();
            KEEP_HEAT_LED_OFF();
            RELAY_D_SetLow();

           

        }
    	tpd_t.run_process_tag= KEY_NULL ;//KEY_CONFIRM_ITEM;


    }


}



/***************************************************************************
    *
    *Function Name:void Run_Display_Handler(void)
    *Function :display smg and led of content 
    *Input Ref:NO
    *Return Ref:NO
    *
***************************************************************************/
void Run_Display_Handler(void)
{
    
	if(tpd_t.gTimer_read_adc >59 || tpd_t.power_on_times < 50){
	  tpd_t.gTimer_read_adc =0;
      tpd_t.power_on_times++;
      if(tpd_t.power_on_times < 50){
           Read_NTC_Temperature_Power_On();
      }
	  else{	
	      Read_NTC_Temperature_Value_Handler();
          
       }
     }

      Smg_Display_Temp_Degree_Handler();

     

    
        
    


    if(tpd_t.confirm_key_select_item_keep_heat == keep_heat_enable){
        if(tpd_t.digital_numbers > tpd_t.temperature_value  || tpd_t.temperature_value <20){  //open on

              tpd_t.keep_heat_temperature_value_low =0;
    		  KEEP_HEAT_LED_ON();
              RELAY_D_SetHigh();
            
    	  	 
       }
       else if((tpd_t.digital_numbers -2) <=tpd_t.temperature_value || tpd_t.temperature_value > 25){
        // KEEP_HEAT_LED_OFF();
         RELAY_D_SetLow();
         tpd_t.keep_heat_temperature_value_low =1;


       }
    }



 }





