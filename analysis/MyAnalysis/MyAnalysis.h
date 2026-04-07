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
    podio::ROOTReader* mReader;
    TFile* mOutFile;

public:
    // Event Instances
    podio::Frame frame;
    MyEvent* ev;
    unsigned int nev;

    uint32_t collectionID_BEMC;
    uint32_t collectionID_NEMC;
    uint32_t collectionID_PEMC;


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

    // MyAnalysisHistogram.cxx
    void ReserveHistograms();

    // MyAnalysisReadPODIO.cxx
    bool ReadPODIO();

    // MyAnalysisReconstruction.cxx
    bool TrackClusterMatching();

    // MyAnalysisCollection.cxx
    void AnalyzeQA();
    void AnalyzeEfficiency();
    void AnalyzeResolution();
    void AnalyzeMatching();
    void AnalyzeDecayVertex();

};

#endif
