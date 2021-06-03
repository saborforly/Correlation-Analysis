// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dOdOdIsrcdIIBDHeaderDict
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// The generated code does not explicitly qualifies STL entities
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "IBDHeader.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_JMcLcLIBDHeader(void *p = 0);
   static void *newArray_JMcLcLIBDHeader(Long_t size, void *p);
   static void delete_JMcLcLIBDHeader(void *p);
   static void deleteArray_JMcLcLIBDHeader(void *p);
   static void destruct_JMcLcLIBDHeader(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::JM::IBDHeader*)
   {
      ::JM::IBDHeader *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::JM::IBDHeader >(0);
      static ::ROOT::TGenericClassInfo 
         instance("JM::IBDHeader", ::JM::IBDHeader::Class_Version(), "IBDHeader.h", 11,
                  typeid(::JM::IBDHeader), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::JM::IBDHeader::Dictionary, isa_proxy, 4,
                  sizeof(::JM::IBDHeader) );
      instance.SetNew(&new_JMcLcLIBDHeader);
      instance.SetNewArray(&newArray_JMcLcLIBDHeader);
      instance.SetDelete(&delete_JMcLcLIBDHeader);
      instance.SetDeleteArray(&deleteArray_JMcLcLIBDHeader);
      instance.SetDestructor(&destruct_JMcLcLIBDHeader);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::JM::IBDHeader*)
   {
      return GenerateInitInstanceLocal((::JM::IBDHeader*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::JM::IBDHeader*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace JM {
//______________________________________________________________________________
atomic_TClass_ptr IBDHeader::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *IBDHeader::Class_Name()
{
   return "JM::IBDHeader";
}

//______________________________________________________________________________
const char *IBDHeader::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::JM::IBDHeader*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int IBDHeader::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::JM::IBDHeader*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *IBDHeader::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::JM::IBDHeader*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *IBDHeader::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::JM::IBDHeader*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace JM
namespace JM {
//______________________________________________________________________________
void IBDHeader::Streamer(TBuffer &R__b)
{
   // Stream an object of class JM::IBDHeader.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(JM::IBDHeader::Class(),this);
   } else {
      R__b.WriteClassBuffer(JM::IBDHeader::Class(),this);
   }
}

} // namespace JM
namespace ROOT {
   // Wrappers around operator new
   static void *new_JMcLcLIBDHeader(void *p) {
      return  p ? new(p) ::JM::IBDHeader : new ::JM::IBDHeader;
   }
   static void *newArray_JMcLcLIBDHeader(Long_t nElements, void *p) {
      return p ? new(p) ::JM::IBDHeader[nElements] : new ::JM::IBDHeader[nElements];
   }
   // Wrapper around operator delete
   static void delete_JMcLcLIBDHeader(void *p) {
      delete ((::JM::IBDHeader*)p);
   }
   static void deleteArray_JMcLcLIBDHeader(void *p) {
      delete [] ((::JM::IBDHeader*)p);
   }
   static void destruct_JMcLcLIBDHeader(void *p) {
      typedef ::JM::IBDHeader current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::JM::IBDHeader

namespace {
  void TriggerDictionaryInitialization_IBDHeaderDict_Impl() {
    static const char* headers[] = {
"IBDHeader.h",
0
    };
    static const char* includePaths[] = {
"/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/IBDEvent",
"/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-Pre2/offline/DataModel/BaseEvent",
"/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-Pre2/offline/DataModel/EDMUtil",
"/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-branch/ExternalLibs/ROOT/6.20.02/include/",
"/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/IBDEvent/Event/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "IBDHeaderDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
namespace JM{class __attribute__((annotate("$clingAutoload$IBDHeader.h")))  IBDHeader;}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "IBDHeaderDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "IBDHeader.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"JM::IBDHeader", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("IBDHeaderDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_IBDHeaderDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_IBDHeaderDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_IBDHeaderDict() {
  TriggerDictionaryInitialization_IBDHeaderDict_Impl();
}
