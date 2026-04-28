#include "MyAnalysis.h"

vector<float> logbinning(int nbins, float x1, float x2);
vector<float> binning(int nbins, float x1, float x2);
void reserve_qa_histograms(map<string,TH1*>& h1, map<string,TH2*>& h2, map<string,TH3*>& h3);
void reserve_eff_histograms(map<string,TH1*>& h1, map<string,TH2*>& h2, map<string,TH3*>& h3);
void reserve_res_histograms(map<string,TH1*>& h1, map<string,TH2*>& h2, map<string,TH3*>& h3);
void reserve_match_EMC_histograms(map<string,TH1*>& h1, map<string,TH2*>& h2, map<string,TH3*>& h3);
void reserve_cluster_QA_histograms(map<string,TH1*>& h1, map<string,TH2*>& h2, map<string,TH3*>& h3);

// *****************************************************************************
vector<float> pTbins = binning(100, 0, 5);
vector<float> etabins = binning(100, -10, 10);
vector<float> phibins = binning(100, -TMath::Pi(), TMath::Pi());
vector<float> pTbins_coarse = binning(20, 0, 5);
vector<float> etabins_coarse = binning(20, -10, 10);

vector<float> pbins = binning(100, 0, 10);
vector<float> dRbins = binning(100, 0, 0.1);
vector<float> sdRbins = binning(100, -0.1, 0.1);
vector<float> dRbins_wide = binning(100, 0, 2.0);
vector<float> sdRbins_wide = binning(100, -2.0, 2.0);
vector<float> ecalbins = binning(5, 0, 5);

vector<float> sbins = binning(20, 0, 20);
vector<float> q2bins = logbinning(200, 0.001, 1000.0);
vector<float> ratbins = binning(100, 0, 2);
vector<float> fracbins = binning(100, 0, 1);


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
    reserve_match_EMC_histograms(h1, h2, h3);
    reserve_cluster_QA_histograms(h1, h2, h3);

    for (map<string,TH1*>::const_iterator itr = h1.begin(); itr != h1.end(); ++itr) itr->second->Sumw2();
    for (map<string,TH2*>::const_iterator itr = h2.begin(); itr != h2.end(); ++itr) itr->second->Sumw2();
    for (map<string,TH3*>::const_iterator itr = h3.begin(); itr != h3.end(); ++itr) itr->second->Sumw2();
}

// *****************************************************************************
void reserve_cluster_QA_histograms(map<string,TH1*>& h1, map<string,TH2*>& h2, map<string,TH3*>& h3)
{
    //vector<float> rbins_becal = {};
    vector<float> zbins_necal = binning(108, -4200, -1500);
    //vector<float> zbins_pecal = binning();


}



