/****************************************************************
* Inneh�ller drivrutiner f�r temperatursensor TMP36.
****************************************************************/
#ifndef TMP36_H_
#define TMP36_H_

#include "adc.h"
#include "serial.h"

/****************************************************************
* TMP36: Strukt f�r implementiering av TMP36.
****************************************************************/
struct tmp36
{
	struct adc adc_input; /* objekt temperaturssensorn �r ansluten till.*/	
	
};

/****************************************************************
* tmp36_init: initerar Ad-omvandlaren samt seriell �verf�ring
              inf�r temperaturm�tning.
			  
			  -self: pekare till temperatursensor
			  -pin:
****************************************************************/
static inline void tmp36_init(struct tmp36* self,
                              const uint8_t pin)
{
	if(pin >= 0 && pin <= 5)
	{
		adc_init(&self->adc_input, pin);
	}
	else if (pin >= 14 && pin <= 19)
	{
		adc_init(&self->adc_input, pin -14);
	}
	
	serial_init(9600);
	return;
	
}
							 
/****************************************************************
* tmp36_get_temperature: 
****************************************************************/
static inline double tmp36_get_temperature(const struct tmp36* self)
{
	const double voltage = adc_read(&self->adc_input) / 1023.0 * 5;
	return 100 * voltage - 50;
}

/****************************************************************
* tmp36_print_temperature: Skriver ut temperaturen via ansluten 
                           seriell terminal.
****************************************************************/
static inline void tmp36_print_temperature(const struct tmp36*self)
{
	serial_print_string("Temperature: ");
	serial_print_double(tmp36_get_temperature(self));
	serial_print_string(" degrees Celcius!\n");
	return;
}

#endif /* TMP36_H_ */