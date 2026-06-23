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

MyCluster convert_cluster(edm4eic::Cluster c, bool is_ECal, int type);

// *****************************************************************************
bool MyAnalysis::ReadPODIO()
{
    auto& particles_sim = frame.get<edm4hep::MCParticleCollection>("MCParticles");
    auto& particles_rec = frame.get<edm4eic::ReconstructedParticleCollection>("ReconstructedChargedParticles");

    collectionID_CKF = frame.get<edm4eic::TrackCollection>("CentralCKFTracks").getID();
    collectionID_TaggerM1 = frame.get<edm4eic::TrackCollection>("TaggerTrackerM1LocalTrackAssociations").getID();
    collectionID_TaggerM2 = frame.get<edm4eic::TrackCollection>("TaggerTrackerM2LocalTrackAssociations").getID();

    auto& associations = frame.get<edm4eic::MCRecoParticleAssociationCollection>("ReconstructedChargedParticleAssociations");

    auto mapGen = gen_mapping(associations);
    auto mapRec = rec_mapping(associations);

    auto& clusters_BEMC = frame.get<edm4eic::ClusterCollection>("EcalBarrelClusters");
    auto& clusters_NEMC = frame.get<edm4eic::ClusterCollection>("EcalEndcapNClusters");
    auto& clusters_PEMC = frame.get<edm4eic::ClusterCollection>("EcalEndcapPClusters");

    auto& clusters_BHCal = frame.get<edm4eic::ClusterCollection>("HcalBarrelClusters");
    auto& clusters_NHCal = frame.get<edm4eic::ClusterCollection>("HcalEndcapNClusters");
    auto& clusters_PHCal = frame.get<edm4eic::ClusterCollection>("LFHCALClusters");

    collectionID_BEMC = clusters_BEMC.getID();
    collectionID_NEMC = clusters_NEMC.getID();
    collectionID_PEMC = clusters_PEMC.getID();

    collectionID_BHCal = clusters_BHCal.getID();
    collectionID_NHCal = clusters_NHCal.getID();
    collectionID_PHCal = clusters_PHCal.getID();

    auto mapTaggerTrackM1 = track_mapping(frame.get<edm4eic::MCRecoTrackParticleAssociationCollection>("TaggerTrackerM1LocalTrackAssociations"));
    auto mapTaggerTrackM2 = track_mapping(frame.get<edm4eic::MCRecoTrackParticleAssociationCollection>("TaggerTrackerM2LocalTrackAssociations"));

    auto mapTrackPoint = trackpoint_mapping(frame.get<edm4eic::TrackSegmentCollection>("CalorimeterTrackProjections"));
    auto mapBEMC = cluster_mapping(frame.get<edm4eic::MCRecoClusterParticleAssociationCollection>("EcalBarrelClusterAssociations"));
    auto mapNEMC = cluster_mapping(frame.get<edm4eic::MCRecoClusterParticleAssociationCollection>("EcalEndcapNClusterAssociations"));
    auto mapPEMC = cluster_mapping(frame.get<edm4eic::MCRecoClusterParticleAssociationCollection>("EcalEndcapPClusterAssociations"));

    auto mapBHCal = cluster_mapping(frame.get<edm4eic::MCRecoClusterParticleAssociationCollection>("HcalBarrelClusterAssociations"));
    auto mapNHCal = cluster_mapping(frame.get<edm4eic::MCRecoClusterParticleAssociationCollection>("HcalEndcapNClusterAssociations"));
    auto mapPHCal = cluster_mapping(frame.get<edm4eic::MCRecoClusterParticleAssociationCollection>("LFHCALClusterAssociations"));

    // MC Particles loop
    for (auto par : particles_sim) ev->particles_sim.push_back(par);

    // Reconstructed Particles loop
    for (auto par : particles_rec) ev->particles_rec.push_back(par);

    for (auto cluster : clusters_BEMC) ev->clusters.push_back(cluster);
    for (auto cluster : clusters_NEMC) ev->clusters.push_back(cluster);
    for (auto cluster : clusters_PEMC) ev->clusters.push_back(cluster);

    for (auto cluster : clusters_BHCal) ev->hclusters.push_back(cluster);
    for (auto cluster : clusters_NHCal) ev->hclusters.push_back(cluster);
    for (auto cluster : clusters_PHCal) ev->hclusters.push_back(cluster);

    // Association Loop
    for (auto asso : associations)
    {
        MyParticle par;
        par.sim = asso.getSim();
        par.rec = asso.getRec();
        unsigned int idsim = par.sim.getObjectID().index;
        //unsigned int idrec = par.rec.getObjectID().index;

        // Fill Track info
        for (unsigned int i = 0; i < par.rec.tracks_size(); ++i)
        {
            auto trk = par.rec.getTracks(i);
            auto idtrk = trk.getObjectID().index;
            if (trk.getObjectID().collectionID == collectionID_CKF)
            {
                par.track = trk;
                par.nhits = trk.measurements_size();

                if (mapTrackPoint.count(idtrk))
                {
                    par.projection.clear();
                    par.projection.insert(par.projection.end(),mapTrackPoint[idtrk].begin(),mapTrackPoint[idtrk].end());
                }
            }

            par.tracks.push_back(trk);
            par.points.push_back({});
            if (mapTrackPoint.count(idtrk))
            {
                const auto& points = mapTrackPoint[idtrk];
                par.points[i].insert(par.points[i].end(),points.begin(),points.end());
            }
        }

        // Fill low-Q2 tagger track info
        par.tracks_tagger.clear();
        if (mapTaggerTrackM1.count(idsim)) par.tracks_tagger.insert(par.tracks_tagger.end(), mapTaggerTrackM1.at(idsim).begin(), mapTaggerTrackM1.at(idsim).end());
        if (mapTaggerTrackM2.count(idsim)) par.tracks_tagger.insert(par.tracks_tagger.end(), mapTaggerTrackM2.at(idsim).begin(), mapTaggerTrackM2.at(idsim).end());

        // Fill Cluster info
        par.clusters.clear();
        if (mapBEMC.count(idsim)) par.clusters.insert(par.clusters.end(), mapBEMC.at(idsim).begin(), mapBEMC.at(idsim).end());
        if (mapNEMC.count(idsim)) par.clusters.insert(par.clusters.end(), mapNEMC.at(idsim).begin(), mapNEMC.at(idsim).end());
        if (mapPEMC.count(idsim)) par.clusters.insert(par.clusters.end(), mapPEMC.at(idsim).begin(), mapPEMC.at(idsim).end());

        par.hclusters.clear();
        if (mapBHCal.count(idsim)) par.hclusters.insert(par.hclusters.end(), mapBHCal.at(idsim).begin(), mapBHCal.at(idsim).end());
        if (mapNHCal.count(idsim)) par.hclusters.insert(par.hclusters.end(), mapNHCal.at(idsim).begin(), mapNHCal.at(idsim).end());
        if (mapPHCal.count(idsim)) par.hclusters.insert(par.hclusters.end(), mapPHCal.at(idsim).begin(), mapPHCal.at(idsim).end());

        // Fill Event
        ev->particles.push_back(par);
    }



    // New
    // Parse simulated particles
    ev->sim.clear();
    //ev->sim.reserve(particles_sim.size());
    for (const auto& par : particles_sim)
    {
        int objectID = par.getObjectID().index;
        auto& sim = ev->sim[objectID];
        sim.obj = par; // Also store the PODIO obj

        sim.p = TVector3(par.getMomentum().x, par.getMomentum().y, par.getMomentum().z);
        sim.ene = par.getEnergy();
        sim.pdg = par.getPDG();
        sim.vtx = TVector3(par.getVertex().x, par.getVertex().y, par.getVertex().z);

        sim.status = par.getGeneratorStatus();
        sim.irec.clear();
        if (mapRec.count(objectID)) for (const auto& rec : mapRec.at(objectID)) sim.irec.push_back(rec.getObjectID().index);
    }

    // Parse reconstructed particles
    ev->rec.clear();
    //ev->rec.reserve(particles_rec.size());
    for (const auto& par : particles_rec)
    {
        int objectID = par.getObjectID().index;
        auto& rec = ev->rec[objectID];
        rec.obj = par;

        rec.p = TVector3(par.getMomentum().x, par.getMomentum().y, par.getMomentum().z);
        rec.ene = 0; // comes from clustering later
        rec.pdg = par.getPDG();
        rec.ref = TVector3(par.getReferencePoint().x, par.getReferencePoint().y, par.getReferencePoint().z);
        if (par.tracks_size() > 0) rec.pos = TVector3(par.getTracks()[0].getPosition().x, par.getTracks()[0].getPosition().y, par.getTracks()[0].getPosition().z);

        // grab track last hit information
        if (par.tracks_size() > 0)
        {
            const auto& trk = par.getTracks()[0];
            rec.nhits = trk.measurements_size();
            for (const auto& hit : trk.getMeasurements())
            {
                auto id = hit.getSurface();
                unsigned int det = (id >> 0) & 0xFF;

                if (find(TRACK_HIT_BARREL_DETECTOR_IDS.begin(), TRACK_HIT_BARREL_DETECTOR_IDS.end(), det) != TRACK_HIT_BARREL_DETECTOR_IDS.end()) {rec.is_track_b = true; break;}
                if (find(TRACK_HIT_NEGATIVE_DETECTOR_IDS.begin(), TRACK_HIT_NEGATIVE_DETECTOR_IDS.end(), det) != TRACK_HIT_NEGATIVE_DETECTOR_IDS.end()) {rec.is_track_n = true; break;}
                if (find(TRACK_HIT_POSITIVE_DETECTOR_IDS.begin(), TRACK_HIT_POSITIVE_DETECTOR_IDS.end(), det) != TRACK_HIT_POSITIVE_DETECTOR_IDS.end()) {rec.is_track_p = true; break;}
                if (find(TRACK_HIT_TAGGER_DETECTOR_IDS.begin(), TRACK_HIT_TAGGER_DETECTOR_IDS.end(), det) != TRACK_HIT_TAGGER_DETECTOR_IDS.end()) {rec.is_track_tagger = true; break;}
            }
        }

        rec.isim.clear();
        rec.clusters.clear();
        rec.clusters_HCal.clear();
        if (mapGen.count(objectID))
        {
            for (const auto& sim : mapGen.at(objectID))
            {
                int idsim = sim.getObjectID().index;
                rec.isim.push_back(idsim); // store gen particle id

                // Truth matching to cluster
                if (mapBEMC.count(idsim)) for (const auto& c : mapBEMC[idsim]) rec.clusters.push_back(convert_cluster(c, 1, 0));
                if (mapNEMC.count(idsim)) for (const auto& c : mapNEMC[idsim]) rec.clusters.push_back(convert_cluster(c, 1, 1));
                if (mapPEMC.count(idsim)) for (const auto& c : mapPEMC[idsim]) rec.clusters.push_back(convert_cluster(c, 1, 2));
                if (mapBHCal.count(idsim)) for (const auto& c : mapBHCal[idsim]) rec.clusters_HCal.push_back(convert_cluster(c, 0, 0));
                if (mapNHCal.count(idsim)) for (const auto& c : mapNHCal[idsim]) rec.clusters_HCal.push_back(convert_cluster(c, 0, 1));
                if (mapPHCal.count(idsim)) for (const auto& c : mapPHCal[idsim]) rec.clusters_HCal.push_back(convert_cluster(c, 0, 2));

                // Truth matching to anything done below
                // ...

            }
        }

        for (auto& c : rec.clusters) if (!rec.cluster || rec.cluster->ene < c.ene) rec.cluster = &c;
        for (auto& c : rec.clusters_HCal) if (!rec.cluster_HCal || rec.cluster_HCal->ene < c.ene) rec.cluster_HCal = &c;

        rec.type = 0;
        for (auto& idsim : rec.isim)
        {
            auto& sim = ev->sim[idsim];
            if (sim.obj.getGeneratorStatus() == 1) rec.type = REC_TYPE_SIGNAL;
            if (sim.obj.getGeneratorStatus() == 2001) rec.type = REC_TYPE_SYNRAD;
            if (sim.obj.getGeneratorStatus() == 3001) rec.type = REC_TYPE_BREMSS;
            if (sim.obj.getGeneratorStatus() == 4001) rec.type = REC_TYPE_TOUSCH;
            if (sim.obj.getGeneratorStatus() == 5001) rec.type = REC_TYPE_COULOM;
            if (rec.type != 0) break;
        }

    }

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

MyCluster convert_cluster(edm4eic::Cluster c, bool is_ECal, int type)
{
    MyCluster cc;

    cc.obj = c;
    cc.is_ECal = is_ECal;
    cc.is_HCal = !is_ECal;
    if (type == 0) cc.is_b = true;
    if (type == 1) cc.is_n = true;
    if (type == 2) cc.is_p = true;

    cc.ene = c.getEnergy();
    cc.pos = TVector3(c.getPosition().x, c.getPosition().y, c.getPosition().z);

    return cc;
}
