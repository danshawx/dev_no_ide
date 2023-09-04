
#include "main.h"
#include "led.h"
#include "driver/drv_usart.h"
#include "test_boot.h"

void SystemClock_Config(void)
{
 LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
 while(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_2)
 {
 }

 /* HSI configuration and activation */
 LL_RCC_HSI_Enable();
 while(LL_RCC_HSI_IsReady() != 1)
 {
 }

 /* LSI configuration and activation */
 LL_RCC_LSI_Enable();
 while(LL_RCC_LSI_IsReady() != 1)
 {
 }

 /* Main PLL configuration and activation */
 LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_1, 8, LL_RCC_PLLR_DIV_2);
 LL_RCC_PLL_Enable();
 LL_RCC_PLL_EnableDomain_SYS();
 while(LL_RCC_PLL_IsReady() != 1)
 {
 }

 /* Set AHB prescaler*/
 LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

 /* Sysclk activation on the main PLL */
 LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
   while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
 {
 }

 /* Set APB1 prescaler*/
 LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
 LL_Init1msTick(64000000);
 /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
 LL_SetSystemCoreClock(64000000);
}

int main(void)
{

// LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);

// LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_13, LL_GPIO_MODE_OUTPUT);
// LL_GPIO_SetPinSpeed(GPIOC, LL_GPIO_PIN_13, LL_GPIO_SPEED_FREQ_HIGH);

/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  /** Disable the internal Pull-Up in Dead Battery pins of UCPD peripheral */
  LL_SYSCFG_DisableDBATT(LL_SYSCFG_UCPD1_STROBE | LL_SYSCFG_UCPD2_STROBE);

  SystemClock_Config();

  // gpio
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
  LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_5);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_5;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);


  usart2_init();

  // led_init();

  // CLI_INIT(CLI_BAUDRATE);


  while (1)
    {
      // LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_13);
      // LL_mDelay(500);
      // LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_5);
      led_task();
      test_boot_task();
    }
}
