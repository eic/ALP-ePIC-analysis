#include <edm4hep/MCParticleCollection.h>

#include <edm4eic/TrackCollection.h>
#include <edm4eic/ClusterCollection.h>
#include <edm4eic/ReconstructedParticleCollection.h>
#include <edm4eic/MCRecoParticleAssociationCollection.h>
#include <edm4eic/MCRecoTrackParticleAssociationCollection.h>

#include <edm4hep/utils/kinematics.h>

#include "MyAnalysis.h"

// *****************************************************************************
map<unsigned int, vector<edm4hep::MCParticle>> gen_mapping(const edm4eic::MCRecoParticleAssociationCollection& associations);
map<unsigned int, vector<edm4eic::ReconstructedParticle>> rec_mapping(const edm4eic::MCRecoParticleAssociationCollection& associations);

map<unsigned int, vector<edm4eic::Track>> track_mapping(const edm4eic::MCRecoTrackParticleAssociationCollection& associations);
map<unsigned int, vector<edm4eic::TrackPoint>> trackpoint_mapping(const edm4eic::TrackSegmentCollection& projections);
map<unsigned int, vector<edm4eic::Cluster>> cluster_mapping(const edm4eic::MCRecoClusterParticleAssociationCollection& associations);

MyCluster convert_cluster(edm4eic::Cluster c, MySelectionCriteria& cuts, bool is_ECal, int type);

int status2type(int status);

unsigned int generate_bitmask(bool is_track_b, bool is_track_n, bool is_track_p, bool is_track_t, bool is_cluster_b, bool is_cluster_n, bool is_cluster_p);


