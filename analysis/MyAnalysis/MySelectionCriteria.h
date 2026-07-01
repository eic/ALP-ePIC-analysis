#ifndef MYSELECTIONCRITERIA
#define MYSELECTIONCRITERIA

#include <iostream>
using namespace std;

class MySelectionCriteria
{
public:
    // PDG ID of final-state lepton, two ALP decay products characterize the event
    int PDG_Lepton;
    int PDG_Decay1;
    int PDG_Decay2;

    // Track
    float Max_Track_Eta;
    float Min_Track_Eta;
    float Min_Track_P;
    int Min_Track_Nhits;

    // Vertex
    float Max_Vertex_Z;
    float Max_Vertex_R;

    // Scattered lepton
    float Max_Lepton_Eta;
    float Min_Lepton_Eta;
    float Min_Lepton_Pt;
    float Min_Lepton_P;
    float Max_Lepton_Ep;
    float Min_Lepton_Ep;

    // Decay particles
    float Max_Decay_Eta;
    float Min_Decay_Eta;
    float Min_Decay_Pt;

    // Clusters
    float Min_ECal_Cluster_E;
    float Min_HCal_Cluster_E;



public:
    MySelectionCriteria(){LoadDefault();}//Loads default (non-decaying ALP) selection cuts}
    ~MySelectionCriteria(){}

    // Defaults to e + A -> e + a with a (= ALP) escaping the detector
    // PDG_Decay = 0 == No ALP decay, = 21 (gluon) == Jet production
    void LoadDefault()
    {
        PDG_Lepton = 11;
        PDG_Decay1 = 0;
        PDG_Decay2 = 0;

        Max_Lepton_Eta = 4.0;
        Min_Lepton_Eta = -4.0;
        Min_Lepton_Pt = 0.5;
        Min_Lepton_P = 0.5;

        Max_Lepton_Ep = 99999;
        Min_Lepton_Ep = 0;

        Max_Decay_Eta = 4.0;
        Min_Decay_Eta = -4.0;
        Min_Decay_Pt = 0.5;

        Max_Track_Eta = 4.0;
        Min_Track_Eta = -4.0;
        Min_Track_P = 0.5;
        Min_Track_Nhits = 5;

        Max_Vertex_Z = 99999;
        Max_Vertex_R = 99999;

        Min_ECal_Cluster_E = 0.0;
        Min_HCal_Cluster_E = 0.0;
    }

    void LoadNonDecayingALP()
    {

    }
};

#endif
