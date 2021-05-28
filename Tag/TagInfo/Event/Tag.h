#ifndef Tag_H
#define Tag_H

#include "Event/HeaderObject.h"
#include "EDMUtil/SmartRef.h"
#include <string>

namespace JM{
    class Tag: public HeaderObject{
        private:
            int m_fileId;
            long m_entryId;


            float m_energy;
            double m_time;

        public:
            Tag();
            ~Tag();

            //virtual function
            EventObject *event(const std::string &value);
            void setEventEntry(const std::string &eventName, Long64_t &value);
            //void setEvent(OECEvent* value){m_event=value;}

            void setFileId(int fileId){ m_fileId = fileId; }
            int getFileId() { return m_fileId; }
            void setEntryId(long id){ m_entryId = id; }
            long getEntryId() {return m_entryId; }

            void setEnergy(float energy){m_energy=energy; }
            float getEnergy() {return m_energy; }            
            void setTime(double time){ m_time=time; }
            double getTime() {return m_time; }


        public:
            ClassDef(Tag,1)
    };
}

#endif
