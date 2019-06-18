//************************************************************************************************//
//*	Project:	This program illustrates the working of the library for the i2c Rotary 
//*	========	encoders from DUPPA on the PSOC microprocessors from Cypress 				
//*																				
//*	File:		main.c			 												
//*	Version:	1.0																
//*																				
//*	Authors:
//* ========
//* Original Arduino-version: 	Simone Caron
//* This PSOC version:			Rudy De Volder														
//*	LICENSE: GPL v3 (http://www.gnu.org/licenses/gpl.html)
//**********************************************************************************************//
//*		https://www.tindie.com/products/Saimon/i2cencoder-v2-connect-multiple-encoder-on-i2c-bus/	
//**********************************************************************************************//
//*																					
//*		Principles of Operation	:													
//*		=========================
//*     Since this software is written in C there is no Object oriented programming and 
//*     since this version is written for PSOC there is no Alloc & Malloc functionality.
//*		So memory must be reserved at compile-time:
//*		To reserve memory for a number of encoders =>
//*     make sure in the folowing header-file: "i2cEncoderLibV2.h" you define as follows: 
//*			#define MAX_IDX  to  nr of I2C_Encoders -1								
//*																		
//*		This version already includes Callback routines but it's partially commented out 
//*     because this implementation is not yet debugged. So POLLING is used instead.
//*																																		
//*																			
//********************************************************************************************//


/* 

PSoc CY8C4247AXI-M485
========================
GND     BRWN
PWR     RED
        ORANGE
        YELLOW
        WHITE

*/

/*
==========================================================================================
Color code of the LED's of the Rotary Encoder:  
==========================================================================================
==========================================================================================
Blue    - Control Left  linear actuator
Green   - Control Right linear actuator
White   - Control Both  linear actuators
Red		- Min/Max error
No LED  - Waiting direction after Dbl Push
Flashing -> Calibrate size of big steps
Dbl push -> + Within 1 second left or right => activate left or right actuator otherwise both actuators
Push + Turn -> Take big steps: Multiply step * 10

Problem with 2 actuators: increment/decrement positions with absolute values using wrapping

*/

//***********************************************************************************//
//**************** Libraries ********************************************************//
//***********************************************************************************//
#include <project.h>
#include <main.h>
#include <stdio.h>
#include "i2cEncoderLibV2.h"

Bool TestI2CAddress( uint8 Address );					//	Check for valid I2C address

void InitializeSystem(void)								//	Start all components, initialize  variables, perform self-test
{
	CyGlobalIntEnable;									//	Enable interrupt handling
	UART_Start();
	I2C_Start();
}
//***********************************************************************************//

static char Buffer[80];										//	UART line buffer

void CRLF() {
    	UART_UartPutChar(0x0d);	//	Cr
    	UART_UartPutChar(0x0a);	//	Lf
}
//Callback when the CVAL is incremented
void encoder_increment() {
            UART_UartPutString("Increment: ");
            sprintf (Buffer, "%i", i2cEnc__readCounterLong());
            UART_UartPutString(Buffer); CRLF();            
            // Write here your code  //
}
//Callback when the CVAL is decremented
void encoder_decrement() {
            UART_UartPutString("Decrement: ");
            sprintf (Buffer, "%i", i2cEnc__readCounterLong());
            UART_UartPutString(Buffer); CRLF();
            // Write here your code  //
}
//Callback when CVAL reach MAX
void encoder_max() {
            UART_UartPutString("Maximum threshold: ");
            sprintf (Buffer, "%i", i2cEnc__readCounterLong());
            UART_UartPutString(Buffer); CRLF();
			// Write here your code  //
}
//Callback when CVAL reach MIN
void encoder_min() {
            UART_UartPutString("Minimum threshold: ");
            sprintf (Buffer, "%i", i2cEnc__readCounterLong());
            UART_UartPutString(Buffer); CRLF();
            // Write here your code  //
}
//Callback when the encoder is pushed
void encoder_push() {
            UART_UartPutString("Push button Pressed"); CRLF();
            // Write here your code  //
			sprintf (Buffer, "encoder_activated = %i \n\r", encoder_activated);
			UART_UartPutString(Buffer);
			if (encoder_activated == 0 ) i2cEnc__writeStep_i((int32_t) 10);
}
//Callback when the encoder is released
void encoder_released() {
            UART_UartPutString("Push button Released"); CRLF();
            // Write here your code  //
			if (encoder_activated == 0 ) i2cEnc__writeStep_i((int32_t) 1);
}
//Callback when the encoder is double pushed
void encoder_double_push() {
            UART_UartPutString("Double push!"); CRLF();
            // Write here your code  //
}

