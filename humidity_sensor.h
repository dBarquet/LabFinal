/* ************************************************************************** */
/* ************************************************************************** */

#ifndef HUMIDITY_SENSOR_H    /* Guard against multiple inclusion */
#define HUMIDITY_SENSOR_H


/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

typedef struct 
{
        uint8_t t_dry;
        uint8_t t_not_too_dry;
        uint8_t t_opt;
        uint8_t t_sat;
        uint8_t t_not_too_sat;
                            
} humidity_thresholds;
   
typedef enum
{
                SECO,
                SATURADO,
                OPTIMO
        
}plant_state;


#define EXAMPLE_CONSTANT 0

    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************





    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************

    uint16_t HumidityGetValue();
    bool IsConversionDone();
    plant_state Change_PlantState(plant_state p_state,humidity_thresholds h_t, uint16_t humidity);


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
