#include "MyAnalysis.h"

#include <algorithm>

#include "TVector3.h"

#include "edm4eic/ReconstructedParticle.h"

bool is_matched(MyCluster& c, MyReconstructedParticle& rec);
float find_Enear(MyReconstructedParticle& rec, MyEvent* ev, float drmax);

// *****************************************************************************
// Preselection for event-level quantity reconstruction
bool MyAnalysis::Preselection()
{
    // Truth-level
    for (auto& [key, sim] : ev->sim)
    {
        sim.isgood = true;
        if (sim.status != 1) sim.isgood = false;
        if (sim.pdg == 0) sim.isgood = false;
        if (sim.p.Mag() < cuts.Min_Track_P) sim.isgood = false;
        if (sim.p.Eta() > cuts.Max_Track_Eta || sim.p.Eta() < cuts.Min_Track_Eta) sim.isgood = false;
    }

    // Reconstruction-level
    for (auto& [key, rec] : ev->rec)
    {
        auto& sim = ev->sim[rec.isim[0]];
        if (rec.p.Mag() > cuts.Min_Track_P) rec.isgood_momentum = true;
        if (rec.p.Eta() < cuts.Max_Track_Eta && rec.p.Eta() > cuts.Min_Track_Eta) rec.isgood_eta = true;
        if (!rec.is_track_t) rec.isgood_tracker = true;
        if (rec.vtx.Mag() > 0 && abs(rec.vtx.Z()) < cuts.Max_Vertex_Z && abs(rec.vtx.Perp()) < cuts.Max_Vertex_R) rec.isgood_vtx = true;
        if (rec.nhits >= cuts.Min_Track_Nhits) rec.isgood_nhits = true;

        if (rec.isgood_momentum && rec.isgood_eta && rec.isgood_tracker && rec.isgood_vtx && rec.isgood_nhits) rec.isgood = true;

        if (rec.ene > 0) if (rec.ene / rec.p.Mag() < cuts.Max_Lepton_Ep && rec.ene / rec.p.Mag() > cuts.Min_Lepton_Ep) rec.isgood_Ep = true;
        if (rec.pdg == sim.pdg) rec.isgood_pid = true;
    }

    return true;
}

// *****************************************************************************
bool MyAnalysis::ReconstructEventQuantities()
{
    // Truth
    // Q2
    float s = 4 * ev->pbeam.Mag() * 110; // 110 GeV nucleon
    ev->q2true = 2 * ev->peletrue.Mag() * ev->pbeam.Mag() * (1.0 - cos(ev->peletrue.Theta() - ev->pbeam.Theta()));
    ev->ytrue = 1.0 - ev->peletrue.Mag() / ev->pbeam.Mag();
    ev->xtrue = ev->q2true / (s * ev->ytrue);
    // missing momentum truth
    ev->pmisstrue = TVector3(0,0,0);
    if (ev->alp != nullptr && ev->alp->status == 1) ev->pmisstrue = ev->palp;
    else
    {
        for (auto& [key, par] : ev->sim)
        {
            if (!par.isgood) continue; // Kinematics cut
            ev->pmisstrue = ev->pmisstrue + par.p;
        }
        ev->pmisstrue = -ev->pmisstrue;
    }

    // Reconstruction
    // Track level
    for (auto& [key, rec] : ev->rec)
    {
        rec.Enear_01 = find_Enear(rec, ev, 0.1);
        rec.Enear_03 = find_Enear(rec, ev, 0.3);
        rec.Enear_05 = find_Enear(rec, ev, 0.5);
        rec.Enear_07 = find_Enear(rec, ev, 0.7);
        rec.Enear_09 = find_Enear(rec, ev, 0.9);
    }



    // Event level
    if (ev->ele != nullptr)
    {
        ev->q2 = 2 * ev->pele.Mag() * ev->pbeam.Mag() * (1.0 - cos(ev->pele.Theta() - ev->pbeam.Theta())); // Q2
        ev->y = 1.0 - ev->pele.Mag() / ev->pbeam.Mag();
        ev->x = ev->q2 / (ev->y * s);

        ev->dphi_e_pmiss = ev->pele.DeltaPhi(ev->pmiss);

        ev->dphi_e_near = -1;
        ev->dR_e_near = -1;
        for (auto& [key, rec] : ev->rec)
        {
            if (!ev->ele->isgood) break;
            if (!rec.isgood) continue;
            if (*(ev->ele) == rec) continue;
            if (ev->dR_e_near <= 0 || ev->dR_e_near > ev->pele.DeltaR(rec.p))
            {
                ev->dR_e_near = ev->pele.DeltaR(rec.p);
                ev->dphi_e_near = ev->pele.DeltaPhi(rec.p);
            }
        }
    }

    ev->pmiss = TVector3(0,0,0); // missing momentum reco
    ev->multiplicity = 0; // multiplicity
    ev->empz = 0; // Sigma(E - Pz)
    ev->pTsqrtET = 0; // pT / sqrt(ET)
    float ETsum = 0;
    // Track loop
    for (auto& [key, par] : ev->rec)
    {
        if (!par.isgood) continue;

        ev->pmiss = ev->pmiss + par.p;
        ev->multiplicity++;
        ev->empz += par.p.Mag() * (1.0 - cos(par.p.Theta()));
        ETsum += par.p.Pt();
    }

    // Cluster loop
    TVector3 vp = ev->ele == nullptr ? TVector3(0,0,0) : ev->ele->vtx;
    for (auto& c : ev->clusters)
    {
        if (!c.isgood) continue;
        bool ismatched = false;
        for (auto& [key, par] : ev->rec) {ismatched = is_matched(c, par); if (ismatched) break;}
        if (ismatched) continue;

        TVector3 pc = c.pos - vp;
        pc.SetMag(c.ene);

        ev->pmiss = ev->pmiss + pc;
        ev->empz += pc.Mag() * (1.0 - cos(pc.Theta()));
        ETsum += pc.Pt();
    }
    if (ETsum > 0) ev->pTsqrtET = ev->pmiss.Pt() / sqrt(ETsum);
    ev->pmiss = -ev->pmiss;

    return true;
}


// *****************************************************************************
bool is_matched(MyCluster& c, MyReconstructedParticle& rec)
{
    for (auto& cc : rec.clusters) if (*cc == c) return true;
    return false;
}


float find_Enear(MyReconstructedParticle& rec, MyEvent* ev, float drmax)
{
    float Enear = 0;
    vector<int> irec_used;
    for (auto& [key2, rec2] : ev->rec)
    {
        if (!rec2.isgood) continue;
        if (rec.p.DeltaR(rec2.p) > drmax) continue;
        Enear += rec2.p.Dot(rec.p) / rec.p.Mag();
        irec_used.push_back(key2);
    }

    TVector3 pos_trk = rec.pos_ECal;
    for (auto& c : ev->clusters)
    {
        if (!c.isgood) continue; // only good clusters
        if (c.pos.DeltaR(pos_trk) > drmax) continue; // check the dR condition
        bool found = false; // if it is associated with a track, just get the track, not this cluster
        for (auto& irec : c.irec) for (auto& irec2 : irec_used) if (irec == irec2) {found = true; break;}
        if (found) continue;

        TVector3 pc = c.pos - rec.vtx;
        pc.SetMag(c.ene);

        Enear += pc.Dot(rec.p) / rec.p.Mag();
    }

    return Enear;
}
