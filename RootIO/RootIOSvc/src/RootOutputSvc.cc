#include "RootIOSvc/RootOutputSvc.h"
#include "SniperKernel/SniperLog.h"
#include "SniperKernel/SvcFactory.h"
#include "SniperKernel/SniperPtr.h"
#include "EvtNavigator/EvtNavigator.h"
#include "RootIOSvc/RootOutputStream.h"
#include "EDMManager.h"
#include "JobInfo.h"
#include "RootIOUtil/RootOutputFileManager.h"

#include "TGeoManager.h"
#include <algorithm>

DECLARE_SERVICE(RootOutputSvc);

RootOutputSvc::RootOutputSvc(const std::string& name)
    : SvcBase(name), m_streamInitialized(false)
{
    declProp("OutputStreams", m_outputFileMap);
}

RootOutputSvc::~RootOutputSvc()
{
}

bool RootOutputSvc::initialize()
{
    LogDebug << "Initializing RootOutputSvc..."
             << std::endl;

    String2String::iterator it, end = m_outputFileMap.end();
    LogDebug << "Output streams list:"
             << std::endl;
    for (it = m_outputFileMap.begin(); it != end; ++it) {
        LogDebug << "Path: " << it->first << "  ==>  " 
                 << "File name: " << it->second
                 << std::endl;
    }

    LogDebug << "RootOutputSvc initialized."
             << std::endl;
    return true;
}

bool RootOutputSvc::finalize()
{
    LogDebug << "Finalizing RootOutputSvc..."
             << std::endl;
    OutputStreamVector::iterator it, end = m_outputStreams.end();
    for (it = m_outputStreams.begin(); it != end; ++it) {
        bool ok = (*it)->close();
        if (!ok) {
            LogError << "Error closing file for " << (*it)->path()
                     << std::endl;
            return false;
        }
    }
    LogDebug << "RootOutputSvc finalized."
             << std::endl;
    return true;
}

bool RootOutputSvc::initializeOutputStream(JM::EvtNavigator* nav)
{
    LogDebug << "Initializing RootOutputStreams..."
             << std::endl;

    // Now, try to confirm the event type of output paths
    for (String2String::iterator it = m_outputFileMap.begin(); it != m_outputFileMap.end(); ++it) {
        JM::HeaderObject* header = nav->getHeader(it->first);
        if (header) {
            m_path2typeMap.insert(std::make_pair(it->first, header->ClassName()));
        }
        else {
            // The EvtNavigator does not hold this output path
            m_path2typeMap.insert(std::make_pair(it->first, "unknown"));
            LogWarn << "Can not find path: " << it->first 
                    << ". Skipped for now" << std::endl;
            m_notYetInitPaths.push_back(it->first);
        }
    }
    
    // Sort the paths according to the priority

    // The first string of the inner vector is the path of the stream to be generated.
    // Rest of the strings are the path of other streams share the same output file(if any).
    std::multimap<int, std::vector<std::string> > priority2paths;

    String2String::iterator it, it2, end  = m_outputFileMap.end();
    for (it = m_outputFileMap.begin(); it != end; ++it) {
        // Get priority of this path, get 0 out of a "unknown" path
        int priority;
        const std::string& headerType = m_path2typeMap[it->first];
        if ("unknown" == headerType) {
            priority = 0;
        }
        else {
            priority = EDMManager::get()->getPriorityWithHeader(headerType);
        }
        std::vector<std::string> paths;
        paths.push_back(it->first);
        for (it2 = m_outputFileMap.begin(); it2 != end; ++it2) {
            // Don't add primary path again
            if (*it == *it2) { continue; }
            // Add the path shares the same output file
            if (it2->second == it->second) { paths.push_back(it2->first); }
        }
        // Map, should be automatically sorted.
        priority2paths.insert(std::make_pair(priority, paths));
    }

    // Now create output file and initialize RootOutputStreams.
    std::multimap<int, std::vector<std::string> >::iterator pit, pend = priority2paths.end();
    for (pit = priority2paths.begin(); pit != pend; ++pit) {
        // Create output file
        std::map<std::string, int> path2priority;
        std::vector<std::string>::iterator oit, oend = pit->second.end();
        for (oit = pit->second.begin(); oit != oend; ++oit) {
            int opriority;
            const std::string& headerType = m_path2typeMap[*oit];
            if ("unknown" == headerType) {
                opriority = 0;
            }
            else {
                opriority = EDMManager::get()->getPriorityWithHeader(headerType);
            }
            path2priority.insert(std::make_pair(*oit, opriority));
        }
        std::string primary_path = pit->second[0];
        // RootOutputFileManager won't create dupilicated output files
        RootOutputFileManager::get()->new_file(m_outputFileMap[primary_path], path2priority);
        // Create output stream
        RootOutputStream* stream = new RootOutputStream(m_path2typeMap[primary_path], primary_path);
        // Start the output file
        stream->newFile(m_outputFileMap[primary_path]);
        // Then the vector is sorted according to priotity
        m_outputStreams.push_back(stream);
    }

    OutputObjMap::iterator eit, eend = m_exOutputObjs.end();
    for (eit = m_exOutputObjs.begin(); eit != eend; ++eit) {
        LogDebug << "Attach Obj: " << eit->first << std::endl;
        doAttachObj(eit->first, eit->second);
    }
    m_streamInitialized = true;
    LogDebug << "All RootOutputStreams are Initialized."
             << std::endl;
    return true;
}

