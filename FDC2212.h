/**
 * @file FDC2212.h
 * @author Rasa Bakhtiar (rb1123@ic.ac.uk)
 * @brief FDC (Capacitance-to-digital-converter) driver for the CapFill boards. Creates FDC class to do so.
 *                  
 * ONLY REGISTERS FOR THE FDC2212 HAVE BEEN DEFINED
 * 
 * ----------------------------- FDC2212QDNTTQ1 DATASHEET ------------------------------------
 * https://www.ti.com/lit/ds/symlink/fdc2212-q1.pdf?ts=1723228575967&ref_url=https%253A%252F%252Fwww.mouser.co.uk%252F
 * 
 * @version 0.1
 * @date 2024-08-9
 * 
 * @copyright Copyright (c) 2023-2024
 * 
 */

#pragma once

#include <Arduino.h>
#include <Wire.h>

class FDC2212 {

    public: 
    FDC2212(uint8_t m_i2caddress, TwoWire m_wire, uint8_t m_channel) : i2caddress(m_i2caddress), wire(m_wire), channel(m_channel){};

    boolean setup();

    uint32_t getReading28(uint8_t chann);

    private:
    // Declaring variables and functions
    // variables
    uint8_t i2caddress;
    TwoWire &wire; 
    uint8_t channel;
    uint8_t autoscanSeq;
    uint8_t deglitchValue;

    // functions
    uint16_t read16FDC(uint16_t address);
    void write16FDC(uint16_t address, uint16_t data);
    void loadSettings();


    // I2C addresses
    static constexpr uint8_t FDC2212_I2C_ADDR_L = 0x2A;
    static constexpr uint8_t FDC2212_I2C_ADDR_H = 0x2B;

    // Defining registers

    // Registers in order of datasheet register list (Figure 18.) !!!FOR FDC2212 ONLY!!!

    static constexpr uint8_t FDC2212_DATA_CH0 = 0x00;
    static constexpr uint8_t FDC2212_DATA_LSB_CH0 = 0x01;
    static constexpr uint8_t FDC2212_DATA_CH1 = 0x02;
    static constexpr uint8_t FDC2212_DATA_LSB_CH1 = 0x03;
    static constexpr uint8_t FDC2212_RCOUNT_CH0 = 0x08;
    static constexpr uint8_t FDC2212_RCOUNT_CH1 = 0x09;
    static constexpr uint8_t FDC2212_OFFSET_CH0 = 0x0C;
    static constexpr uint8_t FDC2212_OFFSET_CH1 = 0x0D;
    static constexpr uint8_t FDC2212_SETTLECOUNT_CH0 = 0x10;
    static constexpr uint8_t FDC2212_SETTLECOUNT_CH1 = 0x11;
    static constexpr uint8_t FDC2212_CLOCK_DIVIDERS_CH0 = 0x14;
    static constexpr uint8_t FDC2212_CLOCK_DIVIDERS_CH1 = 0x15;
    static constexpr uint8_t FDC2212_STATUS = 0x18;
    static constexpr uint8_t FDC2212_STATUS_CONFIG = 0x19;
    static constexpr uint8_t FDC2212_CONFIG = 0x1A;
    static constexpr uint8_t FDC2212_MUX_CONFIG = 0x1B;
    static constexpr uint8_t FDC2212_RESET_DEV = 0x1C;
    static constexpr uint8_t FDC2212_DRIVE_CURRENT_CH0 = 0x1E;
    static constexpr uint8_t FDC2212_DRIVE_CURRENT_CH1 = 0x1F;
    static constexpr uint8_t FDC2212_MANUFACTURER_ID = 0x7E;
    static constexpr uint8_t FDC2212_DEVICE_ID = 0x7F;

    // Put in registers for FDC2214 extra channels here if needed
};