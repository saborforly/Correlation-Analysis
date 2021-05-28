#include "SniperKernel/AlgBase.h"
#include "SniperKernel/AlgFactory.h"
#include "SniperKernel/SniperLog.h"
#include "SniperMuster/GlobalBuffer.h"
#include <fstream>

class GTagInfoPopAlg : public AlgBase
{
    public :

        GTagInfoPopAlg(const std::string& name);
        virtual ~GTagInfoPopAlg();

        bool initialize();
        bool execute();
        bool finalize();

    private :

        GlobalBuffer* m_gbuf;

        std::string   m_fname;
        std::ofstream m_ofs;
};

DECLARE_ALGORITHM(GTagInfoPopAlg);

GTagInfoPopAlg::GTagInfoPopAlg(const std::string& name)
    : AlgBase(name)
{
    declProp("DataFile", m_fname);
}

GTagInfoPopAlg::~GTagInfoPopAlg()
{
}

bool GTagInfoPopAlg::initialize()
{
    m_gbuf = GlobalBuffer::FromStream("GEvtStream");

    if ( ! m_fname.empty() ) {
        //m_ofs.open(m_fname, std::ios::trunc);
    }

    return true;
}

bool GTagInfoPopAlg::execute()
{
    LogDebug<<"+++Output before pop  +++"<<std::endl;

    GlobalBuffer::TagInfo* tagInfo = m_gbuf->tagInfo_pop();
    if(tagInfo != nullptr){
        m_gbuf->tagInfo_popDone(tagInfo);
    }else{
        m_par->stop();
    }

    LogDebug<<"+++Output after pop+++"<<std::endl;
    return true;
}

bool GTagInfoPopAlg::finalize()
{
    return true;
}

