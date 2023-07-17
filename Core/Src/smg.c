#include "smg.h"
#include "tm1650.h"
#include "run.h"
#include "led.h"


void Run_Keep_Heat_Setup_Digital_Numbers(void)
{

    switch(tpd_t.keep_heat_fun_digital_numbers ==1){

	case 0:

	break;

	case 1:

        Smg_Display_Digital_Numbers_Changed(tpd_t.digital_numbers );

    break;

	
    }

}





