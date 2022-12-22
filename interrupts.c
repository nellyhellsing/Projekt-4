/********************************************************************************
* interrupts.c: Innehåller avbrottsrutiner.
********************************************************************************/
#include "header.h"

/* Globala objekt */
static volatile uint32_t timer1_counter = 0;
static volatile uint32_t timer1_max_count = (uint32_t)(60000 / 0.128 + 0.5);

static uint32_t executed_interrupts[5];
static volatile uint32_t num_executed_interrupts = 0;
static volatile uint32_t index = 0;
/*******************************************************************
* Average: Räknar ut genomsnittstemperaturen av de fem
*         senaste mätningarna.
*******************************************************************/
static uint32_t average(uint32_t* data, const int size)
{
	uint32_t sum = 0; 
	
	for (int i = 0; i < size; ++i)
	{
		sum += data[i];
	}
	
	return (uint32_t)(sum / 5.0 + 0.5);
}
/*******************************************************************
* Update_executed_interrupts: Räknar genomsnittstiden
*                             mellan de fem senaste knapptryckningarna.
*******************************************************************/
static void update_executed_interrupts(void)
{
	executed_interrupts[index++] = num_executed_interrupts;
	num_executed_interrupts = 0;
	
	if (index >= 5)
	{
		timer1_max_count = average(executed_interrupts, 5); 
		index = 0;
	}
	return;
}

/*******************************************************************
* PCINT0_vect: Vi aktiverar avbrottsrutin som äger rum vid nedtryckning
*               av tryckknapp b1.
*			   
*              När knappen är nedtryckt skrivs temperaturen ut via
*              seriell terminal. Sedan nollställs timer1 och genom
*			   snitts tiden för knapptryck uppdateras. 
*			  
*			   Avbrottet är avstängt i 300ms efterknapptryck för 
*			   att undvika kontaktsstudsar. 
*******************************************************************/
ISR (PCINT0_vect)
{
	PCICR &= ~(1 << PCIE0);
	TIMSK0 = (1 << TOIE0);

	if (button_is_pressed(&b1))
	{
		tmp36_print_temperature(&temp1);
		timer1_counter = 0;
		update_executed_interrupts();
	}		
	return;
}

/********************************************************************************
* ISR (TIMER0_OVF_vect): Avbrottsrutin som äger rum vid overflow av timer 0,
*                        dvs. uppräkning till 256, vilket sker var 0.128:e
*                        millisekund när timern är aktiverad.
*                        
*                        När vi trycker på knappen räknar vi upp till 300ms,
*                        efter den tiden nollställs counter0 och timer0, för att
*                        sedan börja räkna upp till 300ms igen.                       
********************************************************************************/
ISR (TIMER0_OVF_vect)
{
	static volatile uint16_t counter0 = 0;
	
	if (++counter0 >= TIMER0_MAX_COUNT)
	{
		PCICR = (1 << PCIE0);
		TIMSK0 = 0x00;
		counter0 = 0;
	}

	return;
}

/********************************************************************************
* ISR (TIMER1_COMPA_vect): Vi skriver ut temperaturen via seriell termial
*                          när timer1_counter når timer1_max_count. Därefter
*						   nollställs timer1_conter.
********************************************************************************/
ISR (TIMER1_COMPA_vect)
{
	num_executed_interrupts++;
	
	if (++timer1_counter >= timer1_max_count)
	{
		tmp36_print_temperature(&temp1);
		timer1_counter = 0;
	}

	return;
}
