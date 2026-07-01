#include "MyAnalysis.h"


// *****************************************************************************
void MyAnalysis::AnalyzeQA()
{
    if (ev->sim.size() > 0) h1["event__stage"]->Fill(0);
    if (ev->rec.size() > 0) h1["event__stage"]->Fill(1);

    if (ev->sim.size() > 0)
    {
        h1["QA_sim__Q2"]->Fill(ev->q2true);
        h1["QA_sim__pe"]->Fill(ev->peletrue.Mag());
        h1["QA_sim__pTmiss"]->Fill(ev->pmisstrue.Pt());
        h1["QA_sim__pTe"]->Fill(ev->peletrue.Pt());
        h1["QA_sim__etae"]->Fill(ev->peletrue.Eta());

        h2["QA_sim__Q2_pTmiss"]->Fill(ev->q2true, ev->pmisstrue.Pt());
        h2["QA_sim__Q2_pTe"]->Fill(ev->q2true, ev->peletrue.Pt());
        h2["QA_sim__Q2_etae"]->Fill(ev->q2true, ev->peletrue.Eta());
        h2["QA_sim__pTmiss_pTe"]->Fill(ev->pmisstrue.Pt(), ev->peletrue.Pt());
        h2["QA_sim__pTmiss_etae"]->Fill(ev->pmisstrue.Pt(), ev->peletrue.Eta());
        h2["QA_sim__etae_pTe"]->Fill(ev->peletrue.Eta(), ev->peletrue.Pt());
        h2["QA_sim__etae_pe"]->Fill(ev->peletrue.Eta(), ev->peletrue.Mag());

        h1["QA_sim_electron__Efrac"]->Fill(ev->peletrue.Mag()/ev->pbeam.Mag());
        h1["QA_sim_ALP__Efrac"]->Fill(ev->palp.Mag()/ev->pbeam.Mag());
    }

    for (auto& [key, rec] : ev->rec)
    {
        auto& sim = ev->sim[rec.isim[0]];
        if (sim.pdg != cuts.PDG_Lepton || sim.status != 1) continue;

        h1["QA_rec__Q2"]->Fill(ev->q2);
        h1["QA_rec__pe"]->Fill(ev->pele.Mag());
        h1["QA_rec__pTmiss"]->Fill(ev->pmiss.Pt());
        h1["QA_rec__pTe"]->Fill(ev->pele.Pt());
        h1["QA_rec__etae"]->Fill(ev->pele.Eta());

        h2["QA_rec__Q2_pTmiss"]->Fill(ev->q2, ev->pmiss.Pt());
        h2["QA_rec__Q2_pTe"]->Fill(ev->q2, ev->pele.Pt());
        h2["QA_rec__Q2_etae"]->Fill(ev->q2, ev->pele.Eta());
        h2["QA_rec__pTmiss_pTe"]->Fill(ev->pmiss.Pt(), ev->pele.Pt());
        h2["QA_rec__pTmiss_etae"]->Fill(ev->pmiss.Pt(), ev->pele.Eta());
        h2["QA_rec__etae_pTe"]->Fill(ev->pele.Eta(), ev->pele.Pt());
        h2["QA_rec__etae_pe"]->Fill(ev->pele.Eta(), ev->pele.Mag());

        break;
    }

    for (auto& [key, rec] : ev->rec)
    {
        auto& sim = ev->sim[rec.isim[0]];

        h2["QA_rec_track__nhits_type"]->Fill(rec.nhits, rec.type);
    }

    for (auto& [key, rec] : ev->rec)
    {
        auto& sim = ev->sim[rec.isim[0]];

        //
        h2["QA_sim__pT_bitmask2"]->Fill(sim.p.Pt(), rec.bitmask);
        h2["QA_sim__p_bitmask2"]->Fill(sim.p.Mag(), rec.bitmask);
        h2["QA_sim__eta_bitmask2"]->Fill(sim.p.Eta(), rec.bitmask);

        //
        h2["QA_rec__nhits_bitmask"]->Fill(rec.nhits, rec.bitmask);
        h2["QA_rec__pT_bitmask"]->Fill(rec.p.Pt(), rec.bitmask);
        h2["QA_rec__p_bitmask"]->Fill(rec.p.Mag(), rec.bitmask);
        h2["QA_rec__eta_bitmask"]->Fill(rec.p.Eta(), rec.bitmask);

        h2["QA_rec__nhits_bitmask2"]->Fill(rec.nhits, rec.bitmask);
        h2["QA_rec__pT_bitmask2"]->Fill(rec.p.Pt(), rec.bitmask);
        h2["QA_rec__p_bitmask2"]->Fill(rec.p.Mag(), rec.bitmask);
        h2["QA_rec__eta_bitmask2"]->Fill(rec.p.Eta(), rec.bitmask);

        if (rec.clusters.size() > 0 && rec.cluster != nullptr)
        {
            h2["QA_rec__E_bitmask"]->Fill(rec.ene, rec.bitmask);
            h2["QA_rec__Ep_bitmask"]->Fill(rec.ene/rec.p.Mag(), rec.bitmask);
            h3["QA_rec__p_Ep_bitmask"]->Fill(rec.p.Mag(), rec.ene/rec.p.Mag(), rec.bitmask);

            h2["QA_rec__E_bitmask2"]->Fill(rec.ene, rec.bitmask);
            h2["QA_rec__Ep_bitmask2"]->Fill(rec.ene/rec.p.Mag(), rec.bitmask);
            h3["QA_rec__p_Ep_bitmask2"]->Fill(rec.p.Mag(), rec.ene/rec.p.Mag(), rec.bitmask);
        }
    }

    for (auto& [key, sim] : ev->sim)
    {
        if (sim.pdg == 0 && sim.status == 2)
        {
            h2["QA_sim_ALP__eta_pT"]->Fill(sim.p.Eta(), sim.p.Pt());
            h2["QA_sim_ALP__etae_eta"]->Fill(ev->peletrue.Eta(), sim.p.Eta());
            h2["QA_sim_ALP__etae_pT"]->Fill(ev->peletrue.Eta(), sim.p.Pt());
            h2["QA_sim_ALP__pTe_eta"]->Fill(ev->peletrue.Pt(), sim.p.Eta());
            h2["QA_sim_ALP__pTe_pT"]->Fill(ev->peletrue.Pt(), sim.p.Pt());

        }

        if (abs(sim.pdg) == 13 && sim.status == 1)
        {
            h3["QA_sim_decay__eta_pT_charge"]->Fill(sim.p.Eta(), sim.p.Pt(), sim.charge);
            h3["QA_sim_decay__etae_eta_charge"]->Fill(ev->peletrue.Eta(), sim.p.Eta(), sim.charge);
            h3["QA_sim_decay__etae_pT_charge"]->Fill(ev->peletrue.Eta(), sim.p.Pt(), sim.charge);
            h3["QA_sim_decay__pTe_eta_charge"]->Fill(ev->peletrue.Pt(), sim.p.Eta(), sim.charge);
            h3["QA_sim_decay__pTe_pT_charge"]->Fill(ev->peletrue.Pt(), sim.p.Pt(), sim.charge);
        }
    }


    // New
    for (auto& [id, rec] : ev->rec)
    {
        if (rec.is_track_b) h3["QA_rec_BT__eta_phi_type"]->Fill(rec.p.Eta(), rec.p.Phi(), rec.type);
        if (rec.is_track_n) h3["QA_rec_NT__eta_phi_type"]->Fill(rec.p.Eta(), rec.p.Phi(), rec.type);
        if (rec.is_track_p) h3["QA_rec_PT__eta_phi_type"]->Fill(rec.p.Eta(), rec.p.Phi(), rec.type);
        if (rec.is_track_b && rec.is_cluster_b) h3["QA_rec_BC__eta_phi_type"]->Fill(rec.p.Eta(), rec.p.Phi(), rec.type);
        if (rec.is_track_n && rec.is_cluster_n) h3["QA_rec_NC__eta_phi_type"]->Fill(rec.p.Eta(), rec.p.Phi(), rec.type);
        if (rec.is_track_p && rec.is_cluster_p) h3["QA_rec_PC__eta_phi_type"]->Fill(rec.p.Eta(), rec.p.Phi(), rec.type);
    }

}


