/* 
 * File:   spi.h
 * Author: hi
 *
 * Created on April 22, 2018, 1:11 PM
 */

#ifndef SPI_H
#define	SPI_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* SPI_H */

void f_cfgspi(void);
unsigned int f_write_SPI_1(unsigned int uicommand1);
unsigned int f_write_SPI_2(unsigned int uicommand2);
void f_write_SPI_3(unsigned int uicommand3);
//unsigned int f_write_SPI_4(unsigned int uicommand5,unsigned int uicommand6);
unsigned int f_read_SPI_1();
unsigned int f_read_SPI_2();
void f_MapModulPins();