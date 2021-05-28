/* Copyright (C) 2018
   Liu Yan<liuyan2016@ihep.ac.cn>
   Jiaheng Zou <zoujh@ihep.ac.cn> Tao Lin <lintao@ihep.ac.cn>
   Weidong Li <liwd@ihep.ac.cn> 
   This file is part of mt.sniper.
 
   You should have received a copy of the GNU Lesser General Public License
   along with mt.sniper.  If not, see <http://www.gnu.org/licenses/>. */

//#include "SniperMuster/GlobalBuffer.h"
#include "BeginIndexHdl.h"
#include "Event/Tag.h"
#include <TMath.h>
#include "SniperKernel/SniperPtr.h"
#include "SniperKernel/SniperDataPtr.h"
#include "SniperKernel/SniperException.h"
#include "SniperKernel/Incident.h"
#include "SniperKernel/SniperLog.h"

BeginIndexHdl::BeginIndexHdl(Task* par, int stoptask_option, double floor, double ceiling, std::string& tagfile, std::string& pathfile)
    : IIncidentHandler(par), m_par(par),m_stoptask_option(stoptask_option),m_floor(floor),m_ceiling(ceiling),m_tagfile(tagfile), m_pathfile(pathfile)
{

    m_timer_1 = new JunoTimer("Ana Task Alg");
    m_timer_1->start();

    m_inpath.open(m_pathfile, std::ios::in);
    m_intag.open(m_tagfile, std::ios::in);
    //LogInfo << "--- IndexIO tagFile ="<<m_tagfile<<"---" << std::endl;
    //LogInfo << "--- IndexIO pathFile ="<<m_pathfile<<"---" << std::endl;

    if(!m_inpath || !m_intag){
        LogError << "^^^ No file Find  ^^^" << std::endl;
        m_domain.stop();
    }

    while(!m_inpath.eof()){
        m_inpath >> m_fileId >> m_filePath;
        if (m_inpath.fail()){
            LogDebug << "^^^ file read finish   ^^^" << std::endl;
            break;
        }

        LogInfo << "^^^ BeginIndexHdl id-path = "<<m_fileId<<"-"<<m_filePath<<std::endl;
        m_fileMap[m_fileId] = m_filePath;
    }
    
    m_inpath.close();

    LogInfo << "--- IO init evtHdl ---" << std::endl;
}

