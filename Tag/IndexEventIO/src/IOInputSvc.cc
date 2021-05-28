#include "IndexEventIO/IOInputSvc.h"
#include "SniperKernel/SvcFactory.h"

DECLARE_SERVICE(IOInputSvcc);

IOInputSvcc::IOInputSvcc(const std::string& name)
    : SvcBase(name)
{
}

IOInputSvcc::~IOInputSvcc()
{
}

bool IOInputSvcc::initialize()
{
    m_gbuf = GlobalBuffer::FromStream("GEvtStream");
    return true;
}

bool IOInputSvcc::finalize()
{
    return true;
}

GlobalBuffer::Elem* IOInputSvcc::next()
{
    return m_gbuf->next();
}
