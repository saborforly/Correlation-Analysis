#ifndef EventAnaAlg_h
#define EventAnaAlg_h


#include "EvtNavigator/NavBuffer.h"
#include "SniperKernel/AlgBase.h"
#include "Event/OECHeader.h"
#include "JunoTimer/JunoTimer.h"

class EventAnaAlg: public AlgBase{

    public:
        EventAnaAlg(const std::string& name);
        ~EventAnaAlg();

        bool initialize(); 
        bool execute(); 
        bool finalize(); 


    private:
        JM::NavBuffer* m_buf;
        int m_total;
        JunoTimer* m_timer;
        //InputReviser *m_inputReviser;

};
#endif