// *****************************************************************************
bool MyAnalysis::ReadPODIO()
{
    // Collections
    auto& particles_sim = frame.get<edm4hep::MCParticleCollection>("MCParticles");
    auto& particles_rec = frame.get<edm4eic::ReconstructedParticleCollection>("ReconstructedChargedParticles");

    auto& associations = frame.get<edm4eic::MCRecoParticleAssociationCollection>("ReconstructedChargedParticleAssociations");

    auto& clusters_BEMC = frame.get<edm4eic::ClusterCollection>("EcalBarrelClusters");
    auto& clusters_NEMC = frame.get<edm4eic::ClusterCollection>("EcalEndcapNClusters");
    auto& clusters_PEMC = frame.get<edm4eic::ClusterCollection>("EcalEndcapPClusters");

    auto& clusters_BHCal = frame.get<edm4eic::ClusterCollection>("HcalBarrelClusters");
    auto& clusters_NHCal = frame.get<edm4eic::ClusterCollection>("HcalEndcapNClusters");
    auto& clusters_PHCal = frame.get<edm4eic::ClusterCollection>("LFHCALClusters");

    // Mapping
    auto mapGen = gen_mapping(associations);
    auto mapRec = rec_mapping(associations);

    auto mapTrackPoint = trackpoint_mapping(frame.get<edm4eic::TrackSegmentCollection>("CalorimeterTrackProjections"));
    auto mapBEMC = cluster_mapping(frame.get<edm4eic::MCRecoClusterParticleAssociationCollection>("EcalBarrelClusterAssociations"));
    auto mapNEMC = cluster_mapping(frame.get<edm4eic::MCRecoClusterParticleAssociationCollection>("EcalEndcapNClusterAssociations"));
    auto mapPEMC = cluster_mapping(frame.get<edm4eic::MCRecoClusterParticleAssociationCollection>("EcalEndcapPClusterAssociations"));

    auto mapBHCal = cluster_mapping(frame.get<edm4eic::MCRecoClusterParticleAssociationCollection>("HcalBarrelClusterAssociations"));
    auto mapNHCal = cluster_mapping(frame.get<edm4eic::MCRecoClusterParticleAssociationCollection>("HcalEndcapNClusterAssociations"));
    auto mapPHCal = cluster_mapping(frame.get<edm4eic::MCRecoClusterParticleAssociationCollection>("LFHCALClusterAssociations"));

    // Parsing
    // Parse simulated particles
    ev->sim.clear();
    //ev->sim.reserve(particles_sim.size());
    for (const auto& par : particles_sim)
    {
        int objectID = par.getObjectID().index;
        auto& sim = ev->sim[objectID];
        //sim.obj = par; // Also store the PODIO obj
        sim.collectionID = par.getObjectID().collectionID;
        sim.index = par.getObjectID().index;
        sim.status = par.getGeneratorStatus();
        sim.type = status2type(sim.status);
        sim.p = TVector3(par.getMomentum().x, par.getMomentum().y, par.getMomentum().z);
        sim.ene = par.getEnergy();
        sim.charge = par.getCharge();
        sim.pdg = par.getPDG();
        sim.vtx = TVector3(par.getVertex().x, par.getVertex().y, par.getVertex().z);

        sim.irec.clear();
        if (mapRec.count(objectID)) for (const auto& rec : mapRec.at(objectID)) sim.irec.push_back(rec.getObjectID().index);
    }

    // Parse reconstructed particles
    // Ideally, we use particle flow object once it comes online
    // However, this is not the case for now
    // There were some issues using ReconstructedParticle when it comes to correctly populating tracks from fake tracker hits
    // So, we use ReconstructedChargedParticle + separate record of clusters for now
    // For convenience, we keep two copies of (almost) all clusters;
    // Under MyReconstructedParticle::clusters, and MyEvent::clusters (and _HCal)
    // We should really keep one copy and refer to it in MyReconstructedParticle
    // But I am too lazy... and they are really small objects

    // Clusters
    for (const auto& c : clusters_BEMC) ev->clusters.push_back(convert_cluster(c, cuts, 1, 0));
    for (const auto& c : clusters_NEMC) ev->clusters.push_back(convert_cluster(c, cuts, 1, 1));
    for (const auto& c : clusters_PEMC) ev->clusters.push_back(convert_cluster(c, cuts, 1, 2));

    for (const auto& c : clusters_BHCal) ev->clusters_HCal.push_back(convert_cluster(c, cuts, 0, 0));
    for (const auto& c : clusters_NHCal) ev->clusters_HCal.push_back(convert_cluster(c, cuts, 0, 1));
    for (const auto& c : clusters_PHCal) ev->clusters_HCal.push_back(convert_cluster(c, cuts, 0, 2));

    // Add associations to the cluster
    for (auto& [idsim, vc] : mapBEMC) for (auto& c : vc) for (auto& myc : ev->clusters) if (myc.index == c.getObjectID().index && myc.collectionID == c.getObjectID().collectionID) myc.isim.push_back(idsim);
    for (auto& [idsim, vc] : mapNEMC) for (auto& c : vc) for (auto& myc : ev->clusters) if (myc.index == c.getObjectID().index && myc.collectionID == c.getObjectID().collectionID) myc.isim.push_back(idsim);
    for (auto& [idsim, vc] : mapPEMC) for (auto& c : vc) for (auto& myc : ev->clusters) if (myc.index == c.getObjectID().index && myc.collectionID == c.getObjectID().collectionID) myc.isim.push_back(idsim);
    //for (auto& c : ev->clusters) c.type = ev->sim[c.isim].type;

    for (auto& [idsim, vc] : mapBHCal) for (auto& c : vc) for (auto& myc : ev->clusters_HCal) if (myc.index == c.getObjectID().index && myc.collectionID == c.getObjectID().collectionID) myc.isim.push_back(idsim);
    for (auto& [idsim, vc] : mapNHCal) for (auto& c : vc) for (auto& myc : ev->clusters_HCal) if (myc.index == c.getObjectID().index && myc.collectionID == c.getObjectID().collectionID) myc.isim.push_back(idsim);
    for (auto& [idsim, vc] : mapPHCal) for (auto& c : vc) for (auto& myc : ev->clusters_HCal) if (myc.index == c.getObjectID().index && myc.collectionID == c.getObjectID().collectionID) myc.isim.push_back(idsim);
    //for (auto& c : ev->clusters_HCal) c.type = ev->sim[c.isim].type;

    // ReconstructedChargedParticle
    ev->rec.clear();
    for (const auto& par : particles_rec)
    {
        int objectID = par.getObjectID().index;
        auto& rec = ev->rec[objectID];
        //rec.obj = par;
        rec.collectionID = par.getObjectID().collectionID;
        rec.index = par.getObjectID().index;

        // Just some parameters
        rec.p = TVector3(par.getMomentum().x, par.getMomentum().y, par.getMomentum().z);
        rec.ene = 0; // comes from clustering later
        rec.charge = par.getCharge();
        rec.pdg = par.getPDG();
        rec.ref = TVector3(par.getReferencePoint().x, par.getReferencePoint().y, par.getReferencePoint().z);
        if (par.tracks_size() > 0) rec.vtx = TVector3(par.getTracks()[0].getPosition().x, par.getTracks()[0].getPosition().y, par.getTracks()[0].getPosition().z);

        // Categorize track based on last hit information
        if (par.tracks_size() > 0)
        {
            const auto& trk = par.getTracks()[0];
            rec.nhits = trk.measurements_size();
            for (const auto& meas : trk.getMeasurements())
            {
                auto id = meas.getSurface();
                bool found = false;
                unsigned int det = (id >> 0) & 0xFF;

                if (find(TRACK_HIT_BARREL_DETECTOR_IDS.begin(), TRACK_HIT_BARREL_DETECTOR_IDS.end(), det) != TRACK_HIT_BARREL_DETECTOR_IDS.end()) {rec.is_track_b = true; found = true;}
                if (find(TRACK_HIT_NEGATIVE_DETECTOR_IDS.begin(), TRACK_HIT_NEGATIVE_DETECTOR_IDS.end(), det) != TRACK_HIT_NEGATIVE_DETECTOR_IDS.end()) {rec.is_track_n = true; found = true;}
                if (find(TRACK_HIT_POSITIVE_DETECTOR_IDS.begin(), TRACK_HIT_POSITIVE_DETECTOR_IDS.end(), det) != TRACK_HIT_POSITIVE_DETECTOR_IDS.end()) {rec.is_track_p = true; found = true;}
                if (find(TRACK_HIT_TAGGER_DETECTOR_IDS.begin(), TRACK_HIT_TAGGER_DETECTOR_IDS.end(), det) != TRACK_HIT_TAGGER_DETECTOR_IDS.end()) {rec.is_track_t = true; found = true;}

                if (found)
                {
                    if (meas.hits_size() != meas.weights_size()) {cout << "Something Wrong, FILE: " << __FILE__ << " LINE: " << __LINE__ << endl; break;}
                    float wsum = 0;
                    rec.pos_outer = TVector3(0,0,0);
                    for (int i = 0; i < meas.hits_size(); ++i)
                    {
                        const auto& hit = meas.getHits()[i];
                        float w = meas.getWeights()[i];
                        wsum += w;
                        TVector3 pos(hit.getPosition().x, hit.getPosition().y, hit.getPosition().z);
                        rec.pos_outer = rec.pos_outer + w * pos;
                    }
                    rec.pos_outer = 1.0 / wsum * rec.pos_outer;
                }
                if (found) break;
            }

            unsigned int idtrk = trk.getObjectID().index;
            if (mapTrackPoint.count(idtrk)) for (auto& tp : mapTrackPoint.at(idtrk))
            {
                TVector3 pos(tp.position.x, tp.position.y, tp.position.z);
                bool found_ECal = false;
                bool found_HCal = false;
                if (rec.is_track_b) if (tp.system == BEMC_SYSTEM_ID && tp.surface == 2) found_ECal = true;
                if (rec.is_track_n) if (tp.system == NEMC_SYSTEM_ID && tp.surface == 2) found_ECal = true;
                if (rec.is_track_p) if (tp.system == PEMC_SYSTEM_ID && tp.surface == 2) found_ECal = true;

                if (rec.is_track_b) if (tp.system == BHCAL_SYSTEM_ID && tp.surface == 2) found_HCal = true;
                if (rec.is_track_n) if (tp.system == NHCAL_SYSTEM_ID && tp.surface == 2) found_HCal = true;
                if (rec.is_track_p) if (tp.system == PHCAL_SYSTEM_ID && tp.surface == 2) found_HCal = true;

                if (found_ECal) rec.pos_ECal = pos;
                if (found_HCal) rec.pos_HCal = pos;
            }
        }

        // Truth match to clusters
        rec.isim.clear();
        rec.clusters.clear();
        rec.clusters_HCal.clear();
        // Truth matching to generated particles
        if (mapGen.count(objectID)) for (const auto& sim : mapGen.at(objectID))
        {
            rec.isim.push_back(sim.getObjectID().index); // store gen particle id
            if (rec.type != REC_TYPE_SIGNAL) rec.type = status2type(sim.getGeneratorStatus()); // if it's a signal, it's a signal
        }
        // Track-cluster matching
        if (rec.type != REC_TYPE_SYNRAD) // if the track is not a fake track from SR, do truth-matching
        {
            for (auto& idsim : rec.isim)
            {
                for (auto& c : ev->clusters) for (auto& isim : c.isim) if (isim == idsim) {rec.clusters.push_back(&c); rec.clusters.back()->irec.push_back(objectID);}
                for (auto& c : ev->clusters_HCal) for (auto& isim : c.isim) if (isim == idsim) {rec.clusters_HCal.push_back(&c); rec.clusters_HCal.back()->irec.push_back(objectID);}
            }
            // Find high cluster
            for (auto& c : rec.clusters) if (!rec.cluster || rec.cluster->ene < c->ene) {rec.cluster = c; rec.ene = c->ene;}
            for (auto& c : rec.clusters_HCal) if (!rec.cluster_HCal || rec.cluster_HCal->ene < c->ene) rec.cluster_HCal = c;
        }
        // Near cluster matching
        if (rec.pos_ECal.Mag() != 0) for (auto& c : ev->clusters) if (rec.cluster_near == nullptr || rec.cluster_near->pos.DeltaR(rec.pos_ECal) > c.pos.DeltaR(rec.pos_ECal)) rec.cluster_near = &c;
        //if (rec.pos_ECal.Mag() != 0 && rec.clusters.size() > 0) cout << setw(15) << "rec_type =" << setw(15) << rec.type << setw(15) << "dR_high = " << setw(15) << rec.pos_ECal.DeltaR(rec.cluster->pos) << setw(15) << "dR_near = " << setw(15) << rec.pos_ECal.DeltaR(rec.cluster_near->pos) << endl;


        if (rec.pos_ECal.Mag() == 0 && !rec.is_track_t) cout << "No projection to ECal with type " << rec.type << endl;
        if (rec.clusters.size() > 0 && rec.cluster == nullptr) cout << "Something Wrong with cluster matching algorithm!!! FILE: " << __FILE__ << ", LINE: " << __LINE__ << endl;
        if (rec.clusters.size() == 0 && rec.cluster != nullptr) cout << "Something Wrong with cluster matching algorithm!!! FILE: " << __FILE__ << ", LINE: " << __LINE__ << endl;
        if (rec.clusters_HCal.size() > 0 && rec.cluster_HCal == nullptr) cout << "Something Wrong with cluster matching algorithm!!! FILE: " << __FILE__ << ", LINE: " << __LINE__ << endl;
        if (rec.clusters_HCal.size() == 0 && rec.cluster_HCal != nullptr) cout << "Something Wrong with cluster matching algorithm!!! FILE: " << __FILE__ << ", LINE: " << __LINE__ << endl;

        // Assign bitmask based on the tracker and calorimeter
        rec.bitmask = generate_bitmask(rec.is_track_b, rec.is_track_n, rec.is_track_p, rec.is_track_t, rec.is_cluster_b, rec.is_cluster_n, rec.is_cluster_p);
    }

    // Find Particle based on Truth
    for (auto& [key, sim] : ev->sim) if (sim.pdg == cuts.PDG_Lepton && sim.status == 1) {ev->eletrue = &sim; ev->peletrue = sim.p; break;}
    for (auto& [key, sim] : ev->sim) if (sim.pdg == 11 && sim.status == 4) {ev->beam = &sim; ev->pbeam = sim.p; break;}
    for (auto& [key, sim] : ev->sim) if (sim.pdg == 0 && sim.status == 1) {ev->alp = &sim; ev->palp = sim.p; break;}
    if (ev->alp == nullptr) for (auto& [key, sim] : ev->sim) if (sim.pdg == 0 && sim.status == 2) {ev->alp = &sim; ev->palp = sim.p; break;}
    for (auto& [key, rec] : ev->rec)
    {
        auto& sim = ev->sim[rec.isim[0]];
        if (sim.pdg == cuts.PDG_Lepton && sim.status == 1 && rec.type == REC_TYPE_SIGNAL) {ev->ele = &rec; ev->pele = rec.p; break;}
    }
    if (ev->eletrue == nullptr || ev->beam == nullptr) cout << "Whatt????? FILE: " << __FILE__ << " LINE: " << __LINE__ << endl;


    return true;
}


