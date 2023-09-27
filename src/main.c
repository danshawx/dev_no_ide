
#include "main.h"
#include "led.h"

#include "test_boot.h"


int main(void)
{
  system_init();

  // usart2_init();

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
