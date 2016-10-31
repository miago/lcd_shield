/**
  ******************************************************************************
  * @file    configuration.c 
  * @author  rnm1
  * @version V1.0
  * @date    22.02.2016
  * @brief   Setup Hardware
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
#include "configuration.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Configure the Clocks
  * @param  None
  * @retval None
  */
void RCC_configuration(void)
{
	//$TASK SPI
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
	
	//$TASK RTC

	
	//$TASK ADC
	// for POT1, attached on A0 -> PA0 on NUCLEO-F103RB -> ADC12_IN0
	// APRB2: Peripheral Bus 2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	
	//$TASK I2C
	// SDA connected to PB8
	// SCL connected to PB9
	// GPIO B is already clocked
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

}

/**
  * @brief  Configure the used GPIOs
  * @param  None
  * @retval None
  */
void GPIO_configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	//$TASK SPI
	
	/* Set up GPIO for SPI pins (SCK PA5, MOSI PA7) */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	/* GPIO_Mode_AF_PP means Alternate Function Push Pull */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* Set up GPIO for SPI pin (SS PB6) */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOB, & GPIO_InitStructure);	
	/* disable spi slave, 1 means disables */
	GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_SET);
	
	/* Set up GPIO for Display (RST PA6) */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	/* Drive reset pin high: reset display */
	GPIO_WriteBit(GPIOA, GPIO_Pin_6, Bit_SET);
	
	/* Set up GPIO for Display (A0 PA8), selects instruction/data*/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	
	//$TASK ADC
	/* set pin PA0 as an analog input */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//$TASK I2C
	// SCL (PB8)and SDA (PB9) are altrenate functions, remapped
	GPIO_PinRemapConfig(GPIO_Remap_I2C1, ENABLE);
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
  * @brief  Configure the ADC, used to read the potentiometers
  * @param  None
  * @retval None
  */
void ADC_configuration(void)
{
	ADC_InitTypeDef  ADC_InitStructure;
	//$TASK ADC
	
	// divide clock: 72/6 = 12 MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	ADC_DeInit(ADC1);
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;  
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; 
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 1;
	
	ADC_Init(ADC1, &ADC_InitStructure);
 
	ADC_Cmd(ADC1, ENABLE);
	
	/* CALIBRATION OF ADC */
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
	
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1,  ADC_SampleTime_239Cycles5);
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

/**
  * @brief  Configure the SPI interface, used to comunicate with the LCD.
  * @param  None
  * @retval None
  */
void SPI_configuration(void)
{
	SPI_InitTypeDef SPI_InitStructure;
	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	
	SPI_Init(SPI1, &SPI_InitStructure);
	
	//SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_RXNE, ENABLE);
	
	SPI_Cmd(SPI1, ENABLE);
}

/**
  * @brief  I2C configuration, used to communicate with the accelerometer
  * @param  None
  * @retval None
  */
void I2C_configuration(void)
{
	
	//I2C_InitTypeDef I2C_InitStructure;
	
	
	
	//$TASK I2C
	//I2C_InitStructure.I2C_ClockSpeed = 400;          
	/*!< Specifies the clock frequency.
                                         This parameter must be set to a value lower than 400kHz */

  //I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;                
	/*!< Specifies the I2C mode.
                                         This parameter can be a value of @ref I2C_mode */

  //I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;           
	/*!< Specifies the I2C fast mode duty cycle.
                                         This parameter can be a value of @ref I2C_duty_cycle_in_fast_mode */

  //I2C_InitStructure.I2C_OwnAddress1 = 0x3c;         
	/*!< Specifies the first device own address.
                                         This parameter can be a 7-bit or 10-bit address. */

  //I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;                 
	/*!< Enables or disables the acknowledgement.
                                         This parameter can be a value of @ref I2C_acknowledgement */

	//I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; 
	/*!< Specifies if 7-bit or 10-bit address is acknowledged.
                                         This parameter can be a value of @ref I2C_acknowledged_address */
}

void RTC_configuration(void)
{	
	//$TASK RTC

}

void NVIC_configuration(void)
{
  // NVIC_InitTypeDef NVIC_InitStructure;

  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	//$TASK RTC

}