// *****************************************************************************
map<unsigned int, vector<edm4hep::MCParticle>> gen_mapping(const edm4eic::MCRecoParticleAssociationCollection& associations)
{
    map<unsigned int, vector<edm4hep::MCParticle>> outmap;
    for (const auto& asso : associations) outmap[asso.getRec().getObjectID().index].push_back(asso.getSim());
    return outmap;
}

map<unsigned int, vector<edm4eic::ReconstructedParticle>> rec_mapping(const edm4eic::MCRecoParticleAssociationCollection& associations)
{
    map<unsigned int, vector<edm4eic::ReconstructedParticle>> outmap;
    for (const auto& asso : associations) outmap[asso.getSim().getObjectID().index].push_back(asso.getRec());
    return outmap;
}


map<unsigned int, vector<edm4eic::Track>> track_mapping(const edm4eic::MCRecoTrackParticleAssociationCollection& associations)
{
    map<unsigned int, vector<edm4eic::Track>> outmap;
    for (const auto& asso : associations) outmap[asso.getSim().getObjectID().index].push_back(asso.getRec());
    return outmap;
}

map<unsigned int, vector<edm4eic::Cluster>> cluster_mapping(const edm4eic::MCRecoClusterParticleAssociationCollection& associations)
{
    map<unsigned int, vector<edm4eic::Cluster>> outmap;
    for (const auto& asso : associations) outmap[asso.getSim().getObjectID().index].push_back(asso.getRec());
    return outmap;
}


