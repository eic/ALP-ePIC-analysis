#include "MyAnalysis.h"

#include <algorithm>

#include "TVector3.h"

#include "edm4eic/ReconstructedParticle.h"

int generate_bitmask(bool is_track_b, bool is_track_n, bool is_track_p, bool is_track_t, bool is_cluster_b, bool is_cluster_n, bool is_cluster_p);



// *****************************************************************************
bool MyAnalysis::FindEventQuantities()
{
    auto ele = ev->GetFinalLepton();
    auto eletrue = ev->GetFinalLeptonTrue();
    auto beam = ev->GetInitialLeptonTrue();
    auto alp = ev->GetALPTrue();

    // Easy ones
    if (ele != edm4eic::ReconstructedParticle::makeEmpty()) ev->pele = TVector3(ele.getMomentum().x,ele.getMomentum().y,ele.getMomentum().z);
    if (eletrue != edm4hep::MCParticle::makeEmpty()) ev->peletrue = TVector3(eletrue.getMomentum().x,eletrue.getMomentum().y,eletrue.getMomentum().z);
    if (beam != edm4hep::MCParticle::makeEmpty()) ev->pbeam = TVector3(beam.getMomentum().x,beam.getMomentum().y,beam.getMomentum().z);
    if (alp != edm4hep::MCParticle::makeEmpty()) ev->palp = TVector3(alp.getMomentum().x,alp.getMomentum().y,alp.getMomentum().z);

    ev->q2 = 2 * ev->pele.Mag() * ev->pbeam.Mag() * (1.0 - cos(ev->pbeam.Theta() - ev->pele.Theta()));
    ev->q2true = 2 * ev->peletrue.Mag() * ev->pbeam.Mag() * (1.0 - cos(ev->pbeam.Theta() - ev->peletrue.Theta()));

    ev->pmisstrue = TVector3(0,0,0);
    for (auto& par : ev->particles_sim) if (par.getGeneratorStatus() == 1 && par.getPDG() != 0)
    {
        TVector3 p(par.getMomentum().x, par.getMomentum().y, par.getMomentum().z);
        ev->pmisstrue = ev->pmisstrue + p;
    }
    //

    // missing momentum
    ev->pmiss = TVector3(0,0,0);
    // tracking component
    for (auto& par : ev->particles_rec)
    {
        TVector3 p(par.getMomentum().x, par.getMomentum().y, par.getMomentum().z);
        // Some cuts?
        ev->pmiss = ev->pmiss + p;
    }
    // clustering component
    for (auto& c : ev->clusters)
    {
        TVector3 p(c.getPosition().x, c.getPosition().y, c.getPosition().z);
        // Projection from primary vertex? primary vertex finding?
        p.SetMag(c.getEnergy());
        // Some cuts?
        bool ismatched = false;
        for (auto& par : ev->particles) for (auto& c2 : par.clusters) if (c2 == c) {ismatched = true; break;}
        if (ismatched) continue;
        ev->pmiss = ev->pmiss + p;
    }

    return true;
}

// *****************************************************************************
bool MyAnalysis::CategorizeEvent()
{
    if (ev->particles.size() == 0) return false;

    for (auto& par : ev->particles)
    {
        const auto& trk = par.track;

        int last_tracker = -1;
        for (const auto& hit : trk.getMeasurements())
        {
            auto id = hit.getSurface();
            uint64_t volume = (id >> 56) & 0xFF;
            uint64_t boundary = (id >> 48) & 0xFF;
            uint64_t layer  = (id >> 36) & 0xFFF;
            uint64_t approach = (id >> 28) & 0xFF;
            uint64_t sensitive = (id >> 8) & 0xFFFFF;
            uint64_t extra = (id >> 0) & 0xFF;
            unsigned int det = extra; // Just so smart

            if (find(TRACK_HIT_BARREL_DETECTOR_IDS.begin(), TRACK_HIT_BARREL_DETECTOR_IDS.end(), det) != TRACK_HIT_BARREL_DETECTOR_IDS.end()) {par.is_track_barrel = true; if (last_tracker == -1) last_tracker = 0;}
            if (find(TRACK_HIT_NEGATIVE_DETECTOR_IDS.begin(), TRACK_HIT_NEGATIVE_DETECTOR_IDS.end(), det) != TRACK_HIT_NEGATIVE_DETECTOR_IDS.end()) {par.is_track_endcap_n = true; if (last_tracker == -1) last_tracker = 1;}
            if (find(TRACK_HIT_POSITIVE_DETECTOR_IDS.begin(), TRACK_HIT_POSITIVE_DETECTOR_IDS.end(), det) != TRACK_HIT_POSITIVE_DETECTOR_IDS.end()) {par.is_track_endcap_p = true; if (last_tracker == -1) last_tracker = 2;}
        }
        if (par.tracks_tagger.size() > 0) par.is_track_tagger = true;

        for (const auto& c : par.clusters)
        {
            if (c.getObjectID().collectionID == collectionID_BEMC) par.is_cluster_barrel = true;
            if (c.getObjectID().collectionID == collectionID_NEMC) par.is_cluster_endcap_n = true;
            if (c.getObjectID().collectionID == collectionID_PEMC) par.is_cluster_endcap_p = true;
        }

        int high_cluster = -1;
        if (par.cluster_high.getObjectID().collectionID == collectionID_BEMC) high_cluster = 0;
        if (par.cluster_high.getObjectID().collectionID == collectionID_NEMC) high_cluster = 1;
        if (par.cluster_high.getObjectID().collectionID == collectionID_PEMC) high_cluster = 2;


        if (par.is_track_barrel) par.bitmask |= (1 << 0);
        if (par.is_track_endcap_n) par.bitmask |= (1 << 1);
        if (par.is_track_endcap_p) par.bitmask |= (1 << 2);
        if (par.is_cluster_barrel) par.bitmask |= (1 << 3);
        if (par.is_cluster_endcap_n) par.bitmask |= (1 << 4);
        if (par.is_cluster_endcap_p) par.bitmask |= (1 << 5);
        if (par.is_track_tagger) par.bitmask |= (1 << 6);

        if (last_tracker == 0) par.bitmask2 |= (1 << 0);
        if (last_tracker == 1) par.bitmask2 |= (1 << 1);
        if (last_tracker == 2) par.bitmask2 |= (1 << 2);
        if (high_cluster == 0) par.bitmask2 |= (1 << 3);
        if (high_cluster == 1) par.bitmask2 |= (1 << 4);
        if (high_cluster == 2) par.bitmask2 |= (1 << 5);
        if (par.is_track_tagger) par.bitmask2 |= (1 << 6);

    }

    return true;
}

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



int generate_bitmask(bool is_track_b, bool is_track_n, bool is_track_p, bool is_track_t, bool is_cluster_b, bool is_cluster_n, bool is_cluster_p)
{
    int bitmask = 0;
    if (is_track_b) bitmask |= (1 << 0);
    if (is_track_n) bitmask |= (1 << 1);
    if (is_track_p) bitmask |= (1 << 2);
    if (is_cluster_b) bitmask |= (1 << 3);
    if (is_cluster_n) bitmask |= (1 << 4);
    if (is_cluster_p) bitmask |= (1 << 5);
    if (is_track_t) bitmask |= (1 << 6);
    return bitmask;
}
