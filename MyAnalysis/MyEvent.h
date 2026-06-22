#ifndef MYEVENT
#define MYEVENT

#include <vector>
#include <map>

#include <TVector3.h>
#include <TLorentzVector.h>

#include <edm4eic/Vertex.h>
#include <edm4hep/MCParticle.h>
#include <edm4eic/ReconstructedParticle.h>
#include <edm4eic/TrackSegmentCollection.h>

#include <edm4eic/Track.h>
#include <edm4eic/TrackPoint.h>
#include <edm4eic/Cluster.h>

using namespace std;

class MyParticle
{
public:
    edm4hep::MCParticle sim;
    edm4eic::ReconstructedParticle rec;

    int bitmask; // includes all track hits
    int bitmask2; // includes only the last hit of tracker and high-ET cluster
    bool is_track_endcap_n;
    bool is_track_endcap_p;
    bool is_track_barrel;
    bool is_track_tagger;
    bool is_cluster_endcap_n;
    bool is_cluster_endcap_p;
    bool is_cluster_barrel;
    //AW 20260616 might add more of these for the ZDC and B0 calorimeters!!


    vector<edm4eic::Track> tracks;
    vector<vector<edm4eic::TrackPoint>> points; // for projection
    vector<edm4eic::Track> tracks_tagger;

    // Track
    edm4eic::Track track; // CentralCKFTracks
    vector<edm4eic::TrackPoint> projection; // Projection for CentralCKFTracks
    int nhits;


    // EMC
    vector<edm4eic::Cluster> clusters;
    edm4eic::Cluster cluster_high;
    edm4eic::Cluster cluster_near;
    TVector3 pos_cluster_sum;
    float ene_cluster_sum;
    TVector3 pos_track;

    // HCal
    vector<edm4eic::Cluster> hclusters;
    edm4eic::Cluster hcluster_high;
    edm4eic::Cluster hcluster_near;
    TVector3 pos_hcluster_sum;
    float ene_hcluster_sum;
    TVector3 pos_track_hcal;

    // AW 20260616 calorimeter stuff for the BDT tree
    // I'll do it in a silly way for now
    vector<edm4eic::Cluster> bdt_clusters;

    MyParticle()
    {
        Clear();
    }

    ~MyParticle()
    {
        Clear();
    }

    void Clear()
    {
        sim = edm4hep::MCParticle();
        rec = edm4eic::ReconstructedParticle();

        bitmask = 0;
        bitmask2 = 0;

        is_track_endcap_n = false;
        is_track_endcap_p = false;
        is_track_barrel = false;
        is_track_tagger = false;

        is_cluster_endcap_n = false;
        is_cluster_endcap_p = false;
        is_cluster_barrel = false;

        tracks.clear();
        points.clear();
        tracks_tagger.clear();

        track = edm4eic::Track();
        projection.clear();
        nhits = 0;

        clusters.clear();
        cluster_high = edm4eic::Cluster();
        cluster_near = edm4eic::Cluster();
        pos_cluster_sum = TVector3(0,0,0);
        ene_cluster_sum = 0;
        pos_track = TVector3(0,0,0);

        hclusters.clear();
        hcluster_high = edm4eic::Cluster();
        hcluster_near = edm4eic::Cluster();
        pos_hcluster_sum = TVector3(0,0,0);
        ene_hcluster_sum = 0;
        pos_track_hcal = TVector3(0,0,0);

        bdt_clusters.clear();
    }
};



class MyEvent
{
public:
    int id;
    uint32_t collectionID_BEMC; // Should move to MyAnalysis eventually
    uint32_t collectionID_NEMC; // Should move to MyAnalysis eventually
    uint32_t collectionID_PEMC; // Should move to MyAnalysis eventually
    uint32_t collectionID_BHCal; // Should move to MyAnalysis eventually
    uint32_t collectionID_NHCal; // Should move to MyAnalysis eventually
    uint32_t collectionID_PHCal; // Should move to MyAnalysis eventually

    int nmatches; // cluster-track matching (EMC)
    int nmatches_hcal; // cluster-track matching (HCal)

    vector<MyParticle> particles; // particles with sim-rec association
    vector<edm4hep::MCParticle> particles_sim; // all simulated particle
    vector<edm4eic::ReconstructedParticle> particles_rec; // all reconstructed particle
    vector<edm4eic::Cluster> clusters; // all EMC clusters
    vector<edm4eic::Cluster> hclusters; // all HCal clusters

    //AW 20260616
    vector<edm4eic::Cluster> bdt_clusters;

    TVector3 pele;//rec
    TVector3 peletrue;
    TVector3 pbeam;//true
    TVector3 pion;//true
    TVector3 palp;//true

    float q2;
    TVector3 pmiss;
    float q2true;
    TVector3 pmisstrue;

