/**
 ******************************************************************************
 * @file    USB_Device/HID_Standalone/Src/main.c
 * @author  MCD Application Team
 * @version V1.2.0
 * @date    30-December-2016
 * @brief   USB device HID demo main file
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics International N.V.
 * All rights reserved.</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted, provided that the following conditions are met:
 *
 * 1. Redistribution of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of other
 *    contributors to this software may be used to endorse or promote products
 *    derived from this software without specific written permission.
 * 4. This software, including modifications and/or derivative works of this
 *    software, must execute solely and exclusively on microcontroller or
 *    microprocessor devices manufactured by or for STMicroelectronics.
 * 5. Redistribution and use of this software other than as permitted under
 *    this license is void and will automatically terminate your rights under
 *    this license.
 *
 * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
 * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
 * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <math.h>

/* Private typedef -----------------------------------------------------------*/
typedef struct {
	int32_t x;
	int32_t y;
} coordinate_t;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define XMAX 480
#define YMAX 272
/* Private variables ---------------------------------------------------------*/
TS_StateTypeDef ts_state;
TS_StateTypeDef *ts_state_ptr = &ts_state;
TS_StateTypeDef ts_state_prev;
TS_StateTypeDef *ts_state_prev_ptr = &ts_state_prev;
uint8_t finger_down = 0;
uint8_t click_event = 0;
USBD_HandleTypeDef USBD_Device;
uint8_t HID_Buffer[4];
uint16_t radius;
uint32_t prev_color;

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void Error_Handler(void);
static void CPU_CACHE_Enable(void);
static void MPU_Config(void);
/* Private functions ---------------------------------------------------------*/
void draw_menu(uint32_t color, uint16_t radius);
void draw_sizes(uint32_t color);
void draw_colors(uint16_t radius);
void redraw_sizes(uint32_t color);
void redraw_colors(uint16_t radius);
void draw_circles();
/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
int main(void) {
	/* Enable the CPU Cache */
	CPU_CACHE_Enable();

	/* STM32F7xx HAL library initialization:
	 - Configure the Flash ART accelerator on ITCM interface
	 - Configure the Systick to generate an interrupt each 1 msec
	 - Set NVIC Group Priority to 4
	 - Low Level Initialization
	 */
	HAL_Init();
	MPU_Config();
	/* Configure the System clock to have a frequency of 216 MHz */
	SystemClock_Config();

	/* Configure LED1 */
	BSP_LED_Init(LED1);

	/* Init Device Library */
	USBD_Init(&USBD_Device, &HID_Desc, 0);

	/* Add Supported Class */
	USBD_RegisterClass(&USBD_Device, USBD_HID_CLASS);

	/* Start Device Process */
	USBD_Start(&USBD_Device);
	
	// Touch screen init
	BSP_TS_Init(XMAX, YMAX);

	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);

	// This byte contains the button states
	// 0b00000001 - the left mouse button is pressed
	// 0b00000010 - the middle mouse button is pressed
	// 0b00000100 - the right mouse button is pressed
	HID_Buffer[0] = 0;
	// This byte contains the x realative movement
	HID_Buffer[1] = 0;
	// This byte contains the y realative movement
	HID_Buffer[2] = 0;

	//LCD inits
	BSP_LCD_Init();
	BSP_LCD_LayerDefaultInit(0, LCD_FB_START_ADDRESS);
	BSP_LCD_LayerDefaultInit(1, LCD_FB_START_ADDRESS+(BSP_LCD_GetXSize()*BSP_LCD_GetYSize()*4));
	BSP_LCD_DisplayOn();
	BSP_LCD_SelectLayer(0);
	BSP_LCD_Clear(0xFF707020);
	radius = 20;
	draw_menu(LCD_COLOR_RED, radius);

	while (1) {
		if(BSP_PB_GetState(BUTTON_KEY)) {
			BSP_LCD_SelectLayer(0);
			BSP_LCD_Clear(0xFF707020);
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
			BSP_LCD_DrawVLine(420, 0, 272);
			BSP_LCD_DrawHLine(420, 131, 60);
			BSP_LCD_DrawVLine(20, 0, 20);
			BSP_LCD_DrawHLine(0, 20, 20);
		}
		BSP_TS_GetState(ts_state_ptr);
		if (ts_state.touchDetected) {
			if (ts_state_ptr->touchX[0] < 420 - radius	&&
				ts_state_ptr->touchX[0] > radius		&&
				ts_state_ptr->touchY[0] < 272 - radius	&&
				ts_state_ptr->touchY[0] > radius) {
				BSP_LCD_SelectLayer(0);
				BSP_LCD_FillCircle(ts_state_ptr->touchX[0], ts_state_ptr->touchY[0], radius);
			}

			if (ts_state_ptr->touchX[0] < 470	&&
				ts_state_ptr->touchX[0] > 434	&&
				ts_state_ptr->touchY[0] < 264	&&
				ts_state_ptr->touchY[0] > 228) {
				redraw_sizes(LCD_COLOR_BLUE);
			}

			if (ts_state_ptr->touchX[0] < 470	&&
				ts_state_ptr->touchX[0] > 434	&&
				ts_state_ptr->touchY[0] < 218	&&
				ts_state_ptr->touchY[0] > 186) {
				redraw_sizes(LCD_COLOR_GREEN);
			}

			if (ts_state_ptr->touchX[0] < 470	&&
				ts_state_ptr->touchX[0] > 434	&&
				ts_state_ptr->touchY[0] < 174	&&
				ts_state_ptr->touchY[0] > 142) {
				redraw_sizes(LCD_COLOR_RED);
			}

			if (ts_state_ptr->touchX[0] < 470	&&
				ts_state_ptr->touchX[0] > 434	&&
				ts_state_ptr->touchY[0] < 116	&&
				ts_state_ptr->touchY[0] > 94) {
				radius = 20;
				redraw_colors(radius);
			}

			if (ts_state_ptr->touchX[0] < 470	&&
				ts_state_ptr->touchX[0] > 434	&&
				ts_state_ptr->touchY[0] < 70	&&
				ts_state_ptr->touchY[0] > 42) {
				radius = 15;
				redraw_colors(radius);
			}

			if (ts_state_ptr->touchX[0] < 470	&&
				ts_state_ptr->touchX[0] > 434	&&
				ts_state_ptr->touchY[0] < 30	&&
				ts_state_ptr->touchY[0] > 5) {
				radius = 10;
				redraw_colors(radius);
			}

			if (ts_state_ptr->touchX[0] < 20	&&
				ts_state_ptr->touchX[0] > 0		&&
				ts_state_ptr->touchY[0] < 20	&&
				ts_state_ptr->touchY[0] > 0) {
				redraw_sizes(0xFF707020);
				draw_circles();

			}



		}
	}//while
}//main