bool RootOutputSvc::write(JM::EvtNavigator* nav)
{
    if (!nav) {
        LogError << "No EvtNavigator, can not write"
                 << std::endl;
        return false;
    }

    if (!m_streamInitialized) {
        // Output streams are not initialized yet
        bool ok = initializeOutputStream(nav);
        if (!ok) {
            LogError << "Fail to initialize output streams" 
                     << std::endl;
            return false;
        }
    }

    // Do we need to initialize the not yet initialized streams?
    StringVector::iterator nit, nend = m_notYetInitPaths.end();
    for (nit = m_notYetInitPaths.begin(); nit != nend; ++nit) {
        JM::HeaderObject* header = nav->getHeader(*nit);
        if (header) {
            // Now we have got the "unknown" path, revise the corresponing output stream
            bool ok = reviseOutputStream(*nit, header->ClassName());
            if (!ok) {
                LogError << "Fail to re-initialize output streams"
                         << std::endl;
                return false;
            }
        }
    }

    LogDebug << "Writing data to output files..."
             << std::endl;

    OutputStreamVector::iterator it, end = m_outputStreams.end();
    for (it = m_outputStreams.begin(); it != end; ++it) {
        bool write = nav->writePath((*it)->path());
        if (!write) {
            // TODO can not just skip it
            LogDebug << "Skipping path: " << (*it)->path()
                     << std::endl;
            continue;
        }
        LogDebug << "Writing path: " << (*it)->path()
                 << std::endl;
        bool ok = (*it)->write(nav);
        if (!ok) {
            LogError << "Fail to write stream for path: " << (*it)->path()
                     << std::endl;
            return false;
        }
    }
    LogDebug << "Finish write(JM::EvtNavigator*)" << std::endl;
    return true;
}

bool RootOutputSvc::reviseOutputStream(const std::string& path, const std::string& headerName)
{
    OutputStreamVector::iterator it, pos, end = m_outputStreams.end();
    for (it = m_outputStreams.begin(); it != end; ++it) {
        if (path == (*it)->path()) {
            // Reset the header and event name of this stream
            (*it)->setHeaderName(headerName);
            // Notify the output file
            int priority = EDMManager::get()->getPriorityWithHeader(headerName);
            RootOutputFileManager::get()->reviseOutputFile(m_outputFileMap[path], path, priority);
            for (pos = it + 1; pos != end; ++pos) {
                if (priority >= EDMManager::get()->getPriorityWithHeader((*pos)->name())) {
                    std::swap(*it, *pos);
                } 
            }
            // Here we assume that one path has only one stream
            break;
        }
    }
    // Notify other output streams
    for (it = m_outputStreams.begin(); it != end; ++it) {
        if (path == (*it)->path()) {
            continue;
        }
        (*it)->revise();
    }
    return true;
}

bool RootOutputSvc::attachObj(const std::string& path, TObject* obj) 
{
    if ("all" == path) {
        for (String2String::iterator it = m_outputFileMap.begin();it != m_outputFileMap.end(); ++it) {
            bool ok = this->attachObj(it->first, obj);
            if (!ok) {
                return false;
            }
        }
        return true;
    }
    std::pair<OutputObjMap::iterator, OutputObjMap::iterator> pos = m_exOutputObjs.equal_range(path);
    OutputObjMap::iterator it;
    for (it = pos.first; it != pos.second; ++it) {
        if (it->second == obj) {
            LogError << "Found duplicated object, failed to attach"
                     << std::endl;
            return false;
        }
    }
    m_exOutputObjs.insert(std::make_pair(path,obj));
    LogDebug << "Attach Obj: " << path << std::endl;
    if (m_streamInitialized) {
        return doAttachObj(path, obj);
    }
    return true;
}

bool RootOutputSvc::doAttachObj(const std::string& path, TObject* obj)
{
    String2String::iterator pos = m_outputFileMap.find(path);
    if (pos != m_outputFileMap.end()) {
        RootOutputFileHandle* file = RootOutputFileManager::get()->get_file_with_name(pos->second);
        if (strcmp(obj->ClassName(), "TGeoManager") == 0) {
            file->addGeoManager(static_cast<TGeoManager*>(obj));
            return true;
        }
        if (strcmp(obj->ClassName(), "JobInfo") == 0) { 
            file->setJobInfo(static_cast<JobInfo*>(obj)); 
            return true; 
        }
        return true;
    }
    // Miss
    LogError << "Can not find output stream: " << path 
             << ". Failed to attach " << obj->ClassName()
             << std::endl;
    return false;
}
