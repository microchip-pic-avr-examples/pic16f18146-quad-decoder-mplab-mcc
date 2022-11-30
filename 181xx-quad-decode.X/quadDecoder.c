#include "quadDecoder.h"

#include <xc.h>
#include "mcc_generated_files/system/system.h"

#define I2C_BUFFER_SIZE 16

static volatile uint8_t buffer[I2C_BUFFER_SIZE];
static volatile uint8_t bufferIndex = 0;

static volatile uint8_t txIndex = 0;
static volatile uint16_t prev_TMR1 = 0;
static volatile uint16_t prev_TMR3 = 0;
static volatile int16_t quadCount = 0;

void WriteByteToEEPROM(QUAD_DECODE_EEPROM_ADDR addr, uint8_t value)
{
    //While not still writing...
    while (NVMCON1bits.WR);
    
    //Select EEPROM
    NVMCON1bits.NVMREGS = 1;
    
    NVMADRH = 0x70; //EEPROM starts at 0x70
    NVMADRL = addr; 
    
    //Load Value
    NVMDATL = value;
    NVMCON1bits.WREN = 1;
    INTCONbits.GIE = 0;    
    
    NVMCON2 = 0x55;
    NVMCON2 = 0xAA;
    NVMCON1bits.WR = 1;
    INTCONbits.GIE = 1;
    NVMCON1bits.WREN = 0;
}

uint8_t ReadByteFromEEPROM(QUAD_DECODE_EEPROM_ADDR addr)
{
    //Select EEPROM
    NVMCON1bits.NVMREGS = 1;
    
    NVMADRH = 0x70; //EEPROM starts at 0x70
    NVMADRL = addr;
    
    //Begin Read Cycle
    NVMCON1bits.RD = 1;
    
    return NVMDATL;
}

//Saves the current settings to EEPROM
void QuadDecode_saveToEEPROM(void)
{
    //Write EEPROM Version
    WriteByteToEEPROM(QUAD_DECODE_EEPROM_VERSION_ADDR, EEPROM_VERSION);
    
    //Write the PWM1 Period (CH1 / CH2)
    WriteByteToEEPROM(QUAD_DECODE_EERPOM_PWM12_PRH, PWM1PRH);
    WriteByteToEEPROM(QUAD_DECODE_EERPOM_PWM12_PRL, PWM1PRL);
    
    //Write the PWM2 Period (CH3 / CH4)
    WriteByteToEEPROM(QUAD_DECODE_EERPOM_PWM34_PRH, PWM2PRH);
    WriteByteToEEPROM(QUAD_DECODE_EERPOM_PWM34_PRL, PWM2PRL);
    
    //Write the PWM1, CH1 Duty Cycle
    WriteByteToEEPROM(QUAD_DECODE_EERPOM_PWM_CH1_DCH, PWM1S1P1H);
    WriteByteToEEPROM(QUAD_DECODE_EERPOM_PWM_CH1_DCL, PWM1S1P1L);
    
    //Write the PWM1, CH2 Duty Cycle
    WriteByteToEEPROM(QUAD_DECODE_EERPOM_PWM_CH2_DCH, PWM1S1P2H);
    WriteByteToEEPROM(QUAD_DECODE_EERPOM_PWM_CH2_DCL, PWM1S1P2L);
    
    //Write the PWM2, CH1 Duty Cycle
    WriteByteToEEPROM(QUAD_DECODE_EERPOM_PWM_CH3_DCH, PWM2S1P1H);
    WriteByteToEEPROM(QUAD_DECODE_EERPOM_PWM_CH3_DCL, PWM2S1P1L);
    
    //Write the PWM2, CH2 Duty Cycle
    WriteByteToEEPROM(QUAD_DECODE_EERPOM_PWM_CH4_DCH, PWM2S1P2H);
    WriteByteToEEPROM(QUAD_DECODE_EERPOM_PWM_CH4_DCL, PWM2S1P2L);
    
    //Write IO Settings
    WriteByteToEEPROM(QUAD_DECODE_EEPROM_IO_SETTINGS, QuadDecode_getIO());
        
    //Wait for Write to Finish
    while (NVMCON1bits.WR);
    
    //Setup for CRCOUT Access
    CRCCON0bits.SETUP = 0b00;
    CRCOUT = 0x00;
    
    //Set addresses
    CRC_SetScannerAddressLimit((EEPROM_START_ADDR + QUAD_DECODE_EEPROM_CRC - 1) ,(EEPROM_START_ADDR));
    CRC_StartScanner();
    
    while (CRC_IsScannerBusy());
    
    //Setup for CRCOUT Access
    CRCCON0bits.SETUP = 0b00;
    
    //Write CRC
    WriteByteToEEPROM(QUAD_DECODE_EEPROM_CRC, CRCOUTL);
    
    asm("NOP");
}

