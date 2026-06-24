#include "MyAnalysis.h"


// *****************************************************************************
void MyAnalysis::AnalyzeQA()
{
    if (ev->particles_sim.size() > 0) h1["event__stage"]->Fill(0);
    if (ev->particles.size() > 0) h1["event__stage"]->Fill(1);

    float q2_sim = ev->q2true;
    float pTmiss_sim = ev->pmisstrue.Pt();
    auto ele_sim = ev->GetFinalLeptonTrue();
    TVector3 pe_sim;
    if (ele_sim != edm4hep::MCParticle::makeEmpty()) pe_sim = TVector3(ele_sim.getMomentum().x, ele_sim.getMomentum().y, ele_sim.getMomentum().z);

    float q2_rec = ev->q2;
    float pTmiss_rec = ev->pmiss.Pt();
    auto ele_rec = ev->GetFinalLepton();
    TVector3 pe_rec;
    if (ele_rec != edm4eic::ReconstructedParticle::makeEmpty()) pe_rec = TVector3(ele_rec.getMomentum().x, ele_rec.getMomentum().y, ele_rec.getMomentum().z);

    auto ele_ini = ev->GetInitialLeptonTrue();
    auto alp = ev->GetALPTrue();
    float Ebeam = 0, Eele = 0, Ealp = 0;
    if (ele_ini != edm4hep::MCParticle::makeEmpty()) Ebeam = ele_ini.getEnergy();
    if (ele_sim != edm4hep::MCParticle::makeEmpty()) Eele = ele_sim.getEnergy();
    if (alp != edm4hep::MCParticle::makeEmpty()) Ealp = alp.getEnergy();

    if (ev->particles_sim.size() > 0)
    {
        h1["QA_sim__Q2"]->Fill(q2_sim);
        h1["QA_sim__pe"]->Fill(pe_sim.Mag());
        h1["QA_sim__pTmiss"]->Fill(pTmiss_sim);
        h1["QA_sim__pTe"]->Fill(pe_sim.Pt());
        h1["QA_sim__etae"]->Fill(pe_sim.Eta());

        h2["QA_sim__Q2_pTmiss"]->Fill(q2_sim, pTmiss_sim);
        h2["QA_sim__Q2_pTe"]->Fill(q2_sim, pe_sim.Pt());
        h2["QA_sim__Q2_etae"]->Fill(q2_sim, pe_sim.Eta());
        h2["QA_sim__pTmiss_pTe"]->Fill(pTmiss_sim, pe_sim.Pt());
        h2["QA_sim__pTmiss_etae"]->Fill(pTmiss_sim, pe_sim.Eta());
        h2["QA_sim__etae_pTe"]->Fill(pe_sim.Eta(), pe_sim.Pt());
        h2["QA_sim__etae_pe"]->Fill(pe_sim.Eta(), pe_sim.Mag());


        h1["QA_sim_electron__Efrac"]->Fill(Eele/Ebeam);
        h1["QA_sim_ALP__Efrac"]->Fill(Ealp/Ebeam);
    }

    for (auto& par : ev->particles)
    {
        if (par.sim.getPDG() != cuts.PDG_Lepton || par.sim.getGeneratorStatus() != 1) continue;

        h1["QA_rec__Q2"]->Fill(q2_rec);
        h1["QA_rec__pe"]->Fill(pe_rec.Mag());
        h1["QA_rec__pTmiss"]->Fill(pTmiss_rec);
        h1["QA_rec__pTe"]->Fill(pe_rec.Pt());
        h1["QA_rec__etae"]->Fill(pe_rec.Eta());

        h2["QA_rec__Q2_pTmiss"]->Fill(q2_rec, pTmiss_rec);
        h2["QA_rec__Q2_pTe"]->Fill(q2_rec, pe_rec.Pt());
        h2["QA_rec__Q2_etae"]->Fill(q2_rec, pe_rec.Eta());
        h2["QA_rec__pTmiss_pTe"]->Fill(pTmiss_rec, pe_rec.Pt());
        h2["QA_rec__pTmiss_etae"]->Fill(pTmiss_rec, pe_rec.Eta());
        h2["QA_rec__etae_pTe"]->Fill(pe_rec.Eta(), pe_rec.Pt());
        h2["QA_rec__etae_pe"]->Fill(pe_rec.Eta(), pe_rec.Mag());

        break;
    }

    for (auto& par : ev->particles)
    {
        int type = 0;
        if (par.sim.getPDG() == cuts.PDG_Lepton && par.sim.getGeneratorStatus() == 1) type = 1;

        h2["QA_rec_track__nhits_type"]->Fill(par.nhits, type);
    }

    for (auto& par : ev->particles)
    {
        auto& sim = par.sim;
        auto& rec = par.rec;
        TVector3 p(rec.getMomentum().x,rec.getMomentum().y,rec.getMomentum().z);
        TVector3 ps(sim.getMomentum().x,sim.getMomentum().y,sim.getMomentum().z);
        auto& c = par.cluster_high;

        //
        h2["QA_sim__pT_bitmask2"]->Fill(ps.Pt(), par.bitmask2);
        h2["QA_sim__p_bitmask2"]->Fill(ps.Mag(), par.bitmask2);
        h2["QA_sim__eta_bitmask2"]->Fill(ps.Eta(), par.bitmask2);

        //
        h2["QA_rec__nhits_bitmask"]->Fill(par.nhits, par.bitmask);
        h2["QA_rec__pT_bitmask"]->Fill(p.Pt(), par.bitmask);
        h2["QA_rec__p_bitmask"]->Fill(p.Mag(), par.bitmask);
        h2["QA_rec__eta_bitmask"]->Fill(p.Eta(), par.bitmask);

        h2["QA_rec__nhits_bitmask2"]->Fill(par.nhits, par.bitmask2);
        h2["QA_rec__pT_bitmask2"]->Fill(p.Pt(), par.bitmask2);
        h2["QA_rec__p_bitmask2"]->Fill(p.Mag(), par.bitmask2);
        h2["QA_rec__eta_bitmask2"]->Fill(p.Eta(), par.bitmask2);

        if (par.clusters.size() > 0)
        {
            h2["QA_rec__E_bitmask"]->Fill(c.getEnergy(), par.bitmask);
            h2["QA_rec__Ep_bitmask"]->Fill(c.getEnergy()/p.Mag(), par.bitmask);
            h3["QA_rec__p_Ep_bitmask"]->Fill(p.Mag(), c.getEnergy()/p.Mag(), par.bitmask);

            h2["QA_rec__E_bitmask2"]->Fill(c.getEnergy(), par.bitmask2);
            h2["QA_rec__Ep_bitmask2"]->Fill(c.getEnergy()/p.Mag(), par.bitmask2);
            h3["QA_rec__p_Ep_bitmask2"]->Fill(p.Mag(), c.getEnergy()/p.Mag(), par.bitmask2);
        }

    }

    for (auto& sim : ev->particles_sim)
    {
        TVector3 p(sim.getMomentum().x, sim.getMomentum().y, sim.getMomentum().z);

        if (abs(sim.getPDG()) == 0 && sim.getGeneratorStatus() == 2)
        {
            h2["QA_sim_ALP__eta_pT"]->Fill(p.Eta(), p.Pt());
            h2["QA_sim_ALP__etae_eta"]->Fill(pe_sim.Eta(), p.Eta());
            h2["QA_sim_ALP__etae_pT"]->Fill(pe_sim.Eta(), p.Pt());
            h2["QA_sim_ALP__pTe_eta"]->Fill(pe_sim.Pt(), p.Eta());
            h2["QA_sim_ALP__pTe_pT"]->Fill(pe_sim.Pt(), p.Pt());

        }

        if (abs(sim.getPDG()) == 13 && sim.getGeneratorStatus() == 1)
        {
            float q = sim.getCharge();

            h3["QA_sim_decay__eta_pT_charge"]->Fill(p.Eta(), p.Pt(), q);
            h3["QA_sim_decay__etae_eta_charge"]->Fill(pe_sim.Eta(), p.Eta(), q);
            h3["QA_sim_decay__etae_pT_charge"]->Fill(pe_sim.Eta(), p.Pt(), q);
            h3["QA_sim_decay__pTe_eta_charge"]->Fill(pe_sim.Pt(), p.Eta(), q);
            h3["QA_sim_decay__pTe_pT_charge"]->Fill(pe_sim.Pt(), p.Pt(), q);
        }
    }

}

