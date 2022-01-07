#ifndef __EXPERIMENT_HEADER__
#define __EXPERIMENT_HEADER__


#include "stdint.h"


void pixHDiff   (uint32_t*, uint32_t*, int, int);
void pixVDiff   (uint32_t*, uint32_t*, int, int);
void pixHAbsDiff(uint32_t*, uint32_t*, int, int);
void pixVAbsDiff(uint32_t*, uint32_t*, int, int);
void pixHDelta  (uint32_t*, uint32_t*, int, int);
void pixVDelta  (uint32_t*, uint32_t*, int, int);

#endif
