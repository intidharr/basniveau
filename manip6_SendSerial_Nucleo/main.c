//usart_send_polling

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Private typedef -----------------------------------------------------------*/

char password[]="ABCDEFGHIJ0123456789";
char password2[]="abcdefghij9876543210";

char Char_tosend;
uint8_t charcount=0;

// Structures
GPIO_InitTypeDef GPIO_InitStructure;
EXTI_InitTypeDef EXTI_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;
USART_InitTypeDef USART_InitStructure;



/* Private functions ---------------------------------------------------------*/
void Delay(vu32 nCount);
uint8_t stringCompare(char str1[],char str2[], uint8_t StrLength);

int main(void)
{
/* ================  Configure the Periph Clocks ===================== */

  /* Enable GPIOx and AFIO clocks */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);

  /* Enable USART2 clocks */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	/* Enable DMA1 clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	
  /* ================  Configure the GPIO ports ===================== */

	  /* Configure Pc.13 as Input Floating */
	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;

  GPIO_Init(GPIOC, &GPIO_InitStructure);
 
	
    /*Configure PA5 as Output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* Configure USART2 Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Configure USART2 Rx as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);


/*====================  EXTI0 Configuration ======================== */
  
      /* Connect Button EXTI Line to Button GPIO Pin */
     GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource13);

    /* Configure Button EXTI line */
   EXTI_InitStructure.EXTI_Line = EXTI_Line13;
   EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
   EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; 
   EXTI_InitStructure.EXTI_LineCmd = ENABLE;
   EXTI_Init(&EXTI_InitStructure);


   /* Enable and set Button EXTI Interrupt to the lowest priority */

   NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
    



/* ====================  USART2 configuration TX Mode======================*/
    /* USART2 configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No ;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Tx;

  USART_Init(USART2, &USART_InitStructure);
  
  /* Enable the USARTx */
  USART_Cmd(USART2, ENABLE);
	
/*----------------------------------------------------------*/

//send the true password 
	while (charcount<20)
{
	while (USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET); //wait until USART2 TX Register is Empty
			Char_tosend = password[charcount] ;
			USART_SendData(USART2,password[charcount]);  //Send Data
			charcount++;
			Delay(0xFFFFF); // Wait before sending next char
}

 while(1)
 {
GPIO_SetBits (GPIOA, GPIO_Pin_5);
	 Delay(0xFFFFF);
GPIO_ResetBits (GPIOA, GPIO_Pin_5);
	 Delay(0xFFFFF);

	 
}//END MAIN

   }                

uint8_t stringCompare(char str1[],char str2[], uint8_t StrLength){
    int i=0;
   
    while(str1[i]!='\0' && str2[i]!='\0' && i<StrLength){
         if(str1[i]!=str2[i]){
             return 0;             
         }
         i++;
    }
         return 1;

}
  
/******************** Function Name  : Delay**************************/
void Delay(vu32 nCount)

{  for(; nCount != 0; nCount--);}

