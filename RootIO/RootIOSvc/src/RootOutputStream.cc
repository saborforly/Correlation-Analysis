#include "RootIOSvc/RootOutputStream.h"
#include "RootIOUtil/RootFileWriter.h"
#include "RootIOUtil/RootOutputFileManager.h"
#include "EvtNavigator/EvtNavigator.h"
#include "Event/HeaderObject.h"
#include "SniperKernel/SniperLog.h"

RootOutputStream::RootOutputStream(const std::string& headername,
                                   const std::string& treepath)
    : m_headerName(headername)
    , m_path(treepath)
    , m_writer(new RootFileWriter(treepath, headername))
{
}

RootOutputStream::~RootOutputStream()
{
    this->close();
    delete m_writer;
}

const std::string& RootOutputStream::path() const
{
    return m_path;
}

const std::string& RootOutputStream::name() const
{
    return m_headerName;
}

int RootOutputStream::entries()
{
    return m_writer->fileEntries();
}

bool RootOutputStream::write(JM::EvtNavigator* nav)
{
    // Write data and EvtNavigator(if nesserary)
    bool ok = m_writer->write(nav);
    return ok;
}

bool RootOutputStream::close()
{
    if (!m_writer->getFile()) return true;
    LogDebug << "Closing file " << m_writer->getFile()->getName() 
             << std::endl;
    m_writer->close();
    return true;
}

void RootOutputStream::revise()
{
    // Now that some new paths have entered the field view of vision, this stream must be notified
    m_writer->revise();
}

void RootOutputStream::setHeaderName(const std::string& name)
{
    m_headerName = name;
    m_writer->setHeaderName(name);
}

void RootOutputStream::newFile(const std::string& filename)
{
    // Only start a new file if filename differes
    if (m_writer->getFile() && filename == m_writer->getFile()->getName()) {
        return;
    }
    this->close();
    m_writer->newFile(RootOutputFileManager::get()->get_file_with_path(m_path));

    LogDebug << "Start a new file: " << filename
             << "for " << m_path
             << std::endl;
}
