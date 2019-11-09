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


uint16_t conversion;

bool ADconv (){
    
    ADC1_ChannelSelect(ADC1_POTN);
    ADC1_Start();
    if (ADC1_IsConversionComplete()==true){
    return true;   
    }
    else 
        return false;
} 

uint16_t  HumidityGetValue(){
     conversion= ADC1_ConversionResultGet()/17.05;  
     return conversion;
}




/*
 * 
 */


