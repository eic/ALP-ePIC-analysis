#include "MyAnalysis.h"

void set_branches(TTree*& tree, MyEvent* ev)
{
    tree->Branch("event", &ev);
}

// *****************************************************************************
bool MyAnalysis::InitTree()
{
    mTreeFile = new TFile(TString(mTreeFileName), "recreate");
    mTreeFile->cd();
    mTree = new TTree("tree", "tree");
    mTree->Branch("event", &ev);
    //
    //set_branches(mTree, ev);

    return true;
}

bool MyAnalysis::FillTree()
{
    mTree->Fill();
    return true;
}

bool MyAnalysis::SaveTree()
{
    mTreeFile->cd();
    mTree->Write();
    mTreeFile->Write();
    mTreeFile->Close();
    return true;
}
