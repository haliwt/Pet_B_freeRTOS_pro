#include "led.h"
#include "run.h"
#include "key.h"

LED_T led_t;




static void Fan_Led_Flicker(void);
static void Tape_Led_Flicker(void);
static void Sterilization_Led_Filcker(void);
static void Keep_Heat_Led_Filcker(void);

static void Add_Dec_Led_Filcker(void);
//static void Keep_heat_SetUp_Led_Filcker(void);

/*************************************************************************
	*
	*Function Name: void Led_Display_Content_Fun(uint8_t selitem)
	*Function : flicker of fan led
	*Input Ref: wich of led flicker -selitem
	*Return Ref:NO
	*
*************************************************************************/
void Led_Display_Content_Fun(uint8_t selitem)
{
   switch(selitem){

   case LED_NULL:
     

   break;

   case FAN_LED:


		if(tpd_t.confirm_key_select_item_tape == tape_enable){
			TAPE_LED_ON();
		    
		    RELAY_B_SetHigh()	;

		}
		else{
    		TAPE_LED_OFF();
    		RELAY_B_SetLow();

		}

		if(tpd_t.confirm_key_select_item_sterilization == sterilization_enable ){
		    STERILIZATION_LED_ON();
            RELAY_C_SetHigh();
		}
		else{
		    STERILIZATION_LED_OFF();

          } 

		

		if(tpd_t.confirm_key_select_item_keep_heat == keep_heat_enable){
		   if(tpd_t.keep_heat_temperature_value_low ==0){
              RELAY_D_SetHigh();
    		  KEEP_HEAT_LED_ON();
          }
          else{
              KEEP_HEAT_LED_ON();
              RELAY_D_SetLow();
             

          }
	  	}
	    else{ 
	  		KEEP_HEAT_LED_OFF();
            RELAY_D_SetLow();


           }

		
   	 
	 if(tpd_t.gTimer_select_fun < 6){
        tpd_t.key_confirm_enable =key_confirm_enable;
        Fan_Led_Flicker();
        
     }
     else{
         if(tpd_t.confirm_key_select_item_fan == confirm_disable){
          FAN_LED_OFF();
          RELAY_A_SetLow();
          tpd_t.run_process_tag = KEY_NULL;
          }
          else{
             tpd_t.run_process_tag = KEY_NULL;
          }
          tpd_t.key_confirm_enable =key_confirm_disable;

     }


   break;

   case TAPE_LED:

      if(tpd_t.confirm_key_select_item_fan == fan_enable){
		FAN_LED_ON();
		
		RELAY_A_SetHigh();
		}
		else{
		FAN_LED_OFF();
		RELAY_A_SetLow();

		}

        

		if(tpd_t.confirm_key_select_item_sterilization == sterilization_enable ){
            RELAY_C_SetHigh();
		    STERILIZATION_LED_ON();
		}
		else{
            RELAY_C_SetLow();
		    STERILIZATION_LED_OFF();//STERILIZATION_LED_OFF();

        }

		

		if(tpd_t.confirm_key_select_item_keep_heat == keep_heat_enable){
           if(tpd_t.keep_heat_temperature_value_low ==0){
              RELAY_D_SetHigh();
    		  KEEP_HEAT_LED_ON();
          }
          else{
              KEEP_HEAT_LED_ON();
              RELAY_D_SetLow();
              

          }
	  	}
	     else{
            RELAY_D_SetLow();
	  		KEEP_HEAT_LED_OFF();//KEEP_HEAT_LED_OFF();
          }
   	  
	 if(tpd_t.gTimer_select_fun < 6){
        tpd_t.key_confirm_enable =key_confirm_enable;
   	    Tape_Led_Flicker();
	 }
     else{
        if(tpd_t.confirm_key_select_item_tape == confirm_disable){

        TAPE_LED_OFF();
        RELAY_B_SetLow();
         tpd_t.run_process_tag = KEY_NULL;
        }
        else{
          tpd_t.run_process_tag = KEY_NULL;
        }
        tpd_t.key_confirm_enable =key_confirm_disable;
     }

	 

   break;

   case STERILIZATION_LED:
      //FAN 
      if(tpd_t.confirm_key_select_item_fan == fan_enable){
		FAN_LED_ON();
		RELAY_A_SetHigh()	;
		}
		else{
		FAN_LED_OFF();
		RELAY_A_SetLow()	;

		}

       //TAPE
		if(tpd_t.confirm_key_select_item_tape == tape_enable){
		TAPE_LED_ON();
		RELAY_B_SetHigh()	;

		}
		else{
			TAPE_LED_OFF();//TAPE_LED_OFF();
		   RELAY_B_SetLow()	;
		}
        //KEEP HEAT
		if(tpd_t.confirm_key_select_item_keep_heat == keep_heat_enable){
		   if(tpd_t.keep_heat_temperature_value_low ==0){
              RELAY_D_SetHigh();
    		  KEEP_HEAT_LED_ON();
          }
          else{
             KEEP_HEAT_LED_ON();
             RELAY_D_SetLow();
              

          }
	  	}
	     else{
            RELAY_D_SetLow();
	  		KEEP_HEAT_LED_OFF();//KEEP_HEAT_LED_OFF();

          }


     //STERILIZATION
      if(tpd_t.gTimer_select_fun < 6){
         tpd_t.key_confirm_enable =key_confirm_enable;
   	     Sterilization_Led_Filcker();
       }
       else{
           if(tpd_t.confirm_key_select_item_sterilization == confirm_disable){

            STERILIZATION_LED_OFF();
            RELAY_C_SetLow();
             tpd_t.run_process_tag = KEY_NULL;
           }
           else{
             tpd_t.run_process_tag = KEY_NULL;
          }
          tpd_t.key_confirm_enable =key_confirm_disable;

       }


   break;

   case KEEP_HEAT_LED:
        //FAN
       if(tpd_t.confirm_key_select_item_fan == fan_enable){
		FAN_LED_ON();
		RELAY_A_SetHigh();
		}
		else{
		FAN_LED_OFF();
		RELAY_A_SetLow();

		}

        //TAPE
		if(tpd_t.confirm_key_select_item_tape == tape_enable){
    		TAPE_LED_ON();
    		
    		RELAY_B_SetHigh();

    	}
    	else{
    		TAPE_LED_OFF();//TAPE_LED_OFF();
    		
    		RELAY_B_SetLow();
    		

		}
        //STERILIZATION 
		if(tpd_t.confirm_key_select_item_sterilization == sterilization_enable ){
		    STERILIZATION_LED_ON();
            RELAY_C_SetHigh()	;
            
		}
		else{
    		STERILIZATION_LED_OFF();//STERILIZATION_LED_OFF();
    		RELAY_C_SetLow()	;

         }

	
      //KEEP HEAT Display of LED 
       if( tpd_t.gTimer_select_fun < 6){
           tpd_t.key_confirm_enable =key_confirm_enable;
           if(tpd_t.keep_heat_fun_digital_numbers ==0){
               led_t.gTimer_keey_heat_flicker=0;
               tpd_t.key_confirm_enable =key_confirm_enable;
	   	       Keep_Heat_Led_Filcker();
           }
           else{
               tpd_t.key_confirm_enable =key_confirm_enable;
               Keep_heat_SetUp_Led_Filcker();

           }
           tpd_t.gTimer_exit_keey_heat_fun=0;
	     
           tpd_t.gTimer_keep_heat_fun=0;
		
       	}
        else{
           if(tpd_t.confirm_key_select_item_keep_heat == confirm_disable){
              KEEP_HEAT_LED_OFF();
              RELAY_D_SetLow();
              tpd_t.run_process_tag = KEY_NULL;
              
            }
            

           if(tpd_t.confirm_key_select_item_keep_heat == keep_heat_enable){
             if(tpd_t.keep_heat_temperature_value_low ==0){
              RELAY_D_SetHigh();
    		  KEEP_HEAT_LED_ON();
             }
             else{
             
             KEEP_HEAT_LED_ON();

             RELAY_D_SetLow();
              

             }

             tpd_t.run_process_tag = KEY_NULL;
            }
           tpd_t.key_confirm_enable =key_confirm_disable;
        }
       

      
   break;

   case KEY_NULL:
     if(tpd_t.confirm_key_select_item_keep_heat == keep_heat_enable){
             if(tpd_t.keep_heat_temperature_value_low ==0){
              RELAY_D_SetHigh();
    		  KEEP_HEAT_LED_ON();
             }
             else{
             
             KEEP_HEAT_LED_ON();

             RELAY_D_SetLow();
              

             }

            
      }


   break;
   

   default:

   break;



   }
   


}


