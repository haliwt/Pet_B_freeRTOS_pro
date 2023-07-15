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
#define  QUEUE_LEN    1   /* ¶ÓÁÐµÄ³¤¶È£¬×î´ó¿É°üº¬¶àÉÙ¸öÏûÏ¢ */
#define  QUEUE_SIZE   1   /* ¶ÓÁÐÖÐÃ¿¸öÏûÏ¢´óÐ¡£¨×Ö½Ú£© */

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
//�������ȼ�
#define START_TASK_PRIO		1
//�����ջ��С	
#define START_STK_SIZE 		128 
//�������ȼ�
#define LED_TASK_PRIO		3
//�����ջ��С	
#define LED0_STK_SIZE 		128  


//�������ȼ�
#define KEY_TASK_PRIO		2
//�����ջ��С	
#define KEY_STK_SIZE 		64

//SemaphoreHandle_t MuxSem_Handle =NULL;

QueueHandle_t Key_Queue =NULL;

/**************************** ������ ********************************
 
 * ��������һ��ָ�룬����ָ��һ�����񣬵����񴴽���֮�����;�����һ��������
 * �Ժ�����Ҫ��������������Ҫͨ��������������������������������Լ�����ô
 * ����������ΪNULL��
***********************************************************************/
static TaskHandle_t AppTaskCreate_Handle = NULL;/* ���������� */
static TaskHandle_t Led_Task_Handle = NULL;/* LED������ */
static TaskHandle_t KEY_Task_Handle = NULL;/* KEY����*/

/**************************************************************************
 *        ��������
**************************************************************************/
void AppTaskCreate(void);/* ���ڴ������� */

void Led_Task(void* pvParameters);/* Led_Task����ʵ�� */
void KEY_Task(void* pvParameters);/* KEY_Task����ʵ�� */

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
  //������ʼ����
   xTaskCreate((TaskFunction_t )AppTaskCreate,            //������
                (const char*    )"AppTaskCreate",          //��������
                (uint16_t       )START_STK_SIZE,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
                (TaskHandle_t*  )&AppTaskCreate_Handle);   //������   

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
  * @ ������  �� AppTaskCreate
  * @ ����˵���� Ϊ�˷����������е����񴴽����������������������
  * @ ����    �� ��  
  * @ ����ֵ  �� ��
  **********************************************************************/
void AppTaskCreate(void)
{
  BaseType_t xReturn = pdPASS;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdPASS */
  
  taskENTER_CRITICAL();           //�����ٽ���

  Key_Queue = xQueueCreate((UBaseType_t) QUEUE_LEN,
                           (UBaseType_t) QUEUE_SIZE);
  if(NULL !=Key_Queue)
      printf("create queue success\r\n") ;                   
  
  xReturn = xTaskCreate((TaskFunction_t )KEY_Task,  /* ������ں��� */
                        (const char*    )"KEY_Task",/* �������� */
                        (uint16_t       )KEY_STK_SIZE,  /* ����ջ��С */
                        (void*          )NULL,/* ������ں������� */
                        (UBaseType_t    )3, /* ��������ȼ� */
                        (TaskHandle_t*  )&KEY_Task_Handle);/* ������ƿ�ָ�� */ 
  if(pdPASS == xReturn)
    printf("KEY_Task success\r\n");
                        
  /* ����Test_Task���� */
  xReturn = xTaskCreate((TaskFunction_t )Led_Task, /* ������ں��� */
                        (const char*    )"Led_Task",/* �������� */
                        (uint16_t       )LED0_STK_SIZE,    /* ����ջ��С */
                        (void*          )NULL,	/* ������ں������� */
                        (UBaseType_t    )2,	    /* ��������ȼ� */
                        (TaskHandle_t*  )&Led_Task_Handle);/* ������ƿ�ָ�� */

  if(pdPASS == xReturn)
    printf("led_task success \r\n");
  
  vTaskDelete(AppTaskCreate_Handle); //ɾ��AppTaskCreate����
  
  taskEXIT_CRITICAL();            //�˳��ٽ���
}

/**********************************************************************
  * @ ������  �� Test_Task
  * @ ����˵���� Test_Task��������
  * @ ����    ��   
  * @ ����ֵ  �� ��
  ********************************************************************/
void Led_Task(void* parameter)
{	
  BaseType_t xReturn = pdPASS;
  uint32_t r_queue;
  uint8_t key_value;
  KEY_FUN_CONFIRM_LED_SetLow();
  while (1)
  {

     xReturn = xQueueReceive( Key_Queue,    /* ÏûÏ¢¶ÓÁÐµÄ¾ä±ú */
                             &r_queue,      /* ·¢ËÍµÄÏûÏ¢ÄÚÈÝ */
                             portMAX_DELAY); /* µÈ´ýÊ±¼ä Ò»Ö±µÈ *///portMAX_DELAY
   
    if(xReturn == pdTRUE){

      

       printf("Led_Task receive = %d \r\n",r_queue);  

      switch(r_queue){

      case 1:
          key_value = FUNCTION_KEY_PRES;

      break;

      case 2:
        key_value = CONFIRM_KEY_PRES;

      break;

      case 3:
           key_value = KEY_LONG_PRES_CONFIRM_MODE;
      break;

       }
   
        Run_InputKey_Model(key_value);
        Run_BoardCommand_Handler();
    	Run_Display_Handler();
     

     

    }
//    else
//        printf("queue is error = %d \r\n",xReturn);   
//   
    
   // taskYIELD();
    vTaskDelay(3);   /* ��ʱ500��tick */
    }
   // vTaskDelay(100);   /* ��ʱ500��tick */
 }


/**********************************************************************
  * @ ������  �� Test_Task
  * @ ����˵���� Test_Task��������
  * @ ����    ��   
  * @ ����ֵ  �� ��
  ********************************************************************/
void KEY_Task(void* parameter)
{	
 // touchpad_t tpd_t;
 BaseType_t xReturn = pdPASS;/* define return of value ,defualt value pdPASS */

 uint32_t send_key_fun = 1;
 uint32_t send_key_confirm =2;
 uint32_t send_key_long_confir =3;
  while (1)
  {

  
    tpd_t.read_key_value=KEY_Scan();

    switch(tpd_t.read_key_value){

     case FUNCTION_KEY_PRES: //FUN
       xReturn = xQueueSend(Key_Queue, 
                             &send_key_fun, 
                             0);
       if(xReturn ==pdPASS){
          printf("send_key_fun success !\r\n");

       }

     break;

     case CONFIRM_KEY_PRES: //CONFIRM_KEY
      xReturn = xQueueSend(Key_Queue, 
                             &send_key_confirm, 
                             0);
       if(xReturn ==pdPASS){
          printf("send_key_con success !\r\n");

       }

     break;

     case KEY_LONG_PRES_CONFIRM_MODE : //long key 
     xReturn = xQueueSend(Key_Queue, 
                             &send_key_long_confir, 
                             0 );
       if(xReturn ==pdPASS){
          printf("Led_Task_Handle_3 success !\r\n");

       }

     break;


    }

    vTaskDelay(10);/* ��ʱ20��tick */
  
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
