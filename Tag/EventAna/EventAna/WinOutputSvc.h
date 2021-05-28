#ifndef WIN_OUTPUT_SVC_H
#define WIN_OUTPUT_SVC_H

#include "SniperMuster/GlobalBuffer.h"
#include "SniperKernel/SvcBase.h"

class WinOutputSvc : public SvcBase
{
    public :

        WinOutputSvc(const std::string& name);
        virtual ~WinOutputSvc();

        bool initialize();
        bool finalize();

        void setDone(GlobalBuffer::Elem* ref);

    private :

        GlobalBuffer* m_gbuf;
};

#endif
