#include "stdint.h"
#include "main.h"


void led_init(void)
{
    uint8_t test_data = 0;

    test_data ++;
}

void led_task(void)
{
#ifdef USE_TEST
    LL_mDelay(3000);
    LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_5);
#else
    LL_mDelay(500);
    LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_5);
#endif
    
}
