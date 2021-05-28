#ifndef IO_INPUT_SVC_H
#define IO_INPUT_SVC_H

#include "SniperMuster/GlobalBuffer.h"
#include "SniperKernel/SvcBase.h"

class IOInputSvcc : public SvcBase
{
    public :

        IOInputSvcc(const std::string& name);
        virtual ~IOInputSvcc();

        bool initialize();
        bool finalize();

        GlobalBuffer::Elem* next();

    private :

        GlobalBuffer* m_gbuf;
        
};

#endif
