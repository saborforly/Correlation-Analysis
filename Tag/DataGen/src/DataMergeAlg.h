#ifndef DataMergeAlg_h
#define DataMergeAlg_h

#include "SniperKernel/AlgBase.h"
#include <vector>
#include <map>
#include "Event/OECHeader.h"
#include "BufferMemMgr/IDataMemMgr.h"
#include "EvtNavigator/NavBuffer.h"
#include "TRandom.h"
#include "JunoTimer/JunoTimer.h"
#include "BufferMemMgr/IDataMemMgr.h"

class DataMergeAlg: public AlgBase
{
    public:
        DataMergeAlg(const std::string& name);

        ~DataMergeAlg();

        bool initialize();
        bool execute();
        bool finalize();

    private:
        JunoTimer* m_timer;
        int m_count;
        IDataMemMgr * m_mMgr;

        TRandom m_myrandom;
        JM::NavBuffer *m_buf;
        double d_dT;

        JM::EvtNavigator* m_nav;
        JM::OECHeader* m_thisHeader;
        JM::OECEvent* m_thisEvent;

};

#endif
