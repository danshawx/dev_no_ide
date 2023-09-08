#include "test_boot.h"



void test_boot_task(void)
{
#ifdef CONFIG_BOOT_F1
    test_boot_f1_task();
#endif

#ifdef CONFIG_BOOT_F2
    test_boot_f2_task();
#endif
}
