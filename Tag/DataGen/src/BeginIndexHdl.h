#ifndef Tag_BeginReadIO_H
#define Tag_BeginReadIO_H

#include "SniperKernel/IIncidentHandler.h"
#include <fstream>
#include "JunoTimer/JunoTimer.h"
#include "EvtNavigator/EvtNavigator.h"
#include "RootIOSvc/NavInputStream.h"
#include "Event/OECHeader.h"
#include <deque>
#include <unordered_map>

class Task;

class BeginIndexHdl : public IIncidentHandler
{
    public :

        BeginIndexHdl(Task* par, int stoptask_option, double floor, double ceiling,std::string& tagfile, std::string& pathfile);

        bool handle(Incident& incident);
        NavInputStream* searchStream(int fileId);
        //std::shared_ptr<NavInputStream > searchStream(int fileId);
    private :
        JunoTimer* m_timer_1;
        JunoTimer* m_timer_2;
 
        std::map<int, std::string> m_fileMap;
        Task*             m_par;

        std::string m_pathfile;
        std::string m_tagfile;

        std::ifstream    m_intag;
        std::ifstream    m_inpath;

        int         m_fileId;
        std::string m_filePath;

        long        m_entryId;
        double      m_energy;
        double      m_time;
        double m_floor;
        double m_ceiling;
        NavInputStream* stream;
        //std::map<int, std::shared_ptr<NavInputStream>> m_streamMap;
        std::map<int, NavInputStream*> m_streamMap;
        std::map<int, int> m_sum;
        unordered_map<long, std::shared_ptr<JM::EvtNavigator >> m_dBuf;
        //std::deque<std::shared_ptr<JM::EvtNavigator >> m_dBuf;
        int  m_iCur; 

        

        int m_stoptask_option;
};

#endif
