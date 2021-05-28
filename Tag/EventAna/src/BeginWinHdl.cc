#include "EventAna/BeginWinHdl.h"
#include "EventAna/WinInputSvc.h"
#include "EventAna/FullWinNavBuf.h"
#include "IndexEventIO/EventWindow.h"


#include "SniperKernel/Incident.h"
#include "SniperKernel/SniperPtr.h"
#include "SniperKernel/SniperDataPtr.h"
#include "SniperKernel/SniperLog.h"
#include "SniperKernel/SniperException.h"
#include <unistd.h>

BeginWinHdl::BeginWinHdl(Task* par)
    : IIncidentHandler(par)
{
    //ROOT::EnableThreadSafety();
    //sleep(5);
    SniperPtr<WinInputSvc> iSvc(par, "InputSvc");
    if ( iSvc.invalid() ) {
        LogFatal << "Cann't find InputSvc for "
                 << par->scope() << par->objName() << std::endl;
        throw SniperException("InputSvc is invalid");
    }
    m_iSvc = iSvc.data();

    SniperDataPtr<FullWinNavBuf> pBuf(par, "/Event");
    if ( pBuf.invalid() ) {
        LogError << "cann't get the EvtNavigator Buffer" << std::endl;
        throw SniperException("NavBuffer is invalid");
    }
    m_buf = pBuf.data();

}

bool BeginWinHdl::handle(Incident& /*incident*/)
{
    auto ref = m_iSvc->next(); 
    LogDebug << "!!! begin !!!"<<std::endl;
    if(ref != nullptr){
        m_buf->reset();        
        auto window = static_cast<EventWindow*>(ref->dptr);
        if(window==nullptr){
            LogDebug <<"!!! first No tagInfo !!! "<<std::endl;
            return false;
        }
        
        int size = window->size();
        int id = 0;

        while (id < size){
            std::shared_ptr<JM::EvtNavigator >& nav = window->getNav(id);
            int p1count = nav.use_count();                                     
            LogDebug << " !!! share count = "<<p1count<<"!!! "<<std::endl;
            
            //JM::OECHeader *tEventHeader=(JM::OECHeader*)(nav.get())->getHeader("/Event/OEC");
            //JM::OECEvent *tEvent=(JM::OECEvent*)tEventHeader->event("JM::OECEvent");
            //double tenergy = tEvent->getEnergy();
            //LogInfo<<"!!!  task energy = "<<tenergy<<" !!!"<<std::endl;
            m_buf->adopt(nav);
            ++id;
        }
        LogDebug << "!!! end !!!"<<std::endl;
        int curId = window->getCurId();
        LogDebug << "!!! curId = "<<curId <<" !!!"<<std::endl;

        m_buf->setCurId(curId);
        m_buf->setRef(ref);

        //m_gbuf->setDone(ref);
        //delete m_window;        
        //m_gbuf->pop_front(); 

        return true;
    }
    //m_iSvc->setOver();
    return m_domain.stop();

}
