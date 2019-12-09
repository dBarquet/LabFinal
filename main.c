/* 
 * File:   main.c
 * Author: Diego
 *
 * Created on 6 de noviembre de 2019, 11:42 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <sys/attribs.h>     //MACROS ISRs
#include "mcc_generated_files/mcc.h"
#include "WS2812.h"
#include "humidity_sensor.h"
/*
 * 
 */
int main(void) {
    
    SYSTEM_Initialize();
    static plant_state p_state= OPTIMO;
    static uint16_t humidity=40;
    ut_tmrDelay_t timer1;
    timer1.state = 0;
    
        while(1){
        
        if (UT_delayDs(&timer1,10)==true) {
        
        LEDA_SetHigh(); 
        humidity=HumidityGetValue();
        }
        
        if(USBGetDeviceState( )>=CONFIGURED_STATE){
        USB_Interface();
        } 
        //humidity=Hum();
        switch(p_state){
            case(OPTIMO):
                Green_SetHigh(); 
                //humidity=HumidityGetValue();
                if(humidity<10){
                    p_state=SATURADO;
                    break;
                }
                else
                    if(humidity>30){
                        p_state=SECO;
                        break;
                    }
                if(LEDA_GetValue()==1 && humidity<15 ){
                    LEDA_SetLow();
                }
                break;
            case(SECO):
                //humidity=HumidityGetValue();
                if(humidity>=10 && humidity<=30){
                    p_state=OPTIMO;
                    break;
                }
                else if(humidity<10){
                        p_state=SATURADO;
                        break;
                    }
                else if(humidity>=30 && humidity<=40){
                 Yellow_SetHigh();
                }
                else if(humidity>=41){
                 Red_SetHigh();
                }
                    
                break;
            case(SATURADO):
                //humidity=HumidityGetValue();
                if(humidity>=10 && humidity<=30){
                    p_state=OPTIMO;
                    break;
                }
                else if(humidity>30){
                    p_state=SECO;
                    break;
                }
                else if(humidity>=6 && humidity<=9){
                 Yellow_SetHigh();
                }
                else if(humidity>=0 && humidity<=5){
                 Red_SetHigh();
                }
                break;
            
        }
            
        }
    
    
        return 0;

}

