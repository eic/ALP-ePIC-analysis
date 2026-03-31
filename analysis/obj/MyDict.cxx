// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME objdIMyDict
#define R__NO_DEPRECATION

/*******************************************************************/
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#define G__DICTIONARY
#include "ROOT/RConfig.hxx"
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

// Header files passed as explicit arguments
#include "MyAnalysis.h"
#include "MyEvent.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static TClass *MyParticle_Dictionary();
   static void MyParticle_TClassManip(TClass*);
   static void *new_MyParticle(void *p = nullptr);
   static void *newArray_MyParticle(Long_t size, void *p);
   static void delete_MyParticle(void *p);
   static void deleteArray_MyParticle(void *p);
   static void destruct_MyParticle(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MyParticle*)
   {
      ::MyParticle *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::MyParticle));
      static ::ROOT::TGenericClassInfo 
         instance("MyParticle", "MyEvent.h", 21,
                  typeid(::MyParticle), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &MyParticle_Dictionary, isa_proxy, 4,
                  sizeof(::MyParticle) );
      instance.SetNew(&new_MyParticle);
      instance.SetNewArray(&newArray_MyParticle);
      instance.SetDelete(&delete_MyParticle);
      instance.SetDeleteArray(&deleteArray_MyParticle);
      instance.SetDestructor(&destruct_MyParticle);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MyParticle*)
   {
      return GenerateInitInstanceLocal(static_cast<::MyParticle*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::MyParticle*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *MyParticle_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::MyParticle*>(nullptr))->GetClass();
      MyParticle_TClassManip(theClass);
   return theClass;
   }

   static void MyParticle_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *MyEvent_Dictionary();
   static void MyEvent_TClassManip(TClass*);
   static void *new_MyEvent(void *p = nullptr);
   static void *newArray_MyEvent(Long_t size, void *p);
   static void delete_MyEvent(void *p);
   static void deleteArray_MyEvent(void *p);
   static void destruct_MyEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MyEvent*)
   {
      ::MyEvent *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::MyEvent));
      static ::ROOT::TGenericClassInfo 
         instance("MyEvent", "MyEvent.h", 56,
                  typeid(::MyEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &MyEvent_Dictionary, isa_proxy, 4,
                  sizeof(::MyEvent) );
      instance.SetNew(&new_MyEvent);
      instance.SetNewArray(&newArray_MyEvent);
      instance.SetDelete(&delete_MyEvent);
      instance.SetDeleteArray(&deleteArray_MyEvent);
      instance.SetDestructor(&destruct_MyEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MyEvent*)
   {
      return GenerateInitInstanceLocal(static_cast<::MyEvent*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::MyEvent*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *MyEvent_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::MyEvent*>(nullptr))->GetClass();
      MyEvent_TClassManip(theClass);
   return theClass;
   }

   static void MyEvent_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *MyAnalysis_Dictionary();
   static void MyAnalysis_TClassManip(TClass*);
   static void *new_MyAnalysis(void *p = nullptr);
   static void *newArray_MyAnalysis(Long_t size, void *p);
   static void delete_MyAnalysis(void *p);
   static void deleteArray_MyAnalysis(void *p);
   static void destruct_MyAnalysis(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MyAnalysis*)
   {
      ::MyAnalysis *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::MyAnalysis));
      static ::ROOT::TGenericClassInfo 
         instance("MyAnalysis", "MyAnalysis.h", 23,
                  typeid(::MyAnalysis), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &MyAnalysis_Dictionary, isa_proxy, 4,
                  sizeof(::MyAnalysis) );
      instance.SetNew(&new_MyAnalysis);
      instance.SetNewArray(&newArray_MyAnalysis);
      instance.SetDelete(&delete_MyAnalysis);
      instance.SetDeleteArray(&deleteArray_MyAnalysis);
      instance.SetDestructor(&destruct_MyAnalysis);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MyAnalysis*)
   {
      return GenerateInitInstanceLocal(static_cast<::MyAnalysis*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::MyAnalysis*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *MyAnalysis_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::MyAnalysis*>(nullptr))->GetClass();
      MyAnalysis_TClassManip(theClass);
   return theClass;
   }

   static void MyAnalysis_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_MyParticle(void *p) {
      return  p ? new(p) ::MyParticle : new ::MyParticle;
   }
   static void *newArray_MyParticle(Long_t nElements, void *p) {
      return p ? new(p) ::MyParticle[nElements] : new ::MyParticle[nElements];
   }
   // Wrapper around operator delete
   static void delete_MyParticle(void *p) {
      delete (static_cast<::MyParticle*>(p));
   }
   static void deleteArray_MyParticle(void *p) {
      delete [] (static_cast<::MyParticle*>(p));
   }
   static void destruct_MyParticle(void *p) {
      typedef ::MyParticle current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::MyParticle

namespace ROOT {
   // Wrappers around operator new
   static void *new_MyEvent(void *p) {
      return  p ? new(p) ::MyEvent : new ::MyEvent;
   }
   static void *newArray_MyEvent(Long_t nElements, void *p) {
      return p ? new(p) ::MyEvent[nElements] : new ::MyEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_MyEvent(void *p) {
      delete (static_cast<::MyEvent*>(p));
   }
   static void deleteArray_MyEvent(void *p) {
      delete [] (static_cast<::MyEvent*>(p));
   }
   static void destruct_MyEvent(void *p) {
      typedef ::MyEvent current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::MyEvent

namespace ROOT {
   // Wrappers around operator new
   static void *new_MyAnalysis(void *p) {
      return  p ? new(p) ::MyAnalysis : new ::MyAnalysis;
   }
   static void *newArray_MyAnalysis(Long_t nElements, void *p) {
      return p ? new(p) ::MyAnalysis[nElements] : new ::MyAnalysis[nElements];
   }
   // Wrapper around operator delete
   static void delete_MyAnalysis(void *p) {
      delete (static_cast<::MyAnalysis*>(p));
   }
   static void deleteArray_MyAnalysis(void *p) {
      delete [] (static_cast<::MyAnalysis*>(p));
   }
   static void destruct_MyAnalysis(void *p) {
      typedef ::MyAnalysis current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::MyAnalysis

namespace ROOT {
   static TClass *vectorlEvectorlEedm4eiccLcLTrackPointgRsPgR_Dictionary();
   static void vectorlEvectorlEedm4eiccLcLTrackPointgRsPgR_TClassManip(TClass*);
   static void *new_vectorlEvectorlEedm4eiccLcLTrackPointgRsPgR(void *p = nullptr);
   static void *newArray_vectorlEvectorlEedm4eiccLcLTrackPointgRsPgR(Long_t size, void *p);
   static void delete_vectorlEvectorlEedm4eiccLcLTrackPointgRsPgR(void *p);
   static void deleteArray_vectorlEvectorlEedm4eiccLcLTrackPointgRsPgR(void *p);
   static void destruct_vectorlEvectorlEedm4eiccLcLTrackPointgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<vector<edm4eic::TrackPoint> >*)
   {
      vector<vector<edm4eic::TrackPoint> > *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<vector<edm4eic::TrackPoint> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<vector<edm4eic::TrackPoint> >", -2, "vector", 428,
                  typeid(vector<vector<edm4eic::TrackPoint> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEvectorlEedm4eiccLcLTrackPointgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<vector<edm4eic::TrackPoint> >) );
      instance.SetNew(&new_vectorlEvectorlEedm4eiccLcLTrackPointgRsPgR);
      instance.SetNewArray(&newArray_vectorlEvectorlEedm4eiccLcLTrackPointgRsPgR);
      instance.SetDelete(&delete_vectorlEvectorlEedm4eiccLcLTrackPointgRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEvectorlEedm4eiccLcLTrackPointgRsPgR);
      instance.SetDestructor(&destruct_vectorlEvectorlEedm4eiccLcLTrackPointgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<vector<edm4eic::TrackPoint> > >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<vector<edm4eic::TrackPoint> >","std::vector<std::vector<edm4eic::TrackPoint, std::allocator<edm4eic::TrackPoint> >, std::allocator<std::vector<edm4eic::TrackPoint, std::allocator<edm4eic::TrackPoint> > > >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<vector<edm4eic::TrackPoint> >*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEvectorlEedm4eiccLcLTrackPointgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<vector<edm4eic::TrackPoint> >*>(nullptr))->GetClass();
      vectorlEvectorlEedm4eiccLcLTrackPointgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEvectorlEedm4eiccLcLTrackPointgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEvectorlEedm4eiccLcLTrackPointgRsPgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<vector<edm4eic::TrackPoint> > : new vector<vector<edm4eic::TrackPoint> >;
   }
   static void *newArray_vectorlEvectorlEedm4eiccLcLTrackPointgRsPgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<vector<edm4eic::TrackPoint> >[nElements] : new vector<vector<edm4eic::TrackPoint> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEvectorlEedm4eiccLcLTrackPointgRsPgR(void *p) {
      delete (static_cast<vector<vector<edm4eic::TrackPoint> >*>(p));
   }
   static void deleteArray_vectorlEvectorlEedm4eiccLcLTrackPointgRsPgR(void *p) {
      delete [] (static_cast<vector<vector<edm4eic::TrackPoint> >*>(p));
   }
   static void destruct_vectorlEvectorlEedm4eiccLcLTrackPointgRsPgR(void *p) {
      typedef vector<vector<edm4eic::TrackPoint> > current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<vector<edm4eic::TrackPoint> >

namespace ROOT {
   static TClass *vectorlEedm4hepcLcLMCParticlegR_Dictionary();
   static void vectorlEedm4hepcLcLMCParticlegR_TClassManip(TClass*);
   static void *new_vectorlEedm4hepcLcLMCParticlegR(void *p = nullptr);
   static void *newArray_vectorlEedm4hepcLcLMCParticlegR(Long_t size, void *p);
   static void delete_vectorlEedm4hepcLcLMCParticlegR(void *p);
   static void deleteArray_vectorlEedm4hepcLcLMCParticlegR(void *p);
   static void destruct_vectorlEedm4hepcLcLMCParticlegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<edm4hep::MCParticle>*)
   {
      vector<edm4hep::MCParticle> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<edm4hep::MCParticle>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<edm4hep::MCParticle>", -2, "vector", 428,
                  typeid(vector<edm4hep::MCParticle>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEedm4hepcLcLMCParticlegR_Dictionary, isa_proxy, 0,
                  sizeof(vector<edm4hep::MCParticle>) );
      instance.SetNew(&new_vectorlEedm4hepcLcLMCParticlegR);
      instance.SetNewArray(&newArray_vectorlEedm4hepcLcLMCParticlegR);
      instance.SetDelete(&delete_vectorlEedm4hepcLcLMCParticlegR);
      instance.SetDeleteArray(&deleteArray_vectorlEedm4hepcLcLMCParticlegR);
      instance.SetDestructor(&destruct_vectorlEedm4hepcLcLMCParticlegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<edm4hep::MCParticle> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<edm4hep::MCParticle>","std::vector<edm4hep::MCParticle, std::allocator<edm4hep::MCParticle> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<edm4hep::MCParticle>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEedm4hepcLcLMCParticlegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<edm4hep::MCParticle>*>(nullptr))->GetClass();
      vectorlEedm4hepcLcLMCParticlegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEedm4hepcLcLMCParticlegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEedm4hepcLcLMCParticlegR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<edm4hep::MCParticle> : new vector<edm4hep::MCParticle>;
   }
   static void *newArray_vectorlEedm4hepcLcLMCParticlegR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<edm4hep::MCParticle>[nElements] : new vector<edm4hep::MCParticle>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEedm4hepcLcLMCParticlegR(void *p) {
      delete (static_cast<vector<edm4hep::MCParticle>*>(p));
   }
   static void deleteArray_vectorlEedm4hepcLcLMCParticlegR(void *p) {
      delete [] (static_cast<vector<edm4hep::MCParticle>*>(p));
   }
   static void destruct_vectorlEedm4hepcLcLMCParticlegR(void *p) {
      typedef vector<edm4hep::MCParticle> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<edm4hep::MCParticle>

namespace ROOT {
   static TClass *vectorlEedm4eiccLcLTrackPointgR_Dictionary();
   static void vectorlEedm4eiccLcLTrackPointgR_TClassManip(TClass*);
   static void *new_vectorlEedm4eiccLcLTrackPointgR(void *p = nullptr);
   static void *newArray_vectorlEedm4eiccLcLTrackPointgR(Long_t size, void *p);
   static void delete_vectorlEedm4eiccLcLTrackPointgR(void *p);
   static void deleteArray_vectorlEedm4eiccLcLTrackPointgR(void *p);
   static void destruct_vectorlEedm4eiccLcLTrackPointgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<edm4eic::TrackPoint>*)
   {
      vector<edm4eic::TrackPoint> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<edm4eic::TrackPoint>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<edm4eic::TrackPoint>", -2, "vector", 428,
                  typeid(vector<edm4eic::TrackPoint>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEedm4eiccLcLTrackPointgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<edm4eic::TrackPoint>) );
      instance.SetNew(&new_vectorlEedm4eiccLcLTrackPointgR);
      instance.SetNewArray(&newArray_vectorlEedm4eiccLcLTrackPointgR);
      instance.SetDelete(&delete_vectorlEedm4eiccLcLTrackPointgR);
      instance.SetDeleteArray(&deleteArray_vectorlEedm4eiccLcLTrackPointgR);
      instance.SetDestructor(&destruct_vectorlEedm4eiccLcLTrackPointgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<edm4eic::TrackPoint> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<edm4eic::TrackPoint>","std::vector<edm4eic::TrackPoint, std::allocator<edm4eic::TrackPoint> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<edm4eic::TrackPoint>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEedm4eiccLcLTrackPointgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<edm4eic::TrackPoint>*>(nullptr))->GetClass();
      vectorlEedm4eiccLcLTrackPointgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEedm4eiccLcLTrackPointgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEedm4eiccLcLTrackPointgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<edm4eic::TrackPoint> : new vector<edm4eic::TrackPoint>;
   }
   static void *newArray_vectorlEedm4eiccLcLTrackPointgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<edm4eic::TrackPoint>[nElements] : new vector<edm4eic::TrackPoint>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEedm4eiccLcLTrackPointgR(void *p) {
      delete (static_cast<vector<edm4eic::TrackPoint>*>(p));
   }
   static void deleteArray_vectorlEedm4eiccLcLTrackPointgR(void *p) {
      delete [] (static_cast<vector<edm4eic::TrackPoint>*>(p));
   }
   static void destruct_vectorlEedm4eiccLcLTrackPointgR(void *p) {
      typedef vector<edm4eic::TrackPoint> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<edm4eic::TrackPoint>

namespace ROOT {
   static TClass *vectorlEedm4eiccLcLTrackgR_Dictionary();
   static void vectorlEedm4eiccLcLTrackgR_TClassManip(TClass*);
   static void *new_vectorlEedm4eiccLcLTrackgR(void *p = nullptr);
   static void *newArray_vectorlEedm4eiccLcLTrackgR(Long_t size, void *p);
   static void delete_vectorlEedm4eiccLcLTrackgR(void *p);
   static void deleteArray_vectorlEedm4eiccLcLTrackgR(void *p);
   static void destruct_vectorlEedm4eiccLcLTrackgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<edm4eic::Track>*)
   {
      vector<edm4eic::Track> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<edm4eic::Track>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<edm4eic::Track>", -2, "vector", 428,
                  typeid(vector<edm4eic::Track>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEedm4eiccLcLTrackgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<edm4eic::Track>) );
      instance.SetNew(&new_vectorlEedm4eiccLcLTrackgR);
      instance.SetNewArray(&newArray_vectorlEedm4eiccLcLTrackgR);
      instance.SetDelete(&delete_vectorlEedm4eiccLcLTrackgR);
      instance.SetDeleteArray(&deleteArray_vectorlEedm4eiccLcLTrackgR);
      instance.SetDestructor(&destruct_vectorlEedm4eiccLcLTrackgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<edm4eic::Track> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<edm4eic::Track>","std::vector<edm4eic::Track, std::allocator<edm4eic::Track> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<edm4eic::Track>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEedm4eiccLcLTrackgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<edm4eic::Track>*>(nullptr))->GetClass();
      vectorlEedm4eiccLcLTrackgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEedm4eiccLcLTrackgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEedm4eiccLcLTrackgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<edm4eic::Track> : new vector<edm4eic::Track>;
   }
   static void *newArray_vectorlEedm4eiccLcLTrackgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<edm4eic::Track>[nElements] : new vector<edm4eic::Track>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEedm4eiccLcLTrackgR(void *p) {
      delete (static_cast<vector<edm4eic::Track>*>(p));
   }
   static void deleteArray_vectorlEedm4eiccLcLTrackgR(void *p) {
      delete [] (static_cast<vector<edm4eic::Track>*>(p));
   }
   static void destruct_vectorlEedm4eiccLcLTrackgR(void *p) {
      typedef vector<edm4eic::Track> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<edm4eic::Track>

namespace ROOT {
   static TClass *vectorlEedm4eiccLcLReconstructedParticlegR_Dictionary();
   static void vectorlEedm4eiccLcLReconstructedParticlegR_TClassManip(TClass*);
   static void *new_vectorlEedm4eiccLcLReconstructedParticlegR(void *p = nullptr);
   static void *newArray_vectorlEedm4eiccLcLReconstructedParticlegR(Long_t size, void *p);
   static void delete_vectorlEedm4eiccLcLReconstructedParticlegR(void *p);
   static void deleteArray_vectorlEedm4eiccLcLReconstructedParticlegR(void *p);
   static void destruct_vectorlEedm4eiccLcLReconstructedParticlegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<edm4eic::ReconstructedParticle>*)
   {
      vector<edm4eic::ReconstructedParticle> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<edm4eic::ReconstructedParticle>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<edm4eic::ReconstructedParticle>", -2, "vector", 428,
                  typeid(vector<edm4eic::ReconstructedParticle>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEedm4eiccLcLReconstructedParticlegR_Dictionary, isa_proxy, 0,
                  sizeof(vector<edm4eic::ReconstructedParticle>) );
      instance.SetNew(&new_vectorlEedm4eiccLcLReconstructedParticlegR);
      instance.SetNewArray(&newArray_vectorlEedm4eiccLcLReconstructedParticlegR);
      instance.SetDelete(&delete_vectorlEedm4eiccLcLReconstructedParticlegR);
      instance.SetDeleteArray(&deleteArray_vectorlEedm4eiccLcLReconstructedParticlegR);
      instance.SetDestructor(&destruct_vectorlEedm4eiccLcLReconstructedParticlegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<edm4eic::ReconstructedParticle> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<edm4eic::ReconstructedParticle>","std::vector<edm4eic::ReconstructedParticle, std::allocator<edm4eic::ReconstructedParticle> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<edm4eic::ReconstructedParticle>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEedm4eiccLcLReconstructedParticlegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<edm4eic::ReconstructedParticle>*>(nullptr))->GetClass();
      vectorlEedm4eiccLcLReconstructedParticlegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEedm4eiccLcLReconstructedParticlegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEedm4eiccLcLReconstructedParticlegR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<edm4eic::ReconstructedParticle> : new vector<edm4eic::ReconstructedParticle>;
   }
   static void *newArray_vectorlEedm4eiccLcLReconstructedParticlegR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<edm4eic::ReconstructedParticle>[nElements] : new vector<edm4eic::ReconstructedParticle>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEedm4eiccLcLReconstructedParticlegR(void *p) {
      delete (static_cast<vector<edm4eic::ReconstructedParticle>*>(p));
   }
   static void deleteArray_vectorlEedm4eiccLcLReconstructedParticlegR(void *p) {
      delete [] (static_cast<vector<edm4eic::ReconstructedParticle>*>(p));
   }
   static void destruct_vectorlEedm4eiccLcLReconstructedParticlegR(void *p) {
      typedef vector<edm4eic::ReconstructedParticle> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<edm4eic::ReconstructedParticle>

namespace ROOT {
   static TClass *vectorlEedm4eiccLcLClustergR_Dictionary();
   static void vectorlEedm4eiccLcLClustergR_TClassManip(TClass*);
   static void *new_vectorlEedm4eiccLcLClustergR(void *p = nullptr);
   static void *newArray_vectorlEedm4eiccLcLClustergR(Long_t size, void *p);
   static void delete_vectorlEedm4eiccLcLClustergR(void *p);
   static void deleteArray_vectorlEedm4eiccLcLClustergR(void *p);
   static void destruct_vectorlEedm4eiccLcLClustergR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<edm4eic::Cluster>*)
   {
      vector<edm4eic::Cluster> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<edm4eic::Cluster>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<edm4eic::Cluster>", -2, "vector", 428,
                  typeid(vector<edm4eic::Cluster>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEedm4eiccLcLClustergR_Dictionary, isa_proxy, 0,
                  sizeof(vector<edm4eic::Cluster>) );
      instance.SetNew(&new_vectorlEedm4eiccLcLClustergR);
      instance.SetNewArray(&newArray_vectorlEedm4eiccLcLClustergR);
      instance.SetDelete(&delete_vectorlEedm4eiccLcLClustergR);
      instance.SetDeleteArray(&deleteArray_vectorlEedm4eiccLcLClustergR);
      instance.SetDestructor(&destruct_vectorlEedm4eiccLcLClustergR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<edm4eic::Cluster> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<edm4eic::Cluster>","std::vector<edm4eic::Cluster, std::allocator<edm4eic::Cluster> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<edm4eic::Cluster>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEedm4eiccLcLClustergR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<edm4eic::Cluster>*>(nullptr))->GetClass();
      vectorlEedm4eiccLcLClustergR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEedm4eiccLcLClustergR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEedm4eiccLcLClustergR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<edm4eic::Cluster> : new vector<edm4eic::Cluster>;
   }
   static void *newArray_vectorlEedm4eiccLcLClustergR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<edm4eic::Cluster>[nElements] : new vector<edm4eic::Cluster>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEedm4eiccLcLClustergR(void *p) {
      delete (static_cast<vector<edm4eic::Cluster>*>(p));
   }
   static void deleteArray_vectorlEedm4eiccLcLClustergR(void *p) {
      delete [] (static_cast<vector<edm4eic::Cluster>*>(p));
   }
   static void destruct_vectorlEedm4eiccLcLClustergR(void *p) {
      typedef vector<edm4eic::Cluster> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<edm4eic::Cluster>

namespace ROOT {
   static TClass *vectorlEMyParticlegR_Dictionary();
   static void vectorlEMyParticlegR_TClassManip(TClass*);
   static void *new_vectorlEMyParticlegR(void *p = nullptr);
   static void *newArray_vectorlEMyParticlegR(Long_t size, void *p);
   static void delete_vectorlEMyParticlegR(void *p);
   static void deleteArray_vectorlEMyParticlegR(void *p);
   static void destruct_vectorlEMyParticlegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<MyParticle>*)
   {
      vector<MyParticle> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<MyParticle>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<MyParticle>", -2, "vector", 428,
                  typeid(vector<MyParticle>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEMyParticlegR_Dictionary, isa_proxy, 4,
                  sizeof(vector<MyParticle>) );
      instance.SetNew(&new_vectorlEMyParticlegR);
      instance.SetNewArray(&newArray_vectorlEMyParticlegR);
      instance.SetDelete(&delete_vectorlEMyParticlegR);
      instance.SetDeleteArray(&deleteArray_vectorlEMyParticlegR);
      instance.SetDestructor(&destruct_vectorlEMyParticlegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<MyParticle> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<MyParticle>","std::vector<MyParticle, std::allocator<MyParticle> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<MyParticle>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEMyParticlegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<MyParticle>*>(nullptr))->GetClass();
      vectorlEMyParticlegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEMyParticlegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEMyParticlegR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<MyParticle> : new vector<MyParticle>;
   }
   static void *newArray_vectorlEMyParticlegR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<MyParticle>[nElements] : new vector<MyParticle>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEMyParticlegR(void *p) {
      delete (static_cast<vector<MyParticle>*>(p));
   }
   static void deleteArray_vectorlEMyParticlegR(void *p) {
      delete [] (static_cast<vector<MyParticle>*>(p));
   }
   static void destruct_vectorlEMyParticlegR(void *p) {
      typedef vector<MyParticle> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<MyParticle>

namespace ROOT {
   static TClass *vectorlEMyEventgR_Dictionary();
   static void vectorlEMyEventgR_TClassManip(TClass*);
   static void *new_vectorlEMyEventgR(void *p = nullptr);
   static void *newArray_vectorlEMyEventgR(Long_t size, void *p);
   static void delete_vectorlEMyEventgR(void *p);
   static void deleteArray_vectorlEMyEventgR(void *p);
   static void destruct_vectorlEMyEventgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<MyEvent>*)
   {
      vector<MyEvent> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<MyEvent>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<MyEvent>", -2, "vector", 428,
                  typeid(vector<MyEvent>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEMyEventgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<MyEvent>) );
      instance.SetNew(&new_vectorlEMyEventgR);
      instance.SetNewArray(&newArray_vectorlEMyEventgR);
      instance.SetDelete(&delete_vectorlEMyEventgR);
      instance.SetDeleteArray(&deleteArray_vectorlEMyEventgR);
      instance.SetDestructor(&destruct_vectorlEMyEventgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<MyEvent> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<MyEvent>","std::vector<MyEvent, std::allocator<MyEvent> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<MyEvent>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEMyEventgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<MyEvent>*>(nullptr))->GetClass();
      vectorlEMyEventgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEMyEventgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEMyEventgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<MyEvent> : new vector<MyEvent>;
   }
   static void *newArray_vectorlEMyEventgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<MyEvent>[nElements] : new vector<MyEvent>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEMyEventgR(void *p) {
      delete (static_cast<vector<MyEvent>*>(p));
   }
   static void deleteArray_vectorlEMyEventgR(void *p) {
      delete [] (static_cast<vector<MyEvent>*>(p));
   }
   static void destruct_vectorlEMyEventgR(void *p) {
      typedef vector<MyEvent> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<MyEvent>

namespace ROOT {
   static TClass *maplEstringcOTH3mUgR_Dictionary();
   static void maplEstringcOTH3mUgR_TClassManip(TClass*);
   static void *new_maplEstringcOTH3mUgR(void *p = nullptr);
   static void *newArray_maplEstringcOTH3mUgR(Long_t size, void *p);
   static void delete_maplEstringcOTH3mUgR(void *p);
   static void deleteArray_maplEstringcOTH3mUgR(void *p);
   static void destruct_maplEstringcOTH3mUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,TH3*>*)
   {
      map<string,TH3*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,TH3*>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,TH3*>", -2, "map", 102,
                  typeid(map<string,TH3*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOTH3mUgR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,TH3*>) );
      instance.SetNew(&new_maplEstringcOTH3mUgR);
      instance.SetNewArray(&newArray_maplEstringcOTH3mUgR);
      instance.SetDelete(&delete_maplEstringcOTH3mUgR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOTH3mUgR);
      instance.SetDestructor(&destruct_maplEstringcOTH3mUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,TH3*> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("map<string,TH3*>","std::map<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, TH3*, std::less<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::pair<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const, TH3*> > >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const map<string,TH3*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOTH3mUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const map<string,TH3*>*>(nullptr))->GetClass();
      maplEstringcOTH3mUgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOTH3mUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOTH3mUgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) map<string,TH3*> : new map<string,TH3*>;
   }
   static void *newArray_maplEstringcOTH3mUgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) map<string,TH3*>[nElements] : new map<string,TH3*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOTH3mUgR(void *p) {
      delete (static_cast<map<string,TH3*>*>(p));
   }
   static void deleteArray_maplEstringcOTH3mUgR(void *p) {
      delete [] (static_cast<map<string,TH3*>*>(p));
   }
   static void destruct_maplEstringcOTH3mUgR(void *p) {
      typedef map<string,TH3*> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class map<string,TH3*>

namespace ROOT {
   static TClass *maplEstringcOTH2mUgR_Dictionary();
   static void maplEstringcOTH2mUgR_TClassManip(TClass*);
   static void *new_maplEstringcOTH2mUgR(void *p = nullptr);
   static void *newArray_maplEstringcOTH2mUgR(Long_t size, void *p);
   static void delete_maplEstringcOTH2mUgR(void *p);
   static void deleteArray_maplEstringcOTH2mUgR(void *p);
   static void destruct_maplEstringcOTH2mUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,TH2*>*)
   {
      map<string,TH2*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,TH2*>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,TH2*>", -2, "map", 102,
                  typeid(map<string,TH2*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOTH2mUgR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,TH2*>) );
      instance.SetNew(&new_maplEstringcOTH2mUgR);
      instance.SetNewArray(&newArray_maplEstringcOTH2mUgR);
      instance.SetDelete(&delete_maplEstringcOTH2mUgR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOTH2mUgR);
      instance.SetDestructor(&destruct_maplEstringcOTH2mUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,TH2*> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("map<string,TH2*>","std::map<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, TH2*, std::less<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::pair<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const, TH2*> > >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const map<string,TH2*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOTH2mUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const map<string,TH2*>*>(nullptr))->GetClass();
      maplEstringcOTH2mUgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOTH2mUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOTH2mUgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) map<string,TH2*> : new map<string,TH2*>;
   }
   static void *newArray_maplEstringcOTH2mUgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) map<string,TH2*>[nElements] : new map<string,TH2*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOTH2mUgR(void *p) {
      delete (static_cast<map<string,TH2*>*>(p));
   }
   static void deleteArray_maplEstringcOTH2mUgR(void *p) {
      delete [] (static_cast<map<string,TH2*>*>(p));
   }
   static void destruct_maplEstringcOTH2mUgR(void *p) {
      typedef map<string,TH2*> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class map<string,TH2*>

namespace ROOT {
   static TClass *maplEstringcOTH1mUgR_Dictionary();
   static void maplEstringcOTH1mUgR_TClassManip(TClass*);
   static void *new_maplEstringcOTH1mUgR(void *p = nullptr);
   static void *newArray_maplEstringcOTH1mUgR(Long_t size, void *p);
   static void delete_maplEstringcOTH1mUgR(void *p);
   static void deleteArray_maplEstringcOTH1mUgR(void *p);
   static void destruct_maplEstringcOTH1mUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,TH1*>*)
   {
      map<string,TH1*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,TH1*>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,TH1*>", -2, "map", 102,
                  typeid(map<string,TH1*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOTH1mUgR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,TH1*>) );
      instance.SetNew(&new_maplEstringcOTH1mUgR);
      instance.SetNewArray(&newArray_maplEstringcOTH1mUgR);
      instance.SetDelete(&delete_maplEstringcOTH1mUgR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOTH1mUgR);
      instance.SetDestructor(&destruct_maplEstringcOTH1mUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,TH1*> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("map<string,TH1*>","std::map<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, TH1*, std::less<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::pair<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const, TH1*> > >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const map<string,TH1*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOTH1mUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const map<string,TH1*>*>(nullptr))->GetClass();
      maplEstringcOTH1mUgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOTH1mUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOTH1mUgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) map<string,TH1*> : new map<string,TH1*>;
   }
   static void *newArray_maplEstringcOTH1mUgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) map<string,TH1*>[nElements] : new map<string,TH1*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOTH1mUgR(void *p) {
      delete (static_cast<map<string,TH1*>*>(p));
   }
   static void deleteArray_maplEstringcOTH1mUgR(void *p) {
      delete [] (static_cast<map<string,TH1*>*>(p));
   }
   static void destruct_maplEstringcOTH1mUgR(void *p) {
      typedef map<string,TH1*> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class map<string,TH1*>

namespace ROOT {
   // Registration Schema evolution read functions
   int RecordReadRules_MyDict() {
      return 0;
   }
   static int _R__UNIQUE_DICT_(ReadRules_MyDict) = RecordReadRules_MyDict();R__UseDummy(_R__UNIQUE_DICT_(ReadRules_MyDict));
} // namespace ROOT
namespace {
  void TriggerDictionaryInitialization_MyDict_Impl() {
    static const char* headers[] = {
"MyAnalysis.h",
"MyEvent.h",
nullptr
    };
    static const char* includePaths[] = {
"/opt/software/linux-x86_64_v2/root-6.38.00-wjrpkij5hcgrmlb522gzpp7irmsvhcig/include/root",
"/opt/local/include",
"MyAnalysis",
"/opt/software/linux-x86_64_v2/root-6.38.00-wjrpkij5hcgrmlb522gzpp7irmsvhcig/include/root",
"/gpfs/mnt/gpfs02/eic/namjae/madgraph/analysis/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "MyDict dictionary forward declarations' payload"

#pragma diagnostic push
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class  __attribute__((annotate("$clingAutoload$MyEvent.h")))  __attribute__((annotate("$clingAutoload$MyAnalysis.h")))  MyParticle;
namespace std{template <typename _Tp> class  __attribute__((annotate("$clingAutoload$bits/allocator.h")))  __attribute__((annotate("$clingAutoload$string")))  allocator;
}
class  __attribute__((annotate("$clingAutoload$MyEvent.h")))  __attribute__((annotate("$clingAutoload$MyAnalysis.h")))  MyEvent;
class  __attribute__((annotate("$clingAutoload$MyAnalysis.h")))  MyAnalysis;
#pragma diagnostic pop
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "MyDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "MyAnalysis.h"
#include "MyEvent.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"MyAnalysis", payloadCode, "@",
"MyEvent", payloadCode, "@",
"MyParticle", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("MyDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_MyDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_MyDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_MyDict() {
  TriggerDictionaryInitialization_MyDict_Impl();
}
