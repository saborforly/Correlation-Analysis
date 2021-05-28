/* Copyright (C) 2020
   You should have received a copy of the GNU Lesser General Public License
   along with mt.sniper.  If not, see <http://www.gnu.org/licenses/>. */

#ifndef BeginReader_H
#define BegReader_H

#include "SniperKernel/IIncidentHandler.h"
#include "SniperMuster/GlobalBuffer.h"
#include <fstream>
#include "IndexReader/IIndexReader.h"

class Task;

class BeginReaderHdl : public IIncidentHandler
{
    public :

        BeginReaderHdl(Task* par, int stoptask_option, std::string& tagfile, std::string& pathfile);

        bool handle(Incident& incident);

    private :
        IIndexReader* m_indexReader; 
        JM::Tag* m_tag;
        std::map<int, std::string> m_fileMap;

        Task*             m_par;
        GlobalBuffer* m_gbuf;

        int m_stoptask_option;

};

#endif
