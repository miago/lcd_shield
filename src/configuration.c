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

void RCC_configuration(void)
{
	//$TASK SPI
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
	
	//$TASK RTC

	
	//$TASK ADC
	
	
	//$TASK I2C

}

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

	
	//$TASK I2C

}

void ADC_configuration(void)
{
	// ADC_InitTypeDef  ADC_InitStructure;
	
	//$TASK ADC
 
}

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

void I2C_configuration(void)
{
	// I2C_InitTypeDef  I2C_InitStructure;
	
	//$TASK I2C

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


