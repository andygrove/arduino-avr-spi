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
    SPI_SS_DDR &= ~(1 << SPI_SS);                        /* set SS input */

    SPI_MOSI_DDR &= !(1 << SPI_MOSI);                   /* input on MOSI */
    SPI_MISO_DDR |= (1 << SPI_MISO);                   /* output on MISO */

    SPI_MOSI_PORT |= (1 << SPI_MOSI);                  /* pullup on MOSI */
    SPI_SCK_DDR &= ~(1 << SPI_SCK);                      /* input on SCK */

    /* Don't have to set phase, polarity b/c
     * default works with 25LCxxx chips */
    //SPCR |= (1 << SPR1);                /* div 16, safer for breadboards */
    //SPCR &= ~(1 << MSTR);                                  /* clock slave */
    SPCR |= (1 << SPE);                                        /* enable */


    // LED on PB0
//    set_bit(DDRB, PB0);

}

//Function to send and receive data
unsigned char spi_tranceiver (unsigned char data)
{
    SPDR = data;                                  //Load data into buffer
    while(!(SPSR & (1<<SPIF) ));                  //Wait until transmission complete
    return(SPDR);                                 //Return received data
}

int main(void)
{
    spi_init_slave();                             //Initialize slave SPI
    unsigned char data = 0;
    while(1)
    {
        data = spi_tranceiver(data);
        // counter = counter + 1;
        //
        // if (counter == 100) {
        //   toggle_bit(PORTB, PB0);
        // }
    }

    // while (1) {
    //   set_bit(PORTB, PB0);
    //   _delay_ms(500);
    //   clear_bit(PORTB, PB0);
    //   _delay_ms(500);
    // }
}
