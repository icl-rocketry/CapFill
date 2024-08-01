#pragma once

#include <librrc/remote/nrcremotesensorbase.h>

#include <librnp/rnp_networkmanager.h>
#include <librnp/rnp_packet.h>

#include <librrc/Helpers/nvsstore.h>
#include <librrc/packets/ptapcalibrationpacket.h>

#include "Sensors/FDC2214.h"

class NRCRemoteCapFill : public NRCRemoteSensorBase<NRCRemoteCapFill>
{
    public:
    
        NRCRemoteCapFill(RnpNetworkManager& networkmanager,
                    uint8_t levelsensorindex,
                    FDC2214 & FDC,
                    uint8_t fdc_channel,
                    float c=1,
                    float grad=1
                    ) : 
            NRCRemoteSensorBase(networkmanager),
            m_levelsensorindex(levelsensorindex),
            m_FDC(FDC),
            m_fdc_channel(fdc_channel),
            m_c(c),
            m_grad(grad)
            {};

        void calibrate_impl(packetptr_t packetptr);

        void update();

        void setup(){
            loadCalibration();

        };

        float getC() {return m_c;};

        float getGrad() {return m_grad;};

        float getLevel() {return level;};

    protected:

        friend class NRCRemoteSensorBase<NRCRemoteCapFill>;
        uint8_t m_levelsensorindex;
        FDC2214& m_FDC;
        uint8_t m_fdc_channel;
        float m_c;
        float m_grad;
        float level;

        void loadCalibration();
};