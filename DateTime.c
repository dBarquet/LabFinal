
/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */
#include "mcc_generated_files/mcc.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "mcc_generated_files/tmr2.h"


struct tm TimeInit;
uint8_t Entered_Data [254];
uint8_t largo;
static uint8_t state=0;

/* TODO:  Include other files here if needed. */

bool set_Year(){
    if(USBGetDeviceState( )>=CONFIGURED_STATE){
    if(getsUSBUSART( Entered_Data, largo )!=0 ){
                TimeInit.tm_year=atoi(Entered_Data);
                memset(Entered_Data,0,sizeof(Entered_Data)); 
                return true;
                    } 
    else
                return false;
    }
    return false;
}

            
bool set_Month(){
            if(USBGetDeviceState( )>=CONFIGURED_STATE){
            if(getsUSBUSART( Entered_Data, largo )!=0 ){
                TimeInit.tm_mon=atoi(Entered_Data);
                memset(Entered_Data,0,sizeof(Entered_Data));
                return true;
                    }      
            else
                return false;
            }
            return false;
            }

bool set_Day(){
            if(USBGetDeviceState( )>=CONFIGURED_STATE){
            if(getsUSBUSART( Entered_Data, largo )!=0 ){
                TimeInit.tm_mday=atoi(Entered_Data);
                memset(Entered_Data,0,sizeof(Entered_Data));
                return true;
            }                
               return false; 
            }
            return false;
            }
bool set_Hour(){
            if(USBGetDeviceState( )>=CONFIGURED_STATE){
            if(getsUSBUSART( Entered_Data, largo )!=0 ){
                TimeInit.tm_hour=atoi(Entered_Data);
                memset(Entered_Data,0,sizeof(Entered_Data));
                return true;
            }
    return false;
}
            return false;
}

bool set_Minute(){
            if(USBGetDeviceState( )>=CONFIGURED_STATE){
            if(getsUSBUSART( Entered_Data, largo )!=0 ){
                TimeInit.tm_min=atoi(Entered_Data);
                memset(Entered_Data,0,sizeof(Entered_Data));
                return true;
            }
    return false;
}
            return false;
}


bool DateTime_Set(){
                
                CDCTxService();
                switch(state){
                case(0):
                    mostrar("Configuración de fecha y hora: \n Ingrese año:");
                    state=1;
                    break;
                
                case(1):
                    if(set_Year()==true){
                        state=2;     
                    }
                    break;
        
                case(2):
                    mostrar("Ingrese mes:"); 
                    state=3;
                    break;
                    
                case(3):
                    if(set_Month()==true){
                        state=4;
                    }
                        break;
                        
                case(4):
                    mostrar("Ingrese día:");
                    state=5;
                    break;
                    
                case(5):
                    if(set_Day()==true){
                        state=6;
                    }   
                    break;                
                    
                case(6):
                    mostrar("Ingrese hora (HH):");
                    state=7;
                    break;
                    
                case(7):
                    if(set_Hour()==true){
                        state=8;}
                        break;
                          
                case(8):
                    mostrar("Ingrese minutos (MM):");
                    state=9;
                    break;
                
                case(9):
                    if(set_Minute()==true){
                    RTCC_TimeSet(&TimeInit);
                    state=10;
                    }
                    break;
            

}
if(state != 10){
    return false;
}    
else{ 
    state=0;
    return true;
}
}


/*
bool UT_delayDs(ut_tmrDelay_t* p_timer, uint8_t p_ds){
    switch ( p_timer->state ) {
        case (0):
            p_timer -> startValue = TMR2_SoftwareCounterGet ();
            p_timer -> state = 1;
            return false;
        case (1): 
            if (TMR2_SoftwareCounterGet () >= (p_timer->startValue + p_ds)){
                p_timer->state = 0;
                return true;}
            else {          
                return false;
            }
    }
}
//

*/
bool delayMs( uint32_t p_delay )
{
	static uint8_t delayState = 0;
	static uint32_t startValue=0;
	
	switch( delayState )
	{
		case 0:
			startValue = TMR2_SoftwareCounterGet ();
			delayState = 1;
			break;
		case 1:
			if( TMR2_SoftwareCounterGet () >= (startValue+p_delay) )
			{
				return true;
			}
			break;
	}
	return false;
}

 /* 
 * 
 * 
 * 
 * 
 * 
bool UT_delayDs(ut_tmrDelay_t* p_timer, uint16_t p_ds){
    switch ( p_timer->state ) {
        case (0):
            //p_timer -> startValue = TMR2_SoftwareCounterGet ();
            p_timer -> startValue = TMR2_Counter16BitGet();
            p_timer -> state = 1;
            return false;
        case (1): 
            //if (TMR2_SoftwareCounterGet () < (p_timer->startValue + p_ds))
            if (TMR2_Counter16BitGet() < (p_timer->startValue + p_ds))
                return false;
            else {
                p_timer->state = 0;
                return true;
            }
    }
}
//


bool delayMs( uint32_t p_delay )
{
	static uint8_t delayState = 0;
	static uint32_t startValue=0;
	
	switch( delayState )
	{
		case 0:
			startValue = TMR2_SoftwareCounterGet ();
			delayState = 1;
			break;
		case 1:
			if( TMR2_SoftwareCounterGet () >= (startValue+p_delay) )
			{
				return true;
			}
			break;
	}
	return false;
}
*/




/* *****************************************************************************
 End of File
 */
