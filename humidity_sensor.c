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
static uint8_t sens_st=0;


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




/*
 * 
 */


