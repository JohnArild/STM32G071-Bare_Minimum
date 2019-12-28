/*
 * main.cpp
 *
 *  Created on: Dec 28, 2019
 *      Author: John Arild Lolland
 *     License: BSD-3, see file LICENSE
 */

#include "stm32g071xx.h"

void waitLoop(int loops); //Prototype for a simple delay loop

int main()
{
	// Setup clocks for NUCLEO-G071 to run at 64 MHz.
	// This is optional, the MCU starts up using internal 16 MHz clock.
	FLASH->ACR |= FLASH_ACR_LATENCY_1; // Two wait states for 64 MHz (1 for 48MHz and 0 for 16MHz)
	RCC->CR |= RCC_CR_HSION; //Enable HSI
	while(!((RCC->CR & RCC_CR_HSIRDY)== RCC_CR_HSIRDY)){;} // Wait for HSE to become ready
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSI; // Set PLL input clock source to HSI
	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLM); // Set Div M of the PLL input clock divide to /1
	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLN); // Setting PLLN to 0 as it is not 0 from reset.
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_3; // Set PLL frequency multiplication factor N to 8
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLR_0; // Set PLL VCO division factor R to /2
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLREN; // PLLRCLK clock output enable
	RCC->CR |= RCC_CR_PLLON; // PLL enable
	while(!((RCC->CR & RCC_CR_PLLRDY)== RCC_CR_PLLRDY)){;} // Wait for PLL to become ready
	RCC->CFGR |= RCC_CFGR_SW_1; // Set System clock switch to PLLRCLK
	while(!((RCC->CFGR & RCC_CFGR_SWS)== RCC_CFGR_SWS_1)){;} // Wait for System clock switch status to return PLLRCLK

	// Setup GPIO
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN; // Enable GPIO A
	GPIOA->MODER &= ~(GPIO_MODER_MODE5); //Reset MODER as default is Analog
	GPIOA->MODER |= GPIO_MODER_MODE5_0; // Set GPIOA Pin 5 as Output
	GPIOA->OTYPER &= ~(GPIO_OTYPER_OT5_Msk); // Set GPIO Pin 5 Output type as push-pull (optional)
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED5_0; // Set GPIOA Pin 5 Output as Low Speed
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD5); // Set GPIOA Pin5 as no Pull-up/Pull-down (optional)

	while(1)
	{
		GPIOA->BSRR |= GPIO_BSRR_BS5; //Turn off PA5
		waitLoop(0xFE);
		GPIOA->BSRR |= GPIO_BSRR_BR5; //Turn on PA5
		waitLoop(0xFE);
	}
}

void waitLoop(int loops)
{
	for(int i = 0; i < loops; i++)
	{
		for(uint32_t j = 0; j < 0xFFF; j++)
		{
			;
		}
	}
}
