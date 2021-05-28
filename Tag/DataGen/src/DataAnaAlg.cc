#include "DataAnaAlg.h"
#include "SniperKernel/AlgFactory.h"
#include "SniperKernel/SniperPtr.h"
#include "SniperKernel/SniperLog.h"
#include "TTimeStamp.h"
#include <TMath.h>
#include "Event/IBDEvent.h"
#include "Event/OECEvent.h"

DECLARE_ALGORITHM(DataAnaAlg);

DataAnaAlg::DataAnaAlg(const std::string& name)
    : AlgBase(name)
{
    declProp("time", m_count = 0);
    declProp("dT", d_dT=1500000);
}

DataAnaAlg::~DataAnaAlg()
{
}

bool DataAnaAlg::initialize()
{

    SniperDataPtr<JM::NavBuffer> navbuf(getRoot(), "/Event");
    if (navbuf.invalid()){
        LogError<<"can not get navbuffer!!!"<<std::endl;
        return false;
    }
    m_buf=navbuf.data();
    SniperPtr<IDataMemMgr> mMgr(*getParent(), "BufferMemMgr");
    if ( mMgr.invalid() ) {
        LogError << "cannot get the BufferMemMgr." << std::endl;
        return false;
    }
    m_mMgr=mMgr.data();

    LogInfo << " initialize Generate Data" << std::endl;

    m_timer = new JunoTimer("Ana Task Alg");
    m_timer->start();
    /*
   SniperPtr<RootWriter> svc(*getParent(), "RootWriter");
    if (svc.invalid()) {
        LogError << "Can't Locate RootWriter. If you want to use it, please "
                 << "enalbe it in your job option file."
                 << std::endl;
    }
    m_evt_tree = svc->bookTree("IBDTag", "Deposit Energy Info for every primary track");

    m_evt_tree->Branch("dE", &m_dE, "dE/F");
    m_evt_tree->Branch("pE",  &m_pE,   "pE/F");
    m_evt_tree->Branch("dist", &m_dist, "dist/D");
    m_evt_tree->Branch("time", &m_time, "time/D");    
    */

    return true;
}

bool DataAnaAlg::execute()
{
    //LogInfo << "Hello world: count: " << m_count << std::endl;
    JM::EvtNavigator* tnav=m_buf->curEvt();
    JM::OECHeader *tHeaderOEC=dynamic_cast<JM::OECHeader*>(tnav->getHeader("/Event/OEC"));
    JM::OECEvent *pairEvent=dynamic_cast<JM::OECEvent*>(tHeaderOEC->event("JM::OECEvent"));
    float tenergy = pairEvent->getEnergy();
    /*
    if(tenergy<1.9 || tenergy>2.5){
        return true;
    }
    double ax = pairEvent->getVertexX();
    double ay = pairEvent->getVertexY();
    double az = pairEvent->getVertexZ();
    double rdist=TMath::Sqrt(ax*ax+ay*ay+az*az);
    if(rdist>17000){
        return true;
    }  
    LogDebug<<"Buffer Size = "<<m_buf->size()  <<endl;
    //++m_count; 
    LogDebug<<"energy = "<<tenergy<<endl;
    bool iscurItRefresh=false;
    //muon veto
    //vector<JM::OECEvent*> aEvts;
    if(m_buf->current()==m_buf->begin()){
        return true;
    }

    JM::NavBuffer::Iterator navit=m_buf->current();
    if(navit==m_buf->begin()){
        return true;
    }
    --navit;
    vector<JM::OECEvent*> aEvts;
    for (;(navit-m_buf->begin())>0;--navit){
    //for (;navit!=m_buf->begin();--navit){
        JM::OECHeader *aHeaderOEC=dynamic_cast<JM::OECHeader*>((*navit)->getHeader("/Event/OEC"));
        JM::OECEvent *aEvent=dynamic_cast<JM::OECEvent*>(aHeaderOEC->event("JM::OECEvent"));
        float aenergy = aEvent->getEnergy();
         LogDebug<<"energy = "<<aenergy<<endl;
         //if(aenergy>12 || aenergy<0.7){
         //   continue;
        //}        
 
        double deltaT=1e9*(pairEvent->getTime()-aEvent->getTime());     
        LogDebug<<"this is a candidate deltaT = "<<deltaT<<std::endl;
        if (deltaT<1000000){//close enough in time
             if(aenergy>12 || aenergy<0.7){
                continue;
            }
            double dx=pairEvent->getVertexX()-aEvent->getVertexX();
            double dy=pairEvent->getVertexY()-aEvent->getVertexY();
            double dz=pairEvent->getVertexZ()-aEvent->getVertexZ();
            double dist=TMath::Sqrt(dx*dx+dy*dy+dz*dz);
            LogDebug<<"a close event"<<endl; 
            if (dist>1500.0){
                if (!iscurItRefresh){
                    //i_curi=tempit;
                    //m_curTime=aEvent->getTime();
                    iscurItRefresh=true;
                }
                continue;
            }
            double px=aEvent->getVertexX();
            double py=aEvent->getVertexY();
            double pz=aEvent->getVertexZ();

            double rdist=TMath::Sqrt(px*px+py*py+pz*pz);
            if(rdist>17000){
                continue;
            }
            //if (isthisEvtmur && aEvent->isMuonRelated()) continue;
            aEvts.push_back(aEvent);
        }else break;
        
    }
    if (aEvts.size()>=2){
        LogDebug<<"multi tag"<<aEvts.size()<<endl;
        return true;
    }
    else if (aEvts.size()==0){
        LogDebug<<"single tag"<<endl;
        return true;
    } else {
        m_count;
        LogDebug<<"a pair"<<endl;
    }
        
    vector<JM::OECEvent*>::iterator aEvtsit=aEvts.begin();
    m_dE=pairEvent->getEnergy();
    m_pE=(*aEvtsit)->getEnergy();
    double dx=pairEvent->getVertexX()-(*aEvtsit)->getVertexX();
    double dy=pairEvent->getVertexY()-(*aEvtsit)->getVertexY();
    double dz=pairEvent->getVertexZ()-(*aEvtsit)->getVertexZ();
    m_dist=TMath::Sqrt(dx*dx+dy*dy+dz*dz);
    m_time=1e9*(pairEvent->getTime()-(*aEvtsit)->getTime());

    // int mytag=getTag(tE,pE,dist,time);
    //m_evt_tree -> Fill();
    LogDebug<<"found tag"<<endl;
    */
    return true;
}



bool DataAnaAlg::finalize()
{
    m_timer->stop();
    float t_time = m_timer->elapsed();
    LogInfo << " TagAnaEvent time = "<<t_time<< std::endl;
    LogInfo << " count = "<<m_count<< std::endl;

    return true;
}

