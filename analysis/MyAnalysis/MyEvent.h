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
    edm4eic::Track track; // CentralCKFTracks
    vector<edm4eic::TrackPoint> projection; // Projection for CentralCKFTracks
    vector<edm4eic::Track> tracks;
    vector<vector<edm4eic::TrackPoint>> points; // for projection
    vector<edm4eic::Track> tracks_tagger;

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
        track = edm4eic::Track();
        projection.clear();
        tracks.clear();
        points.clear();
        tracks_tagger.clear();

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
        particles_sim.clear();
        particles_rec.clear();
        particles.clear();
        clusters.clear();
        hclusters.clear();
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

    float Q2_true()
    {
        auto ele1 = GetInitialLeptonTrue();
        auto ele2 = GetFinalLeptonTrue(); if (ele2 == edm4hep::MCParticle::makeEmpty()) return -1;
        TVector3 p1(ele1.getMomentum().x, ele1.getMomentum().y, ele1.getMomentum().z);
        TVector3 p2(ele2.getMomentum().x, ele2.getMomentum().y, ele2.getMomentum().z);
        return 2 * ele1.getEnergy() * ele2.getEnergy() * (1.0 - cos(p1.Theta() - p2.Theta()));
    }

    float Q2()
    {
        auto ele1 = GetInitialLeptonTrue();
        auto ele2 = GetFinalLepton(); if (ele2 == edm4eic::ReconstructedParticle::makeEmpty()) return -1;
        TVector3 p1(ele1.getMomentum().x, ele1.getMomentum().y, ele1.getMomentum().z);
        TVector3 p2(ele2.getMomentum().x, ele2.getMomentum().y, ele2.getMomentum().z);
        return 2 * ele1.getEnergy() * ele2.getEnergy() * (1.0 - cos(p1.Theta() - p2.Theta()));
    }

    TVector3 pTmiss_true()
    {
        TVector3 psum;
        for (auto par : particles_sim) if (par.getGeneratorStatus() == 1 && par.getPDG() != 0) {TVector3 p(par.getMomentum().x, par.getMomentum().y, par.getMomentum().z); psum = psum + p;}
        return -psum;
    }

    TVector3 pTmiss()
    {
        TVector3 psum;
        for (auto par : particles_rec) {TVector3 p(par.getMomentum().x, par.getMomentum().y, par.getMomentum().z); psum = psum + p;}
        return -psum;
    }

    void Print();
};









