#include "nrcremotecapfill.h"
#include <Preferences.h>

void NRCRemoteCapFill::update()
{
    Serial.println(m_FDC.getReading28(m_fdc_channel));
}

void NRCRemoteCapFill::calibrate_impl(packetptr_t packetptr){
    
    CapFillCalibrationPacket calibrate_comm(*packetptr);

    std::vector<uint8_t> serialisedvect = packetptr->getBody();

    std::string NVSName = "CAPFILL" + std::to_string(m_levelsensorindex);
    NVSStore _NVS(NVSName, NVSStore::calibrationType::CapFill);
    
    _NVS.saveBytes(serialisedvect);

    m_c = calibrate_comm.c;
    m_grad = calibrate_comm.grad;
}

void NRCRemoteCapFill::loadCalibration(){
    
    std::string NVSName = "CAPFILL" + std::to_string(m_levelsensorindex);
    NVSStore _NVS(NVSName, NVSStore::calibrationType::CapFill);

    std::vector<uint8_t> calibSerialised = _NVS.loadBytes();
    
    if(calibSerialised.size() == 0){
        return;
    }
    CapFillCalibrationPacket calibpacket;
    calibpacket.deserializeBody(calibSerialised);

    m_c = calibpacket.c;
    m_grad = calibpacket.grad;

}