/*************************************************************************
	*
	*Function Name: static void Fan_Flicker(void)
	*Function : flicker of fan led
	*Input Ref: NO
	*Return Ref:NO
	*
*************************************************************************/
static void Fan_Led_Flicker(void)
{
   
	if(led_t.gTimer_flicker < 30 ){ //10ms*10

	  FAN_LED_ON();

    }
	else if(led_t.gTimer_flicker >29 && led_t.gTimer_flicker <61){

	    
	  FAN_LED_OFF();


	}
	else{
	  led_t.gTimer_flicker=0;

    }

}


static void Tape_Led_Flicker(void)
{
	if(led_t.gTimer_flicker < 30){ //10ms*10
	
		 TAPE_LED_ON()  ;
	
	   }
	   else if(led_t.gTimer_flicker >29 && led_t.gTimer_flicker <61){
	
		  TAPE_LED_OFF();
	
	
	   }
	   else{
		 led_t.gTimer_flicker=0;
	
	   }



}


static void Sterilization_Led_Filcker(void)
{

	if(led_t.gTimer_flicker < 30){ //500ms
	
		 STERILIZATION_LED_ON();
	
	   }
	   else if(led_t.gTimer_flicker >29 && led_t.gTimer_flicker <61){
	
		  STERILIZATION_LED_OFF();
	
	
	   }
	   else{
		 led_t.gTimer_flicker=0;
	
	   }



}


