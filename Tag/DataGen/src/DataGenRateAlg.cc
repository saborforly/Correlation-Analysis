#include "DataGenRateAlg.h"
#include "SniperKernel/AlgFactory.h"
#include "SniperKernel/SniperPtr.h"
#include "SniperKernel/SniperLog.h"
#include "TTimeStamp.h"
#include "Event/SimHeader.h"
#include "TVector3.h"

DECLARE_ALGORITHM(DataGenRateAlg);

DataGenRateAlg::DataGenRateAlg(const std::string& name)
    : AlgBase(name)
{
    declProp("time", m_count = 0);
    declProp("pathfile", m_pathfile);
    declProp("RateMap", m_rateMap);
}

DataGenRateAlg::~DataGenRateAlg()
{
}

bool DataGenRateAlg::initialize()
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
    m_Th232[0]=getStream("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/mergy/Th232-1000812080.root");
    m_Th232[1]=getStream("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/mergy/Th232-1000822120.root");
    m_Th232[2]=getStream("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/mergy/Th232-1000832120.root");
    m_Th232[3]=getStream("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/mergy/Th232-1000842120.root");
    m_Th232[4]=getStream("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/mergy/Th232-1000842160.root");
    m_Th232[5]=getStream("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/mergy/Th232-1000862200.root");
    m_Th232[6]=getStream("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/mergy/Th232-1000882240.root");
    m_Th232[7]=getStream("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/mergy/Th232-1000882280.root");
    m_Th232[8]=getStream("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/mergy/Th232-1000892280.root");
    m_Th232[9]=getStream("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/mergy/Th232-1000902280.root");
    m_Th232[10]=getStream("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/mergy/Th232-1000902320.root");

    m_U238[0]=getStream("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/mergy/U238-1000822100.root");
    m_U238[1]=getStream("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/mergy/U238-1000822140.root");
    m_U238[2]=getStream("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/mergy/U238-1000832100.root");
    m_U238[3]=getStream("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/mergy/U238-1000832140.root");
    m_U238[4]=getStream("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/mergy/U238-1000842100.root");
    m_U238[5]=getStream("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/mergy/U238-1000842140.root");
    m_U238[6]=getStream("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/mergy/U238-1000842180.root");
    m_U238[7]=getStream("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/mergy/U238-1000862220.root");
    m_U238[8]=getStream("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/mergy/U238-1000882260.root");
    m_U238[9]=getStream("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/mergy/U238-1000902340.root");
    m_U238[10]=getStream("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/mergy/U238-1000912341.root");
    m_U238[11]=getStream("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/mergy/U238-1000922340.root");
    m_U238[12]=getStream("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/mergy/U238-1000922380.root");

    m_K40[0]=getStream("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/mergy/K40-0.root");
    m_K40[1]=getStream("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/mergy/K40-1.root");
    m_K40[2]=getStream("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/mergy/K40-2.root");
    m_K40[3]=getStream("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/mergy/K40-3.root");
    m_K40[4]=getStream("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/mergy/K40-4.root");
    m_K40[5]=getStream("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/mergy/K40-5.root");
    m_K40[6]=getStream("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/mergy/K40-6.root");
    m_K40[7]=getStream("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/mergy/K40-7.root");
    m_K40[8]=getStream("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/mergy/K40-8.root");

    K40_entryId = 1;
    Th232_entryId = 1;
    U238_entryId = 1;
    IBD_entryId = 1;
    m_cur_IBDTime=0.0;
    m_cur_bgTime=0.0; 

    m_totalRate = 0;
    int tag=0;
    string sample;
    for(map<string,double>::iterator it=m_rateMap.begin(); it!=m_rateMap.end(); it++){
        m_totalRate += it->second;
        tag ++;
        sample = it->first;
        m_tagMap[sample]=tag;
    }

    IBD_flag=0;
    return true;
}

