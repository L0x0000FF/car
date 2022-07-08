#ifndef HAL_H
#define HAL_H

//Includes
#include <stdint.h>

// C functions
#ifdef __cplusplus
extern "C" {
#endif

void HAL_init(void);
void HAL_defaultTask(void);

#ifdef __cplusplus
}
#endif

#endif
