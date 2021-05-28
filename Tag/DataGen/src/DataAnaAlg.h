#ifndef DataAnaAlg_h
#define DataAnaAlg_h

#include "SniperKernel/AlgBase.h"
#include <vector>
#include <map>
#include "Event/OECHeader.h"
#include "Event/IBDHeader.h"

#include "BufferMemMgr/IDataMemMgr.h"
#include "EvtNavigator/NavBuffer.h"
#include "TRandom.h"
#include "JunoTimer/JunoTimer.h"
#include "TTree.h"
#include "RootWriter/RootWriter.h"

class DataAnaAlg: public AlgBase
{
    public:
        DataAnaAlg(const std::string& name);

        ~DataAnaAlg();

        bool initialize();
        bool execute();
        bool finalize();

    private:
        JunoTimer* m_timer;
        int m_count;
        TRandom m_myrandom;
        JM::NavBuffer *m_buf;
        double d_dT;

        JM::EvtNavigator* m_nav;
        JM::OECHeader* m_thisHeader;
        JM::OECEvent* m_thisEvent;
        IDataMemMgr * m_mMgr;
        
        Float_t m_dE;
        Float_t m_pE;
        Double_t m_dist;
        Double_t m_time;
        TTree* m_evt_tree;

};

#endif
