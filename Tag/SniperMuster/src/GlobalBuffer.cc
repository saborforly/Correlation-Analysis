/* Copyright (C) 2018
   LiuYan<liuyan2016@ihep.ac.cn>
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

#include "SniperMuster/GlobalBuffer.h"
#include "SniperKernel/SniperLog.h"
#include "GlobalStream.h"
#include <iostream>


GlobalBuffer* GlobalBuffer::FromStream(const std::string& name)
{
    auto stream = GlobalStream::Get(name);
    return stream->buffer();
}

GlobalBuffer::GlobalBuffer(int capacity, int cordon)
    : m_capacity(capacity),
      m_cordon(cordon)
{
    if ( m_capacity < 10 ) {
        m_capacity = 10;
        LogWarn << "Capacity is too small, set it to 10" << std::endl;
    }
    if ( m_cordon*1.0/m_capacity < 0.3 ) {
        m_cordon = int(m_capacity*0.3);
        LogWarn << "Cordon is too small, set it to " << m_cordon << std::endl;
    }

    m_store = new Elem[m_capacity];

    m_end   = m_store + m_capacity;
    for ( m_begin = m_store; m_begin != m_end; ++m_begin ) {
        m_begin->dptr = nullptr;
        m_begin->stat = -1;
        m_begin->next = m_begin + 1;
    }
    (--m_end)->next = m_store;

    m_begin = m_store;
    m_end   = m_begin;
    m_ref   = m_begin;

    //m_queSize=20;
    
    //m_tagInfoSize = 20;
    m_tagInfo_store = new TagInfo[m_capacity];
    m_tagInfo_end   = m_tagInfo_store + m_capacity;
    for ( m_tagInfo_begin = m_tagInfo_store; m_tagInfo_begin != m_tagInfo_end; ++m_tagInfo_begin ) {
        m_tagInfo_begin->dptr = nullptr;
        m_tagInfo_begin->stat = -1;
        m_tagInfo_begin->next = m_tagInfo_begin + 1;
    }
    (--m_tagInfo_end)->next = m_tagInfo_store;
    m_tagInfo_begin = m_tagInfo_store;
    m_tagInfo_end   = m_tagInfo_begin;
    m_tagInfo_ref   = m_tagInfo_begin;
}

GlobalBuffer::~GlobalBuffer()
{
    delete[] m_store;
}


void GlobalBuffer::setIdPath(std::map<int, std::string>& idPath){
    m_idPath = idPath;
    m_idPathCond.notify_one();
}

void GlobalBuffer::setMinMaxFileId(int minFileId, int maxFileId){
    m_minFileId = minFileId;
    m_MaxFileId = maxFileId;   

}

int GlobalBuffer::getMinFileId(){
    return m_minFileId;
}

int GlobalBuffer::getMaxFileId(){
    return m_MaxFileId;
}
std::map<int, std::string>& GlobalBuffer::getIdPath(){
    std::unique_lock<std::mutex> ltmp(m_mutex_idPath);
    m_idPathCond.wait( ltmp,[this] { return m_idPath.size()>0;}); 
    return m_idPath;
}


//all tag
void GlobalBuffer::tagInfo_push(void* dptr)
{   
    std::unique_lock<std::mutex> ltmp(m_infotemp);
    m_tagInfoPushCond.wait( ltmp,[this] { return this->m_tagInfo_end->next->stat == -1; });
    LogDebug<<"+++ TagInfo_push  +++ "<<std::endl;
    ltmp.unlock();

    std::lock_guard<std::mutex> lock(m_info0);
    m_tagInfo_end->dptr = dptr;
    m_tagInfo_end->stat = 0; 
    if ( dptr != nullptr ) {
        m_tagInfo_end = m_tagInfo_end->next;
        m_tagInfoNextCond.notify_one();
    }
    else {
        LogDebug<<"+++ TagInfo_push nullptr  +++ "<<std::endl;
        m_tagInfoNextCond.notify_all();
    }
}

GlobalBuffer::TagInfo* GlobalBuffer::tagInfo_next()
{
    TagInfo* ref = nullptr;
    std::unique_lock<std::mutex> ltmp(m_info0);
    LogDebug<<"+++ TagInfo_next  +++ "<<std::endl;
    m_tagInfoNextCond.wait( ltmp,[this] { return this->m_tagInfo_ref->stat == 0; });
    if ( m_tagInfo_ref->dptr != nullptr ) {
        ref = m_tagInfo_ref;
        ref->stat = 1;
        m_tagInfo_ref = m_tagInfo_ref->next;
    }else{
        LogDebug<<"+++ TagInfo_next nullptr+++ "<<std::endl;
    }

    return ref;

}

void GlobalBuffer::tagInfo_setSel(GlobalBuffer::TagInfo* data)
{
    std::lock_guard<std::mutex> lock(m_info1);
    data->stat = 2;
    m_tagInfoPopCond.notify_one();
}

void GlobalBuffer::tagInfo_setNoSel(GlobalBuffer::TagInfo* data)
{
    std::lock_guard<std::mutex> lock(m_info1);
    data->stat = 3;
    m_tagInfoPopCond.notify_one();
}


GlobalBuffer::TagInfo* GlobalBuffer::tagInfo_pop()
{   
    TagInfo* ref = nullptr;
    LogDebug<<"+++ TagInfo_pop  +++ "<<std::endl;
    std::unique_lock<std::mutex> lock(m_info1);
    m_tagInfoPopCond.wait( lock,[this] { return this->m_tagInfo_begin->stat >= 2; });
    lock.unlock();
    if ( m_tagInfo_begin->dptr != nullptr ) {
        ref = m_tagInfo_begin;         
     
        //m_tagInfo_begin->dptr = nullptr; 
        //m_tagInfo_begin->stat = -1;
        m_tagInfo_begin = m_tagInfo_begin->next;

    }else{
        
        LogDebug<<"+++ TagInfo_pop nullptr +++ "<<std::endl;
    }

    return ref;
}
void GlobalBuffer::tagInfo_popDone(GlobalBuffer::TagInfo* data)
{
    std::lock_guard<std::mutex> lock(m_info1);
    data->stat = -1;
    data->dptr = nullptr;
    int size = m_tagInfo_end - m_tagInfo_begin;
    LogDebug<<"+++ TagInfo_pop nullptr +++ "<<std::endl;
    if ( size < 0 )
        size += m_capacity;
    if( (unsigned int)size < m_cordon){
        m_tagInfoPushCond.notify_one();
    }
}


void GlobalBuffer::setTagInfoOver(int step)
{
    if ( step == 1 ) {
        std::lock_guard<std::mutex> lock(m_infotemp);
        m_tagInfo_end = m_tagInfo_ref;
        m_tagInfo_end->next->stat = -1;
        m_tagInfoPushCond.notify_one();
    }

    else if ( step == 2 ) {
        m_tagInfo_ref->dptr = nullptr;
        tagInfo_setNoSel(m_tagInfo_ref);
    }
    LogDebug <<"+++ set Over tagInfo  step= "<<step<< "+++"<<std::endl;    
}

/*
//be selected tag
void GlobalBuffer::tagSel_push(int fileId, long entryId)
{
    LogDebug<<"+++ deque_pushBack lock before+++ "<<std::endl;
    std::unique_lock<std::mutex> ltmp(m_deq0);
    m_deqPushCond.wait( ltmp,[this] { return this->m_deque.size() < m_queSize; });
    LogDebug<<"+++ deque_pushBack lock after +++ "<<std::endl;
    ltmp.unlock();

    //std::lock_guard<std::mutex> lock(m_mutex0);

    m_tag = {fileId,entryId };
    m_deque.push_back(m_tag);

    m_deqPopCond.notify_one();
}

GlobalBuffer::TagSel GlobalBuffer::tagSel_pop()
{   
    std::unique_lock<std::mutex> ltmp(m_deq1);
    LogDebug<<"+++ pop tag deque size before = "<<m_deque.size()<<"+++"<<std::endl;

    m_deqPopCond.wait( ltmp,[this] { return this->m_deque.size()>0; });
    ltmp.unlock();

    GlobalBuffer::TagSel tag=m_deque.front();
    m_deque.pop_front();
    m_deqPushCond.notify_one();
    return tag;

}
*/

