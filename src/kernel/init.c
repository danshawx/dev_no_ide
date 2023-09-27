#include "init.h"

extern const struct init_entry __init_start[];
extern const struct init_entry __init_EARLY_start[];
extern const struct init_entry __init_PRE_KERNEL_1_start[];
extern const struct init_entry __init_POST_KERNEL_start[];
extern const struct init_entry __init_APP_start[];
extern const struct init_entry __init_end[];

static void sys_init_run_level(enum init_level level)
{
	static const struct init_entry *levels[] = {
		__init_EARLY_start,
		__init_PRE_KERNEL_1_start,
		__init_POST_KERNEL_start,
		__init_APP_start,

		/* End marker */
		__init_end,
	};
	const struct init_entry *entry;

	for (entry = levels[level]; entry < levels[level+1]; entry++) 
    {
        if (entry->init)
        {
            entry->init();
        }
	}
}


void system_init(void)
{
    sys_init_run_level(INIT_LEVEL_EARLY);
    sys_init_run_level(INIT_LEVEL_PRE_KERNEL_1);
    // sys_init_run_level(INIT_LEVEL_POST_KERNEL);
    sys_init_run_level(INIT_LEVEL_APP);
}

