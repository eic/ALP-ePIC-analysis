#include "MyAnalysis.h"


// *****************************************************************************
void MyAnalysis::AnalyzeQA()
{
    if (ev->particles_sim.size() > 0) h1["event__stage"]->Fill(0);
    if (ev->particles.size() > 0) h1["event__stage"]->Fill(1);

    float q2_sim = ev->Q2_true();
    float pTmiss_sim = ev->pTmiss_true().Pt();
    auto ele_sim = ev->GetFinalLeptonTrue();
    TVector3 pe_sim;
    if (ele_sim != edm4hep::MCParticle::makeEmpty()) pe_sim = TVector3(ele_sim.getMomentum().x, ele_sim.getMomentum().y, ele_sim.getMomentum().z);

    float q2_rec = ev->Q2();
    float pTmiss_rec = ev->pTmiss().Pt();
    auto ele_rec = ev->GetFinalLepton();
    TVector3 pe_rec;
    if (ele_rec != edm4eic::ReconstructedParticle::makeEmpty()) pe_rec = TVector3(ele_rec.getMomentum().x, ele_rec.getMomentum().y, ele_rec.getMomentum().z);

    if (ev->particles_sim.size() > 0)
    {
        h1["QA_sim__Q2"]->Fill(q2_sim);
        h1["QA_sim__pTmiss"]->Fill(pTmiss_sim);
        h1["QA_sim__pTe"]->Fill(pe_sim.Pt());
        h1["QA_sim__etae"]->Fill(pe_sim.Eta());

        h2["QA_sim__Q2_pTmiss"]->Fill(q2_sim, pTmiss_sim);
        h2["QA_sim__Q2_pTe"]->Fill(q2_sim, pe_sim.Pt());
        h2["QA_sim__Q2_etae"]->Fill(q2_sim, pe_sim.Eta());
        h2["QA_sim__pTmiss_pTe"]->Fill(pTmiss_sim, pe_sim.Pt());
        h2["QA_sim__pTmiss_etae"]->Fill(pTmiss_sim, pe_sim.Eta());
        h2["QA_sim__etae_pTe"]->Fill(pe_sim.Eta(), pe_sim.Pt());
    }

    if (ev->particles_rec.size() > 0)
    {
        h1["QA_rec__Q2"]->Fill(q2_rec);
        h1["QA_rec__pTmiss"]->Fill(pTmiss_rec);
        h1["QA_rec__pTe"]->Fill(pe_rec.Pt());
        h1["QA_rec__etae"]->Fill(pe_rec.Eta());

        h2["QA_rec__Q2_pTmiss"]->Fill(q2_rec, pTmiss_rec);
        h2["QA_rec__Q2_pTe"]->Fill(q2_rec, pe_rec.Pt());
        h2["QA_rec__Q2_etae"]->Fill(q2_rec, pe_rec.Eta());
        h2["QA_rec__pTmiss_pTe"]->Fill(pTmiss_rec, pe_rec.Pt());
        h2["QA_rec__pTmiss_etae"]->Fill(pTmiss_rec, pe_rec.Eta());
        h2["QA_rec__etae_pTe"]->Fill(pe_rec.Eta(), pe_rec.Pt());
    }


}

// *****************************************************************************
void MyAnalysis::AnalyzeEfficiency()
{
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
    // Does it have a good pT
    bool isgood_pTe = pele.Pt() > cuts.Min_Lepton_Pt;
    // Good eta?
    bool isgood_etae = pele.Eta() > cuts.Min_Lepton_Eta && pele.Eta() < cuts.Max_Lepton_Eta;
    // Does the lepton track have matching ECAL clusters?
    bool isgood_cluster = false;
    for (auto par : ev->particles) if (par.sim.getPDG() == 11 && par.sim.getGeneratorStatus() == 1 && par.clusters.size() > 0) {isgood_cluster = true; break;}

    int stage = 0;
    if (isgood_rec) stage = 1;
    if (isgood_rec && isgood_PID) stage = 2;
    if (isgood_rec && isgood_PID && isgood_pTe) stage = 3;
    if (isgood_rec && isgood_PID && isgood_pTe && isgood_etae) stage = 4;

    for (int istage = 0; istage < 20; istage++)
    {
        if (istage > stage) break;

        float q2_sim = ev->Q2_true();
        float pTmiss_sim = ev->pTmiss_true().Pt();
        auto ele_sim = ev->GetFinalLeptonTrue();
        TVector3 pe_sim;
        if (ele_sim != edm4hep::MCParticle::makeEmpty()) pe_sim = TVector3(ele_sim.getMomentum().x, ele_sim.getMomentum().y, ele_sim.getMomentum().z);

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
    }
}

