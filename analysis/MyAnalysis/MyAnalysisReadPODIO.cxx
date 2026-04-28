#include <edm4hep/MCParticleCollection.h>

#include <edm4eic/TrackCollection.h>
#include <edm4eic/ClusterCollection.h>
#include <edm4eic/ReconstructedParticleCollection.h>
#include <edm4eic/MCRecoParticleAssociationCollection.h>
#include <edm4eic/MCRecoTrackParticleAssociationCollection.h>

#include <edm4hep/utils/kinematics.h>

#include "MyAnalysis.h"

// *****************************************************************************
map<unsigned int, vector<edm4eic::Track>> track_mapping(const edm4eic::MCRecoTrackParticleAssociationCollection& associations);
map<unsigned int, vector<edm4eic::TrackPoint>> trackpoint_mapping(const edm4eic::TrackSegmentCollection& projections);
map<unsigned int, vector<edm4eic::Cluster>> cluster_mapping(const edm4eic::MCRecoClusterParticleAssociationCollection& associations);

// *****************************************************************************
bool MyAnalysis::ReadPODIO()
{
    auto& particles_sim = frame.get<edm4hep::MCParticleCollection>("MCParticles");
    auto& particles_rec = frame.get<edm4eic::ReconstructedParticleCollection>("ReconstructedChargedParticles");

    auto collectionID_CKF = frame.get<edm4eic::TrackCollection>("CentralCKFTracks").getID();
    auto collectionID_TM1 = frame.get<edm4eic::TrackCollection>("TaggerTrackerM1LocalTrackAssociations").getID();
    auto collectionID_TM2 = frame.get<edm4eic::TrackCollection>("TaggerTrackerM2LocalTrackAssociations").getID();

    auto& associations = frame.get<edm4eic::MCRecoParticleAssociationCollection>("ReconstructedChargedParticleAssociations");

    auto& clusters_BEMC = frame.get<edm4eic::ClusterCollection>("EcalBarrelClusters");
    auto& clusters_NEMC = frame.get<edm4eic::ClusterCollection>("EcalEndcapNClusters");
    auto& clusters_PEMC = frame.get<edm4eic::ClusterCollection>("EcalEndcapPClusters");

    auto& clusters_BHCal = frame.get<edm4eic::ClusterCollection>("HcalBarrelClusters");
    auto& clusters_NHCal = frame.get<edm4eic::ClusterCollection>("HcalEndcapNClusters");
    auto& clusters_PHCal = frame.get<edm4eic::ClusterCollection>("LFHCALClusters");

    // Temporarily keeping two different copies of cluster collection ID for ev->Print()...
    // Don't wanna do friends...
    ev->collectionID_BEMC = clusters_BEMC.getID();
    ev->collectionID_NEMC = clusters_NEMC.getID();
    ev->collectionID_PEMC = clusters_PEMC.getID();
    collectionID_BEMC = clusters_BEMC.getID();
    collectionID_NEMC = clusters_NEMC.getID();
    collectionID_PEMC = clusters_PEMC.getID();

    ev->collectionID_BHCal = clusters_BHCal.getID();
    ev->collectionID_NHCal = clusters_NHCal.getID();
    ev->collectionID_PHCal = clusters_PHCal.getID();
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
            if (par.rec.getTracks(i).getObjectID().collectionID == collectionID_CKF) par.track = par.rec.getTracks(i);
            auto idtrk = par.track.getObjectID().index;
            if (mapTrackPoint.count(idtrk))
            {
                par.projection.clear();
                const auto& points = mapTrackPoint[idtrk];
                par.projection.insert(par.projection.end(),points.begin(),points.end());
            }

            par.tracks.push_back(par.rec.getTracks(i));
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


    return true;
}

// *****************************************************************************
map<unsigned int, vector<edm4eic::Track>> track_mapping(const edm4eic::MCRecoTrackParticleAssociationCollection& associations)
{
    map<unsigned int, vector<edm4eic::Track>> trackmap;
    for (const auto& asso : associations) trackmap[asso.getSim().getObjectID().index].push_back(asso.getRec());
    return trackmap;
}

map<unsigned int, vector<edm4eic::TrackPoint>> trackpoint_mapping(const edm4eic::TrackSegmentCollection& projections)
{
    std::map<unsigned int, vector<edm4eic::TrackPoint>> tpmap;
    for (const auto& proj : projections) for (const auto& tp : proj.getPoints()) tpmap[proj.getTrack().getObjectID().index].push_back(tp);
    return tpmap;
}

// *****************************************************************************
map<unsigned int, vector<edm4eic::Cluster>> cluster_mapping(const edm4eic::MCRecoClusterParticleAssociationCollection& associations)
{
    map<unsigned int, vector<edm4eic::Cluster>> clustermap;
    for (const auto& asso : associations) clustermap[asso.getSim().getObjectID().index].push_back(asso.getRec());
    return clustermap;
}
