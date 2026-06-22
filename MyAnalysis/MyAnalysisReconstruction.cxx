#include "MyAnalysis.h"

#include <algorithm>

#include "TVector3.h"

#include "edm4eic/ReconstructedParticle.h"

// Check definitions.xml and make sure these values are correct in 10 years
#define BEMC_SYSTEM_ID 101
#define NEMC_SYSTEM_ID 103
#define PEMC_SYSTEM_ID 102

#define BHCAL_SYSTEM_ID 111
#define NHCAL_SYSTEM_ID 113
#define PHCAL_SYSTEM_ID 116

const vector<int> TRACK_HIT_BARREL_DETECTOR_IDS = {59, 60, 61, 62, 63, 64, 65, 66, 67, 31, 32, 33, 90, 91, 92};
const vector<int> TRACK_HIT_NEGATIVE_DETECTOR_IDS = {68, 69, 70, 71, 72, 73, 74, 75, 76, 34, 35, 36, 131, 132};
const vector<int> TRACK_HIT_POSITIVE_DETECTOR_IDS = {77, 78, 79, 80, 81, 82, 83, 37, 38, 39, 120, 121, 122};



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

/*bool MyAnalysis::ClusterAndTrackInfo(){

    //just to be safe!!
    ev->bdt_RP = 0;
    ev->bdt_ZDC = 0;
    ev->bdt_b0 = 0;

    if(ev->particles_rec.size() == 0){
        return true;
    }
    if(par.bdt_clusters.size() == 0){
        //look at if there are any clusters!!!!
        return true;
    }
    if(par.tracks.size() == 0){
        //information about the tracks!!!
        return true;
    }

    ev->bdt_RP = 0;
    ev->bdt_ZDC = 0;
    ev->bdt_b0 = 0;

    //how do I make sure that I grab the right elements??? for the right clusters???
    return true;
}
*/

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

