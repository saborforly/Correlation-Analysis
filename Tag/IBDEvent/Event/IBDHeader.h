#ifndef IBDHEADER_H
#define IBDHEADER_H

#include "Event/HeaderObject.h"
#include "EDMUtil/SmartRef.h"
#include "IBDEvent.h"

using namespace std;

namespace JM{
    class IBDHeader:public HeaderObject{
        public:
            IBDHeader();
            ~IBDHeader();

            //virtual function
            EventObject *event(const string &value);
            void setEventEntry(const string &eventName, Long64_t &value);
            
            void setEvent(IBDEvent* value){m_event=value;}


        private:
            JM::SmartRef m_event;

        public:
            ClassDef(IBDHeader,2)
    };
}

#endif
