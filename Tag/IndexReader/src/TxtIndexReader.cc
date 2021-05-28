#include "IndexReader/TxtIndexReader.h"
#include "SniperKernel/SniperLog.h"
#include "SniperKernel/SniperPtr.h"

#include "TTimeStamp.h"


TxtIndexReader::TxtIndexReader(const std::string& tagFile, const std::string& pathFile) :  IIndexReader(tagFile, pathFile) {
    m_tag = new JM::Tag();
}

TxtIndexReader::~TxtIndexReader() {
    m_fileMap.clear();
    delete m_tag;
}

bool
TxtIndexReader::initialize(){


    m_inpath.open(m_pathFile, std::ios::in);
    m_intag.open(m_tagFile, std::ios::in);
    if(!m_inpath || !m_intag){
        LogError << "^^^ No file Find  ^^^" << std::endl;
        return false;
    }
    max_fileId = INT_MIN;
    min_fileId = INT_MAX;
    while(!m_inpath.eof()){
        m_inpath >> m_fileId >> m_filePath;
        if (m_inpath.fail()){
            LogDebug << "^^^ file read finish   ^^^" << std::endl;
            break;
        }   
        if(m_fileId > max_fileId) max_fileId = m_fileId;
        if(m_fileId < min_fileId) min_fileId = m_fileId;
      
        LogDebug << "^^^ BeginReaderHdl id-path = "<<m_fileId<<"-"<<m_filePath<<std::endl;
        m_fileMap.insert ( std::pair<int, std::string>(m_fileId, m_filePath) );
    }
    m_inpath.close();
   
 
    LogInfo << "TxtIndexReader initialize()" << std::endl;
    return true;
}


JM::Tag* TxtIndexReader::getIndexData() {

    if(!m_intag.eof()){
        m_intag >> m_fileId >> m_entryId >> m_energy >>m_time;
        if (m_intag.fail())  return nullptr;

        LogDebug << "^^^ BeginReaderHdl fileId-entryId-energy-time: "<<m_fileId<<"-"<<m_entryId<<"-"<<m_energy<<"-"<<m_time<<std::endl;
        m_tag->setFileId(m_fileId);
        m_tag->setEntryId(m_entryId);
        m_tag->setEnergy(m_energy);
        m_tag->setTime(m_time);
        return m_tag;

    }else{
        m_intag.close();
        LogDebug << "^^^ finish TxtReader ^^^"<<std::endl;
        return nullptr;
    }
}

