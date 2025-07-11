#include "scheduler.h"
#include "uart.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

// Task to blink LED on PB5
void task_blink() {
    static int toggle = 0;
    PORTB = (toggle ^= (1 << PB5)); 
}

// Task to echo received UART data
void task_uart_echo() {
    if (UCSR0A & (1 << RXC0)) {
        uart_send(UDR0); 
    }
}

// Task to log status message
void task_logger() {
    uart_send_string("[INFO] System running.\n");
}

// Register demo tasks with the scheduler
void register_demo_tasks() {
    DDRB |= (1 << PB5); 
    scheduler_add(task_uart_echo, 1, 1, "uart_echo");
    scheduler_add(task_blink, 500, 3, "led_blink");
    scheduler_add(task_logger, 1000, 5, "logger");
}