//Loads settings from EEPROM, if possible
//If EEPROM is invalid, settings are not loaded
void QuadDecode_loadFromEEPROM(void)
{
    //Setup CRC for 8-bit operations
    CRCCON0bits.EN = 0;
    CRCCON2bits.DLEN = 7;
    CRCCON0bits.EN = 1;
    
    bool memOK = false;
    
    //Check Version ID
    if (EEPROM_VERSION == ReadByteFromEEPROM(QUAD_DECODE_EEPROM_VERSION_ADDR))
    {
        //EEPROM Version ID is OK
        
        //Setup for CRCOUT Access
        CRCCON0bits.SETUP = 0b00;
        CRCOUT = 0x00;
        
        //Validate CRC
        CRC_SetScannerAddressLimit((EEPROM_START_ADDR + QUAD_DECODE_EEPROM_CRC) ,(EEPROM_START_ADDR));
        CRC_StartScanner();
        
        //Wait...
        while (CRC_IsScannerBusy());
    
        if (CRCOUTL == 0x00)
        {
            //CRC is Valid
            memOK = true;
        }
    }
    
    
    if (memOK)
    {
        //Memory OK, begin loading settings
        
        //IO Setup
        QuadDecode_setupIO(ReadByteFromEEPROM(QUAD_DECODE_EEPROM_IO_SETTINGS));
        
        //PWM1 Period (PWM_CH1, PWM_CH2)
        PWM1PRH = ReadByteFromEEPROM(QUAD_DECODE_EERPOM_PWM12_PRH);
        PWM1PRL = ReadByteFromEEPROM(QUAD_DECODE_EERPOM_PWM12_PRL);
        
        //PWM2 Period (PWM_CH3, PWM_CH4)
        PWM2PRH = ReadByteFromEEPROM(QUAD_DECODE_EERPOM_PWM34_PRH);
        PWM2PRL = ReadByteFromEEPROM(QUAD_DECODE_EERPOM_PWM34_PRL);
        
        //PWM1, Channel 1 Duty Cycle
        PWM1S1P1H = ReadByteFromEEPROM(QUAD_DECODE_EERPOM_PWM_CH1_DCH);
        PWM1S1P1L = ReadByteFromEEPROM(QUAD_DECODE_EERPOM_PWM_CH1_DCL);
        
        //PWM1, Channel 2 Duty Cycle
        PWM1S1P2H = ReadByteFromEEPROM(QUAD_DECODE_EERPOM_PWM_CH2_DCH);
        PWM1S1P2L = ReadByteFromEEPROM(QUAD_DECODE_EERPOM_PWM_CH2_DCL);
        
        //PWM2, Channel 1 Duty Cycle
        PWM2S1P1H = ReadByteFromEEPROM(QUAD_DECODE_EERPOM_PWM_CH3_DCH);
        PWM2S1P1L = ReadByteFromEEPROM(QUAD_DECODE_EERPOM_PWM_CH3_DCL);
        
        //PWM2, Channel 2 Duty Cycle
        PWM2S1P2H = ReadByteFromEEPROM(QUAD_DECODE_EERPOM_PWM_CH4_DCH);
        PWM2S1P2L = ReadByteFromEEPROM(QUAD_DECODE_EERPOM_PWM_CH4_DCL);
    }
    else
    {
        //Memory Failed
        //Use the compile time defaults
        QuadDecode_saveToEEPROM();
    }

    //Enable all PWM at the same time
    PWMEN = 0x03;
}

