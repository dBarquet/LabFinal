/* ************************************************************************** */
/** Descriptive File Name

 * 
/* ************************************************************************** */
/* Section: Included Files                                                    */

#include "usb_interface.h" 
#include "mcc_generated_files/mcc.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>


// Section: Functions                                               
/* ************************************************************************** */
uint8_t Entered_Data [254];
uint8_t largo;
static interface_state_t ESTADO = MENU;
static uint8_t menu_st=0;
static int selection=0;

void USB_Interface(){
    
    CDCTxService();
    memset(Entered_Data,0,sizeof(Entered_Data));
    largo=254;
    
    switch(ESTADO){
        case(MENU):
            menu_st=0;
            menu();
            break;
            
        case(FIJAR_HORA):
        if(DateTime_Set()==true){
        ESTADO=MENU;
        }           
        break;   
    }
    
}

void menu(){
    switch(menu_st){
        case(0):
                if(mostrar("Menu: \n 1- Fijar hora \n 2- Consultar hora \n 3- Agregar planta \n 4- Setear colores para umbrales de humedad \n 5- Ingresar telefono ")==true){
                selection=0;
                menu_st=1;
                }
                break;
        case (1):
                if(USBGetDeviceState( )>=CONFIGURED_STATE){
                    if(getsUSBUSART( Entered_Data, largo )!=0 ){
                        selection=atoi(Entered_Data);
                        memset(Entered_Data,0,sizeof(Entered_Data));
                    }
                }
                else
                break;
                
                switch(selection){
                    case(0):
                        break;
                    case(1): 
                        ESTADO=FIJAR_HORA;
                        break;
                    case(2):
                        ESTADO=CONSULTAR_HORA;
                        break;
                    case(3):
                        ESTADO= AGREGAR_PLANTA;
                        break;
                    case(4):
                        ESTADO= SETEAR_UMBRALES_COLORES;
                        break;
                    case(5):   
                        ESTADO= INGRESAR_TELEFONO;
                        break;
                }
    }
    
}


bool mostrar(char *data) {
        if(USBGetDeviceState( )>=CONFIGURED_STATE){
    if(USBUSARTIsTxTrfReady( )){
        putsUSBUSART(data );
        return true;
    }
    else return false;
}
        else return false;
        }

/* *****************************************************************************
 End of File
 */
