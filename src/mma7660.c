/**
  ******************************************************************************
  * @file    MMA7660.c 
  * @author  rnm1
  * @version V1.0
  * @date    23.02.2016
  * @brief   MMA7660 3-Axis Orientation/Motion Detection Sensor library functions
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
#include "mma7660.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//$TASK MMA7669

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initialize MMA7660
  * @param  None
  * @retval None
  */
void MMA7660init(void)
{
	MMA7660setMode(MMA7660_STAND_BY);
	MMA7660setSampleRate(AUTO_SLEEP_64);
	MMA7660setMode(MMA7660_ACTIVE);
}

/**
  * @brief  set mode of MMA7660
	* @param  uint8_t mode: MMA7660_STAND_BY or MMA7660_ACTIVE
  * @retval None
  */
void MMA7660setMode(uint8_t mode)
{
	//$TASK MMA7660
	/*set mode by writing MMA7660_MODE and mode over I2C*/
	uint8_t data_to_send[2];
	
	/*
	B7   B6   B5   B4   B3   B2   B1   B0
	IAH  IPP  SCPS ASE  AWE  TON  -    MODE
	
	
	MODE: 0: standby      1: active
	TON: Test sfuff  0: as defined by mode, 1: test mode
	AWE: Autowakeup, 0: disabled, 1: enabled
	ASE: Autosleep,  0: disabled, 1: enabled
	SCPS: Prescaler  0: divide by 1, 1: divide by 16
	IPP: interrupt   0: Open Drain 1: Push-Pull
	IAH: 0: interrupt is active low, 1: interrupt is active high
	*/
	
	data_to_send[0] = MMA7660_MODE;
	data_to_send[1] = mode;
		
	I2C_Write_n_byte(I2C1, MMA7660_ADDR, 2, data_to_send);
}

/**
  * @brief  set samplerate of MMA7660
	* @param  uint8_t rate: AUTO_SLEEP_1 to AUTO_SLEEP_120 (120 sample per second)
  * @retval None
  */
void MMA7660setSampleRate(uint8_t rate)
{
	//$TASK MMA7660
	/*set sample rate by writing MMA7660_SR and rate over I2C*/
	
	I2C_Write_2_byte(I2C1, MMA7660_ADDR, MMA7660_SR, rate);
}

/**
  * @brief  get x,y and z-acceleration of MMA7660
	* @param  float *x, float *y, float *z: give x,y and z variable as reference
  * @retval None
  */
void MMA7660getAcceleration(float *x, float *y, float *z)
{
	uint8_t buffer[3] = {64, 64, 64};

	//$TASK MMA7660
	/* while alert bit is set: read all 3 data byte */
	
	while ( buffer[0] > 63 | buffer[1] > 63 | buffer[2] > 63) {
		I2C_Write_1_Read_n_byte(I2C1, MMA7660_ADDR, MMA7660_X, 3, buffer);
	}
	
	*x = (((int8_t)(buffer[0]<<2))/4)/MMA7660_SENSITIVITY;
	*y = (((int8_t)(buffer[1]<<2))/4)/MMA7660_SENSITIVITY;
	*z = (((int8_t)(buffer[2]<<2))/4)/MMA7660_SENSITIVITY;

	/* calculate accelerations */

}