void draw_menu(uint32_t color, uint16_t radius)
{
	BSP_LCD_Clear(0xFF707020);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DrawVLine(420, 0, 272);
	BSP_LCD_DrawHLine(420, 131, 60);
	BSP_LCD_DrawVLine(20, 0, 20);
	BSP_LCD_DrawHLine(0, 20, 20);
	BSP_LCD_SelectLayer(1);
	BSP_LCD_Clear(0x00707020);
	draw_sizes(color);
	draw_colors(radius);
	BSP_LCD_SelectLayer(0);
	BSP_LCD_SetTextColor(color);
}

void draw_circles()
{
	BSP_LCD_SelectLayer(1);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_DrawCircle(452, 100, 20);
	BSP_LCD_DrawCircle(452, 56, 15);
	BSP_LCD_DrawCircle(452, 20, 10);
}

void draw_sizes(uint32_t color)
{
	BSP_LCD_SetTextColor(color);
	BSP_LCD_FillCircle(452, 100, 20);
	BSP_LCD_FillCircle(452, 56, 15);
	BSP_LCD_FillCircle(452, 20, 10);
}

void redraw_sizes(uint32_t color)
{
	BSP_LCD_SelectLayer(1);
	BSP_LCD_Clear(0x00707020);
	draw_sizes(color);
	draw_colors(radius);
	BSP_LCD_SelectLayer(0);
	BSP_LCD_SetTextColor(color);
	prev_color = color;
}

void draw_colors(uint16_t radius)
{
	BSP_LCD_SetTextColor(LCD_COLOR_RED);
	BSP_LCD_FillCircle(452, 158, radius);
	BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
	BSP_LCD_FillCircle(452, 202, radius);
	BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
	BSP_LCD_FillCircle(452, 246, radius);
}

void redraw_colors(uint16_t radius)
{
	BSP_LCD_SelectLayer(1);
	BSP_LCD_Clear(0x00707020);
	BSP_LCD_FillCircle(452, 100, 20);
	BSP_LCD_FillCircle(452, 56, 15);
	BSP_LCD_FillCircle(452, 20, 10);
	draw_colors(radius);
	BSP_LCD_SetTextColor(prev_color);
}
/**
 * @brief This function provides accurate delay (in milliseconds) based
 *        on SysTick counter flag.
 * @note This function is declared as __weak to be overwritten in case of other
 *       implementations in user file.
 * @param Delay: specifies the delay time length, in milliseconds.
 * @retval None
 */

void HAL_Delay(__IO uint32_t Delay) {
	while (Delay) {
		if (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) {
			Delay--;
		}
	}
}

/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follow :
 *            System Clock source            = PLL (HSE)
 *            SYSCLK(Hz)                     = 216000000
 *            HCLK(Hz)                       = 216000000
 *            AHB Prescaler                  = 1
 *            APB1 Prescaler                 = 4
 *            APB2 Prescaler                 = 2
 *            HSE Frequency(Hz)              = 25000000
 *            PLL_M                          = 25
 *            PLL_N                          = 432
 *            PLL_P                          = 2
 *            VDD(V)                         = 3.3
 *            Main regulator output voltage  = Scale1 mode
 *            Flash Latency(WS)              = 7
 * @param  None
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	/* Enable HSE Oscillator and activate PLL with HSE as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 25;
	RCC_OscInitStruct.PLL.PLLN = 432;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 9;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/* Activate the OverDrive to reach the 216 Mhz Frequency */
	if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
		Error_Handler();
	}

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
	 clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
	RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK) {
		Error_Handler();
	}
}

static void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct;

  /* Disable the MPU */
  HAL_MPU_Disable();

  /* Configure the MPU attributes as WT for SRAM */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = 0x20010000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_256KB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /* Enable the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
void Error_Handler(void) {
	/* User may add here some code to deal with this error */
	while (1) {
	}
}

/**
 * @brief  CPU L1-Cache enable.
 * @param  None
 * @retval None
 */
void CPU_CACHE_Enable(void) {
	/* Enable I-Cache */
	SCB_EnableICache();

	/* Enable D-Cache */
	SCB_EnableDCache();
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
