#include "Event/IBDEvent.h"
#include <iostream>

ClassImp(JM::IBDEvent);
namespace JM{
    IBDEvent::IBDEvent(){
        m_pE=-1;
        m_dE=-1;
        m_dist=-1;
        m_time=-1;
    }

    IBDEvent::~IBDEvent(){
    }

}
