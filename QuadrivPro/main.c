/*
 * QuadrivPro.c
 *
 * Created: 10.11.2017 11:06:00
 * Author : Hm
 */ 

#define F_CPU	16e6

#include <avr/io.h>
#include <util/delay.h>

#define RELAY_PORT			PORTC
#define RELAY_bp			PC6

#define STATE_LED_PORT		PORTD
#define STATE_LED_bp		PD4

#define POWER_OUT_PORT		PORTC
#define POWER_OUT_1_bp		PC5
#define POWER_OUT_2_bp		PC4
#define POWER_OUT_3_bp		PC3
#define POWER_OUT_4_bp		PC2

#define DDRx(PORT)			(*(&PORT-1))
#define PINx(PIN)			(*(&PIN-2 ))

#define BS(PORT, BIT)		(PORT |=  (1<<BIT))
#define BC(PORT, BIT)		(PORT &= ~(1<<BIT))
#define BT(PIN, BIT)		(PIN  =   (1<<BIT))


int main(void)
{
	DDRx(STATE_LED_PORT) |= (1<<STATE_LED_bp);
	
	DDRx(RELAY_PORT)	 |= (1<<RELAY_bp);
	
	DDRx(POWER_OUT_PORT) |= (1<<POWER_OUT_1_bp) | // power out driver(s) cnfg.
							(1<<POWER_OUT_2_bp) |
							(1<<POWER_OUT_3_bp) |
							(1<<POWER_OUT_4_bp);
	
    while (1) 
    {
		uint8_t cycleCnt = 0x00;

		for (cycleCnt = 0x00 ; cycleCnt < 6 ; cycleCnt++)
		{
			BS(RELAY_PORT,RELAY_bp);
			BS(POWER_OUT_PORT,(POWER_OUT_1_bp | 
							   POWER_OUT_2_bp |
							   POWER_OUT_3_bp |
							   POWER_OUT_4_bp));
			BS(STATE_LED_PORT,STATE_LED_bp);
			_delay_ms(450);
			BC(RELAY_PORT,RELAY_bp);
			BC(POWER_OUT_PORT,POWER_OUT_1_bp |
							  POWER_OUT_2_bp |
							  POWER_OUT_3_bp |
							  POWER_OUT_4_bp );
			BC(STATE_LED_PORT,STATE_LED_bp);
			_delay_ms(450);
		}
		
		_delay_ms(3000);
		
    }
}

