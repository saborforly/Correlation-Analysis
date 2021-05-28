#include "EventAna/WinOutputSvc.h"
#include "SniperKernel/SvcFactory.h"

DECLARE_SERVICE(WinOutputSvc);

WinOutputSvc::WinOutputSvc(const std::string& name)
    : SvcBase(name)
{
}

WinOutputSvc::~WinOutputSvc()
{
}

bool WinOutputSvc::initialize()
{
    m_gbuf = GlobalBuffer::FromStream("GEvtStream");
    return true;
}

bool WinOutputSvc::finalize()
{
    return true;
}

void WinOutputSvc::setDone(GlobalBuffer::Elem* ref)
{
    return m_gbuf->setDone(ref);
}