static void Keep_Heat_Led_Filcker(void)
{

	if(led_t.gTimer_flicker < 30){ //500ms
	
		KEEP_HEAT_LED_ON();
	
	   }
	   else if(led_t.gTimer_flicker >29 && led_t.gTimer_flicker <61){
	
		 
	     KEEP_HEAT_LED_OFF();
	
	   }
	   else{
		 led_t.gTimer_flicker=0;
	
	  }




}


static void Add_Dec_Led_Filcker(void)
{

  
//	if(led_t.gTimer_flicker < 10){ //500ms
//
//		ADD_DEC_LED_ON();	
//	//	KEEP_HEAT_LED_ON();
//
//	}
//	else if(led_t.gTimer_flicker >9 && led_t.gTimer_flicker <21){
//
//
//		ADD_DEC_LED_OFF();		
//
//	}
//	else{
//		led_t.gTimer_flicker=0;
//
//	}

    ADD_DEC_LED_ON();	



}


void Keep_heat_SetUp_Led_Filcker(void)
{

  
	if(led_t.gTimer_keey_heat_flicker <1){ //

		KEY_FUN_CONFIRM_LED_SetLow();
		KEEP_HEAT_LED_ON();	
	  

	}
	else if(led_t.gTimer_keey_heat_flicker >0 && led_t.gTimer_keey_heat_flicker <2){


		KEY_FUN_CONFIRM_LED_SetHigh();
		KEEP_HEAT_LED_OFF();
	   
	    

	}
	else{
		led_t.gTimer_keey_heat_flicker=0;
        KEY_FUN_CONFIRM_LED_SetLow();
		KEEP_HEAT_LED_ON();	

	}

    
          






}

