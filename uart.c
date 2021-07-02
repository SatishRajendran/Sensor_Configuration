#include "uart.h"
#include "timer.h"
#include "p33FJ128MC802.h"

#define FCY      40000000
#define BAUDRATE 115200            
#define BRGVAL   ((FCY/BAUDRATE)/16)-1          //Prescalar value is used as 1:16

void f_cfgUart1()
{
U1MODEbits.STSEL    = 0; // 1-Stop bit
U1MODEbits.PDSEL    = 0; // No Parity, 8-Data bits
U1MODEbits.ABAUD    = 0; // Auto-Baud disabled
U1MODEbits.BRGH     = 0; // Standard-Speed mode
U1MODEbits.RTSMD    = 0; //Read to send with simplex mode
U1BRG = BRGVAL;          // Baud Rate setting for 115200
U1STAbits.UTXISEL0  = 0; // Interrupt after one TX character is transmitted
U1STAbits.UTXISEL1  = 0;
IEC0bits.U1TXIE     = 1; // Enable UART TX interrupt
IEC0bits.U1RXIE     = 0; // Enable UART RX interrupt
IPC3bits.U1TXIP     = 5;
U1MODEbits.UARTEN   = 1; // Enable UART
U1STAbits.UTXEN     = 1; // Enable UART TX
IEC4bits.U2EIE      = 0; //clear Error interrupt UART
}

void __attribute__((interrupt, no_auto_psv))_U1TXInterrupt(void)
{
    //while(U1STAbits.TRMT==0)
    {
        IFS0bits.U1TXIF = 0; // Clear TX Interrupt flag
        //U1TXREG = 'a'; // Transmit one character
    }
}

void __attribute__((interrupt, no_auto_psv))_U1RXInterrupt(void)
{
    IFS0bits.U1RXIF = 0; //Clear RX Interrupt flag
}