// *****************************************************************************
void MyAnalysis::AnalyzeResolution()
{
    if (ev->particles_sim.size() == 0 || ev->particles_rec.size() == 0) return;

    float q2_sim = ev->Q2_true();
    float pTmiss_sim = ev->pTmiss_true().Pt();
    auto ele_sim = ev->GetFinalLeptonTrue();
    TVector3 pe_sim;
    if (ele_sim != edm4hep::MCParticle::makeEmpty()) pe_sim = TVector3(ele_sim.getMomentum().x, ele_sim.getMomentum().y, ele_sim.getMomentum().z);

    float q2_rec = ev->Q2();
    float pTmiss_rec = ev->pTmiss().Pt();
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
    if (ev->nmatches == 0) return;

    for (auto& par : ev->particles)
    {
        int det = -1;
        if (par.cluster_high.getObjectID().collectionID == collectionID_BEMC) det = 0;
        if (par.cluster_high.getObjectID().collectionID == collectionID_NEMC) det = 1;
        if (par.cluster_high.getObjectID().collectionID == collectionID_PEMC) det = 2;

        TVector3 mom(par.rec.getMomentum().x, par.rec.getMomentum().y, par.rec.getMomentum().z);
        float ene_high = par.cluster_high.getEnergy();
        TVector3 pos_high(par.cluster_high.getPosition().x, par.cluster_high.getPosition().y, par.cluster_high.getPosition().z);
        float ene_sum = par.ene_cluster_sum;
        TVector3 pos_sum = par.pos_cluster_sum;
        TVector3 pos_trk = par.pos_track;

        h2["Match__nclspertrk_det"]->Fill(par.clusters.size(), det);

        h2["Match__E_det"]->Fill(ene_high, det);
        h2["Match__Etot_det"]->Fill(ene_sum, det);
        h3["Match__eta_phi_det"]->Fill(pos_high.Eta(), pos_high.Phi(), det);
        h3["Match__eta_E_det"]->Fill(pos_high.Eta(), ene_high, det);

        h2["Match__dR_det"]->Fill(pos_trk.DeltaR(pos_high), det);
        h2["Match__dRtot_det"]->Fill(pos_trk.DeltaR(pos_sum), det);

        h3["Match_all__p_E_det"]->Fill(mom.Mag(), ene_high, det);
        h3["Match_all__p_Etot_det"]->Fill(mom.Mag(), ene_sum, det);
        h3["Match_all__p_Ep_det"]->Fill(mom.Mag(), ene_high / mom.Mag(), det);
        h3["Match_all__p_Eptot_det"]->Fill(mom.Mag(), ene_sum / mom.Mag(), det);

        if (par.sim.getGeneratorStatus() == 1 && par.sim.getPDG() == cuts.PDG_Lepton)
        {
            h3["Match_electron__p_E_det"]->Fill(mom.Mag(), ene_high, det);
            h3["Match_electron__p_Etot_det"]->Fill(mom.Mag(), ene_sum, det);
            h3["Match_electron__p_Ep_det"]->Fill(mom.Mag(), ene_high / mom.Mag(), det);
            h3["Match_electron__p_Eptot_det"]->Fill(mom.Mag(), ene_sum / mom.Mag(), det);
        }

    }
}

// *****************************************************************************
void MyAnalysis::AnalyzeDecayVertex()
{

}
