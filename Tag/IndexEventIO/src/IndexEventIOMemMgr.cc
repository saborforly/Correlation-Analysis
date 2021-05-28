/* Copyright (C) 2018
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

#include "IndexEventIO/IndexEventIOMemMgr.h"
#include "IndexEventIO/BeginIOHdl.h"
#include "SniperKernel/Task.h"
#include "SniperKernel/DataMemSvc.h"
#include "SniperKernel/SniperPtr.h"
#include "SniperKernel/SvcFactory.h"
#include "TROOT.h"
#include "IndexEventIO/BeginReadIOHdl.h"
DECLARE_SERVICE(IndexEventIOMemMgr);

IndexEventIOMemMgr::IndexEventIOMemMgr(const std::string& name)
    : SvcBase(name)
{
   declProp("TimeWindow", m_bufBounds); 
   //declProp("pathFile", m_pathfile);
   //declProp("tagFile", m_tagfile);
}
IndexEventIOMemMgr::~IndexEventIOMemMgr()
{
}

bool IndexEventIOMemMgr::initialize()
{

    if ( m_bufBounds.size() < 2 ) {
        m_bufBounds.resize(2);
        m_bufBounds[0] = 0.0, m_bufBounds[1] = 0.0;
    }

    Task* par = getParent();
    //if ( par->find("InputSvc") != 0 ) {
    IIncidentHandler* bi = new BeginIOHdl(par,0, m_bufBounds[0],m_bufBounds[1]);
    //IIncidentHandler* bi = new BeginReadIOHdl(par,0, m_bufBounds[0],m_bufBounds[1],m_tagfile, m_pathfile);
    bi->regist("BeginEvent");
    m_icdts.push_back(bi);
    //}
    LogDebug << "--- IndexEventIOSvc IndexEventIOMemMgr::initialize success ---" << std::endl;
    return true;
}


bool IndexEventIOMemMgr::finalize()
{
    LogDebug << "--- IndexEventIOSvc IndexEventIOMemMgr::finalize ---" << std::endl;
    for ( auto it = m_icdts.rbegin(); it != m_icdts.rend(); ++it ) {
        delete *it;
    }
    return true;
}
