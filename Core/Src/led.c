#include "led.h"
#include "run.h"
#include "key.h"

LED_T led_t;




static void Fan_Led_Flicker(void);
static void Tape_Led_Flicker(void);
static void Sterilization_Led_Filcker(void);
static void Keep_Heat_Led_Filcker(void);

static void Add_Dec_Led_Filcker(void);
static void Keep_heat_SetUp_Led_Filcker(void);

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
		}
		else
		    STERILIZATION_LED_OFF();

		if(tpd_t.confirm_key_select_item_add_dec == add_dec_enable ){
		    ADD_DEC_LED_ON();	 
		}
		else 
		 ADD_DEC_LED_OFF();	 

		if(tpd_t.confirm_key_select_item_keep_heat == keep_heat_enable){
		  KEEP_HEAT_LED_ON();
	  	}
	     else 
	  		KEEP_HEAT_LED_OFF();

		
   	 
	 if(tpd_t.gTimer_select_fun < 6){
        Fan_Led_Flicker();
		  

	 }
     else{
	  
	  	FAN_LED_OFF();
		tpd_t.confirm_key_select_item_fan = confirm_disable;
		tpd_t.gTimer_select_fun =8;
		RELAY_A_SetLow()	;
     }


   break;

   case TAPE_LED:

      if(tpd_t.confirm_key_select_item_fan == fan_enable){
		FAN_LED_ON();//FAN_LED_ON();
		
		RELAY_A_SetHigh()	;
		}
		else{
		FAN_LED_OFF();//FAN_LED_OFF();
		
		RELAY_A_SetLow()	;

		}

		if(tpd_t.confirm_key_select_item_sterilization == sterilization_enable ){
		STERILIZATION_LED_ON();
		}
		else
		STERILIZATION_LED_OFF();//STERILIZATION_LED_OFF();

		if(tpd_t.confirm_key_select_item_add_dec == add_dec_enable ){
		ADD_DEC_LED_ON();	 
		}
		else 
		ADD_DEC_LED_OFF();//ADD_DEC_LED_OFF();	

		if(tpd_t.confirm_key_select_item_keep_heat == keep_heat_enable){
		  KEEP_HEAT_LED_ON();
	  	}
	     else 
	  		KEEP_HEAT_LED_OFF();//KEEP_HEAT_LED_OFF();
   	  
	 if(tpd_t.gTimer_select_fun < 6){
   	    Tape_Led_Flicker();
	 }
	 else{
	    tpd_t.gTimer_select_fun =8;
		tpd_t.confirm_key_select_item_tape = confirm_disable ;
         TAPE_LED_OFF();//TAPE_LED_OFF();
		
		 RELAY_B_SetLow()	;

	 }
	 

   break;

   case STERILIZATION_LED:

      if(tpd_t.confirm_key_select_item_fan == fan_enable){
		FAN_LED_ON();//FAN_LED_ON();
		RELAY_A_SetHigh()	;
		}
		else{
		FAN_LED_OFF();//FAN_LED_OFF();
		RELAY_A_SetLow()	;

		}

		if(tpd_t.confirm_key_select_item_tape == tape_enable){
		TAPE_LED_ON();
		
			
		RELAY_B_SetHigh()	;

		}
		else{
			TAPE_LED_OFF();//TAPE_LED_OFF();
		
		
		     RELAY_B_SetLow()	;
		}

		if(tpd_t.confirm_key_select_item_keep_heat == keep_heat_enable){
		  KEEP_HEAT_LED_ON();
	  	}
	     else 
	  		KEEP_HEAT_LED_OFF();//KEEP_HEAT_LED_OFF();


   
      if(tpd_t.gTimer_select_fun < 6){
   	     Sterilization_Led_Filcker();
       }
	   else{
	   	  tpd_t.gTimer_select_fun =8;
		  tpd_t.confirm_key_select_item_sterilization = confirm_disable;
		  STERILIZATION_LED_OFF();//STERILIZATION_LED_OFF();
		 
	   }

   break;

   case KEEP_HEAT_LED:

       if(tpd_t.confirm_key_select_item_fan == fan_enable){
		FAN_LED_ON();//FAN_LED_ON();
		RELAY_A_SetHigh()	;
		}
		else{
		FAN_LED_OFF();//FAN_LED_OFF();
		RELAY_A_SetLow()	;

		}

		if(tpd_t.confirm_key_select_item_tape == tape_enable){
		TAPE_LED_ON();
		
		RELAY_B_SetHigh()	;

		}
		else{
		TAPE_LED_OFF();//TAPE_LED_OFF();
		
		RELAY_B_SetLow()	;
		

		}

		if(tpd_t.confirm_key_select_item_sterilization == sterilization_enable ){
		STERILIZATION_LED_ON();
		}
		else
		STERILIZATION_LED_OFF();//STERILIZATION_LED_OFF();

	
   
       if(tpd_t.gTimer_select_fun < 6){
	   	   Keep_Heat_Led_Filcker();
		   tpd_t.keep_heat_run_flag= 1;
	       led_t.gTimer_keey_heat_flicker=0;
		   tpd_t.gTimer_keep_heat_fun=0;
		
       	}
	   else{
	     tpd_t.gTimer_select_fun =8;
		 tpd_t.confirm_key_select_item_keep_heat = confirm_disable;
	      KEEP_HEAT_LED_OFF();//KEEP_HEAT_LED_OFF();
		  tpd_t.keep_heat_run_flag= 0;


	     }
	
      
   break;

   case LED_ALL_OFF:

      FAN_LED_OFF();
	  TAPE_LED_OFF();
	  STERILIZATION_LED_OFF();
	  KEEP_HEAT_LED_OFF();
	  ADD_DEC_LED_OFF();   

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
   
	if(led_t.gTimer_flicker < 1){ //500ms

	  FAN_LED_ON();

    }
	else if(led_t.gTimer_flicker >0 && led_t.gTimer_flicker <2){

	    
	  FAN_LED_OFF();


	}
	else{
	  led_t.gTimer_flicker=0;

    }

}


