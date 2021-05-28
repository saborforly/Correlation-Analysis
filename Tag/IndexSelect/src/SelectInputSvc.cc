#include "IndexSelect/SelectInputSvc.h"
#include "SniperKernel/SvcFactory.h"

DECLARE_SERVICE(SelectInputSvc);

SelectInputSvc::SelectInputSvc(const std::string& name)
    : SvcBase(name)
{
}

SelectInputSvc::~SelectInputSvc()
{
}

bool SelectInputSvc::initialize()
{
    m_gbuf = GlobalBuffer::FromStream("GEvtStream");
    return true;
}

bool SelectInputSvc::finalize()
{
    return true;
}


GlobalBuffer::TagInfo* SelectInputSvc::next()
{
    return m_gbuf->tagInfo_next();
}
void SelectInputSvc::setTagInfoOver()
{
    m_gbuf->setTagInfoOver(2);
}