// *****************************************************************************
void MyAnalysis::AnalyzeEfficiency()
{
    auto ele_sim = ev->GetFinalLeptonTrue();
    TVector3 pe_sim(0,0,0);
    if (ele_sim != edm4hep::MCParticle::makeEmpty()) pe_sim = TVector3(ele_sim.getMomentum().x, ele_sim.getMomentum().y, ele_sim.getMomentum().z);

    auto ele = ev->GetFinalLepton();
    TVector3 pele(0,0,0);
    int pdgele = 0;
    if (ele != edm4eic::ReconstructedParticle::makeEmpty())
    {
        pele = TVector3(ele.getMomentum().x, ele.getMomentum().y, ele.getMomentum().z);
        pdgele = ev->GetFinalLepton().getPDG();
    }


    // Is there any reconstructed track? true electron matched track?
    bool isgood_rec = (ev->particles_rec.size() > 0 && ele != edm4eic::ReconstructedParticle::makeEmpty());
    // Does the lepton have the correct PID?
    bool isgood_PID = pdgele == 11;
    // Does it have a good pT or p?
    bool isgood_pTe = pe_sim.Pt() > cuts.Min_Lepton_Pt;
    bool isgood_pe = pe_sim.Mag() > cuts.Min_Lepton_P;
    // Good eta?
    bool isgood_etae = pe_sim.Eta() > cuts.Min_Lepton_Eta && pe_sim.Eta() < cuts.Max_Lepton_Eta;
    // Does the lepton track have matching ECAL clusters?
    bool isgood_cluster = false;
    for (auto par : ev->particles) if (par.sim.getPDG() == 11 && par.sim.getGeneratorStatus() == 1 && par.clusters.size() > 0) {isgood_cluster = true; break;}

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

    if (isgood_pTe && isgood_etae) stages.push_back(15);
    if (isgood_pTe && isgood_etae && isgood_rec) stages.push_back(16);
    if (isgood_pTe && isgood_etae && isgood_rec && isgood_cluster) stages.push_back(17);

    //if (isgood_pe && isgood_etae && isgood_rec && isgood_PID) stages.push_back(15);


    for (int istage : stages)
    {
        float q2_sim = ev->q2true;
        float pTmiss_sim = ev->pmisstrue.Pt();

        h2["Eff__Q2_stage"]->Fill(q2_sim, istage);
        h2["Eff__pTmiss_stage"]->Fill(pTmiss_sim, istage);
        h2["Eff__pTe_stage"]->Fill(pe_sim.Pt(), istage);
        h2["Eff__etae_stage"]->Fill(pe_sim.Eta(), istage);
        h3["Eff__Q2_pTmiss_stage"]->Fill(q2_sim, pTmiss_sim, istage);
        h3["Eff__Q2_pTe_stage"]->Fill(q2_sim, pe_sim.Pt(), istage);
        h3["Eff__Q2_etae_stage"]->Fill(q2_sim, pe_sim.Eta(), istage);
        h3["Eff__pTmiss_pTe_stage"]->Fill(pTmiss_sim, pe_sim.Pt(), istage);
        h3["Eff__pTmiss_etae_stage"]->Fill(pTmiss_sim, pe_sim.Eta(), istage);
        h3["Eff__etae_pTe_stage"]->Fill(pe_sim.Eta(), pe_sim.Pt(), istage);

        h2["Eff__pe_stage"]->Fill(pe_sim.Mag(), istage);
        h3["Eff__etae_pe_stage"]->Fill(pe_sim.Eta(), pe_sim.Mag(), istage);
    }
}

