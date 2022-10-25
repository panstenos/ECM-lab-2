//main.c

#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits)
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep)

#include <xc.h>
#include "LEDarray.h"

#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  


void main(void) 
{
    // setup pin for input (connected to button)
    TRISFbits.TRISF2=1; //set TRIS value for pin (input)
    ANSELFbits.ANSELF2=0; //turn off analogue input on pin 

	unsigned int count=0;
    LEDarray_init();
    
    while (1) {
        while (PORTFbits.RF2); //empty while loop (wait for button press in RF2 sensor)
        
            if (!PORTFbits.RF2){ // when button 'RF2' is pressed
                count++; // increase the count when the button is pressed
                }
		if (count>511) {count=0;} //reset a when it gets too big
		LEDarray_disp_bin(count); //output a on the LED array in binary
		__delay_ms(500); // Delay so human eye can see change //original delay 50ms
    }
}
