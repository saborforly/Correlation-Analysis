/* Copyright (C) 2020
   LiuYan <LiuYan2016@ihep.ac.cn>
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

#include "Muster.h"
#include "TaskSupervisor.h"
#include "MusterContext.h"
#include "SyncAssistor.h"
#include "SniperKernel/Task.h"
#include "SniperKernel/SniperContext.h"
#include "SniperKernel/SniperException.h"
#include "SniperKernel/SniperLog.h"
#include <tbb/task.h>
#include <tbb/task_scheduler_init.h>
#include <boost/python.hpp>

#include "SniperMuster/GlobalBuffer.h"
#include "TROOT.h"
//#include <unistd.h>

namespace bp = boost::python;

Muster::Muster()
    : m_threads_one(0),m_threads_two(0),m_threads(0)
{
    ROOT::EnableThreadSafety();
    MusterContext::create();
    sniper_context.set(Sniper::SysMode::MT);
    m_supervisorOne = new TaskSupervisor();
    m_supervisorTwo = new TaskSupervisor();
}

Muster::~Muster()
{
    LogDebug << "release ~Muster" << std::endl;

    m_supervisorOne->join();
    LogDebug << "releasing all One  Muster Tasks" << std::endl;
    m_supervisorTwo->join();

    MusterContext::destroy();
    LogDebug << "releasing all Two Muster Tasks" << std::endl;
}

void Muster::setEvtMax(int evtMax)
{
    MusterContext::instance().setEvtMax(evtMax);
}

bool Muster::configSelect(bp::api::object& functor, unsigned int nthreads)
{
    m_threads_one = nthreads;
    for ( unsigned int i = 0; i < nthreads; ++i )
    {
        LogDebug << "Muster Tasks input One" << std::endl;
        m_supervisorOne->intake(functor);
        ++m_threads;
    }
    return true;
}

bool Muster::configAna(bp::api::object& functor, unsigned int nthreads)
{
    m_threads_two = nthreads;
    for ( unsigned int i = 0; i < nthreads; ++i )
    {
        LogDebug << "Muster Tasks input two" << std::endl;
        m_supervisorTwo->intake(functor);
        ++m_threads;
    }
    return true;
}


bool Muster::run()
{
    sniper_context.set_threads(m_threads);

    LogDebug << "totally open " << m_threads << " std::threads" << std::endl;
    m_supervisorOne->execute();
    m_supervisorTwo->execute();
    SyncAssistor::run();
    return true;
}