// *****************************************************************************
void MyAnalysis::AnalyzeResolution()
{
    if (ev->particles_sim.size() == 0 || ev->particles_rec.size() == 0) return;

    float q2_sim = ev->q2true;
    float pTmiss_sim = ev->pmisstrue.Pt();
    auto ele_sim = ev->GetFinalLeptonTrue();
    TVector3 pe_sim;
    if (ele_sim != edm4hep::MCParticle::makeEmpty()) pe_sim = TVector3(ele_sim.getMomentum().x, ele_sim.getMomentum().y, ele_sim.getMomentum().z);

    float q2_rec = ev->q2;
    float pTmiss_rec = ev->pmiss.Pt();
    auto ele_rec = ev->GetFinalLepton();
    TVector3 pe_rec;
    if (ele_rec != edm4eic::ReconstructedParticle::makeEmpty()) pe_rec = TVector3(ele_rec.getMomentum().x, ele_rec.getMomentum().y, ele_rec.getMomentum().z);

    h2["Res__Q2true_Q2"]->Fill(q2_sim, q2_rec);
    h2["Res__pTmisstrue_pTmiss"]->Fill(pTmiss_sim, pTmiss_rec);
    h2["Res__pTetrue_pTe"]->Fill(pe_sim.Pt(), pe_rec.Pt());
    h2["Res__etaetrue_etae"]->Fill(pe_sim.Eta(), pe_rec.Eta());

    h2["Res__Q2_ratio"]->Fill(q2_sim, q2_rec/q2_sim);
    h2["Res__pTmiss_ratio"]->Fill(pTmiss_sim, pTmiss_rec/pTmiss_sim);
    h2["Res__pTe_ratio"]->Fill(pe_sim.Pt(), pe_rec.Pt()/pe_sim.Pt());
    h2["Res__etae_ratio"]->Fill(pe_sim.Eta(), pe_rec.Eta()/pe_sim.Eta());
    h3["Res__pTe_etae_pTeratio"]->Fill(pe_sim.Pt(), pe_sim.Eta(), pe_rec.Pt()/pe_sim.Pt());
    h3["Res__etae_pTe__etaeratio"]->Fill(pe_sim.Eta(), pe_sim.Pt(), pe_rec.Eta()/pe_sim.Eta());
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

    for (auto& par : ev->particles)
    {
        vector<string> prefixes = {"Match_ECAL_", "Match_HCAL_"};
        for (unsigned int itype = 0; itype < prefixes.size(); ++itype)
        {
            string prefix = prefixes[itype];

            // Reject tracks that go through multiple calorimeters
            bool isgood_one_detector = true;
            if (itype == 0) for (unsigned int i = 0; i < par.clusters.size(); ++i) if (par.clusters[i].getObjectID().collectionID != par.clusters[0].getObjectID().collectionID) isgood_one_detector = false;
            if (itype == 1) for (unsigned int i = 0; i < par.clusters.size(); ++i) if (par.clusters[i].getObjectID().collectionID != par.clusters[0].getObjectID().collectionID) isgood_one_detector = false;

            int det = -1;
            auto idc = itype == 0 ? par.cluster_high.getObjectID().collectionID : par.hcluster_high.getObjectID().collectionID;
            if (idc == collectionID_BEMC || idc == collectionID_BHCal) det = 0;
            if (idc == collectionID_NEMC || idc == collectionID_NHCal) det = 1;
            if (idc == collectionID_PEMC || idc == collectionID_PHCal) det = 2;

            TVector3 mom(par.rec.getMomentum().x, par.rec.getMomentum().y, par.rec.getMomentum().z);
            unsigned int ncls = par.clusters.size();
            TVector3 pos_trk = par.pos_track;
            float ene_sum = par.ene_cluster_sum;
            TVector3 pos_sum = par.pos_cluster_sum;
            float ene_high = par.cluster_high.getEnergy();
            TVector3 pos_high(par.cluster_high.getPosition().x, par.cluster_high.getPosition().y, par.cluster_high.getPosition().z);
            float ene_near = par.cluster_near.getEnergy();
            TVector3 pos_near(par.cluster_near.getPosition().x, par.cluster_near.getPosition().y, par.cluster_near.getPosition().z);
            if (itype != 0)
            {
                ncls = par.hclusters.size();
                pos_trk = par.pos_track_hcal;
                ene_sum = par.ene_hcluster_sum;
                pos_sum = par.pos_hcluster_sum;
                ene_high = par.hcluster_high.getEnergy();
                pos_high = TVector3(par.hcluster_high.getPosition().x, par.hcluster_high.getPosition().y, par.hcluster_high.getPosition().z);
                ene_near = par.hcluster_near.getEnergy();
                pos_near = TVector3(par.hcluster_near.getPosition().x, par.hcluster_near.getPosition().y, par.hcluster_near.getPosition().z);
            }


            h2[prefix + "track__nclusters_det"]->Fill(ncls, det);

            h2[prefix + "track_all__p_det"]->Fill(mom.Mag(), det); // all tracks (regardless of existence of matched cluster)
            h3[prefix + "track_all__eta_phi_det"]->Fill(mom.Eta(), mom.Phi(), det);
            h3[prefix + "track_all__eta_p_det"]->Fill(mom.Eta(), mom.Mag(), det);

            bool ismatched = (pos_trk.Perp() > 0);
            if (!ismatched) continue;
            if (itype == 0 && par.clusters.size() == 0) continue;
            if (itype == 1 && par.hclusters.size() == 0) continue;
            if (!isgood_one_detector) continue;

            h2[prefix + "track__p_det"]->Fill(mom.Mag(), det);
            h3[prefix + "track__eta_phi_det"]->Fill(mom.Eta(), mom.Phi(), det);
            h3[prefix + "track__eta_p_det"]->Fill(mom.Eta(), mom.Mag(), det);

            for (unsigned int i = 0; i < ncls; ++i)
            {
                auto c = itype == 0 ? par.clusters[i] : par.hclusters[i];
                TVector3 pos(c.getPosition().x, c.getPosition().y, c.getPosition().z);
                h3[prefix + "track__nclusters_E_det"]->Fill(ncls, c.getEnergy(), det);
                h3[prefix + "track__nclusters_deta_det"]->Fill(ncls, pos.Eta() - pos_trk.Eta(), det);
                h3[prefix + "track__nclusters_dphi_det"]->Fill(ncls, pos.DeltaPhi(pos_trk), det);
                h3[prefix + "track__nclusters_dR_det"]->Fill(ncls, pos.DeltaR(pos_trk), det);
            }

            h2[prefix + "cluster_high__E_det"]->Fill(ene_high, det);
            h2[prefix + "cluster_high__dR_det"]->Fill(pos_high.DeltaR(pos_trk), det);
            h2[prefix + "cluster_high__deta_det"]->Fill(pos_high.Eta() - pos_trk.Eta(), det);
            h2[prefix + "cluster_high__dphi_det"]->Fill(pos_high.DeltaPhi(pos_trk), det);
            h3[prefix + "cluster_high__eta_phi_det"]->Fill(pos_high.Eta(), pos_high.Phi(), det);
            h3[prefix + "cluster_high__eta_E_det"]->Fill(pos_high.Eta(), ene_high, det);

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

            h3[prefix + "all_high__p_E_det"]->Fill(mom.Mag(), ene_high, det);
            h3[prefix + "all_high__p_Ep_det"]->Fill(mom.Mag(), ene_high / mom.Mag(), det);

            h3[prefix + "all_near__p_E_det"]->Fill(mom.Mag(), ene_near, det);
            h3[prefix + "all_near__p_Ep_det"]->Fill(mom.Mag(), ene_near / mom.Mag(), det);

            h3[prefix + "all_sum__p_E_det"]->Fill(mom.Mag(), ene_sum, det);
            h3[prefix + "all_sum__p_Ep_det"]->Fill(mom.Mag(), ene_sum / mom.Mag(), det);

            if (par.sim.getGeneratorStatus() == 1 && par.sim.getPDG() == cuts.PDG_Lepton)
            {
                h3[prefix + "electron_high__p_E_det"]->Fill(mom.Mag(), ene_high, det);
                h3[prefix + "electron_high__p_Ep_det"]->Fill(mom.Mag(), ene_high / mom.Mag(), det);

                h3[prefix + "electron_near__p_E_det"]->Fill(mom.Mag(), ene_near, det);
                h3[prefix + "electron_near__p_Ep_det"]->Fill(mom.Mag(), ene_near / mom.Mag(), det);

                h3[prefix + "electron_sum__p_E_det"]->Fill(mom.Mag(), ene_sum, det);
                h3[prefix + "electron_sum__p_Ep_det"]->Fill(mom.Mag(), ene_sum / mom.Mag(), det);
            }

        }

    }
}