//Calculates the number of pulses
void QuadDecode_calculatePulseCount(void)
{
    uint16_t new_TMR1, new_TMR3, net_TMR1, net_TMR3;
    
    //Get Current Values
    new_TMR1 = Timer1_Read();
    new_TMR3 = Timer3_Read();
    
    //Zero out the net change
    net_TMR1 = 0;
    net_TMR3 = 0;
    
    if (new_TMR1 < prev_TMR1)
    {
        //Rollover occurred
        //Add an offset to the net value and clear old value
        net_TMR1 = 0xFFFF - prev_TMR1;
        prev_TMR1 = 0;
    }
    
    if (new_TMR3 < prev_TMR3)
    {
        //Rollover occurred
        //Add an offset to the net value and clear the old value
        net_TMR3 = 0xFFFF - prev_TMR3;
        prev_TMR3 = 0;
    }
    
    //Find the net change
    net_TMR1 += new_TMR1 - prev_TMR1;
    net_TMR3 += new_TMR3 - prev_TMR3;
    
    //Calculate the net encoder change
    quadCount = net_TMR1 - net_TMR3;

    //Store the old values
    prev_TMR1 = new_TMR1;
    prev_TMR3 = new_TMR3;
}

//Returns a signed 8-bit value indicating the number of pulses
int8_t QuadDecode_sendI2CData(void)
{
    if (txIndex == 0)
    {
        //Calculate the quad decoder
        QuadDecode_calculatePulseCount();
        txIndex++;
        
        return ((quadCount >> 8) & 0xFF);
    }
    else
    {
        //Send the LSB
        //Then, reset the state machine
        
        txIndex = 0;
        return (quadCount & 0xFF);
    }
    
    return 0x00;
}

//Loads I2C RX Data
void QuadDecode_loadData(uint8_t rxByte)
{
    buffer[bufferIndex] = rxByte;
    bufferIndex++;
}

//Processes I2C RX Data
void QuadDecode_completeTransaction(void)
{
    if (bufferIndex != 0)
    {
        //Virtual address to start on
        QUAD_DECODE_ADDRESS addr = buffer[0];
        
        //Array Index (for reads)
        uint8_t aIndex = 1;
        
        //Has an error occurred?
        bool isGood = true;
        
        //Temp variable to make 16-bit values
        uint16_t temp16;
        
        //Number of bytes remaining
        uint8_t remaining;
        
        //While data remains...
        while ((aIndex < bufferIndex) && (isGood))
        {
            //Load the 1st byte
            temp16 = buffer[aIndex];
            aIndex++;

            //Calculate the remaining bytes to read
            remaining = bufferIndex - aIndex;
            
            //Process data
            switch(addr)
            {
                case QUAD_DECODE_PWM_CH12_PR:
                {
                    //PWM 1 - PR Value (Period)
                    //2 Bytes
                    
                    if (remaining >= 1)
                    {
                        //Create 16-bit word
                        temp16 = (temp16 << 8) | buffer[aIndex];
                        aIndex++;
                        
                        //Load Period Registers
                        PWM1_16BIT_WritePeriodRegister(temp16);
                    }
                    break;
                }
                case QUAD_DECODE_PWM_CH34_PR:
                {
                    //PWM 2 - PR Value (Period)
                    //2 Bytes
                    
                    if (remaining >= 1)
                    {
                        //Create 16-bit word
                        temp16 = (temp16 << 8) | buffer[aIndex];
                        aIndex++;
                        
                        //Load Period Registers
                        PWM2_16BIT_WritePeriodRegister(temp16);
                    }
                    break;
                }
                case QUAD_DECODE_PWM_CH1_DC:
                {
                    //PWM 1, CH1 - Duty Cycle
                    //2 Bytes
                    
                    if (remaining >= 1)
                    {
                        //Create 16-bit word
                        temp16 = (temp16 << 8) | buffer[aIndex];
                        aIndex++;
                        
                        //Load Duty Cycle Register
                        PWM1_16BIT_SetSlice1Output1DutyCycleRegister(temp16);
                    }
                    break;
                }
                case QUAD_DECODE_PWM_CH2_DC:
                {
                    //PWM 1, CH2 - Duty Cycle
                    //2 Bytes
                    
                    if (remaining >= 1)
                    {
                        //Create 16-bit word
                        temp16 = (temp16 << 8) | buffer[aIndex];
                        aIndex++;
                        
                        //Load Duty Cycle Register
                        PWM1_16BIT_SetSlice1Output2DutyCycleRegister(temp16);
                    }
                    break;
                }
                case QUAD_DECODE_PWM_CH3_DC:
                {
                    //PWM 2, CH1 - Duty Cycle
                    //2 Bytes
                    
                    if (remaining >= 1)
                    {
                        //Create 16-bit word
                        temp16 = (temp16 << 8) | buffer[aIndex];
                        aIndex++;
                        
                        //Load Duty Cycle Register
                        PWM2_16BIT_SetSlice1Output1DutyCycleRegister(temp16);
                    }
                    break;
                }
                case QUAD_DECODE_PWM_CH4_DC:
                {
                    //PWM 2, CH2 - Duty Cycle
                    //2 Bytes
                    
                    if (remaining >= 1)
                    {
                        //Create 16-bit word
                        temp16 = (temp16 << 8) | buffer[aIndex];
                        aIndex++;
                        
                        //Load Duty Cycle Register
                        PWM2_16BIT_SetSlice1Output2DutyCycleRegister(temp16);
                    }
                    break;
                }
                case QUAD_DECODE_IO_CONFIG:
                {
                    //IO Configuration
                    //1 Byte
                    
                    QuadDecode_setupIO((uint8_t)(temp16 & 0xFF));
                    
                    break;
                }
                case QUAD_DECODE_EEPROM_SAVE:
                {
                    //EEPROM Sequence
                    //2 Bytes
                    
                    //If extra data remains - do NOT write to EEPROM
                    
                    if (remaining == 1)
                    {
                        temp16 = (temp16 << 8) | buffer[aIndex];
                        aIndex++;
                        
                        if (temp16 == EEPROM_UNLOCK)
                        {
                            //EEPROM Unlock OK
                            
                            //Write Data
                            QuadDecode_saveToEEPROM();
                        }
                    }
                    break;
                }
                default:
                {
                    //Unknown value - exit
                    isGood = false;
                }
            }
            addr++;
        }
        
        //Apply PWM changes
        PWMLOAD = 0x03;
    }
    else
    {
        //I2C was a read
        txIndex = 0;
    }
    
    //Reset access counter
    bufferIndex = 0;
}

