#ifndef IBDEVENT_H
#define IBDEVENT_H
#include "Event/EventObject.h"
#include <string>

#include "TTimeStamp.h"

using namespace std;

namespace JM{
    class IBDEvent:public EventObject{
        public:
            IBDEvent();
            ~IBDEvent();
            void setPE(float pE){ m_pE = pE; }
            float getPE() { return m_pE; }
            void setDE(float dE){ m_dE = dE; }
            float getDE() {return m_dE; }

            void setDist(double dist){m_dist=dist; }
            double getDist() {return m_dist; }
            void setTime(double time){ m_time=time; }
            double getTime() {return m_time; }

        private:
            float m_pE;
            float m_dE;
            double m_dist;
            double m_time;

        public:
            ClassDef(IBDEvent,2)
    };
}
#endif
