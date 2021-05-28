#ifndef Win_INPUT_SVC_H
#define Win_INPUT_SVC_H

#include "SniperMuster/GlobalBuffer.h"
#include "SniperKernel/SvcBase.h"

class WinInputSvc : public SvcBase
{
    public :

        WinInputSvc(const std::string& name);
        virtual ~WinInputSvc();

        bool initialize();
        bool finalize();

        GlobalBuffer::Elem* next();
        void setOver();

    private :

        GlobalBuffer* m_gbuf;
        
};

#endif
