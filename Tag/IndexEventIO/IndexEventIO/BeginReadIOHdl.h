#ifndef IndexEvent_BeginReadIO_H
#define IndexEvent_BeginReadIO_H

#include "SniperKernel/IIncidentHandler.h"
#include "IndexEventIO/EventWindow.h"
#include "IndexEventIO/WindowHandler.h"
#include "SniperMuster/GlobalBuffer.h"
#include <fstream>
#include "JunoTimer/JunoTimer.h"
class Task;

class BeginReadIOHdl : public IIncidentHandler
{
    public :

        BeginReadIOHdl(Task* par, int stoptask_option, double floor, double ceiling,std::string& tagfile, std::string& pathfile);

        bool handle(Incident& incident);

    private :
        JunoTimer* m_timer;
 
        std::map<int, std::string> m_fileMap;
        Task*             m_par;
        GlobalBuffer* m_gbuf;

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

        WindowHandler* m_winHandler;
        EventWindow* m_tagWin;
        int m_stoptask_option;
};

#endif