inline void MyEvent::Print()
{
    int ww = 15;
    cout << "*******************************************************************" << endl;
    cout << "Event " << id << " Information" << endl;
    cout << " - MCParticle List:" << endl;
    for (unsigned int i = 0; i < particles_sim.size(); ++i)
    {
        auto par = particles_sim[i];
        TVector3 p(par.getMomentum().x, par.getMomentum().y, par.getMomentum().z);
        int mother1 = par.parents_size() > 0 ? par.getParents()[0].getObjectID().index : -9999;
        int mother2 = par.parents_size() > 1 ? par.getParents()[1].getObjectID().index : -9999;
        if (i == 0) cout << setw(ww) << "i" << setw(ww) << "stat" << setw(ww) << "mother1" << setw(ww) << "mother2" << setw(ww) << "pdg" << setw(ww) << "pt" << setw(ww) << "eta" << setw(ww) << "phi" << endl;
        cout << setw(ww) << i << setw(ww) << par.getGeneratorStatus() << setw(ww) << mother1 << setw(ww) << mother2 << setw(ww) << par.getPDG() << setw(ww) << p.Pt() << setw(ww) << p.Eta() << setw(ww) << p.Phi() << endl;
    }

    if (particles_rec.size() > 0) cout << " - ReconstructedChargedParticle List:" << endl;
    for (unsigned int i = 0; i < particles_rec.size(); ++i)
    {
        auto par = particles_rec[i];
        TVector3 p(par.getMomentum().x, par.getMomentum().y, par.getMomentum().z);
        if (i == 0) cout << setw(ww) << "i" << setw(ww) << "pdg" << setw(ww) << "pt" << setw(ww) << "eta" << setw(ww) << "phi" << endl;
        cout << setw(ww) << i << setw(ww) << par.getPDG() << setw(ww) << p.Pt() << setw(ww) << p.Eta() << setw(ww) << p.Phi() << endl;
    }

    if (particles.size() > 0) cout << " - TrackPoint List:" << endl;
    for (unsigned int i = 0; i < particles.size(); ++i)
    {
        auto par = particles[i];
        auto rec = particles[i].rec;
        TVector3 p(rec.getMomentum().x, rec.getMomentum().y, rec.getMomentum().z);
        if (par.points.size() == 0) continue;
        for (unsigned int j = 0; j < par.points.size(); j++)
        {
            for (unsigned int k = 0; k < par.points[j].size(); k++)
            {
                auto pts = par.points[j][k];
                TVector3 pos(pts.position.x, pts.position.y, pts.position.z);
                if (i == 0 && j == 0 && k == 0) cout << setw(ww) << "i" << setw(ww) << "j" << setw(ww) << "k" << setw(ww) << "pdg" << setw(ww) << "pT/R" << setw(ww) << "pZ/z" << setw(ww) << "eta" << setw(ww) << "phi" << endl;
                if (j == 0 && k == 0) cout << setw(ww) << i << setw(ww) << "" << setw(ww) << "" << setw(ww) << par.rec.getPDG() << setw(ww) << p.Pt() << setw(ww) << p.Pz() << setw(ww) << p.Eta() << setw(ww) << p.Phi() << endl;
                cout << setw(ww) << i << setw(ww) << j << setw(ww) << k << setw(ww) << "" << setw(ww) << pos.Perp() << setw(ww) << pos.Z() << setw(ww) << pos.Eta() << setw(ww) << pos.Phi() << endl;
            }
        }

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


    if (nmatches > 0)
    {
        cout << " - Track-Cluster Matching:" << endl;
        for (unsigned int i = 0; i < particles.size(); ++i)
        {
            auto par = particles[i];
            auto rec = par.rec;
            TVector3 p(rec.getMomentum().x, rec.getMomentum().y, rec.getMomentum().z);
            if (i == 0) cout << setw(ww) << "i" << setw(ww) << "type" << setw(ww) << "sub_idx" << setw(ww) << "E/p" << setw(ww) << "pT/R" << setw(ww) << "pz/z" << setw(ww) << "eta" << setw(ww) << "phi" << endl;
            cout << setw(ww) << i << setw(ww) << "rec" << setw(ww) << "" << setw(ww) << p.Mag() << setw(ww) << p.Pt() << setw(ww) << p.Z() << setw(ww) << p.Eta() << setw(ww) << p.Phi() << endl;
            for (unsigned int j = 0; j < par.tracks.size(); ++j)
            {
                auto trk = par.tracks[j];
                TVector3 ptrk(trk.getMomentum().x, trk.getMomentum().y, trk.getMomentum().z);
                cout << setw(ww) << i << setw(ww) << "trk" << setw(ww) << j << setw(ww) << ptrk.Mag() << setw(ww) << ptrk.Pt() << setw(ww) << ptrk.Z() << setw(ww) << ptrk.Eta() << setw(ww) << ptrk.Phi() << endl;
                for (unsigned int k = 0; k < par.points[j].size(); ++k)
                {
                    auto pts = par.points[j][k];
                    TVector3 pos(pts.position.x, pts.position.y, pts.position.z);
                    cout << setw(ww) << i << setw(ww) << "pts" << setw(ww) << k << setw(ww) << "" << setw(ww) << pos.Perp() << setw(ww) << pos.Z() << setw(ww) << pos.Eta() << setw(ww) << pos.Phi() << endl;
                }
            }

            for (unsigned int j = 0; j < par.clusters.size(); ++j)
            {
                auto c = clusters[j];
                string type = "";
                if (c.getObjectID().collectionID == collectionID_BEMC) type = "cls_b";
                if (c.getObjectID().collectionID == collectionID_NEMC) type = "cls_n";
                if (c.getObjectID().collectionID == collectionID_PEMC) type = "cls_p";
                TVector3 pos(c.getPosition().x, c.getPosition().y, c.getPosition().z);
                cout << setw(ww) << i << setw(ww) << type << setw(ww) << j << setw(ww) << c.getEnergy() << setw(ww) << pos.Perp() << setw(ww) << pos.Z() << setw(ww) << pos.Eta() << setw(ww) << pos.Phi() << endl;
            }
        }
    }
    cout << "*******************************************************************" << endl;
    cout << endl;
}

#endif
