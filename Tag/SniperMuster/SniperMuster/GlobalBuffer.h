/* Copyright (C) 2020
   LiuYan <liuyan2016@ihep.ac.cn>
   Jiaheng Zou <zoujh@ihep.ac.cn> Tao Lin <lintao@ihep.ac.cn>
   Weidong Li <liwd@ihep.ac.cn> Xingtao Huang <huangxt@sdu.edu.cn>
   This file is part of mt.sniper.
 
   mt.sniper is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
 
   mt.sniper is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.
 
   You should have received a copy of the GNU Lesser General Public License
   along with mt.sniper.  If not, see <http://www.gnu.org/licenses/>. */

#ifndef SNIPER_GLOBAL_BUFFER_H
#define SNIPER_GLOBAL_BUFFER_H

#include <string>
#include <mutex>
#include <condition_variable>
#include <deque>
#include <map>
class GlobalBuffer
{
    public :

        static GlobalBuffer* FromStream(const std::string& name);

        struct Elem {
            void*  dptr;
            // -1:invalid, 0:ready, 1:being processed, 2:done
            long   stat;
            Elem*  next;
        };

        GlobalBuffer(int capacity, int cordon);
        virtual ~GlobalBuffer();

        void  push_back(void* dptr);
        void* pop_front();
        Elem* next();

        void  setDone(Elem* data);

        void  setOver(int step);
        unsigned int rough_size();

        void setIdPath(std::map<int, std::string>& idPath);
        void setMinMaxFileId(int minFileId, int maxFileId);
        int getMinFileId();
        int getMaxFileId();
        std::map<int, std::string>& getIdPath();

        struct TagInfo{
            void*  dptr;
            long   stat;

            TagInfo* next; 
        };
        void tagInfo_push(void* dptr);
        TagInfo* tagInfo_next();
        TagInfo* tagInfo_pop();
        void tagInfo_popDone(TagInfo* data);
        void tagInfo_setSel(TagInfo* data);
        void tagInfo_setNoSel(TagInfo* data);
        void setTagInfoOver(int step);  

        /*
        struct TagSel{
            int fileId;
            long entryId;
        };
        void tagSel_push(int fileId, long entryId);
        TagSel tagSel_pop(); 
        */

    private :
        std::map<int, std::string> m_idPath;
        int m_minFileId;
        int m_MaxFileId;
        std::mutex m_mutex_idPath; 
        std::condition_variable  m_idPathCond;

        int m_tagInfoSize;
        TagInfo* m_tagInfo_store;
        TagInfo* m_tagInfo_ref;
        TagInfo* m_tagInfo_begin;
        TagInfo* m_tagInfo_end;
        std::mutex               m_infotemp;
        std::mutex               m_info0;
        std::mutex               m_info1;
        std::condition_variable  m_tagInfoPopCond;
        std::condition_variable  m_tagInfoPushCond;
        std::condition_variable  m_tagInfoNextCond; 
        /*
        std::deque<TagSel> m_deque;
        int m_queSize;
        TagSel m_tag;
        std::mutex               m_deq0;
        std::mutex               m_deq1;
        std::condition_variable  m_deqPopCond;
        std::condition_variable  m_deqPushCond;
        */

        unsigned int  m_capacity;
        unsigned int  m_cordon;
        Elem*         m_store;

        Elem*         m_begin;
        Elem*         m_end;
        Elem*         m_ref;
        std::mutex               m_munav;
        std::mutex               m_mutemp;
        std::mutex               m_mutex0;
        std::mutex               m_mutex1;
        std::condition_variable  m_slotCond;
        std::condition_variable  m_dataCond;
        std::condition_variable  m_doneCond;
};

#endif
