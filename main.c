//main.c

#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits)
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep)

//include all the necessary header files
#include <xc.h>
#include "LEDarray.h"
#include "ADC.h"
#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  


void main(void) //main function
{   
    LEDarray_init(); //initialise the LEDarray function
    ADC_init(); // initialise the ADC function
    
    unsigned int max = 0; //initialise 'max' to 0
    
    while (1) { //unlimited loop
        // if the current value is greater than the max value 'max' -> set the current value to 'max' 
        if (ADC_getval() > max){max = ADC_getval();} //update 'max'
        
        else{
        max = max - 5.1; //decrease max value by 1/5th of the delay function below -> 0.2s * 5 = 1s delay
        __delay_ms(200); //delay function of 0.2s to make the LED array output visible
        }
        
        LEDarray_disp_PPM(ADC_getval(),max); //call the PPM function
    }
}
