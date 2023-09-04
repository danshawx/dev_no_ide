
#include <stdio.h>
#include "tk_log.h"
#include "tk_log_config.h"
#include "drv_delay.h"

#ifdef LOG_FUN_ENABLE

char timestaptemp[20];

void time_to_timestamp(void)
{
    uint8_t hours, minutes, seconds;
    uint16_t mseconds;
    uint32_t ticks = drv_systick();

    hours = (ticks / 1000) / 3600;
    minutes = ((ticks / 1000) % 3600) / 60;
    seconds = ((ticks / 1000) % 3600) % 60;
    mseconds = ticks - hours * 3600 * 1000 - minutes * 60 * 1000 - seconds * 1000;

    sprintf(timestaptemp,"%.2d:%.2d:%.2d:%.3d",
                        hours,
                        minutes,
                        seconds,
                        mseconds);
}



#endif



