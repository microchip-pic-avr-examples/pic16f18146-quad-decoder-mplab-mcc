/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  3.0.0
*/

/*
© [2022] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef PINS_H
#define PINS_H

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set IO_RA1 aliases
#define PWM_CH3_TRIS                 TRISAbits.TRISA1
#define PWM_CH3_LAT                  LATAbits.LATA1
#define PWM_CH3_PORT                 PORTAbits.RA1
#define PWM_CH3_WPU                  WPUAbits.WPUA1
#define PWM_CH3_OD                   ODCONAbits.ODCA1
#define PWM_CH3_ANS                  ANSELAbits.ANSA1
#define PWM_CH3_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define PWM_CH3_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define PWM_CH3_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define PWM_CH3_GetValue()           PORTAbits.RA1
#define PWM_CH3_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define PWM_CH3_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define PWM_CH3_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define PWM_CH3_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define PWM_CH3_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define PWM_CH3_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define PWM_CH3_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define PWM_CH3_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set IO_RA2 aliases
#define PWM_CH2_TRIS                 TRISAbits.TRISA2
#define PWM_CH2_LAT                  LATAbits.LATA2
#define PWM_CH2_PORT                 PORTAbits.RA2
#define PWM_CH2_WPU                  WPUAbits.WPUA2
#define PWM_CH2_OD                   ODCONAbits.ODCA2
#define PWM_CH2_ANS                  ANSELAbits.ANSA2
#define PWM_CH2_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define PWM_CH2_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define PWM_CH2_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define PWM_CH2_GetValue()           PORTAbits.RA2
#define PWM_CH2_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define PWM_CH2_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define PWM_CH2_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define PWM_CH2_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define PWM_CH2_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define PWM_CH2_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define PWM_CH2_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define PWM_CH2_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set IO_RA5 aliases
#define PWM_CH4_TRIS                 TRISAbits.TRISA5
#define PWM_CH4_LAT                  LATAbits.LATA5
#define PWM_CH4_PORT                 PORTAbits.RA5
#define PWM_CH4_WPU                  WPUAbits.WPUA5
#define PWM_CH4_OD                   ODCONAbits.ODCA5
#define PWM_CH4_ANS                  ANSELAbits.ANSA5
#define PWM_CH4_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define PWM_CH4_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define PWM_CH4_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define PWM_CH4_GetValue()           PORTAbits.RA5
#define PWM_CH4_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define PWM_CH4_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define PWM_CH4_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define PWM_CH4_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define PWM_CH4_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define PWM_CH4_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define PWM_CH4_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define PWM_CH4_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set IO_RB4 aliases
#define IO_RB4_TRIS                 TRISBbits.TRISB4
#define IO_RB4_LAT                  LATBbits.LATB4
#define IO_RB4_PORT                 PORTBbits.RB4
#define IO_RB4_WPU                  WPUBbits.WPUB4
#define IO_RB4_OD                   ODCONBbits.ODCB4
#define IO_RB4_ANS                  ANSELBbits.ANSB4
#define IO_RB4_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define IO_RB4_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define IO_RB4_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define IO_RB4_GetValue()           PORTBbits.RB4
#define IO_RB4_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define IO_RB4_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define IO_RB4_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define IO_RB4_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define IO_RB4_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define IO_RB4_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define IO_RB4_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define IO_RB4_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set IO_RB6 aliases
#define IO_RB6_TRIS                 TRISBbits.TRISB6
#define IO_RB6_LAT                  LATBbits.LATB6
#define IO_RB6_PORT                 PORTBbits.RB6
#define IO_RB6_WPU                  WPUBbits.WPUB6
#define IO_RB6_OD                   ODCONBbits.ODCB6
#define IO_RB6_ANS                  ANSELBbits.ANSB6
#define IO_RB6_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define IO_RB6_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define IO_RB6_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define IO_RB6_GetValue()           PORTBbits.RB6
#define IO_RB6_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define IO_RB6_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define IO_RB6_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define IO_RB6_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)
#define IO_RB6_SetPushPull()        do { ODCONBbits.ODCB6 = 0; } while(0)
#define IO_RB6_SetOpenDrain()       do { ODCONBbits.ODCB6 = 1; } while(0)
#define IO_RB6_SetAnalogMode()      do { ANSELBbits.ANSB6 = 1; } while(0)
#define IO_RB6_SetDigitalMode()     do { ANSELBbits.ANSB6 = 0; } while(0)

// get/set IO_RC0 aliases
#define QUAD_A_TRIS                 TRISCbits.TRISC0
#define QUAD_A_LAT                  LATCbits.LATC0
#define QUAD_A_PORT                 PORTCbits.RC0
#define QUAD_A_WPU                  WPUCbits.WPUC0
#define QUAD_A_OD                   ODCONCbits.ODCC0
#define QUAD_A_ANS                  ANSELCbits.ANSC0
#define QUAD_A_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define QUAD_A_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define QUAD_A_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define QUAD_A_GetValue()           PORTCbits.RC0
#define QUAD_A_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define QUAD_A_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define QUAD_A_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define QUAD_A_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define QUAD_A_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define QUAD_A_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define QUAD_A_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define QUAD_A_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set IO_RC1 aliases
#define QUAD_B_TRIS                 TRISCbits.TRISC1
#define QUAD_B_LAT                  LATCbits.LATC1
#define QUAD_B_PORT                 PORTCbits.RC1
#define QUAD_B_WPU                  WPUCbits.WPUC1
#define QUAD_B_OD                   ODCONCbits.ODCC1
#define QUAD_B_ANS                  ANSELCbits.ANSC1
#define QUAD_B_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define QUAD_B_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define QUAD_B_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define QUAD_B_GetValue()           PORTCbits.RC1
#define QUAD_B_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define QUAD_B_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define QUAD_B_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define QUAD_B_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define QUAD_B_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define QUAD_B_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define QUAD_B_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define QUAD_B_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set IO_RC4 aliases
#define BUTTON_IN_TRIS                 TRISCbits.TRISC4
#define BUTTON_IN_LAT                  LATCbits.LATC4
#define BUTTON_IN_PORT                 PORTCbits.RC4
#define BUTTON_IN_WPU                  WPUCbits.WPUC4
#define BUTTON_IN_OD                   ODCONCbits.ODCC4
#define BUTTON_IN_ANS                  ANSELCbits.ANSC4
#define BUTTON_IN_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define BUTTON_IN_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define BUTTON_IN_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define BUTTON_IN_GetValue()           PORTCbits.RC4
#define BUTTON_IN_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define BUTTON_IN_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define BUTTON_IN_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define BUTTON_IN_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define BUTTON_IN_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define BUTTON_IN_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define BUTTON_IN_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define BUTTON_IN_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set IO_RC5 aliases
#define PWM_CH1_TRIS                 TRISCbits.TRISC5
#define PWM_CH1_LAT                  LATCbits.LATC5
#define PWM_CH1_PORT                 PORTCbits.RC5
#define PWM_CH1_WPU                  WPUCbits.WPUC5
#define PWM_CH1_OD                   ODCONCbits.ODCC5
#define PWM_CH1_ANS                  ANSELCbits.ANSC5
#define PWM_CH1_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define PWM_CH1_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define PWM_CH1_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define PWM_CH1_GetValue()           PORTCbits.RC5
#define PWM_CH1_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define PWM_CH1_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define PWM_CH1_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define PWM_CH1_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define PWM_CH1_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define PWM_CH1_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define PWM_CH1_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define PWM_CH1_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)

// get/set IO_RC6 aliases
#define BUTTON_OUT_TRIS                 TRISCbits.TRISC6
#define BUTTON_OUT_LAT                  LATCbits.LATC6
#define BUTTON_OUT_PORT                 PORTCbits.RC6
#define BUTTON_OUT_WPU                  WPUCbits.WPUC6
#define BUTTON_OUT_OD                   ODCONCbits.ODCC6
#define BUTTON_OUT_ANS                  ANSELCbits.ANSC6
#define BUTTON_OUT_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define BUTTON_OUT_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define BUTTON_OUT_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define BUTTON_OUT_GetValue()           PORTCbits.RC6
#define BUTTON_OUT_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define BUTTON_OUT_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define BUTTON_OUT_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define BUTTON_OUT_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define BUTTON_OUT_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define BUTTON_OUT_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define BUTTON_OUT_SetAnalogMode()      do { ANSELCbits.ANSC6 = 1; } while(0)
#define BUTTON_OUT_SetDigitalMode()     do { ANSELCbits.ANSC6 = 0; } while(0)

/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize (void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handling routine
 * @param none
 * @return none
 */
void PIN_MANAGER_IOC(void);


#endif // PINS_H
/**
 End of File
*/