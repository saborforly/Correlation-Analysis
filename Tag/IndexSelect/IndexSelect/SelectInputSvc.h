#ifndef Select_INPUT_SVC_H
#define Select_INPUT_SVC_H

#include "SniperMuster/GlobalBuffer.h"
#include "SniperKernel/SvcBase.h"

class SelectInputSvc : public SvcBase
{
    public :

        SelectInputSvc(const std::string& name);
        virtual ~SelectInputSvc();

        bool initialize();
        bool finalize();
        void setTagInfoOver();
        GlobalBuffer::TagInfo* next();

    private :

        GlobalBuffer* m_gbuf;
};

#endif
