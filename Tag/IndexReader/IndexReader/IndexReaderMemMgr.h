/* Copyright (C) 2020
 
   You should have received a copy of the GNU Lesser General Public License
   along with mt.sniper.  If not, see <http://www.gnu.org/licenses/>. */

#ifndef IndexMemIOMgr_H
#define IndexMemIOMgr_H

#include "SniperKernel/SvcBase.h"
#include <list>

class IIncidentHandler;

class IndexReaderMemMgr : public SvcBase
{
    public :

        IndexReaderMemMgr(const std::string& name);
        virtual ~IndexReaderMemMgr();

        bool initialize();
        bool finalize();

    private :
        std::string m_pathfile;
        std::string m_tagfile;
        std::list<IIncidentHandler*> m_icdts;
};

#endif
