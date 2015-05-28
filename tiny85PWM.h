#include <Arduino.h>

/**
 * Filename: tiny85PWM
 * Author: Nicholas Pelham
 * Date: 02 December 2014
 *
 * Description:
 *   Provides basic pulse width modulation functionality for software pins
 *   0, 1, and 4 on the ATTiny85
**/


/**
 * Initializes Timer/Counter Control Registers, Waveform Generation Mode, 
 * Clock Select, and Compare Match Output Bits for Fast Pulse Width 
 * Modulation. Sets the Output Compare Registers appropriately for matching
 * frequency and initializes the OCRnA and OCRnB to 0.
**/
void initPWM() {        
        // Timer 0
        TCCR0A = (1<<WGM00) | (1<<WGM01) 
		| (1<<COM0A1) | (1<<COM0B1); 	// fast PWM, clear OC0A and OC0B on compare
        TCCR0B = (1<<CS00); 			// fast PWM, top at 0xFF, no prescaler
        OCR0A = OCR0B = 0;			// duty cycle // pulse width

        // Timer 1
        TCCR1 = (1<<CS10); 			// no prescaler
        GTCCR = (1<<COM1B1) | (1<<PWM1B); 	// clear OC1B on compare
        OCR1B = 0; 				// duty cycle // pulse width
        OCR1C = 255; 				// frequency
}

/**
 * Used in place of analogWrite to force pulse width modulation on software
 * pin 4. It may not be neccessary to assign the value directly to OCR0A or
 * OCR0B, but it is done for consistancy.
 * If an invalid pin number is passed as pinNum, the function passes the 
 * parameters to Arduino's analogWrite function.
 *
 * Parameters:
 *    pinNum - Software pin number which will be assigned a value
 *    value  - The value ranging from 0 to 255 which will be assigned to the 
 *             pin.
**/
void writePWM(unsigned short pinNum, unsigned char value)
	switch(pinNum) {
	case 0:
		OCR0A = value; 			// duty cycle
		break;
	case 1:
		OCR0B = value;			// duty cycle
		break;
	case 4:
		OCR1B = value;			// duty cycle
		break;
	default:
		analogWrite(pinNum, value);
		break;
	}
}
