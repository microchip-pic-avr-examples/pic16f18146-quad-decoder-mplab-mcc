 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
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
#include "mcc_generated_files/system/system.h"
#include "quadDecoder.h"

#include <stdbool.h>
#include <stdint.h>

static volatile bool canSleep = false;

//Handler for I2C
bool Serial_callback(i2c_client_transfer_event_t event)
{
    bool rtnCode = false;
    
    switch (event)
    {
        case I2C_CLIENT_TRANSFER_EVENT_ADDR_MATCH:
        {
            //Address Match!
            rtnCode = true;
            canSleep = false;
            break;
        }
        case I2C_CLIENT_TRANSFER_EVENT_RX_READY:
        {
            //Ready to read data
            QuadDecode_loadData(I2C1_Client.ReadByte());
            break;
        }
        case I2C_CLIENT_TRANSFER_EVENT_TX_READY:
        {
            //Ready to send data
            I2C1_Client.WriteByte(QuadDecode_sendI2CData());
            rtnCode = true;
            break;
        }
        case I2C_CLIENT_TRANSFER_EVENT_STOP_BIT_RECEIVED:
        {
            //Stop bit
            canSleep = true;
            break;
        }
        case I2C_CLIENT_TRANSFER_EVENT_ERROR:
        {
            //I2C Error
            break;
        }
        default:
        {
            //Something happened!
        }
    }
    return rtnCode;
}

int main(void)
{
    SYSTEM_Initialize();
    
    //Load NVM Settings
    QuadDecode_loadFromEEPROM();

    //Configure I2C
    I2C1_CallbackRegister(&Serial_callback);
    
    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable(); 

    // Enable the Peripheral Interrupts 
    INTERRUPT_PeripheralInterruptEnable(); 

    while(1)
    {
        //If no I2C activity, we can sleep
        if (SSP1STATbits.P)
        {
            QuadDecode_completeTransaction();
            asm("SLEEP");
            asm("NOP");
            asm("NOP");
        }
    }    
}