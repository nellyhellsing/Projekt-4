/******************************************************************
* serial.c: innehåller drivrutiner för seriell överföring.
******************************************************************/
#include "serial.h"


/******************************************************************
* serial_init: Initierar seriall transmissions, där vi skickar
               en bit i taget med angivet baud rate(bithastighet)
			   mätt i kilobits per sekund. \r = carriage retur,
			   skickas så att första utskiften hamnar längst till
			   vänster.
			   
			   1. Vi aktiverar serill transmisson (sändning) genom
			   att ettställa biten TXEN0 i kontroll-och status
			   registet USCR0B.
			   
			   2. Vi ställer in att åtta bitar ska skickas i taget
			   (ett täcken är 8-bitar) via ettställning av bitarna 
			   UCSZ00-UCSZ01.
			   
			   3. Vi ställer in baud rate (överförförings hastighet)
			   genom att skriva till 16-bitars registet UBRR0.
			   
			   UBRR0 = F_CPU / (16 * baud_rate_kbps) -1
			   där f_cpu är mikrodatorns klockfrekvens och baud rate
			   är överföringshastigheten i kilobits per sekund.
			   Vi använder flytalsdivision genom att sätta 16.0
			   Vi avrundar till närmsta heltal genom att addera 0.5.
			   Vi typomvandlar resultatet till uint16_t. 
			   
			   4. Vi lägger 'r' så att första utskriften hamnar
			   längst till vänster.
			   
			   5. Vi indikerar att seriell överföring är aktiverat
			   så att vi inte kan återinitera USART av misstag.
*******************************************************************/
void serial_init(const uint16_t baud_rate_kbps)
{
	static bool serial_initialized = false;
	if (serial_initialized) return;
	
	UCSR0B = (1 << TXEN0);
	UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
	UBRR0 = (uint16_t)(F_CPU / (16.0 * baud_rate_kbps) -1 + 0.5);
	UDR0 = '\r';
	
	serial_initialized = true;
	return;
}

/******************************************************************
* serial_print_char: Skickar angivet tecken till ansluten seriell
                      terminal.
					  1. Vi väntar på att postfacket UDR0 är tomt.
					  
					  - c: Tecknet som ska skickas.
					  2. Så fort postfacket UDR0 är tomt så lägger vi 
					  in det nya tecknet så att de skickas nedan.
					  
*******************************************************************/
void serial_print_char(const char c)
{
	while ((UCSR0A & (1 << UDRE0)) ==0);
	UDR0 = c;
	return;
}

/******************************************************************
* serial_print_string: Skickar angivet textstycke till ansluten
                       seriell terminal.
					   - s: Textstycket som ska skickas.
					   
					   1. Vi initerar genom strängen från början till
					   slut och skickar
*******************************************************************/
void serial_print_string(const char* s)
{
	for (int i = 0; s[i]; ++i)
	{
		serial_print_char(s[i]);
		
		if (s[i]=='\n')
		{
			serial_print_char('\r');
		}
	}
		
	return;
}

/******************************************************************
* serial_print_integer: Skriver  angivet signerat heltal till
                        ansluten seriell terminal.
						- number: talet som ska skrivas ut.
						%ld = long decimal
*******************************************************************/
void serial_print_integer(const int32_t number)
{
	char s[20]= {'\0'};
	sprintf(s,"%ld", number);
	serial_print_string(s);
	return;
		
}

/******************************************************************
* serial_print_unsigned: Skriver  angivet osignerat heltal till
                        ansluten seriell terminal.
						- number: talet som ska skrivas ut.
						 %lu= long unsigned.
*******************************************************************/
void serial_print_unsigned(const uint32_t number)
{
	char s[20]= {'\0'};
	sprintf(s, "%lu", number);
	serial_print_string(s);
	return;
}

/******************************************************************
* serial_print_double: Skriver angivet flyttal till ansluten seriell 
                       terminal.
						- number: talet som ska skrivas ut.
*******************************************************************/
void serial_print_double(const double number)
{
	char s[20]= {'\0'};
	const int32_t integer = (int32_t)number;
	int32_t decimal;
	
	if(integer >= 0)
	{
		decimal = (int32_t)((number - integer) * 100 + 0.5);
	} 
	else 
	{
		decimal = (int32_t)((integer - number) * 100 + 0.5);
	}
	sprintf(s,"%ld.%ld", integer, decimal);
	serial_print_string(s);
	return;
	
}