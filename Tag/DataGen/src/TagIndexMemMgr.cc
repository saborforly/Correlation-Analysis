#include "SniperKernel/Task.h"
#include "SniperKernel/DataMemSvc.h"
#include "SniperKernel/SniperPtr.h"
#include "SniperKernel/SvcFactory.h"
#include "TROOT.h"
#include "BeginIndexHdl.h"
#include "TagIndexMemMgr.h"

DECLARE_SERVICE(TagIndexMemMgr);

TagIndexMemMgr::TagIndexMemMgr(const std::string& name)
    : SvcBase(name)
{
   declProp("TimeWindow", m_bufBounds); 
   declProp("pathFile", m_pathfile);
   declProp("tagFile", m_tagfile);
}
TagIndexMemMgr::~TagIndexMemMgr()
{
}

bool TagIndexMemMgr::initialize()
{

    if ( m_bufBounds.size() < 2 ) {
        m_bufBounds.resize(2);
        m_bufBounds[0] = 0.0, m_bufBounds[1] = 0.0;
    }

    Task* par = getParent();
    //if ( par->find("InputSvc") != 0 ) {
    //IIncidentHandler* bi = new BeginIOHdl(par,0, m_bufBounds[0],m_bufBounds[1]);
    IIncidentHandler* bi = new BeginIndexHdl(par,0, m_bufBounds[0],m_bufBounds[1],m_tagfile, m_pathfile);
    bi->regist("BeginEvent");
    m_icdts.push_back(bi);
    //}
    LogDebug << "--- TagIOSvc TagIndexMemMgr::initialize success ---" << std::endl;
    return true;
}


bool TagIndexMemMgr::finalize()
{
    LogDebug << "--- TagIOSvc TagIndexMemMgr::finalize ---" << std::endl;
    for ( auto it = m_icdts.rbegin(); it != m_icdts.rend(); ++it ) {
        delete *it;
    }
    return true;
}
