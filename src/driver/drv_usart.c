
#include "drv_usart.h"

#include "main.h"

uint8_t g_txdma_buf[CONFIG_USARTDMA_TX_MAXLEN] = {0};
uint8_t g_rxdma_buf[CONFIG_USARTDMA_RX_MAXLEN] = {0};

uint8_t g_tx_buf[CONFIG_USART_TX_MAXLEN] = {0};
uint8_t g_rx_buf[CONFIG_USART_RX_MAXLEN] = {0};

decirquedate_t *p_usarttxque = NULL;
decirquedate_t *p_usartrxque = NULL;

void comm_bufinit_hal(void)
{
    p_usarttxque = decirque_init(CONFIG_USART_TXQUE_MAXLEN);
    p_usartrxque = decirque_init(CONFIG_USART_RXQUE_MAXLEN);
}

void comm_dmauconf_hal(void)
{
    /* (3) Configure the DMA functional parameters for transmission */
    LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_2,
                           (uint32_t)g_txdma_buf,
                           LL_USART_DMA_GetRegAddr(USART2, LL_USART_DMA_REG_DATA_TRANSMIT),
                           LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_CHANNEL_2));
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_2, CONFIG_USARTDMA_TX_MAXLEN);

    /* (4) Configure the DMA functional parameters for reception */

    LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_1,
                           LL_USART_DMA_GetRegAddr(USART2, LL_USART_DMA_REG_DATA_RECEIVE),
                           (uint32_t)g_rxdma_buf,
                           LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_CHANNEL_1));
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, CONFIG_USARTDMA_RX_MAXLEN);

    /* (5) Enable DMA transfer complete/error interrupts  */
    //LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_2);
    LL_DMA_EnableIT_TE(DMA1, LL_DMA_CHANNEL_2);
    //LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_1);
    LL_DMA_EnableIT_TE(DMA1, LL_DMA_CHANNEL_1);

    LL_USART_EnableDMAReq_RX(USART2);
    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);

    LL_USART_EnableIT_IDLE(USART2);

}

void comm_tx_hal(uint8_t *p_txbuf, uint8_t tx_len)
{
    uint8_t tx_dmalen = 0;

    decirque_push(p_usarttxque, p_txbuf, tx_len);
    if (!LL_DMA_IsEnabledChannel(DMA1, LL_DMA_CHANNEL_2))
    {
        tx_dmalen = (p_usarttxque->size < CONFIG_USARTDMA_TX_MAXLEN) ? p_usarttxque->size : CONFIG_USARTDMA_TX_MAXLEN;
        if (1 == decirque_pop(p_usarttxque, g_txdma_buf, tx_dmalen))
        {
        	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_2, tx_dmalen);
        	LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_2);
            LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_2);
            LL_USART_EnableDMAReq_TX(USART2);
        }
    }
}


//******************** handler ***********************
static void dma1_receivecomplete_callback(void)
{
	uint8_t rx_dmalen = 0;

	//LL_DMA_DisableIT_TC(DMA1, LL_DMA_CHANNEL_1);
	//LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_1);
	LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_1);

	rx_dmalen = CONFIG_USARTDMA_RX_MAXLEN - LL_DMA_GetDataLength(DMA1, LL_DMA_CHANNEL_1);
	decirque_push(p_usartrxque, g_rxdma_buf, rx_dmalen);

	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, CONFIG_USARTDMA_RX_MAXLEN);

	//LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_1);
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
}

void comm_dma_chan2_handler(void)
{
    if(LL_DMA_IsActiveFlag_TC2(DMA1))
    {
        LL_DMA_ClearFlag_GI2(DMA1);
        /* Call function Transmission complete Callback */
        //DMA1_TransmitComplete_Callback();
        LL_USART_EnableIT_TC(USART2);
    }
    else if(LL_DMA_IsActiveFlag_TE2(DMA1))
    {
        /* Call Error function */
        //USART_TransferError_Callback();
    	LL_DMA_ClearFlag_TE2(DMA1);
    }
//    if(LL_DMA_IsActiveFlag_TC3(DMA1))
//    {
//        LL_DMA_ClearFlag_GI3(DMA1);
//        /* Call function Reception complete Callback */
//        //DMA1_ReceiveComplete_Callback();
//    }
//    else if(LL_DMA_IsActiveFlag_TE3(DMA1))
//    {
//    	LL_DMA_ClearFlag_TE3(DMA1);
//        /* Call Error function */
//        //USART_TransferError_Callback();
//    }
}


