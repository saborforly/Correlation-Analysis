#ifndef INDEX_READER_H
#define INDEX_READER_H

#include "SniperKernel/AlgBase.h"
#include "Event/Tag.h"

class IIndexReader {
  public:
    IIndexReader(const std::string& tagFile, const std::string& pathFile);
    virtual ~IIndexReader();
    virtual bool initialize() = 0;

    virtual JM::Tag* getIndexData() = 0;
    virtual std::map<int, std::string> getFileMap() = 0;
    virtual int getMinFileId() = 0;
    virtual int getMaxFileId() = 0;

  protected:
    std::string m_tagFile;
    std::string m_pathFile;
    JM::Tag* m_tag;
    bool m_run;
};
#endif
