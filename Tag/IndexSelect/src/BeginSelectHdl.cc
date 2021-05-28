#include "SniperMuster/GlobalBuffer.h"
#include "IndexSelect/BeginSelectHdl.h"
#include "IndexSelect/SelectInputSvc.h"
#include "IndexSelect/SelectStore.h"

#include "EvtNavigator/NavBuffer.h"
#include "Event/Tag.h"
#include "SniperKernel/SniperPtr.h"
#include "SniperKernel/SniperDataPtr.h"
#include "SniperKernel/SniperException.h"
#include "SniperKernel/Incident.h"

BeginSelectHdl::BeginSelectHdl(Task* par)
    : IIncidentHandler(par)
{
    SniperPtr<SelectInputSvc> iSvc(par, "InputSvc");
    if ( iSvc.invalid() ) {
        LogFatal << "Cann't find InputSvc for "
                 << par->scope() << par->objName() << std::endl;
        throw SniperException("InputSvc is invalid");
    }
    m_iSvc = iSvc.data();

    SniperDataPtr<SelectStore> pStore(par, "/Tag");
    if ( pStore.invalid() ) {
        LogFatal << "Cann't find Data Store" << std::endl;
        throw SniperException("Data Store is invalid");
    }
    LogDebug << "### TagSelectSvc BeginSelectHdl initialize ###"<<std::endl;

    m_store = pStore.data();
}

bool BeginSelectHdl::handle(Incident& /*incident*/)
{
    GlobalBuffer::TagInfo* ref = m_iSvc->next();
    LogDebug << "### TagSelectSvc BeginSelectHdl handle ###"<<std::endl;
    if ( ref != nullptr ) {
        auto evt = static_cast<JM::EvtNavigator*>(ref->dptr);
        m_store->adopt(evt);
        m_store->setRef(ref);
        return true;
    }
    m_iSvc->setTagInfoOver();
    return m_domain.stop();
}
