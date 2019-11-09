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
/*
 * 
 */
int main(void) {
   
    SYSTEM_Initialize();
        while(1){
            
        if(USBGetDeviceState( )>=CONFIGURED_STATE){
      
        USB_Interface();
       
        }  
            
        }
        return 0;

}

