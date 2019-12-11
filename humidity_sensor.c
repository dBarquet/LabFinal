/* 
 *
 * Created on 9 de noviembre de 2019, 12:30 PM
 * 
 *Sensor de humedad simulado con el potenciómetro
 * Conversor A/D
 * funciones de GetValue
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "../stdbool.h"
#include "humidity_sensor.h"
#include "mcc_generated_files/adc1.h"
#include "mcc_generated_files/tmr2.h"


uint16_t conversion;
static uint8_t sens_st=0;


/*
uint16_t  HumidityGetValue(){

    switch(sens_st){
                case(0):                   
                    ADC1_ChannelSelect(ADC1_POTN);
                    ADC1_Start();
                    sens_st=1;                
                    ADC1_Stop();                  
                    break;
                    
                case(1):     
                    
                    if(ADC1_IsConversionComplete()==AD1CON1bits.DONE){ 
                       conversion= ADC1_ConversionResultGet()/17.05;
                       sens_st=0;
                       return conversion;                  
                    }
                    break;
}
}
 
*/
uint16_t  HumidityGetValue(){ 
    conversion= ADC1_ConversionResultGet()/17.05;
    return conversion; 

}

/*
uint16_t Humidity_Check(){
            if (UT_delayDs(ptimer1,50)==true) {
            LEDA_SetHigh(); 
            if(IsConversionDone()==true){
                humidity=HumidityGetValue();
            }
        }
    
}*/

bool IsConversionDone(){
    switch(sens_st){
                case(0):                   
                    ADC1_ChannelSelect(ADC1_POTN);
                    ADC1_Start();
                    sens_st=1;                
                    ADC1_Stop();                  
                    return false;
                    
                case(1):                         
                    if(ADC1_IsConversionComplete()==AD1CON1bits.DONE){ 
                       sens_st=0;
                       return true;                  
                    }
    }
}


plant_state Change_PlantState(plant_state p_state,humidity_thresholds h_t, uint16_t humidity){
    if(p_state==OPTIMO){
                if(humidity <= h_t.t_not_too_sat){
                    return SATURADO;
                }
                else if(humidity>=h_t.t_not_too_dry){
                    return SECO;
                }
                else
                    return OPTIMO;
    }
    if(p_state==SATURADO){
                if(humidity>h_t.t_not_too_sat && humidity<h_t.t_not_too_dry){
                    return OPTIMO;
                }
                else if(humidity>=h_t.t_not_too_dry){
                    return SECO;
                }
                else
                    return SATURADO;
    }
    if(p_state==SECO){
                if(humidity>h_t.t_not_too_sat && humidity<h_t.t_not_too_dry){
                    return OPTIMO;
                }
                else if(humidity<=h_t.t_not_too_sat){
                    return SATURADO;
                }
                else
                    return SECO;
    }
}




/*
 * 
 */


