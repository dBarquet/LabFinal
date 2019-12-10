#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xc.h>
#include <sys/attribs.h>     //MACROS ISRs
#include "mcc_generated_files/mcc.h"
#include "DateTime.h"
#include "sim.h"

volatile bool SIMok=false;

void iniciarSIM808() {
static uint8_t SIMstate=0;
uint8_t rxBuffer [254];
uint8_t txBuffer [254];
uint8_t length;
PWRKEY_SetDigitalInput();
ut_tmrDelay_t timer2;
ut_tmrDelay_t *ptimer2;
ptimer2->state = 0;
ptimer2->startValue = 0;

switch(SIMstate) {
	
	case (0):
		PWRKEY_SetDigitalOutput();
		PWRKEY_SetLow();
        
    case (1):
		if( UT_delayDs(ptimer2,10) == true ) {
			PWRKEY_SetDigitalInput();          
			SIMstate=2;
		}
    SIMstate=1;
	break;
    
	case (2):
		if( UT_delayDs(ptimer2, 20 ) == true && GPS_STATUS_GetValue() == 1){
			SIMstate=3;
			}
	break;
	
	case (3):
        if (UART1_IsRxReady()) {
            memset(txBuffer,0,sizeof(txBuffer));
            strcpy(txBuffer, "A");
            UART1_WriteBuffer ( txBuffer ,  strlen (txBuffer));
			SIMstate=4;
        }
    break;
        
    case (4):
        if ( UT_delayDs(ptimer2, 40 ) == true) {
            memset(txBuffer,0,sizeof(txBuffer));
            strcpy(txBuffer, "AT\r" );
            UART1_WriteBuffer ( txBuffer ,  strlen (txBuffer));
            SIMstate=5;
        }
    break;            
    
    case (5):
        UART1_ReadBuffer ( rxBuffer , 1 );
        memset(txBuffer,0,sizeof(txBuffer));
        strcpy(txBuffer,"\r\nOK\r\n");
            if ((memcmp(rxBuffer, txBuffer, strlen (txBuffer))) == 0) {
            SIMstate=6;
            }
            else
                if ( UT_delayDs(ptimer2, 10 ) == true) {
                 SIMstate=3;
                }
        break;
        
    case (6):
        memset(txBuffer,0,sizeof(txBuffer));
        strcpy(txBuffer, "AT+CPIN?\r");
        UART1_WriteBuffer ( txBuffer ,  strlen (txBuffer));
        SIMstate=8;
        break;
    
   
    case (8):
        if (UART1_ReadBuffer ( rxBuffer , 1 ) == 0){
            memset(txBuffer,0,sizeof(txBuffer));
            strcpy(txBuffer,"+CPIN:READY\r\n\r\nOK\r\n");
                    if ((memcmp(rxBuffer, txBuffer, strlen (txBuffer))) == 0) {
                        SIMstate=10;
                        memset(txBuffer,0,sizeof(txBuffer));
                        strcpy(txBuffer,"AT+COPS=1,2,\"74801\"\r");
                        UART1_WriteBuffer ( txBuffer ,  strlen (txBuffer));
                    }
                    else
                        memset(txBuffer,0,sizeof(txBuffer));
                        strcpy(txBuffer,"+CPIN:SIM PIN\r\n\r\nOK\r\n");
                        if ((memcmp(rxBuffer, txBuffer, strlen (txBuffer))) == 0){
                            SIMstate=9;
                            memset(txBuffer,0,sizeof(txBuffer));
                            strcpy(txBuffer,"AT+CPIN=5136\r");
                            UART1_WriteBuffer ( txBuffer ,  strlen (txBuffer));                        
                        }
        }
        break;
    
    case (9):
        UART1_ReadBuffer ( rxBuffer , 1 );
        memset(txBuffer,0,sizeof(txBuffer));
        strcpy(txBuffer,"\r\nOK\r\n");
            if ((memcmp(rxBuffer, txBuffer, strlen (txBuffer))) == 0){
            SIMstate=10;
            memset(txBuffer,0,sizeof(txBuffer));
            strcpy(txBuffer,"AT+COPS=1,2,\"74801\"\r");
            UART1_WriteBuffer ( txBuffer ,  strlen (txBuffer));
            }
        else                                        
                if ( UT_delayDs(ptimer2, 10 ) == true) {
                 SIMstate=6;
                }
        break;
	
    case (10):
        memset(txBuffer,0,sizeof(txBuffer));
        strcpy(txBuffer,"AT+CGNSPWR=1\r");
        UART1_WriteBuffer ( txBuffer ,  strlen (txBuffer));
        SIMstate=11;
        break;
        //Ver si aca se pone achique de cuando le mandas la prendida a recibir el ok
    case (11):
        UART1_ReadBuffer ( rxBuffer , 1 );
        memset(txBuffer,0,sizeof(txBuffer));
        strcpy(txBuffer,"\r\nOK\r\n");
            if ((memcmp(rxBuffer, txBuffer, strlen (txBuffer))) == 0){
            SIMstate=12;
        }
        else
                if ( UT_delayDs(ptimer2, 10 ) == true) {
                 SIMstate=10;
                }
        break;
        
    case (12):
        memset(txBuffer,0,sizeof(txBuffer));
        strcpy(txBuffer,'AT+CGNSSEQ="RMC"\r');
        UART1_WriteBuffer ( txBuffer ,  strlen (txBuffer));
        SIMstate=13;
        break;
        
    case (13):
        UART1_ReadBuffer ( rxBuffer , 1 );
        memset(txBuffer,0,sizeof(txBuffer));
        strcpy(txBuffer,"\r\nOK\r\n");
            if ((memcmp(rxBuffer, txBuffer, strlen (txBuffer))) == 0){
            SIMstate=14;
            }    
        else
                if ( UT_delayDs(ptimer2, 10 ) == true) {
                 SIMstate=12;
                }
        break;
        
       
    case (14):
      SIMok=true;
        break;
}}


bool checkSIM808 () {

	if (SIMok=true && GPS_STATUS_GetValue() == 1){
        return true;
    }
    else
        return false;
}
        
