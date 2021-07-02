#include <stdio.h>
#include "conv.h"
#include "spi.h"
#include "uart.h"
#include "timer.h"
#include <math.h>




int16_t UpscaleTwosComplement(int16_t value, size_t length)
{
    // Too large?
    /*if (length > 15)
    {
        throw std::out_of_range("UpscaleTwosComplement length too large");
    }*/
    uint16_t mask = (~0) << length;
    // Too small for complement?
    if (length < 2)
    {
        return (~mask & value);
    }
    // Two's complement?
    uint16_t msb = 1 << (length-1);
    if (value & msb)
    {
        return (mask | value);
    }
    else
    {
        return (~mask & value);
    }
}