//tagWindow
void GlobalBuffer::push_back(void* dptr)
{
    std::unique_lock<std::mutex> ltmp(m_mutemp);
    LogDebug<<"+++ GlobalBuffer::push_back m_end->next->stat = "<<m_end->next->stat<<" +++"<<std::endl;
    m_slotCond.wait( ltmp,[this] { return this->m_end->next->stat == -1; });
    ltmp.unlock();

    std::lock_guard<std::mutex> lock(m_mutex0);
    m_end->dptr = dptr;
    m_end->stat = 0;
    if ( dptr != nullptr ) {
        LogDebug<<"+++ Window  ref push back = +++"<<std::endl;
        m_end = m_end->next;
        m_dataCond.notify_one();
    }
    else {
        LogDebug<<"+++ Window  ref push back nullptr +++"<<std::endl;
        m_dataCond.notify_all();
    }
    
}

void* GlobalBuffer::pop_front()
{
    void* dptr = nullptr;

    std::unique_lock<std::mutex> lock(m_mutex1);
    LogDebug<<"+++ GlobalBuffer::pop_front m_begin->stat = "<<m_begin->stat<<" +++"<<std::endl;
    m_doneCond.wait( lock,
            [this] { return this->m_begin->stat == 2; }
            );
    lock.unlock();
    // suppose there is only one thread to pop a global buffer
    if ( m_begin->dptr != nullptr ) {
        dptr = m_begin->dptr;
        m_begin->dptr = nullptr;
        m_begin->stat = -1;
        m_begin = m_begin->next;

        if ( this->rough_size() < m_cordon ) { //notify for push_back
            m_slotCond.notify_one();
        }
    }
    LogDebug<<"+++ GlobalBuffer::pop_front finish +++"<<std::endl;
    return dptr;
}

