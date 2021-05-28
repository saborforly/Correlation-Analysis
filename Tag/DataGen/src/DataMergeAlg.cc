#include "DataMergeAlg.h"
#include "SniperKernel/AlgFactory.h"
#include "SniperKernel/SniperPtr.h"
#include "SniperKernel/SniperLog.h"
#include "TTimeStamp.h"
#include "Event/SimEvent.h"
#include "Event/SimHeader.h"

DECLARE_ALGORITHM(DataMergeAlg);

DataMergeAlg::DataMergeAlg(const std::string& name)
    : AlgBase(name)
{
    declProp("time", m_count = 0);
    declProp("dT", d_dT=2000000);
}

DataMergeAlg::~DataMergeAlg()
{
}

bool DataMergeAlg::initialize()
{

    SniperDataPtr<JM::NavBuffer> navbuf(getRoot(), "/Event");
    if (navbuf.invalid()){
        LogError<<"can not get navbuffer!!!"<<std::endl;
        return false;
    }
    m_buf=navbuf.data();

    m_timer = new JunoTimer("Ana Task Alg");
    m_timer->start();
    LogInfo << " initialize Generate Data" << std::endl;
    SniperPtr<IDataMemMgr> mMgr(*getParent(), "BufferMemMgr");
    m_mMgr=mMgr.data();   


    return true;
}

bool DataMergeAlg::execute()
{
    ++m_count;
    //LogInfo << "Hello world: count: " << m_count << std::endl;
    JM::EvtNavigator* tnav=m_buf->curEvt();
    JM::SimHeader *tHeaderSim=dynamic_cast<JM::SimHeader*>(tnav->getHeader("/Event/Sim"));
    JM::SimEvent *tEventSim=dynamic_cast<JM::SimEvent*>(tHeaderSim->event());

    JM::SimHeader * thisHeader= new JM::SimHeader();
    JM::SimEvent * thisEvent= new JM::SimEvent();
    JM::EvtNavigator* thisNav = new JM::EvtNavigator();
    thisHeader->setEvent(thisEvent);
    thisNav->addHeader("/Event/Sim", thisHeader);
    m_mMgr->adopt(thisNav, "/Event"); 
    
    /*
    const TTimeStamp thisTime = tnav->TimeStamp();
    for (JM::NavBuffer::Iterator navit=++m_buf->current();navit!=m_buf->end();++navit){
        JM::OECHeader *aHeaderOEC=dynamic_cast<JM::OECHeader*>((*navit)->getHeader("/Event/OEC"));
        JM::OECEvent *aEventOEC=dynamic_cast<JM::OECEvent*>(aHeaderOEC->event("JM::OECEvent"));
        const TTimeStamp& afterTime=(*navit)->TimeStamp();
        double dt=(afterTime-thisTime);
        LogDebug << "select event dt= " << dt<<" afterTime="<<afterTime << std::endl;
        if (dt>d_dT) break;//time correlated
    }
    */
    return true;
}

bool DataMergeAlg::finalize()
{
    m_timer->stop();
    float t_time = m_timer->elapsed();
    LogInfo << " TagAnaEvent time = "<<t_time<< std::endl;


    return true;
}