    //I'm thinking it's event per event?? a "different" variable?
    int bdt_nev, sig_bkgd_label; //these might be wrong, these might need to be event variables????
    float bdt_elec_e, bdt_pt, bdt_eta, bdt_elec_beam_rat, bdt_pt_miss, bdt_p, bdt_phi, bdt_q2, bdt_angle;
    int bdt_mult; //multiplicity
    float bdt_RP, bdt_ZDC, bdt_b0;

    //AW 20260622 new quantities
    float bdt_dr, bdt_e_pz, bdt_et, bdt_pperp, bdt_et_pperp, bdt_dphi, bdt_dphi_avg;

    MyEvent()
    {
        Clear();
    }

    ~MyEvent()
    {
        Clear();
    }

    void Clear()
    {
        id = -1;
        collectionID_BEMC = 0;
        collectionID_NEMC = 0;
        collectionID_PEMC = 0;
        nmatches = 0;
        nmatches_hcal = 0;
        particles_sim.clear();
        particles_rec.clear();
        particles.clear();
        clusters.clear();
        hclusters.clear();
        bdt_clusters.clear(); //AW 20260616

        pele = TVector3(0,0,0);
        peletrue = TVector3(0,0,0);
        pbeam = TVector3(0,0,0);
        pion = TVector3(0,0,0);
        palp = TVector3(0,0,0);

        q2 = 0;
        pmiss = TVector3(0,0,0);
        q2true = 0;
        pmisstrue = TVector3(0,0,0);

        //AW 20260605
        bdt_nev = 0; //these might be wrong, these might need to be event variables????
        sig_bkgd_label = -1;
        bdt_elec_e = 0; 
        bdt_pt = 0;
        bdt_eta = 0;
        bdt_elec_beam_rat = 0;
        bdt_pt_miss = 0;
        bdt_p = 0;
        bdt_phi = 0;
        bdt_q2 = 0;
        bdt_angle = 0;

        bdt_mult = 0;
        bdt_RP = 0;
        bdt_ZDC = 0;
        bdt_b0 = 0;

        //AW 20260622 new bdt values
        bdt_dr = 0; 
        bdt_e_pz = 0;
        bdt_et = 0;
        bdt_pperp = 0;
        bdt_et_pperp = 0;
        bdt_dphi = 0;
        bdt_dphi_avg = 0;

    }

    edm4eic::ReconstructedParticle GetFinalLepton()
    {
        for (auto par : particles) if (par.sim.getPDG() == 11 && par.sim.getGeneratorStatus() == 1) return par.rec;
        return edm4eic::ReconstructedParticle::makeEmpty();
    }

    edm4hep::MCParticle GetFinalLeptonTrue()
    {
        for (auto par : particles_sim) if (par.getPDG() == 11 && par.getGeneratorStatus() == 1) return par;
        return edm4hep::MCParticle::makeEmpty();
    }

    edm4hep::MCParticle GetInitialLeptonTrue()
    {
        for (auto par : particles_sim) if (par.getPDG() == 11 && par.getGeneratorStatus() == 4) return par;
        return edm4hep::MCParticle::makeEmpty();
    }

    edm4hep::MCParticle GetALPTrue()
    {
        for (auto par : particles_sim) if (par.getPDG() == 0 && par.getGeneratorStatus() == 1) return par;
        return edm4hep::MCParticle::makeEmpty();
    }



    void Print();
};