//Sets IO up according to QUAD_DECODE_IO
void QuadDecode_setupIO(uint8_t value)
{
    //Setup Bitfields
    QUAD_DECODE_IO io;
    io.rxByte = value;
    
    //For inputs, 1 = Internal WPU, 0 = External Pull-up
    
    //Inputs
    if (io.QUAD_A)
    {
        QUAD_A_SetPullup();
    }
    else
    {
        QUAD_A_ResetPullup();
    }
    
    if (io.QUAD_B)
    {
        QUAD_B_SetPullup();
    }
    else
    {
        QUAD_B_ResetPullup();
    }
    
    if (io.BUTTON_IN)
    {
        BUTTON_IN_SetPullup();
    }
    else
    {
        BUTTON_IN_ResetPullup();
    }
    
    //For outputs, 1 = Open-Drain, 0 = PUSH-PULL
    
    //Outputs
    if (io.PWM_CH4)
    {
        PWM_CH4_SetOpenDrain();
    }
    else
    {
        PWM_CH4_SetPushPull();
    }

    
    if (io.PWM_CH3)
    {
        PWM_CH3_SetOpenDrain();
    }
    else
    {
        PWM_CH3_SetPushPull();
    }
    
    if (io.PWM_CH2)
    {
        PWM_CH2_SetOpenDrain();
    }
    else
    {
        PWM_CH2_SetPushPull();
    }
    
    if (io.PWM_CH1)
    {
        PWM_CH1_SetOpenDrain();
    }
    else
    {
        PWM_CH1_SetPushPull();
    }
        
    if (io.BUTTON_OUT)
    {
        BUTTON_OUT_SetOpenDrain();
    }
    else
    {
        BUTTON_OUT_SetPushPull();
    }
}

//Gets the byte that represents the current IO state
uint8_t QuadDecode_getIO(void)
{
    QUAD_DECODE_IO ioSettings;
    ioSettings.rxByte = 0x00;
    
    //Inputs
    //1 - WPU, 0 - No Pullup
    ioSettings.BUTTON_IN = BUTTON_IN_WPU;
    ioSettings.QUAD_B = QUAD_B_WPU;
    ioSettings.QUAD_A = QUAD_A_WPU;
    
    //Outputs
    //1 - Open Drain, 0 - Push-Pull
    ioSettings.PWM_CH1 = PWM_CH1_OD;
    ioSettings.PWM_CH2 = PWM_CH2_OD;
    ioSettings.PWM_CH3 = PWM_CH3_OD;
    ioSettings.PWM_CH4 = PWM_CH4_OD;
    ioSettings.BUTTON_OUT = BUTTON_OUT_OD;
    
    return ioSettings.rxByte;
}