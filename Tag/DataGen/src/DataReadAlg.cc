#include "DataReadAlg.h"
#include "SniperKernel/AlgFactory.h"
#include "SniperKernel/SniperPtr.h"
#include "SniperKernel/SniperLog.h"
#include "TTimeStamp.h"
#include "TMath.h"
DECLARE_ALGORITHM(DataReadAlg);

DataReadAlg::DataReadAlg(const std::string& name)
    : AlgBase(name)
{
    declProp("fileID", fileID = 0);
    declProp("lowEnergy",   lowEnergy = 0);
}

DataReadAlg::~DataReadAlg()
{
}

bool DataReadAlg::initialize()
{
    

    SniperDataPtr<JM::NavBuffer> navbuf(getParent(), "/Event");
    if (navbuf.invalid()){
        LogError<<"can not get navbuffer!!!"<<endl;
        return false;
    }
    m_buf=navbuf.data();

    LogInfo << " initialize Read Data" << std::endl;

    outfile.open("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/tag.txt", ios::app);
    count=-1; 
    return true;
}

bool DataReadAlg::execute()
{
    count++;      
    JM::EvtNavigator* nav = m_buf->curEvt();
    JM::OECHeader* m_thisHeader =(JM::OECHeader*) nav->getHeader("/Event/OEC");
    JM::OECEvent *m_thisEvent=(JM::OECEvent*)m_thisHeader->event("JM::OECEvent");
    long entryID = count;

    TTimeStamp timeStamp = m_thisEvent->getTime();
    double energy = m_thisEvent->getEnergy();
    double time = timeStamp.AsDouble();
     
    //double guess=m_myrandom.Uniform(1.0); 
    //if(guess<rate){
    if(energy>1.9 && energy<2.5){
        double px=m_thisEvent->getVertexX();
        double py=m_thisEvent->getVertexY();
        double pz=m_thisEvent->getVertexZ();

        double rdist=TMath::Sqrt(px*px+py*py+pz*pz);
        if(rdist<17000){
            outfile << fileID << "\t" << entryID << "\t"<<energy<<"\t" << time << endl;   
            //LogInfo << "read file: "<<fileID <<"entryID: " << entryID << std::endl;
        }
    }
    return true;
}

bool DataReadAlg::finalize()
{
    outfile.close();
    LogInfo << " finalized successfully" << std::endl;

    return true;
}

