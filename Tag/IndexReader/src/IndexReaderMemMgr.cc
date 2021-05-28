/* Copyright (C) 2020
   Liu Yan <liuyan2016@ihep.ac.cn>
   Jiaheng Zou <zoujh@ihep.ac.cn> Tao Lin <lintao@ihep.ac.cn>
   Weidong Li <liwd@ihep.ac.cn> Xingtao Huang <huangxt@sdu.edu.cn>
   This file is part of mt.sniper.
 
   mt.sniper is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
 
   mt.sniper is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.
 
   You should have received a copy of the GNU Lesser General Public License
   along with mt.sniper.  If not, see <http://www.gnu.org/licenses/>. */

#include "IndexReader/IndexReaderMemMgr.h"
#include "IndexReader/BeginReaderHdl.h"
#include "SniperKernel/Task.h"
#include "SniperKernel/DataMemSvc.h"
#include "SniperKernel/SniperPtr.h"
#include "SniperKernel/SvcFactory.h"
#include "TROOT.h"

DECLARE_SERVICE(IndexReaderMemMgr);

IndexReaderMemMgr::IndexReaderMemMgr(const std::string& name)
    : SvcBase(name)
{
    declProp("pathFile", m_pathfile);
    declProp("tagFile", m_tagfile);

}

IndexReaderMemMgr::~IndexReaderMemMgr()
{
}

bool IndexReaderMemMgr::initialize()
{
    Task* par = getParent();
    //if ( par->find("InputSvc") != 0 ) {
    IIncidentHandler* bi = new BeginReaderHdl(par,0, m_tagfile, m_pathfile);
    bi->regist("BeginEvent");
    m_icdts.push_back(bi);
    //}
    LogDebug << "--- IndexIOSvc IndexReaderMemMgr::initialize success ---" << std::endl;
    return true;
}


bool IndexReaderMemMgr::finalize()
{
    LogDebug << "--- IndexIOSvc IndexReaderMemMgr::finalize ---" << std::endl;
    for ( auto it = m_icdts.rbegin(); it != m_icdts.rend(); ++it ) {
        delete *it;
    }
    return true;
}
