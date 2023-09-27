#ifndef GCC_DEF_H
#define GCC_DEF_H

#ifndef __noasan
#define __noasan /**/
#endif

#ifndef __aligned
#define __aligned(x)	__attribute__((__aligned__(x)))
#endif

#define __used		__attribute__((__used__))



#endif