bool MyAnalysis::WriteToBdtTree()
{
    if(ev->particles_rec.size() == 0){
        //if nothing is reconstructed, continue!!! Avoid seg faults!!
        return true;
    }
    //###################### Write to Branches of the new flat TTree format!!!################
    //AW 20260604
    //make special cases for when it's the signal and when it's the background
    ev->bdt_nev = nev; //initialize with some value?
    ev->sig_bkgd_label = -1;
    cout << "nev value" << nev << endl;
    ev->bdt_elec_e = 0;
    ev->bdt_pt = 0;
    ev->bdt_eta = 0;
    ev->bdt_elec_beam_rat = 0;
    ev->bdt_pt_miss = 0;
    ev->bdt_p = 0;
    ev->bdt_phi = 0;
    ev->bdt_q2 = 0;
    ev->bdt_angle = 0;
    ev->bdt_mult = ev->particles_rec.size();
    ev->bdt_RP = 0;
    ev->bdt_ZDC = 0;
    ev->bdt_b0 = 0;
    //AW 20260622 newest BDT variables!!!
    ev->bdt_dr = 0; //
    ev->bdt_e_pz = 0; // done
    ev->bdt_et = 0;
    ev->bdt_pperp = 0; // perpindicular component of the sum of all of the vectors!!
    ev->bdt_et_pperp = 0;
    ev->bdt_dphi = 0;
    ev->bdt_dphi_avg = 0;

    TVector3 bdt_particle;
    TVector3 bdt_beam;
    TVector3 bdt_alp = ev->pmiss; //this should be fine, does this make sense??
    float particle_mass = 0;
    float beam_mass = 0;
    float smallest_phi = 1000;

    //find the maximum pt rec particle!!! 2 cases!!
    /*
    if((file_type==0)||(file_type==1)){
        //aem_axem inclusive case
        ev->sig_bkgd_label = 1; //this is the signal!!
        bdt_particle = ev->pele; //already did these!!!
        bdt_beam = ev->pbeam;
        particle_mass = 0.000511; //Mass in GeV
        beam_mass = 0.000511;
        TVector3 temp;
        int elec_index = -1;
        int par_count = 0;

        for(auto &par : ev->particles_rec){
            temp = TVector3(par.getMomentum().x,par.getMomentum().y,par.getMomentum().z);
            ev->bdt_dphi_avg+= bdt_alp.DeltaPhi(temp);
            temp.Clear();
            par_count++;
            if(par.getPDG() == 11){elec_index = par_count;}
        }

        if((par.getPDG() == 11) && (par.clusters_size() > 0)){
                for(std::vector< edm4hep::Cluster >::const_iterator itr = par.clusters_begin(); itr != par.clusters_end(); ++itr){
                    ev->bdt_e_pz += (itr.getEnergy()*(1-TMath::Cos(temp.Theta())));
                }
            }
        if(par.clusters_size() > 0){
                //statement for if there's no clusters!!!

        }
    }
    */

    if((file_type == 2) || (file_type==3) || (file_type==0) || (file_type==1)){
        //find the highest pt electron for the event!!
        int max_index = 0;
        float max,pt;
        max = 0;
        pt = 0;
        //ev->sig_bkgd_label = 0; //This is the background label!!

        ev->sig_bkgd_label = ((file_type==0) || (file_type==1)) ? 1 : 0; // 1 = signal, 0 = background;

        TVector3 temp;
        TVector3 temp_sum = TVector3(0,0,0);

        float dphi = 0;

        for(int i =0;i<ev->particles_rec.size();i++){
            //if it falls into the low Q^2 tagger, just ignore it!!!
            if(ev->particles[i].is_track_tagger == true){continue;}

            temp = TVector3(ev->particles_rec[i].getMomentum().x,ev->particles_rec[i].getMomentum().y,ev->particles_rec[i].getMomentum().z);
            ev->bdt_dphi_avg += abs(bdt_alp.DeltaPhi(temp)); // take the average of the absolute value of all of them??
            pt = TMath::Sq(ev->particles_rec[i].getMomentum().x)+TMath::Sq(ev->particles_rec[i].getMomentum().y);//this may be a funciton??

            temp_sum = temp_sum + temp; // sum for the bdt_pperp

            if((ev->particles_rec[i].getPDG() == 11) && (pt > max)){
                max = pt; // index of the max!
                max_index = i;
            }

            dphi = bdt_alp.DeltaPhi(temp);

            if(dphi < smallest_phi){smallest_phi = dphi;}

            //getting the sum of ALL energy deposits in the calorimeter for reconstructed particles???
            if(ev->particles_rec[i].clusters_size() > 0){
                for(vector<edm4eic::Cluster>::const_iterator itr = ev->particles_rec[i].clusters_begin(); itr != ev->particles_rec[i].clusters_end(); ++itr){
                    ev->bdt_et += ((*itr).getEnergy()*TMath::Sin(temp.Theta()));
                }
            }
            if(ev->particles_rec[i].clusters_size() == 0){
                //if there's no cluster??? Should I do this? Similar scenario?
                ev->bdt_et = (ev->particles_rec[i].getEnergy()*TMath::Sin(temp.Theta()));
            }

            temp.Clear();
        }

        ev->bdt_pperp = temp_sum.Perp();

        TVector3 elec_high;
        TVector3 not_elec;

        float beam_temp = 0;

        //get the electron beam!
        for (auto& par : ev->particles_sim){
            if (par.getGeneratorStatus() == 4 && par.getPDG() != 11)
            {   //want to get the beam!!! Honestly I don't know if this even makes sense....
                not_elec = TVector3(par.getMomentum().x,par.getMomentum().y,par.getMomentum().z);
                beam_temp = par.getMass();
            }
            if(par.getGeneratorStatus() == 4 && par.getPDG() == 11){
                elec_high = TVector3(par.getMomentum().x,par.getMomentum().y,par.getMomentum().z);
            }
        }

        particle_mass = ev->particles_rec[max_index].getMass();    
        bdt_beam = (ev->particles_rec[max_index].getPDG() == 11) ? elec_high : not_elec;
        beam_mass = (ev->particles_rec[max_index].getPDG() == 11) ? 0.000511 : beam_temp; // AW 20260618 new
        bdt_particle = TVector3(ev->particles_rec[max_index].getMomentum().x,ev->particles_rec[max_index].getMomentum().y,ev->particles_rec[max_index].getMomentum().z); // just for now, syntax is wrong!!
    
        //use max pt elec index, already selected for the electron
        if(ev->particles_rec[max_index].clusters_size() > 0){
            for(vector< edm4eic::Cluster >::const_iterator itr = ev->particles_rec[max_index].clusters_begin(); itr != ev->particles_rec[max_index].clusters_end(); ++itr){
                ev->bdt_e_pz += ((*itr).getEnergy()*(1-TMath::Cos(bdt_particle.Theta())));
            }
            ev->bdt_e_pz = ev->bdt_e_pz - bdt_particle.Pz();
        }
        if(ev->particles_rec[max_index].clusters_size() == 0){
            ev->bdt_e_pz = (ev->particles_rec[max_index].getEnergy()*(1-TMath::Cos(bdt_particle.Theta())));
            //or alternatively just bdt_particle.E - bdt_particle.Pz() ????
            ev->bdt_e_pz = ev->bdt_e_pz - bdt_particle.Pz();
        }

        elec_high.Clear();
        not_elec.Clear();
    }

    if(((bdt_particle.Mag() > 0.5) && (abs(bdt_particle.Eta()) < 4)) || (file_type == 3)){ //change from the bdt thing!! use from the rec or sim list of particles????
        //MAKE NO SELECTION CUTS FOR NOW!!
        //should I make the same selection cuts on the qed???
        ev->bdt_elec_e = TMath::Sqrt(TMath::Sq(bdt_particle.Mag()) + TMath::Sq(particle_mass)); // AW 20260618
        ev->bdt_pt = bdt_particle.Pt();
        ev->bdt_eta = bdt_particle.Eta();
        ev->bdt_elec_beam_rat = (ev->bdt_elec_e)/(TMath::Sqrt(TMath::Sq(bdt_beam.Mag()) + TMath::Sq(beam_mass))); // AW 20260618
        ev->bdt_pt_miss = bdt_alp.Pt(); // this is a little goofy lol
        ev->bdt_p = TMath::Sqrt(TMath::Sq(bdt_particle.Px())+TMath::Sq(bdt_particle.Py())+TMath::Sq(bdt_particle.Pz())); 
        ev->bdt_phi = bdt_particle.Phi();
        ev->bdt_q2 = 2 * ev->bdt_elec_e * TMath::Sqrt(TMath::Sq(bdt_beam.Mag()) + TMath::Sq(beam_mass)) * (1.0 - cos(bdt_beam.Theta() - bdt_particle.Theta()));;
        ev->bdt_angle = TMath::Pi()-bdt_particle.Theta(); //opening angle between the beam and the electron ,,,, just think about it lol
        ev->bdt_RP = 0; // detector bdt variables
        ev->bdt_ZDC = 0;
        ev->bdt_b0 = 0;
        
        //AW 20260622 new variables for BDT
        ev->bdt_dr = bdt_alp.DeltaR(bdt_particle);
        //ev->bdt_e_pz = 0; // added earlier
        //ev->bdt_et = 0; 
        //ev->bdt_pperp = 0;
        ev->bdt_et_pperp = ev->bdt_pperp/TMath::Sqrt(ev->bdt_et);
        ev->bdt_dphi = smallest_phi; // think about this one??
        ev->bdt_dphi_avg = (ev->bdt_dphi_avg)/(ev->particles_rec.size());
    }
    else{
        //AKA it doesn't fall within the detector acceptances!!!
        return true;
    }

    bdtTree->Fill();

    //########################################################################################
    //Already made the variables here that I want to use!!!
    //fill them into their 1D histograms!!!
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


    if(file_type == 2){ //DIS kinematics study!!!
        TVector3 dis_particle;
        for(int i = 0;i<ev->particles_rec.size();i++){
            //fine for now??? More values later ig?
            dis_particle = TVector3(ev->particles_rec[i].getMomentum().x,ev->particles_rec[i].getMomentum().y,ev->particles_rec[i].getMomentum().z); // establish the particle,
            h1["dis_e"]->Fill(TMath::Sqrt(TMath::Sq(dis_particle.Mag()) + TMath::Sq(ev->particles_rec[i].getMass())));
            h1["dis_pt"]->Fill(dis_particle.Pt());
            h1["dis_eta"]->Fill(dis_particle.Eta());
            h1["dis_p"]->Fill(TMath::Sqrt(TMath::Sq(dis_particle.Px())+TMath::Sq(dis_particle.Py())+TMath::Sq(dis_particle.Pz())));
            h1["dis_phi"]->Fill(dis_particle.Phi());
            //should I also do a histogram for the pdg of the reconstructed particles???
            dis_particle.Clear();
        }
        
        TVector3 dis_electron;
        int dis_elec_count = 0;

        for(auto& par : ev->particles){
            if(par.sim.getPDG() == 11 && par.sim.getGeneratorStatus() == 1){ 
                //what if there's more than one electron? which one should I pick?
                dis_elec_count++;
                cout << "DIS electron count:  " << dis_elec_count << endl;                
                dis_electron = TVector3(par.rec.getMomentum().x, par.rec.getMomentum().y, par.rec.getMomentum().z);
                h1["dis_elec_e"]->Fill(TMath::Sqrt(TMath::Sq(dis_electron.Mag()) + TMath::Sq(par.rec.getMass())));
                h1["dis_elec_pt"]->Fill(dis_electron.Pt());
                h1["dis_elec_eta"]->Fill(dis_electron.Eta());
                h1["dis_elec_beam_rat"]->Fill(TMath::Sqrt(TMath::Sq(dis_electron.Mag()) + TMath::Sq(par.rec.getMass()))/TMath::Sqrt(TMath::Sq(ev->pbeam.Mag()) + TMath::Sq(0.000511))); //do I need to do this one?
                //h1["dis_elec_pt_miss"]->Fill(); //what about this one?
                h1["dis_elec_p"]->Fill(TMath::Sqrt(TMath::Sq(dis_electron.Px())+TMath::Sq(dis_electron.Py())+TMath::Sq(dis_electron.Pz())));
                h1["dis_elec_phi"]->Fill(dis_electron.Phi());
                //slightly more sus about this one?
                h1["dis_elec_q2"]->Fill(2 * TMath::Sqrt(TMath::Sq(dis_electron.Mag()) + TMath::Sq(par.rec.getMass())) * TMath::Sqrt(TMath::Sq(ev->pbeam.Mag()) + TMath::Sq(0.000511)) * (1.0 - cos(ev->pbeam.Theta() - dis_electron.Theta()))); //should I compare to a ion beam or the electron beam???
                h1["dis_elec_angle"]->Fill(TMath::Pi()-dis_electron.Theta()); //same???
                dis_electron.Clear();
            }
        }
    }

    h1["bdt_dr"]->Fill(ev->bdt_dr);
    h1["bdt_e_pz"]->Fill(ev->bdt_e_pz);
    h1["bdt_et"]->Fill(ev->bdt_et);
    h1["bdt_pperp"]->Fill(ev->bdt_pperp);
    h1["bdt_et_pperp"]->Fill(ev->bdt_et_pperp);
    h1["bdt_dphi"]->Fill(ev->bdt_dphi);
    h1["bdt_dphi_avg"]->Fill(ev->bdt_dphi_avg);

    //########################################################################################
    return true;
}

