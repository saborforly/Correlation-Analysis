#include "IndexReader/IIndexReader.h"
#include "SniperKernel/SniperLog.h"
#include "SniperKernel/SniperPtr.h"

IIndexReader::IIndexReader(const std::string& tagFile, const std::string& pathFile){
  m_tagFile = tagFile;
  m_pathFile= pathFile;
}

IIndexReader::~IIndexReader(){

}

