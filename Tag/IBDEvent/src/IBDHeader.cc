#include "Event/IBDHeader.h"

ClassImp(JM::IBDHeader);

namespace JM{
    IBDHeader::IBDHeader(){
    }

    IBDHeader::~IBDHeader(){
    }

    EventObject* IBDHeader::event(const string &value){
        if (value=="JM::IBDEvent"){
            return m_event.GetObject();
        }
        return NULL;
    }
    void IBDHeader::setEventEntry(const string &eventName, Long64_t &value){
        if (eventName=="JM::IBDEvent"){
            m_event.setEntry(value);
        }
    }
}
