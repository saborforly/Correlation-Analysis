/* Copyright (C) 2020
   Liu Yan<liuyan2016@ihep.ac.cn>
   Jiaheng Zou <zoujh@ihep.ac.cn> Tao Lin <lintao@ihep.ac.cn>
   Weidong Li <liwd@ihep.ac.cn> 
   This file is part of mt.sniper.
 
   You should have received a copy of the GNU Lesser General Public License
   along with mt.sniper.  If not, see <http://www.gnu.org/licenses/>. */

//#include "SniperMuster/GlobalBuffer.h"
#include "IndexReader/BeginReaderHdl.h"
#include "IndexReader/TxtIndexReader.h"
#include "Event/Tag.h"
#include "EvtNavigator/NavBuffer.h"
#include "SniperKernel/SniperPtr.h"
#include "SniperKernel/SniperDataPtr.h"
#include "SniperKernel/SniperException.h"
#include "SniperKernel/Incident.h"
#include "SniperKernel/SniperLog.h"
#include <limits.h>


BeginReaderHdl::BeginReaderHdl(Task* par, int stoptask_option, std::string& tagfile, std::string& pathfile)
    : IIncidentHandler(par), m_par(par),m_stoptask_option(stoptask_option)
{
    m_gbuf = GlobalBuffer::FromStream("GEvtStream");
 
    m_indexReader = new TxtIndexReader(tagfile, pathfile);   
    bool flag = m_indexReader->initialize();
    if(!flag){
        LogError << "^^^ No file Find  ^^^" << std::endl;
        m_domain.stop();
    }

    m_gbuf->setMinMaxFileId(m_indexReader->getMinFileId(), m_indexReader->getMaxFileId());

    m_fileMap = m_indexReader->getFileMap();
    m_gbuf->setIdPath(m_fileMap);

    LogDebug << "^^^^^ BeginReaderHdl init ^^^^^" << std::endl;
}

bool BeginReaderHdl::handle(Incident& /*incident*/)
{
    LogDebug << "^^^ BeginReaderHdl Handler ^^^" << std::endl;
    //reader tag
    while(true){
        m_tag = m_indexReader->getIndexData();        

        if(m_tag==nullptr){
            break;
        }
        JM::EvtNavigator* m_nav = new JM::EvtNavigator();
        m_nav->addHeader("/Tag", m_tag);

        m_gbuf->tagInfo_push(m_nav); 
    }
    
    m_gbuf->tagInfo_push(nullptr);    

    return m_domain.stop();
}

