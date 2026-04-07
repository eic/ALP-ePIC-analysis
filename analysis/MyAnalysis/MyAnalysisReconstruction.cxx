#include "MyAnalysis.h"

#include "TVector3.h"

#include "edm4eic/ReconstructedParticle.h"


// *****************************************************************************
bool MyAnalysis::TrackClusterMatching()
{
    if (ev->particles.size() == 0) return false;

    for (auto& par : ev->particles)
    {
        if (par.tracks.size() == 0 || par.clusters.size() == 0 || par.points.size() == 0) continue;

        edm4eic::ReconstructedParticle& rec = par.rec;
        // Find highest pT track associated with electron
        // -> But this is not possible for samples produced before Mar 2026...
        // -> Just take the reconstructed particle momentum
        // -> For track projection..., take the first track since most (if not all?) reconstructedparticles only have 1 track
        vector<edm4eic::TrackPoint>& pts = par.points[0];
        if (pts.size() == 0) return false;

        // One simulated electron can create clusters in more than one calorimeters.
        // In order to make life easier, only consider events where the electron hits one and only one calorimeter.
        for (int i = 0; i < par.clusters.size(); ++i) if (par.clusters[i].getObjectID().collectionID != par.clusters[0].getObjectID().collectionID) continue;

        // Find highest E cluster
        TVector3 pos_high(0,0,0);
        float ene_high = 0;
        for (auto c : par.clusters)
        {
            if (c.getEnergy() > ene_high)
            {
                ene_high = c.getEnergy();
                pos_high.SetXYZ(c.getPosition().x, c.getPosition().y, c.getPosition().z);
                par.cluster_high = c;
            }
        }

        // Find Cluster of cluster (Cluster sum)
        for (auto c : par.clusters)
        {
            if (c.getObjectID().collectionID != par.cluster_high.getObjectID().collectionID) continue;
            par.pos_cluster_sum += c.getEnergy() * TVector3(c.getPosition().x, c.getPosition().y, c.getPosition().z);
            par.ene_cluster_sum += c.getEnergy();
        }
        par.pos_cluster_sum = (1.0 / par.ene_cluster_sum) * par.pos_cluster_sum;

        // Find Track point associated with the corresponding calorimeter
        bool found_track_pos = false;
        for (auto pt : pts)
        {
            TVector3 pos(pt.position.x, pt.position.y, pt.position.z);
            int type = -1; // 0 = BEMC, 1 = NEMC, 2 = PEMC
            float x = 0; // Expected track point depth
            if (par.cluster_high.getObjectID().collectionID == collectionID_BEMC) {x = 875; type = 0;}
            if (par.cluster_high.getObjectID().collectionID == collectionID_NEMC) {x = -1800; type = 1;}
            if (par.cluster_high.getObjectID().collectionID == collectionID_PEMC) {x = 3400; type = 2;}

            if (type == 0 && abs(pos.Perp() - x) < 1.0) found_track_pos = true;
            if (type != 0 && abs(pos.Z() - x) < 1.0) found_track_pos = true;

            if (found_track_pos) {par.pos_track = pos; break;}
        }

        if (found_track_pos) ev->nmatches++;
    }

    return true;
}
