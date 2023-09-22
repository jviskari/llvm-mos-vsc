#ifndef C64_INTERRUPT_H
#define C64_INTERRUPT_H

#define CINV (*(uint16_t *) 0x0314)

// ==================================================
//                       macros
// ==================================================

#define handle_sys_irq()                                                       \
    asm("lda $dc0d\n\t"                                                        \
        "cli\n\t"                                                              \
        "jmp $ea31")

#define return_sys_irq() asm("jmp $ea7e")

#define is_sys_irq(irq) (irq < 0x80)

#define ack_vic_irq(irq)                                                       \
    asm("lda $d019\n\t"                                                        \
        "sta $d019"                                                            \
        : "=r"(irq)                                                            \
        :                                                                      \
        : "a")

// function prototypes
void irq_handler() __attribute__((noreturn));

#define interrupt_set_handler(handler) (CINV = (uint16_t) handler)

#endif
