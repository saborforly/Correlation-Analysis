#include "SniperKernel/SniperLog.h"
#include "EventAna/FullWinNavBuf.h"

using JM::EvtNavigator;

FullWinNavBuf::FullWinNavBuf()
{
}

FullWinNavBuf::~FullWinNavBuf()
{
}

void FullWinNavBuf::setCurId(int curId){
    m_iCur = curId;
}


bool FullWinNavBuf::adopt(std::shared_ptr<JM::EvtNavigator > nav)
{
    m_dBuf.push_back(nav);
    
    return true;
}

bool FullWinNavBuf::reset()
{
    //clear();
    //for ( Iterator it = m_dBuf.begin(); it != m_dBuf.end(); ++it ) {
    //    delete  (*it).get();
    //    m_dBuf.erase(it);
    //}
    m_dBuf.clear();
    //clear();
    m_iCur = -1;
    return true;
}

