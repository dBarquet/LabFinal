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
#include "utils.h"

/*
 * 
 */
int main(void) {
    
    SYSTEM_Initialize();
    static plant_state p_state= OPTIMO;
    uint16_t humidity;
   /* 
    static ut_tmrDelay_t timer1;   
    timer1.startValue = 0;
    timer1.state = 0;
     */   
    

    static ut_tmrDelay_t p1;
    //static ut_tmrDelay_t p2;
    //p2.state=UT_TMR_DELAY_INIT;
    p1.state=UT_TMR_DELAY_INIT;
    
    //default values
    thres_colors colors;
    colors.Dry_color=RED;
    colors.Not_too_Dry_color=BLUE;
    colors.Opt_color=GREEN;
    colors.Not_too_sat_color=YELLOW;
    colors.Sat_color=WHITE;
    
    humidity_thresholds h_t;
    h_t.t_dry=41;
    h_t.t_not_too_dry=21;
    h_t.t_sat=5;
    h_t.t_not_too_sat=9;
    
        while(1){
        
     //   if (UT_delayDs(ptimer1,50)==true) {
     //       LEDA_SetHigh(); 
            if(IsConversionDone()==true){
                humidity=HumidityGetValue();
            }
//        }
        if (UT_delayDs(&p1,50)==true) {
            LEDA_SetHigh(); 
        }

        
        if(USBGetDeviceState( )>=CONFIGURED_STATE){
        USB_Interface();
        } 
        
        Plant_State_Color(colors,humidity);
        
        
        switch(p_state){
            case(OPTIMO):
                /*if(IsConversionDone()==true){
                humidity=HumidityGetValue();}
                else
                    break;*/
                p_state=Change_PlantState(OPTIMO, h_t, humidity);
                 break;   
                
                if(LEDA_GetValue()==1 && humidity<15 ){
                    LEDA_SetLow();
                }
                break;
                
            case(SECO):
                /*
                if(IsConversionDone()==true){
                humidity=HumidityGetValue();}
                else
                    break;*/
                p_state=Change_PlantState(SECO, h_t, humidity);
                break;
                
            case(SATURADO):
                /*
                if(IsConversionDone()==true){
                humidity=HumidityGetValue();}
                else
                    break;*/
                p_state=Change_PlantState(SATURADO, h_t, humidity);
                break;
            
        }            
        }
    
        return 0;

}

