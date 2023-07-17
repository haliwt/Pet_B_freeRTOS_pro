/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "key.h"
#include "smg.h"
#include "run.h"
#include "delay.h"
#include "led.h"
#include "ntc.h"
#include "tm1650.h"
#include "interrupt_manager.h"
#include "FreeRTOS.h"
#include "task.h"
#include "run.h"
#include "semphr.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define ULONG_MAX  0xffffffffUL
#define  QUEUE_LEN    1   /* б╤ц⌠ц│ц░б╣ц└бЁб╓б╤ц┬бёб╛ц≈ц╝б╢цЁб©ц┴б╟ц╪б╨б╛б╤ц═ц┴ц≥б╦ц╤ц▐ц╩ц▐б╒ */
#define  QUEUE_SIZE   1   /* б╤ц⌠ц│ц░ц√ц░ц┐б©б╦ц╤ц▐ц╩ц▐б╒б╢цЁц░б║бёб╗ц≈ц√б╫ц бёб╘ */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//хннЯсеох╪╤
#define START_TASK_PRIO		1
//хннЯ╤яу╩╢Сп║	
#define START_STK_SIZE 		128 
//хннЯсеох╪╤
#define LED_TASK_PRIO		2
//хннЯ╤яу╩╢Сп║	
#define LED0_STK_SIZE 		128 


//хннЯсеох╪╤
#define KEY_TASK_PRIO		3
//хннЯ╤яу╩╢Сп║	
#define KEY_STK_SIZE 		64

//SemaphoreHandle_t MuxSem_Handle =NULL;

//QueueHandle_t Key1_Queue =NULL;
//QueueHandle_t Key2_Queue =NULL;
//QueueHandle_t Key3_Queue =NULL;



/**************************** хннЯ╬Д╠З ********************************
 
 * хннЯ╬Д╠Зйгр╩╦Жж╦уКё╛сцсзж╦оРр╩╦ЖхннЯё╛╣╠хннЯ╢╢╫╗╨цж╝╨Сё╛кЭ╬м╬ъспакр╩╦ЖхннЯ╬Д╠З
 * рт╨Снрцгр╙оК╡ывВуБ╦ЖхннЯ╤╪пХр╙м╗╧ЩуБ╦ЖхннЯ╬Д╠Зё╛хГ╧ШйгвтиМ╣дхннЯ╡ывВвт╪╨ё╛дгц╢
 * уБ╦Ж╬Д╠З©иртн╙NULL║ё
***********************************************************************/

static TaskHandle_t AppTaskCreate_Handle = NULL;/* ╢╢╫╗хннЯ╬Д╠З */
static TaskHandle_t Led_Task_Handle = NULL;/* LEDхннЯ╬Д╠З */
static TaskHandle_t KEY_Task_Handle = NULL;/* KEYхннЯ*/

/**************************************************************************
 *        ╨╞йЩиЫцВ
**************************************************************************/
void AppTaskCreate(void);/* сцсз╢╢╫╗хннЯ */

void Led_Task(void* pvParameters);/* Led_TaskхннЯй╣ож */
void KEY_Task(void* pvParameters);/* KEY_TaskхннЯй╣ож */

/*****************************************************************/


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_TIM14_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  delay_init(24);
  HAL_TIM_Base_Start_IT(&htim14);//HAL_TIM_Base_Start(&htim3);
  /* USER CODE END 2 */

  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  //О©╫О©╫О©╫О©╫О©╫О©╫й╪О©╫О©╫О©╫О©╫
   xTaskCreate((TaskFunction_t )AppTaskCreate,            //О©╫О©╫О©╫О©╫О©╫О©╫
                (const char*    )"AppTaskCreate",          //О©╫О©╫О©╫О©╫О©╫О©╫О©╫О©╫
                (uint16_t       )START_STK_SIZE,        //О©╫О©╫О©╫О©╫О©╫у╩О©╫О©╫п║
                (void*          )NULL,                  //О©╫О©╫О©╫щ╦О©╫О©╫О©╫О©╫О©╫О©╫О©╫О©╫д╡О©╫О©╫О©╫
                (UBaseType_t    )START_TASK_PRIO,       //О©╫О©╫О©╫О©╫О©╫О©╫О©╫х╪О©╫
                (TaskHandle_t*  )&AppTaskCreate_Handle);   //О©╫О©╫О©╫О©╫О©╫О©╫   

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}


/***********************************************************************
  * @ О©╫О©╫О©╫О©╫О©╫О©╫  О©╫О©╫ AppTaskCreate
  * @ О©╫О©╫О©╫О©╫к╣О©╫О©╫О©╫О©╫ н╙О©╫к╥О©╫О©╫О©╫О©╫О©╫О©╫О©╫О©╫О©╫О©╫п╣О©╫О©╫О©╫О©╫Я╢╢╫О©╫О©╫О©╫О©╫О©╫О©╫О©╫О©╫О©╫О©╫О©╫О©╫О©╫О©╫О©╫О©╫О©╫О©╫О©╫О©╫О©╫О©╫
  * @ О©╫О©╫О©╫О©╫    О©╫О©╫ О©╫О©╫  
  * @ О©╫О©╫О©╫О©╫ж╣  О©╫О©╫ О©╫О©╫
  **********************************************************************/