GlobalBuffer::Elem* GlobalBuffer::next()
{
    Elem* ref = nullptr;
    std::unique_lock<std::mutex> lock(m_mutex0);
    LogDebug<<"+++ Window ref nextBefore "<< this->m_ref->stat <<"+++"<<std::endl;
    m_dataCond.wait( lock, [this] { return this->m_ref->stat == 0; } );


    if ( m_ref->dptr != nullptr ) {
        ref = m_ref;
        ref->stat = 1;
        m_ref = m_ref->next;
    }
    return ref;
}

void GlobalBuffer::setDone(GlobalBuffer::Elem* data)
{
    std::lock_guard<std::mutex> lock(m_mutex1);
    data->stat = 2;
    m_doneCond.notify_one();
}

void GlobalBuffer::setOver(int step)
{
    //FIXME: how to free the data memory ?

    if ( step == 1 ) {
        // prevent infinite waiting of the input stream
        std::lock_guard<std::mutex> lock(m_mutemp);
        m_end = m_ref;
        m_end->next->stat = -1;
        m_slotCond.notify_one();
    }
    else if ( step == 2 ) {
        m_ref->dptr = nullptr;
        setDone(m_ref);
    }
    LogDebug <<"+++ set Over step= "<<step<< "+++"<<std::endl;
}

unsigned int GlobalBuffer::rough_size()
{
    // not accurate in multi-threads context
    int size = m_end - m_begin;
    if ( size < 0 )
        size += m_capacity;
    return (unsigned int)size;
}
