/* ************************************************************************** */
/** WS2812

  @Company
    BQN

  @File Name
    WS2812.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include "WS2812.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/interrupt_manager.h" 
#include "humidity_sensor.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */
const ws2812_t WHITE    = {25, 25, 25};
const ws2812_t RED      = {25, 0, 0};
const ws2812_t GREEN    = {0, 25, 0};
const ws2812_t BLUE     = {0, 0, 25};
const ws2812_t BLACK     = {0, 0, 0};
const ws2812_t YELLOW     = {25, 25, 0};

ws2812_t vectorLEDs[8];


void ApagarLEDs(){
    uint8_t i;
    for (i=1;i<sizeof(vectorLEDs);i=i++){
        vectorLEDs[i]=BLACK;
        
    }
    WS2812_send(vectorLEDs, sizeof(vectorLEDs) );
    
}

void Green_SetHigh(){
    uint8_t i;
    for (i=1;i<sizeof(vectorLEDs);i++){
        vectorLEDs[i]=GREEN;    
    }
    WS2812_send(vectorLEDs, sizeof(vectorLEDs) );
   
}

void Red_SetHigh(){
    uint8_t i;
    for (i=1;i<sizeof(vectorLEDs);i++){
        vectorLEDs[i]=RED;    
    }
    WS2812_send(vectorLEDs, sizeof(vectorLEDs) );
   
}

void Blue_SetHigh(){
    uint8_t i;
    for (i=1;i<sizeof(vectorLEDs);i++){
        vectorLEDs[i]=BLUE;    
    }
    WS2812_send(vectorLEDs, sizeof(vectorLEDs) );
   
}


void Yellow_SetHigh(){
    uint8_t i;
    for (i=1;i<sizeof(vectorLEDs);i++){
        vectorLEDs[i]=YELLOW;    
    }
    WS2812_send(vectorLEDs, sizeof(vectorLEDs) );
   
}

void White_SetHigh(){
    uint8_t i;
    for (i=1;i<sizeof(vectorLEDs);i++){
        vectorLEDs[i]=WHITE;    
    }
    WS2812_send(vectorLEDs, sizeof(vectorLEDs) );
   
}

void RGB_SetHigh(ws2812_t color){
    if(color.r==BLUE.r && color.g==BLUE.g && color.b==BLUE.b){
        Blue_SetHigh();
    }
    else  if(color.r==GREEN.r && color.g==GREEN.g && color.b==GREEN.b){
        Green_SetHigh();
    }
    else  if(color.r==YELLOW.r && color.g==YELLOW.g && color.b==YELLOW.b){
        Yellow_SetHigh();
    }
    else  if(color.r==RED.r && color.g==RED.g && color.b==RED.b){
        Red_SetHigh();
    }
    else  if(color.r==WHITE.r && color.g==WHITE.g && color.b==WHITE.b){
        White_SetHigh();
    }    
}

void Plant_State_Color(thres_colors colors,uint16_t humidity){
    
                if(humidity>=41){
                RGB_SetHigh(colors.Dry_color);
                }
                else if(humidity>=31 && humidity<=40){
                 RGB_SetHigh(colors.Not_too_Dry_color);
                }
                else if(humidity>=10 && humidity<=30){
                RGB_SetHigh(colors.Opt_color);    
                }
                else if(humidity>=6 && humidity<=9){
                 RGB_SetHigh(colors.Not_too_sat_color);
                }
                else if(humidity<=5){
                 RGB_SetHigh(colors.Sat_color);
                }  
    }
    






/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/* ************************************************************************** */


static uint32_t WS2812_bitFlip( uint8_t p_b )
{
    p_b = (p_b & 0xF0) >> 4 | (p_b & 0x0F) << 4;
    p_b = (p_b & 0xCC) >> 2 | (p_b & 0x33) << 2;
    p_b = (p_b & 0xAA) >> 1 | (p_b & 0x55) << 1;
    return (uint32_t)p_b;
}

static void WS2812_sendSingle( ws2812_t* p_led )
{
    uint8_t j;
    uint32_t val;
    // the WS2812 wants bits in the order of:
    // GGGGGGGGRRRRRRRRBBBBBBBB
    // but I want to work in the opposite order. so i'm going to flip
    // the bits around and do some shifting so my order is
    // BBBBBBBBRRRRRRRRGGGGGGGG
    // with the most significant bit on the far right. so the RGB value
    // of 128 64 32, which normally would be:
    // R : 0b10000000
    // G : 0b01000000
    // B : 0b00100000
    // will become:
    // BBBBBBBBRRRRRRRRGGGGGGGG
    // 000001000000000100000010
    val = (WS2812_bitFlip(p_led->b) << 16) + (WS2812_bitFlip(p_led->r) << 8) + (WS2812_bitFlip(p_led->g));

    // now begin shifting them over one at a time
    for( j = 0; j < 24; j++ )
    {
        // depending on if the currently viewed bit is 1 or 0
        // the pin will stay high for different times
        if(val&1){
            // if it is a 1, let it stay higher a bit longer
            LED_CTRL_SetHigh( ); // 0.90 us
            _nop( );
            _nop( );
            _nop( );
            _nop( );
            _nop( );
            _nop( );
            _nop( );
            _nop( );
            _nop( );
            _nop( );
            _nop( );
            _nop( );
            _nop( );
            _nop( );
            _nop( );
            _nop( );
            _nop( );
            _nop( );
            LED_CTRL_SetLow( ); // 0.35 us
            _nop( );
            _nop( );
            _nop( );
            _nop( );
            _nop( );
        }else{
            // but a 0 should go high and then low as fast as possible
            LED_CTRL_SetHigh( ); // 0.35 us
            _nop( );
            _nop( );
            _nop( );
            _nop( );
            _nop( );
            LED_CTRL_SetLow( ); // 0.90 us
            _nop( );
            _nop( );
            _nop( );
            _nop( );
            _nop( );
            _nop( );
            _nop( );
            _nop( );
            _nop( );
            _nop( );
            _nop( );
            _nop( );
            _nop( );
            _nop( );
            _nop( );
            _nop( );
            _nop( );
            _nop( );
        }

        // and then right shift to get the next bit
        val=val>>1;
    }
}


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

// *****************************************************************************

/** 
  @Function
    int ExampleInterfaceFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Remarks
    Refer to the example_file.h interface header for function usage details.
 */
void WS2812_send( ws2812_t *p_leds, uint8_t p_length )
{
    uint8_t i;
    
    INTERRUPT_GlobalDisable();
    
    //WS2812_sendMultiple( p_leds, p_length );
    for( i=0; i<p_length; i++ )
    {
        WS2812_sendSingle( (p_leds+i) );
    }
    
    INTERRUPT_GlobalEnable();
}

/* *****************************************************************************
 End of File
 */