// *****************************************************************************
void MyAnalysis::AnalyzeDecayVertex()
{

}

// *****************************************************************************
void MyAnalysis::AnalyzeElectronIdentification()
{
    if (ev->particles.size() == 0) return;

    // return if sim -> more than one particle
    bool is_unique = true;
    for (unsigned int i = 0; i < ev->particles.size() - 1; ++i) for (unsigned int j = i + 1; j < ev->particles.size(); ++j) if (ev->particles[i].sim == ev->particles[j].sim) {is_unique = false; break;}
    if (!is_unique) {cout << "Duplicate event!" << endl; return;}

    for (auto& par : ev->particles)
    {
        if (par.tracks.size() > 1) {cout << "More than one track!" << endl; continue;}

        bool is_electron = par.sim.getPDG() == cuts.PDG_Lepton;

        bool has_ECal_clusters = par.clusters.size() > 0;
        bool is_one_ECAL = true;
        for (unsigned int i = 0; i < par.clusters.size(); ++i) if (par.clusters[i].getObjectID().collectionID != par.clusters[0].getObjectID().collectionID) is_one_ECAL = false;
        string type_ECAL = "";
        for (auto c : par.clusters)
        {
            if (c.getObjectID().collectionID == collectionID_BEMC) type_ECAL = "ECal-B";
            if (c.getObjectID().collectionID == collectionID_NEMC) type_ECAL = "ECal-N";
            if (c.getObjectID().collectionID == collectionID_PEMC) type_ECAL = "ECal-P";
        }

        bool has_HCal_clusters = par.hclusters.size() > 0;
        bool is_one_HCAL = true;
        for (unsigned int i = 0; i < par.hclusters.size(); ++i) if (par.hclusters[i].getObjectID().collectionID != par.hclusters[0].getObjectID().collectionID) is_one_HCAL = false;
        string type_HCAL = "";
        for (auto c : par.hclusters)
        {
            if (c.getObjectID().collectionID == collectionID_BHCal) type_HCAL = "HCal-B";
            if (c.getObjectID().collectionID == collectionID_NHCal) type_HCAL = "HCal-N";
            if (c.getObjectID().collectionID == collectionID_PHCal) type_HCAL = "HCal-P";
        }

        bool has_projection = true;
        if (par.projection.size() == 0) has_projection = false;

        //
        if (par.tracks.size() == 0) continue;
        if (!has_ECal_clusters && !has_HCal_clusters) continue;
        //if (type_ECAL != "ECal-P" && type_HCAL != "HCal-P") continue;
        if (!has_HCal_clusters) continue;

        auto rec = par.rec;
        auto sim = par.sim;

        edm4eic::Cluster c_ECAL;
        edm4eic::Cluster c_HCAL;
        if (has_ECal_clusters) {float ene = 0; for (auto c : par.clusters) if (ene < c.getEnergy()) {ene = c.getEnergy(); c_ECAL = c;}}
        if (has_HCal_clusters) {float ene = 0; for (auto c : par.hclusters) if (ene < c.getEnergy()) {ene = c.getEnergy(); c_HCAL = c;}}

        int ww = 15;
        TVector3 ps(sim.getMomentum().x, sim.getMomentum().y, sim.getMomentum().z);
        TVector3 pr(rec.getMomentum().x, rec.getMomentum().y, rec.getMomentum().z);
        TVector3 posE(c_ECAL.getPosition().x, c_ECAL.getPosition().y, c_ECAL.getPosition().z);
        TVector3 posH(c_HCAL.getPosition().x, c_HCAL.getPosition().y, c_HCAL.getPosition().z);

        /*
        cout << "Event : " << ev->id << endl;
        cout << setw(ww) << "type" << setw(ww) << "PDG/CAL/id" << setw(ww) << "system" << setw(ww) << "surface" << setw(ww) << "E/p" << setw(ww) << "pT/R" << setw(ww) << "pZ/Z" << setw(ww) << "eta" << setw(ww) << "phi" << endl;
        cout << setw(ww) << "Genparticle" << setw(ww) << sim.getPDG() << setw(ww) << "" << setw(ww) << "" << setw(ww) << sim.getEnergy() << setw(ww) << ps.Pt() << setw(ww) << ps.Pz() << setw(ww) << ps.Eta() << setw(ww) << ps.Phi() << endl;
        cout << setw(ww) << "RecParticle" << setw(ww) << rec.getPDG() << setw(ww) << "" << setw(ww) << "" << setw(ww) << pr.Mag() << setw(ww) << pr.Pt() << setw(ww) << pr.Pz() << setw(ww) << pr.Eta() << setw(ww) << pr.Phi() << endl;
        if (has_ECal_clusters && is_one_ECAL) cout << setw(ww) << "ECalCluster" << setw(ww) << type_ECAL << setw(ww) << "" << setw(ww) << "" << setw(ww) << c_ECAL.getEnergy() << setw(ww) << posE.Perp() << setw(ww) << posE.Z() << setw(ww) << posE.Eta() << setw(ww) << posE.Phi() << endl;
        if (has_HCal_clusters && is_one_HCAL) cout << setw(ww) << "HCalCluster" << setw(ww) << type_HCAL << setw(ww) << "" << setw(ww) << "" << setw(ww) << c_HCAL.getEnergy() << setw(ww) << posH.Perp() << setw(ww) << posH.Z() << setw(ww) << posH.Eta() << setw(ww) << posH.Phi() << endl;
        if (has_projection) for (int i = 0; i < par.projection.size(); ++i)
        {
            auto p = par.projection[i];
            TVector3 pos(p.position.x, p.position.y, p.position.z);
            cout << setw(ww) << "TrackPoint" << setw(ww) << i << setw(ww) << p.system << setw(ww) << p.surface << setw(ww) << "" << setw(ww) << pos.Perp() << setw(ww) << pos.Z() << setw(ww) << pos.Eta() << setw(ww) << pos.Phi() << endl;
        }
        cout << endl;
        */

        // Look at defintions.xml
    }
}

