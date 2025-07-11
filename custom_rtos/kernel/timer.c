#include "scheduler.h"

#define TCCR0A (*(volatile unsigned char*)0x44)
#define TCCR0B (*(volatile unsigned char*)0x45)
#define TIMSK0 (*(volatile unsigned char*)0x6E)
#define OCR0A  (*(volatile unsigned char*)0x47)
#define TCNT0  (*(volatile unsigned char*)0x46)

#define SREG   (*(volatile unsigned char*)0x5F)

#define ISR(v) void v(void) __attribute__((signal)); void v(void)

ISR(TIMER0_COMPA_vect) {
    scheduler_tick();
}

void timer0_init() {
    TCCR0A = (1 << 1);              // CTC mode
    TCCR0B = (1 << 1) | (1 << 0);   // clk/64
    OCR0A = 249;                    // 1ms
    TIMSK0 |= (1 << 1);             // enable compare A
    TCNT0 = 0;
}
