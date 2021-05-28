/* Copyright (C) 2020
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

#ifndef EventMemIOMgr_H
#define EventMemIOMgr_H

#include "SniperKernel/SvcBase.h"
#include <list>

class IIncidentHandler;

class EventWinMemMgr : public SvcBase
{
    public :

        EventWinMemMgr(const std::string& name);
        virtual ~EventWinMemMgr();

        bool initialize();
        bool finalize();

    private :

        std::list<IIncidentHandler*> m_icdts;
};

#endif
