
#ifndef Select_STORE_H
#define Select_STORE_H

#include "SniperKernel/IDataBlock.h"
#include "SniperMuster/GlobalBuffer.h"
#include "Event/Tag.h"
#include <memory>
#include "EvtNavigator/NavBuffer.h"

class JM::Tag;

class SelectStore : public IDataBlock
{
    public :

        SelectStore() : m_evt(nullptr) {}
        virtual ~SelectStore();

        void adopt(JM::EvtNavigator* evt);

        JM::EvtNavigator* curEvt() { return m_evt; }

        // for the convenience of testing
        void setRef(GlobalBuffer::TagInfo* ref) { m_ref = ref; }
        GlobalBuffer::TagInfo* ref() { return m_ref; }

    private :

        JM::EvtNavigator* m_evt;

        GlobalBuffer::TagInfo* m_ref;
};

#endif
