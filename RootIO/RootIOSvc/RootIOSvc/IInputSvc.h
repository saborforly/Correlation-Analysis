#ifndef I_INPUT_SVC_H
#define I_INPUT_SVC_H 1

#include <map>
#include <string>
#include <vector>
#include "RootIOSvc/IInputStream.h"

class IInputSvc {

    public:
        typedef std::map<std::string,IInputStream*> InputStreamMap;
        typedef std::vector<std::string>  InputFileList;
        typedef std::map<std::string, InputFileList> InputFileMap;

        IInputSvc() {}
        virtual ~IInputSvc() {}

        virtual IInputStream* getInputStream(const std::string& path) = 0;

};


#endif
