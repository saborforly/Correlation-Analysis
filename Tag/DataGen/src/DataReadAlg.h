#ifndef DataReadAlg_h
#define DataReadAlg_h

#include "SniperKernel/AlgBase.h"
#include <vector>
#include <map>
#include "Event/OECHeader.h"
#include "BufferMemMgr/IDataMemMgr.h"
#include "EvtNavigator/NavBuffer.h"
#include "TRandom.h"
#include <fstream>
#include<iostream>
#include "TRandom.h"

class DataReadAlg: public AlgBase
{
    public:
        DataReadAlg(const std::string& name);

        ~DataReadAlg();

        bool initialize();
        bool execute();
        bool finalize();

    private:
        int fileID;
        double lowEnergy;
        long count;
        ofstream outfile; 
        TRandom m_myrandom;

        JM::EvtNavigator* m_nav;
        JM::OECHeader* m_thisHeader;
        JM::OECEvent* m_thisEvent;
        JM::NavBuffer *m_buf;
        

};

#endif
