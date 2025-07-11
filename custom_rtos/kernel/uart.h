#ifndef UART_H
#define UART_H
void uart_init();
void uart_send(char c);
void uart_send_string(const char* str);
#endif
