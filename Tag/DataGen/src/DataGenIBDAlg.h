#ifndef DataGenIBDAlg_h
#define DataGenIBDAlg_h

#include "SniperKernel/AlgBase.h"
#include <vector>
#include <map>
#include "Event/OECHeader.h"
#include "BufferMemMgr/IDataMemMgr.h"
#include "EvtNavigator/NavBuffer.h"
#include "TRandom.h"
#include "fstream"
#include "Event/SimEvent.h"
#include "RootIOSvc/NavInputStream.h"

class DataGenIBDAlg: public AlgBase
{
    public:
        DataGenIBDAlg(const std::string& name);

        ~DataGenIBDAlg();

        bool initialize();
        bool execute();
        bool finalize();
        NavInputStream* getStream(std::string);

    private:
        int m_count;
        std::string m_fileId;
        std::string m_filePath;
        std::map<std::string,double> m_rateMap;
        std::map<std::string,int> m_tagMap;

        double m_totalRate;

        int IBD_flag;
        int IBD_entryId;
        double m_cur_IBDTime;
        double m_cur_bgTime;        
        std::string m_pathfile;
        ifstream m_inpath;
        NavInputStream* stream;
        std::map<std::string, NavInputStream*> m_fileMap;  
        

        TRandom m_myrandom;

        JM::EvtNavigator* m_nav;
        JM::OECHeader* m_thisHeader;
        JM::OECEvent* m_thisEvent;
        IDataMemMgr * m_mMgr;

};

#endif
