#ifndef ROOT_IO_STREAM
#define ROOT_IO_STREAM 1

#include <string>

class RootIOStream {

    public:
        RootIOStream(const std::string& name) : m_addr(0), m_name(name) {}
        virtual ~RootIOStream() {}

        const std::string& objName() { return m_name; }

    protected:
        void* m_addr;
        std::string m_name;
};

#endif
