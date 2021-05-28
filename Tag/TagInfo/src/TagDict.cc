// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dOdOdIsrcdITagDict
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
#include "Tag.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_JMcLcLTag(void *p = 0);
   static void *newArray_JMcLcLTag(Long_t size, void *p);
   static void delete_JMcLcLTag(void *p);
   static void deleteArray_JMcLcLTag(void *p);
   static void destruct_JMcLcLTag(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::JM::Tag*)
   {
      ::JM::Tag *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::JM::Tag >(0);
      static ::ROOT::TGenericClassInfo 
         instance("JM::Tag", ::JM::Tag::Class_Version(), "Tag.h", 9,
                  typeid(::JM::Tag), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::JM::Tag::Dictionary, isa_proxy, 4,
                  sizeof(::JM::Tag) );
      instance.SetNew(&new_JMcLcLTag);
      instance.SetNewArray(&newArray_JMcLcLTag);
      instance.SetDelete(&delete_JMcLcLTag);
      instance.SetDeleteArray(&deleteArray_JMcLcLTag);
      instance.SetDestructor(&destruct_JMcLcLTag);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::JM::Tag*)
   {
      return GenerateInitInstanceLocal((::JM::Tag*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::JM::Tag*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace JM {
//______________________________________________________________________________
atomic_TClass_ptr Tag::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Tag::Class_Name()
{
   return "JM::Tag";
}

//______________________________________________________________________________
const char *Tag::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::JM::Tag*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Tag::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::JM::Tag*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Tag::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::JM::Tag*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Tag::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::JM::Tag*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace JM
namespace JM {
//______________________________________________________________________________
void Tag::Streamer(TBuffer &R__b)
{
   // Stream an object of class JM::Tag.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(JM::Tag::Class(),this);
   } else {
      R__b.WriteClassBuffer(JM::Tag::Class(),this);
   }
}

} // namespace JM
namespace ROOT {
   // Wrappers around operator new
   static void *new_JMcLcLTag(void *p) {
      return  p ? new(p) ::JM::Tag : new ::JM::Tag;
   }
   static void *newArray_JMcLcLTag(Long_t nElements, void *p) {
      return p ? new(p) ::JM::Tag[nElements] : new ::JM::Tag[nElements];
   }
   // Wrapper around operator delete
   static void delete_JMcLcLTag(void *p) {
      delete ((::JM::Tag*)p);
   }
   static void deleteArray_JMcLcLTag(void *p) {
      delete [] ((::JM::Tag*)p);
   }
   static void destruct_JMcLcLTag(void *p) {
      typedef ::JM::Tag current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::JM::Tag

namespace {
  void TriggerDictionaryInitialization_TagDict_Impl() {
    static const char* headers[] = {
"Tag.h",
0
    };
    static const char* includePaths[] = {
"/junofs/users/liuyan2016/OEC/oec-prototype/Tag/TagInfo",
"/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-Pre2/offline/DataModel/BaseEvent",
"/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-Pre2/offline/DataModel/EDMUtil",
"/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-branch/ExternalLibs/ROOT/6.20.02/include/",
"/junofs/users/liuyan2016/OEC/oec-prototype/Tag/TagInfo/Event/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TagDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
namespace JM{class __attribute__((annotate("$clingAutoload$Tag.h")))  Tag;}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TagDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "Tag.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"JM::Tag", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TagDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TagDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TagDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TagDict() {
  TriggerDictionaryInitialization_TagDict_Impl();
}
