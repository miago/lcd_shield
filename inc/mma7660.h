/**
  ******************************************************************************
  * @file     mma7660.h
	* @autor		rnm1
	* @version	V1.0
	* @date			22.02.2016
  * @brief    library file display.c
  ******************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MMA7660_H
#define __MMA7660_H


#define MMA7660_ADDR 0x98 // 0x96 ?
#define MMA7660_SENSITIVITY 22.13 // g^-1, comes from 32/1.4 g^-1

#define MMA7660_X 0x00
#define MMA7660_Y 0x01
#define MMA7660_Z 0x02
#define MMA7660_TILT 0x03
#define MMA7660_SRST 0x04
#define MMA7660_SPCNT 0x05
#define MMA7660_INTSU 0x06
#define MMA7660_MODE 0x07
#define MMA7660_STAND_BY 0x00 // (?)
#define MMA7660_ACTIVE 0x01 // (?)
#define MMA7660_SR 0x00 // 08 (?)//sample rate register
#define AUTO_SLEEP_120 0x00//120 sample per second
#define AUTO_SLEEP_64 0x01
#define AUTO_SLEEP_32 0x02
#define AUTO_SLEEP_16 0x03
#define AUTO_SLEEP_8 0x04
#define AUTO_SLEEP_4 0x05
#define AUTO_SLEEP_2 0x06
#define AUTO_SLEEP_1 0x07
#define MMA7660_PDET 0x09
#define MMA7660_PD 0x0A

/* Includes ------------------------------------------------------------------*/	
#include "stm32f10x.h"
#include "i2c.h"

/* Private defines------------------------------------------------------------*/
/* Prototypes ------------------------------------------------------------------*/
void MMA7660init(void);
void MMA7660setMode(uint8_t mode);
void MMA7660setSampleRate(uint8_t rate);
void MMA7660getAcceleration(float *x, float *y, float *z);

#endif /*__MMA7660_H */

/********** (C) COPYRIGHT BFH TI Bienne - Mechatronics Lab *****END OF FILE****/
