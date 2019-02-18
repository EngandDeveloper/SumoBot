/*==============================================================================
	Project: Sumo               Namik
	Version: 3.0				Date: January 26, 2018
	Target: CHRPmini			Processor: PIC16F886

	A sonar-based Sumo robot.
==============================================================================*/

#include	"xc.h"				// XC compiler general include file

#include	"stdint.h"			// Integer definition
#include	"stdbool.h"			// Boolean (true/false) definition

#include	"CHRPmini.h"		// User-created variables and functions

/*==============================================================================
	Global variable definitions
 =============================================================================*/
unsigned char mode;				// Operating modes (search, attack)) // help to put my attack and search modes in main function
unsigned char range;			// Target range in cm // will indicate range of my robot to closest object in the sonarSensor function and make the sonarSensor function global
unsigned char target;			// Target acquisition counter

/*==============================================================================
	Program constant definitions
 =============================================================================*/
#define	search		0			// Search mode
#define	attack		1			// Attack mode
#define	maxRange	75			// Maximum sonar target range in cm because ring is 90 cm and my robot is 17cm

/*==============================================================================
	Motor direction constant definitions
 =============================================================================*/

const char fwd = 0b00001010;      // Code to go forward
const char rev = 0b00000101;      // Code to go reverse 
const char left = 0b00001000;     // Code to go left
const char right = 0b00000010;    // Code to go right
const char stop = 0b00000000;     // Code to stop
         
unsigned bool frontLine;               // later use to make detecting front line a global variable to use in both search and attack mode
unsigned bool backLine;               // later use to make detecting back line a global variable to use in both search and attack mode

void wait(void) // 5 second delay function in the beginning of match
{
    while(S2 == 1);
    
    for(unsigned char i = 10; i != 0; i--)
    {
        __delay_ms(500);
        LED2 = !LED2;        // turn on/off the LED2 to indicate we are in the wait function
    }
}

/*==============================================================================
	Sonar range function. Returns target distance in cm, or 0 if error.
 =============================================================================*/

void sonarSensor(void)
{  
        TRIG = 1;
        __delay_ms(20);
        TRIG = 0;
        
        range = 0;            // make range zero here. Otherwise it will continue even if range is bigger than zero.
        
        while(ECHO == 0);     // wait when ECHO is zero
        
        while(ECHO == 1)
        {
            __delay_us(50);   // delay of echo of sound reach back to sonar sensor
            range++;
        }
        
        if(range > maxRange)
        {
            range = 0;       // if sonar sensor can't detect anything within 75 cm(or in maxRange), make range zero. So, in search mode, robot will turn around to search different directions 
        }     
}


void detectLine(void)
{    
    if(Q1 == 0 && Q2 == 1)    // if front sensor detect change colour of ring make line1 = 1
    {
        frontLine = 1;
    }
    
    if(Q1 == 1 && Q2 == 0)   // if back sensor detect change colour of ring make line1 = 1
    {
        backLine = 1;
    }
}
/*==============================================================================
	Main program code
==============================================================================*/

int main(void)
{
    // Initialize I/O and peripherals
    initPorts();
        
    LED3 = 1;       // Turn on front light sensor's LED
    LED4 = 1;       // Turn on back light sensor's LED
    wait();         // function to wait 5 second before start fight
    mode = search;  // to start with search mode
    
    while(1)
    {
        while(mode == search)		// Search mode
		{
            sonarSensor(); 
			detectLine();
			
			if(range == 0)         // if there is no enemy within 75 cm turn right to find enemy
			{
				PORTB = right;
                __delay_ms(200);    // To check sonarSensor and detectLine after a while
			}
			
			if(frontLine == 1)          // if front sensor detect line, go back and then left to save robot from fall out off ring
			{
				PORTB = rev;
                __delay_ms(1000);   // Delay before robot start turning left. This delay prevent motor go rev a very little and then immediately start turning left
                PORTB = left;
                __delay_ms(500);    // To check sonarSensor and detectLine after a while
                frontLine = 0;      // to reset line variable. Otherwise, even though robot turn back to ring, it pretend it is still at the edge of the ring
			}
		
			if(backLine == 1)           // if back sensor detect line, go forward and then right to save robot from fall out off ring
			{
				PORTB = fwd;
                __delay_ms(1000);   // Delay before robot start turning right. This delay prevent motor go front a very little and then immediately start turning right
                PORTB = right;
                __delay_ms(500);    // To check sonarSensor and detectLine after a while
                backLine = 0;      // to reset line variable. Otherwise, even though robot turn back to ring, it pretend it is still at the edge of the ring
			}

			if(range >= 1 && range <= maxRange)
			{
				mode = attack;
			}
            __delay_ms(5);  // delay to help sonarSensor to work 
		}

		while(mode == attack)   // Attack mode
		{
            sonarSensor();
			detectLine();
			
			if(range >= 1 && range <= maxRange)
			{
					PORTB = fwd;			// Go forward to push enemy out off ring
                    __delay_ms(100);        // To check sonarSensor and detectLine after a while
			}
			
			if(frontLine == 1)
			{
				mode = search;  // if detect the edge of the ring go to search mode to save robot from fall out off ring
			}
		
			if(backLine == 1)
			{
				mode = search;  // if detect the edge of the ring go to search mode to save robot from fall out off ring
			}
            
            if(range == 0)
			{
				mode = search;  // if range is zero go to search mode to find enemy
			}
            __delay_ms(5);   // delay to help sonarSensor to work
		}
        
    }
}