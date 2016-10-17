/**
  ******************************************************************************
  * @file    main.c 
  * @author  aal1
  * @version V1.0
  * @date    30.09.2015
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 BFH TI Bienne - aal1 </center></h2>
  *
  ******************************************************************************
	* @information
	*
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** Fonts */
#include "font5x7.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* System */
static __IO uint32_t uwTimingDelay;
extern uint32_t ms_ticks;
RCC_ClocksTypeDef RCC_Clocks;

/* RTC 1/10 Second */
__IO uint32_t TimeDisplay = 0;


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
	float ax, ay, az;
	
  /* SysTick end of count event each 1ms */
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);
	
	/* Hardware Configuration and Initialisation */
  RCC_configuration();
	GPIO_configuration();
	ADC_configuration();
	SPI_configuration();
	I2C_configuration();
	NVIC_configuration();
	
	//$TASK SPI: Turn on all dots - test whether LCD has been initialised properly
	glcd_command(0xA5);

//_$todo	while(1); 
	
	//$TASK glcd
	glcd_select_screen((uint8_t *)&glcd_buffer,&glcd_bbox);
	glcd_reset();
	glcd_ST7565R_init();
	
	//$TASK RTC
	RTC_initialisation();
	
	//$TASK Accelerometer
	MMA7660init();
	
	//$TASK glcd
	/* Set the font */
	/* write "hello world" on display */
	
	while(1) {
    /* If 100ms has been elapsed */
    if (TimeDisplay == 1)
    {
			//$TASK ADC
			/* set contrast of display with ADC value from potentiometer 1 */

			
			//$TASK Accelerometer
			/* get acceleration data */
			
      Display(RTC_GetCounter(),readTemperatur(), ax, ay, az);
      TimeDisplay = 0;
    }
	}
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void delay_ms(__IO uint32_t nTime)
{ 
  uwTimingDelay = nTime;

  while(uwTimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (uwTimingDelay != 0x00)
  { 
    uwTimingDelay--;
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
