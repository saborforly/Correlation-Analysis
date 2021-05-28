#ifndef ROOT_OUTPUT_STREAM_H
#define ROOT_OUTPUT_STREAM_H 0

#include <map>
#include <string>
#include "IOutputStream.h"

namespace JM {
    class EvtNavigator;
}

class RootFileWriter;
class TObject;

class RootOutputStream : public IOutputStream {

public:

    // Other paths to be written to the same file in this stream(if any)
    typedef std::map<std::string, int> PathMap;
    
    RootOutputStream(const std::string& headername, 
                     const std::string& treepath);
    virtual ~RootOutputStream();
    /// RootIOStream interface
    const std::string& path() const;
    const std::string& name() const;
    /// Write current state of addr to disk.
    bool write(JM::EvtNavigator* nav);
    /// Write tree to file and close file.
    bool close();

    void revise();
    /// Set the header name
    void setHeaderName(const std::string& value);
    /// Start a new output file
    void newFile(const std::string& filename);
    /// Return the number of entries in the output stream
    int entries();

private:
    std::string m_headerName, m_path;
    RootFileWriter* m_writer;
};

#endif
