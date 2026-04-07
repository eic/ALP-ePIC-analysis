#include "MyAnalysis.h"

vector<float> logbinning(int nbins, float x1, float x2);
vector<float> binning(int nbins, float x1, float x2);
void reserve_qa_histograms(map<string,TH1*>& h1, map<string,TH2*>& h2, map<string,TH3*>& h3);
void reserve_eff_histograms(map<string,TH1*>& h1, map<string,TH2*>& h2, map<string,TH3*>& h3);
void reserve_res_histograms(map<string,TH1*>& h1, map<string,TH2*>& h2, map<string,TH3*>& h3);
void reserve_matching_histograms(map<string,TH1*>& h1, map<string,TH2*>& h2, map<string,TH3*>& h3);

// *****************************************************************************
vector<float> pTbins = binning(100, 0, 5);
vector<float> etabins = binning(100, -10, 10);
vector<float> phibins = binning(100, -TMath::Pi(), TMath::Pi());
vector<float> pTbins_coarse = binning(20, 0, 5);
vector<float> etabins_coarse = binning(20, -10, 10);

vector<float> pbins = binning(100, 0, 10);
vector<float> dRbins = binning(100, 0, 0.1);
vector<float> ecalbins = binning(5, 0, 5);

vector<float> sbins = binning(10, 0, 10);
vector<float> q2bins = logbinning(200, 0.001, 1000.0);
vector<float> ratbins = binning(100, 0, 2);


// *****************************************************************************
void MyAnalysis::ReserveHistograms()
{
    h1.clear();
    h2.clear();
    h3.clear();
    mOutFile->cd();

    // Event counter
    h1["event__stage"] = new TH1F("event__stage", "", 20, 0, 20);

    // QA histograms
    reserve_qa_histograms(h1, h2, h3);
    reserve_eff_histograms(h1, h2, h3);
    reserve_res_histograms(h1, h2, h3);
    reserve_matching_histograms(h1, h2, h3);

    for (map<string,TH1*>::const_iterator itr = h1.begin(); itr != h1.end(); ++itr) itr->second->Sumw2();
    for (map<string,TH2*>::const_iterator itr = h2.begin(); itr != h2.end(); ++itr) itr->second->Sumw2();
    for (map<string,TH3*>::const_iterator itr = h3.begin(); itr != h3.end(); ++itr) itr->second->Sumw2();
}

// *****************************************************************************

// *****************************************************************************
void reserve_matching_histograms(map<string,TH1*>& h1, map<string,TH2*>& h2, map<string,TH3*>& h3)
{
    h2["Match__nclspertrk_det"] = new TH2F("Match__nclspertrk_det", ";N_{cluster}/Track", 10, 0, 10, 5, 0, 5);
    h2["Match__E_det"] = new TH2F("Match__E_det", ";E_{cluster} (GeV)", pbins.size() - 1, &pbins[0], ecalbins.size() - 1, &ecalbins[0]);
    h2["Match__Etot_det"] = new TH2F("Match__Etot_det", ";#SigmaE_{cluster} (GeV)/Track", pbins.size() - 1, &pbins[0], ecalbins.size() - 1, &ecalbins[0]);
    h3["Match__eta_phi_det"] = new TH3F("Match__eta_phi_det", ";#eta_{cluster};#phi_{cluster}", etabins.size() - 1, &etabins[0], phibins.size() - 1, &phibins[0], ecalbins.size() - 1, &ecalbins[0]);
    h3["Match__eta_E_det"] = new TH3F("Match__eta_E_det", ";#eta_{cluster};E_{cluster}", etabins.size() - 1, &etabins[0], pbins.size() - 1, &pbins[0], ecalbins.size() - 1, &ecalbins[0]);

    h2["Match__dR_det"] = new TH2F("Match__dR_det", ";#DeltaR_{trk,high-cluster} (mm)", dRbins.size() - 1, &dRbins[0], ecalbins.size() - 1, &ecalbins[0]);
    h2["Match__dRtot_det"] = new TH2F("Match__dRtot_det", ";#DeltaR_{trk,sum-cluster} (mm)", dRbins.size() - 1, &dRbins[0], ecalbins.size() - 1, &ecalbins[0]);

    h3["Match_electron__p_E_det"] = new TH3F("Match_electron__p_E_det", ";p_{e} (GeV);high-E_{cluster} (GeV)", pbins.size() - 1, &pbins[0], pbins.size() - 1, &pbins[0], ecalbins.size() - 1, &ecalbins[0]);
    h3["Match_electron__p_Etot_det"] = new TH3F("Match_electron__p_Etot_det", ";p_{e} (GeV);#SigmaE_{cluster} (GeV)", pbins.size() - 1, &pbins[0], pbins.size() - 1, &pbins[0], ecalbins.size() - 1, &ecalbins[0]);
    h3["Match_electron__p_Ep_det"] = new TH3F("Match_electron__p_Ep_det", ";p_{e} (GeV);high-E_{cluster}/p_{e}", pbins.size() - 1, &pbins[0], ratbins.size() - 1, &ratbins[0], ecalbins.size() - 1, &ecalbins[0]);
    h3["Match_electron__p_Eptot_det"] = new TH3F("Match_electron__p_Eptot_det", ";p_{e} (GeV);#SigmaE_{cluster}/p_{e}", pbins.size() - 1, &pbins[0], ratbins.size() - 1, &ratbins[0], ecalbins.size() - 1, &ecalbins[0]);

    h3["Match_all__p_E_det"] = new TH3F("Match_all__p_E_det", ";p (GeV);high-E_{cluster} (GeV)", pbins.size() - 1, &pbins[0], pbins.size() - 1, &pbins[0], ecalbins.size() - 1, &ecalbins[0]);
    h3["Match_all__p_Etot_det"] = new TH3F("Match_all__p_Etot_det", ";p (GeV);#SigmaE_{cluster} (GeV)", pbins.size() - 1, &pbins[0], pbins.size() - 1, &pbins[0], ecalbins.size() - 1, &ecalbins[0]);
    h3["Match_all__p_Ep_det"] = new TH3F("Match_all__p_Ep_det", ";p (GeV);high-E_{cluster}/p", pbins.size() - 1, &pbins[0], ratbins.size() - 1, &ratbins[0], ecalbins.size() - 1, &ecalbins[0]);
    h3["Match_all__p_Eptot_det"] = new TH3F("Match_all__p_Eptot_det", ";p (GeV);#SigmaE_{cluster}/p", pbins.size() - 1, &pbins[0], ratbins.size() - 1, &ratbins[0], ecalbins.size() - 1, &ecalbins[0]);
}


