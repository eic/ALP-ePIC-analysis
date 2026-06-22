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


// Check definitions.xml and make sure these values are correct in 10 years
#define BEMC_SYSTEM_ID 101
#define NEMC_SYSTEM_ID 103
#define PEMC_SYSTEM_ID 102

#define BHCAL_SYSTEM_ID 111
#define NHCAL_SYSTEM_ID 113
#define PHCAL_SYSTEM_ID 116

const vector<int> TRACK_HIT_BARREL_DETECTOR_IDS = {59, 60, 61, 62, 63, 64, 65, 66, 67, 31, 32, 33, 90, 91, 92};
const vector<int> TRACK_HIT_NEGATIVE_DETECTOR_IDS = {68, 69, 70, 71, 72, 73, 74, 75, 76, 34, 35, 36, 131, 132};
const vector<int> TRACK_HIT_POSITIVE_DETECTOR_IDS = {77, 78, 79, 80, 81, 82, 83, 37, 38, 39, 120, 121, 122};
const vector<int> TRACK_HIT_TAGGER_DETECTOR_IDS = {198, 199};

using namespace std;

class MyAnalysis
{
private:
    // IO
    string mInFileName;
    string mOutFileName;
    podio::ROOTReader* mReader;
    TFile* mOutFile;

public:
    // Event Instances
    podio::Frame frame;
    MyEvent* ev;
    unsigned int nev;

    // Tracker ID
    uint32_t collectionID_CKF;
    uint32_t collectionID_TaggerM1;
    uint32_t collectionID_TaggerM2;

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

public:
    MyAnalysis();
    MyAnalysis(string ifname, string ofname);
    ~MyAnalysis();

    bool Run();
private:
    bool Init();
    bool Next();
    bool End();

    void TestingSpace();

    // MyAnalysisHistogram.cxx
    void ReserveHistograms();

    // MyAnalysisReadPODIO.cxx
    bool ReadPODIO();

    // MyAnalysisReconstruction.cxx
    bool TrackClusterMatching(); // EMC
    bool TrackHCalClusterMatching(); // HCAL
    bool CategorizeEvent(); // Truth-matched calculation
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
