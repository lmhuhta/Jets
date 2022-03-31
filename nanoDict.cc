// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME nanoDict
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
#include "src/AliJBaseCard.h"
#include "src/AliJCard.h"
#include "src/JHistos.h"
#include "src/AliJBaseTrack.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *AliJBaseCard_Dictionary();
   static void AliJBaseCard_TClassManip(TClass*);
   static void *new_AliJBaseCard(void *p = 0);
   static void *newArray_AliJBaseCard(Long_t size, void *p);
   static void delete_AliJBaseCard(void *p);
   static void deleteArray_AliJBaseCard(void *p);
   static void destruct_AliJBaseCard(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::AliJBaseCard*)
   {
      ::AliJBaseCard *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::AliJBaseCard));
      static ::ROOT::TGenericClassInfo 
         instance("AliJBaseCard", "src/AliJBaseCard.h", 33,
                  typeid(::AliJBaseCard), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &AliJBaseCard_Dictionary, isa_proxy, 0,
                  sizeof(::AliJBaseCard) );
      instance.SetNew(&new_AliJBaseCard);
      instance.SetNewArray(&newArray_AliJBaseCard);
      instance.SetDelete(&delete_AliJBaseCard);
      instance.SetDeleteArray(&deleteArray_AliJBaseCard);
      instance.SetDestructor(&destruct_AliJBaseCard);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::AliJBaseCard*)
   {
      return GenerateInitInstanceLocal((::AliJBaseCard*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::AliJBaseCard*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *AliJBaseCard_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::AliJBaseCard*)0x0)->GetClass();
      AliJBaseCard_TClassManip(theClass);
   return theClass;
   }

   static void AliJBaseCard_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static void *new_AliJBaseTrack(void *p = 0);
   static void *newArray_AliJBaseTrack(Long_t size, void *p);
   static void delete_AliJBaseTrack(void *p);
   static void deleteArray_AliJBaseTrack(void *p);
   static void destruct_AliJBaseTrack(void *p);
   static void streamer_AliJBaseTrack(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::AliJBaseTrack*)
   {
      ::AliJBaseTrack *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::AliJBaseTrack >(0);
      static ::ROOT::TGenericClassInfo 
         instance("AliJBaseTrack", ::AliJBaseTrack::Class_Version(), "src/AliJBaseTrack.h", 33,
                  typeid(::AliJBaseTrack), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::AliJBaseTrack::Dictionary, isa_proxy, 16,
                  sizeof(::AliJBaseTrack) );
      instance.SetNew(&new_AliJBaseTrack);
      instance.SetNewArray(&newArray_AliJBaseTrack);
      instance.SetDelete(&delete_AliJBaseTrack);
      instance.SetDeleteArray(&deleteArray_AliJBaseTrack);
      instance.SetDestructor(&destruct_AliJBaseTrack);
      instance.SetStreamerFunc(&streamer_AliJBaseTrack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::AliJBaseTrack*)
   {
      return GenerateInitInstanceLocal((::AliJBaseTrack*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::AliJBaseTrack*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *AliJCard_Dictionary();
   static void AliJCard_TClassManip(TClass*);
   static void *new_AliJCard(void *p = 0);
   static void *newArray_AliJCard(Long_t size, void *p);
   static void delete_AliJCard(void *p);
   static void deleteArray_AliJCard(void *p);
   static void destruct_AliJCard(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::AliJCard*)
   {
      ::AliJCard *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::AliJCard));
      static ::ROOT::TGenericClassInfo 
         instance("AliJCard", "src/AliJCard.h", 44,
                  typeid(::AliJCard), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &AliJCard_Dictionary, isa_proxy, 0,
                  sizeof(::AliJCard) );
      instance.SetNew(&new_AliJCard);
      instance.SetNewArray(&newArray_AliJCard);
      instance.SetDelete(&delete_AliJCard);
      instance.SetDeleteArray(&deleteArray_AliJCard);
      instance.SetDestructor(&destruct_AliJCard);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::AliJCard*)
   {
      return GenerateInitInstanceLocal((::AliJCard*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::AliJCard*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *AliJCard_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::AliJCard*)0x0)->GetClass();
      AliJCard_TClassManip(theClass);
   return theClass;
   }

   static void AliJCard_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *JHistos_Dictionary();
   static void JHistos_TClassManip(TClass*);
   static void delete_JHistos(void *p);
   static void deleteArray_JHistos(void *p);
   static void destruct_JHistos(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::JHistos*)
   {
      ::JHistos *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::JHistos));
      static ::ROOT::TGenericClassInfo 
         instance("JHistos", "src/JHistos.h", 29,
                  typeid(::JHistos), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &JHistos_Dictionary, isa_proxy, 0,
                  sizeof(::JHistos) );
      instance.SetDelete(&delete_JHistos);
      instance.SetDeleteArray(&deleteArray_JHistos);
      instance.SetDestructor(&destruct_JHistos);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::JHistos*)
   {
      return GenerateInitInstanceLocal((::JHistos*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::JHistos*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *JHistos_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::JHistos*)0x0)->GetClass();
      JHistos_TClassManip(theClass);
   return theClass;
   }

   static void JHistos_TClassManip(TClass* ){
   }

} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr AliJBaseTrack::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *AliJBaseTrack::Class_Name()
{
   return "AliJBaseTrack";
}