// AW 20260623
void MyAnalysis::AnalyzeBdtVariables(){
    // Fill into 1D histograms
    h1["bdt_elec_e"]->Fill(ev->bdt_elec_e);
    h1["bdt_pt"]->Fill(ev->bdt_pt);
    h1["bdt_eta"]->Fill(ev->bdt_eta);
    h1["bdt_elec_beam_rat"]->Fill(ev->bdt_elec_beam_rat);
    h1["bdt_pt_miss"]->Fill(ev->bdt_pt_miss);
    h1["bdt_p"]->Fill(ev->bdt_p);
    h1["bdt_phi"]->Fill(ev->bdt_phi);
    h1["bdt_sig_label"]->Fill(ev->sig_bkgd_label);
    h1["bdt_q2"]->Fill(ev->bdt_q2);
    h1["bdt_angle"]->Fill(ev->bdt_angle);
    h1["bdt_dr"]->Fill(ev->bdt_dr);
    h1["bdt_e_pz"]->Fill(ev->bdt_e_pz);
    h1["bdt_et"]->Fill(ev->bdt_et);
    h1["bdt_pperp"]->Fill(ev->bdt_pperp);
    h1["bdt_et_pperp"]->Fill(ev->bdt_et_pperp);
    h1["bdt_dphi"]->Fill(ev->bdt_dphi);
    h1["bdt_dphi_avg"]->Fill(ev->bdt_dphi_avg);

    if(file_type == 2){ //If it's a DIS file, looking at all particles
        TVector3 dis_particle;
        for(map<int,MyReconstructedParticle>::const_iterator itr = ev->rec.begin(); itr!= ev->rec.end(); ++itr){
            dis_particle = TVector3(itr->second.obj.getMomentum().x,itr->second.obj.getMomentum().y,itr->second.obj.getMomentum().z); // establish the particle,
            h1["dis_e"]->Fill(TMath::Sqrt(TMath::Sq(dis_particle.Mag()) + TMath::Sq(itr->second.obj.getMass())));
            h1["dis_pt"]->Fill(dis_particle.Pt());
            h1["dis_eta"]->Fill(dis_particle.Eta());
            h1["dis_p"]->Fill(TMath::Sqrt(TMath::Sq(dis_particle.Px())+TMath::Sq(dis_particle.Py())+TMath::Sq(dis_particle.Pz())));
            h1["dis_phi"]->Fill(dis_particle.Phi());
            dis_particle.Clear();
        }
        
        TVector3 dis_electron;

        for(map<int,MyGeneratedParticle>::const_iterator itr = ev->sim.begin(); itr!= ev->sim.end(); ++itr){ // looking at DIS electrons
            if(ev->rec[itr->first].type != 1){continue;} // if it's not the DIS signal
            if(itr->second.obj.getPDG() == 11 && itr->second.obj.getGeneratorStatus() == 1){ 
                dis_electron = TVector3(ev->rec[itr->first].obj.getMomentum().x, ev->rec[itr->first].obj.getMomentum().y, ev->rec[itr->first].obj.getMomentum().z);
                h1["dis_elec_e"]->Fill(TMath::Sqrt(TMath::Sq(dis_electron.Mag()) + TMath::Sq(ev->rec[itr->first].obj.getMass())));
                h1["dis_elec_pt"]->Fill(dis_electron.Pt());
                h1["dis_elec_eta"]->Fill(dis_electron.Eta());
                h1["dis_elec_beam_rat"]->Fill(TMath::Sqrt(TMath::Sq(dis_electron.Mag()) + TMath::Sq(ev->rec[itr->first].obj.getMass()))/TMath::Sqrt(TMath::Sq(ev->pbeam.Mag()) + TMath::Sq(0.000511))); //do I need to do this one?
                h1["dis_elec_p"]->Fill(TMath::Sqrt(TMath::Sq(dis_electron.Px())+TMath::Sq(dis_electron.Py())+TMath::Sq(dis_electron.Pz())));
                h1["dis_elec_phi"]->Fill(dis_electron.Phi());
                h1["dis_elec_q2"]->Fill(2 * TMath::Sqrt(TMath::Sq(dis_electron.Mag()) + TMath::Sq(ev->rec[itr->first].obj.getMass())) * TMath::Sqrt(TMath::Sq(ev->pbeam.Mag()) + TMath::Sq(0.000511)) * (1.0 - cos(ev->pbeam.Theta() - dis_electron.Theta()))); //should I compare to a ion beam or the electron beam???
                h1["dis_elec_angle"]->Fill(dis_electron.Theta());
                dis_electron.Clear();
            }
        }
    }
}
