/* 
 * File:   main.c
 * Author: Diego
 *
 * Created on 6 de noviembre de 2019, 11:42 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <xc.h>
#include <sys/attribs.h>     //MACROS ISRs
#include "mcc_generated_files/mcc.h"
#include "WS2812.h"
#include "humidity_sensor.h"
#include "DateTime.h"

/*
 * 
 */
int main(void) {
    
    SYSTEM_Initialize();
    static plant_state p_state= OPTIMO;
    uint16_t humidity;
    //humidity=30;
    ut_tmrDelay_t timer1;
    timer1.state = 0;
    //timer1.startValue = 0;
    
        while(1){
        if (UT_delayDs(&timer1,10)==true) {
        
        LEDA_SetHigh(); 
        humidity=HumidityGetValue();
        }
        
        if(USBGetDeviceState( )>=CONFIGURED_STATE){
        USB_Interface();
        } 
        
        switch(p_state){
            case(OPTIMO):
                Green_SetHigh();
                if(IsConversionDone()==true){
                humidity=HumidityGetValue();}
                else
                    break;
                if(humidity<10){
                    p_state=SATURADO;
                    break;
                }
                if(humidity>30){
                    p_state=SECO;
                    break;
                }
                if(LEDA_GetValue()==1 && humidity<15 ){
                    LEDA_SetLow();
                }
                break;
                
            case(SECO):
                if(IsConversionDone()==true){
                humidity=HumidityGetValue();}
                else
                    break;
                
                if(humidity>=31 && humidity<=40){
                 Yellow_SetHigh();
                }
                if(humidity>=41){
                 Red_SetHigh();
                }  
                /**/
                if(humidity>=10 && humidity<=30){
                    p_state=OPTIMO;
                    break;
                }
                if(humidity<10){
                    p_state=SATURADO;
                    break;
                }

                break;
                
            case(SATURADO):
                if(IsConversionDone()==true){
                humidity=HumidityGetValue();}
                else
                    break;
                if(humidity>=6 && humidity<=9){
                 Yellow_SetHigh();
                }
                if(humidity<=5){
                 Red_SetHigh();
                }
                if(humidity>=10 && humidity<=30){
                    p_state=OPTIMO;
                    break;
                }
                if(humidity>30){
                    p_state=SECO;
                    break;
                }
                break;
            
        }
            
        }
    
    
        return 0;

}

