/**
  ******************************************************************************
  * @file    lm75b.c 
  * @author  rnm1
  * @version V1.0
  * @date    23.02.2016
  * @brief   LM75B temperature library functions
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 BFH TI Bienne - rnm1 </center></h2>
  *
  ******************************************************************************
	* @information
	*
	*
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "lm75b.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//$TASK LM75B

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Reads the temperature from LM75B over I2C
  * @param  None
  * @retval Temperature
  */
float readTemperature(void)
{
	int16_t tmp;
	
	//$TASK LM75B

	
	return (float)tmp;
}

/********** (C) COPYRIGHT BFH TI Bienne - Mechatronics Lab *****END OF FILE****/
