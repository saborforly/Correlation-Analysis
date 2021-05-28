#include "EventAna/EventWinMemMgr.h"
#include "EventAna/BeginWinHdl.h"
#include "EventAna/EndWinHdl.h"
#include "EventAna/FullWinNavBuf.h"

#include "SniperKernel/Task.h"
#include "SniperKernel/DataMemSvc.h"
#include "SniperKernel/SniperPtr.h"
#include "SniperKernel/SvcFactory.h"

DECLARE_SERVICE(EventWinMemMgr);

EventWinMemMgr::EventWinMemMgr(const std::string& name)
    : SvcBase(name)
{
}

EventWinMemMgr::~EventWinMemMgr()
{
}

bool EventWinMemMgr::initialize()
{
    //Task* par = getParent();
    SniperPtr<DataMemSvc> mSvc(m_par, "DataMemSvc");
    mSvc->regist("/Event", new FullWinNavBuf());

    if ( m_par->find("InputSvc") != 0 ) {
        IIncidentHandler* bi = new BeginWinHdl(m_par);
        bi->regist("BeginEvent");
        m_icdts.push_back(bi);
    }

    if ( m_par->find("OutputSvc") != 0 ) {
        IIncidentHandler* ei = new EndWinHdl(m_par);
        ei->regist("EndEvent");
        m_icdts.push_back(ei);
    }
    
    LogDebug << "---  EventWinMemMgr::initialize success ---" << std::endl;
    return true;
}


bool EventWinMemMgr::finalize()
{
    LogDebug << "--- EventWinMemMgr::finalize ---" << std::endl;
    for ( auto it = m_icdts.rbegin(); it != m_icdts.rend(); ++it ) {
        delete *it;
    }
    return true;
}