bool DataGenRateAlg::execute()
{
    ++m_count;
    LogInfo << "count: " << m_count << std::endl;
    int tag;
    double ranNum=m_myrandom.Uniform(m_totalRate);

    string sample;
    double sumRate = 0;
    for(map<string,double>::iterator it=m_rateMap.begin(); it!=m_rateMap.end(); it++){
        sumRate += it->second;
        if(ranNum<sumRate){
            sample = it->first;
            break;
        }
    }
    int fileId=0;
    if(sample=="U238"){
        fileId = m_myrandom.Integer(13);
        stream = m_U238[fileId];
        tag=1;
    }
    if(sample=="Th232"){
        fileId = m_myrandom.Integer(11);
        stream = m_Th232[fileId];
        tag=2;
    }

    if(sample=="K40"){
        fileId = m_myrandom.Integer(9);
        stream = m_K40[fileId];
        tag=3;
    }


    //stream=m_fileMap["K40"];
    //int entryId = m_myrandom.Integer(100000);
    stream->next();
    long cur_entry = stream->getEntry();
    long total_entry = stream->getEntries();
    LogDebug << "select sample= "<<sample<< " fileId= "<< fileId <<" entryId=" <<cur_entry << std::endl;
    if(cur_entry>=total_entry){
        stream->first();
    }
    //stream->setEntry(entryId, true);    
    
    JM::EvtNavigator* tmp = (JM::EvtNavigator*) stream->get();
    std::shared_ptr<JM::EvtNavigator > share_tmp= std::make_shared<JM::EvtNavigator>(*tmp);
    JM::SimHeader* simheader = dynamic_cast<JM::SimHeader*>((share_tmp.get())->getHeader("/Event/Sim"));
    JM::SimEvent* se = dynamic_cast<JM::SimEvent*>(simheader->event());

    Float_t total_energy=0.0;
    Float_t genx=0.0;
    Float_t geny=0.0;
    Float_t genz=0.0;
    const std::vector<JM::SimTrack*>& m_tracks = se->getTracksVec();
    JM::SimTrack* sitrk = 0;
    for (size_t i = 0; i < m_tracks.size(); ++i) {
        sitrk = m_tracks[i];

        Float_t genx1 = sitrk->getQEdepX();
        Float_t geny1 = sitrk->getQEdepY();
        Float_t genz1 = sitrk->getQEdepZ();
        Float_t energy = sitrk->getQEdep();
        total_energy+=energy;
        genx+=genx1*energy;
        geny+=geny1*energy;
        genz+=genz1*energy;
    }
    genx = genx/total_energy;
    geny = geny/total_energy;
    genz = genz/total_energy;
    double bg_tau = 1.0/m_totalRate;
    double bg_time = m_myrandom.Exp(bg_tau);
    
    /*
    if(IBD_flag==0){
        double IBD_tau = 60.0/(24.0*60.0*60.0);
        m_cur_IBDTime+=m_myrandom.Exp(IBD_tau);
        IBD_flag = 1;
    }
    if(IBD_flag==1){
        LogDebug << "BGTime= "<<m_cur_bgTime<< " IBDTime="<< m_cur_IBDTime << std::endl;
        if(m_cur_IBDTime>m_cur_bgTime && m_cur_IBDTime<m_cur_bgTime+bg_time){
            IBD_flag = 0;

            stream=m_fileMap["IBD"];
            stream->setEntry(IBD_entryId, true);
            IBD_entryId++;
            JM::EvtNavigator* tmp = (JM::EvtNavigator*) stream->get();
            std::shared_ptr<JM::EvtNavigator > share_tmp= std::make_shared<JM::EvtNavigator>(*tmp);
            JM::SimHeader* simheader = dynamic_cast<JM::SimHeader*>((share_tmp.get())->getHeader("/Event/Sim"));
            JM::SimEvent* se = dynamic_cast<JM::SimEvent*>(simheader->event());
            JM::SimTrack* sitrk = se->findTrackByTrkID(1);
            Float_t genx1 = sitrk->getQEdepX();
            Float_t geny1 = sitrk->getQEdepY();
            Float_t genz1 = sitrk->getQEdepZ();
            Float_t energy = sitrk->getQEdep();

            m_thisEvent = new JM::OECEvent();     //init event
            m_thisHeader = new JM::OECHeader();  //init header 
            m_nav = new JM::EvtNavigator();
            int sec = (int)(m_cur_IBDTime);
            int nsec = (int)((m_cur_IBDTime-sec)*1.0e9);
            LogDebug << "IBD energy = "<<energy<< " sec= "<< sec <<" nsec=" <<nsec << std::endl;
            TTimeStamp thistime(sec, nsec);
            m_nav->setTimeStamp(thistime);

            m_thisEvent->setVertexX(genx1);
            m_thisEvent->setVertexY(geny1);
            m_thisEvent->setVertexZ(genz1);
            m_thisEvent->setTime(thistime);
            m_thisEvent->setEnergy(energy);
            m_thisEvent->addTag(0);
            m_thisHeader->setEvent(m_thisEvent);
            m_nav->addHeader("/Event/OEC", m_thisHeader);
            m_mMgr->adopt(m_nav, "/Event");
        }
    }
    */
    m_cur_bgTime+=bg_time;
    int sec = (int)(m_cur_bgTime);
    int nsec = (int)((m_cur_bgTime-sec)*1.0e9);
    LogDebug << "Bg energy = "<<total_energy<< " sec= "<< sec <<" nsec=" <<nsec << std::endl;
    m_thisEvent = new JM::OECEvent();     //init event
    m_thisHeader = new JM::OECHeader();  //init header 
    m_nav = new JM::EvtNavigator();
    TTimeStamp thistime(sec, nsec);
    m_nav->setTimeStamp(thistime);

    m_thisEvent->setVertexX(genx);
    m_thisEvent->setVertexY(geny);
    m_thisEvent->setVertexZ(genz);
    m_thisEvent->setTime(thistime);
    m_thisEvent->setEnergy(total_energy);
    m_thisEvent->addTag(tag);

    m_thisHeader->setEvent(m_thisEvent);
    m_nav->addHeader("/Event/OEC", m_thisHeader);
    m_mMgr->adopt(m_nav, "/Event");

    return true;
}

NavInputStream* DataGenRateAlg::getStream(std::string path)
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

bool DataGenRateAlg::finalize()
{
    LogInfo << " finalized successfully" << std::endl;

    return true;
}

