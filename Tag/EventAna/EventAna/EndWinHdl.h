#ifndef END_WIN_HANDLER_H
#define END_WIN_HANDLER_H

#include "SniperKernel/IIncidentHandler.h"

class Task;
class WinOutputSvc;
class FullWinNavBuf;

class EndWinHdl : public IIncidentHandler
{
    public :

        EndWinHdl(Task* par);

        bool handle(Incident& incident);

    private :

        WinOutputSvc* m_oSvc;
        FullWinNavBuf* m_buf;
};

#endif
