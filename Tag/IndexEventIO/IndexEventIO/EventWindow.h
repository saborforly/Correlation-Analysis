#ifndef Event_Window_H
#define Event_Window_H

#include <atomic>
#include <string>
#include <deque>
#include "EvtNavigator/EvtNavigator.h"

class EventWindow
{
    public :
        EventWindow();
        virtual ~EventWindow();
        void clear();
        void push_front(std::shared_ptr<JM::EvtNavigator > nav);
        void push_back(std::shared_ptr<JM::EvtNavigator > nav);
        int size();
        std::shared_ptr<JM::EvtNavigator >& getNav(int id);
        
        void setCurId(int curId);
        int  getCurId();

    private :
        int m_iCur;
        std::deque<std::shared_ptr<JM::EvtNavigator > > m_window;
};

#endif
