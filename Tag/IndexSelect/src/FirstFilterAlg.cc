#include <boost/python.hpp>
#include "IndexSelect/FirstFilterAlg.h"

#include "SniperKernel/AlgFactory.h"
#include "SniperKernel/SniperPtr.h"
#include "SniperKernel/SniperDataPtr.h"
#include "SniperKernel/SniperLog.h"
#include "SniperKernel/SniperException.h"

#include "Event/Tag.h"
#include "EvtNavigator/NavBuffer.h"
#include "IndexSelect/SelectStore.h"

DECLARE_ALGORITHM(FirstFilterAlg); 

FirstFilterAlg::FirstFilterAlg(const std::string& name)
: AlgBase(name)
{
    //declProp("lightyield", lightyield=1350);
}

FirstFilterAlg::~FirstFilterAlg(){
}

bool FirstFilterAlg::initialize()
{
    //for  input
    SniperDataPtr<SelectStore>  m_navBuf(getParent(), "/Tag");
    if ( m_navBuf.invalid() ) {
        LogError << "cannot get the NavBuffer @ /Event" << std::endl;
        return false;
    }
    m_buf = m_navBuf.data();
    m_gbuf = GlobalBuffer::FromStream("GEvtStream");
    m_total=0; 
    LogDebug  <<  "### TagSelectSvc FirstFilterAlg::initialize ###" << std::endl; 

    m_timer = new JunoTimer("Select Task FirstAlg");                                
    m_timer->start(); 
    return true; 
}

bool FirstFilterAlg::execute()
{
    //获取当前快信号事例 Header
    GlobalBuffer::TagInfo* info = m_buf->ref();
    JM::EvtNavigator* nav = m_buf->curEvt();
    JM::Tag *tTag=(JM::Tag*)nav->getHeader("/Tag");
    double tenergy = tTag->getEnergy();
    if(tenergy >1.7){
        int fileId = tTag->getFileId();
        long entryId = tTag->getEntryId();
        ++m_total;
        LogDebug<<"### Tag path = "<<fileId<<" entryId = "<<entryId <<"###"<<std::endl;
        m_gbuf->tagInfo_setSel(info);
        //m_gbuf->deque_pushBack(fileId, entryId);
    }else{
        m_gbuf->tagInfo_setNoSel(info);
    }
    //sleep(10);    
    return true;
}

bool FirstFilterAlg::finalize()
{
    //long id=-99;
    //std::string path= "";
    //m_gbuf->deque_pushBack(path, id);
    m_timer->stop();
    float t_time = m_timer->elapsed();
    LogInfo << " FirstFilterAlg time = "<<t_time<< std::endl;

    LogDebug << "### TagSelectSvc finalized ###" << std::endl;
    return true;
}


