/******************************************************************
* serial.h: inneh�ller drivrutiner f�r seriell �verf�ring
******************************************************************/
#ifndef SERIAL_H_
#define SERIAL_H_

#include "misc.h"

/******************************************************************
* serial_init: Initierar seriall transmissions, d�r vi skickar
               en bit i taget med angivet baud rate(bithastighet)
			   m�tt i kilobits per sekund. \r = carriage retur,
			   skickas s� att f�rsta utskiften hamnar l�ngst till
			   v�nster.
*******************************************************************/
void serial_init(const uint16_t baud_rate_kbps);

/******************************************************************
* serial_print_char: Skickar angivet tecken till ansluten seriell
                      terminal.
*******************************************************************/
void serial_print_char(const char c);

/******************************************************************
* serial_print_string: Skickar angivet textstycke till ansluten
                       seriell terminal.
					   - s: Textstycket som ska skickas.
*******************************************************************/
void serial_print_string(const char* s);

/******************************************************************
* serial_print_integer: Skriver  angivet signerat heltal till
                        ansluten seriell terminal.
						- number: talet som ska skrivas ut.
*******************************************************************/
void serial_print_integer(const int32_t number);

/******************************************************************
* serial_print_unsigned: Skriver  angivet osignerat heltal till
                        ansluten seriell terminal.
						- number: talet som ska skrivas ut.
*******************************************************************/
void serial_print_unsigned(const uint32_t number);

/******************************************************************
* serial_print_double: Skriver angivet flyttal till ansluten seriell 
                       terminal.
						- number: talet som ska skrivas ut.
*******************************************************************/
void serial_print_double(const double number);


#endif /* SERIAL_H_ */