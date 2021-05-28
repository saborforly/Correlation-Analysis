/* Copyright (C) 2018
   Liu Yan<liuyan2016@ihep.ac.cn>
   Jiaheng Zou <zoujh@ihep.ac.cn> Tao Lin <lintao@ihep.ac.cn>
   Weidong Li <liwd@ihep.ac.cn> 
   This file is part of mt.sniper.
 
   You should have received a copy of the GNU Lesser General Public License
   along with mt.sniper.  If not, see <http://www.gnu.org/licenses/>. */

#include "SniperMuster/GlobalBuffer.h"
#include "IndexEventIO/BeginIOHdl.h"
#include "Event/Tag.h"

#include "SniperKernel/SniperPtr.h"
#include "SniperKernel/SniperDataPtr.h"
#include "SniperKernel/SniperException.h"
#include "SniperKernel/Incident.h"
#include "SniperKernel/SniperLog.h"

BeginIOHdl::BeginIOHdl(Task* par, int stoptask_option, double floor, double ceiling)
    : IIncidentHandler(par), m_par(par),m_stoptask_option(stoptask_option),m_floor(floor),m_ceiling(ceiling)
{
    m_gbuf = GlobalBuffer::FromStream("GEvtStream");
    m_winHandler = new WindowHandler();

    m_winHandler->setTimeWindow(m_floor, m_ceiling);
    LogInfo << "--- IO init evtHdl ---" << std::endl;
}

bool BeginIOHdl::handle(Incident& /*incident*/)
{
    LogDebug << "--- IO begin handle ---" << std::endl;
    //get Tag path, entryId
    //fileID and filePath; from ID search pre and back filepath for window
    m_winHandler->setAllPath(m_gbuf->getIdPath());
    while(true){
        //time set window size, fileId and entryId get window
        GlobalBuffer::TagInfo* tagInfo = m_gbuf->tagInfo_pop();
        if(tagInfo != nullptr){
            LogDebug << "--- IO state = "<<tagInfo->stat<<" evtHdl ---" << std::endl;

            if(tagInfo->stat == 2){

                JM::EvtNavigator* nav = static_cast<JM::EvtNavigator*>(tagInfo->dptr);
                JM::Tag *tTag=(JM::Tag*)nav->getHeader("/Tag");
                m_fileId = tTag->getFileId();
                m_entryId = tTag->getEntryId();            
                LogDebug << "--- IO fileId = "<<m_fileId<< " entryId = "<<m_entryId<<" evtHdl ---" << std::endl;
                auto deq = m_winHandler->getWindow(m_fileId, m_entryId);
                m_gbuf->push_back(deq);

            }
            m_gbuf->tagInfo_popDone(tagInfo);
        }else{
            LogDebug << "--- IO tagInfo_pop  nullptr ---" << std::endl;
            break; 
        }

    }
    LogDebug << "--- IO finish evtHdl ---" << std::endl;    
    
    // fanalize push
    LogDebug<<"--- push back nullptr ---"<<std::endl;
    GlobalBuffer::Elem* ref=nullptr;
    m_gbuf->push_back(ref);
    delete m_winHandler;
    return m_domain.stop();
}

