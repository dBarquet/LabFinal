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
    
        while(1){
        
        if(USBGetDeviceState( )>=CONFIGURED_STATE){
        USB_Interface();
        } 
        
        switch(p_state){
            case(OPTIMO):
                Green_SetHigh(); 
                if(HumidityGetValue()<10){
                    p_state=SECO;
                    break;
                }
                else
                    if(HumidityGetValue()>20){
                        p_state=SATURADO;
                        break;
                    }
                if(LEDA_GetValue()==1 && HumidityGetValue()<15 ){
                    LEDA_SetLow();
                }
                break;
            case(SECO):
                
                if(HumidityGetValue()>=10 && HumidityGetValue()<=20){
                    p_state=OPTIMO;
                    break;
                }
                else if(HumidityGetValue()<10){
                        p_state=SATURADO;
                        break;
                    }
                else if(HumidityGetValue()>=30 && HumidityGetValue()<=40){
                 Yellow_SetHigh();
                }
                else if(HumidityGetValue()>=41){
                 Red_SetHigh();
                }
                    
                break;
            case(SATURADO):
                if(HumidityGetValue()>=10 && HumidityGetValue()<=20){
                    p_state=OPTIMO;
                    break;
                }
                else if(HumidityGetValue()<10){
                    p_state=SECO;
                    break;
                }
                else if(HumidityGetValue()>=6 && HumidityGetValue()<=9){
                 Yellow_SetHigh();
                }
                else if(HumidityGetValue()>=0 && HumidityGetValue()<=5){
                 Red_SetHigh();
                }
                break;
            
        }
            
        }
    
    
        return 0;

}

