/* ************************************************************************** */
/** WS2812

  @Company
    BQN

  @File Name
    WS2812.h

  @Summary
    Declaraciones para el manejo de los leds WS2812.

  @Description
    Contiene la estructura que almacena los datos RGB de un led y la declaración
    de la función de escritura en el led.
 */
/* ************************************************************************** */

#ifndef _WS2812_H    /* Guard against multiple inclusion */
#define _WS2812_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include <stdint.h>

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */
/* ************************************************************************** */
typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
}ws2812_t;

typedef struct
{
   ws2812_t Dry_color;
   ws2812_t Not_too_Dry_color;
   ws2812_t Opt_color;
   ws2812_t Not_too_sat_color;
   ws2812_t Sat_color;
}thres_colors;


extern const ws2812_t WHITE;
extern const ws2812_t RED;
extern const ws2812_t GREEN;
extern const ws2812_t BLUE;
extern const ws2812_t BLACK;
extern const ws2812_t YELLOW;


void WS2812_send( ws2812_t *p_leds, uint8_t p_length );
void ApagarLEDs();
void Green_SetHigh();
void Red_SetHigh();
void Yellow_SetHigh();
void Blue_SetHigh();
void White_SetHigh();
void Plant_State_Color(thres_colors colors,uint16_t humidity);

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************

/** ws2812_t

  @Summary
    Estructura que contiene el valor para un led WS2812

  @Description
    Estructura que contiene el valor para un led WS2812
    <p>
    Contiene 3 bytes con el valor RGB de cada led.
    <p>

  @Remarks
    None
 */


// *****************************************************************************
// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/**
  @Function
    void WS2812_send( ws2812_t* p_led );

  @Summary
    Transmite un valor rgb a un led.

  @Description
    Transmite un valor rgb a un led.

  @Precondition
    None

  @Parameters
    @param p_led Puntero a la estrucutra que contiene los valores para configurar un led individual.


  @Returns
    void

  @Remarks
    None.
 */

#endif /* _WS2812_H */

/* *****************************************************************************
 End of File
 */
