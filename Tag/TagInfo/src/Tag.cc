#include "Event/Tag.h"

ClassImp(JM::Tag);

namespace JM{
    Tag::Tag(){
    }

    Tag::~Tag(){
    }

    EventObject* Tag::event(const std::string &value){
        //if (value=="JM::OECEvent"){return m_event.GetObject();}
        return NULL;
    }
    void Tag::setEventEntry(const std::string &eventName, Long64_t &value){
        //if (eventName=="JM::OECEvent"){m_event.setEntry(value);}
    }
}
