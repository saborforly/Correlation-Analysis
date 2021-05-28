/* Copyright (C) 2018
   Liu Yan<liuyan2016@ihep.ac.cn>
   Jiaheng Zou <zoujh@ihep.ac.cn> Tao Lin <lintao@ihep.ac.cn>
   Weidong Li <liwd@ihep.ac.cn> 
   This file is part of mt.sniper.
 
   You should have received a copy of the GNU Lesser General Public License
   along with mt.sniper.  If not, see <http://www.gnu.org/licenses/>. */

//#include "SniperMuster/GlobalBuffer.h"
#include "IndexEventIO/BeginReadIOHdl.h"
#include "Event/Tag.h"

#include "SniperKernel/SniperPtr.h"
#include "SniperKernel/SniperDataPtr.h"
#include "SniperKernel/SniperException.h"
#include "SniperKernel/Incident.h"
#include "SniperKernel/SniperLog.h"

BeginReadIOHdl::BeginReadIOHdl(Task* par, int stoptask_option, double floor, double ceiling, std::string& tagfile, std::string& pathfile)
    : IIncidentHandler(par), m_par(par),m_stoptask_option(stoptask_option),m_floor(floor),m_ceiling(ceiling),m_tagfile(tagfile), m_pathfile(pathfile)
{
    m_gbuf = GlobalBuffer::FromStream("GEvtStream");
    m_winHandler = new WindowHandler();
    m_winHandler->setTimeWindow(m_floor, m_ceiling);

    /*
    m_inpath.open(m_pathfile, std::ios::in);
    m_intag.open(m_tagfile, std::ios::in);
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

        LogDebug << "^^^ BeginReadIOHdl id-path = "<<m_fileId<<"-"<<m_filePath<<std::endl;
        m_fileMap.insert ( std::pair<int, std::string>(m_fileId, m_filePath) );
    }
    m_inpath.close();
    m_gbuf->setIdPath(m_fileMap);
    */

    m_timer = new JunoTimer("Ana Task Alg");
    m_timer->start();
    LogInfo << "--- IO init evtHdl ---" << std::endl;
}

bool BeginReadIOHdl::handle(Incident& /*incident*/)
{
    LogDebug << "--- IO begin handle ---" << std::endl;
    //get Tag path, entryId
    //fileID and filePath; from ID search pre and back filepath for window
    m_winHandler->setAllPath(m_gbuf->getIdPath());
    
    while(!m_intag.eof()){
        m_intag >> m_fileId >> m_entryId >> m_energy >>m_time;
        if (m_intag.fail())  break;

        LogDebug << "^^^ BeginReadIOHdl fileId-entryId-energy-time: "<<m_fileId<<"-"<<m_entryId<<"-"<<m_energy<<"-"<<m_time<<std::endl;
        auto deq = m_winHandler->getWindow(m_fileId, m_entryId);
        m_gbuf->push_back(deq);

    }
    
    m_intag.close();

    m_timer->stop();
    float t_time = m_timer->elapsed();
    LogInfo << " ReadIO time = "<<t_time<< std::endl;   

    LogDebug << "--- IO finish evtHdl ---" << std::endl;    
    
    // fanalize push
    LogDebug<<"--- push back nullptr ---"<<std::endl;
    GlobalBuffer::Elem* ref=nullptr;
    m_gbuf->push_back(ref);
    delete m_winHandler;
    return m_domain.stop();
}

