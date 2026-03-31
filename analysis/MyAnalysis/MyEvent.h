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
    vector<edm4eic::Cluster> clusters_BEMC;
    vector<edm4eic::Cluster> clusters_NEMC;
    vector<edm4eic::Cluster> clusters_PEMC;
    vector<edm4eic::Track> tracks;
    vector<vector<edm4eic::TrackPoint>> points; // for projection

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
        clusters_BEMC.clear();
        clusters_NEMC.clear();
        clusters_PEMC.clear();
        tracks.clear();
        points.clear();
    }
};



class MyEvent
{
public:
    int id;
    vector<MyParticle> particles; // particles with sim-rec association
    vector<edm4hep::MCParticle> particles_sim; // all simulated particle
    vector<edm4eic::ReconstructedParticle> particles_rec; // all reconstructed particle
    vector<edm4eic::Cluster> clusters; // all clusters

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
        particles_sim.clear();
        particles_rec.clear();
        particles.clear();
        clusters.clear();
    }

    void Print();
};

inline void MyEvent::Print()
{
    int ww = 15;
    cout << "Event " << id << " Information" << endl;
    cout << "MCParticle List:" << endl;
    for (unsigned int i = 0; i < particles_sim.size(); ++i)
    {
        auto par = particles_sim[i];
        TVector3 p(par.getMomentum().x, par.getMomentum().y, par.getMomentum().z);
        int mother1 = par.parents_size() > 0 ? par.getParents()[0].getObjectID().index : -9999;
        int mother2 = par.parents_size() > 0 ? par.getParents()[1].getObjectID().index : -9999;
        if (i == 0) cout << setw(ww) << "i" << setw(ww) << "stat" << setw(ww) << "mother1" << setw(ww) << "mother2" << setw(ww) << "pdg" << setw(ww) << "pt" << setw(ww) << "eta" << setw(ww) << "phi" << endl;
        cout << setw(ww) << i << setw(ww) << par.getGeneratorStatus() << setw(ww) << mother1 << setw(ww) << mother2 << setw(ww) << par.getPDG() << setw(ww) << p.Pt() << setw(ww) << p.Eta() << setw(ww) << p.Phi() << endl;
    }
    cout << "ReconstructedChargedParticle List:" << endl;
    for (unsigned int i = 0; i < particles_rec.size(); ++i)
    {
        auto par = particles_rec[i];
        TVector3 p(par.getMomentum().x, par.getMomentum().y, par.getMomentum().z);
        if (i == 0) cout << setw(ww) << "i" << setw(ww) << "pdg" << setw(ww) << "pt" << setw(ww) << "eta" << setw(ww) << "phi" << endl;
        cout << setw(ww) << i << setw(ww) << par.getPDG() << setw(ww) << p.Pt() << setw(ww) << p.Eta() << setw(ww) << p.Phi() << endl;
    }

    cout << endl;
}

#endif
