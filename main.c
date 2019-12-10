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
#include "sim.h"
/*
 * 
 */
int main(void) {
    
    SYSTEM_Initialize();
    static volatile plant_state p_state= OPTIMO;
    uint16_t humidity;
    
    uint8_t timer1;
    ut_tmrDelay_t* ptimer1;
    ptimer1=&timer1;
   // ptimer1->startValue = 0;
    ptimer1->state = 0;
    LEDA_SetLow();

    
        while(1){
            
        if (UT_delayDs(ptimer1,1)==true) {
        LEDA_SetHigh(); 
            if(IsConversionDone()==true){
                    humidity=HumidityGetValue();
            }
        }
        
        if(USBGetDeviceState( )>=CONFIGURED_STATE){
        USB_Interface();
        } 
        
        Plant_State_Color(GREEN,RED,WHITE,humidity);
        
        
        switch(p_state){
            case(OPTIMO):
                if(IsConversionDone()==true){
                humidity=HumidityGetValue();}
                else
                    break;
                p_state=Change_PlantState(OPTIMO, humidity);
                 break;   
                
                if(LEDA_GetValue()==1 && humidity<15 ){
                    LEDA_SetLow();
                }
                break;
                
            case(SECO):
                if(IsConversionDone()==true){
                humidity=HumidityGetValue();}
                else
                    break;
                p_state=Change_PlantState(OPTIMO, humidity);
                break;
                
            case(SATURADO):
                if(IsConversionDone()==true){
                humidity=HumidityGetValue();}
                else
                    break;
                p_state=Change_PlantState(OPTIMO, humidity);
                break;
            
        }            
        }
    
        return 0;

}

