#include <stdint.h>
#include <stdio.h>
#include <c64.h>
#include <6502.h>
#include "c64_interrupt.h"

const uint8_t top    = 0;
const uint8_t bottom = 100;


void setup(void)
{
    SEI();

    interrupt_set_handler(irq_handler);

    VIC.bordercolor = top;
    VIC.ctrl1 &= 0x7f;
    VIC.imr = 0x81;

    CLI();

}

void irq_handler(void)
{
    uint8_t irq;
    ack_vic_irq(irq);

    if (is_sys_irq(irq))
    {
        handle_sys_irq();
    }
    else
    {
        if (VIC.rasterline < bottom)
        {
            VIC.bordercolor = COLOR_YELLOW;
            VIC.rasterline  = bottom;
        }
        else
        {
            VIC.bordercolor = COLOR_BLUE;
            VIC.rasterline  = top;
        }
    }

    return_sys_irq();
}


int main(void)
{
    const char * cur = "HELLO, PUTCHAR!\n";

    setup();

    while (*cur)
        __putchar(*cur++);

    while (1)
        ;


    return 0;
}
