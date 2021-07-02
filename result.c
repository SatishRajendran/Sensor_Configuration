#include "spi.h"
#include "timer.h"
#include "p33FJ128MC802.h"
#include <stdint.h>


unsigned int f_result1()
{
    
    unsigned int uiMSB1=0x0000,uiLSB1=0x0000,uiCOM1=0x0000,offx=0x0000;
               
                uiLSB1 = f_write_SPI_2(0x8200);             //Acc LSB write(write 2) //gyro LSB write(write 1)
                
                uiMSB1 = f_write_SPI_2(0x8300);             //Acc MSB write(write 2) //gyro MSB write(write 1)
                
                //f_write_SPI_3(0x3601);
                
                //offx=f_write_SPI_2(0xB600);
                
                uiCOM1 = ((( (uiMSB1) << 8 ) |  (uiLSB1)) >> 4 ); //| offx);
                
                return uiCOM1;
}

unsigned int f_result2()
{
    
    unsigned int uiMSB2=0x0000,uiLSB2=0x0000,uiCOM2=0x0000,offy=0x0000;
                
                uiLSB2 = f_write_SPI_2(0x8400);
                
                uiMSB2 = f_write_SPI_2(0x8500);
                
                //f_write_SPI_3(0x3610);
                
                //offy=f_write_SPI_2(0xB600);
               
                uiCOM2 = ((( (uiMSB2) << 8 ) |  (uiLSB2)) >> 4 ); //| offy);
                
                return uiCOM2;
                
}

unsigned int f_result3()
{
    
    unsigned int uiMSB3=0x0000,uiLSB3=0x0000,uiCOM3=0x0000,offz=0x0000;
                
                uiLSB3 = f_write_SPI_2(0x8600);
                
                uiMSB3 = f_write_SPI_2(0x8700);
                
                //f_write_SPI_3(0x3611);
                
                //offz=f_write_SPI_2(0xB600);
                
                uiCOM3 = ((( (uiMSB3) << 8 ) |  (uiLSB3)) >> 4 );// | offz);
                
                return uiCOM3;
}

unsigned int f_result4()
{
    unsigned int uiMSB4=0x0000,uiLSB4=0x0000,uiCOM4=0x0000;
    
                uiLSB4 = f_write_SPI_1(0x8200);
                
                uiMSB4 = f_write_SPI_1(0x8300);
                
                uiCOM4 = (((uiMSB4) << 8 ) | (uiLSB4));
                
                return uiCOM4;
}

unsigned int f_result5()
{
    unsigned int uiMSB5=0x0000,uiLSB5=0x0000,uiCOM5=0x0000;
    
                uiLSB5 = f_write_SPI_1(0x8400);
                
                uiMSB5 = f_write_SPI_1(0x8500);
                
                uiCOM5 = (((uiMSB5) << 8 ) | (uiLSB5));
                
                return uiCOM5;
}

unsigned int f_result6()
{
    unsigned int uiMSB6=0x0000,uiLSB6=0x0000,uiCOM6=0x0000;
    
                uiLSB6 = f_write_SPI_1(0x8600);
                
                uiMSB6 = f_write_SPI_1(0x8700);
                
                uiCOM6 = (((uiMSB6) << 8 ) | (uiLSB6));
                
                return uiCOM6;
}