int main()
{

	InitializeSystem();
	
	UART_UartPutChar(0x0C);	//	Clear screen
    
    i2cEnc__init(4); //Construct Encoder nr0 on address 4
	i2cEnc__reset();	
    /*
    // Definition of the callback-events for encoder nr 0:
	  i2cEnc__SetEvent(EV_ButtonRelease 	,encoder_released);
	  i2cEnc__SetEvent(EV_Increment 		,encoder_increment);
	  i2cEnc__SetEvent(EV_Decrement 		,encoder_decrement);
	  i2cEnc__SetEvent(EV_Max 				,encoder_max);
	  i2cEnc__SetEvent(EV_Min 				,encoder_min);
	  i2cEnc__SetEvent(EV_ButtonPush 		,encoder_push);
	  i2cEnc__SetEvent(EV_ButtonRelease 	,encoder_released);
	  i2cEnc__SetEvent(EV_ButtonDoublePush	,encoder_double_push); */

	      
    i2cEnc__init(5); //Construct Encoder nr1 on address 5
    i2cEnc__reset();
    
    /*
    // Definition of the callback-events for encoder nr 1:
	  i2cEnc__SetEvent(EV_ButtonRelease 	,encoder_released);
	  i2cEnc__SetEvent(EV_Increment 		,encoder_increment);
	  i2cEnc__SetEvent(EV_Decrement 		,encoder_decrement);
	  i2cEnc__SetEvent(EV_Max 				,encoder_max);
	  i2cEnc__SetEvent(EV_Min 				,encoder_min);
	  i2cEnc__SetEvent(EV_ButtonPush 		,encoder_push);
	  i2cEnc__SetEvent(EV_ButtonRelease 	,encoder_released);
	  i2cEnc__SetEvent(EV_ButtonDoublePush	,encoder_double_push);  */
     
    encoder_activated = 0; 
      //i2cEnc__begin( INT_DATA  | WRAP_DISABLE | DIRE_LEFT  | IPUP_ENABLE  | RMOD_X1 | RGB_ENCODER);
      //i2cEnc__begin( INT_DATA  | WRAP_DISABLE |              IPUP_ENABLE  | RMOD_X1 | STD_ENCODER); // try also this!
        i2cEnc__begin( INT_DATA  | WRAP_DISABLE | DIRE_RIGHT | IPUP_DISABLE | RMOD_X1 | RGB_ENCODER); // try also this!

      i2cEnc__writeCounter_i((int32_t) 0);  /* Reset the counter value */
      i2cEnc__writeMax_i((int32_t) 200);    /* Set the maximum threshold*/
      i2cEnc__writeMin_i((int32_t) -200);   /* Set the minimum threshold */
      i2cEnc__writeStep_i((int32_t) 1);     /* Set the step */
      i2cEnc__writeAntibouncingPeriod(20);  /* Set an anti-bouncing of 200ms */
      i2cEnc__writeDoublePushPeriod(50);    /* Set a period for the double push of 500ms */
    
  	  /* Enable the I2C Encoder V2 interrupts according to the previous attached callbacks */
	  //i2cEnc__autoconfigInterrupt();  
      i2cEnc__writeInterruptConfig(0xff);   /* //Polling: Enable all the interrupt */
	  
    
    encoder_activated = 1; 
      //i2cEnc__begin( INT_DATA  | WRAP_DISABLE | DIRE_LEFT  | IPUP_ENABLE  | RMOD_X1 | RGB_ENCODER);
      //i2cEnc__begin( INT_DATA  | WRAP_DISABLE |              IPUP_ENABLE  | RMOD_X1 | STD_ENCODER); // try also this!
        i2cEnc__begin( INT_DATA  | WRAP_DISABLE | DIRE_RIGHT | IPUP_ENABLE  | RMOD_X1 | RGB_ENCODER); // try also this!

      i2cEnc__writeCounter_i((int32_t) 1500);  // Reset the counter value 
      i2cEnc__writeMax_i((int32_t) 1768);     // Set the maximum threshold
      i2cEnc__writeMin_i((int32_t) -366);    // Set the minimum threshold 
      i2cEnc__writeStep_i((int32_t) 1);     // Set the step 
      i2cEnc__writeAntibouncingPeriod(20);  // Set an anti-bouncing of 200ms 
      i2cEnc__writeDoublePushPeriod(50);    // Set a period for the double push of 500ms 
  	  // Enable the I2C Encoder V2 interrupts according to the previous attached callbacks 
	  //i2cEnc__autoconfigInterrupt();
	  i2cEnc__writeInterruptConfig(0xff);   /* // Polling: Enable all the interrupt */
	
	
	/* blink RGB LED nr 0 */
	encoder_activated = 0;
		i2cEnc__writeFadeRGB(5); //Fade enabled with 5ms step
		i2cEnc__writeRGBCode(0xFF0000);
		CyDelay(600);
		i2cEnc__writeRGBCode(0x00FF00);
		CyDelay(600);
		i2cEnc__writeRGBCode(0x0000FF);
		CyDelay(600);
		i2cEnc__writeRGBCode(0x000000);
		i2cEnc__writeFadeRGB(3); //Fade enabled with 3ms step */
		
	
	/* blink RGB LED nr 1 */
	encoder_activated = 1;
		i2cEnc__writeFadeRGB(5); //Fade enabled with 5ms step
		i2cEnc__writeRGBCode(0xFF0000);
		CyDelay(600);
		i2cEnc__writeRGBCode(0x00FF00);
		CyDelay(600);
		i2cEnc__writeRGBCode(0x0000FF);
		CyDelay(600);
		i2cEnc__writeRGBCode(0x000000);
		i2cEnc__writeFadeRGB(3); //Fade enabled with 3ms step	
	
	UART_UartPutString("Program started\n\r");
    
    u_int8_t val = i2cEnc__readDoublePushPeriod();
    sprintf (Buffer, "DblPush period = %d", val);
    UART_UartPutString(Buffer);
    
	while(forever)							//	*** Main loop
	{

        for (encoder_activated = 0; encoder_activated < encoder_last_idx; encoder_activated++ ) {
            if (Encoder_INT_Read() == LOW) {
                          
                if (i2cEnc__updateStatus()) {
                    /* With polling : */
                      sprintf (Buffer, "\n\rDecoder %d: ", encoder_activated);     
                      UART_UartPutString(Buffer); 
                    
                      if (i2cEnc__readStatus_match(RINC)) {
                        UART_UartPutString("Increment: ");
                        sprintf (Buffer, "%d", i2cEnc__readCounterByte());
                        UART_UartPutString(Buffer); CRLF();
                        
                        // Write here your code  //

                      }
                      if (i2cEnc__readStatus_match(RDEC)) {
                        UART_UartPutString("Decrement: ");
                        sprintf (Buffer, "%d", i2cEnc__readCounterByte());
                        UART_UartPutString(Buffer); CRLF();
                        
                        // Write here your code  //

                      }

                      if (i2cEnc__readStatus_match(RMAX)) {
                        UART_UartPutString("Maximum threshold: ");
                        sprintf (Buffer, "%d", i2cEnc__readCounterByte());
                        UART_UartPutString(Buffer); CRLF();

                        // Write here your code  //

                      }

                      if (i2cEnc__readStatus_match(RMIN)) {
                        UART_UartPutString("Minimum threshold: ");
                        sprintf (Buffer, "%d", i2cEnc__readCounterByte());
                        UART_UartPutString(Buffer); CRLF();

                        // Write here your code  //

                      }
            		
                      if (i2cEnc__readStatus_match(PUSHP)) {
                        UART_UartPutString("Push button Pressed"); CRLF();

                        // Write here your code  //

                      }
            		
                      if (i2cEnc__readStatus_match(PUSHR)) {
                        UART_UartPutString("Push button Released"); CRLF();

                        // Write here your code  //

                      }

                      if (i2cEnc__readStatus_match(PUSHD)) {
                        UART_UartPutString("Double push!"); CRLF();

                        // Write here your code  //

                      } /* */
                }
            }
        }
	}
}
//***********************************************************************************//

Bool TestI2CAddress(uint8 Address) // to check a device is present on this i2c address
{ uint32 Status;
	Status = I2C_I2CMasterSendStart(Address,I2C_I2C_READ_XFER_MODE, I2C_TIMEOUT);
	I2C_I2CMasterSendStop(I2C_TIMEOUT);
	if(Status) return FALSE;							//	Status indicates error, so no address response
	return TRUE;										//	Status shows no error
}
//***********************************************************************************//



