#ifndef INIT_H
#define INIT_H

#include "gcc_def.h"

enum init_level 
{
	INIT_LEVEL_EARLY = 0,
	INIT_LEVEL_PRE_KERNEL_1,
	INIT_LEVEL_POST_KERNEL,
	INIT_LEVEL_APP,
};

struct init_entry 
{
	int (*init)(void);
    // int (*init)(const struct device *dev);
};


#define STRINGIFY(x) #x
#define STRING_CONCATENATE(x, y) (x ## y)
#define DECL_ALIGN(type) __aligned(__alignof(type)) type


#define INIT_ENTRY_SECTION(level, prio)                                      \
	__attribute__((__section__(".init_" #level STRINGIFY(prio)"_")))

#define INIT_ENTRY_NAME(init_id) STRING_CONCATENATE(__init_, init_id)


#define INIT_ENTRY_DEFINE(init_id, init_fn, device, level, prio)             \
	static const DECL_ALIGN(struct init_entry)                           \
		INIT_ENTRY_SECTION(level, prio) __used __noasan              \
		INIT_ENTRY_NAME(init_id) = {                                 \
			.init = (init_fn),                                     \
	}


#define SYS_INIT_NAMED(name, init_fn, level, prio)                             \
	INIT_ENTRY_DEFINE(name, init_fn, NULL, level, prio)

#define SYS_INIT(init_fn, level, prio)                                         \
	SYS_INIT_NAMED(init_fn, init_fn, level, prio)


void system_init(void);


#endif


