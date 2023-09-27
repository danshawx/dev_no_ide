#ifndef DRV_UART_H
#define DRV_UART_H

#include "stdint.h"
#include "queue.h"

#define CONFIG_USARTDMA_TX_MAXLEN    (10)
#define CONFIG_USARTDMA_RX_MAXLEN    (20)

#define CONFIG_USART_TX_MAXLEN       (30)
#define CONFIG_USART_RX_MAXLEN       (30)

#define CONFIG_USART_TXQUE_MAXLEN     (CONFIG_USART_TX_MAXLEN * 3)
#define CONFIG_USART_RXQUE_MAXLEN     (CONFIG_USART_RX_MAXLEN * 2)



extern uint8_t g_txdma_buf[CONFIG_USARTDMA_TX_MAXLEN];
extern uint8_t g_rxdma_buf[CONFIG_USARTDMA_RX_MAXLEN];

extern uint8_t g_tx_buf[CONFIG_USART_TX_MAXLEN];
extern uint8_t g_rx_buf[CONFIG_USART_RX_MAXLEN];

extern decirquedate_t *p_usarttxque;
extern decirquedate_t *p_usartrxque;


void comm_dmauconf_hal(void);
void comm_bufinit_hal(void);
// void comm_tx_hal(uint8_t *p_txbuf, uint8_t tx_len);
//void comm_dma_usart_handler(void);
void comm_dma_chan2_handler(void);
void comm_dma_chan1_handler(void);
// void comm_usart1_handler(void);
void comm_usart2_handler(void);

// void usart2_init(void);

#endif
