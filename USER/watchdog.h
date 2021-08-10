#ifndef __WATCHDOG_H__
#define __WATCHDOG_H__

#include "def.h"
#include "stm32f10x.h"


VOID I_WD_Init(VOID);

VOID I_WD_Feed(STATUS* status);


#endif
