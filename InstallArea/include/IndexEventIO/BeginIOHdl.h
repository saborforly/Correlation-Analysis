#ifndef IndexEvent_BeginIO_H
#define IndexEvent_BeginIO_H

#include "SniperKernel/IIncidentHandler.h"
#include "IndexEventIO/EventWindow.h"
#include "IndexEventIO/WindowHandler.h"
#include "SniperMuster/GlobalBuffer.h"

class Task;

class BeginIOHdl : public IIncidentHandler
{
    public :

        BeginIOHdl(Task* par, int stoptask_option, double floor, double ceiling);

        bool handle(Incident& incident);

    private :
        std::map<int, std::string> m_fileMap;
        Task*             m_par;
        GlobalBuffer* m_gbuf;

        long m_entryId;
        int m_fileId;
        double m_floor;
        double m_ceiling;

        WindowHandler* m_winHandler;
        EventWindow* m_tagWin;
        int m_stoptask_option;
};

#endif
