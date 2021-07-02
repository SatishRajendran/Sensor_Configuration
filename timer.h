/* 
 * File:   timer.h
 * Author: hi
 *
 * Created on April 22, 2018, 1:10 PM
 */

#ifndef TIMER_H
#define	TIMER_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* TIMER_H */

#include <stdint.h>

extern unsigned int uiCounter1;

void f_Init_T1(void);
void f_oscConfig(void);
//void f_delay(unsigned int uimseconds);
void f_delay(uint32_t time_in_us);