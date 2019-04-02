/*
 * utilities.c
 *
 *  Created on: 2 de abr de 2019
 *      Author: Andre
 */
#include "lib_utilities.h"
#include "stdint.h"

static volatile uint32_t currentTime = 0;

void run_current_time(void)
{
    currentTime++;
}
uint32_t get_current_time(void)
{
    return currentTime;
}
uint32_t elapsed_time(uint32_t timeMark)
{
    uint32_t result;
    uint32_t buffer = currentTime;
    if(buffer >= timeMark){
        result = buffer - timeMark;
    }else{
        result = buffer + ((uint32_t)0xFFFFFFFF - timeMark);
    }
    return result;
}