static void Tape_Led_Flicker(void)
{
	if(led_t.gTimer_flicker < 1){ //500ms
	
		 TAPE_LED_ON()  ;
	
	   }
	   else if(led_t.gTimer_flicker >0 && led_t.gTimer_flicker <2){
	
		  TAPE_LED_OFF();
	
	
	   }
	   else{
		 led_t.gTimer_flicker=0;
	
	   }



}


static void Sterilization_Led_Filcker(void)
{

	if(led_t.gTimer_flicker < 1){ //500ms
	
		 STERILIZATION_LED_ON();
	
	   }
	   else if(led_t.gTimer_flicker >0 && led_t.gTimer_flicker <2){
	
		  STERILIZATION_LED_OFF();
	
	
	   }
	   else{
		 led_t.gTimer_flicker=0;
	
	   }



}


static void Keep_Heat_Led_Filcker(void)
{

	if(led_t.gTimer_flicker < 1){ //500ms
	
		KEEP_HEAT_LED_ON();
	
	   }
	   else if(led_t.gTimer_flicker >0 && led_t.gTimer_flicker <2){
	
		 
	     KEEP_HEAT_LED_OFF();
	
	   }
	   else{
		 led_t.gTimer_flicker=0;
	
	  }




}


static void Add_Dec_Led_Filcker(void)
{

  
	if(led_t.gTimer_flicker < 1){ //500ms

		ADD_DEC_LED_ON();	
		KEEP_HEAT_LED_ON();

	}
	else if(led_t.gTimer_flicker >0 && led_t.gTimer_flicker <2){


		ADD_DEC_LED_OFF();		

	}
	else{
		led_t.gTimer_flicker=0;

	}



}


static void Keep_heat_SetUp_Led_Filcker(void)
{

  
	if(led_t.gTimer_keey_heat_flicker < 1){ //500ms

		KEY_FUN_CONFIRM_LED_SetLow();
		KEEP_HEAT_LED_ON();	
	  

	}
	else if(led_t.gTimer_keey_heat_flicker >0 && led_t.gTimer_keey_heat_flicker <2){


		KEY_FUN_CONFIRM_LED_SetHigh();
		KEEP_HEAT_LED_OFF();
	   
	    

	}
	else{
		led_t.gTimer_keey_heat_flicker=0;

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
		 
	      RELAY_B_SetLow()	;

	  	}

   		if(tpd_t.confirm_key_select_item_sterilization == sterilization_enable ){
         STERILIZATION_LED_ON();
       }
	   else
	      STERILIZATION_LED_OFF();

     
	  if(tpd_t.confirm_key_select_item_keep_heat == keep_heat_enable){
		  KEEP_HEAT_LED_ON();
	  	}
	   else 
	  		KEEP_HEAT_LED_OFF();

	
	 // select 
	  tpd_t.confirm_key_select_item_fan = fan_enable ;
      FAN_LED_ON(); 
	  RELAY_A_SetHigh()	;
     
    

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
         STERILIZATION_LED_ON();
       }
	   else
	      STERILIZATION_LED_OFF();
	
	
	  if(tpd_t.confirm_key_select_item_keep_heat == keep_heat_enable){
		  KEEP_HEAT_LED_ON();
	  	}
	   else 
	  		KEEP_HEAT_LED_OFF();

	 
	  
	  //Select tape led fun
	  tpd_t.confirm_key_select_item_tape = tape_enable;
	 
   	  TAPE_LED_ON();
	  RELAY_B_SetHigh()	;
	  

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
		  KEEP_HEAT_LED_ON();
	  	}
	   else 
	  		KEEP_HEAT_LED_OFF();
	   
 
	  
	  //select sterilization fun
	   tpd_t.confirm_key_select_item_sterilization = sterilization_enable ;
       STERILIZATION_LED_ON();
   	   

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
         STERILIZATION_LED_ON();
       }
	   else
	      STERILIZATION_LED_OFF();
	   
      
	  if(tpd_t.keep_heat_run_flag==1){
           tpd_t.keep_heat_run_flag ++;
    
	  }
	  //select keep heat fun
	  switch(tpd_t.keep_heat_run_flag){

	   case 2:
			if(tpd_t.gTimer_keep_heat_fun< 11){
	
				tpd_t.keep_heat_fun_digital_numbers=1;
				ADD_DEC_LED_ON();  
				Keep_heat_SetUp_Led_Filcker();
				
			}
			else{
				tpd_t.gTimer_keep_heat_fun= 12;
				tpd_t.confirm_key_select_item_keep_heat = confirm_disable;
				KEEP_HEAT_LED_OFF();
				ADD_DEC_LED_OFF();  
			    KEY_FUN_CONFIRM_LED_SetLow() ;

				tpd_t.keep_heat_fun_digital_numbers=0;


			}
			

	  break;

	  case 3:
	  	      tpd_t.confirm_key_select_item_keep_heat = keep_heat_enable;
	          KEEP_HEAT_LED_ON();
			  ADD_DEC_LED_OFF();  
			  KEY_FUN_CONFIRM_LED_SetLow() ;


	  break;
    
	 }

   break;


   case LED_ALL_OFF:

      FAN_LED_OFF();
	  TAPE_LED_OFF();
	  STERILIZATION_LED_OFF();
	  KEEP_HEAT_LED_OFF();
	  ADD_DEC_LED_OFF();   

   break;

   default:

   break;



   }



}