// *****************************************************************************
void reserve_res_histograms(map<string,TH1*>& h1, map<string,TH2*>& h2, map<string,TH3*>& h3)
{
    h2["Res__Q2true_Q2"] = new TH2F("Res__Q2true_Q2", ";Generated Q^{2} (GeV^{2});Reconstructed Q^{2} (GeV^{2})", q2bins.size() - 1, &q2bins[0], q2bins.size() - 1, &q2bins[0]);
    h2["Res__pTmisstrue_pTmiss"] = new TH2F("Res__pTmisstrue_pTmiss", ";Generated p_{T,miss} (GeV);Reconstructed p_{T,miss} (GeV)", pTbins.size() - 1, &pTbins[0], pTbins.size() - 1, &pTbins[0]);
    h2["Res__pTetrue_pTe"] = new TH2F("Res__pTetrue_pTe", ";Generated p_{T,e} (GeV);Reconstructed p_{T,e} (GeV)", pTbins.size() - 1, &pTbins[0], pTbins.size() - 1, &pTbins[0]);
    h2["Res__etaetrue_etae"] = new TH2F("Res__etaetrue_etae", ";Generated #eta_{e};Reconstructed #eta_{e}", etabins.size() - 1, &etabins[0], etabins.size() - 1, &etabins[0]);

    h2["Res__Q2_ratio"] = new TH2F("Res__Q2_ratio", ";Generated Q^{2} (GeV^{2});Reconstructed / Generated", q2bins.size() - 1, &q2bins[0], ratbins.size() - 1, &ratbins[0]);
    h2["Res__pTmiss_ratio"] = new TH2F("Res__pTmiss_ratio", ";Generated p_{T,miss} (GeV);Reconstructed / Generated", pTbins.size() - 1, &pTbins[0], ratbins.size() - 1, &ratbins[0]);
    h2["Res__pTe_ratio"] = new TH2F("Res__pTe_ratio", ";Generated p_{T,e} (GeV);Reconstructed / Generated", pTbins.size() - 1, &pTbins[0], ratbins.size() - 1, &ratbins[0]);
    h2["Res__etae_ratio"] = new TH2F("Res__etae_ratio", ";Generated #eta_{e};Reconstructed / Generated", etabins.size() - 1, &etabins[0], ratbins.size() - 1, &ratbins[0]);

    h3["Res__pTe_etae_pTeratio"] = new TH3F("Res__pTe_etae_pTeratio", ";Generated p_{T,e} (GeV);Generated #eta_{e};Reconstructed / Generated", pTbins.size() - 1, &pTbins[0], etabins_coarse.size() - 1, &etabins_coarse[0], ratbins.size() - 1, &ratbins[0]);
    h3["Res__etae_pTe__etaeratio"] = new TH3F("Res__etae_pTe__etaeratio", ";Generated #eta_{e};Generated p_{T,e} (GeV);Reconstructed / Generated", etabins.size() - 1, &etabins[0], pTbins_coarse.size() - 1, &pTbins_coarse[0], ratbins.size() - 1, &ratbins[0]);
}

