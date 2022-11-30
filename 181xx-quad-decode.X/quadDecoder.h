#ifndef QUADDECODER_H
#define	QUADDECODER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>
    
    //This defines the virtual addresses for this example
    typedef enum {
        QUAD_DECODE_PWM_CH12_PR = 0, 
        QUAD_DECODE_PWM_CH34_PR, 
        QUAD_DECODE_PWM_CH1_DC, 
        QUAD_DECODE_PWM_CH2_DC, 
        QUAD_DECODE_PWM_CH3_DC, 
        QUAD_DECODE_PWM_CH4_DC, 
        QUAD_DECODE_IO_CONFIG, 
        QUAD_DECODE_EEPROM_SAVE
    } QUAD_DECODE_ADDRESS;
    
    typedef union
    {
        struct
        {
            unsigned BUTTON_IN : 1; // LSB
            unsigned QUAD_B : 1;
            unsigned QUAD_A : 1;
            unsigned PWM_CH1 : 1;
            unsigned PWM_CH2 : 1;
            unsigned PWM_CH3 : 1;
            unsigned PWM_CH4 : 1;
            unsigned BUTTON_OUT : 1; //MSB
        };
        
        uint8_t rxByte;
    } QUAD_DECODE_IO;
    
//EEPROM Unlock Code
#define EEPROM_UNLOCK 0xAA55
    
//Version ID of the EEPROM
#define EEPROM_VERSION 0x01
    
    typedef enum {
        QUAD_DECODE_EEPROM_VERSION_ADDR = 0x00,
        QUAD_DECODE_EERPOM_PWM12_PRH, QUAD_DECODE_EERPOM_PWM12_PRL,
        QUAD_DECODE_EERPOM_PWM34_PRH, QUAD_DECODE_EERPOM_PWM34_PRL,
        QUAD_DECODE_EERPOM_PWM_CH1_DCH, QUAD_DECODE_EERPOM_PWM_CH1_DCL,
        QUAD_DECODE_EERPOM_PWM_CH2_DCH, QUAD_DECODE_EERPOM_PWM_CH2_DCL,
        QUAD_DECODE_EERPOM_PWM_CH3_DCH, QUAD_DECODE_EERPOM_PWM_CH3_DCL,
        QUAD_DECODE_EERPOM_PWM_CH4_DCH, QUAD_DECODE_EERPOM_PWM_CH4_DCL,
        QUAD_DECODE_EEPROM_IO_SETTINGS, QUAD_DECODE_EEPROM_CRC
    } QUAD_DECODE_EEPROM_ADDR;
    
#define EEPROM_START_ADDR 0xF000
    
    //Saves the current settings to EEPROM
    void QuadDecode_saveToEEPROM(void);
    
    //Loads settings from EEPROM, if possible
    //If EEPROM is invalid, settings are not loaded
    void QuadDecode_loadFromEEPROM(void);
    
    //Calculates the number of pulses, and loads the count into a variable
    void QuadDecode_calculatePulseCount(void);
    
    //Returns a signed 8-bit value indicating the number of pulses
    int8_t QuadDecode_sendI2CData(void);
    
    //Loads I2C RX Data
    void QuadDecode_loadData(uint8_t rxByte);
    
    //Processes I2C RX Data
    void QuadDecode_completeTransaction(void);
    
    //Sets IO up according to QUAD_DECODE_IO
    void QuadDecode_setupIO(uint8_t value);
    
    //Gets the byte that represents the current IO state
    uint8_t QuadDecode_getIO(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* QUADDECODER_H */

