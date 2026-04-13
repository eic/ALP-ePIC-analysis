#include "MyAnalysis.h"

#include "TVector3.h"

#include "edm4eic/ReconstructedParticle.h"

#define BEMC_SYSTEM_ID 101
#define NEMC_SYSTEM_ID 103
#define PEMC_SYSTEM_ID 102

#define BHCAL_SYSTEM_ID 111
#define NHCAL_SYSTEM_ID 113
#define PHCAL_SYSTEM_ID 116

// *****************************************************************************
bool MyAnalysis::TrackClusterMatching()
{
    if (ev->particles.size() == 0) return false;

    for (auto& par : ev->particles)
    {
        // Find most energetic cluster (high cluster)
        // Find Cluster of cluster (Cluster sum)
        if (par.clusters.size() == 0) continue;
        float ene_high = 0;
        for (auto c : par.clusters)
        {
            par.pos_cluster_sum += c.getEnergy() * TVector3(c.getPosition().x, c.getPosition().y, c.getPosition().z);
            par.ene_cluster_sum += c.getEnergy();
            if (ene_high < c.getEnergy()) {ene_high = c.getEnergy(); par.cluster_high = c;}
        }
        par.pos_cluster_sum = (1.0 / par.ene_cluster_sum) * par.pos_cluster_sum;

        // Find the nearest cluster
        if (par.tracks.size() == 0 || par.clusters.size() == 0 || par.projection.size() == 0) continue;

        //edm4eic::ReconstructedParticle& rec = par.rec;
        // Find highest pT track associated with electron
        // -> But this is not possible for samples produced before Mar 2026...
        // -> Just take the reconstructed particle momentum
        // -> For track projection..., take the first track since most (if not all?) reconstructedparticles only have 1 track

        // One simulated electron can create clusters in more than one calorimeters.
        // In order to make life easier, only consider events where the electron hits one and only one calorimeter.
        bool isgood_one_detector = true;
        uint32_t det = 0;
        for (unsigned int i = 0; i < par.clusters.size(); ++i)
        {
            det = par.clusters[i].getObjectID().collectionID;
            if (det != par.clusters[0].getObjectID().collectionID) isgood_one_detector = false;
        }
        if (!isgood_one_detector) continue;

        // Find Track point associated with the corresponding calorimeter
        bool found_track_pos = false;
        for (auto p : par.projection)
        {
            TVector3 pos(p.position.x, p.position.y, p.position.z);
            if (det == collectionID_BEMC) if (p.system == BEMC_SYSTEM_ID && p.surface == 2) found_track_pos = true;
            if (det == collectionID_NEMC) if (p.system == NEMC_SYSTEM_ID && p.surface == 2) found_track_pos = true;
            if (det == collectionID_PEMC) if (p.system == PEMC_SYSTEM_ID && p.surface == 2) found_track_pos = true;

            if (found_track_pos) {par.pos_track = pos; break;}
        }

        // Find nearest E cluster
        float dr_near = 9999999;
        TVector3 pos_near(0,0,0);
        for (auto c : par.clusters)
        {
            TVector3 pos(c.getPosition().x, c.getPosition().y, c.getPosition().z);
            float dr = pos.DeltaR(par.pos_track);
            if (dr < dr_near)
            {
                dr_near = dr;
                pos_near = pos;
                par.cluster_near = c;
            }
        }

        if (found_track_pos && pos_near.Perp() > 0) ev->nmatches++;
    }

    return true;
}

// *****************************************************************************
bool MyAnalysis::TrackHCalClusterMatching()
{
    if (ev->particles.size() == 0) return false;

    for (auto& par : ev->particles)
    {
        // Find most energetic cluster (high cluster)
        // Find Cluster of cluster (Cluster sum)
        if (par.hclusters.size() == 0) continue;
        float ene_high = 0;
        for (auto c : par.hclusters)
        {
            par.pos_hcluster_sum += c.getEnergy() * TVector3(c.getPosition().x, c.getPosition().y, c.getPosition().z);
            par.ene_hcluster_sum += c.getEnergy();
            if (ene_high < c.getEnergy()) {ene_high = c.getEnergy(); par.hcluster_high = c;}
        }
        par.pos_hcluster_sum = (1.0 / par.ene_hcluster_sum) * par.pos_hcluster_sum;


        // Find the nearest cluster
        if (par.tracks.size() == 0 || par.hclusters.size() == 0 || par.projection.size() == 0) continue;

        //edm4eic::ReconstructedParticle& rec = par.rec;
        // Find highest pT track associated with electron
        // -> But this is not possible for samples produced before Mar 2026...
        // -> Just take the reconstructed particle momentum
        // -> For track projection..., take the first track since most (if not all?) reconstructedparticles only have 1 track
        if (par.projection.size() == 0) return false;

        bool isgood_one_detector = true;
        uint32_t det = 0;
        for (unsigned int i = 0; i < par.hclusters.size(); ++i)
        {
            det = par.hclusters[i].getObjectID().collectionID;
            if (det != par.hclusters[0].getObjectID().collectionID) isgood_one_detector = false;
        }
        if (!isgood_one_detector) continue;

        // Find Track point associated with the corresponding calorimeter
        bool found_track_pos = false;
        for (auto p : par.projection)
        {
            TVector3 pos(p.position.x, p.position.y, p.position.z);
            if (det == collectionID_BHCal) if (p.system == BHCAL_SYSTEM_ID && p.surface == 2) found_track_pos = true;
            if (det == collectionID_NHCal) if (p.system == NHCAL_SYSTEM_ID && p.surface == 2) found_track_pos = true;
            if (det == collectionID_PHCal) if (p.system == PHCAL_SYSTEM_ID && p.surface == 2) found_track_pos = true;

            if (found_track_pos) {par.pos_track_hcal = pos; break;}
        }

        // Find nearest E cluster
        float dr_near = 9999999;
        TVector3 pos_near(0,0,0);
        for (auto c : par.hclusters)
        {
            TVector3 pos(c.getPosition().x, c.getPosition().y, c.getPosition().z);
            float dr = pos.DeltaR(par.pos_track_hcal);
            if (dr < dr_near)
            {
                dr_near = dr;
                pos_near = pos;
                par.hcluster_near = c;
            }
        }

        if (found_track_pos && pos_near.Perp() > 0) ev->nmatches_hcal++;
    }

    return true;
}
