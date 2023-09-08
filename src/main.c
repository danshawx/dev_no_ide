

#include "main.h"



/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follows :
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 170000000
  *            HCLK(Hz)                       = 170000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            PLL_M                          = 4
  *            PLL_N                          = 85
  *            PLL_P                          = 2
  *            PLL_Q                          = 2
  *            PLL_R                          = 2
  *            Flash Latency(WS)              = 8
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  /* Flash Latency configuration */
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_4);

  /* Enable boost mode to be able to reach 170MHz */
  LL_PWR_EnableRange1BoostMode();

  /* HSI configuration and activation */
  LL_RCC_HSI_Enable();
  while(LL_RCC_HSI_IsReady() != 1)
  {
  };

  /* Main PLL configuration and activation */
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_4, 85, LL_RCC_PLLR_DIV_2);
  LL_RCC_PLL_Enable();
  LL_RCC_PLL_EnableDomain_SYS();
  while(LL_RCC_PLL_IsReady() != 1)
  {
  };

  /* Sysclk activation on the main PLL */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_2);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  };

  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  /* Insure 1µs transition state at intermediate medium speed clock based on DWT */
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
  while(DWT->CYCCNT < 100);
  /* Set APB1 & APB2 prescaler*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

  /* Set systick to 1ms in using frequency set to 170MHz */
  /* This frequency can be calculated through LL RCC macro */
  /* ex: __LL_RCC_CALC_PLLCLK_FREQ(__LL_RCC_CALC_HSI_FREQ(),
                                  LL_RCC_PLLM_DIV_4, 85, LL_RCC_PLLR_DIV_2)*/
  LL_Init1msTick(170000000);

  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(170000000);
}


int main(void)
{
    // led_init();
    SystemClock_Config();

    while(1)
    {
        led_task();
        test_boot_task();
    }
    return 0;
}

