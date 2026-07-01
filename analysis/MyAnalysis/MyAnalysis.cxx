#include <type_traits>

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

template <typename T>
void print_vector(const vector<T>& vec, int ww = 15);

// *****************************************************************************
MyAnalysis::MyAnalysis()
{
    cuts.LoadDefault();
}

MyAnalysis::MyAnalysis(string ifname, string ofname)
{
    mInFileName = ifname;
    mOutFileName = ofname;
    mMakeTree = false;

    cuts.LoadDefault();
}

MyAnalysis::MyAnalysis(string ifname, string ofname, string treefname)
{
    mInFileName = ifname;
    mOutFileName = ofname;
    mTreeFileName = treefname;
    mMakeTree = true;

    cuts.LoadDefault();
}

// *****************************************************************************
MyAnalysis::~MyAnalysis()
{
    delete mReader;
    delete mOutFile;
    delete ev;
    if (mMakeTree)
    {
        delete mTreeFile;
        delete mTree;
    }
}

// *****************************************************************************
bool MyAnalysis::Run()
{
    Init();
    if (mMakeTree) InitTree();
    while (Next())
    {
        if (nev % 100 == 0) cout << nev << " events processed..." << endl;
        //if (ev->particles_rec.size() > 0) ev->Print();
        //if (ev->particles.size() > 0) ev->Print();
        //if (ev->nmatches > 0) ev->Print();

        if (mMakeTree) FillTree();
        nev++;
    }
    if (mMakeTree) SaveTree();
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
    frame = podio::Frame(mReader->readNextEntry(podio::Category::Event));

    ReadPODIO();
    Preselection();
    ReconstructEventQuantities();

    // Your Analysis begins here
    TestingSpace();
    AnalyzeQA();
    AnalyzeEfficiency();
    AnalyzeResolution();
    AnalyzeMatching();
    AnalyzeBackground();

    return true;
}

// *****************************************************************************
void MyAnalysis::TestingSpace()
{
    if (ev->multiplicity == 0) return;

    int ww = 15;
    int i = 0;

    cout << endl;
    cout << "Event:" << endl;
    print_vector<string>({"id", "istrue", "Q2", "x", "y", "pe", "pZe", "pTe", "etae", "phie"}, ww);
    print_vector<float>({ev->id, 1, ev->q2true, ev->xtrue, ev->ytrue, ev->peletrue.Mag(), ev->peletrue.Pz(), ev->peletrue.Pt(), ev->peletrue.Eta(), ev->peletrue.Phi()}, ww);
    print_vector<float>({ev->id, 0, ev->q2, ev->x, ev->y, ev->pele.Mag(), ev->pele.Pz(), ev->pele.Pt(), ev->pele.Eta(), ev->pele.Phi()}, ww);

    cout << endl;
    print_vector<string>({"multiplicity", "empz", "pTsET", "dphi_e_near", "dR_e_near", "dphi_e_pmiss"}, ww);
    print_vector<float>({ev->multiplicity, ev->empz, ev->pTsqrtET, ev->dphi_e_near, ev->dR_e_near, ev->dphi_e_pmiss}, ww);


    cout << endl;
    cout << "Gen:" << endl;
    i = 0;
    for (auto& [key, sim] : ev->sim)
    {
        if (sim.status % 1000 != 1 || int(sim.status / 1000) == 2) continue;
        if (i == 0) print_vector<string>({"i", "stat", "pdg", "ene", "p", "pz", "pT", "eta", "phi"}, ww);
        print_vector<float>({i, sim.status, sim.pdg, sim.ene, sim.p.Mag(), sim.p.Z(), sim.p.Pt(), sim.p.Eta(), sim.p.Phi()}, ww);
        i++;
    }

    cout << endl;
    cout << "Rec:" << endl;
    i = 0;
    for (auto& [key, rec] : ev->rec)
    {
        auto& sim = ev->sim[rec.isim[0]];
        if (i == 0) print_vector<string>({"i", "type", "is_track_b", "is_track_n", "is_track_p", "is_track_t", "pdg", "ene", "p", "pz", "pT", "eta", "phi", "Enear1", "Enear3", "Enear5", "Enear7", "Enear9"}, ww);
        print_vector<float>({i, rec.type, rec.is_track_b, rec.is_track_n, rec.is_track_p, rec.is_track_t, sim.pdg, rec.ene, rec.p.Mag(), rec.p.Z(), rec.p.Pt(), rec.p.Eta(), rec.p.Phi(), rec.Enear_01, rec.Enear_03, rec.Enear_05, rec.Enear_07, rec.Enear_09}, ww);
        i++;
    }

    cout << endl;
    cout << "Cluster:" << endl;
    i = 0;
    for (auto& c : ev->clusters)
    {
        auto& sim = ev->sim[c.isim[0]];
        if (i == 0) print_vector<string>({"i", "type", "pdg", "ene", "eta", "phi"}, ww);
        print_vector<float>({i, c.type, sim.pdg, c.ene, c.pos.Eta(), c.pos.Phi(), c.collectionID, c.index, sim.collectionID, sim.index}, ww);
        i++;
    }



    cout << endl;

    /*
    pele = TVector3(0,0,0);
    peletrue = TVector3(0,0,0);
    pbeam = TVector3(0,0,0);
    pion = TVector3(0,0,0);
    palp = TVector3(0,0,0);

    q2 = 0;
    pmiss = TVector3(0,0,0);
    q2true = 0;
    pmisstrue = TVector3(0,0,0);
    multiplicity = 0;
    empz = 0;
    pTsqrtET = 0;

    dphi_e_near = -1;
    dR_e_near = -1;
    dphi_e_pmiss = -1;
    */
    return;
}



template <typename T>
void print_vector(const vector<T>& vec, int ww)
{
    for (const auto& x : vec) cout << setw(ww) << x;
    cout << endl;
}
