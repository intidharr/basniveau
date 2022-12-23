// Interrupts EXTI Project

/**
 ******************************************************************************
 * @file    EXTI/stm32f10x_it.c
 * @author  MCD Application Team
 * @version V1.0.0
 * @date    15/09/2018
 * @brief   Main Interrupt Service Routines.
 *          This file provides template for all exceptions handler and peripherals
 *          interrupt service routine.
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"

void Delay(vu32 nCount);
uint8_t stringCompare(char str1[], char str2[], uint8_t StrLength);

/** @addtogroup Examples
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
 * @brief  This function handles NMI exception.
 * @param  None
 * @retval None
 */
void NMI_Handler(void)
{
}

/**
 * @brief  This function handles Hard Fault exception.
 * @param  None
 * @retval None
 */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
 * @brief  This function handles Memory Manage exception.
 * @param  None
 * @retval None
 */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
 * @brief  This function handles Bus Fault exception.
 * @param  None
 * @retval None
 */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
 * @brief  This function handles Usage Fault exception.
 * @param  None
 * @retval None
 */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
 * @brief  This function handles SVCall exception.
 * @param  None
 * @retval None
 */
void SVC_Handler(void)
{
}

/**
 * @brief  This function handles Debug Monitor exception.
 * @param  None
 * @retval None
 */
void DebugMon_Handler(void)
{
}

/**
 * @brief  This function handles PendSV_Handler exception.
 * @param  None
 * @retval None
 */
void PendSV_Handler(void)
{
}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*            STM32F10x Peripherals Interrupt Handlers                        */
/******************************************************************************/

/**
 * @brief  This function handles DMA interrupt requests.
 */

int i;
extern char Receive_Buffer[20];
extern char Compare_Buffer[20];

void DMA1_Channel5_IRQHandler(void)
{
  /* Test on DMAx Channely Transfer Complete interrupt */
  if (DMA_GetITStatus(DMA1_IT_TC5))
  {
    /* Code a ajouter pour assurer le fonctionnement désiré */

    if (stringCompare(Receive_Buffer, Compare_Buffer, 20))
    {
      GPIO_SetBits(GPIOA, GPIO_Pin_5);
      USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
    }
    else
    {
      GPIO_SetBits(GPIOA, GPIO_Pin_5);
      Delay(0xFFFFF);
      GPIO_ResetBits(GPIOA, GPIO_Pin_5);
      Delay(0xFFFFF);
      GPIO_SetBits(GPIOA, GPIO_Pin_5);
      Delay(0xFFFFF);
      GPIO_ResetBits(GPIOA, GPIO_Pin_5);
      Delay(0xFFFFF);
    }

    /* Clear DMAx Channely TC interrupt pending bit */
    DMA_ClearITPendingBit(DMA1_IT_TC5);
  }
}

/**
 * @brief  This function handles USART2 TX interrupt requests.
 * @param  None
 * @retval None
 */

int txcount = 0;
extern char Transmit_Buffer[];

void USART2_IRQHandler(void)
{
  // Test on USART2 TX Interrupt
  if (USART_GetITStatus(USART2, USART_IT_TXE))
  {
    // Code a ajouter pour assurer le fonctionnement désiré
    if (txcount < 8)
    {
      USART_SendData(USART2, Transmit_Buffer[txcount]);
      txcount++;
    }
    else
    {
      USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
    }
  }
}