// *****************************************************************************
void MyAnalysis::AnalyzeEfficiency()
{
    // Is there any reconstructed track? true electron matched track?
    bool isgood_rec = (ev->rec.size() > 0 && ev->ele != nullptr);
    // Does the lepton have the correct PID?
    bool isgood_PID = ev->ele == nullptr ? false : ev->ele->isgood_pid;
    // Does it have a good or p?
    bool isgood_pe = ev->ele == nullptr ? false : ev->ele->isgood_momentum;
    // Good eta?
    bool isgood_etae = ev->ele == nullptr ? false : ev->ele->isgood_eta;
    // Does the lepton track have matching ECAL clusters?
    bool isgood_cluster = ev->ele == nullptr ? false : ev->ele->clusters.size();

    vector<int> stages;
    stages.push_back(0);
    if (isgood_rec) stages.push_back(1);
    if (isgood_rec && isgood_PID) stages.push_back(2);
    if (isgood_rec && isgood_PID && isgood_cluster) stages.push_back(3);
    if (isgood_rec && isgood_PID && isgood_cluster && isgood_pe) stages.push_back(4);
    if (isgood_rec && isgood_PID && isgood_cluster && isgood_pe && isgood_etae) stages.push_back(5);

    if (isgood_pe && isgood_etae) stages.push_back(10);
    if (isgood_pe && isgood_etae && isgood_rec) stages.push_back(11);
    if (isgood_pe && isgood_etae && isgood_rec && isgood_cluster) stages.push_back(12);

    for (int istage : stages)
    {
        h2["Eff__Q2_stage"]->Fill(ev->q2true, istage);
        h2["Eff__pTmiss_stage"]->Fill(ev->pmisstrue.Pt(), istage);
        h2["Eff__pTe_stage"]->Fill(ev->peletrue.Pt(), istage);
        h2["Eff__etae_stage"]->Fill(ev->peletrue.Eta(), istage);
        h3["Eff__Q2_pTmiss_stage"]->Fill(ev->q2true, ev->pmisstrue.Pt(), istage);
        h3["Eff__Q2_pTe_stage"]->Fill(ev->q2true, ev->peletrue.Pt(), istage);
        h3["Eff__Q2_etae_stage"]->Fill(ev->q2true, ev->peletrue.Eta(), istage);
        h3["Eff__pTmiss_pTe_stage"]->Fill(ev->pmisstrue.Pt(), ev->peletrue.Pt(), istage);
        h3["Eff__pTmiss_etae_stage"]->Fill(ev->pmisstrue.Pt(), ev->peletrue.Eta(), istage);
        h3["Eff__etae_pTe_stage"]->Fill(ev->peletrue.Eta(), ev->peletrue.Pt(), istage);

        h2["Eff__pe_stage"]->Fill(ev->peletrue.Mag(), istage);
        h3["Eff__etae_pe_stage"]->Fill(ev->peletrue.Eta(), ev->peletrue.Mag(), istage);
    }
}



