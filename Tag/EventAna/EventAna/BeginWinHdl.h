#ifndef BEGIN_EVENT_HANDLER_H
#define BEGIN_EVENT_HANDLER_H

#include "SniperKernel/IIncidentHandler.h"
#include "SniperMuster/GlobalBuffer.h"


class Task;
class FullWinNavBuf;
class WinInputSvc;

class BeginWinHdl : public IIncidentHandler
{
    public :

        BeginWinHdl(Task* par);

        bool handle(Incident& incident);

    private :

        FullWinNavBuf*  m_buf;
        WinInputSvc* m_iSvc;

        // 0: stop root (default)
        // 1: stop current task
};

#endif
