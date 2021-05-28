#include "DataGenIBDAlg.h"
#include "SniperKernel/AlgFactory.h"
#include "SniperKernel/SniperPtr.h"
#include "SniperKernel/SniperLog.h"
#include "TTimeStamp.h"
#include "Event/SimHeader.h"
#include "TVector3.h"

DECLARE_ALGORITHM(DataGenIBDAlg);

DataGenIBDAlg::DataGenIBDAlg(const std::string& name)
    : AlgBase(name)
{
    declProp("time", m_count = 0);
    declProp("pathfile", m_pathfile);
    declProp("RateMap", m_rateMap);
}

DataGenIBDAlg::~DataGenIBDAlg()
{
}

bool DataGenIBDAlg::initialize()
{

    SniperPtr<IDataMemMgr> mMgr(*getParent(), "BufferMemMgr");
    if ( mMgr.invalid() ) {
        LogError << "cannot get the BufferMemMgr." << std::endl;
        return false;
    }
    m_mMgr=mMgr.data();
    LogInfo << " initialize Generate Data" << std::endl;

    m_inpath.open(m_pathfile, std::ios::in);
    /*
    while(!m_inpath.eof()){
        m_inpath >> m_fileId >> m_filePath;
        if (m_inpath.fail()){
            LogDebug << "^^^ file read finish   ^^^" << std::endl;
            break;
        }   
        LogInfo << "^^^ BeginIndexHdl id-path = "<<m_fileId<<"-"<<m_filePath<<std::endl;
        NavInputStream* stream = getStream(m_filePath);
        m_fileMap[m_fileId] = stream;
        
    }
    */
    stream = getStream("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/IBD.root");
    m_cur_IBDTime=0.0;

    m_totalRate = 0;
    int tag=0;
    string sample;

    IBD_flag=0;
    return true;
}

bool DataGenIBDAlg::execute()
{
    ++m_count;
    LogInfo << "count: " << m_count << std::endl;
    int tag;

    string sample;
    double sumRate = 0;
    if(IBD_flag==2){
        stream->next();
        double rate = 60.0/(24.0*60.0*60.0);
        double bg_tau = 1.0/rate;
        double bg_time = m_myrandom.Exp(bg_tau);
        m_cur_IBDTime+=bg_time;
        IBD_flag=0;
    }
    long cur_entry = stream->getEntry();
    long total_entry = stream->getEntries();
    if(cur_entry>=total_entry){
        stream->first();
    }
    //stream->setEntry(entryId, true);    
    JM::EvtNavigator* tmp = (JM::EvtNavigator*) stream->get();
    std::shared_ptr<JM::EvtNavigator > share_tmp= std::make_shared<JM::EvtNavigator>(*tmp);
    JM::SimHeader* simheader = dynamic_cast<JM::SimHeader*>((share_tmp.get())->getHeader("/Event/Sim"));
    JM::SimEvent* se = dynamic_cast<JM::SimEvent*>(simheader->event());

    const std::vector<JM::SimTrack*>& m_tracks = se->getTracksVec();
    JM::SimTrack* sitrk = 0;

    if(IBD_flag==0){
        sitrk = m_tracks[0];
        IBD_flag=1;
    }else if(IBD_flag==1){
        IBD_flag=2;
        sitrk = m_tracks[1];
    }
        double tmp_time;
        int pdgId =sitrk->getPDGID();
        double exitT = sitrk->getExitT();
        if(pdgId<0){
            tmp_time = m_cur_IBDTime;
        }else{
            tmp_time = m_cur_IBDTime+exitT/1.0e9 ;
        }
        
        int sec = (int)(tmp_time);
        int nsec = (int)((tmp_time-sec)*1.0e9);

        Float_t genx = sitrk->getQEdepX();
        Float_t geny = sitrk->getQEdepY();
        Float_t genz = sitrk->getQEdepZ();
        Float_t energy = sitrk->getQEdep();
        m_thisEvent = new JM::OECEvent();     //init event
        m_thisHeader = new JM::OECHeader();  //init header 
        m_nav = new JM::EvtNavigator();
        TTimeStamp thistime(sec, nsec);
        m_nav->setTimeStamp(thistime);

        m_thisEvent->setVertexX(genx);
        m_thisEvent->setVertexY(geny);
        m_thisEvent->setVertexZ(genz);
        m_thisEvent->setTime(thistime);
        m_thisEvent->setEnergy(energy);            
        m_thisEvent->addTag(pdgId);

        m_thisHeader->setEvent(m_thisEvent);
        m_nav->addHeader("/Event/OEC", m_thisHeader);
        m_mMgr->adopt(m_nav, "/Event");
        LogDebug <<"IBD_flag="<<IBD_flag<<" pdg = "<<pdgId<<" exitT="<<exitT<<" sec="<<sec<<" nsec="<<nsec<< std::endl;
    
    



    return true;
}

NavInputStream* DataGenIBDAlg::getStream(std::string path)
{
    std::vector<std::string> pathList;
    pathList.push_back(path);
    NavInputStream* stream = new NavInputStream(pathList);
    bool okay = stream->initialize();
    if (!okay) {
        LogError << "Failed to initialize NavInputStream"<< std::endl;
    }
    okay = stream->first(true);
    if (!okay) {
        LogError << "Failed to get tag stream"<< std::endl;
    }
    return stream;
}

bool DataGenIBDAlg::finalize()
{
    LogInfo << " finalized successfully" << std::endl;

    return true;
}

