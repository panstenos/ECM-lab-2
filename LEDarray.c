#include <xc.h>
#include "LEDarray.h"

/************************************
/ LEDarray_init
/ Function used to initialise pins to drivcvxc           e the LEDarray
************************************/
void LEDarray_init(void)
{
	//set up TRIS registers for pins connected to LED array
    TRISGbits.TRISG0=0; //set TRIS value for pin (output)
    TRISGbits.TRISG1=0; //set TRIS value for pin (output)
    TRISAbits.TRISA2=0; //set TRIS value for pin (output)
    TRISFbits.TRISF6=0; //set TRIS value for pin (output)
    TRISAbits.TRISA4=0; //set TRIS value for pin (output)
    TRISAbits.TRISA5=0; //set TRIS value for pin (output)
    TRISFbits.TRISF0=0; //set TRIS value for pin (output)
    TRISBbits.TRISB0=0; //set TRIS value for pin (output)
    TRISBbits.TRISB1=0; //set TRIS value for pin (output)
    
    ANSELGbits.ANSELG0=0; //turn off analogue input on pin 
    ANSELGbits.ANSELG1=0; //turn off analogue input on pin 
    ANSELAbits.ANSELA2=0; //turn off analogue input on pin 
    ANSELFbits.ANSELF6=0; //turn off analogue input on pin 
    ANSELAbits.ANSELA4=0; //turn off analogue input on pin 
    ANSELAbits.ANSELA5=0; //turn off analogue input on pin 
    ANSELFbits.ANSELF0=0; //turn off analogue input on pin 
    ANSELBbits.ANSELB0=0; //turn off analogue input on pin
    ANSELBbits.ANSELB1=0; //turn off analogue input on pin
    
	//set initial output LAT values (they may have random values when powered on)
    LATGbits.LATG0=0; //set TRIS value for pin (output)
    LATGbits.LATG1=0; //set TRIS value for pin (output)
    LATAbits.LATA2=0; //set TRIS value for pin (output)
    LATFbits.LATF6=0; //set TRIS value for pin (output)
    LATAbits.LATA4=0; //set TRIS value for pin (output)
    LATAbits.LATA5=0; //set TRIS value for pin (output)
    LATFbits.LATF0=0; //set TRIS value for pin (output)
    LATBbits.LATB0=0; //set TRIS value for pin (output)
    LATBbits.LATB1=0; //set TRIS value for pin (output)
}

/************************************
/ LEDarray_disp_bin
/ Function used to display a number on the LED array in binary
************************************/
void LEDarray_disp_bin(unsigned int number)
{
	//some code to turn on/off the pins connected to the LED array
	//if statements and bit masks can be used to determine if a particular pin should be on/off
    if (number & 0b000000001) {LATGbits.LATG0=1;} else {LATGbits.LATG0=0;}
    if (number & 0b000000010) {LATGbits.LATG1=1;} else {LATGbits.LATG1=0;}
    if (number & 0b000000100) {LATAbits.LATA2=1;} else {LATAbits.LATA2=0;}
    if (number & 0b000001000) {LATFbits.LATF6=1;} else {LATFbits.LATF6=0;}
    if (number & 0b000010000) {LATAbits.LATA4=1;} else {LATAbits.LATA4=0;}
    if (number & 0b000100000) {LATAbits.LATA5=1;} else {LATAbits.LATA5=0;}
    if (number & 0b001000000) {LATFbits.LATF0=1;} else {LATFbits.LATF0=0;}
    if (number & 0b010000000) {LATBbits.LATB0=1;} else {LATBbits.LATB0=0;}
    if (number & 0b100000000) {LATBbits.LATB1=1;} else {LATBbits.LATB1=0;}
}

/************************************
/ Function LEDarray_disp_dec
/ Used to display a number on the LEDs
/ where each LED is a value of 10
************************************/
void LEDarray_disp_dec(unsigned int number)
{
	unsigned int disp_val;
	disp_val = 0;
    //some code to manipulate the variable number into the correct
    //format and store in disp_val for display on the LED array  
    if (number <= 9) {disp_val = 0;}    
    if (number >  9) {disp_val = 1;}
    if (number > 19) {disp_val = 3;}
    if (number > 29) {disp_val = 7;}
    if (number > 39) {disp_val = 15;}
    if (number > 49) {disp_val = 31;}
    if (number > 59) {disp_val = 63;}
    if (number > 69) {disp_val = 127;}
    if (number > 79) {disp_val = 255;}
    if (number > 89) {disp_val = 511;}
	LEDarray_disp_bin(disp_val); 	//display value on LED array
}

/************************************
/ LEDarray_disp_PPM
/ Function used to display a level on the LED array with peak hold
/ cur_val is the current level from the most recent sample, and max is the peak value for the last second
/ these input values need to calculated else where in your code
************************************/
void LEDarray_disp_PPM(unsigned int cur_val, unsigned int max)
{
        
    unsigned int con_curr;	
    con_curr = 0;
    // convert current value to multiple LED output 
    // split the resistance input to deciles
    if (cur_val <= 25.5) {con_curr = 0;}    
    if (cur_val >  25.5) {con_curr = 1;}
    if (cur_val > 51.0) {con_curr = 3;}
    if (cur_val > 76.5) {con_curr = 7;}
    if (cur_val > 102) {con_curr = 15;}
    if (cur_val > 127.5) {con_curr = 31;}
    if (cur_val > 153) {con_curr = 63;}
    if (cur_val > 178.5) {con_curr = 127;}
    if (cur_val > 204) {con_curr = 255;}
    if (cur_val > 229.5) {con_curr = 511;}
    
	unsigned int con_max;
	con_max = 0;
    // convert max value to single LED output 
    // split the resistance input to deciles
    if (max <= 25.5) {con_max = 0;}    
    if (max >  25.5) {con_max = 1;}
    if (max > 51.0) {con_max = 2;}
    if (max > 76.5) {con_max = 4;}
    if (max > 102) {con_max = 8;}
    if (max > 127.5) {con_max = 16;}
    if (max > 153) {con_max = 32;}
    if (max > 178.5) {con_max = 64;}
    if (max > 204) {con_max = 128;}
    if (max > 229.5) {con_max = 256;}
    
    unsigned int disp_val; 
    
    disp_val = con_max | con_curr;
	LEDarray_disp_bin(disp_val);	//display value on LED array
}



