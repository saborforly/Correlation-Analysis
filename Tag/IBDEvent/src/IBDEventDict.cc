// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dOdOdIsrcdIIBDEventDict
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
#include "IBDEvent.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_JMcLcLIBDEvent(void *p = 0);
   static void *newArray_JMcLcLIBDEvent(Long_t size, void *p);
   static void delete_JMcLcLIBDEvent(void *p);
   static void deleteArray_JMcLcLIBDEvent(void *p);
   static void destruct_JMcLcLIBDEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::JM::IBDEvent*)
   {
      ::JM::IBDEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::JM::IBDEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("JM::IBDEvent", ::JM::IBDEvent::Class_Version(), "IBDEvent.h", 11,
                  typeid(::JM::IBDEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::JM::IBDEvent::Dictionary, isa_proxy, 4,
                  sizeof(::JM::IBDEvent) );
      instance.SetNew(&new_JMcLcLIBDEvent);
      instance.SetNewArray(&newArray_JMcLcLIBDEvent);
      instance.SetDelete(&delete_JMcLcLIBDEvent);
      instance.SetDeleteArray(&deleteArray_JMcLcLIBDEvent);
      instance.SetDestructor(&destruct_JMcLcLIBDEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::JM::IBDEvent*)
   {
      return GenerateInitInstanceLocal((::JM::IBDEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::JM::IBDEvent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace JM {
//______________________________________________________________________________
atomic_TClass_ptr IBDEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *IBDEvent::Class_Name()
{
   return "JM::IBDEvent";
}

//______________________________________________________________________________
const char *IBDEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::JM::IBDEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int IBDEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::JM::IBDEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *IBDEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::JM::IBDEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *IBDEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::JM::IBDEvent*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace JM
namespace JM {
//______________________________________________________________________________
void IBDEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class JM::IBDEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(JM::IBDEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(JM::IBDEvent::Class(),this);
   }
}

} // namespace JM
namespace ROOT {
   // Wrappers around operator new
   static void *new_JMcLcLIBDEvent(void *p) {
      return  p ? new(p) ::JM::IBDEvent : new ::JM::IBDEvent;
   }
   static void *newArray_JMcLcLIBDEvent(Long_t nElements, void *p) {
      return p ? new(p) ::JM::IBDEvent[nElements] : new ::JM::IBDEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_JMcLcLIBDEvent(void *p) {
      delete ((::JM::IBDEvent*)p);
   }
   static void deleteArray_JMcLcLIBDEvent(void *p) {
      delete [] ((::JM::IBDEvent*)p);
   }
   static void destruct_JMcLcLIBDEvent(void *p) {
      typedef ::JM::IBDEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::JM::IBDEvent

namespace {
  void TriggerDictionaryInitialization_IBDEventDict_Impl() {
    static const char* headers[] = {
"IBDEvent.h",
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
#line 1 "IBDEventDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
namespace JM{class __attribute__((annotate("$clingAutoload$IBDEvent.h")))  IBDEvent;}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "IBDEventDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "IBDEvent.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"JM::IBDEvent", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("IBDEventDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_IBDEventDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_IBDEventDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_IBDEventDict() {
  TriggerDictionaryInitialization_IBDEventDict_Impl();
}
