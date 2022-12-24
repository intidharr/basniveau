//usart_send_polling

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Private typedef -----------------------------------------------------------*/

char rcvBuffer[20];

char Char_rcv;
uint8_t charcount=0;

// Structures
GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;


/* Private functions ---------------------------------------------------------*/
void Delay(vu32 nCount);

int main(void)
{
/* ================  Configure the Periph Clocks ===================== */

  /* Enable GPIOx and AFIO clocks */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);

  /* Enable USART2 clocks */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	
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



/* ====================  USART2 configuration RX Mode======================*/
    /* USART2 configured as follow:
        - BaudRate = 9600 baud  
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
  USART_InitStructure.USART_Mode = USART_Mode_Rx;

  USART_Init(USART2, &USART_InitStructure);
  
  /* Enable the USARTx */
  USART_Cmd(USART2, ENABLE);
	
/*----------------------------------------------------------*/
	 // receive 20 chacarters and fill the rcvBufferA ARRAY
	 while (charcount<20){
		
		 while (USART_GetFlagStatus(USART2,USART_FLAG_RXNE)==RESET); //wait until USART2 RX Register is not Empty
			
		 rcvBuffer[charcount++] = USART_ReceiveData (USART2);  //read characte 
		 Delay(0xFFF); // 
		}
	
	 while(1){
		GPIO_SetBits (GPIOA, GPIO_Pin_5);
		Delay(0xFFFFF);
		GPIO_ResetBits (GPIOA, GPIO_Pin_5);
		Delay(0xFFFFF);
	 
		}//END MAIN

 }                

  
/******************** Function Name  : Delay**************************/
void Delay(vu32 nCount)

{  for(; nCount != 0; nCount--);}

