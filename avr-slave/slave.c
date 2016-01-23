#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "pinDefines.h"
#include "macros.h"

#define ACK 0x7E

void spi_init_slave (void)
{
    // set SCK, SS and MOSI as input
    SPI_SCK_DDR  &= ~(1 << SPI_SCK);
    SPI_MOSI_DDR &= ~(1 << SPI_MOSI);
    SPI_SS_DDR   &= ~(1 << SPI_SS);

    // set MISO as output
    SPI_MISO_DDR |= (1 << SPI_MISO);

    // pullup on MOSI
    SPI_MOSI_PORT |= (1 << SPI_MOSI);

    // enable SPI
    SPCR |= (1 << SPE);

    // PB0 = output (LED)
    DDRB |= (1 << PB0);

}

/* Send and receive one byte between master and slave. */
unsigned char spi_tranceiver (unsigned char data)
{
    SPDR = data;
    while(!(SPSR & (1<<SPIF) ));
    unsigned char received = SPDR;
    unsigned char tmp = SPSR;

    // toggle the LED
    PORTB ^= 1 << PB0;

    return received;
}

int main(void)
{
    spi_init_slave();
    unsigned char data = 0;
    unsigned char send = 0;
    while(1) {
        send = data * 2;
        data = spi_tranceiver(send);
    }
}
