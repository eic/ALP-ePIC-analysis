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
    string mInFileName;
    string mOutFileName;
    podio::ROOTReader* mReader;
    podio::Frame mFrame;
    TFile* mOutFile;

public:
    unsigned int nev;
    MyEvent* ev;
    map<string,TH1*> h1;
    map<string,TH2*> h2;
    map<string,TH3*> h3;

    // MySelectionCriteria.cxx (WIP)
    MySelectionCriteria cuts;
    

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
    map<unsigned int, vector<edm4eic::TrackPoint>> TrackPointMap(const edm4eic::TrackSegmentCollection& projections);
    map<unsigned int, vector<edm4eic::Cluster>> ClusterMap(const edm4eic::MCRecoClusterParticleAssociationCollection& associations);

};

#endif
