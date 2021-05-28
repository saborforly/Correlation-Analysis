#ifndef IndexEventMemIOMgr_H
#define IndexEventMemIOMgr_H

#include "SniperKernel/SvcBase.h"
#include <list>

class IIncidentHandler;

class IndexEventIOMemMgr : public SvcBase
{
    public :

        IndexEventIOMemMgr(const std::string& name);
        virtual ~IndexEventIOMemMgr();

        bool initialize();
        bool finalize();

    private :
        std::vector<double>          m_bufBounds;
        std::list<IIncidentHandler*> m_icdts;
        std::string m_pathfile;
        std::string m_tagfile;
};

#endif
