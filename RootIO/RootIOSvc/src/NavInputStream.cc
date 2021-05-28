#include "RootIOSvc/NavInputStream.h"
#include "RootIOUtil/NavTreeList.h"
#include "RootIOUtil/RootFileReader.h"
#include "InputElementKeeper.h"
#include "SniperKernel/SniperLog.h"

NavInputStream::NavInputStream(const StringVector& file)
    : RootIOStream("NavInputStream")
    , m_trees(0)
    , m_entry(-1)
    , m_entries(-1)
    , m_files(file)
    , m_reader(0)
{
}

NavInputStream::~NavInputStream()
{
    delete m_trees;
    delete m_reader;
}

bool NavInputStream::initialize()
{
    // Initialize NavInputStream
    m_reader = new RootFileReader(m_files, true);
    bool okay = m_reader->checkAndExecute();
    if (!okay) {
        LogError << "Reasonableness check of input file failed, please check input file list"
                 << std::endl;
        return false;
    }

    m_trees = m_reader->getNavTree();
    m_navPath = m_reader->getNavPath();
    return true;
}

JM::EvtNavigator* NavInputStream::get()
{
    if (!m_addr) {
        LogError << "No EvtNavigator is loaded"
                 << std::endl;
        return 0;
    }
    JM::EvtNavigator* nav = static_cast<JM::EvtNavigator*>(m_addr);
    nav->setPath(m_navPath);
    nav->resetWriteFlag();
    return nav;
}

bool NavInputStream::read()
{
    void* addr = 0;
    NavTreeHandle* handle = m_trees->current();
    if (!handle) {
        LogError << "No current nav tree"
                 << std::endl;
        return false;
    }

    bool ok = handle->read(addr);
    LogDebug << "Read EvtNavigator at entry " << m_entry
             << " from file " << handle->filename()
             << std::endl;
    if (ok) m_addr = addr;
    return ok;
}

bool NavInputStream::setEntry(int entry, bool read)
{
    int steps = entry - m_entry;
    LogDebug << "Set entry to " << entry
             << std::endl;
    if (steps < 0) return prev(-steps, read);
    if (steps > 0) return next(steps, read);
    return true;                // no change
}

bool NavInputStream::next(int nsteps, bool read)
{
    NavTreeHandle* handle = m_trees->current();

    if (!handle) {
        LogError << "No current nav tree, can't go forward"
                 << std::endl;
        return false;
    }

    LogDebug << "Move forward for " << nsteps << " step(s)"
             << std::endl;

    while (nsteps) {

        // must leave current file?
        if (handle->entry() + nsteps >= handle->entries()) {

            // burn what steps current file provides
            int jump = handle->entries() - (handle->entry() + 1);
            nsteps -= jump;
            m_entry += jump;
            if (!m_trees->next()) {
                LogDebug << "Already at last file, cannot go next"
                         << std::endl;
                return false;
            }
            handle = m_trees->current();
            continue;
        }

        // Current nav tree has enough entries left
        handle->next(nsteps);
        m_entry += nsteps;
        nsteps = 0;
        break;
    }
    LogDebug  << "Now at stream entry " << m_entry
              << " (file: " << handle->filename() << " file entry: " << handle->entry() << ")"
              << std::endl;
    if (read) return this->read();
    return true;
}

bool NavInputStream::prev(int nsteps, bool read)
{
    NavTreeHandle* handle = m_trees->current();
    if (!handle) {
        LogError << "No current nav tree, can't go backward"
                 << std::endl;
        return false;
    }

    LogDebug << "Move forward for " << nsteps << "step(s)"
             << std::endl;

    while (nsteps) {

        // must leave current file?
        if (handle->entry()-nsteps < 0) {

            // Burn what steps this file provides
            int jump = 1 + handle->entry();
            nsteps -= jump;
            m_entry -= jump;
            if (!m_trees->prev()) {
                LogError <<  "Already at first file, cannot go prev"
                         << std::endl;
                return false;
            }
            handle = m_trees->current();
            handle->ending();      // position file entry at end
            continue;
        }

        // Can stay in current file
        handle->prev(nsteps);
        m_entry -= nsteps;
        nsteps = 0;
        break;
    }

    LogDebug << "Now at stream entry " << m_entry
             << " (file: " << handle->filename() << " file entry: " << handle->entry() << ")"
             << std::endl;

    if (read) return this->read();
    return true;
}

bool NavInputStream::first(bool read)
{
    bool okay = m_trees->first();
    if (!okay) {
        LogError << "Failed to go to first tree in stream"
                 << std::endl;
        return false;
    }
    NavTreeHandle* handle = m_trees->current();
    if (!handle) {
        LogError << "Failed to get current tree in stream"
                 << std::endl;
        return false;
    }

    okay = handle->beginning();
    if (!okay) return false;

    m_entry = 0;
    if (read) return this->read();
    return true;
}

bool NavInputStream::last(bool read)
{
    bool okay = m_trees->last();
    if (!okay) {
        LogError << "Failed to go to last tree in stream"
                 << std::endl;
        return false;
    }

    NavTreeHandle* handle = m_trees->current();
    if (!handle) {
        LogError << "Failed to get current tree in stream"
                 << std::endl;
        return false;
    }

    okay = handle->ending();
    if (!okay) return false;

    if (read) return this->read();
    return true;
}

bool NavInputStream::getObj(TObject*& obj, const std::string& objName) 
{
    return InputElementKeeper::GetInputElementKeeper()->GetObj(obj, objName);
}

long NavInputStream::getEntry()
{
    return m_entry;
}

long NavInputStream::getEntries()
{
    if( m_entries>=0 )  return m_entries;
    else {
        m_entries=0;
        NavTreeList::iterator it,itend = m_trees->end();
        for( it=m_trees->begin(); it!=itend; ++it ) {
            m_entries+= (*it)->entries();
        }
        return m_entries;
     }
}

std::string NavInputStream::streamname()
{
    std::string current_name;
    NavTreeHandle* handle = m_trees->current();
    if (!handle) {
        LogError << "No current nav tree"
                 << std::endl;
    } else {
        current_name = handle->filename();
    }

    return current_name;
}
