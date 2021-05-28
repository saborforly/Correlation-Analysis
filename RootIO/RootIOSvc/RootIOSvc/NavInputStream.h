#ifndef NAV_INPUT_STREAM
#define NAV_INPUT_STREAM 0

#include "IInputStream.h"
#include "RootIOStream.h"
#include "EvtNavigator/EvtNavigator.h"

#include <string>
#include <vector>

class RootFileReader;
class NavTreeList;

class NavInputStream : public IInputStream, public RootIOStream {

    typedef std::vector<std::string> StringVector;

    public:
        NavInputStream(const StringVector& file);
        ~NavInputStream();
        // Iniaizlie NavInputStream.
        bool initialize();
        // Get the EvtNavigator just read.
        JM::EvtNavigator* get();
        // Set the absolute entry to read.  If read is true read entry
        bool setEntry(int entry, bool read=true);
        // Set entry to entry + steps.  If read is true read the resulting entry
        bool next(int steps=1, bool read=true);
        // Set entry to entry - steps.  If read is true read the resluting entry
        bool prev(int nsteps=1, bool read=true);
        // Go to the very first entry.
        bool first(bool read=true);
        // Go to the very last entry.
        bool last(bool read=true);
        // Get user object
        bool getObj(TObject*& obj, const std::string& objName);
        // Get current entry number
        long getEntry();
        // Get total entry number
        long getEntries();
        // Get current file name
        std::string streamname();
    private:
        /// Read in current entry.
        bool read();

    private:
        NavTreeList*    m_trees;      // Implementation of TTrees list holding EvtNavigators
        long            m_entry;      // Current entry number
        long            m_entries;    // Total entry numbers
        StringVector    m_files;      // File list
        StringVector    m_navPath;    // Event path list of EvtNavigators
        RootFileReader* m_reader;     // Tool for file-level analyzing(validation, metadata-extraction)
};


#endif
