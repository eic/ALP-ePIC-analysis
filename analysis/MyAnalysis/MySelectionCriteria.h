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

    float Max_Lepton_Eta;
    float Min_Lepton_Eta;
    float Min_Lepton_Pt;

    float Max_Decay_Eta;
    float Min_Decay_Eta;
    float Min_Decay_Pt;

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

        Max_Decay_Eta = 4.0;
        Min_Decay_Eta = -4.0;
        Min_Decay_Pt = 0.5;
    }

    void LoadNonDecayingALP()
    {

    }
};

#endif