// *****************************************************************************
void MyAnalysis::AnalyzeResolution()
{
    if (ev->eletrue == nullptr || ev->ele == nullptr) return;

    h2["Res__Q2true_Q2"]->Fill(ev->q2true, ev->q2);
    h2["Res__pTmisstrue_pTmiss"]->Fill(ev->pmisstrue.Pt(), ev->pmiss.Pt());
    h2["Res__pTetrue_pTe"]->Fill(ev->peletrue.Pt(), ev->pele.Pt());
    h2["Res__etaetrue_etae"]->Fill(ev->peletrue.Eta(), ev->pele.Eta());

    h2["Res__Q2_ratio"]->Fill(ev->q2true, ev->q2/ev->q2true);
    h2["Res__pTmiss_ratio"]->Fill(ev->pmisstrue.Pt(), ev->pmiss.Pt()/ev->pmisstrue.Pt());
    h2["Res__pTe_ratio"]->Fill(ev->peletrue.Pt(), ev->pele.Pt()/ev->peletrue.Pt());
    h2["Res__etae_ratio"]->Fill(ev->peletrue.Eta(), ev->pele.Eta()/ev->peletrue.Eta());
    h3["Res__pTe_etae_pTeratio"]->Fill(ev->peletrue.Pt(), ev->peletrue.Eta(), ev->pele.Pt()/ev->peletrue.Pt());
    h3["Res__etae_pTe__etaeratio"]->Fill(ev->peletrue.Eta(), ev->peletrue.Pt(), ev->pele.Eta()/ev->peletrue.Eta());
}


