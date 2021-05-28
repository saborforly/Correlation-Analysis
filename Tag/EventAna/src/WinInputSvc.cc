#include "EventAna/WinInputSvc.h"
#include "SniperKernel/SvcFactory.h"

DECLARE_SERVICE(WinInputSvc);

WinInputSvc::WinInputSvc(const std::string& name)
    : SvcBase(name)
{
}

WinInputSvc::~WinInputSvc()
{
}

bool WinInputSvc::initialize()
{
    m_gbuf = GlobalBuffer::FromStream("GEvtStream");
    return true;
}

bool WinInputSvc::finalize()
{
    return true;
}

GlobalBuffer::Elem* WinInputSvc::next()
{
    return m_gbuf->next();
}

void WinInputSvc::setOver()
{
    m_gbuf->setOver(2);
}
