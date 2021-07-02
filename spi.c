#include "spi.h"
#include "timer.h"
#include "p33FJ128MC802.h"
#include <stdint.h>

#define FCY 40000000;

unsigned int f_write_SPI_1(unsigned int uicommand1)
{	
	unsigned int temp1;	
    unsigned int j;
    
	LATBbits.LATB13 = 0;		          // lower the slave select line       for port RB5 pin 24
   	temp1   = SPI1BUF;			          // dummy read of the SPI1BUF register to clear the SPIRBF flag
	SPI1BUF = uicommand1;                  // write the data out to the SPI peripheral
    while (SPI1STATbits.SPITBF);	      // wait for the data to be sent out
    while (!SPI1STATbits.SPIRBF);          
    LATBbits.LATB13 = 1;                // raise the slave select line
    
    j=f_read_SPI_1();
    
    return j;
}

unsigned int f_write_SPI_2(unsigned int uicommand2)
{	
	unsigned int temp2;	
    unsigned int i;
    
	LATBbits.LATB14 = 0;		          // lower the slave select line       for port RB5 pin 25
   	temp2   = SPI1BUF;			          // dummy read of the SPI1BUF register to clear the SPIRBF flag
	SPI1BUF = uicommand2;                 // write the data out to the SPI peripheral
    
    while (SPI1STATbits.SPITBF);	      // wait for the data to be sent out
    while (!SPI1STATbits.SPIRBF);          
    LATBbits.LATB14 = 1;                  // raise the slave select line
    
    i=f_read_SPI_2();

    return i;
}

void f_write_SPI_3(unsigned int uicommand3)
{	
	unsigned int temp3;	
    //unsigned int k;
    
	LATBbits.LATB14 = 0;		          // lower the slave select line       for port RB5 pin 25
   	temp3   = SPI1BUF;			          // dummy read of the SPI1BUF register to clear the SPIRBF flag
	SPI1BUF = uicommand3;                 // write the data out to the SPI peripheral
    
    while (SPI1STATbits.SPITBF);	      // wait for the data to be sent out
    while (!SPI1STATbits.SPIRBF);          
    LATBbits.LATB14 = 1;                  // raise the slave select line
}

/*unsigned int f_write_SPI_3(unsigned int uicommand3,unsigned int uivalue1)
{
    unsigned int temp3,temp4;	
    unsigned int k;
    
	LATBbits.LATB14 = 0;		          // lower the slave select line       for port RB5 pin 24
   	temp3   = SPI1BUF;			          // dummy read of the SPI1BUF register to clear the SPIRBF flag
	SPI1BUF = uicommand3;                 // write the data out to the SPI peripheral
    temp4   = SPI1BUF;
    SPI1BUF = uivalue1;
                 
    while (SPI1STATbits.SPITBF);	      // wait for the data to be sent out
    while (!SPI1STATbits.SPIRBF);          
    //LATBbits.LATB14 = 1;                  // raise the slave select line
    
    k=f_read_SPI_2();
    
    uivalue1 = uivalue1 & k ;
      
    LATBbits.LATB14 = 1;
    
    //uivalue1 = f_read_SPI_2();
    
    return uivalue1;
}

unsigned int f_write_SPI_4(unsigned int uicommand5,unsigned int uicommand6)
{	
	unsigned int temp5,temp6;	
    unsigned int l,m;
   
	LATBbits.LATB14 = 0;		          // lower the slave select line       for port RB5 pin 25
   	temp5   = SPI1BUF;			          // dummy read of the SPI1BUF register to clear the SPIRBF flag
	SPI1BUF = uicommand5;
    
    f_delay(10);
    
    while (SPI1STATbits.SPITBF);	      // wait for the data to be sent out
    while (!SPI1STATbits.SPIRBF);
    
    l=f_read_SPI_2();    
    
    LATBbits.LATB14 = 1;  
   
        
    LATBbits.LATB14 = 0;		          // lower the slave select line       for port RB5 pin 25
    
    temp6   = SPI1BUF;
    SPI1BUF = uicommand6;                 // write the data out to the SPI peripheral
    
    f_delay(10);
    
    while (SPI1STATbits.SPITBF);	      // wait for the data to be sent out
    while (!SPI1STATbits.SPIRBF); 
    
    LATBbits.LATB14 = 1;                  // raise the slave select line
    
    m=f_read_SPI_2();
                    
    return m ;
}*/