// *****************************************************************************
void MyAnalysis::AnalyzeMatching()
{
    // Track projection to EMC finder
    // There is a lot of unecessary ambiguities here
    // 1. "ReconstructedParticle" and "ReconstructedChargedParticle" CAN point to more than one track (WHY?)
    // 2. Truth-seeded clustering CAN happen even when there are no track projection across the detector (WHY?)
    // 3. Clustering takes place somewhere between EMC surface -- 20~50 mm inside the detector (3500+22.3mm for PEMC, and -1800-50mm for NEMC, and BEMC it's all over the place (imaging...?))
    // For now, I am going to simply use the track point at Radius = 875mm (BEMC), or Z = -1800mm (NEMC), 3400mm (PEMC) of the highest-pT track
    //if (ev->nmatches == 0) return;

    for (auto& [key, rec] : ev->rec)
    {
        auto& sim = ev->sim[rec.isim[0]];
        vector<string> prefixes = {"Match_ECAL_", "Match_HCAL_"};
        for (unsigned int itype = 0; itype < prefixes.size(); ++itype)
        {
            string prefix = prefixes[itype];

            // Tracks
            TVector3 mom = rec.p;
            unsigned int ncls = itype == 0 ? rec.clusters.size() : rec.clusters_HCal.size();
            TVector3 pos_trk = itype == 0 ? rec.pos_ECal : rec.pos_HCal;

            int det = -1 + rec.is_track_b * 1 + rec.is_track_n * 2 + rec.is_track_p * 3;
            h2[prefix + "track__nclusters_det"]->Fill(ncls, det);
            h2[prefix + "track_all__p_det"]->Fill(mom.Mag(), det); // all tracks (regardless of existence of matched cluster)
            h3[prefix + "track_all__eta_phi_det"]->Fill(mom.Eta(), mom.Phi(), det);
            h3[prefix + "track_all__eta_p_det"]->Fill(mom.Eta(), mom.Mag(), det);

            // Clusters
            if (itype == 0 && rec.clusters.size() == 0) continue;
            if (itype == 1 && rec.clusters_HCal.size() == 0) continue;
            if (itype == 0 && rec.pos_ECal.Mag() == 0) continue;
            if (itype == 1 && rec.pos_HCal.Mag() == 0) continue;

            // Reject tracks that go through multiple calorimeters
            bool isgood_one_detector = true;
            if (itype == 0) for (auto& c : rec.clusters) if (c->collectionID != rec.clusters[0]->collectionID) {isgood_one_detector = false; break;}
            if (itype == 1) for (auto& c : rec.clusters_HCal) if (c->collectionID != rec.clusters_HCal[0]->collectionID) {isgood_one_detector = false; break;}
            if (!isgood_one_detector) continue;

            if (itype == 0) det = -1 + rec.cluster->is_b * 1 + rec.cluster->is_n * 2 + rec.cluster->is_p * 3;
            if (itype == 1) det = -1 + rec.cluster_HCal->is_b * 1 + rec.cluster_HCal->is_n * 2 + rec.cluster_HCal->is_p * 3;

            h2[prefix + "track__p_det"]->Fill(mom.Mag(), det);
            h3[prefix + "track__eta_phi_det"]->Fill(mom.Eta(), mom.Phi(), det);
            h3[prefix + "track__eta_p_det"]->Fill(mom.Eta(), mom.Mag(), det);
            for (unsigned int i = 0; i < ncls; ++i)
            {
                auto& c = itype == 0 ? rec.clusters[i] : rec.clusters_HCal[i];
                TVector3 pos = c->pos;
                h3[prefix + "track__nclusters_E_det"]->Fill(ncls, c->ene, det);
                h3[prefix + "track__nclusters_deta_det"]->Fill(ncls, pos.Eta() - pos_trk.Eta(), det);
                h3[prefix + "track__nclusters_dphi_det"]->Fill(ncls, pos.DeltaPhi(pos_trk), det);
                h3[prefix + "track__nclusters_dR_det"]->Fill(ncls, pos.DeltaR(pos_trk), det);
            }

            float ene_high = itype == 0 ? rec.cluster->ene : rec.cluster_HCal->ene;
            TVector3 pos_high = itype == 0 ? rec.cluster->pos : rec.cluster_HCal->pos;

            h2[prefix + "cluster_high__E_det"]->Fill(ene_high, det);
            h2[prefix + "cluster_high__dR_det"]->Fill(pos_high.DeltaR(pos_trk), det);
            h2[prefix + "cluster_high__deta_det"]->Fill(pos_high.Eta() - pos_trk.Eta(), det);
            h2[prefix + "cluster_high__dphi_det"]->Fill(pos_high.DeltaPhi(pos_trk), det);
            h3[prefix + "cluster_high__eta_phi_det"]->Fill(pos_high.Eta(), pos_high.Phi(), det);
            h3[prefix + "cluster_high__eta_E_det"]->Fill(pos_high.Eta(), ene_high, det);

            /*
            h2[prefix + "cluster_near__E_det"]->Fill(ene_near, det);
            h2[prefix + "cluster_near__dR_det"]->Fill(pos_near.DeltaR(pos_trk), det);
            h2[prefix + "cluster_near__deta_det"]->Fill(pos_near.Eta() - pos_trk.Eta(), det);
            h2[prefix + "cluster_near__dphi_det"]->Fill(pos_near.DeltaPhi(pos_trk), det);
            h3[prefix + "cluster_near__eta_phi_det"]->Fill(pos_near.Eta(), pos_near.Phi(), det);
            h3[prefix + "cluster_near__eta_E_det"]->Fill(pos_near.Eta(), ene_near, det);

            h2[prefix + "cluster_sum__E_det"]->Fill(ene_sum, det);
            h2[prefix + "cluster_sum__dR_det"]->Fill(pos_sum.DeltaR(pos_trk), det);
            h2[prefix + "cluster_sum__deta_det"]->Fill(pos_sum.Eta() - pos_trk.Eta(), det);
            h2[prefix + "cluster_sum__dphi_det"]->Fill(pos_sum.DeltaPhi(pos_trk), det);
            h3[prefix + "cluster_sum__eta_phi_det"]->Fill(pos_sum.Eta(), pos_sum.Phi(), det);
            h3[prefix + "cluster_sum__eta_E_det"]->Fill(pos_sum.Eta(), ene_sum, det);
            */

            h3[prefix + "all_high__p_E_det"]->Fill(mom.Mag(), ene_high, det);
            h3[prefix + "all_high__p_Ep_det"]->Fill(mom.Mag(), ene_high / mom.Mag(), det);

            //h3[prefix + "all_near__p_E_det"]->Fill(mom.Mag(), ene_near, det);
            //h3[prefix + "all_near__p_Ep_det"]->Fill(mom.Mag(), ene_near / mom.Mag(), det);

            //h3[prefix + "all_sum__p_E_det"]->Fill(mom.Mag(), ene_sum, det);
            //h3[prefix + "all_sum__p_Ep_det"]->Fill(mom.Mag(), ene_sum / mom.Mag(), det);

            auto& sim = ev->sim[rec.isim[0]];
            if (sim.status == 1 && sim.pdg == cuts.PDG_Lepton)
            {
                h3[prefix + "electron_high__p_E_det"]->Fill(mom.Mag(), ene_high, det);
                h3[prefix + "electron_high__p_Ep_det"]->Fill(mom.Mag(), ene_high / mom.Mag(), det);

                //h3[prefix + "electron_near__p_E_det"]->Fill(mom.Mag(), ene_near, det);
                //h3[prefix + "electron_near__p_Ep_det"]->Fill(mom.Mag(), ene_near / mom.Mag(), det);

                //h3[prefix + "electron_sum__p_E_det"]->Fill(mom.Mag(), ene_sum, det);
                //h3[prefix + "electron_sum__p_Ep_det"]->Fill(mom.Mag(), ene_sum / mom.Mag(), det);
            }

        }

    }
}



