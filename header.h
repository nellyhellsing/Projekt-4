/********************************************************************************
* header.h: Inneh�ller globala objekt och deklarationer f�r implementering av
*           det inbyggda systemet.
********************************************************************************/
#ifndef HEADER_H_
#define HEADER_H_

/* Inkluderingsdirektiv: */
#include "button.h"
#include "timer.h"
#include "tmp36.h"

/* Deklaration av globala objekt: */

extern struct button b1;    /* Tryckknappar. */
 
extern struct tmp36 temp1;  /* Temperatursensor */
extern volatile bool timer1_enabled;
extern volatile bool timer2_enabled;

/* Makrodefinition */ 
#define TIMER0_MAX_COUNT (uint32_t)(300 / 0.128 + 0.5)

/********************************************************************************
* setup: Initierar det inbyggda systemet.
********************************************************************************/
void setup(void);

#endif /* HEADER_H_ */