// *****************************************************************************
void reserve_eff_histograms(map<string,TH1*>& h1, map<string,TH2*>& h2, map<string,TH3*>& h3)
{
    h2["Eff__Q2_stage"] = new TH2F("Eff__Q2_stage", ";Generated Q^{2} (GeV^{2})", q2bins.size() - 1, &q2bins[0], sbins.size() - 1, &sbins[0]);
    h2["Eff__pTmiss_stage"] = new TH2F("Eff__pTmiss_stage", ";Generated p_{T,miss} (GeV)", pTbins.size() - 1, &pTbins[0], sbins.size() - 1, &sbins[0]);
    h2["Eff__pTe_stage"] = new TH2F("Eff__pTe_stage", ";Generated p_{T,e} (GeV)", pTbins.size() - 1, &pTbins[0], sbins.size() - 1, &sbins[0]);
    h2["Eff__etae_stage"] = new TH2F("Eff__etae_stage", ";Generated #eta_{e}", etabins.size() - 1, &etabins[0], sbins.size() - 1, &sbins[0]);

    h3["Eff__Q2_pTmiss_stage"] = new TH3F("Eff__Q2_pTmiss_stage", ";Generated Q^{2} (GeV^{2});Generated p_{T,miss} (GeV)", q2bins.size() - 1, &q2bins[0], pTbins.size() - 1, &pTbins[0], sbins.size() - 1, &sbins[0]);
    h3["Eff__Q2_pTe_stage"] = new TH3F("Eff__Q2_pTe_stage", ";Generated Q^{2} (GeV^{2});Generated p_{T,e} (GeV)", q2bins.size() - 1, &q2bins[0], pTbins.size() - 1, &pTbins[0], sbins.size() - 1, &sbins[0]);
    h3["Eff__Q2_etae_stage"] = new TH3F("Eff__Q2_etae_stage", ";Generated Q^{2} (GeV^{2});Generated #eta_{e}", q2bins.size() - 1, &q2bins[0], etabins.size() - 1, &etabins[0], sbins.size() - 1, &sbins[0]);
    h3["Eff__pTmiss_pTe_stage"] = new TH3F("Eff__pTmiss_pTe_stage", ";Generated p_{T,miss} (GeV);Generated p_{T,e} (GeV)", pTbins.size() - 1, &pTbins[0], pTbins.size() - 1, &pTbins[0], sbins.size() - 1, &sbins[0]);
    h3["Eff__pTmiss_etae_stage"] = new TH3F("Eff__pTmiss_etae_stage", ";Generated p_{T,miss} (GeV);Generated #eta_{e}", pTbins.size() - 1, &pTbins[0], etabins.size() - 1, &etabins[0], sbins.size() - 1, &sbins[0]);
    h3["Eff__etae_pTe_stage"] = new TH3F("Eff__etae_pTe_stage", ";Generated #eta_{e};Generated p_{T,e} (GeV)", etabins.size() - 1, &etabins[0], pTbins.size() - 1, &pTbins[0], sbins.size() - 1, &sbins[0]);
}

