#ifndef FULL_WIN_NAV_BUF_H
#define FULL_WIN_NAV_BUF_H

#include "EvtNavigator/NavBuffer.h"
#include "SniperMuster/GlobalBuffer.h"
class FullWinNavBuf : public JM::NavBuffer
{
    public :

        FullWinNavBuf();

        virtual ~FullWinNavBuf();
        void setCurId(int curId);
        bool adopt(std::shared_ptr<JM::EvtNavigator > nav);

        bool reset();
        void setRef(GlobalBuffer::Elem* ref){m_ref = ref;};
        GlobalBuffer::Elem* ref(){ return m_ref;};

    private :
        GlobalBuffer::Elem* m_ref;

};

#endif
