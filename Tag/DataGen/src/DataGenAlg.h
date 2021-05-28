#ifndef DataGenAlg_h
#define DataGenAlg_h

#include "SniperKernel/AlgBase.h"
#include <vector>
#include <map>
#include "Event/OECHeader.h"
#include "BufferMemMgr/IDataMemMgr.h"
#include "EvtNavigator/NavBuffer.h"
#include "TRandom.h"

class DataGenAlg: public AlgBase
{
    public:
        DataGenAlg(const std::string& name);

        ~DataGenAlg();

        bool initialize();
        bool execute();
        bool finalize();

    private:
        int m_count;
        TRandom m_myrandom;

        JM::EvtNavigator* m_nav;
        JM::OECHeader* m_thisHeader;
        JM::OECEvent* m_thisEvent;
        IDataMemMgr * m_mMgr;

};

#endif
