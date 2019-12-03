#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xc.h>
#include <sys/attribs.h>     //MACROS ISRs
#include "mcc_generated_files/mcc.h"
#include "DateTime.h"


void iniciarSIM808() {
static uint8_t SIMstate=0;
uint8_t rxBuffer [254];
uint8_t txBuffer [254];
uint8_t PIN [4];
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
        if (UART1_IsRxReady()) {
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
                if ( delayMs( 1000 ) == true) {
                 SIMstate=2;
                }
        break;
        
    case (5):
        strcpy(txBuffer, "AT+CPIN?\r");
        UART1_WriteBuffer ( txBuffer ,  strlen (txBuffer));
        SIMstate=6;
        break;
    
    case (6):
        if (UART1_ReadBuffer ( "\r\nOK\r\n" , strlen("\r\nOK\r\n") ) == 0){
            SIMstate=7;
        }
        else
            if ( delayMs( 1000 ) == true) {
                 SIMstate=5;
                }
        break;
        
    case (7):
        if (UART1_ReadBuffer ( &rxBuffer , strlen(rxBuffer) ) == 0){
            memset(txBuffer,0,sizeof(txBuffer));
            strcpy(txBuffer,"READY");
                    if ((memcmp(rxBuffer, txBuffer, 5)) == 0) {
                        SIMstate=9;
                        strcpy(txBuffer,"AT+COPS=1,2,\"74801\"\r");
                        UART1_WriteBuffer ( txBuffer ,  strlen (txBuffer));
                    }
                    else
                        strcpy(txBuffer,"SIM PIN");
                        if ((memcmp(rxBuffer, txBuffer, 5)) == 0){
                            SIMstate=8;
                            strcpy(txBuffer,"AT+CPIN=1234\r");
                            UART1_WriteBuffer ( txBuffer ,  strlen (txBuffer));                        
                        }
        }
        break;
    
    case (8):
        if (UART1_ReadBuffer ( "\r\nOK\r\n" , strlen("\r\nOK\r\n") ) == 0){
            SIMstate=9;
            strcpy(txBuffer,"AT+COPS=1,2,\"74801\"\r");
            UART1_WriteBuffer ( txBuffer ,  strlen (txBuffer));
            }
        else                                        //Ver si este achique esta bien
                if ( delayMs( 1000 ) == true) {
                 SIMstate=6;
                }
        break;
	
    case (9):
        strcpy(txBuffer,"AT+CGNSPWR=1\r");
        UART1_WriteBuffer ( txBuffer ,  strlen (txBuffer));
        SIMstate=10;
        break;
        //Ver si aca se pone achique de cuando le mandas la prendida a recibir el ok
    case (10):
        if (UART1_ReadBuffer ( "\r\nOK\r\n" , strlen("\r\nOK\r\n") ) == 0){
            SIMstate=11;
        }
        else
                if ( delayMs( 1000 ) == true) {
                 SIMstate=9;
                }
        break;
        
    case (11):
        strcpy(txBuffer,'AT+CGNSSEQ="RMC"\r');
        UART1_WriteBuffer ( txBuffer ,  strlen (txBuffer));
        SIMstate=12;
        break;
        
    case (12):
        if (UART1_ReadBuffer ( "\r\nOK\r\n" , strlen("\r\nOK\r\n") ) == 0){
            SIMstate=13;
            }    
        else
                if ( delayMs( 1000 ) == true) {
                 SIMstate=11;
                }
        break;
        
       
    case (13):
        break;
}}

