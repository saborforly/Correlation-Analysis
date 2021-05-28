#include <boost/python.hpp>
#include "EventAna/EventAnaAlg.h"

#include "SniperKernel/AlgFactory.h"
#include <boost/filesystem.hpp>
#include "SniperKernel/SniperPtr.h"
#include "SniperKernel/SniperDataPtr.h"
#include "SniperKernel/SniperLog.h"
#include "SniperKernel/SniperException.h"

#include "Event/OECHeader.h"
#include "EvtNavigator/NavBuffer.h"



DECLARE_ALGORITHM(EventAnaAlg); 

EventAnaAlg::EventAnaAlg(const std::string& name)
: AlgBase(name)
{
    //declProp("lightyield", lightyield=1350);
}

EventAnaAlg::~EventAnaAlg(){
}

bool EventAnaAlg::initialize()
{
    //for OEC input
    SniperDataPtr<JM::NavBuffer>  m_navBuf(getParent(), "/Event");
    if ( m_navBuf.invalid() ) {
        LogError << "cannot get the NavBuffer @ /Event" << std::endl;
        return false;
    }
    m_buf = m_navBuf.data();
    m_total=0; 
    LogDebug  << "!!! EventAnaAlg initialized successfully !!!" << std::endl; 
    m_timer = new JunoTimer("Ana Task Alg");
    m_timer->start();

    return true; 
}

bool EventAnaAlg::execute()
{
    int size = m_buf->size();
    if (size==0){
        LogInfo << "!!! No event select !!!" << std::endl;
        return true;
    }else m_total=size;
    LogDebug<<"!!! EventAnaAlg  buffer size = "<<size<<" !!!"<<std::endl;
    JM::EvtNavigator* nav = m_buf->curEvt();
    JM::OECHeader *tEventHeader=(JM::OECHeader*)nav->getHeader("/Event/OEC");
    JM::OECEvent *tEvent=(JM::OECEvent*)tEventHeader->event("JM::OECEvent");
    double tenergy = tEvent->getEnergy();

    LogDebug<<"!!! EventAnaAlg  task energy = "<<tenergy<<" !!!"<<std::endl;
    
    return true;
}

bool EventAnaAlg::finalize()
{
    m_timer->stop();
    float t_time = m_timer->elapsed();
    LogInfo << " EventAnaAlg time = "<<t_time<< std::endl;
    
    LogDebug <<"!!! EventAnaAlg "<<objName()<< "finalized successfully !!!" << std::endl;
    return true;
}


