#include "DataGenAlg.h"
#include "SniperKernel/AlgFactory.h"
#include "SniperKernel/SniperPtr.h"
#include "SniperKernel/SniperLog.h"
#include "TTimeStamp.h"

DECLARE_ALGORITHM(DataGenAlg);

DataGenAlg::DataGenAlg(const std::string& name)
    : AlgBase(name)
{
    declProp("time", m_count = 0);
}

DataGenAlg::~DataGenAlg()
{
}

bool DataGenAlg::initialize()
{

    SniperPtr<IDataMemMgr> mMgr(*getParent(), "BufferMemMgr");
    if ( mMgr.invalid() ) {
        LogError << "cannot get the BufferMemMgr." << std::endl;
        return false;
    }
    m_mMgr=mMgr.data();
    LogInfo << " initialize Generate Data" << std::endl;

    return true;
}

bool DataGenAlg::execute()
{
    ++m_count;
    LogInfo << "Hello world: count: " << m_count << std::endl;

    m_thisEvent = new JM::OECEvent();     //init event
    m_thisHeader = new JM::OECHeader();  //init header 

    m_nav = new JM::EvtNavigator();
    TTimeStamp thistime(m_count,m_count);
    m_nav->setTimeStamp(thistime);
    m_thisEvent->setTime(thistime);
    
    double energy=m_myrandom.Uniform(3.0);
    LogInfo << "energy = "<<energy << std::endl;

    m_thisEvent->setEnergy(energy);

    m_thisHeader->setEvent(m_thisEvent);
    m_nav->addHeader("/Event/OEC", m_thisHeader);
    m_mMgr->adopt(m_nav, "/Event");

    return true;
}

bool DataGenAlg::finalize()
{
    LogInfo << " finalized successfully" << std::endl;

    return true;
}

