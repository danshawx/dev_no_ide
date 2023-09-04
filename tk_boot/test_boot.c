#include "test_boot.h"
#include "test_boot_f1.h"
#include "header.h"

#ifdef CONFIG_BOOTLOADER
void test_boot_task(void)
{
    test_boot_f1_task();
}
#endif
