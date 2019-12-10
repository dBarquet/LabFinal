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
#include "DateTime.h"
#include "humidity_sensor.h"


// Section: Functions                                               
/* ************************************************************************** */
uint8_t Entered_Data [254];
uint8_t largo;
uint16_t conversion;
static interface_state_t ESTADO = MENU;
static uint8_t menu_st=0;
//static uint8_t sens_st=0;
static uint8_t set_st=0;
int umbral_seco;
int umbral_optimo;
int umbral_saturado;
int color_seco;
int color_optimo;
int color_optimo;
static int selection=0;
static uint8_t mostrar_st=0;
char H [100];
char M [100];
char sens [100];
struct tm CurrentTime;
uint16_t conv;



void USB_Interface(){
    
    CDCTxService();
    memset(Entered_Data,0,sizeof(Entered_Data));
    memset(sens,0,sizeof(sens));
    conversion=0;
    largo=254;
    
    switch(ESTADO){
        case(MENU):
            menu();
            break;
            
        case(FIJAR_HORA):
        if(DateTime_Set()==true){
        ESTADO=MENU;
        menu_st=0;
        }           
        break;  
        
        case(CONSULTAR_HORA):
            CDCTxService( );
            RTCC_TimeGet(&CurrentTime);
                int HH=CurrentTime.tm_hour;
                int MM=CurrentTime.tm_min;
                if(mostrar_Varios("\nLa hora es: ",itoa(H,HH,10),":",itoa(M,MM,10),"\n")==true){
                    menu_st=0;
                    ESTADO=MENU;
                    
                }      
        break;
     
        case(VALOR_SENSOR):
            if(IsConversionDone()==true){
                    conv=HumidityGetValue();
            
            
            if(mostrar(itoa(sens,conv,10))==true){
            menu_st=0;
            ESTADO=MENU;
            }
            }

        break;
        
        case(SETEAR_UMBRALES_COLORES):
            switch(set_st){
                case(0):
                    if(mostrar(" Ingrese valor de humedad de suelo SECO (entre 0Cb-60Cb): ")==true){
                    set_st=1;
                    }
                break;
                
                case(1):
                    if(USBGetDeviceState( )>=CONFIGURED_STATE){
                        if(getsUSBUSART( Entered_Data, largo )!=0 ){
                        umbral_seco=atoi(Entered_Data);
                        memset(Entered_Data,0,sizeof(Entered_Data));
                        set_st=2;
                        break;
                        }
                    }
                    else
                break;
                    
                case(2):
                    if(mostrar(" Ingrese color para indicar suelo SECO: \n 1- Rojo \n 2- Blanco \n 3- Verde \n 4- Azul \n 5- Amarillo ")==true){
                    set_st=3;
                    }
                break;
                
                case(3):
                        if(USBGetDeviceState( )>=CONFIGURED_STATE){
                        if(getsUSBUSART( Entered_Data, largo )!=0 ){
                        color_seco=atoi(Entered_Data);
                        memset(Entered_Data,0,sizeof(Entered_Data));
                        set_st=4;
                        break;
                        }
                    }
                    else
                break;
                        
                case(4):
                        if(mostrar(" Ingrese valor de humedad de suelo SATURADO (entre 0Cb-60Cb): ")==true){
                        set_st=5;
                        }
                break;
                
                case(5):
                    if(USBGetDeviceState( )>=CONFIGURED_STATE){
                        if(getsUSBUSART( Entered_Data, largo )!=0 ){
                        umbral_saturado=atoi(Entered_Data);
                        memset(Entered_Data,0,sizeof(Entered_Data));
                        set_st=6;
                        break;
                        }
                    }
                    else
                break;
                    
                case(6):
                    if(mostrar(" Ingrese color para indicar suelo SATURADO: \n 1- Rojo \n 2- Blanco \n 3- Verde \n 4- Azul ")==true){
                    set_st=7;
                    }
                break;
                            
                case(7):
                        if(USBGetDeviceState( )>=CONFIGURED_STATE){
                        if(getsUSBUSART( Entered_Data, largo )!=0 ){
                        color_seco=atoi(Entered_Data);
                        memset(Entered_Data,0,sizeof(Entered_Data));
                        set_st=8;
                        break;
                        }
                    }
                    else
                break;
                        
                case(8):
                    if(mostrar(" Ingrese color para indicar suelo OPTIMO: \n 1- Rojo \n 2- Blanco \n 3- Verde \n 4- Azul ")==true){
                    set_st=9;
                    }
                break;
                
                case(9):
                        if(USBGetDeviceState( )>=CONFIGURED_STATE){
                        if(getsUSBUSART( Entered_Data, largo )!=0 ){
                        color_optimo=atoi(Entered_Data);
                        memset(Entered_Data,0,sizeof(Entered_Data));
                        set_st=0;
                        menu_st=0;
                        ESTADO=MENU;
                        break;
                        }
                    }
                    else
                break;
        }
        break;
            
    }
}
    


void menu(){
    switch(menu_st){
        case(0):
                if(mostrar("Menu: \n 1- Fijar hora \n 2- Consultar hora \n 3- Agregar planta \n 4- Setear umbrales de humedad y colores \n 5- Ingresar telefono \n 6- Consultar valor sensor ")==true){
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
                    case(6):   
                        ESTADO= VALOR_SENSOR;
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

bool mostrar_Varios(char *data0,char *data1,char *data2,char *data3,char *data4){
    switch(mostrar_st){
        case 0: if(mostrar(data0)==true){
            mostrar_st=1;
            return false;
        }
        break;
        
        case 1: if(mostrar(data1)==true){
            mostrar_st=2;
            return false;
        }
        break;
        
        case 2: if(mostrar(data2)==true){
            mostrar_st=3;
            return false;
        }
        break;
        
        case 3: if(mostrar(data3)==true){
            mostrar_st=4;
            return false;
        }
        break;
        
        case 4: if(mostrar(data4)==true){
            mostrar_st=0;
            return true;   
        }
        break;
    } 
}

/* *****************************************************************************
 End of File
 */

