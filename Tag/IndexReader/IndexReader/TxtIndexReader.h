#ifndef TxtIndexReader_H
#define TxtIndexReader_H

#include "IndexReader/IIndexReader.h"
#include <fstream>

class TxtIndexReader: public IIndexReader{
  public:
    TxtIndexReader(const std::string& tagFile, const std::string& pathFile);
    virtual ~TxtIndexReader();
    bool initialize();

    JM::Tag* getIndexData();
    std::map<int, std::string> getFileMap(){
        return m_fileMap;
    }
    int getMinFileId(){
        return min_fileId;
    }
    int getMaxFileId(){
        return max_fileId;
    }

 private:
    std::map<int, std::string> m_fileMap;

    std::ifstream    m_intag;
    std::ifstream    m_inpath;

    int         m_fileId;
    std::string m_filePath;
    int max_fileId;
    int min_fileId;

    long        m_entryId;
    double      m_energy;
    double      m_time;

};
#endif //TxtIndexReader_H