void MyAnalysis::AnalyzeBackground()
{
    h1["QA_BGR_Event__ntrks"]->Fill(ev->multiplicity);
    h1["QA_BGR_Event__empz"]->Fill(ev->empz);
    h1["QA_BGR_Event__pTsqrtET"]->Fill(ev->pTsqrtET);
    h1["QA_BGR_Event__pTmiss"]->Fill(ev->pmiss.Pt());

    for (auto& [key, rec] : ev->rec)
    {
        h2["QA_BGR_Track__nhits_type"]->Fill(rec.nhits, rec.type);
        h2["QA_BGR_Track__p_type"]->Fill(rec.p.Mag(), rec.type);
        h2["QA_BGR_Track__pT_type"]->Fill(rec.p.Pt(), rec.type);
        h2["QA_BGR_Track__eta_type"]->Fill(rec.p.Eta(), rec.type);

        h2["QA_BGR_Vertex__vz_type"]->Fill(rec.vtx.Z(), rec.type);
        h2["QA_BGR_Vertex__vx_type"]->Fill(rec.vtx.X(), rec.type);
        h2["QA_BGR_Vertex__vy_type"]->Fill(rec.vtx.Y(), rec.type);
        h2["QA_BGR_Vertex__vr_type"]->Fill(rec.vtx.Perp(), rec.type);

        if (rec.clusters.size() > 0 && rec.cluster == nullptr) cout << "What???? FILE: " << __FILE__ << " LINE: " << __LINE__ << endl;
        if (rec.isgood && rec.clusters.size() > 0 && rec.cluster != nullptr && rec.cluster->isgood)
        {
            h2["QA_BGR_TrackCluster__dphi_type"]->Fill(rec.pos_ECal.DeltaPhi(rec.cluster->pos), rec.type);
            h2["QA_BGR_TrackCluster__deta_type"]->Fill(abs(rec.pos_ECal.Eta() - rec.cluster->pos.Eta()), rec.type);
            h2["QA_BGR_TrackCluster__dR_type"]->Fill(rec.pos_ECal.DeltaR(rec.cluster->pos), rec.type);
            h2["QA_BGR_TrackCluster__Ep_type"]->Fill(rec.cluster->ene/rec.p.Mag(), rec.type);
            h3["QA_BGR_TrackCluster__p_Ep_type"]->Fill(rec.p.Mag(), rec.cluster->ene/rec.p.Mag(), rec.type);
        }

        if (rec.isgood && rec.clusters.size() > 0 && rec.cluster_near != nullptr && rec.cluster_near->isgood)
        {
            h2["QA_BGR_TrackNearCluster__dphi_type"]->Fill(rec.pos_ECal.DeltaPhi(rec.cluster_near->pos), rec.type);
            h2["QA_BGR_TrackNearCluster__deta_type"]->Fill(abs(rec.pos_ECal.Eta() - rec.cluster_near->pos.Eta()), rec.type);
            h2["QA_BGR_TrackNearCluster__dR_type"]->Fill(rec.pos_ECal.DeltaR(rec.cluster_near->pos), rec.type);
            h2["QA_BGR_TrackNearCluster__Ep_type"]->Fill(rec.cluster_near->ene/rec.p.Mag(), rec.type);
            h3["QA_BGR_TrackNearCluster__p_Ep_type"]->Fill(rec.p.Mag(), rec.cluster_near->ene/rec.p.Mag(), rec.type);
        }

    }

    for (auto& c : ev->clusters)
    {
        h2["QA_BGR_Cluster__E_type"]->Fill(c.ene, c.type);
        h2["QA_BGR_Cluster__eta_type"]->Fill(c.pos.Eta(), c.type);
        h3["QA_BGR_Cluster__eta_E_type"]->Fill(c.pos.Eta(), c.ene, c.type);
    }

}