//______________________________________________________________________________
const char *AliJBaseTrack::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AliJBaseTrack*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int AliJBaseTrack::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AliJBaseTrack*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *AliJBaseTrack::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AliJBaseTrack*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *AliJBaseTrack::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AliJBaseTrack*)0x0)->GetClass(); }
   return fgIsA;
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_AliJBaseCard(void *p) {
      return  p ? new(p) ::AliJBaseCard : new ::AliJBaseCard;
   }
   static void *newArray_AliJBaseCard(Long_t nElements, void *p) {
      return p ? new(p) ::AliJBaseCard[nElements] : new ::AliJBaseCard[nElements];
   }
   // Wrapper around operator delete
   static void delete_AliJBaseCard(void *p) {
      delete ((::AliJBaseCard*)p);
   }
   static void deleteArray_AliJBaseCard(void *p) {
      delete [] ((::AliJBaseCard*)p);
   }
   static void destruct_AliJBaseCard(void *p) {
      typedef ::AliJBaseCard current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::AliJBaseCard

//______________________________________________________________________________
void AliJBaseTrack::Streamer(TBuffer &R__b)
{
   // Stream an object of class AliJBaseTrack.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TLorentzVector::Streamer(R__b);
      R__b >> fID;
      R__b >> fLabel;
      R__b >> fParticleType;
      R__b >> fCharge;
      R__b >> fStatus;
      R__b >> fFlags;
      R__b.CheckByteCount(R__s, R__c, AliJBaseTrack::IsA());
   } else {
      R__c = R__b.WriteVersion(AliJBaseTrack::IsA(), kTRUE);
      TLorentzVector::Streamer(R__b);
      R__b << fID;
      R__b << fLabel;
      R__b << fParticleType;
      R__b << fCharge;
      R__b << fStatus;
      R__b << fFlags;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_AliJBaseTrack(void *p) {
      return  p ? new(p) ::AliJBaseTrack : new ::AliJBaseTrack;
   }
   static void *newArray_AliJBaseTrack(Long_t nElements, void *p) {
      return p ? new(p) ::AliJBaseTrack[nElements] : new ::AliJBaseTrack[nElements];
   }
   // Wrapper around operator delete
   static void delete_AliJBaseTrack(void *p) {
      delete ((::AliJBaseTrack*)p);
   }
   static void deleteArray_AliJBaseTrack(void *p) {
      delete [] ((::AliJBaseTrack*)p);
   }
   static void destruct_AliJBaseTrack(void *p) {
      typedef ::AliJBaseTrack current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_AliJBaseTrack(TBuffer &buf, void *obj) {
      ((::AliJBaseTrack*)obj)->::AliJBaseTrack::Streamer(buf);
   }
} // end of namespace ROOT for class ::AliJBaseTrack

namespace ROOT {
   // Wrappers around operator new
   static void *new_AliJCard(void *p) {
      return  p ? new(p) ::AliJCard : new ::AliJCard;
   }
   static void *newArray_AliJCard(Long_t nElements, void *p) {
      return p ? new(p) ::AliJCard[nElements] : new ::AliJCard[nElements];
   }
   // Wrapper around operator delete
   static void delete_AliJCard(void *p) {
      delete ((::AliJCard*)p);
   }
   static void deleteArray_AliJCard(void *p) {
      delete [] ((::AliJCard*)p);
   }
   static void destruct_AliJCard(void *p) {
      typedef ::AliJCard current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::AliJCard

namespace ROOT {
   // Wrapper around operator delete
   static void delete_JHistos(void *p) {
      delete ((::JHistos*)p);
   }
   static void deleteArray_JHistos(void *p) {
      delete [] ((::JHistos*)p);
   }
   static void destruct_JHistos(void *p) {
      typedef ::JHistos current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::JHistos

namespace {
  void TriggerDictionaryInitialization_nanoDict_Impl() {
    static const char* headers[] = {
"src/AliJBaseCard.h",
"src/AliJCard.h",
"src/JHistos.h",
"src/AliJBaseTrack.h",
0
    };
    static const char* includePaths[] = {
"/home/alidock/.sw/slc7_x86-64/ROOT/v6-20-08-alice1-local1/include/",
"/home/alidock/software/FlowJet/Jet/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "nanoDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$src/AliJBaseCard.h")))  AliJBaseCard;
class __attribute__((annotate("$clingAutoload$AliJBaseTrack.h")))  __attribute__((annotate("$clingAutoload$src/AliJCard.h")))  AliJBaseTrack;
class __attribute__((annotate("$clingAutoload$src/AliJCard.h")))  AliJCard;
class __attribute__((annotate("$clingAutoload$src/JHistos.h")))  JHistos;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "nanoDict dictionary payload"

#ifndef JTKT
  #define JTKT 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "src/AliJBaseCard.h"
#include "src/AliJCard.h"
#include "src/JHistos.h"
#include "src/AliJBaseTrack.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"AliJBaseCard", payloadCode, "@",
"AliJBaseTrack", payloadCode, "@",
"AliJCard", payloadCode, "@",
"JHistos", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("nanoDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_nanoDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_nanoDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_nanoDict() {
  TriggerDictionaryInitialization_nanoDict_Impl();
}
