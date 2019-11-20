/* ************************************************************************** */
/** Descriptive File Name

#ifndef _EXAMPLE_FILE_NAME_H    /* Guard against multiple inclusion */
#define _EXAMPLE_FILE_NAME_H

/* Section: Included Files                                                    */
/* ************************************************************************** */
#include "stdbool.h" 

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

        typedef enum
{
        MENU,
        FIJAR_HORA,
        CONSULTAR_HORA,
        AGREGAR_PLANTA,
        SETEAR_UMBRALES_COLORES,
        INGRESAR_TELEFONO,
        VALOR_SENSOR
        
}interface_state_t;


    



    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    
 void USB_Interface();   
 bool mostrar(char *data);
 void menu();
 bool mostrar_Varios(char *data0,char *data1,char *data2,char *data3,char *data4);
    
    
    
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif



/* *****************************************************************************
 End of File
 */