inline void MyEvent::Print()
{
    int ww = 15;
    cout << "*******************************************************************" << endl;
    cout << "Event " << id << " Information" << endl;
    cout << " - Event Parameters:" << endl;
    cout << "type" << setw(ww) << "Q2" << setw(ww) << "pmiss" << setw(ww) << "pzmiss" << setw(ww) << "pTmiss" << setw(ww) << "eta_miss" << setw(ww) << "phi_miss" << endl;
    cout << "sim" << setw(ww) << q2true << setw(ww) << pmisstrue.Mag() << setw(ww) << pmisstrue.Pz() << setw(ww) << pmisstrue.Pt() << setw(ww) << pmisstrue.Eta() << setw(ww) << pmisstrue.Phi() << endl;
    cout << "rec" << setw(ww) << q2 << setw(ww) << pmiss.Mag() << setw(ww) << pmiss.Pz() << setw(ww) << pmiss.Pt() << setw(ww) << pmiss.Eta() << setw(ww) << pmiss.Phi() << endl;

    cout << " - MCParticle List:" << endl;
    for (unsigned int i = 0; i < particles_sim.size(); ++i)
    {
        auto par = particles_sim[i];
        TVector3 p(par.getMomentum().x, par.getMomentum().y, par.getMomentum().z);
        int mother1 = par.parents_size() > 0 ? par.getParents()[0].getObjectID().index : -9999;
        int mother2 = par.parents_size() > 1 ? par.getParents()[1].getObjectID().index : -9999;
        if (i == 0) cout << setw(ww) << "i" << setw(ww) << "stat" << setw(ww) << "mother1" << setw(ww) << "mother2" << setw(ww) << "pdg" << setw(ww) << "p" << setw(ww) << "pz" << setw(ww) << "pt" << setw(ww) << "eta" << setw(ww) << "phi" << endl;
        cout << setw(ww) << i << setw(ww) << par.getGeneratorStatus() << setw(ww) << mother1 << setw(ww) << mother2 << setw(ww) << par.getPDG() << setw(ww) << p.Mag() << setw(ww) << p.Pz() << setw(ww) << p.Pt() << setw(ww) << p.Eta() << setw(ww) << p.Phi() << endl;
    }

    cout << " - MCParticle List (short):" << endl;
    for (unsigned int i = 0; i < particles_sim.size(); ++i)
    {
        auto par = particles_sim[i];
        TVector3 p(par.getMomentum().x, par.getMomentum().y, par.getMomentum().z);
        int mother1 = par.parents_size() > 0 ? par.getParents()[0].getObjectID().index : -9999;
        int mother2 = par.parents_size() > 1 ? par.getParents()[1].getObjectID().index : -9999;
        if (i == 0) cout << setw(ww) << "i" << setw(ww) << "stat" << setw(ww) << "mother1" << setw(ww) << "mother2" << setw(ww) << "pdg" << setw(ww) << "p" << setw(ww) << "pz" << setw(ww) << "pt" << setw(ww) << "eta" << setw(ww) << "phi" << endl;
        if (par.getGeneratorStatus() != 1) continue;
        cout << setw(ww) << i << setw(ww) << par.getGeneratorStatus() << setw(ww) << mother1 << setw(ww) << mother2 << setw(ww) << par.getPDG() << setw(ww) << p.Mag() << setw(ww) << p.Pz() << setw(ww) << p.Pt() << setw(ww) << p.Eta() << setw(ww) << p.Phi() << endl;
    }


    if (particles_rec.size() > 0) cout << " - ReconstructedChargedParticle List:" << endl;
    for (unsigned int i = 0; i < particles_rec.size(); ++i)
    {
        auto par = particles_rec[i];
        TVector3 p(par.getMomentum().x, par.getMomentum().y, par.getMomentum().z);
        if (i == 0) cout << setw(ww) << "i" << setw(ww) << "pdg" << setw(ww) << "p" << setw(ww) << "pz" << setw(ww) << "pt" << setw(ww) << "eta" << setw(ww) << "phi" << endl;
        cout << setw(ww) << i << setw(ww) << par.getPDG() << setw(ww) << p.Mag() << setw(ww) << p.Pz() << setw(ww) << p.Pt() << setw(ww) << p.Eta() << setw(ww) << p.Phi() << endl;
    }


    if (clusters.size() > 0) cout << " - EMC Cluster List:" << endl;
    for (unsigned int i = 0; i < clusters.size(); ++i)
    {
        auto c = clusters[i];
        string type = "";
        if (c.getObjectID().collectionID == collectionID_BEMC) type = "BEMC";
        if (c.getObjectID().collectionID == collectionID_NEMC) type = "NEMC";
        if (c.getObjectID().collectionID == collectionID_PEMC) type = "PEMC";
        TVector3 pos(c.getPosition().x, c.getPosition().y, c.getPosition().z);
        if (i == 0) cout << setw(ww) << "i" << setw(ww) << "type" << setw(ww) << "index" << setw(ww) << "energy" << setw(ww) << "radius" << setw(ww) << "z" << setw(ww) << "eta" << setw(ww) << "phi" << endl;
        cout << setw(ww) << i << setw(ww) << type << setw(ww) << c.getObjectID().index << setw(ww) << c.getEnergy() << setw(ww) << pos.Perp() << setw(ww) << pos.Z() << setw(ww) << pos.Eta() << setw(ww) << pos.Phi() << endl;
    }

    if (hclusters.size() > 0) cout << " - HCal Cluster List:" << endl;
    for (unsigned int i = 0; i < hclusters.size(); ++i)
    {
        auto c = hclusters[i];
        string type = "";
        if (c.getObjectID().collectionID == collectionID_BHCal) type = "BHCal";
        if (c.getObjectID().collectionID == collectionID_NHCal) type = "NHCal";
        if (c.getObjectID().collectionID == collectionID_PHCal) type = "PHCal";
        TVector3 pos(c.getPosition().x, c.getPosition().y, c.getPosition().z);
        if (i == 0) cout << setw(ww) << "i" << setw(ww) << "type" << setw(ww) << "index" << setw(ww) << "energy" << setw(ww) << "radius" << setw(ww) << "z" << setw(ww) << "eta" << setw(ww) << "phi" << endl;
        cout << setw(ww) << i << setw(ww) << type << setw(ww) << c.getObjectID().index << setw(ww) << c.getEnergy() << setw(ww) << pos.Perp() << setw(ww) << pos.Z() << setw(ww) << pos.Eta() << setw(ww) << pos.Phi() << endl;
    }


    cout << "*******************************************************************" << endl;
    cout << endl;
}

#endif
