/**
  ******************************************************************************
  * @file     lm75b.h
	* @autor		rnm1
	* @version	V1.0
	* @date			23.02.2016
  * @brief    library file lm75b.c
  ******************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LM75B_H
#define __LM75B_H

/* Includes ------------------------------------------------------------------*/	
#include "stm32f10x.h"
#include "i2c.h"

#define LM75B_ADDR  0x90
#define LM75B_TEMP  0x00 //Temperature register (RO)
#define LM75B_CONF  0x00 //Configuration register (R/W)
#define LM75B_THYST 0x00 //Overtemperature shutdown threshold register (R/W)
#define LM75B_TOS   0x00 //Hysteresis register (R/W)

/* Private defines------------------------------------------------------------*/
/* Prototypes ------------------------------------------------------------------*/
float readTemperature(void);

#endif /*__LM75B_H */

/********** (C) COPYRIGHT BFH TI Bienne - Mechatronics Lab *****END OF FILE****/
