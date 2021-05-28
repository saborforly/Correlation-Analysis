#include "IndexEventIO/EventWindow.h"
#include "TTimeStamp.h"
#include "SniperKernel/SniperLog.h"

EventWindow::EventWindow()
{
}


EventWindow::~EventWindow()
{
    clear();
}

void EventWindow::clear()
{
    m_window.clear();
}

void EventWindow::push_front(std::shared_ptr<JM::EvtNavigator > nav){
    m_window.push_front(nav);
}

void EventWindow::push_back(std::shared_ptr<JM::EvtNavigator > nav){
    m_window.push_back(nav);
}


int EventWindow::size(){
    return m_window.size();
}


std::shared_ptr<JM::EvtNavigator >& EventWindow::getNav(int id){
    //for(std::deque<std::shared_ptr<JM::EvtNavigator > >::iterator it=m_window.begin(); it != m_window.end(); it++){
    //    int p1count = (*it).use_count();
    //    LogDebug << " !!! EventIOSvc EventWindow::pop_front count = "<<p1count<<"!!! "<<std::endl;
    //}

    //std::shared_ptr<JM::EvtNavigator > nav = m_window.front(); 
    //std::shared_ptr<JM::EvtNavigator > nav = m_window[id];
    //m_window.pop_front();
    return m_window[id];
}

void EventWindow::setCurId(int curId){
    m_iCur = curId;
}

int  EventWindow::getCurId(){
    return m_iCur;
}
