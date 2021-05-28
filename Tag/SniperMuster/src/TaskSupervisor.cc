/* Copyright (C) 2018
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

#include "TaskSupervisor.h"
//#include "SniperTbbTask.h"
#include "SniperKernel/SniperLog.h"
#include "ThreadAssistor.h"
#include <boost/python.hpp>
namespace bp = boost::python;

TaskSupervisor::~TaskSupervisor()
{
    m_children.clear();
    

}

bool TaskSupervisor::intake(bp::api::object& functor)
{
    bp::api::object task = functor();
    m_children.push_back(
            new ThreadAssistor(task) );

    return true;
}

void TaskSupervisor::execute()
{
    if ( m_stat )  // @ continuation status
    {
        LogDebug << "entering continuation status" << std::endl;
    }
    else  // @ init status
    {
        int n = m_children.size();

        LogDebug << " children size = "<< n << std::endl;
        //recycle_as_safe_continuation();
        m_stat = true;

        //set_ref_count(n+1);
        for ( auto c : m_children ) {
            (*c).start();
        }

    }

    //return nullptr;
}

void TaskSupervisor::join(){
    for ( auto c : m_children ) {
        (*c).join();
    }
}
