#define UBRR0H (*(volatile unsigned char*)0xC5)
#define UBRR0L (*(volatile unsigned char*)0xC4)
#define UCSR0B (*(volatile unsigned char*)0xC1)
#define UCSR0C (*(volatile unsigned char*)0xC2)
#define UCSR0A (*(volatile unsigned char*)0xC0)
#define UDR0   (*(volatile unsigned char*)0xC6)

void uart_init() {
    unsigned int ubrr = 103; // 9600 baud at 16MHz
    UBRR0H = (ubrr >> 8);
    UBRR0L = ubrr;
    UCSR0B = (1 << 4) | (1 << 3);  // RXEN | TXEN
    UCSR0C = (1 << 1) | (1 << 2);  // 8-bit
}

void uart_send(char c) {
    while (!(UCSR0A & (1 << 5)));
    UDR0 = c;
}

void uart_send_string(const char* str) {
    while (*str) uart_send(*str++);
}
