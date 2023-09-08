#include "main.h"
#include "led.h"


void led_init(void)
{
    // LL_EXTI_InitTypeDef EXTI_InitStruct = {0};
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
    // LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
    // LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);

    /**/
    LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_5);

    /**/
    // LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_6);

    /**/
    GPIO_InitStruct.Pin = LL_GPIO_PIN_5;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_5);

    /**/
    // GPIO_InitStruct.Pin = LL_GPIO_PIN_6;
    // GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    // GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    // GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    // GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
    // LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /**/
    // LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTA, LL_SYSCFG_EXTI_LINE6);

    /**/
    // EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_6;
    // EXTI_InitStruct.LineCommand = ENABLE;
    // EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
    // EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
    // LL_EXTI_Init(&EXTI_InitStruct);

    /**/
    // LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_6, LL_GPIO_PULL_DOWN);

    // /**/
    // LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_6, LL_GPIO_MODE_INPUT);

    /* EXTI interrupt init*/
    // NVIC_SetPriority(EXTI9_5_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
    // NVIC_EnableIRQ(EXTI9_5_IRQn);;
}

void led_task(void)
{
    static uint8_t start = 0;

    if (0 == start)
    {
        start += 1;
        led_init();
    }

#ifdef USE_TEST
    LL_mDelay(3000);
    LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_5);
#else
    LL_mDelay(500);
    LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_5);
#endif
    
}
