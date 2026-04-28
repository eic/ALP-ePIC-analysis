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
        //if (ev->particles.size() > 0) ev->Print();
        //if (ev->nmatches > 0) ev->Print();

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

    cuts.LoadDefault();

    collectionID_BEMC = 0;
    collectionID_NEMC = 0;
    collectionID_PEMC = 0;
    collectionID_BHCal = 0;
    collectionID_NHCal = 0;
    collectionID_PHCal = 0;

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
    frame = podio::Frame(mReader->readNextEntry(podio::Category::Event));

    ReadPODIO();
    TrackClusterMatching();
    TrackHCalClusterMatching();

    // Your Analysis begins here
    TestingSpace();
    AnalyzeQA();
    AnalyzeEfficiency();
    AnalyzeResolution();
    AnalyzeMatching();
    AnalyzeDecayVertex();

    AnalyzeElectronIdentification();
    // Your Analysis ends here

    return true;
}

// *****************************************************************************
void MyAnalysis::TestingSpace()
{
    // Low Q2 tagger?
    int kk = 0;
    for (unsigned int i = 0; i < ev->particles.size(); ++i)
    {
        auto& par = ev->particles[i];
        auto& sim = par.sim;
        auto& rec = par.rec;
        TVector3 ps(sim.getMomentum().x,sim.getMomentum().y,sim.getMomentum().z);
        TVector3 pr(rec.getMomentum().x,rec.getMomentum().y,rec.getMomentum().z);

        //if (ps.Eta() > -6 || pr.Eta() > -6) continue;
        if (par.tracks_tagger.size() == 0) continue;
        kk++;

        int ww = 15;
        if (kk == 1) cout << setw(ww) << "i" << setw(ww) << "type" << setw(ww) << "PDG" << setw(ww) << "Collection" << setw(ww) << "P" << setw(ww) << "Pz" << setw(ww) << "Pt" << setw(ww) << "eta" << setw(ww) << "phi" << endl;
        cout << setw(ww) << i << setw(ww) << "MCParticle" << setw(ww) << sim.getPDG() << setw(ww) << sim.getObjectID().collectionID << setw(ww) << ps.Mag() << setw(ww) << ps.Pz() << setw(ww) << ps.Pt() << setw(ww) << ps.Eta() << setw(ww) << ps.Phi() << endl;
        cout << setw(ww) << i << setw(ww) << "RecChaPar" << setw(ww) << "" << setw(ww) << rec.getObjectID().collectionID << setw(ww) << pr.Mag() << setw(ww) << pr.Pz() << setw(ww) << pr.Pt() << setw(ww) << pr.Eta() << setw(ww) << pr.Phi() << endl;
        for (unsigned int j = 0; j < par.tracks.size(); ++j)
        {
            auto& trk = par.tracks[j];
            TVector3 p(trk.getMomentum().x,trk.getMomentum().y,trk.getMomentum().z);
            cout << setw(ww) << i << setw(ww) << "Track" << setw(ww) << "" << setw(ww) << trk.getObjectID().collectionID << setw(ww) << p.Mag() << setw(ww) << p.Pz() << setw(ww) << p.Pt() << setw(ww) << p.Eta() << setw(ww) << p.Phi() << endl;
        }
        for (unsigned int j = 0; j < par.tracks_tagger.size(); ++j)
        {
            auto& trk = par.tracks_tagger[j];
            TVector3 p(trk.getMomentum().x,trk.getMomentum().y,trk.getMomentum().z);
            cout << setw(ww) << i << setw(ww) << "TagTrk" << setw(ww) << "" << setw(ww) << trk.getObjectID().collectionID << setw(ww) << p.Mag() << setw(ww) << p.Pz() << setw(ww) << p.Pt() << setw(ww) << p.Eta() << setw(ww) << p.Phi() << endl;
        }
    }
}