void comm_dma_chan1_handler(void)
{
//    if(LL_DMA_IsActiveFlag_TC2(DMA1))
//    {
//        LL_DMA_ClearFlag_GI2(DMA1);
//        /* Call function Transmission complete Callback */
//        //DMA1_TransmitComplete_Callback();
//        LL_USART_EnableIT_TC(USART2);
//    }
//    else if(LL_DMA_IsActiveFlag_TE2(DMA1))
//    {
//        /* Call Error function */
//        //USART_TransferError_Callback();
//    	LL_DMA_ClearFlag_TE2(DMA1);
//    }
    if(LL_DMA_IsActiveFlag_TC3(DMA1))
    {
        LL_DMA_ClearFlag_GI3(DMA1);
        /* Call function Reception complete Callback */
        //DMA1_ReceiveComplete_Callback();
    }
    else if(LL_DMA_IsActiveFlag_TE3(DMA1))
    {
    	LL_DMA_ClearFlag_TE3(DMA1);
        /* Call Error function */
        //USART_TransferError_Callback();
    }
}

void comm_usart2_tx_handler(void)
{
	 uint8_t tx_dmalen = 0;

	if (is_decirqueempty(p_usarttxque))
	{
		LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_2);
	}
	else
	{
		tx_dmalen = (p_usarttxque->size < CONFIG_USARTDMA_TX_MAXLEN) ? p_usarttxque->size : CONFIG_USARTDMA_TX_MAXLEN;
		if (1 == decirque_pop(p_usarttxque, g_txdma_buf, tx_dmalen))
		{
			LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_2);
			LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_2, tx_dmalen);
			LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_2);
			//LL_USART_EnableDMAReq_TX(USART2);
		}
	}
}

void comm_usart2_handler(void)
{
	if (LL_USART_IsActiveFlag_TC(USART2))
	{
		LL_USART_ClearFlag_TC(USART2);
		LL_USART_DisableIT_TC(USART2);
		comm_usart2_tx_handler();
	}
	if (LL_USART_IsActiveFlag_IDLE(USART2))
	{
		LL_USART_ClearFlag_IDLE(USART2);
		LL_USART_DisableIT_IDLE(USART2);
		dma1_receivecomplete_callback();
		LL_USART_EnableIT_IDLE(USART2);
	}
}


void usart2_config(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  LL_USART_InitTypeDef USART_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the peripherals clocks
  */
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    // Error_Handler();
  }

  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);

  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
  /**USART2 GPIO Configuration
  PA2   ------> USART2_TX
  PA3   ------> USART2_RX
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_2;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USART2 DMA Init */

  /* USART2_RX Init */
  LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_1, LL_DMAMUX_REQ_USART2_RX);

  LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_1, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);

  LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PRIORITY_LOW);

  LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MODE_NORMAL);

  LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PERIPH_NOINCREMENT);

  LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MEMORY_INCREMENT);

  LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PDATAALIGN_BYTE);

  LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MDATAALIGN_BYTE);

  /* USART2_TX Init */
  LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_2, LL_DMAMUX_REQ_USART2_TX);

  LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_2, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);

  LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_2, LL_DMA_PRIORITY_LOW);

  LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MODE_NORMAL);

  LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_2, LL_DMA_PERIPH_NOINCREMENT);

  LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MEMORY_INCREMENT);

  LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_2, LL_DMA_PDATAALIGN_BYTE);

  LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MDATAALIGN_BYTE);

  /* USART2 interrupt Init */
  NVIC_SetPriority(USART2_LPUART2_IRQn, 0);
  NVIC_EnableIRQ(USART2_LPUART2_IRQn);

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  USART_InitStruct.PrescalerValue = LL_USART_PRESCALER_DIV1;
  USART_InitStruct.BaudRate = 115200;
  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
  LL_USART_Init(USART2, &USART_InitStruct);
  LL_USART_SetTXFIFOThreshold(USART2, LL_USART_FIFOTHRESHOLD_1_8);
  LL_USART_SetRXFIFOThreshold(USART2, LL_USART_FIFOTHRESHOLD_1_8);
  LL_USART_DisableFIFO(USART2);
  LL_USART_ConfigAsyncMode(USART2);

  /* USER CODE BEGIN WKUPType USART2 */

  /* USER CODE END WKUPType USART2 */

  LL_USART_Enable(USART2);

  /* Polling USART2 initialisation */
  while((!(LL_USART_IsActiveFlag_TEACK(USART2))) || (!(LL_USART_IsActiveFlag_REACK(USART2))))
  {
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

int usart2_init(void)
{
    comm_bufinit_hal();
    usart2_config();

    return 0;
}

SYS_INIT(usart2_init, PRE_KERNEL_1, CONFIG_DRV_USART_INIT_PRIO);
