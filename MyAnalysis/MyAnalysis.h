// *****************************************************************************
// MyAnalysis.h
// Jae Nam, jnam@bnl.gov
// Analysis framework for ALP@ePIC studies.
// Expects a PODIO file from EICRecon with ePIC geometry as input.
// It returns (currently) root file containing analysis histograms,
// and (eventually) root tree file with ALP events.
// v0.20260331
// Right now this analysis (efficiency, resolution/smearing, cluster matching) rely on truth-matching of the scatter lepton.
// This needs to be updated once a robust lepton identification strategy is developed.
// *****************************************************************************

#ifndef MYANALYSIS
#define MYANALYSIS

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"

#include <podio/Frame.h>
#include <podio/ROOTReader.h>
#include <edm4eic/MCRecoClusterParticleAssociationCollection.h>
#include <edm4eic/TrackSegmentCollection.h>

#include "MyEvent.h"
#include "MySelectionCriteria.h"

using namespace std;

class MyAnalysis
{
private:
    // IO
    string mInFileName;
    string mOutFileName;
    string bdtFileName; //AW 20260604
    //string signal_type;
    podio::ROOTReader* mReader;
    TFile* mOutFile;
    TFile* bdtFile; //AW 20260604

public:
    // Event Instances
    podio::Frame frame;
    MyEvent* ev;
    unsigned int nev;

    int file_type; //this stores whether or not it's a signal file, DIS bkground file, or qed compton file
    /*
    file_type = 0; -> inclusive signal
    file_type = 1; -> decay signal
    file_type = 2; -> dis bkgd
    file_type = 3; -> qed compton bkgd 
    */

    // Tracker ID
    uint32_t collectionID_CKF;
    //uint32_t collectionID_TaggerM1;
    //uint32_t collectionID_TaggerM2;

    // Calorimeter ID
    uint32_t collectionID_BEMC;
    uint32_t collectionID_NEMC;
    uint32_t collectionID_PEMC;
    uint32_t collectionID_BHCal;
    uint32_t collectionID_NHCal;
    uint32_t collectionID_PHCal;


    // Selection Cuts
    // MySelectionCriteria.h
    MySelectionCriteria cuts;

    // Histograms
    map<string,TH1*> h1;
    map<string,TH2*> h2;
    map<string,TH3*> h3;


    //AW 20260604
    //I may have to include the Trees here!!!
    TTree* bdtTree; // AW 20260604 //Or should it be a private variable?
    //Event* bdt_ev; //I don't think I need this!

    //AW 20260604 Creating Branch Addresses for the TTree??? MOVED TO MyEvent.h!!!
    //int bdt_nev; //these might be wrong, these might need to be event variables????
    //float bdt_elec_e, bdt_pt, bdt_eta, bdt_elec_beam_rat, bdt_pt_miss, bdt_p, bdt_phi, bdt_q2, bdt_angle;


public:
    MyAnalysis();
    //MyAnalysis(string ifname, string ofname, string treename, string signal_type);
    
    MyAnalysis(string ifname, string ofname, string treename); 
    ~MyAnalysis();

    bool Run();
private:
    bool Init();
    bool Next();
    bool End();

    void TestingSpace();

    // MyAnalysisHistogram.cxx
    void ReserveHistograms(); //should I write the branches in another function 

    // MyAnalysisReadPODIO.cxx
    bool ReadPODIO();

    // MyAnalysisReconstruction.cxx
    bool TrackClusterMatching(); // EMC
    bool TrackHCalClusterMatching(); // HCAL
    bool CategorizeEvent(); // Truth-matched calculation
    bool WriteToBdtTree();//AW 20260605 find event-level information, save it to a flat tree!!
    bool FindEventQuantities(); //Truth-matched calculation

    // MyAnalysisCollection.cxx
    void AnalyzeQA();
    void AnalyzeEfficiency();
    void AnalyzeResolution();
    void AnalyzeMatching();
    void AnalyzeDecayVertex();

    void AnalyzeElectronIdentification();

};

#endif