unsigned int f_read_SPI_1()
{
    unsigned int uiout1;
    while(!SPI1STATbits.SPIRBF);
    uiout1 = SPI1BUF;
    return uiout1; 
}

unsigned int f_read_SPI_2()
{
    unsigned int uiout2;
    while(!SPI1STATbits.SPIRBF);
    uiout2 = SPI1BUF;
    return uiout2; 
}


void f_MapModulPins()
{
__builtin_write_OSCCONL(OSCCON & 0xbf);     // PPSUnLock

//SPI PINS CONFIGURATION
RPOR1bits.RP3R = 8 ;                        // Assign RP3 as Output Pin To SPI1 Clock Output.pin 7
RPOR2bits.RP4R = 7 ;                        // Assign RP4 as Output Pin SPI1 Data Output.pin 11
RPOR2bits.RP5R = 9 ;                        // Assign RP2 as Output Pin Where is SPI1 Slave Select Output. SS1OUT
                                            // pin 14
RPINR20bits.SDI1R = 2;                      // Assign SPI data input pin 6 
RPINR20bits.SCK1R = 3;                      // Assign SPI clock input 

//UART PINS COFIGURATION
RPOR3bits.RP7R    = 3;                      //Remapping Pin Rp8 as Uart Transmit 16th pin MC
RPINR18 = 0x09;                             // Make Pin RP9 U1RX 18th pin in MC

__builtin_write_OSCCONL(OSCCON | 0x40);     // PPSLock

//! Extra digital output as Chip Select
//TRISDbits.TRISD8 = 0; // 
}

void f_cfgspi(void)
{
    IFS0bits.SPI1IF = 0;        // Clear the Interrupt flag
    IEC0bits.SPI1IE = 1;        // Disable the interrupt //enabling
    
    // SPI1CON1 Register Settings
    SPI1STATbits.SPIEN  = 0;    // Disable SPI module
    SPI1CON1bits.DISSCK = 0;    // Internal serial clock is enabled
    SPI1CON1bits.DISSDO = 0;    // SDOx pin is controlled by the module
    SPI1CON1bits.MODE16 = 1;    // Communication is word-wide (16 bits) 

    SPI1CON1bits.MSTEN = 1;     // Master mode enabled
    SPI1CON1bits.SMP   = 0;     // Input data is sampled at the middle of data output time
    SPI1CON1bits.CKE   = 0;     // Serial output data changes on transition from active clock state to active state.//Idle clock state to active clock state
    
    //Slave frame pulse setting
    SPI1CON1bits.SSEN   = 0;     // Slave select is enabled(automatic)
   
    /*SPI1CON2bits.FRMDLY = 0;    // Frame sync pulse coincides with first bit clock
    SPI1CON2bits.FRMEN  = 0;    // Framed SPIx support enabled (SSx pin used as frame sync pulse input/output)
    SPI1CON2bits.FRMPOL = 0;    // Frame sync pulse is active-low
    SPI1CON2bits.SPIFSD = 0;    // Frame sync pulse input (slave)*/
  
    // Idle clock state to active clock state
    SPI1CON1bits.CKP = 1;       // Idle state for clock is a high level;
    SPI1CON1bits.SPRE = 0b110;  // secondary scale 111= pre-scale 2:1
    SPI1CON1bits.PPRE = 0b10;   // primary scale 10 = pre-scale 4:1
                                // around 6-7 Mhz but no answers yet
    
    // active state is a high level
    SPI1STATbits.SPIEN  = 1;     // Enable SPI module
    SPI1STATbits.SPIROV = 0;    // Clear the SPIROV bit 
    
    
    // Interrupt Controller Settings
    IFS0bits.SPI1IF = 0;        // Clear the Interrupt flag
    IEC0bits.SPI1IE = 0;        // Enable the interrupt
    //IPC2bits.SPI1IP = 6;    // highest priority
    
}



void __attribute__((interrupt,no_auto_psv)) _SPI1Interrupt(void)
{  
  IFS0bits.SPI1IF = 0;         // Clear Interrupt status of SPI1
}

 	