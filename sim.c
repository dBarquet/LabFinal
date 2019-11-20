#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
			SIMstate=3;
        }
    break;
        
    case (3):
        if ( delayMs( 4000 ) == true) {
            UART1_WriteBuffer ( "AT\r" ,  strlen ("AT\r"));
            SIMstate=4;
        }
    break;            
    
    case (4):
        if (UART1_ReadBuffer ( "\r\nOK\r\n" , strlen("\r\nOK\r\n") ) == 0){
            SIMstate=5;
            }
            else
                if ( delayMs( 3000 ) == true) {
                 SIMstate=3;
                }
        break;
        

	
    
    
    
    case (5):
        UART1_WriteBuffer ( "AT+CPIN?\r" ,  strlen ("AT+CPIN?\r"));
        
        
        if (necesita sim) {
		//Buffer='Ingrese SIM';
		//putsUSBUSART( Buffer );
        //CDCTxService( );
		memccpy(Buffer, SIM, 4);
            SIMstate=6;
/*	}
	else SIMstate=7;
	break;
	
	case (6):
		if(getsUSBUSART( Buffer, length )!=0 ){
				memccpy(Buffer, SIM, 4);
			meter el sim en modulo
			SIMstate=7;
*/		}
	break
	
	case (6):
	GPS
}}
}