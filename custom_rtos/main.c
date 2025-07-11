#include "scheduler.h"
#include "timer.h"
#include "uart.h"
#include "tasks.h"

int main() {
    uart_init();
    timer0_init();
    scheduler_init();

    register_demo_tasks();  // LED, echo, logger

    __asm__ __volatile__ ("sei");  // Enable global interrupts

    while (1) {
        scheduler_run();  // Cooperative loop
    }
}
