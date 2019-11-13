#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <sys/attribs.h>     //MACROS ISRs
#include "mcc_generated_files/mcc.h"
#include "DateTime.h"


void iniciarSIM808() {
static uint8_t SIMstate=0;
uint8_t Buffer [254];
uint8_t SIM [4];
uint8_t length;
PWRKEY_SetDigitalInput();

switch(SIMstate) {
	
	case (0):
		PWRKEY_SetDigitalOutput();
		PWRKEY_SetLow();
		if( delayMs( 1000 ) == true ) {
			PWRKEY_SetDigitalInput();
            
			SIMstate=1;
		}
	break;
    
	case (1):
		if( delayMs( 2000 ) == true && GPS_STATUS_SetHigh()){
			SIMstate=2;
			}
	break;
	
	case (2):
        if (UART1_IsRxReady(void)) {
            UART1_WriteBuffer ( "A" ,  strlen ("A"));
        
	
    
    
    
    case (2):
	if (necesita sim) {
		Buffer='Ingrese SIM';
		putsUSBUSART( Buffer );
        CDCTxService( );
		SIMstate=3;
	}
	else SIMstate=4;
	break
	
	case (3):
		if(getsUSBUSART( Buffer, length )!=0 ){
				memccpy(Buffer, SIM, 4);
			meter el sim en modulo
			SIMstate=4;
		}
	break
	
	case (4):
	GPS
}}
}