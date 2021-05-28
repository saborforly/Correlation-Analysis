#include "SniperKernel/AlgBase.h"
#include "SniperKernel/AlgFactory.h"
#include "SniperKernel/SniperLog.h"
#include "SniperMuster/GlobalBuffer.h"
#include <fstream>
#include "IndexEventIO/EventWindow.h"

class GBufPopAlg : public AlgBase
{
    public :

        GBufPopAlg(const std::string& name);
        virtual ~GBufPopAlg();

        bool initialize();
        bool execute();
        bool finalize();

    private :

        GlobalBuffer* m_gbuf;

        std::string   m_fname;
        std::ofstream m_ofs;
};

DECLARE_ALGORITHM(GBufPopAlg);

GBufPopAlg::GBufPopAlg(const std::string& name)
    : AlgBase(name)
{
    declProp("DataFile", m_fname);
}

GBufPopAlg::~GBufPopAlg()
{
}

bool GBufPopAlg::initialize()
{
    m_gbuf = GlobalBuffer::FromStream("GEvtStream");

    if ( ! m_fname.empty() ) {
        //m_ofs.open(m_fname, std::ios::trunc);
    }

    return true;
}

bool GBufPopAlg::execute()
{
    LogDebug<<"+++Output before pop  +++"<<std::endl;
    auto window = static_cast<EventWindow*>(m_gbuf->pop_front());

    if ( window != nullptr ) {
        if ( ! m_fname.empty() ) {
           // m_ofs << evt->getGid() << '\t' << evt->getLid()  << std::endl;
        }
        delete window;
    }
    else {
        m_par->stop();
    }
    LogDebug<<"+++Output after pop+++"<<std::endl;
    return true;
}

bool GBufPopAlg::finalize()
{
    return true;
}