/*************************************************************************
	*
	*Function Name: void Key_Confirm_Handler(uint8_t selitem)
	*Function : flicker of fan led
	*Input Ref: wich of led flicker -selitem
	*Return Ref:NO
	*
*************************************************************************/
void Key_Confirm_Handler(uint8_t selitem)
{

    static uint8_t fan_confirm_flag,tape_confirm_flag,kill_confirm_flag;

   switch(selitem){

   case LED_NULL:
   
	  

   break;

   case FAN_LED:
   	    if(tpd_t.confirm_key_select_item_tape == tape_enable){
	      TAPE_LED_ON();
		  
		  RELAY_A_SetHigh()	;

	  }
	  else{
	      TAPE_LED_OFF();
		 
	      RELAY_A_SetLow()	;

	  	}

   		
     if(tpd_t.confirm_key_select_item_sterilization == sterilization_enable ){
            RELAY_C_SetHigh();
            STERILIZATION_LED_ON();
          }
          else{
             RELAY_C_SetLow();
             STERILIZATION_LED_OFF();
          }
       
       
         if(tpd_t.confirm_key_select_item_keep_heat == keep_heat_enable){
            if(tpd_t.keep_heat_temperature_value_low ==0){
                RELAY_D_SetHigh();
                KEEP_HEAT_LED_ON();
            }
            else{
              
               
                KEEP_HEAT_LED_ON();

                RELAY_D_SetLow();
               

            }
          }
          else{ 
               RELAY_D_SetLow();
               KEEP_HEAT_LED_OFF();
     
              }
	
	 // select 
	  fan_confirm_flag = fan_confirm_flag ^ 0x01;
       if(fan_confirm_flag==1){
    	  tpd_t.confirm_key_select_item_fan = fan_enable ;
          FAN_LED_ON(); 
    	  RELAY_A_SetHigh() ;

        }
        else{
            tpd_t.confirm_key_select_item_fan = confirm_disable ;
             FAN_LED_OFF(); 
             RELAY_A_SetLow() ;
        }
     
    
      tpd_t.run_process_tag=KEY_NULL;
   break;

   case TAPE_LED:
   	   if(tpd_t.confirm_key_select_item_fan == fan_enable){
   	     FAN_LED_ON();
		  RELAY_A_SetHigh()   ;
   	   }
	   else{
	     FAN_LED_OFF();
		 RELAY_A_SetLow()   ;

	   }

	    if(tpd_t.confirm_key_select_item_sterilization == sterilization_enable ){
         RELAY_C_SetHigh();
         STERILIZATION_LED_ON();
       }
	   else{
          RELAY_C_SetLow();
	      STERILIZATION_LED_OFF();
       }
	
	
	  if(tpd_t.confirm_key_select_item_keep_heat == keep_heat_enable){
           if(tpd_t.keep_heat_temperature_value_low ==0){
              RELAY_D_SetHigh();
    		  KEEP_HEAT_LED_ON();
          }
          else{
                KEEP_HEAT_LED_ON();
              RELAY_D_SetLow();
             

          }
	  	}
	   else{ 
            RELAY_D_SetLow();
	  		KEEP_HEAT_LED_OFF();

           }

	 
	  
	  //Select tape led fun
	  tape_confirm_flag = tape_confirm_flag ^ 0x01;
       if(tape_confirm_flag==1){
    	  tpd_t.confirm_key_select_item_tape = tape_enable;
    	 
       	  TAPE_LED_ON();
    	  RELAY_B_SetHigh()	;
      }
      else{
          tpd_t.confirm_key_select_item_tape = confirm_disable ;

           TAPE_LED_OFF();
           RELAY_B_SetLow() ;
           
       }
	  
    tpd_t.run_process_tag=KEY_NULL;
   break;

   case STERILIZATION_LED:
   	   if(tpd_t.confirm_key_select_item_fan == fan_enable){
   	     FAN_LED_ON();
		 RELAY_A_SetHigh()   ;
   	   }
	   else{
	     FAN_LED_OFF();
		 RELAY_A_SetLow()   ;
	   }

      if(tpd_t.confirm_key_select_item_tape == tape_enable){
	      TAPE_LED_ON();
		  
	  	  RELAY_B_SetHigh()   ;

	  }
	  else{
	      TAPE_LED_OFF();
		
	       RELAY_B_SetLow()   ;

	  }
	 
	   if(tpd_t.confirm_key_select_item_keep_heat == keep_heat_enable){
          if(tpd_t.keep_heat_temperature_value_low ==0){
              RELAY_D_SetHigh();
    		  KEEP_HEAT_LED_ON();
          }
          else{
              KEEP_HEAT_LED_ON();
              RELAY_D_SetLow();
             

          }
	  	}
	   else{ 
            RELAY_D_SetLow();
	  		KEEP_HEAT_LED_OFF();

           }
	   
 
	  
	  //select sterilization fun
	   kill_confirm_flag = kill_confirm_flag ^ 0x01;
       if(kill_confirm_flag==1){
    	   tpd_t.confirm_key_select_item_sterilization = sterilization_enable ;
           STERILIZATION_LED_ON();
           RELAY_C_SetHigh();
       }
       else{
         tpd_t.confirm_key_select_item_sterilization = confirm_disable ;

          STERILIZATION_LED_OFF();
          RELAY_C_SetLow();


       }
   	   
    tpd_t.run_process_tag=KEY_NULL;
       
   break;

   case KEEP_HEAT_LED:

       if(tpd_t.confirm_key_select_item_fan == fan_enable){
   	     FAN_LED_ON();
		 RELAY_A_SetHigh()   ;
   	   }
	   else{
	     FAN_LED_OFF();
		 RELAY_A_SetLow()   ;

	   }

      if(tpd_t.confirm_key_select_item_tape == tape_enable){
	      TAPE_LED_ON();
          
		   RELAY_B_SetHigh()   ;

	  }
	  else{
	      TAPE_LED_OFF();
		  RELAY_B_SetLow()	;
	  	}
   	    
       if(tpd_t.confirm_key_select_item_sterilization == sterilization_enable ){
         RELAY_C_SetHigh();
         STERILIZATION_LED_ON();
       }
	   else{
	      STERILIZATION_LED_OFF();
          RELAY_C_SetLow();

       }

      
     //control 
     if(tpd_t.confirm_key_select_item_keep_heat == keep_heat_enable){
  
                 KEEP_HEAT_LED_OFF();
           
				tpd_t.keep_heat_fun_digital_numbers=0;
                KEY_FUN_CONFIRM_LED_SetLow() ;

                tpd_t.confirm_key_select_item_keep_heat=confirm_disable;
                 RELAY_D_SetLow();
                tpd_t.run_process_tag=KEY_NULL; 

      
        }
        else{
         if(tpd_t.gTimer_keep_heat_fun< 11){
	
				tpd_t.keep_heat_fun_digital_numbers=1; //select keep heat item 
				ADD_DEC_LED_ON();  
				Keep_heat_SetUp_Led_Filcker();
           
				
			}
			else{
                if(tpd_t.confirm_key_select_item_keep_heat == confirm_disable){
				tpd_t.gTimer_keep_heat_fun= 12;
				 RELAY_D_SetLow();
				KEEP_HEAT_LED_OFF();
				ADD_DEC_LED_OFF();  
			    
                }
                else {
                     if(tpd_t.keep_heat_temperature_value_low ==0){
                          RELAY_D_SetHigh();
                		  KEEP_HEAT_LED_ON();
                      }
                      else{
                          KEEP_HEAT_LED_ON();
                          RELAY_D_SetLow();
                         

                      }
                }
             
				tpd_t.keep_heat_fun_digital_numbers=0;
                KEY_FUN_CONFIRM_LED_SetLow() ;
                tpd_t.run_process_tag=KEY_NULL; 
               

            }
           }
       
	  break;

	
    
	
    case KEY_NULL:
      

      KEY_FUN_CONFIRM_LED_SetLow() ;
      if(tpd_t.confirm_key_select_item_keep_heat == keep_heat_enable){
          if(tpd_t.keep_heat_temperature_value_low ==0){
              RELAY_D_SetHigh();
    		  KEEP_HEAT_LED_ON();
          }
          else{
              KEEP_HEAT_LED_ON();
              RELAY_D_SetLow();
             

          }
	  }
      
      
   break;

   default:

   break;



   }


}




