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
    cuts.LoadDefault();
}

MyAnalysis::MyAnalysis(string ifname, string ofname, string treename)
{
    // AW 20260604 -> thinking that I can just include another file that is a tree
    //I can read the event information into??
    mInFileName = ifname;
    mOutFileName = ofname;
    bdtFileName = treename; //AW 20260604

    cuts.LoadDefault();
}

// *****************************************************************************
MyAnalysis::~MyAnalysis()
{
    delete mReader;
    delete mOutFile;
    delete bdtFile;
    delete ev;
}

// *****************************************************************************
bool MyAnalysis::Run()
{
    Init();
    while (Next())
    {
        if (nev % 100 == 0) cout << nev << " events processed..." << endl;
        //if (ev->particles_rec.size() > 0) ev->Print();
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
    cout << "Hello I am in the Init function for MyAnalysis.cxx!!!" << endl;

    mReader = new podio::ROOTReader();
    mReader->openFile(mInFileName);

    mOutFile = new TFile(TString(mOutFileName), "recreate");
    bdtFile = new TFile(TString(bdtFileName), "recreate");

    // AW 20260604 Don't know the exact placement for this, but it's just an idea:
    bdtTree = new TTree("tree","tree"); 
    //bdt_ev = new Event; // AW 20260604 // will fill this later??

    mOutFile->cd();
    ReserveHistograms();

    nev = 0;
    ev = new MyEvent();

    //AW 20260604 just going to make the branches here??
    // I'm worried about the cd current directory stuff lollll
    bdtTree->Branch("Event_Number",&(ev->bdt_nev));
    bdtTree->Branch("Signal_Background_Label",&(ev->sig_bkgd_label));
    bdtTree->Branch("Electron_Energy", &(ev->bdt_elec_e));
    bdtTree->Branch("Transverse_Momentum",&(ev->bdt_pt));
    bdtTree->Branch("Eta",&(ev->bdt_eta));
    bdtTree->Branch("Electron_to_Beam_Energy_Ratio", &(ev->bdt_elec_beam_rat));
    bdtTree->Branch("Missing_Pt",&(ev->bdt_pt_miss));
    bdtTree->Branch("Momentum", &(ev->bdt_p));
    bdtTree->Branch("Phi", &(ev->bdt_phi));
    bdtTree->Branch("Q2", &(ev->bdt_q2));
    bdtTree->Branch("Opening_Angle_between_Beam_and_Particle", &(ev->bdt_angle));

    bdtTree->Branch("Multiplicity", &(ev->bdt_mult));
    bdtTree->Branch("Roman_Pots", &(ev->bdt_RP));
    bdtTree->Branch("ZDC", &(ev->bdt_ZDC));
    bdtTree->Branch("B0", &(ev->bdt_b0));
    
    //AW 20260622 Create new branches in the tree!!!
    bdtTree->Branch("Delta_R", &(ev->bdt_dr));
    bdtTree->Branch("elect_ecal_clusters_minus_pz", &(ev->bdt_e_pz));
    bdtTree->Branch("Ecal_clusters_e", &(ev->bdt_et));
    bdtTree->Branch("perp_p", &(ev->bdt_pperp));
    bdtTree->Branch("pperp_sqrt_et_ratio", &(ev->bdt_et_pperp));
    bdtTree->Branch("Delta_Phi", &(ev->bdt_dphi));
    bdtTree->Branch("Delta_Phi_Average", &(ev->bdt_dphi_avg));


    //int bdt_mult; //multiplicity
    //float bdt_RP, bdt_ZDC, bdt_b0;


    cout << "hello!!!!!!????? wtf am i??"<<endl;    
    string incl_signal = "aem_axem";
    string decay_signal = "aem_ax_emmupmum";
    string dis_bkgd = "dis";
    string DIS_bkgd = "DIS";
    string qed_bkgd = "qed_compton";

    /*
    file_type = 0; -> inclusive signal
    file_type = 1; -> decay signal
    file_type = 2; -> dis bkgd
    file_type = 3; -> qed compton bkgd 
    */

    file_type = -1;

    if(mInFileName.find(incl_signal) !=std::string::npos){
        file_type = 0;
    }
    if(mInFileName.find(decay_signal) !=std::string::npos){
        file_type = 1;
    }
    if(mInFileName.find(dis_bkgd) !=std::string::npos){
        file_type = 2;
    }
    if(mInFileName.find(DIS_bkgd) !=std::string::npos){
        file_type = 2;
    }
    if(mInFileName.find(qed_bkgd) !=std::string::npos){
        file_type = 3;
    }

    cout <<"Input file name:  "<< mInFileName << endl;
    cout << "file_type!!   "<< file_type << endl;

    collectionID_CKF = 0;
    //collectionID_TaggerM1 = 0;
    //collectionID_TaggerM2 = 0;

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
    bdtTree->Write(); //AW 20260604
    bdtFile->Write(); //AW 20260604
    bdtFile->Close(); //AW 20260604

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

    //cout << "I made it to the Next function in MyAnalysis.cxx!!" << endl;

    ReadPODIO();

    TrackClusterMatching();
    TrackHCalClusterMatching();
    FindEventQuantities();
    CategorizeEvent();
    WriteToBdtTree(); // AW 2026 put it in MyAnalysisReconstruction.cxx
    
    // Your Analysis begins here
    TestingSpace();
    AnalyzeQA();
    AnalyzeEfficiency();
    AnalyzeResolution();
    AnalyzeMatching();
    AnalyzeDecayVertex();

    AnalyzeElectronIdentification();
    // Your Analysis ends here

    //cout << "here 1 billion" << endl;

    return true;
}

// *****************************************************************************
void MyAnalysis::TestingSpace()
{
    // Event classification: LowQ2, EndcapN, Barrel, EndcapP
    if (true)
    {
        for (unsigned int i = 0; i < ev->particles.size(); ++i)
        {
            auto& par = ev->particles[i];
            auto& sim = par.sim;
            auto& rec = par.rec;
            TVector3 ps(sim.getMomentum().x,sim.getMomentum().y,sim.getMomentum().z);
            TVector3 pr(rec.getMomentum().x,rec.getMomentum().y,rec.getMomentum().z);


            int ww = 15;
            if (i == 0) cout << endl;
            if (i == 0) cout << setw(ww) << "i" << setw(ww) << "type" << setw(ww) << "PDG" << setw(ww) << "Collection" << setw(ww) << "P/E" << setw(ww) << "Pz/Z" << setw(ww) << "Pt/R" << setw(ww) << "eta" << setw(ww) << "phi" << endl;

            cout << setw(ww) << i << setw(ww) << "Gen" << setw(ww) << sim.getPDG() << setw(ww) << sim.getObjectID().collectionID << setw(ww) << ps.Mag() << setw(ww) << ps.Pz() << setw(ww) << ps.Pt() << setw(ww) << ps.Eta() << setw(ww) << ps.Phi() << endl;
            cout << setw(ww) << i << setw(ww) << "Rec" << setw(ww) << "" << setw(ww) << rec.getObjectID().collectionID << setw(ww) << pr.Mag() << setw(ww) << pr.Pz() << setw(ww) << pr.Pt() << setw(ww) << pr.Eta() << setw(ww) << pr.Phi() << endl;
            for (unsigned int j = 0; j < par.tracks.size(); ++j)
            {
                auto& trk = par.tracks[j];
                TVector3 p(trk.getMomentum().x,trk.getMomentum().y,trk.getMomentum().z);
                cout << setw(ww) << i << setw(ww) << "Track" << setw(ww) << "" << setw(ww) << trk.getObjectID().collectionID << setw(ww) << p.Mag() << setw(ww) << p.Pz() << setw(ww) << p.Pt() << setw(ww) << p.Eta() << setw(ww) << p.Phi() << setw(ww) << endl;
                for (unsigned int k = 0; k < trk.measurements_size(); ++k)
                {
                    auto hit = trk.getMeasurements(k);
                    auto id = hit.getSurface();
                    uint64_t volume = (id >> 56) & 0xFF;
                    uint64_t boundary = (id >> 48) & 0xFF;
                    uint64_t layer  = (id >> 36) & 0xFFF;
                    uint64_t approach = (id >> 28) & 0xFF;
                    uint64_t sensitive = (id >> 8) & 0xFFFFF;
                    uint64_t extra = (id >> 0) & 0xFF;
                    //cout << setw(ww) << i << setw(ww) << "Hit" << setw(2*ww) << hit.getSurface() << setw(ww) << hit.getLoc().a << setw(ww) << hit.getLoc().b << endl;
                    //cout << setw(ww) << i << setw(ww) << "Hit" << setw(ww) << hit.hits_size() << endl;
                    //cout << setw(ww) << i << setw(ww) << "Hit" << setw(2*ww) << id << setw(ww) << volume << setw(ww) << boundary << setw(ww) << layer << setw(ww) << approach << setw(ww) << sensitive << setw(ww) << extra << endl;
                    cout << setw(ww) << i << setw(ww) << "Hit" << setw(ww) << extra << endl;
                }
            }
            for (unsigned int j = 0; j < par.tracks_tagger.size(); ++j)
            {
                auto& trk = par.tracks_tagger[j];
                TVector3 p(trk.getMomentum().x,trk.getMomentum().y,trk.getMomentum().z);
                cout << setw(ww) << i << setw(ww) << "TagTrk" << setw(ww) << "" << setw(ww) << trk.getObjectID().collectionID << setw(ww) << p.Mag() << setw(ww) << p.Pz() << setw(ww) << p.Pt() << setw(ww) << p.Eta() << setw(ww) << p.Phi() << endl;
            }
            for (unsigned int j = 0; j < par.clusters.size(); ++j)
            {
                auto& c = par.clusters[j];
                TVector3 pos(c.getPosition().x,c.getPosition().y,c.getPosition().z);
                cout << setw(ww) << i << setw(ww) << "Cluster" << setw(ww) << "" << setw(ww) << c.getObjectID().collectionID << setw(ww) << c.getEnergy() << setw(ww) << pos.Z() << setw(ww) << pos.Perp() << setw(ww) << pos.Eta() << setw(ww) << pos.Phi() << setw(ww) << par.nhits << endl;
            }
            for (unsigned int j = 0; j < par.hclusters.size(); ++j)
            {
                auto& c = par.hclusters[j];
                TVector3 pos(c.getPosition().x,c.getPosition().y,c.getPosition().z);
                cout << setw(ww) << i << setw(ww) << "HCluster" << setw(ww) << "" << setw(ww) << c.getObjectID().collectionID << setw(ww) << c.getEnergy() << setw(ww) << pos.Z() << setw(ww) << pos.Perp() << setw(ww) << pos.Eta() << setw(ww) << pos.Phi() << setw(ww) << par.nhits << endl;
            }
        }

    }

    /*
    // Low Q2 tagger
    if (false)
    {
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
                cout << setw(ww) << i << setw(ww) << "Track" << setw(ww) << "" << setw(ww) << trk.getObjectID().collectionID << setw(ww) << p.Mag() << setw(ww) << p.Pz() << setw(ww) << p.Pt() << setw(ww) << p.Eta() << setw(ww) << p.Phi() << setw(ww) << par.nhits << endl;
            }
            for (unsigned int j = 0; j < par.tracks_tagger.size(); ++j)
            {
                auto& trk = par.tracks_tagger[j];
                TVector3 p(trk.getMomentum().x,trk.getMomentum().y,trk.getMomentum().z);
                cout << setw(ww) << i << setw(ww) << "TagTrk" << setw(ww) << "" << setw(ww) << trk.getObjectID().collectionID << setw(ww) << p.Mag() << setw(ww) << p.Pz() << setw(ww) << p.Pt() << setw(ww) << p.Eta() << setw(ww) << p.Phi() << endl;
            }
        }
    }
    */
}