// *****************************************************************************
void reserve_qa_histograms(map<string,TH1*>& h1, map<string,TH2*>& h2, map<string,TH3*>& h3)
{
    // QA Plots (Sim)
    h1["QA_sim__Q2"] = new TH1F("QA_sim__Q2", ";Generated Q^{2} (GeV^{2})", q2bins.size() - 1, &q2bins[0]);
    h1["QA_sim__pTmiss"] = new TH1F("QA_sim__pTmiss", ";Generated p_{T,miss} (GeV)", pTbins.size() - 1, &pTbins[0]);
    h1["QA_sim__pTe"] = new TH1F("QA_sim__pTe", ";Generated p_{T,e} (GeV)", pTbins.size() - 1, &pTbins[0]);
    h1["QA_sim__etae"] = new TH1F("QA_sim__etae", ";Generated #eta_{e}", etabins.size() - 1, &etabins[0]);

    h2["QA_sim__Q2_pTmiss"] = new TH2F("QA_sim__Q2_pTmiss", ";Generated Q^{2} (GeV^{2});Generated p_{T,miss} (GeV)", q2bins.size() - 1, &q2bins[0], pTbins.size() - 1, &pTbins[0]);
    h2["QA_sim__Q2_pTe"] = new TH2F("QA_sim__Q2_pTe", ";Generated Q^{2} (GeV^{2});Generated p_{T,e} (GeV)", q2bins.size() - 1, &q2bins[0], pTbins.size() - 1, &pTbins[0]);
    h2["QA_sim__Q2_etae"] = new TH2F("QA_sim__Q2_etae", ";Generated Q^{2} (GeV^{2});Generated #eta_{e}", q2bins.size() - 1, &q2bins[0], etabins.size() - 1, &etabins[0]);
    h2["QA_sim__pTmiss_pTe"] = new TH2F("QA_sim__pTmiss_pTe", ";Generated p_{T,miss} (GeV);Generated p_{T,e} (GeV)", pTbins.size() - 1, &pTbins[0], pTbins.size() - 1, &pTbins[0]);
    h2["QA_sim__pTmiss_etae"] = new TH2F("QA_sim__pTmiss_etae", ";Generated p_{T,miss} (GeV);Generated #eta_{e}", pTbins.size() - 1, &pTbins[0], etabins.size() - 1, &etabins[0]);
    h2["QA_sim__etae_pTe"] = new TH2F("QA_sim__etae_pTe", ";Generated #eta_{e};Generated p_{T,e} (GeV)", etabins.size() - 1, &etabins[0], pTbins.size() - 1, &pTbins[0]);

    // QA Plots (Rec)
    h1["QA_rec__Q2"] = new TH1F("QA_rec__Q2", ";Reconstructed Q^{2} (GeV^{2})", q2bins.size() - 1, &q2bins[0]);
    h1["QA_rec__pTmiss"] = new TH1F("QA_rec__pTmiss", ";Reconstructed p_{T,miss} (GeV)", pTbins.size() - 1, &pTbins[0]);
    h1["QA_rec__pTe"] = new TH1F("QA_rec__pTe", ";Reconstructed p_{T,e} (GeV)", pTbins.size() - 1, &pTbins[0]);
    h1["QA_rec__etae"] = new TH1F("QA_rec__etae", ";Reconstructed #eta_{e}", etabins.size() - 1, &etabins[0]);

    h2["QA_rec__Q2_pTmiss"] = new TH2F("QA_rec__Q2_pTmiss", ";Reconstructed Q^{2} (GeV^{2});Reconstructed p_{T,miss} (GeV)", q2bins.size() - 1, &q2bins[0], pTbins.size() - 1, &pTbins[0]);
    h2["QA_rec__Q2_pTe"] = new TH2F("QA_rec__Q2_pTe", ";Reconstructed Q^{2} (GeV^{2});Reconstructed p_{T,e} (GeV)", q2bins.size() - 1, &q2bins[0], pTbins.size() - 1, &pTbins[0]);
    h2["QA_rec__Q2_etae"] = new TH2F("QA_rec__Q2_etae", ";Reconstructed Q^{2} (GeV^{2});Reconstructed #eta_{e}", q2bins.size() - 1, &q2bins[0], etabins.size() - 1, &etabins[0]);
    h2["QA_rec__pTmiss_pTe"] = new TH2F("QA_rec__pTmiss_pTe", ";Reconstructed p_{T,miss} (GeV);Reconstructed p_{T,e} (GeV)", pTbins.size() - 1, &pTbins[0], pTbins.size() - 1, &pTbins[0]);
    h2["QA_rec__pTmiss_etae"] = new TH2F("QA_rec__pTmiss_etae", ";Reconstructed p_{T,miss} (GeV);Reconstructed #eta_{e}", pTbins.size() - 1, &pTbins[0], etabins.size() - 1, &etabins[0]);
    h2["QA_rec__etae_pTe"] = new TH2F("QA_rec__etae_pTe", ";Reconstructed #eta_{e};Reconstructed p_{T,e} (GeV)", etabins.size() - 1, &etabins[0], pTbins.size() - 1, &pTbins[0]);
}








// *****************************************************************************
vector<float> logbinning(int nbins, float x1, float x2)
{
    vector<float> x;
    for (int i = 0; i <= nbins; ++i)
    {
        float lx1 = log10(x1);
        float lx2 = log10(x2);
        float dlx = (lx2 - lx1)/float(nbins);
        x.push_back(pow(10, lx1 + float(i) * dlx));
    }
    return x;
}

// *****************************************************************************
vector<float> binning(int nbins, float x1, float x2)
{
    vector<float> x;
    for (int i = 0; i <= nbins; ++i) x.push_back(x1 + float(i) / float(nbins) * (x2 - x1));
    return x;
}
