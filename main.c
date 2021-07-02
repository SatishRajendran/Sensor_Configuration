#include <stdio.h>
#include "spi.h"
#include "timer.h"
#include "uart.h"
#include "conv.h"
#include "result.h"
#include <math.h>
#include <stdint.h>
#include "p33FJ128MC802.h"


    _FOSCSEL(FNOSC_FRC & IESO_OFF)                //Fosc selection is made with Primary oscillator
    _FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_NONE); 
                                           //Clock switching is enabled, Fail-Safe Clock Monitor is disabled               
                                           //OSC2 pin has clock out function
                                           //No Oscillator Mode
    
    _FWDT(FWDTEN_OFF & WDTPOST_PS512 & WDTPRE_PR128);                     
                                            // Watchdog Timer Enabled/disabled by user software
                                            // (LPRC can be disabled by clearing SWDTEN bit in RCON register
    
    _FPOR(FPWRT_PWR128);                    //POR timer value(128ms)
    
    
    _FICD(JTAGEN_OFF & ICS_PGD1) ;          // Disable JTAG amd Comm channnel select

    
    unsigned int uiMSB5=0x0000,uiLSB5=0x0000;
    unsigned int uiMSB6=0x0000,uiLSB6=0x0000;
    signed int uiCOM1=0x0000,uiCOM2=0x0000,uiCOM3=0x0000,uiCOM4=0x0000,uiCOM5=0x0000,uiCOM6=0x0000;
    int i1=0,i2=0,i3=0,i4=0,i5=0,i6=0;
    float f1=0.0,f2=0.0,f3=0.0,f4=0.0,f5=0.0,f6=0.0;
    double fi1=0.0,fi2=0.0,fi3=0.0,fi4=0.0,fi5=0.0,fi6=0.0;
    unsigned int ang1=0x0000,band1=0x0000,ang2=0x0000,band2=0x0000;
    
    int main(void) 
{
    
    f_oscConfig();
    
   __builtin_write_OSCCONH(0x01);           // Initiate Clock Switch to PLL (NOSC=0b001)

   __builtin_write_OSCCONL(OSCCON | 0x01);  // Start clock switching 
   
    while (OSCCONbits.COSC != 0b001);       // Wait for Clock switch to occur
    
    while(OSCCONbits.LOCK != 1) {};         // Wait for PLL to lock
    
   
    f_Init_T1();
    
	TRISBbits.TRISB2 = 1;               //assigning pin for SPI data in
    TRISBbits.TRISB3 = 0;               //assigning pin for clock pulse     
    TRISBbits.TRISB4 = 0;               //assigning pin for SPI data out
    
    TRISAbits.TRISA0 = 0;               //assigning port A as output
    TRISBbits.TRISB14= 0;               //assigning port B15 as slave select output for acc pin 25
    TRISBbits.TRISB13= 0;               //assigning port B12 as slave select output for gyro pin 24
    AD1PCFGLbits.PCFG0 = 1;
    AD1CON1bits.ADON = 0;               //Disable ADC
    ADPCFG = 0xFFFF;                    //all Pins are digital I/O 
 
    LATAbits.LATA0 = 0;
    LATAbits.LATA0 = 1;
    RPOR5bits.RP11R= 1;
    PORTBbits.RB2=1;    
        
        f_cfgspi();
        f_cfgUart1();
        f_MapModulPins();
        
        
   
                     
    while(1)
    {
          if(uiCounter1>1)
            {
                LATAbits.LATA0=~LATAbits.LATA0;
                //ang=f_write_SPI_3(0xA4,0xB6);                   //soft-reset
                
                //ang1  = f_write_SPI_3(0x8F00,0b0011);             //for range to be between +-2g
                //band1 = f_write_SPI_3(0x9000,0b01000);            //for bandwidth to be 1000Hz   
                //f_write_SPI_3(0x9300,0b0001);                     //for fifo-config
                //f_write_SPI_3(0xAC00,0b00);                       //for symmetrical orientation
                f_write_SPI_3(0b0001000000001000);                       
                              
                //ang2 = f_write_SPI_3(0x8F00,0b010);              //for angle
                //band2 =f_write_SPI_3(0x9000,0b0011);             //for bandwidth
                
                uiCOM1 = f_result1();             //ACC_x Data
                uiCOM2 = f_result2();             //ACC_y Data
                uiCOM3 = f_result3();             //ACC_z Data
                uiCOM4 = f_result4();             //GYRO_x Data
                uiCOM5 = f_result5();             //GYRO_y Data
                uiCOM6 = f_result6();             //GYRO_z Data
                                                                                         
                //uiCOM1 = ((( (uiMSB1) << 8 ) |  (uiLSB1)) >> 4 );            //to get 12 bits of data output
                
                //uiCOM2 = ((( (uiMSB2) << 8 ) |  (uiLSB2)) >> 4 );
                
                //uiCOM3 = ((( (uiMSB3) << 8 ) |  (uiLSB3)) >> 4 );

                //uiCOM4 = (((uiMSB4) << 8 ) | (uiLSB4));                      //to get 16 bit of data output.
                
                //uiCOM5 = (((uiMSB5) << 8 ) | (uiLSB5));
                
                //uiCOM6 = (((uiMSB6) << 8 ) | (uiLSB6));
                
                i1 = UpscaleTwosComplement(uiCOM1,12);                             //two's complement for 12 bit data
                
                i2 = UpscaleTwosComplement(uiCOM2,12);
                
                i3 = UpscaleTwosComplement(uiCOM3,12);
                      
                i4 = UpscaleTwosComplement(uiCOM4,16);                                          //two's complement for 16 bit data
                
                i5 = UpscaleTwosComplement(uiCOM5,16);
                
                i6 = UpscaleTwosComplement(uiCOM6,16);
                                                           
                f1 = (float)(i1);                                                               //changing the values into float
                
                f2 = (float)(i2); 
                
                f3 = (float)(i3); 
                
                f4 = (float)(i4); 
                
                f5 = (float)(i5); 
                
                f6 = (float)(i6); 
               
                fi1 = (float)(f1/1024);                                     //dividing with a selective factor to change the raw data
 
                fi2 = (float)(f2/1024);                                     //dividing with a selective factor to change the raw data

                fi3 = (float)(f3/1024);                                     //dividing with a selective factor to change the raw data

                fi4 = (float)(f4/16.4);                                                          //dividing with a selective factor to change the raw data
                
                fi5 = (float)(f5/16.4);                                                          //dividing with a selective factor to change the raw data
                
                fi6 = (float)(f6/16.4);                                                          //dividing with a selective factor to change the raw data
                
                if(U1STAbits.TRMT == 1)
                {
                  
                  printf("ACC_X=%.3f, ACC_Y=%.3f, ACC_Z=%.3f\n",fi1,fi2,fi3);
                  //printf("GYRO_X=%.3f, GYRO_Y=%.3f, GYRO_Z=%.3f\n",fi4,fi5,fi6);
                  //printf ("ACC_X=%.3f g, ACC_Y=%.3f g, ACC_Z=%.3f g, GYRO_X=%.3f, GYRO_Y=%.3f, GYRO_Z=%.3f\n",fi1,fi2,fi3,fi4,fi5,fi6); 
                }
            
            uiCounter1=0; 
            }
              
    }
        
    return 0;
}
        
 
 