// *****************************************************************************
void reserve_match_EMC_histograms(map<string,TH1*>& h1, map<string,TH2*>& h2, map<string,TH3*>& h3)
{
    vector<string> prefixes = {"Match_ECAL_", "Match_HCAL_"};
    for (int itype = 0; itype < prefixes.size(); ++itype)
    {
        string prefix = prefixes[itype];
        vector<float> temp_dRbins;
        vector<float> temp_sdRbins;

        if (itype == 0)
        {
            temp_dRbins = dRbins;
            temp_sdRbins = sdRbins;
        }
        else
        {
            temp_dRbins = dRbins_wide;
            temp_sdRbins = sdRbins_wide;
        }

        h2[prefix + "track__nclusters_det"] = new TH2F(TString(prefix + "track__nclusters_det"), ";N_{cluster}/Track", 10, 0, 10, ecalbins.size() - 1, ecalbins[0], ecalbins.back());

        h3[prefix + "track__nclusters_E_det"] = new TH3F(TString(prefix + "track__nclusters_E_det"), ";N_{cluster}/Track;E_{cluster} (GeV)", 10, 0, 10, pbins.size() - 1, pbins[0], pbins.back(), ecalbins.size() - 1, ecalbins[0], ecalbins.back());
        h3[prefix + "track__nclusters_deta_det"] = new TH3F(TString(prefix + "track__nclusters_deta_det"), ";N_{cluster}/Track;#Delta#eta_{trk,cls}", 10, 0, 10, temp_sdRbins.size() - 1, temp_sdRbins[0], temp_sdRbins.back(), ecalbins.size() - 1, ecalbins[0], ecalbins.back());
        h3[prefix + "track__nclusters_dphi_det"] = new TH3F(TString(prefix + "track__nclusters_dphi_det"), ";N_{cluster}/Track;#Delta#phi_{trk,cls}", 10, 0, 10, temp_sdRbins.size() - 1, temp_sdRbins[0], temp_sdRbins.back(), ecalbins.size() - 1, ecalbins[0], ecalbins.back());
        h3[prefix + "track__nclusters_dR_det"] = new TH3F(TString(prefix + "track__nclusters_dR_det"), ";N_{cluster}/Track;#DeltaR_{trk,cls}", 10, 0, 10, temp_dRbins.size() - 1, temp_dRbins[0], temp_dRbins.back(), ecalbins.size() - 1, ecalbins[0], ecalbins.back());

        h2[prefix + "track__p_det"] = new TH2F(TString(prefix + "track__p_det"), ";p_{trk} OR E_{cls} (GeV)", pbins.size() - 1, &pbins[0], ecalbins.size() - 1, &ecalbins[0]);
        h3[prefix + "track__eta_phi_det"] = new TH3F(TString(prefix + "track__eta_phi_det"), ";#eta_{trk,pos};#phi_{trk,pos}", etabins.size() - 1, &etabins[0], phibins.size() - 1, &phibins[0], ecalbins.size() - 1, &ecalbins[0]);
        h3[prefix + "track__eta_p_det"] = new TH3F(TString(prefix + "track__eta_p_det"), ";#eta_{trk,pos};p_{trk} OR E_{cls} (GeV)", etabins.size() - 1, &etabins[0], pbins.size() - 1, &pbins[0], ecalbins.size() - 1, &ecalbins[0]);

        h2[prefix + "track_all__p_det"] = new TH2F(TString(prefix + "track_all__p_det"), ";p_{trk} OR E_{cls} (GeV)", pbins.size() - 1, &pbins[0], ecalbins.size() - 1, &ecalbins[0]);
        h3[prefix + "track_all__eta_phi_det"] = new TH3F(TString(prefix + "track_all__eta_phi_det"), ";#eta_{trk,pos};#phi_{trk,pos}", etabins.size() - 1, &etabins[0], phibins.size() - 1, &phibins[0], ecalbins.size() - 1, &ecalbins[0]);
        h3[prefix + "track_all__eta_p_det"] = new TH3F(TString(prefix + "track_all__eta_p_det"), ";#eta_{trk,pos};p_{trk} OR E_{cls} (GeV)", etabins.size() - 1, &etabins[0], pbins.size() - 1, &pbins[0], ecalbins.size() - 1, &ecalbins[0]);

        h2[prefix + "cluster_high__E_det"] = new TH2F(TString(prefix + "cluster_high__E_det"), ";E_{high-cluster} (GeV)", pbins.size() - 1, &pbins[0], ecalbins.size() - 1, &ecalbins[0]);
        h2[prefix + "cluster_high__dR_det"] = new TH2F(TString(prefix + "cluster_high__dR_det"), ";#DeltaR_{trk,high-cluster}", temp_dRbins.size() - 1, &temp_dRbins[0], ecalbins.size() - 1, &ecalbins[0]);
        h2[prefix + "cluster_high__deta_det"] = new TH2F(TString(prefix + "cluster_high__deta_det"), ";#Delta#eta_{trk,high-cluster}", temp_sdRbins.size() - 1, &temp_sdRbins[0], ecalbins.size() - 1, &ecalbins[0]);
        h2[prefix + "cluster_high__dphi_det"] = new TH2F(TString(prefix + "cluster_high__dphi_det"), ";#Delta#phi_{trk,near-cluster}", temp_sdRbins.size() - 1, &temp_sdRbins[0], ecalbins.size() - 1, &ecalbins[0]);
        h3[prefix + "cluster_high__eta_phi_det"] = new TH3F(TString(prefix + "cluster_high__eta_phi_det"), ";#eta_{high-cluster};#phi_{high-cluster}", etabins.size() - 1, &etabins[0], phibins.size() - 1, &phibins[0], ecalbins.size() - 1, &ecalbins[0]);
        h3[prefix + "cluster_high__eta_E_det"] = new TH3F(TString(prefix + "cluster_high__eta_E_det"), ";#eta_{high-cluster};E_{high-cluster}", etabins.size() - 1, &etabins[0], pbins.size() - 1, &pbins[0], ecalbins.size() - 1, &ecalbins[0]);

        h2[prefix + "cluster_near__E_det"] = new TH2F(TString(prefix + "cluster_near__E_det"), ";E_{near-cluster} (GeV)", pbins.size() - 1, &pbins[0], ecalbins.size() - 1, &ecalbins[0]);
        h2[prefix + "cluster_near__dR_det"] = new TH2F(TString(prefix + "cluster_near__dR_det"), ";#DeltaR_{trk,near-cluster}", temp_dRbins.size() - 1, &temp_dRbins[0], ecalbins.size() - 1, &ecalbins[0]);
        h2[prefix + "cluster_near__deta_det"] = new TH2F(TString(prefix + "cluster_near__deta_det"), ";#Delta#eta_{trk,near-cluster}", temp_sdRbins.size() - 1, &temp_sdRbins[0], ecalbins.size() - 1, &ecalbins[0]);
        h2[prefix + "cluster_near__dphi_det"] = new TH2F(TString(prefix + "cluster_near__dphi_det"), ";#Delta#phi_{trk,near-cluster}", temp_sdRbins.size() - 1, &temp_sdRbins[0], ecalbins.size() - 1, &ecalbins[0]);
        h3[prefix + "cluster_near__eta_phi_det"] = new TH3F(TString(prefix + "cluster_near__eta_phi_det"), ";#eta_{near-cluster};#phi_{near-cluster}", etabins.size() - 1, &etabins[0], phibins.size() - 1, &phibins[0], ecalbins.size() - 1, &ecalbins[0]);
        h3[prefix + "cluster_near__eta_E_det"] = new TH3F(TString(prefix + "cluster_near__eta_E_det"), ";#eta_{near-cluster};E_{near-cluster}", etabins.size() - 1, &etabins[0], pbins.size() - 1, &pbins[0], ecalbins.size() - 1, &ecalbins[0]);

        h2[prefix + "cluster_sum__E_det"] = new TH2F(TString(prefix + "cluster_sum__E_det"), ";E_{sum-cluster} (GeV)", pbins.size() - 1, &pbins[0], ecalbins.size() - 1, &ecalbins[0]);
        h2[prefix + "cluster_sum__dR_det"] = new TH2F(TString(prefix + "cluster_sum__dR_det"), ";#DeltaR_{trk,sum-cluster}", temp_dRbins.size() - 1, &temp_dRbins[0], ecalbins.size() - 1, &ecalbins[0]);
        h2[prefix + "cluster_sum__deta_det"] = new TH2F(TString(prefix + "cluster_sum__deta_det"), ";#Delta#eta_{trk,sum-cluster}", temp_sdRbins.size() - 1, &temp_sdRbins[0], ecalbins.size() - 1, &ecalbins[0]);
        h2[prefix + "cluster_sum__dphi_det"] = new TH2F(TString(prefix + "cluster_sum__dphi_det"), ";#Delta#phi_{trk,near-cluster}", temp_sdRbins.size() - 1, &temp_sdRbins[0], ecalbins.size() - 1, &ecalbins[0]);
        h3[prefix + "cluster_sum__eta_phi_det"] = new TH3F(TString(prefix + "cluster_sum__eta_phi_det"), ";#eta_{sum-cluster};#phi_{sum-cluster}", etabins.size() - 1, &etabins[0], phibins.size() - 1, &phibins[0], ecalbins.size() - 1, &ecalbins[0]);
        h3[prefix + "cluster_sum__eta_E_det"] = new TH3F(TString(prefix + "cluster_sum__eta_E_det"), ";#eta_{sum-cluster};E_{sum-cluster}", etabins.size() - 1, &etabins[0], pbins.size() - 1, &pbins[0], ecalbins.size() - 1, &ecalbins[0]);


        h3[prefix + "electron_high__p_E_det"] = new TH3F(TString(prefix + "electron_high__p_E_det"), ";p_{e} (GeV);E_{high-cluster} (GeV)", pbins.size() - 1, &pbins[0], pbins.size() - 1, &pbins[0], ecalbins.size() - 1, &ecalbins[0]);
        h3[prefix + "electron_high__p_Ep_det"] = new TH3F(TString(prefix + "electron_high__p_Ep_det"), ";p_{e} (GeV);E_{high-cluster}/p_{e}", pbins.size() - 1, &pbins[0], ratbins.size() - 1, &ratbins[0], ecalbins.size() - 1, &ecalbins[0]);
        h3[prefix + "all_high__p_E_det"] = new TH3F(TString(prefix + "all_high__p_E_det"), ";p (GeV);E_{cluster} (GeV)", pbins.size() - 1, &pbins[0], pbins.size() - 1, &pbins[0], ecalbins.size() - 1, &ecalbins[0]);
        h3[prefix + "all_high__p_Ep_det"] = new TH3F(TString(prefix + "all_high__p_Ep_det"), ";p (GeV);E_{cluster}/p", pbins.size() - 1, &pbins[0], ratbins.size() - 1, &ratbins[0], ecalbins.size() - 1, &ecalbins[0]);

        h3[prefix + "electron_near__p_E_det"] = new TH3F(TString(prefix + "electron_near__p_E_det"), ";p_{e} (GeV);E_{near-cluster} (GeV)", pbins.size() - 1, &pbins[0], pbins.size() - 1, &pbins[0], ecalbins.size() - 1, &ecalbins[0]);
        h3[prefix + "electron_near__p_Ep_det"] = new TH3F(TString(prefix + "electron_near__p_Ep_det"), ";p_{e} (GeV);E_{near-cluster}/p_{e}", pbins.size() - 1, &pbins[0], ratbins.size() - 1, &ratbins[0], ecalbins.size() - 1, &ecalbins[0]);
        h3[prefix + "all_near__p_E_det"] = new TH3F(TString(prefix + "all_near__p_E_det"), ";p (GeV);E_{cluster} (GeV)", pbins.size() - 1, &pbins[0], pbins.size() - 1, &pbins[0], ecalbins.size() - 1, &ecalbins[0]);
        h3[prefix + "all_near__p_Ep_det"] = new TH3F(TString(prefix + "all_near__p_Ep_det"), ";p (GeV);E_{cluster}/p", pbins.size() - 1, &pbins[0], ratbins.size() - 1, &ratbins[0], ecalbins.size() - 1, &ecalbins[0]);

        h3[prefix + "electron_sum__p_E_det"] = new TH3F(TString(prefix + "electron_sum__p_E_det"), ";p_{e} (GeV);E_{sum-cluster} (GeV)", pbins.size() - 1, &pbins[0], pbins.size() - 1, &pbins[0], ecalbins.size() - 1, &ecalbins[0]);
        h3[prefix + "electron_sum__p_Ep_det"] = new TH3F(TString(prefix + "electron_sum__p_Ep_det"), ";p_{e} (GeV);E_{sum-cluster}/p_{e}", pbins.size() - 1, &pbins[0], ratbins.size() - 1, &ratbins[0], ecalbins.size() - 1, &ecalbins[0]);
        h3[prefix + "all_sum__p_E_det"] = new TH3F(TString(prefix + "all_sum__p_E_det"), ";p (GeV);E_{cluster} (GeV)", pbins.size() - 1, &pbins[0], pbins.size() - 1, &pbins[0], ecalbins.size() - 1, &ecalbins[0]);
        h3[prefix + "all_sum__p_Ep_det"] = new TH3F(TString(prefix + "all_sum__p_Ep_det"), ";p (GeV);E_{cluster}/p", pbins.size() - 1, &pbins[0], ratbins.size() - 1, &ratbins[0], ecalbins.size() - 1, &ecalbins[0]);

    }

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

    h1["QA_sim_electron__Efrac"] = new TH1F("QA_sim_electron__Efrac", ";E_{ele}/E_{beam}", fracbins.size() - 1, &fracbins[0]);
    h1["QA_sim_ALP__Efrac"] = new TH1F("QA_sim_ALP__Efrac", ";E_{ALP}/E_{beam}", fracbins.size() - 1, &fracbins[0]);

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
