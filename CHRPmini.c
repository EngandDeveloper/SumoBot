/*==============================================================================
	CHRPmini - PIC16F886 hardware initialization and user functions.
==============================================================================*/

#include	"xc.h"				// XC compiler general include file

#include	"stdint.h"			// Include integer definitions
#include	"stdbool.h"			// Include Boolean (true/false) definitions

#include	"CHRPmini.h"		// Include user-created constants and functions

void initPorts(void)
{
	// TODO - Initialize oscillator, ports, and add (optional) user functions.

	// Initialize user ports and peripherals.

	ANSEL = 0b00000000;			// Make all PORTA pins digital I/O
	ANSELH = 0b00000000;		// Make all PORTB pins digital I/O
	OPTION_REG = 0b01010001;	// PORTB pull-ups on, TMR0 internal div 4

	// Set port directions for I/O pins: 0 = Output, 1 = Input

	TRISA = 0b00101111;			// Set Q1, Q2 phototransistor lines as inputs,
								// runLED, IR LED and beeper as outputs in PORTA
	TRISB = 0b11110000;			// Set up PORTB motor outputs, switches as input
	TRISC = 0b10110010;			// Set up receive and transmit lines for IR
								// demodulator (U4) and LED4, PING output and
								// ECHO input for ultrasonic module

	// Set starting I/O conditions.

	PORTA = 0;					// Clear all PORTA outputs, turn on run LED
	PORTB = 0;					// Clear all PORTB motor outputs
	PORTC = 0;					// Clear all PORTC servo outputs

	// Enable interrupts, if needed.
}
