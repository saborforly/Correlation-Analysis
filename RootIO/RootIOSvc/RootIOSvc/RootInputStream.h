#ifndef ROOT_INPUT_STREAM_H
#define ROOT_INPUT_STREAM_H 0

#include "IInputStream.h"
#include "RootIOStream.h"

#include <vector>
#include <string>

class RootInputStream : public IInputStream, public RootIOStream {

    public:
        RootInputStream(const std::vector<std::string>& files) : RootIOStream("RootInputStream") {}
        ~RootInputStream() {}

        virtual TObject* get() { return 0; }
};

#endif
