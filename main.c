#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits)
#pragma config WDTE = OFF       // WDT operating mode (WDT enabled regardless of sleep)

#include <xc.h>
#include "LEDarray.h"

#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  

void main(void) {
    LEDarray_init();
    int direction = 2; // direction is 1 for decreasing or 2 for increasing
    unsigned int number = 1; // define initial count
    
    while (1) {
        
        if (direction == 1) {  // loop for decreasing
            LEDarray_disp_bin(number); //output a on the LED array in binary            
            __delay_ms(50); // Delay function
            number = number >> 1; // shift number to the right
            if (number < 2) {direction = 2;} // when number is less than 2; i.e. 1 change direction
        }
        else {
            LEDarray_disp_bin(number); //output a on the LED array in binary
            __delay_ms(50); // Delay function
            number = number << 1; // shift number to the left
            if (number > 255) {direction = 1;} // when number is more than 255; i.e. 256 change direction
        }


    }
}
