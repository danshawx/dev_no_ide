#ifndef DRV_CONFIG_H
#define DRV_CONFIG_H

#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_utils.h"
#include "stm32g0xx_ll_system.h"
#include "stm32g0xx_ll_utils.h"
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_dma.h"
#include "stm32g0xx_ll_usart.h"

#include "stm32g0xx_hal_rcc.h"
#include "stm32g0xx_hal_rcc_ex.h"

#include "drv_gpio.h"
#include "drv_sysclock.h"

#include "init.h"


#define CONFIG_DRV_SYSCLOCK_INIT_PRIO    (1)

#define CONFIG_DRV_GPIO_INIT_PRIO    (20)
#define CONFIG_DRV_USART_INIT_PRIO    (21)



#endif
