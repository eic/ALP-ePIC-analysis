#include <edm4hep/MCParticleCollection.h>

#include <edm4eic/ClusterCollection.h>
#include <edm4eic/ReconstructedParticleCollection.h>
#include <edm4eic/MCRecoParticleAssociationCollection.h>
#include <edm4eic/MCRecoTrackParticleAssociationCollection.h>

#include <edm4hep/utils/kinematics.h>

#include "MyAnalysis.h"


// *****************************************************************************
bool MyAnalysis::ReadPODIO()
{
    auto& particles_rec = mFrame.get<edm4eic::ReconstructedParticleCollection>("ReconstructedChargedParticles");
    auto& particles_sim = mFrame.get<edm4hep::MCParticleCollection>("MCParticles");
    auto& associations = mFrame.get<edm4eic::MCRecoParticleAssociationCollection>("ReconstructedChargedParticleAssociations");

    auto& clusters_BEMC = mFrame.get<edm4eic::ClusterCollection>("EcalBarrelClusters");
    auto& clusters_NEMC = mFrame.get<edm4eic::ClusterCollection>("EcalEndcapNClusters");
    auto& clusters_PEMC = mFrame.get<edm4eic::ClusterCollection>("EcalEndcapPClusters");

    auto mapTrackPoint = TrackPointMap(mFrame.get<edm4eic::TrackSegmentCollection>("CalorimeterTrackProjections"));
    auto mapBEMC = ClusterMap(mFrame.get<edm4eic::MCRecoClusterParticleAssociationCollection>("EcalBarrelClusterAssociations"));
    auto mapNEMC = ClusterMap(mFrame.get<edm4eic::MCRecoClusterParticleAssociationCollection>("EcalEndcapNClusterAssociations"));
    auto mapPEMC = ClusterMap(mFrame.get<edm4eic::MCRecoClusterParticleAssociationCollection>("EcalEndcapPClusterAssociations"));

    // MC Particles loop
    for (auto par : particles_sim) ev->particles_sim.push_back(par);

    // Reconstructed Particles loop
    for (auto par : particles_rec) ev->particles_rec.push_back(par);

    for (auto cluster : clusters_BEMC) ev->clusters.push_back(cluster);
    for (auto cluster : clusters_NEMC) ev->clusters.push_back(cluster);
    for (auto cluster : clusters_PEMC) ev->clusters.push_back(cluster);

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
            par.tracks.push_back(par.rec.getTracks(i));
            par.points.push_back({});
            unsigned int idtrk = par.tracks[i].getObjectID().index;

            if (mapTrackPoint.count(idtrk))
            {
                const auto& points = mapTrackPoint[idtrk];
                par.points[i].insert(par.points[i].end(),points.begin(),points.end());
            }
        }

        // Fill Cluster info
        if (mapBEMC.count(idsim)) par.clusters_BEMC = mapBEMC.at(idsim);
        if (mapNEMC.count(idsim)) par.clusters_NEMC = mapNEMC.at(idsim);
        if (mapPEMC.count(idsim)) par.clusters_PEMC = mapPEMC.at(idsim);

        // Fill Event
        ev->particles.push_back(par);
    }

    return true;
}

// *****************************************************************************
map<unsigned int, vector<edm4eic::TrackPoint>> MyAnalysis::TrackPointMap(const edm4eic::TrackSegmentCollection& projections)
{
    std::map<unsigned int, vector<edm4eic::TrackPoint>> tpmap;
    for (const auto& proj : projections) for (const auto& tp : proj.getPoints()) tpmap[proj.getTrack().getObjectID().index].push_back(tp);
    return tpmap;
}

// *****************************************************************************
map<unsigned int, vector<edm4eic::Cluster>> MyAnalysis::ClusterMap(const edm4eic::MCRecoClusterParticleAssociationCollection& associations)
{
    map<unsigned int, vector<edm4eic::Cluster>> clustermap;
    for (const auto& asso : associations) clustermap[asso.getSim().getObjectID().index].push_back(asso.getRec());
    return clustermap;
}