void AppTaskCreate(void)
{
  BaseType_t xReturn = pdPASS;/* О©╫О©╫О©╫О©╫р╩О©╫О©╫О©╫О©╫О©╫О©╫О©╫О©╫о╒О©╫О©╫О©╫О©╫ж╣О©╫О©╫д╛О©╫О©╫н╙pdPASS */
  
  taskENTER_CRITICAL();           //О©╫О©╫О©╫О©╫О©╫ы╫О©╫О©╫О©╫

                 
  
  xReturn = xTaskCreate((TaskFunction_t )KEY_Task,  /* О©╫О©╫О©╫О©╫О©╫О©╫з╨О©╫О©╫О©╫ */
                        (const char*    )"KEY_Task",/* О©╫О©╫О©╫О©╫О©╫О©╫О©╫О©╫ */
                        (uint16_t       )KEY_STK_SIZE,  /* О©╫О©╫О©╫О©╫у╩О©╫О©╫п║ */
                        (void*          )NULL,/* О©╫О©╫О©╫О©╫О©╫О©╫з╨О©╫О©╫О©╫О©╫О©╫О©╫О©╫ */
                        (UBaseType_t    )3, /* О©╫О©╫О©╫О©╫О©╫О©╫О©╫О©╫х╪О©╫ */
                        (TaskHandle_t*  )&KEY_Task_Handle);/* О©╫О©╫О©╫О©╫О©╫О©╫ф©О©╫ж╦О©╫О©╫ */ 
  if(pdPASS == xReturn)
    printf("KEY_Task success\r\n");
                        
  /* О©╫О©╫О©╫О©╫Test_TaskО©╫О©╫О©╫О©╫ */
  xReturn = xTaskCreate((TaskFunction_t )Led_Task, /* О©╫О©╫О©╫О©╫О©╫О©╫з╨О©╫О©╫О©╫ */
                        (const char*    )"Led_Task",/* О©╫О©╫О©╫О©╫О©╫О©╫О©╫О©╫ */
                        (uint16_t       )LED0_STK_SIZE,    /* О©╫О©╫О©╫О©╫у╩О©╫О©╫п║ */
                        (void*          )NULL,	/* О©╫О©╫О©╫О©╫О©╫О©╫з╨О©╫О©╫О©╫О©╫О©╫О©╫О©╫ */
                        (UBaseType_t    )2,	    /* О©╫О©╫О©╫О©╫О©╫О©╫О©╫О©╫х╪О©╫ */
                        (TaskHandle_t*  )&Led_Task_Handle);/* О©╫О©╫О©╫О©╫О©╫О©╫ф©О©╫ж╦О©╫О©╫ */

  if(pdPASS == xReturn)
    printf("led_task success \r\n");
  else
    printf("led_task error \r\n"); 
  
  vTaskDelete(AppTaskCreate_Handle); //и╬О©╫О©╫AppTaskCreateО©╫О©╫О©╫О©╫
  
  taskEXIT_CRITICAL();            //О©╫кЁО©╫О©╫ы╫О©╫О©╫О©╫
}

/**********************************************************************
  * @ О©╫О©╫О©╫О©╫О©╫О©╫  О©╫О©╫ Test_Task
  * @ О©╫О©╫О©╫О©╫к╣О©╫О©╫О©╫О©╫ Test_TaskО©╫О©╫О©╫О©╫О©╫О©╫О©╫О©╫
  * @ О©╫О©╫О©╫О©╫    О©╫О©╫   
  * @ О©╫О©╫О©╫О©╫ж╣  О©╫О©╫ О©╫О©╫
  ********************************************************************/
void Led_Task(void* parameter)
{	
 

  const TickType_t xMaxBlockTime = pdMS_TO_TICKS(10); /* maximum waiting 100ms */

  KEY_FUN_CONFIRM_LED_SetLow();
  while (1)
  {

   
      Run_Display_Handler();
      printf("led_task runing \r\n");
      vTaskDelay(2000);   /* О©╫О©╫й╠500О©╫О©╫tick */

     

    }

 }
 


/**********************************************************************
  * @ О©╫О©╫О©╫О©╫О©╫О©╫  О©╫О©╫ Test_Task
  * @ О©╫О©╫О©╫О©╫к╣О©╫О©╫О©╫О©╫ Test_TaskО©╫О©╫О©╫О©╫О©╫О©╫О©╫О©╫
  * @ О©╫О©╫О©╫О©╫    О©╫О©╫   
  * @ О©╫О©╫О©╫О©╫ж╣  О©╫О©╫ О©╫О©╫
  ********************************************************************/
void KEY_Task(void* parameter)
{	
 // touchpad_t tpd_t;
 BaseType_t xReturn = pdPASS;/* define return of value ,defualt value pdPASS */
 
  while (1)
  {

   
    tpd_t.read_key_value=KEY_Scan();
    if(tpd_t.read_key_value!=0){
        vTaskSuspend(Led_Task_Handle);/* б╩ц√б╦б╢LEDц┬ц▌ц▌ц╠бёб║ */
        printf("vTaskSuspend is success \r\n");

     }
    Run_InputKey_Model(tpd_t.read_key_value);
    Run_BoardCommand_Handler();


    if(tpd_t.run_process_tag==KEY_NULL){
        tpd_t.run_process_tag++;
        printf("vTaskResume is success \r\n");
        vTaskResume(Led_Task_Handle);/* б╩ц√б╦б╢LEDц┬ц▌ц▌ц╠бёб║ */
        
     }
    vTaskDelay(1);/* О©╫О©╫й╠20О©╫О©╫tick */
  
     }

}
/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 9;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV6;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
