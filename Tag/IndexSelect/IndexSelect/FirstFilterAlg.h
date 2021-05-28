#ifndef FirstFilterAlg_h
#define FirstFilterAlg_h


#include "EvtNavigator/NavBuffer.h"
#include "SniperKernel/AlgBase.h"
#include "Event/Tag.h"
#include "SniperMuster/GlobalBuffer.h"
#include "IndexSelect/SelectStore.h"
#include "JunoTimer/JunoTimer.h"

class FirstFilterAlg: public AlgBase{

    public:
        FirstFilterAlg(const std::string& name);
        ~FirstFilterAlg();

        bool initialize(); 
        bool execute(); 
        bool finalize(); 


    private:
        SelectStore* m_buf;

        GlobalBuffer* m_gbuf;
        int m_total;
        JunoTimer* m_timer;

        //InputReviser *m_inputReviser;

};
#endif
