#include "timer.h"
#include <time.h>
#include "spi.h"
#include "uart.h"
#include "p33FJ128MC802.h"
#include <stdint.h>



unsigned int uiCounter1;

void f_Init_T1(void)
{
T1CONbits.TON = 0;      // Disable Timer
T1CONbits.TCS = 0;      // Select internal instruction cycle clock
T1CONbits.TGATE = 0;    // Disable Gated Timer mode
T1CONbits.TCKPS = 3;    // Select 1:256 Prescaler 40Mhz/256 = 156250Hz
TMR1 = 0x00;            // Clear timer register
PR1  = 30000;           // Load the period value Period value 
                                        //20ms needed
                                  // --> 20ms/(1/156250Hz)= 3125
IPC0bits.T1IP = 1;      // Set Timer1 Interrupt Priority Level
IFS0bits.T1IF = 0;      // Clear Timer1 Interrupt 
IEC0bits.T1IE = 1;      // Enable Timer1 interrupt
T1CONbits.TON = 1;      // Start Timer
}

void f_oscConfig(void)
{

    //Configure Oscillator to operate the device at 40Mhz
 	//Fosc= Fin*M/(N1*N2), Fcy=Fosc/2
 	//Fosc= 10M*32/(2*2)=80Mhz for 10M input clock 

	PLLFBD=41;//41,78;				//M=PLLFBD+2
    CLKDIVbits.PLLPRE  =0;//0,0;	//N1=2//N1=1
	CLKDIVbits.PLLPOST =0;//0,1;	//N2=2//N2=2
	OSCTUN             =0;		    //to make 7.37MHz 
    //CLKDIVbits.DOZEN   =1;
    //CLKDIVbits.DOZE    =0b001;      //Fcy divided by 2
	
    
    RCONbits.SWDTEN=0;
}
    

/*void f_delay(unsigned int uimseconds)
{
    clock_t goal = uimseconds + clock();
    while (goal > clock());
}*/
 
 void f_delay(uint32_t time_in_us) 
 {
    volatile uint32_t cnt1 = 0;
    volatile uint32_t cnt2 = 0;
    for(cnt1 = 0; cnt1 < time_in_us; cnt1++) 
    {
        for(cnt2 = 0; cnt2 < 20; cnt2++) 
        {
            cnt2++;
            cnt1--;
        }
    }
}
//-----------------------------------------------------------------
 void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void)
 //-----------------------------------------------------------------
                                                        // interrupt routine of Timer T1
 {
   
     uiCounter1=uiCounter1+1;
     IFS0bits.T1IF = 0;                                 // clear interrupt flag
 }