map<unsigned int, vector<edm4eic::TrackPoint>> trackpoint_mapping(const edm4eic::TrackSegmentCollection& projections)
{
    map<unsigned int, vector<edm4eic::TrackPoint>> outmap;
    for (const auto& proj : projections) for (const auto& tp : proj.getPoints()) outmap[proj.getTrack().getObjectID().index].push_back(tp);
    return outmap;
}
// *****************************************************************************

MyCluster convert_cluster(edm4eic::Cluster c, MySelectionCriteria& cuts, bool is_ECal, int type)
{
    MyCluster cc;

    //cc.obj = c;
    cc.collectionID = c.getObjectID().collectionID;
    cc.index = c.getObjectID().index;
    cc.is_ECal = is_ECal;
    cc.is_HCal = !is_ECal;
    cc.is_b = false; cc.is_n = false; cc.is_p = false;
    if (type == 0) cc.is_b = true;
    if (type == 1) cc.is_n = true;
    if (type == 2) cc.is_p = true;

    cc.ene = c.getEnergy();
    cc.pos = TVector3(c.getPosition().x, c.getPosition().y, c.getPosition().z);

    if (is_ECal) if (cc.ene > cuts.Min_ECal_Cluster_E) cc.isgood = true;
    if (!is_ECal) if (cc.ene > cuts.Min_HCal_Cluster_E) cc.isgood = true;

    return cc;
}


unsigned int generate_bitmask(bool is_track_b, bool is_track_n, bool is_track_p, bool is_track_t, bool is_cluster_b, bool is_cluster_n, bool is_cluster_p)
{
    unsigned int bitmask = 0;
    if (is_track_b) bitmask |= (1 << 0);
    if (is_track_n) bitmask |= (1 << 1);
    if (is_track_p) bitmask |= (1 << 2);
    if (is_cluster_b) bitmask |= (1 << 3);
    if (is_cluster_n) bitmask |= (1 << 4);
    if (is_cluster_p) bitmask |= (1 << 5);
    if (is_track_t) bitmask |= (1 << 6);
    return bitmask;
}


int status2type(int status)
{
    if (int(status / 1000) < 2) return REC_TYPE_SIGNAL;
    if (int(status / 1000) == 2) return REC_TYPE_SYNRAD;
    if (int(status / 1000) == 3) return REC_TYPE_BREMSS;
    if (int(status / 1000) == 4) return REC_TYPE_TOUSCH;
    if (int(status / 1000) == 5) return REC_TYPE_COULOM;
    return 0;
}
