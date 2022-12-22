/********************************************************************************
* setup.c: Innehåller funktionalitet för initiering av det inbyggda systemet.
********************************************************************************/
#include "header.h"

static inline void init_timers(void);

/* Definition av globala objekt: */

struct button b1;   /* Tryckknapp. */

struct tmp36 temp1; /* Temperatursensor */

/********************************************************************************
* setup: Initierar det inbyggda systemet.
********************************************************************************/
void setup(void)
{

	button_init(&b1, 13);
	
	button_enable_interrupt(&b1);

    tmp36_init(&temp1, A2);
	tmp36_print_temperature(&temp1);
	
	init_timers();
	
	return;
}

/********************************************************************************
* init_timers:  Initierar timerkretsar på Timer 0 och Timer 1.
********************************************************************************/
static inline void init_timers(void)
{ 
	asm("SEI");
	TCCR0B = (1 << CS01);

	TCCR1B = (1 << WGM12) | (1 << CS11);
	OCR1A = 256; /* Båda räknar till 256. */
	TIMSK1 = (1 << OCIE1A); /* Sätter på, avbrott var 60:e sekund. */
	return;
}
