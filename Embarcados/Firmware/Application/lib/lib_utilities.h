/*
 * utilities.h
 *
 *  Created on: 1 de abr de 2019
 *      Author: Andre
 */

#ifndef LIB_LIB_UTILITIES_H_
#define LIB_LIB_UTILITIES_H_

#include "stdint.h"

#ifndef TRUE
#define TRUE         1
#endif

#ifndef FALSE
#define FALSE        0
#endif


void run_current_time(void);
uint32_t get_current_time(void);
uint32_t elapsed_time(uint32_t timeMark);

#endif /* LIB_LIB_UTILITIES_H_ */