bool BeginIndexHdl::handle(Incident& /*incident*/)
{
    LogInfo << "--- IO begin handle ---" << std::endl;
    int count=0; 
    int pairCount=0;

    std::vector<std::string> pathList;
    pathList.push_back(m_filePath);
    LogInfo << " filePath: "<<m_filePath<<std::endl;

    stream = new NavInputStream(pathList);
    bool okay = stream->initialize();
    if (!okay) {
        LogError << "Failed to initialize NavInputStream"<< std::endl;
    }
    okay = stream->first(true);
    if (!okay) {
        LogError << "Failed to get tag stream"<< std::endl;
    }
    long m_bufMin = 1e9;
    long m_bufMax = 0;

    long m_curMax = 0;
    long m_curMin = 0;
    m_timer_2 = new JunoTimer("Ana Task Alg");
    m_timer_2->start();
 
    while(!m_intag.eof()){
        m_intag >> m_fileId >> m_entryId >> m_energy >>m_time;
        if (m_intag.fail())  break;
        //count++;
        //LogInfo << "^^^ BeginIndexHdl fileId-entryId-energy-time: "<<m_fileId<<"-"<<m_entryId<<"-"<<m_energy<<"-"<<m_time<<std::endl;
        /*
        stream = searchStream(m_fileId);
        //LogInfo << " test 0 "<<std::endl;
        if(stream == nullptr){
            cur_file = m_fileId;
            std::map<int, std::string>::iterator it = m_fileMap.find(m_fileId);
            std::string path;
            if (it != m_fileMap.end()){
                path= it->second;
            }
            else continue;
            //LogInfo << " test 1 "<<std::endl;
            std::vector<std::string> pathList;
            pathList.push_back(path);

            stream = new NavInputStream(pathList);        
            bool okay = stream->initialize();
            if (!okay) {
                LogError << "Failed to initialize NavInputStream"<< std::endl;
            }
            okay = stream->first(true);
            if (!okay) {
                LogError << "Failed to get tag stream"<< std::endl;
            }
            //LogInfo << " test 2 "<<std::endl;
            m_streamMap[m_fileId] = stream;
        }
        */
        //LogInfo<<"before "<<m_entryId<<" "<<m_iCur<<" "<<all<<" "<<m_dBuf.size()<<std::endl;

        m_curMax = m_entryId;

        stream->setEntry(m_entryId, true);
        JM::EvtNavigator* tmp = (JM::EvtNavigator*) stream->get();
        std::shared_ptr<JM::EvtNavigator > share_cur = std::make_shared<JM::EvtNavigator>(*tmp);

        JM::OECHeader *tEventHeader=(JM::OECHeader*) (share_cur.get())->getHeader("/Event/OEC");
        JM::OECEvent *pairEvent=(JM::OECEvent*)tEventHeader->event("JM::OECEvent");
        double tenergy = pairEvent->getEnergy();
        
        m_sum[m_entryId] = 1; 
         
        //m_dBuf[m_entryId] = share_cur;
        bool iscurItRefresh=false;
        m_entryId=m_entryId-1;
        vector<JM::OECEvent*> aEvts;

        for (;m_entryId>=0;--m_entryId){
            //m_curMin = m_entryId;
            m_sum[m_entryId] = 1;

            //LogInfo <<"after "<<m_entryId<<" "<<m_iCur<<" "<<all<<" "<<m_dBuf.size()<< std::endl;
            //if(m_entryId>=m_bufMin && m_entryId<=m_bufMax){
            //    share_tmp = m_dBuf[m_entryId];
            //}else{
                stream->setEntry(m_entryId, true);
                //stream->prev();
                JM::EvtNavigator* navit = (JM::EvtNavigator*) stream->get();
                std::shared_ptr<JM::EvtNavigator > share_tmp= std::make_shared<JM::EvtNavigator>(*navit);
                //m_dBuf[m_entryId] = share_tmp;
            //}
            //JM::OECHeader *aEventHeader=(JM::OECHeader*) navit->getHeader("/Event/OEC");
            JM::OECHeader *aEventHeader=(JM::OECHeader*) (share_tmp.get())->getHeader("/Event/OEC");
            JM::OECEvent *aEvent=dynamic_cast<JM::OECEvent*>(aEventHeader->event("JM::OECEvent"));
            float aenergy = aEvent->getEnergy();                               
            //LogInfo<<"energy = "<<aenergy<<endl;                             
         
            double deltaT=1e9*(pairEvent->getTime()-aEvent->getTime());        
            //LogInfo<<"this is a candidate deltaT = "<<deltaT<<std::endl;
            if (deltaT<1000000.0){//close enough in time
                if(aenergy>12 || aenergy<0.7){
                    continue;
                }
                double dx=pairEvent->getVertexX()-aEvent->getVertexX();
                double dy=pairEvent->getVertexY()-aEvent->getVertexY();
                double dz=pairEvent->getVertexZ()-aEvent->getVertexZ();
                double dist=TMath::Sqrt(dx*dx+dy*dy+dz*dz);
                //LogInfo<<"a close event dist = "<<dist<<endl;
                if (dist>1500.0){
                    if (!iscurItRefresh){
                        iscurItRefresh=true;
                    }
                    continue;
                }
                double px=aEvent->getVertexX();
                double py=aEvent->getVertexY();
                double pz=aEvent->getVertexZ();

                double rdist=TMath::Sqrt(px*px+py*py+pz*pz);
                // LogInfo<<"a close event rdist = "<<rdist<<endl;
                if(rdist>17000.0){
                    continue;
                }
                aEvts.push_back(aEvent);
            }else break;
            
        }
        //LogInfo<<"test 2"<<endl;
        //for(long bufId=m_bufMin; bufId<m_curMin; ++bufId){
        //    if(bufId>m_bufMax) break;
        //    m_dBuf.erase(bufId);
        //}
        //m_bufMin=m_curMin;
        //m_bufMax=m_curMax;

        if (aEvts.size()>=2){
            //LogInfo<<"multi tag"<<aEvts.size()<<endl;
        }else if (aEvts.size()==0){
            //LogInfo<<"single tag"<<endl;
        } else {
            ++pairCount;
            //LogInfo<<"a pair"<<endl;
        }
        
    
    }

    m_timer_2->stop();
    float time_2 = m_timer_2->elapsed();
    m_timer_1->stop();
    float time_1 = m_timer_1->elapsed();

    LogInfo << " ReadIO time_all = "<<time_1<< std::endl;   
    LogInfo << " ReadIO time_exe = "<<time_2<< std::endl;
    LogInfo << " load event = "<<m_sum.size()<< std::endl;
    LogInfo << " pair = "<<pairCount<< std::endl;
    m_intag.close();

    for(auto item =m_streamMap.begin();item!=m_streamMap.end();item++)
    {
        item->second->finalize();
        delete item->second;
    }
    LogDebug << "--- IO finish evtHdl ---" << std::endl;    
    
    return m_domain.stop();
}

NavInputStream*  BeginIndexHdl::searchStream(int fileId){
    NavInputStream*  stream = nullptr;
    std::map<int, NavInputStream*>::iterator it = m_streamMap.find(fileId);
    if (it != m_streamMap.end()){
            stream = it->second;
    }
    return stream;
}

