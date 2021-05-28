#ifndef Select_MEM_MGR_H
#define Select_MEM_MGR_H

#include "SniperKernel/SvcBase.h"
#include <list>

class IIncidentHandler;

class SelectMemMgr : public SvcBase
{
    public :

        SelectMemMgr(const std::string& name);
        virtual ~SelectMemMgr();

        bool initialize();
        bool finalize();

    private :
        std::list<IIncidentHandler*> m_icdts;
};

#endif
