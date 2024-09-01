/**
 * @file FDC2212.cpp
 * @author Rasa Bakhtiar (rb1123@ic.ac.uk)
 * @brief FDC (Capacitance-to-digital-converter) driver for the CapFill boards. Defines functions
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

#include "FDC2212.h"
#include "Config/pinmap_config.h"

boolean FDC2212::setup() {

    int devId = read16FDC(FDC2212_DEVICE_ID);
    Serial.println(devId);
    if (devId != 0x3055) {
        return false;
    };

    loadSettings();
    return true;
};

void FDC2212::loadSettings() {
    if (channel == 0) {
        write16FDC(FDC2212_CONFIG, 0x1481);
		write16FDC(FDC2212_SETTLECOUNT_CH0, 0x64);
		write16FDC(FDC2212_RCOUNT_CH0, 0xFFFF);
		write16FDC(FDC2212_OFFSET_CH0, 0x0000);
		write16FDC(FDC2212_CLOCK_DIVIDERS_CH0, 0x2001);
		write16FDC(FDC2212_DRIVE_CURRENT_CH0, 0xF800);
	} else {
        write16FDC(FDC2212_CONFIG, 0x5481);
        write16FDC(FDC2212_SETTLECOUNT_CH1, 0x64);
		write16FDC(FDC2212_RCOUNT_CH1, 0xFFFF);
		write16FDC(FDC2212_OFFSET_CH1, 0x0000);
		write16FDC(FDC2212_CLOCK_DIVIDERS_CH1, 0x2001);
		write16FDC(FDC2212_DRIVE_CURRENT_CH1, 0xF800);
    }

    write16FDC(FDC2212_MUX_CONFIG, 0x820D);  //set mux config for channels
};

uint32_t FDC2212::getReading28(uint8_t chann) {

    uint32_t reading;
    if (chann == 0) {
        reading = (uint32_t) read16FDC(FDC2212_DATA_CH0) << 16;
        reading |= read16FDC(FDC2212_DATA_LSB_CH0);
        return reading;
    } else if (chann == 1) {
        reading = (uint32_t) read16FDC(FDC2212_DATA_CH1) << 16;
        reading |= read16FDC(FDC2212_DATA_LSB_CH1);
        return reading;
    } else {
        return 10000000;
    }
};


uint16_t FDC2212::read16FDC(uint16_t address) {
    uint16_t data = 0;

    wire.beginTransmission(i2caddress);
    wire.write(static_cast<uint8_t>(address));
    wire.endTransmission();

    wire.requestFrom(i2caddress, 2);

    if (wire.available() != 2) {
        Serial.print("Availabe not working:");
        Serial.println(wire.available());
    } else {
        uint8_t MSB = wire.read();
        uint8_t LSB = wire.read();
        data = (MSB << 8) | LSB;
    }

    return data;
};

void FDC2212::write16FDC(uint16_t address, uint16_t data) {
    wire.beginTransmission(i2caddress);
    wire.write(static_cast<uint8_t>(address));
    wire.write(data >> 8);
    wire.write(data & 0xFF);
    wire.endTransmission();
};