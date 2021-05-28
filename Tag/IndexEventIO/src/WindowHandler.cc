#include "IndexEventIO/WindowHandler.h"
#include "TTimeStamp.h"
#include "SniperKernel/SniperLog.h"
#include "Event/OECHeader.h"

WindowHandler::WindowHandler()
{
    m_bufMin = 1e9;
    m_bufMax = 0;
    m_curMax = 0;
    m_curMin = 0;
}


WindowHandler::~WindowHandler()
{
    LogDebug << " -- WindowHandler release --- "<<std::endl;
    m_fileMap.clear();
    m_navMap.clear();
}

void WindowHandler::setTimeWindow(double floor, double ceiling)
{
    m_floor = floor;
    m_ceiling = ceiling;
}

void WindowHandler::setAllPath(std::map<int, std::string>& fileMap)
{
    LogDebug << " -- WindowHandler::setAllPath --- "<<std::endl;
    m_fileMap = fileMap;

}


std::string WindowHandler::getPath(int id)
{
    std::map<int, std::string>::iterator it;
    it = m_fileMap.find(id);
    if (it != m_fileMap.end()){
        return it->second;
    }
    return ""; 
}



std::shared_ptr<JM::EvtNavigator >  WindowHandler::searchNav(long entryId){
    std::map<long, std::shared_ptr<JM::EvtNavigator> > ::iterator it;
    it = m_navMap.find(entryId);
    if (it != m_navMap.end()){
        return it->second;
    }

    return nullptr;
}

NavInputStream*   WindowHandler::searchStream(int fileId){
    std::map<int, NavInputStream*>::iterator it;
    it = m_streamMap.find(fileId);
    if (it != m_streamMap.end()){ 
        return it->second;
    }

    return nullptr;
}




EventWindow* WindowHandler::getWindow(int fileId, long entryId)
{

    EventWindow* tagWindow = new EventWindow();

    LogDebug << " -- WindowHandler::getWindow -- "<<std::endl;
 
    m_stream = searchStream(fileId);
    if(m_stream == nullptr){
        cur_path = getPath(fileId);
        if(cur_path=="") return nullptr;
        m_stream = getStream(cur_path);
        m_stream_entry = m_stream->getEntries();
        m_streamMap[fileId] = m_stream;
    }

    cur_nav = searchNav(entryId);

    if (cur_nav == nullptr){
        m_stream->setEntry(entryId, true);
        JM::EvtNavigator* tmp = (JM::EvtNavigator*) m_stream->get();
        cur_nav = std::make_shared<JM::EvtNavigator>(*tmp);
        m_navMap[entryId]=cur_nav;
    }
    m_curMin = entryId; 
    TTimeStamp cur_time = (cur_nav.get()) -> TimeStamp();
    tagWindow->push_front(cur_nav);

    //tagWindow->setCurId(0);
    int cur_id=0;    
    /* 
    LogDebug << " -- WindowHandler previous events-- "<<std::endl;
    long pre_id = entryId-1;
    std::string pre_path;
    std::shared_ptr<NavInputStream> pre_stream = cur_stream;
    //previous event
    while(true){
        if(pre_id<0){
            break;
        }

        std::shared_ptr<JM::EvtNavigator > pre_nav = searchNav(pre_fileId, pre_id); 
        if (pre_nav == nullptr){
            (pre_stream.get())->setEntry(pre_id, true);
            JM::EvtNavigator* tmp = (JM::EvtNavigator*) (pre_stream.get())->get();
            pre_nav = std::make_shared<JM::EvtNavigator>(*tmp);
        }
        TTimeStamp pre_time = (pre_nav.get())->TimeStamp();
        if ((cur_time-pre_time) <= -m_floor){
            ++cur_id;
            std::shared_ptr<JM::EvtNavigator > pre_nav_tmp = pre_nav;

        }else{
            break; 
        }
        pre_id = pre_id-1;
    }
    */
    tagWindow->setCurId(cur_id);

    LogDebug << " -- WindowHandler back events-- "<<std::endl;
    //back event
    long back_id = entryId;
    while(true){
        back_id++;
        if(back_id >= m_stream_entry){
            break;
        }

        std::shared_ptr<JM::EvtNavigator > back_nav = searchNav(back_id);
        if (back_nav == nullptr){
            m_stream->setEntry(back_id, true);
            JM::EvtNavigator* tmp = (JM::EvtNavigator*) m_stream->get();
            back_nav = std::make_shared<JM::EvtNavigator>(*tmp);
        }
        TTimeStamp back_time = (back_nav.get())->TimeStamp();
        double deltaT=1e9*(back_time-cur_time);

        m_navMap[back_id]=back_nav;

        if (deltaT <= m_ceiling){
            tagWindow->push_back(back_nav);

        }else{
            break;                                            
        }
    }
    m_curMax = back_id;

    for(long bufId=m_bufMin; bufId<m_curMin; ++bufId){
        if(bufId>m_bufMax) break;
        m_navMap.erase(bufId);
    }
    m_bufMin=m_curMin;
    m_bufMax=m_curMax;
    
    //Attention: this will use most time
    int sz = tagWindow->size();
    for( int it=0; it<sz; ++it ) {
       auto& nav = tagWindow->getNav(it);
       JM::OECHeader *tEventHeader=(JM::OECHeader*)(nav.get())->getHeader("/Event/OEC");
       JM::OECEvent *tEvent=(JM::OECEvent*)tEventHeader->event("JM::OECEvent");
    }
    

    return tagWindow;
}             


NavInputStream* WindowHandler::getStream(std::string path)
{
    //delete stream;
    std::vector<std::string> pathList;
    pathList.push_back(path);

    NavInputStream *stream = new NavInputStream(pathList);
    bool okay = stream->initialize();
    if (!okay) {
        LogError << "Failed to initialize NavInputStream"<< std::endl;
    }
    okay = stream->first(true);
    if (!okay) {
        LogError << "Failed to get tag stream"<< std::endl;
    }

    return stream;
}

