#include "TTree.h"
#include "TString.h"
#include "TClonesArray.h"
#include "TVector3.h"
#include "TLorentzVector.h"

#include <edm4hep/MCParticleCollection.h>

#include <edm4eic/ClusterCollection.h>
#include <edm4eic/ReconstructedParticleCollection.h>
#include <edm4eic/MCRecoParticleAssociationCollection.h>
#include <edm4eic/MCRecoTrackParticleAssociationCollection.h>

#include <edm4hep/utils/kinematics.h>

#include "MyAnalysis.h"

// *****************************************************************************
MyAnalysis::MyAnalysis()
{

}

MyAnalysis::MyAnalysis(string ifname, string ofname)
{
    mInFileName = ifname;
    mOutFileName = ofname;
}

// *****************************************************************************
MyAnalysis::~MyAnalysis()
{
    //delete mFrame;
    delete mReader;
    delete mOutFile;
    delete ev;
}

// *****************************************************************************
bool MyAnalysis::Run()
{
    Init();
    while (Next())
    {
        if (nev % 100 == 0) cout << nev << " events processed..." << endl;
        if (ev->particles.size() > 0) ev->Print();

        nev++;
    }
    End();

    return true;
}

// *****************************************************************************
bool MyAnalysis::Init()
{
    mReader = new podio::ROOTReader();
    mReader->openFile(mInFileName);

    mOutFile = new TFile(TString(mOutFileName), "recreate");
    mOutFile->cd();
    ReserveHistograms();

    nev = 0;
    ev = new MyEvent();

    return true;
}

// *****************************************************************************
bool MyAnalysis::End()
{
    mOutFile->Write();
    mOutFile->Close();
    return true;
}

// *****************************************************************************
bool MyAnalysis::Next()
{
    if (nev >= mReader->getEntries(podio::Category::Event)) return false;

    ev->Clear();
    ev->id = nev;
    mFrame = podio::Frame(mReader->readNextEntry(podio::Category::Event));

    ReadPODIO();

    return true;
}
