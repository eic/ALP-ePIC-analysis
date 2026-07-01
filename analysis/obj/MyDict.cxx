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
#include "MySelectionCriteria.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_MyCluster(void *p = nullptr);
   static void *newArray_MyCluster(Long_t size, void *p);
   static void delete_MyCluster(void *p);
   static void deleteArray_MyCluster(void *p);
   static void destruct_MyCluster(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MyCluster*)
   {
      ::MyCluster *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::MyCluster >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("MyCluster", ::MyCluster::Class_Version(), "MyEvent.h", 30,
                  typeid(::MyCluster), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::MyCluster::Dictionary, isa_proxy, 4,
                  sizeof(::MyCluster) );
      instance.SetNew(&new_MyCluster);
      instance.SetNewArray(&newArray_MyCluster);
      instance.SetDelete(&delete_MyCluster);
      instance.SetDeleteArray(&deleteArray_MyCluster);
      instance.SetDestructor(&destruct_MyCluster);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MyCluster*)
   {
      return GenerateInitInstanceLocal(static_cast<::MyCluster*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::MyCluster*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_MyGeneratedParticle(void *p = nullptr);
   static void *newArray_MyGeneratedParticle(Long_t size, void *p);
   static void delete_MyGeneratedParticle(void *p);
   static void deleteArray_MyGeneratedParticle(void *p);
   static void destruct_MyGeneratedParticle(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MyGeneratedParticle*)
   {
      ::MyGeneratedParticle *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::MyGeneratedParticle >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("MyGeneratedParticle", ::MyGeneratedParticle::Class_Version(), "MyEvent.h", 83,
                  typeid(::MyGeneratedParticle), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::MyGeneratedParticle::Dictionary, isa_proxy, 4,
                  sizeof(::MyGeneratedParticle) );
      instance.SetNew(&new_MyGeneratedParticle);
      instance.SetNewArray(&newArray_MyGeneratedParticle);
      instance.SetDelete(&delete_MyGeneratedParticle);
      instance.SetDeleteArray(&deleteArray_MyGeneratedParticle);
      instance.SetDestructor(&destruct_MyGeneratedParticle);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MyGeneratedParticle*)
   {
      return GenerateInitInstanceLocal(static_cast<::MyGeneratedParticle*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::MyGeneratedParticle*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_MyReconstructedParticle(void *p = nullptr);
   static void *newArray_MyReconstructedParticle(Long_t size, void *p);
   static void delete_MyReconstructedParticle(void *p);
   static void deleteArray_MyReconstructedParticle(void *p);
   static void destruct_MyReconstructedParticle(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MyReconstructedParticle*)
   {
      ::MyReconstructedParticle *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::MyReconstructedParticle >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("MyReconstructedParticle", ::MyReconstructedParticle::Class_Version(), "MyEvent.h", 132,
                  typeid(::MyReconstructedParticle), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::MyReconstructedParticle::Dictionary, isa_proxy, 4,
                  sizeof(::MyReconstructedParticle) );
      instance.SetNew(&new_MyReconstructedParticle);
      instance.SetNewArray(&newArray_MyReconstructedParticle);
      instance.SetDelete(&delete_MyReconstructedParticle);
      instance.SetDeleteArray(&deleteArray_MyReconstructedParticle);
      instance.SetDestructor(&destruct_MyReconstructedParticle);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MyReconstructedParticle*)
   {
      return GenerateInitInstanceLocal(static_cast<::MyReconstructedParticle*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::MyReconstructedParticle*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_MyEvent(void *p = nullptr);
   static void *newArray_MyEvent(Long_t size, void *p);
   static void delete_MyEvent(void *p);
   static void deleteArray_MyEvent(void *p);
   static void destruct_MyEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MyEvent*)
   {
      ::MyEvent *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::MyEvent >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("MyEvent", ::MyEvent::Class_Version(), "MyEvent.h", 258,
                  typeid(::MyEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::MyEvent::Dictionary, isa_proxy, 4,
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
} // end of namespace ROOT

namespace ROOT {
   static TClass *MySelectionCriteria_Dictionary();
   static void MySelectionCriteria_TClassManip(TClass*);
   static void *new_MySelectionCriteria(void *p = nullptr);
   static void *newArray_MySelectionCriteria(Long_t size, void *p);
   static void delete_MySelectionCriteria(void *p);
   static void deleteArray_MySelectionCriteria(void *p);
   static void destruct_MySelectionCriteria(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MySelectionCriteria*)
   {
      ::MySelectionCriteria *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::MySelectionCriteria));
      static ::ROOT::TGenericClassInfo 
         instance("MySelectionCriteria", "MySelectionCriteria.h", 7,
                  typeid(::MySelectionCriteria), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &MySelectionCriteria_Dictionary, isa_proxy, 4,
                  sizeof(::MySelectionCriteria) );
      instance.SetNew(&new_MySelectionCriteria);
      instance.SetNewArray(&newArray_MySelectionCriteria);
      instance.SetDelete(&delete_MySelectionCriteria);
      instance.SetDeleteArray(&deleteArray_MySelectionCriteria);
      instance.SetDestructor(&destruct_MySelectionCriteria);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MySelectionCriteria*)
   {
      return GenerateInitInstanceLocal(static_cast<::MySelectionCriteria*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::MySelectionCriteria*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *MySelectionCriteria_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::MySelectionCriteria*>(nullptr))->GetClass();
      MySelectionCriteria_TClassManip(theClass);
   return theClass;
   }

   static void MySelectionCriteria_TClassManip(TClass* ){
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
         instance("MyAnalysis", "MyAnalysis.h", 51,
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

//______________________________________________________________________________
atomic_TClass_ptr MyCluster::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *MyCluster::Class_Name()
{
   return "MyCluster";
}

//______________________________________________________________________________
const char *MyCluster::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MyCluster*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int MyCluster::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MyCluster*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MyCluster::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MyCluster*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MyCluster::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MyCluster*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr MyGeneratedParticle::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *MyGeneratedParticle::Class_Name()
{
   return "MyGeneratedParticle";
}

//______________________________________________________________________________
const char *MyGeneratedParticle::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MyGeneratedParticle*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int MyGeneratedParticle::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MyGeneratedParticle*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MyGeneratedParticle::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MyGeneratedParticle*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MyGeneratedParticle::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MyGeneratedParticle*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr MyReconstructedParticle::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *MyReconstructedParticle::Class_Name()
{
   return "MyReconstructedParticle";
}

//______________________________________________________________________________
const char *MyReconstructedParticle::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MyReconstructedParticle*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int MyReconstructedParticle::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MyReconstructedParticle*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MyReconstructedParticle::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MyReconstructedParticle*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MyReconstructedParticle::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MyReconstructedParticle*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr MyEvent::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *MyEvent::Class_Name()
{
   return "MyEvent";
}

//______________________________________________________________________________
const char *MyEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MyEvent*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int MyEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MyEvent*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MyEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MyEvent*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MyEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MyEvent*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void MyCluster::Streamer(TBuffer &R__b)
{
   // Stream an object of class MyCluster.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(MyCluster::Class(),this);
   } else {
      R__b.WriteClassBuffer(MyCluster::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_MyCluster(void *p) {
      return  p ? new(p) ::MyCluster : new ::MyCluster;
   }
   static void *newArray_MyCluster(Long_t nElements, void *p) {
      return p ? new(p) ::MyCluster[nElements] : new ::MyCluster[nElements];
   }
   // Wrapper around operator delete
   static void delete_MyCluster(void *p) {
      delete (static_cast<::MyCluster*>(p));
   }
   static void deleteArray_MyCluster(void *p) {
      delete [] (static_cast<::MyCluster*>(p));
   }
   static void destruct_MyCluster(void *p) {
      typedef ::MyCluster current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::MyCluster

//______________________________________________________________________________
void MyGeneratedParticle::Streamer(TBuffer &R__b)
{
   // Stream an object of class MyGeneratedParticle.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(MyGeneratedParticle::Class(),this);
   } else {
      R__b.WriteClassBuffer(MyGeneratedParticle::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_MyGeneratedParticle(void *p) {
      return  p ? new(p) ::MyGeneratedParticle : new ::MyGeneratedParticle;
   }
   static void *newArray_MyGeneratedParticle(Long_t nElements, void *p) {
      return p ? new(p) ::MyGeneratedParticle[nElements] : new ::MyGeneratedParticle[nElements];
   }
   // Wrapper around operator delete
   static void delete_MyGeneratedParticle(void *p) {
      delete (static_cast<::MyGeneratedParticle*>(p));
   }
   static void deleteArray_MyGeneratedParticle(void *p) {
      delete [] (static_cast<::MyGeneratedParticle*>(p));
   }
   static void destruct_MyGeneratedParticle(void *p) {
      typedef ::MyGeneratedParticle current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::MyGeneratedParticle

//______________________________________________________________________________
void MyReconstructedParticle::Streamer(TBuffer &R__b)
{
   // Stream an object of class MyReconstructedParticle.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(MyReconstructedParticle::Class(),this);
   } else {
      R__b.WriteClassBuffer(MyReconstructedParticle::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_MyReconstructedParticle(void *p) {
      return  p ? new(p) ::MyReconstructedParticle : new ::MyReconstructedParticle;
   }
   static void *newArray_MyReconstructedParticle(Long_t nElements, void *p) {
      return p ? new(p) ::MyReconstructedParticle[nElements] : new ::MyReconstructedParticle[nElements];
   }
   // Wrapper around operator delete
   static void delete_MyReconstructedParticle(void *p) {
      delete (static_cast<::MyReconstructedParticle*>(p));
   }
   static void deleteArray_MyReconstructedParticle(void *p) {
      delete [] (static_cast<::MyReconstructedParticle*>(p));
   }
   static void destruct_MyReconstructedParticle(void *p) {
      typedef ::MyReconstructedParticle current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::MyReconstructedParticle

//______________________________________________________________________________
void MyEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class MyEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(MyEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(MyEvent::Class(),this);
   }
}

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
   static void *new_MySelectionCriteria(void *p) {
      return  p ? new(p) ::MySelectionCriteria : new ::MySelectionCriteria;
   }
   static void *newArray_MySelectionCriteria(Long_t nElements, void *p) {
      return p ? new(p) ::MySelectionCriteria[nElements] : new ::MySelectionCriteria[nElements];
   }
   // Wrapper around operator delete
   static void delete_MySelectionCriteria(void *p) {
      delete (static_cast<::MySelectionCriteria*>(p));
   }
   static void deleteArray_MySelectionCriteria(void *p) {
      delete [] (static_cast<::MySelectionCriteria*>(p));
   }
   static void destruct_MySelectionCriteria(void *p) {
      typedef ::MySelectionCriteria current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::MySelectionCriteria

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
   static TClass *vectorlEintgR_Dictionary();
   static void vectorlEintgR_TClassManip(TClass*);
   static void *new_vectorlEintgR(void *p = nullptr);
   static void *newArray_vectorlEintgR(Long_t size, void *p);
   static void delete_vectorlEintgR(void *p);
   static void deleteArray_vectorlEintgR(void *p);
   static void destruct_vectorlEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<int>*)
   {
      vector<int> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<int>", -2, "vector", 428,
                  typeid(vector<int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEintgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<int>) );
      instance.SetNew(&new_vectorlEintgR);
      instance.SetNewArray(&newArray_vectorlEintgR);
      instance.SetDelete(&delete_vectorlEintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEintgR);
      instance.SetDestructor(&destruct_vectorlEintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<int> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<int>","std::vector<int, std::allocator<int> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<int>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<int>*>(nullptr))->GetClass();
      vectorlEintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEintgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<int> : new vector<int>;
   }
   static void *newArray_vectorlEintgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<int>[nElements] : new vector<int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEintgR(void *p) {
      delete (static_cast<vector<int>*>(p));
   }
   static void deleteArray_vectorlEintgR(void *p) {
      delete [] (static_cast<vector<int>*>(p));
   }
   static void destruct_vectorlEintgR(void *p) {
      typedef vector<int> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<int>

namespace ROOT {
   static TClass *vectorlEMySelectionCriteriagR_Dictionary();
   static void vectorlEMySelectionCriteriagR_TClassManip(TClass*);
   static void *new_vectorlEMySelectionCriteriagR(void *p = nullptr);
   static void *newArray_vectorlEMySelectionCriteriagR(Long_t size, void *p);
   static void delete_vectorlEMySelectionCriteriagR(void *p);
   static void deleteArray_vectorlEMySelectionCriteriagR(void *p);
   static void destruct_vectorlEMySelectionCriteriagR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<MySelectionCriteria>*)
   {
      vector<MySelectionCriteria> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<MySelectionCriteria>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<MySelectionCriteria>", -2, "vector", 428,
                  typeid(vector<MySelectionCriteria>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEMySelectionCriteriagR_Dictionary, isa_proxy, 4,
                  sizeof(vector<MySelectionCriteria>) );
      instance.SetNew(&new_vectorlEMySelectionCriteriagR);
      instance.SetNewArray(&newArray_vectorlEMySelectionCriteriagR);
      instance.SetDelete(&delete_vectorlEMySelectionCriteriagR);
      instance.SetDeleteArray(&deleteArray_vectorlEMySelectionCriteriagR);
      instance.SetDestructor(&destruct_vectorlEMySelectionCriteriagR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<MySelectionCriteria> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<MySelectionCriteria>","std::vector<MySelectionCriteria, std::allocator<MySelectionCriteria> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<MySelectionCriteria>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEMySelectionCriteriagR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<MySelectionCriteria>*>(nullptr))->GetClass();
      vectorlEMySelectionCriteriagR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEMySelectionCriteriagR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEMySelectionCriteriagR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<MySelectionCriteria> : new vector<MySelectionCriteria>;
   }
   static void *newArray_vectorlEMySelectionCriteriagR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<MySelectionCriteria>[nElements] : new vector<MySelectionCriteria>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEMySelectionCriteriagR(void *p) {
      delete (static_cast<vector<MySelectionCriteria>*>(p));
   }
   static void deleteArray_vectorlEMySelectionCriteriagR(void *p) {
      delete [] (static_cast<vector<MySelectionCriteria>*>(p));
   }
   static void destruct_vectorlEMySelectionCriteriagR(void *p) {
      typedef vector<MySelectionCriteria> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<MySelectionCriteria>

namespace ROOT {
   static TClass *vectorlEMyReconstructedParticlegR_Dictionary();
   static void vectorlEMyReconstructedParticlegR_TClassManip(TClass*);
   static void *new_vectorlEMyReconstructedParticlegR(void *p = nullptr);
   static void *newArray_vectorlEMyReconstructedParticlegR(Long_t size, void *p);
   static void delete_vectorlEMyReconstructedParticlegR(void *p);
   static void deleteArray_vectorlEMyReconstructedParticlegR(void *p);
   static void destruct_vectorlEMyReconstructedParticlegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<MyReconstructedParticle>*)
   {
      vector<MyReconstructedParticle> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<MyReconstructedParticle>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<MyReconstructedParticle>", -2, "vector", 428,
                  typeid(vector<MyReconstructedParticle>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEMyReconstructedParticlegR_Dictionary, isa_proxy, 4,
                  sizeof(vector<MyReconstructedParticle>) );
      instance.SetNew(&new_vectorlEMyReconstructedParticlegR);
      instance.SetNewArray(&newArray_vectorlEMyReconstructedParticlegR);
      instance.SetDelete(&delete_vectorlEMyReconstructedParticlegR);
      instance.SetDeleteArray(&deleteArray_vectorlEMyReconstructedParticlegR);
      instance.SetDestructor(&destruct_vectorlEMyReconstructedParticlegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<MyReconstructedParticle> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<MyReconstructedParticle>","std::vector<MyReconstructedParticle, std::allocator<MyReconstructedParticle> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<MyReconstructedParticle>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEMyReconstructedParticlegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<MyReconstructedParticle>*>(nullptr))->GetClass();
      vectorlEMyReconstructedParticlegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEMyReconstructedParticlegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEMyReconstructedParticlegR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<MyReconstructedParticle> : new vector<MyReconstructedParticle>;
   }
   static void *newArray_vectorlEMyReconstructedParticlegR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<MyReconstructedParticle>[nElements] : new vector<MyReconstructedParticle>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEMyReconstructedParticlegR(void *p) {
      delete (static_cast<vector<MyReconstructedParticle>*>(p));
   }
   static void deleteArray_vectorlEMyReconstructedParticlegR(void *p) {
      delete [] (static_cast<vector<MyReconstructedParticle>*>(p));
   }
   static void destruct_vectorlEMyReconstructedParticlegR(void *p) {
      typedef vector<MyReconstructedParticle> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<MyReconstructedParticle>

namespace ROOT {
   static TClass *vectorlEMyGeneratedParticlegR_Dictionary();
   static void vectorlEMyGeneratedParticlegR_TClassManip(TClass*);
   static void *new_vectorlEMyGeneratedParticlegR(void *p = nullptr);
   static void *newArray_vectorlEMyGeneratedParticlegR(Long_t size, void *p);
   static void delete_vectorlEMyGeneratedParticlegR(void *p);
   static void deleteArray_vectorlEMyGeneratedParticlegR(void *p);
   static void destruct_vectorlEMyGeneratedParticlegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<MyGeneratedParticle>*)
   {
      vector<MyGeneratedParticle> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<MyGeneratedParticle>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<MyGeneratedParticle>", -2, "vector", 428,
                  typeid(vector<MyGeneratedParticle>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEMyGeneratedParticlegR_Dictionary, isa_proxy, 4,
                  sizeof(vector<MyGeneratedParticle>) );
      instance.SetNew(&new_vectorlEMyGeneratedParticlegR);
      instance.SetNewArray(&newArray_vectorlEMyGeneratedParticlegR);
      instance.SetDelete(&delete_vectorlEMyGeneratedParticlegR);
      instance.SetDeleteArray(&deleteArray_vectorlEMyGeneratedParticlegR);
      instance.SetDestructor(&destruct_vectorlEMyGeneratedParticlegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<MyGeneratedParticle> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<MyGeneratedParticle>","std::vector<MyGeneratedParticle, std::allocator<MyGeneratedParticle> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<MyGeneratedParticle>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEMyGeneratedParticlegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<MyGeneratedParticle>*>(nullptr))->GetClass();
      vectorlEMyGeneratedParticlegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEMyGeneratedParticlegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEMyGeneratedParticlegR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<MyGeneratedParticle> : new vector<MyGeneratedParticle>;
   }
   static void *newArray_vectorlEMyGeneratedParticlegR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<MyGeneratedParticle>[nElements] : new vector<MyGeneratedParticle>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEMyGeneratedParticlegR(void *p) {
      delete (static_cast<vector<MyGeneratedParticle>*>(p));
   }
   static void deleteArray_vectorlEMyGeneratedParticlegR(void *p) {
      delete [] (static_cast<vector<MyGeneratedParticle>*>(p));
   }
   static void destruct_vectorlEMyGeneratedParticlegR(void *p) {
      typedef vector<MyGeneratedParticle> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<MyGeneratedParticle>

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
   static TClass *vectorlEMyClustergR_Dictionary();
   static void vectorlEMyClustergR_TClassManip(TClass*);
   static void *new_vectorlEMyClustergR(void *p = nullptr);
   static void *newArray_vectorlEMyClustergR(Long_t size, void *p);
   static void delete_vectorlEMyClustergR(void *p);
   static void deleteArray_vectorlEMyClustergR(void *p);
   static void destruct_vectorlEMyClustergR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<MyCluster>*)
   {
      vector<MyCluster> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<MyCluster>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<MyCluster>", -2, "vector", 428,
                  typeid(vector<MyCluster>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEMyClustergR_Dictionary, isa_proxy, 4,
                  sizeof(vector<MyCluster>) );
      instance.SetNew(&new_vectorlEMyClustergR);
      instance.SetNewArray(&newArray_vectorlEMyClustergR);
      instance.SetDelete(&delete_vectorlEMyClustergR);
      instance.SetDeleteArray(&deleteArray_vectorlEMyClustergR);
      instance.SetDestructor(&destruct_vectorlEMyClustergR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<MyCluster> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<MyCluster>","std::vector<MyCluster, std::allocator<MyCluster> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<MyCluster>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEMyClustergR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<MyCluster>*>(nullptr))->GetClass();
      vectorlEMyClustergR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEMyClustergR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEMyClustergR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<MyCluster> : new vector<MyCluster>;
   }
   static void *newArray_vectorlEMyClustergR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<MyCluster>[nElements] : new vector<MyCluster>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEMyClustergR(void *p) {
      delete (static_cast<vector<MyCluster>*>(p));
   }
   static void deleteArray_vectorlEMyClustergR(void *p) {
      delete [] (static_cast<vector<MyCluster>*>(p));
   }
   static void destruct_vectorlEMyClustergR(void *p) {
      typedef vector<MyCluster> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<MyCluster>

namespace ROOT {
   static TClass *vectorlEMyClustermUgR_Dictionary();
   static void vectorlEMyClustermUgR_TClassManip(TClass*);
   static void *new_vectorlEMyClustermUgR(void *p = nullptr);
   static void *newArray_vectorlEMyClustermUgR(Long_t size, void *p);
   static void delete_vectorlEMyClustermUgR(void *p);
   static void deleteArray_vectorlEMyClustermUgR(void *p);
   static void destruct_vectorlEMyClustermUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<MyCluster*>*)
   {
      vector<MyCluster*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<MyCluster*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<MyCluster*>", -2, "vector", 428,
                  typeid(vector<MyCluster*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEMyClustermUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<MyCluster*>) );
      instance.SetNew(&new_vectorlEMyClustermUgR);
      instance.SetNewArray(&newArray_vectorlEMyClustermUgR);
      instance.SetDelete(&delete_vectorlEMyClustermUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEMyClustermUgR);
      instance.SetDestructor(&destruct_vectorlEMyClustermUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<MyCluster*> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<MyCluster*>","std::vector<MyCluster*, std::allocator<MyCluster*> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<MyCluster*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEMyClustermUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<MyCluster*>*>(nullptr))->GetClass();
      vectorlEMyClustermUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEMyClustermUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEMyClustermUgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<MyCluster*> : new vector<MyCluster*>;
   }
   static void *newArray_vectorlEMyClustermUgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<MyCluster*>[nElements] : new vector<MyCluster*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEMyClustermUgR(void *p) {
      delete (static_cast<vector<MyCluster*>*>(p));
   }
   static void deleteArray_vectorlEMyClustermUgR(void *p) {
      delete [] (static_cast<vector<MyCluster*>*>(p));
   }
   static void destruct_vectorlEMyClustermUgR(void *p) {
      typedef vector<MyCluster*> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<MyCluster*>

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
   static TClass *maplEintcOMyReconstructedParticlegR_Dictionary();
   static void maplEintcOMyReconstructedParticlegR_TClassManip(TClass*);
   static void *new_maplEintcOMyReconstructedParticlegR(void *p = nullptr);
   static void *newArray_maplEintcOMyReconstructedParticlegR(Long_t size, void *p);
   static void delete_maplEintcOMyReconstructedParticlegR(void *p);
   static void deleteArray_maplEintcOMyReconstructedParticlegR(void *p);
   static void destruct_maplEintcOMyReconstructedParticlegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<int,MyReconstructedParticle>*)
   {
      map<int,MyReconstructedParticle> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<int,MyReconstructedParticle>));
      static ::ROOT::TGenericClassInfo 
         instance("map<int,MyReconstructedParticle>", -2, "map", 102,
                  typeid(map<int,MyReconstructedParticle>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEintcOMyReconstructedParticlegR_Dictionary, isa_proxy, 0,
                  sizeof(map<int,MyReconstructedParticle>) );
      instance.SetNew(&new_maplEintcOMyReconstructedParticlegR);
      instance.SetNewArray(&newArray_maplEintcOMyReconstructedParticlegR);
      instance.SetDelete(&delete_maplEintcOMyReconstructedParticlegR);
      instance.SetDeleteArray(&deleteArray_maplEintcOMyReconstructedParticlegR);
      instance.SetDestructor(&destruct_maplEintcOMyReconstructedParticlegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<int,MyReconstructedParticle> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("map<int,MyReconstructedParticle>","std::map<int, MyReconstructedParticle, std::less<int>, std::allocator<std::pair<int const, MyReconstructedParticle> > >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const map<int,MyReconstructedParticle>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEintcOMyReconstructedParticlegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const map<int,MyReconstructedParticle>*>(nullptr))->GetClass();
      maplEintcOMyReconstructedParticlegR_TClassManip(theClass);
   return theClass;
   }

   static void maplEintcOMyReconstructedParticlegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEintcOMyReconstructedParticlegR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) map<int,MyReconstructedParticle> : new map<int,MyReconstructedParticle>;
   }
   static void *newArray_maplEintcOMyReconstructedParticlegR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) map<int,MyReconstructedParticle>[nElements] : new map<int,MyReconstructedParticle>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEintcOMyReconstructedParticlegR(void *p) {
      delete (static_cast<map<int,MyReconstructedParticle>*>(p));
   }
   static void deleteArray_maplEintcOMyReconstructedParticlegR(void *p) {
      delete [] (static_cast<map<int,MyReconstructedParticle>*>(p));
   }
   static void destruct_maplEintcOMyReconstructedParticlegR(void *p) {
      typedef map<int,MyReconstructedParticle> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class map<int,MyReconstructedParticle>

namespace ROOT {
   static TClass *maplEintcOMyGeneratedParticlegR_Dictionary();
   static void maplEintcOMyGeneratedParticlegR_TClassManip(TClass*);
   static void *new_maplEintcOMyGeneratedParticlegR(void *p = nullptr);
   static void *newArray_maplEintcOMyGeneratedParticlegR(Long_t size, void *p);
   static void delete_maplEintcOMyGeneratedParticlegR(void *p);
   static void deleteArray_maplEintcOMyGeneratedParticlegR(void *p);
   static void destruct_maplEintcOMyGeneratedParticlegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<int,MyGeneratedParticle>*)
   {
      map<int,MyGeneratedParticle> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<int,MyGeneratedParticle>));
      static ::ROOT::TGenericClassInfo 
         instance("map<int,MyGeneratedParticle>", -2, "map", 102,
                  typeid(map<int,MyGeneratedParticle>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEintcOMyGeneratedParticlegR_Dictionary, isa_proxy, 0,
                  sizeof(map<int,MyGeneratedParticle>) );
      instance.SetNew(&new_maplEintcOMyGeneratedParticlegR);
      instance.SetNewArray(&newArray_maplEintcOMyGeneratedParticlegR);
      instance.SetDelete(&delete_maplEintcOMyGeneratedParticlegR);
      instance.SetDeleteArray(&deleteArray_maplEintcOMyGeneratedParticlegR);
      instance.SetDestructor(&destruct_maplEintcOMyGeneratedParticlegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<int,MyGeneratedParticle> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("map<int,MyGeneratedParticle>","std::map<int, MyGeneratedParticle, std::less<int>, std::allocator<std::pair<int const, MyGeneratedParticle> > >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const map<int,MyGeneratedParticle>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEintcOMyGeneratedParticlegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const map<int,MyGeneratedParticle>*>(nullptr))->GetClass();
      maplEintcOMyGeneratedParticlegR_TClassManip(theClass);
   return theClass;
   }

   static void maplEintcOMyGeneratedParticlegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEintcOMyGeneratedParticlegR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) map<int,MyGeneratedParticle> : new map<int,MyGeneratedParticle>;
   }
   static void *newArray_maplEintcOMyGeneratedParticlegR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) map<int,MyGeneratedParticle>[nElements] : new map<int,MyGeneratedParticle>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEintcOMyGeneratedParticlegR(void *p) {
      delete (static_cast<map<int,MyGeneratedParticle>*>(p));
   }
   static void deleteArray_maplEintcOMyGeneratedParticlegR(void *p) {
      delete [] (static_cast<map<int,MyGeneratedParticle>*>(p));
   }
   static void destruct_maplEintcOMyGeneratedParticlegR(void *p) {
      typedef map<int,MyGeneratedParticle> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class map<int,MyGeneratedParticle>

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
"MySelectionCriteria.h",
nullptr
    };
    static const char* includePaths[] = {
"/opt/software/linux-x86_64_v2/root-6.38.00-fkwc2k4hr7237weejmvf3wustfw4ahjp/include/root",
"/opt/local/include",
"MyAnalysis",
"/opt/software/linux-x86_64_v2/root-6.38.00-fkwc2k4hr7237weejmvf3wustfw4ahjp/include/root",
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
class  __attribute__((annotate("$clingAutoload$MyEvent.h")))  __attribute__((annotate("$clingAutoload$MyAnalysis.h")))  MyCluster;
namespace std{template <typename _Tp> class  __attribute__((annotate("$clingAutoload$bits/allocator.h")))  __attribute__((annotate("$clingAutoload$string")))  allocator;
}
class  __attribute__((annotate("$clingAutoload$MySelectionCriteria.h")))  __attribute__((annotate("$clingAutoload$MyAnalysis.h")))  MySelectionCriteria;
class  __attribute__((annotate("$clingAutoload$MyEvent.h")))  __attribute__((annotate("$clingAutoload$MyAnalysis.h")))  MyReconstructedParticle;
class  __attribute__((annotate("$clingAutoload$MyEvent.h")))  __attribute__((annotate("$clingAutoload$MyAnalysis.h")))  MyGeneratedParticle;
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
#include "MySelectionCriteria.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"MyAnalysis", payloadCode, "@",
"MyCluster", payloadCode, "@",
"MyEvent", payloadCode, "@",
"MyGeneratedParticle", payloadCode, "@",
"MyReconstructedParticle", payloadCode, "@",
"MySelectionCriteria", payloadCode, "@",
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
