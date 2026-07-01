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

// 0 = init/unIDed, 1 = MC signal, 2 = SR fake track (status == 2001), 3 = bremsstrahlung, 4 = Touschek, 5 = Coulomb
#define REC_TYPE_SIGNAL 1
#define REC_TYPE_SYNRAD 2
#define REC_TYPE_BREMSS 3
#define REC_TYPE_TOUSCH 4
#define REC_TYPE_COULOM 5



class MyCluster : public TObject
{
public:
    //edm4eic::Cluster obj;
    int index;
    unsigned int collectionID;

    int type; // 0 = init/unIDed, 1 = MC signal, 2 = SR fake track (status == 2001), 3 = Brems, 4 = Touschek, 5 = Coulomb
    bool isgood;

    vector<int> isim;
    vector<int> irec;
    bool is_ECal;
    bool is_HCal;
    bool is_b;
    bool is_n;
    bool is_p;

    float ene;
    TVector3 pos;

public:
    MyCluster(){Clear();}
    ~MyCluster(){Clear();}
    void Clear()
    {
        index = -1;
        collectionID = 0;

        type = 0;
        isgood = false;

        isim.clear();
        irec.clear();
        is_ECal = false;
        is_HCal = false;
        is_b = false;
        is_n = false;
        is_p = false;

        ene = 0;
        pos = TVector3(0,0,0);
    }

    bool operator==(const MyCluster& other) const
    {
        return (index == other.index) && (collectionID == other.collectionID);
    }

    ClassDef(MyCluster, 1);
};


class MyGeneratedParticle : public TObject
{
public:
    //edm4hep::MCParticle obj;
    int index;
    unsigned int collectionID;

    int type; // 0 = init/unIDed, 1 = MC signal, 2 = SR fake track (status == 2001), 3 = Brems, 4 = Touschek, 5 = Coulomb
    TVector3 p;
    float ene;
    float charge;
    int pdg;
    TVector3 vtx;

    vector<int> irec;
    int status;

    bool isgood;

public:
    MyGeneratedParticle(){Clear();}
    ~MyGeneratedParticle(){Clear();}
    void Clear()
    {
        index = -1;
        collectionID = 0;

        type = 0;

        p = TVector3(0,0,0);
        ene = 0;
        charge = 0;
        pdg = 0;
        vtx = TVector3(0,0,0);

        irec.clear();
        status = 0;

        isgood = false;
    }

    bool operator==(const MyGeneratedParticle& other) const
    {
        return (index == other.index) && (collectionID == other.collectionID);
    }

    ClassDef(MyGeneratedParticle, 1);
};

class MyReconstructedParticle : public TObject
{
public:
    //edm4eic::ReconstructedParticle obj;
    int index;
    unsigned int collectionID;

    TVector3 p;
    float ene;
    float charge;
    int pdg;
    TVector3 vtx; // Track::getPosition() == Poionts to the position of track near the vertex
    TVector3 ref; // ReconstructedParticle::getReferencePoint() == Points to the MCParticle vertex position
    TVector3 pos_ECal; // Position at ECal surface
    TVector3 pos_HCal; // Position at HCal surface
    TVector3 pos_outer; // Position of the outermost tracking hit
    int nhits;
    float Enear_01;
    float Enear_03;
    float Enear_05;
    float Enear_07;
    float Enear_09;

    int type; // 0 = init/unIDed, 1 = MC signal, 2 = SR fake track (status == 2001), 3 = Brems, 4 = Touschek, 5 = Coulomb

    vector<int> isim;
    bool is_track_b;
    bool is_track_n;
    bool is_track_p;
    bool is_track_t;
    bool is_cluster_b;
    bool is_cluster_n;
    bool is_cluster_p;
    unsigned int bitmask;

    vector<MyCluster*> clusters; // truth matched clusters
    MyCluster* cluster; // highest energy ECAL cluster (truth matched)
    MyCluster* cluster_near; // nearest EC cluster (not truth matched)

    vector<MyCluster*> clusters_HCal;
    MyCluster* cluster_HCal; // highest energy HCAL cluster

    // selection
    bool isgood;
    bool isgood_momentum;
    bool isgood_eta;
    bool isgood_tracker;
    bool isgood_Ep;
    bool isgood_vtx;
    bool isgood_pid;
    bool isgood_nhits;


public:
    MyReconstructedParticle(){Clear();}
    ~MyReconstructedParticle()
    {
        Clear();
    }

    void Clear()
    {
        index = -1;
        collectionID = 0;

        p = TVector3(0,0,0);
        ene = 0;
        charge = 0;
        pdg = 0;
        ref = TVector3(0,0,0);
        pos_ECal = TVector3(0,0,0);
        pos_HCal = TVector3(0,0,0);
        pos_outer = TVector3(0,0,0);
        Enear_01 = 0;
        Enear_03 = 0;
        Enear_05 = 0;
        Enear_07 = 0;
        Enear_09 = 0;

        type = 0;

        isim.clear();
        is_track_b = false;
        is_track_n = false;
        is_track_p = false;
        is_track_t = false;
        is_cluster_b = false;
        is_cluster_n = false;
        is_cluster_p = false;
        bitmask = 0;

        nhits = 0;

        cluster = nullptr;
        cluster_near = nullptr;
        clusters.clear();

        cluster_HCal = nullptr;
        clusters_HCal.clear();

        isgood = false;
        isgood_momentum = false;
        isgood_eta = false;
        isgood_tracker = false;
        isgood_Ep = false;
        isgood_vtx = false;
        isgood_pid = false;
        isgood_nhits = false;

    }

    void GenerateBitmask()
    {

    }

    bool operator==(const MyReconstructedParticle& other) const
    {
        return (index == other.index) && (collectionID == other.collectionID);
    }

    ClassDef(MyReconstructedParticle, 1);
};



class MyEvent : public TObject
{
public:
    // New
    int id;
    map<int, MyGeneratedParticle> sim;
    map<int, MyReconstructedParticle> rec;
    vector<MyCluster> clusters;
    vector<MyCluster> clusters_HCal;

    MyGeneratedParticle* eletrue;
    MyReconstructedParticle* ele;
    MyReconstructedParticle* ecand;
    MyGeneratedParticle* beam;
    MyGeneratedParticle* alp;

    TVector3 pele;//rec
    TVector3 peletrue;
    TVector3 pbeam;//true
    TVector3 pion;//true
    TVector3 palp;//true

    float q2;
    float x;
    float y;
    TVector3 pmiss;
    float q2true;
    float xtrue;
    float ytrue;
    TVector3 pmisstrue;

    int multiplicity;
    float empz;
    float pTsqrtET;

    float dphi_e_near;
    float dR_e_near;
    float dphi_e_pmiss;

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
        sim.clear();
        rec.clear();

        id = -1;
        clusters.clear();
        clusters_HCal.clear();

        eletrue = nullptr;
        ele = nullptr;
        ecand = nullptr;
        beam = nullptr;
        alp = nullptr;

        pele = TVector3(0,0,0);
        peletrue = TVector3(0,0,0);
        pbeam = TVector3(0,0,0);
        pion = TVector3(0,0,0);
        palp = TVector3(0,0,0);

        q2 = 0;
        x = 0;
        y = 0;
        pmiss = TVector3(0,0,0);
        q2true = 0;
        xtrue = 0;
        ytrue = 0;
        pmisstrue = TVector3(0,0,0);
        multiplicity = 0;
        empz = 0;
        pTsqrtET = 0;

        dphi_e_near = -1;
        dR_e_near = -1;
        dphi_e_pmiss = -1;
    }

    ClassDef(MyEvent, 1);
};


#endif
