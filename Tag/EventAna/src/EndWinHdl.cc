#include "SniperKernel/SniperPtr.h"
#include "SniperKernel/SniperDataPtr.h"
#include "SniperKernel/SniperException.h"
#include "SniperKernel/Incident.h"
#include "EventAna/EndWinHdl.h"
#include "EventAna/WinOutputSvc.h"
#include "EventAna/FullWinNavBuf.h"

EndWinHdl::EndWinHdl(Task* par)
    : IIncidentHandler(par)
{
    SniperPtr<WinOutputSvc> oSvc(par, "OutputSvc");
    if ( oSvc.invalid() ) {
        LogFatal << "Cann't find OutputSvc for "
                 << par->scope() << par->objName() << std::endl;
        throw SniperException("OutputSvc is invalid");
    }
    m_oSvc = oSvc.data();

    SniperDataPtr<FullWinNavBuf> pBuf(par, "/Event");
    if ( pBuf.invalid() ) {
        LogFatal << "Cann't find Data" << std::endl;
        throw SniperException("Data m_buf is invalid");
    }
    m_buf = pBuf.data();
}

bool EndWinHdl::handle(Incident& /*incident*/)
{
    m_oSvc->setDone( m_buf->ref() );

    return true;
}
