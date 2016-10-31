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

/**
* @brief Counter for the delay function
 */
static __IO uint32_t uwTimingDelay;

/**
* @brief Millisecond system counter, managed by SysTick_Handler 
*/
extern uint32_t ms_ticks;

/**
* @brief Configuration variable for the system clock
*/
RCC_ClocksTypeDef RCC_Clocks;

/**
* @brief RTC 1/10 Second
*/
__IO uint32_t TimeDisplay = 0;

// defines for the displays
#define DATACOL 0
#define ROW1 0
#define ROW2 8
#define ROW3 16
#define ROW4 24

/* Private function prototypes -----------------------------------------------*/
uint8_t getContrast(uint16_t raw_value);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Scales the value of the potentiometer linearly between 0 and 63, such that
	it can be used to set the constrast of the LCD.
  * @param  raw_value Raw value of the potentiometer, bounded between 0 and 4095
  * @retval ocnstrast Contrast value scaled between 0 and 63
  */
uint8_t getContrast(uint16_t raw_value){
	uint8_t contrast;
	contrast = (uint8_t)(((float)raw_value) * 63.0 / 4095);
	return contrast;
}

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
	float ax, ay, az;
	
	uint16_t tempRaw;
	float temp;
	
	char text1[25];
	
	//char contrast_text[5];
	uint16_t pot_1_value_raw;
	uint8_t contrast;
	
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
	glcd_select_screen((uint8_t *)&glcd_buffer, &glcd_bbox);
	glcd_reset();
	glcd_ST7565R_init();
	
	//$TASK RTC
	RTC_initialisation();
	
	//$TASK Accelerometer
	MMA7660init();
	
	//$TASK glcd
	/* Set the font */
	/* write "hello world" on display */
	
	glcd_tiny_set_font(Font5x7, 5, 7, GLCD_LCD_HEIGHT, GLCD_LCD_WIDTH);
	glcd_clear_buffer();
	glcd_tiny_draw_string(0, 0, "SPI & LCD Working!");
	glcd_write();
	
	
	/* cycle contrast: from 0 (brightest) to 63 (darkest) */
	
	/*
	delay_ms(1000);
	
	for(uint8_t contr = 0; contr <= 63; contr++){
		glcd_set_contrast(contr);
		sprintf(contrast_text, "%4d", contr);
		glcd_tiny_set_font(Font5x7, 5, 7, GLCD_LCD_HEIGHT, GLCD_LCD_WIDTH);
		glcd_clear_buffer();
		glcd_tiny_draw_string(0, 0, contrast_text);
		glcd_write();
		delay_ms(100);
	}
	
	glcd_set_contrast(30);
	*/
	
	
	while(1) {
		
		//$TASK ADC
		/* set contrast of display with ADC value from potentiometer 1 */
		pot_1_value_raw = ADC_GetConversionValue(ADC1);
		// normalize to be between 0 and 63
		
		contrast = getContrast(pot_1_value_raw);
		glcd_set_contrast(contrast);
		//$TASK Accelerometer
		
		MMA7660getAcceleration(&ax, &ay, &az);
		sprintf(text1, "x: %4.2f", ax);
		glcd_draw_string_xy(0, ROW2, text1);
		sprintf(text1, "y: %4.2f", ay);
		glcd_draw_string_xy(0, ROW3, text1);
		sprintf(text1, "z: %4.2f", az);
		glcd_draw_string_xy(0, ROW4, text1);
		
		
		// temperature
		
		tempRaw = I2C_Write_1_Read_2_byte(I2C1, LM75B_ADDR, LM75B_TEMP) >> 5;
		
		if (tempRaw & (1<<10))
		{
			tempRaw |= 0xfc00;
		}

		temp = (float) tempRaw * 0.125;
		
		sprintf(text1, "%3.1f", temp);
		
		glcd_draw_string_xy(60, ROW2, text1);
		
		// put it on the display
		glcd_write();
		
    /* If 100ms has been elapsed */
    if (TimeDisplay == 1)
    {
			/* get acceleration data */
      Display(RTC_GetCounter(),readTemperature(), ax, ay, az);
      TimeDisplay = 0;
    }
		delay_ms(100);
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
