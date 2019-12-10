/* ************************************************************************** */
/* ************************************************************************** */

#ifndef _EXAMPLE_FILE_NAME_H    /* Guard against multiple inclusion */
#define _EXAMPLE_FILE_NAME_H


/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


#define EXAMPLE_CONSTANT 0

    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

    typedef struct _example_struct_t {
        /* Describe structure member. */
        int some_number;

        /* Describe structure member. */
        bool some_flag;

    } example_struct_t;
    
typedef enum
{
                SECO,
                SATURADO,
                OPTIMO
        
}plant_state;


    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************

    uint16_t HumidityGetValue();
    bool IsConversionDone();
    plant_state Change_PlantState(plant_state p_state, uint16_t humidity);


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
