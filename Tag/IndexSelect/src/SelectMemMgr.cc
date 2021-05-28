#include "IndexSelect/SelectMemMgr.h"
#include "IndexSelect/SelectStore.h"
#include "IndexSelect/BeginSelectHdl.h"
//#include "EndEvtHdl.h"
#include "SniperKernel/Task.h"
#include "SniperKernel/DataMemSvc.h"
#include "SniperKernel/SniperPtr.h"
#include "SniperKernel/SvcFactory.h"
#include "JunoTimer/JunoTimer.h"

DECLARE_SERVICE(SelectMemMgr);

SelectMemMgr::SelectMemMgr(const std::string& name)
    : SvcBase(name)
{
}

SelectMemMgr::~SelectMemMgr()
{
}

bool SelectMemMgr::initialize()
{
    SniperPtr<DataMemSvc> pSvc(m_par, "DataMemSvc");
    pSvc->regist("/Tag", new SelectStore());
    LogDebug << "### TagSelectSvc SelectMemMgr initialize ###"<<std::endl;

    if ( m_par->find("InputSvc") != 0 ) {
        IIncidentHandler* bi = new BeginSelectHdl(m_par);
        bi->regist("BeginEvent");
        m_icdts.push_back(bi);
    }

    //if ( m_par->find("OutputSvc") != 0 ) {
        //IIncidentHandler* ei = new EndEvtHdl(m_par);
        //ei->regist("EndEvent");
        //m_icdts.push_back(ei);
    //}

    return true;
}

bool SelectMemMgr::finalize()
{
    for ( auto it = m_icdts.rbegin(); it != m_icdts.rend(); ++it ) {
        delete *it;
    }

    return true;
}
