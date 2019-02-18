/*==============================================================================
	CHRPmini - PIC16F886 symbolic constants for user and main functions.
==============================================================================*/

// TODO - Add user constant definitions for user.c and main.c here. Constant
// definitions provide names for all CHRPmini I/O devices and program constants.

// PORTA I/O device definitions
#define Q1			RA0			// Phototransistor Q1 input
#define Q2			RA1			// Phototransistor Q2 input
#define LED2		RA4			// Run LED, LED2 output
#define RUNLED      RA4         // Run LED, LED2 output
#define VM			RA5			// Motor supply voltage divider input
#define BEEPER		RA6			// Piezo beeper P1 output
#define P1			RA6			// Piezo beeper P1 output
#define LED3		RA7			// Floor illumination LED (LED3) output

// PORTB I/O device definitions
#define M1A			RB0			// Motor 1 A output
#define M1B			RB1			// Motor 1 B output
#define M2A			RB2			// Motor 2 A output
#define M2B			RB3			// Motor 2 B output
#define	S2			RB4			// Switch S2 input
#define S3			RB5			// Switch S3 input

// PORTC I/O device definitions
#define	TRIG		RC0			// Ultrasonic distance sensor Trigger output
#define SERVO1		RC0			// Servo 1 output (external header H2)
#define ECHO		RC1			// Ultrasonic distance sensor Echo input
#define	SERVO2		RC1			// Servo 2 output (external header H3)
#define	SERVO3		RC2			// Servo 3 output (external header H4)
#define SERVO4		RC3			// Servo 4 output (external header H5)
#define LED4		RC6			// Communication/sensor LED, LED4 output
#define IR			RC7			// IR demodulator U4 input
#define U4			RC7			// IR demodulator U4 input

// A-D Converter input channel definitions
#define ADCH0		0b00000000	// A-D channel 0 input
#define	ADQ1		0b00000000	// Q1 phototransistor A-D input channel (Ch0)
#define ADCH1		0b00000100	// A-D channel 1 input
#define	ADQ2		0b00000100	// Q2 phototransistor A-D input channel (Ch1)
#define ADCH2		0b00001000	// A-D channel 2 input
#define ADCH3		0b00001100	// A-D channel 3 input
#define ADCH4		0b00010000	// A-D channel 4 input
#define	ADVM		0b00010000	// Motor voltage divider A-D input channel (Ch4)

// Clock frequency for delay macros and simulation
#define _XTAL_FREQ	4000000			// Set clock frequency for time delays
#define FCY			_XTAL_FREQ/4	// Set processor cycle time

void initPorts(void);    // Port configuration function prototype declaration

