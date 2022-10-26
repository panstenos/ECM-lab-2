//main.c

#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits)
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep)

#include <xc.h>
#include "LEDarray.h"
#include "ADC.h"
#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  


void main(void) 
{   
    // setup pin for input (connected to button)
    LEDarray_init();
    ADC_init();
    
    unsigned int max = 0;
    
    while (1) {
        // if the current value is greater than the max value -> set that as the max value
        if (ADC_getval() > max){max = ADC_getval();}
        
        else{
        max = max >> 1;
        }
        
        LEDarray_disp_PPM(ADC_getval(),max); //use the PPM function

    }
}
