/* ************************************************************************** */
/** Descriptive File Name

#ifndef _EXAMPLE_FILE_NAME_H    /* Guard against multiple inclusion */
#define _EXAMPLE_FILE_NAME_H

/* Section: Included Files                                                    */
/* ************************************************************************** */
#include "../stdbool.h" 

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
        INGRESAR_TELEFONO
        
}interface_state_t;
    



    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    
 void USB_Interface();   
 bool mostrar(char *data);
 void menu();
    
    
    
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif



/* *****************************************************************************
 End of File
 */
