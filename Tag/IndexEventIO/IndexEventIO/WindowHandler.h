#ifndef Window_Handler_H
#define Window_Handler_H

#include <atomic>
#include <string>
#include <deque>
#include "EvtNavigator/EvtNavigator.h"
#include "RootIOSvc/NavInputStream.h"
#include "IndexEventIO/EventWindow.h"

class WindowHandler
{
    public :
   

        WindowHandler();
        virtual ~WindowHandler();

        NavInputStream* getStream(std::string path);

        void setTimeWindow(double floor, double ceiling);

        std::string getPath(int id);
        std::shared_ptr<JM::EvtNavigator >  searchNav(long entryId);
        NavInputStream*   searchStream(int fileId);

        EventWindow* getWindow(int fileId, long id);
        void setAllPath(std::map<int, std::string>& fileMap);

    private :
        double m_floor;
        double m_ceiling;
        long m_bufMin,m_bufMax, m_curMin, m_curMax;

        int m_gid;
        std::map<int, std::string> m_fileMap;

        std::map<long, std::shared_ptr<JM::EvtNavigator> > m_navMap;
        
        std::map<int, NavInputStream*> m_streamMap;

        std::string cur_path;
        NavInputStream* m_stream;
        long m_stream_entry;
        std::shared_ptr<JM::EvtNavigator > cur_nav; 
};

#endif
