//____________________________________________________________________________..
//
// This is a template for a Fun4All SubsysReco module with all methods from the
// $OFFLINE_MAIN/include/fun4all/SubsysReco.h baseclass
// You do not have to implement all of them, you can just remove unused methods
// here and in EM_CALO.h.
//
// EM_CALO(const std::string &name = "EM_CALO")
// everything is keyed to EM_CALO, duplicate names do work but it makes
// e.g. finding culprits in logs difficult or getting a pointer to the module
// from the command line
//
// EM_CALO::~EM_CALO()
// this is called when the Fun4AllServer is deleted at the end of running. Be
// mindful what you delete - you do loose ownership of object you put on the node tree
//
// int EM_CALO::Init(PHCompositeNode *topNode)
// This method is called when the module is registered with the Fun4AllServer. You
// can create historgrams here or put objects on the node tree but be aware that
// modules which haven't been registered yet did not put antyhing on the node tree
//
// int EM_CALO::InitRun(PHCompositeNode *topNode)
// This method is called when the first event is read (or generated). At
// this point the run number is known (which is mainly interesting for raw data
// processing). Also all objects are on the node tree in case your module's action
// depends on what else is around. Last chance to put nodes under the DST Node
// We mix events during readback if branches are added after the first event
//
// int EM_CALO::process_event(PHCompositeNode *topNode)
// called for every event. Return codes trigger actions, you find them in
// $OFFLINE_MAIN/include/fun4all/Fun4AllReturnCodes.h
//   everything is good:
//     return Fun4AllReturnCodes::EVENT_OK
//   abort event reconstruction, clear everything and process next event:
//     return Fun4AllReturnCodes::ABORT_EVENT; 
//   proceed but do not save this event in output (needs output manager setting):
//     return Fun4AllReturnCodes::DISCARD_EVENT; 
//   abort processing:
//     return Fun4AllReturnCodes::ABORT_RUN
// all other integers will lead to an error and abort of processing
//
// int EM_CALO::ResetEvent(PHCompositeNode *topNode)
// If you have internal data structures (arrays, stl containers) which needs clearing
// after each event, this is the place to do that. The nodes under the DST node are cleared
// by the framework
//
// int EM_CALO::EndRun(const int runnumber)
// This method is called at the end of a run when an event from a new run is
// encountered. Useful when analyzing multiple runs (raw data). Also called at
// the end of processing (before the End() method)
//
// int EM_CALO::End(PHCompositeNode *topNode)
// This is called at the end of processing. It needs to be called by the macro
// by Fun4AllServer::End(), so do not forget this in your macro
//
// int EM_CALO::Reset(PHCompositeNode *topNode)
// not really used - it is called before the dtor is called
//
// void EM_CALO::Print(const std::string &what) const
// Called from the command line - useful to print information when you need it
//
//____________________________________________________________________________..

#include "EM_CALO.h"

#include <fun4all/Fun4AllReturnCodes.h>

#include <phool/PHCompositeNode.h>
/// Cluster/Calorimeter includes
#include <calobase/RawCluster.h>
#include <calobase/RawClusterContainer.h>
#include <calobase/RawClusterUtility.h>
#include <calobase/RawTower.h>
#include <calobase/RawTowerContainer.h>
#include <calobase/RawTowerGeom.h>
#include <calobase/RawTowerGeomContainer.h>
#include <calotrigger/CaloTriggerInfo.h>
/// C++ includes
#include <cassert>
#include <sstream>
#include <string>
#include <vector>
/// ROOT includes
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TMath.h>
#include <TNtuple.h>
#include <TTree.h>
/// Fun4All includes
#include <fun4all/Fun4AllHistoManager.h>
#include <fun4all/Fun4AllReturnCodes.h>
#include <g4main/PHG4Hit.h>
#include <g4main/PHG4Particle.h>
#include <g4main/PHG4TruthInfoContainer.h>
#include <phool/PHCompositeNode.h>
#include <phool/getClass.h>
/// HEPMC truth includes
#include <HepMC/GenEvent.h>
#include <HepMC/GenVertex.h>
#include <phhepmc/PHHepMCGenEvent.h>
#include <phhepmc/PHHepMCGenEventMap.h>
/// Tracking includes
#include <g4vertex/GlobalVertex.h>
#include <g4vertex/GlobalVertexMap.h>
#include <trackbase_historic/SvtxTrack.h>
#include <trackbase_historic/SvtxTrackMap.h>
#include <trackbase_historic/SvtxVertex.h>
#include <trackbase_historic/SvtxVertexMap.h>
#include <trackbase_historic/SvtxTrack_FastSim.h>
using namespace std;
//____________________________________________________________________________..
EM_CALO::EM_CALO(const std::string &name, const std::string &filename):
  SubsysReco(name)
  , m_outfilename(filename)
  , m_analyzeTracks(false)
  , m_analyzeTruth(false)
  , m_analyzeTowers(false)
  
  
{
std::cout << "EM_CALO::EM_CALO(const std::string &name) Calling ctor" << std::endl;
 
 initializeTrees();
}

//____________________________________________________________________________..
EM_CALO::~EM_CALO()
{
  std::cout << "EM_CALO::~EM_CALO() Calling dtor" << std::endl;
  delete m_tracktree;
  delete m_truthtree;
  delete m_clustertree;
  
 }

//____________________________________________________________________________..
int EM_CALO::Init(PHCompositeNode *topNode)
{
  
  std::cout << "EM_CALO::Init(PHCompositeNode *topNode) Initializing" << std::endl;
  std::cout <<"**********************"<< m_outfilename<<"*********************"<<std::endl;
  const std::string EPtower = "eta_phi_h_tower";
  const std::string EPtruth = "eta_phi_h_truth";
  const std::string EEdet = "eta_energy_h_det";
  const std::string EEtruth = "eta_energy_h_truth";
  
  
  m_outfile = new TFile(m_outfilename.c_str(), "RECREATE");
  eta_phi_tower= new TH2F(EPtower.c_str(), ";#eta;#phi [rad]", 1000, -4, 2, 500, -TMath::Pi(), TMath::Pi());
  eta_phi_truth= new TH2F(EPtruth.c_str(), ";#eta;#phi [rad]", 1000, -4, 2, 500, -TMath::Pi(), TMath::Pi());
  eta_energy_det= new TH2F(EEdet.c_str(), ";#eta;energy ", 1000, -4, 2, 500, 0, 15);
  eta_energy_truth= new TH2F(EEtruth.c_str(), ";#eta;energy ", 1000, -4, 2, 500, 0, 15);
  p_ptruth = new TH2F("ptruth vs p", ";Ptruth;p ", 1000, 0, 20, 500, 0, 20);
  number_events = new TH1F("events","eta",1000,-4,2);
  histogram_f = new TH1F("f","(Erec-Etr)/Etr",1000,-2,2);
  EEMC_EP_pion_elec = new TH1F("EEMC Ep pion elec","Ep",1000,0,2);
  CEMC_EP_pion_elec = new TH1F("CEMC Ep pion elec","Ep",1000,0,2);
  
  E_deltaR_h = new TH1D("E delta R", ";delta R", 2000, 0, 1 );
  E_tower_cluster = new TH2F("E towercluster", ";cluster E;tower E", 1000, 0, 25, 1000, 0, 25);
  C_deltaR_h = new TH1D("C delta R", ";delta R", 2000, 0, 10 );
  C_tower_cluster = new TH2F("C towercluster", ";cluster E;tower E", 1000, 0, 25, 2000, 0, 50);
  EEMC_m_energy_h = new TH1D("E energy_h", ";#energy", 1000, 0, 1);
  EEMC_Cluster_counts = new TH1D("E counts", ";Counts", 5000, 0,700);
  CEMC_m_energy_h = new TH1D("C energy_h", ";#energy", 1000, 0, 1);
  CEMC_Cluster_counts = new TH1D("C counts", ";Counts", 5000, 0,700);
  
  EEMC_pip_no_epcut = new TH1D("E ep pipcut counts", ";Counts", 4000, 0,20);
  EEMC_pip_epcut = new TH1D("E ep pip counts", ";Counts", 4000, 0,20);

  //electron
  EEMC_elec_phi_eta_nf = new TH2F("E e- phi vs eta nf", ";eta;phi ", 1000, -4, 2, 1000, -M_PI, M_PI);
  EEMC_elec_phi_eta_pf = new TH2F("E e- phi vs eta pf", ";eta;phi ", 1000, -4, 2, 1000, -M_PI, M_PI);
  EEMC_elec_etruth_e= new TH2F("E e- E truth vs E det", ";E truth;E ", 400, 0, 20, 1000, 0, 25);
  EEMC_elec_ptruth_e= new TH2F("E e- P truth vs E det", ";P truth;E ", 200, 0, 20, 1000, 0, 25); 
  EEMC_elec_Ep = new TH2F("E e- Ep", ";P truth;E/p ", 400, 0, 20, 5000, 0, 2);
  EEMC_elec_p_ptruth = new TH2F("E e- ptruth vs p", ";Ptruth;p ", 1000, 0, 25, 1000, 0, 25);
  EEMC_elec_dpp_ptruth = new TH2F("E e- ptruth vs dpp", ";Ptruth;p ", 1000, 0, 25, 3000, -2, 2);
  EEMC_elec_dee_etruth = new TH2F("E e- etruth vs dee", ";Etruth;e ", 1000, 0, 25, 3000, -2, 2);
  EEMC_elec_dee_etruth_cut = new TH2F("E e- cut etruth vs dee", ";Etruth;e ", 1000, 0, 25, 3000, -2, 2);
  EEMC_elec_Eclus_Etruth= new TH2F("E e- etruth vs Eclus", ";Etruth;E cluster ", 1000, 0, 20, 2000, 0, 20);
  EEMC_m_eta_phi_h = new TH2F("E e- phi vs eta cluster", ";eta;phi ", 1000, -4, 2, 1000, -M_PI, M_PI);

  
  CEMC_elec_Eclus_Etruth= new TH2F("C e- etruth vs Eclus", ";Etruth;E cluster ", 1000, 0, 20, 2000, 0, 20);
  CEMC_elec_etruth_e= new TH2F("C e- E truth vs E det", ";E truth;E ", 400, 0, 20, 1000, 26.19, 51.19);
  CEMC_elec_ptruth_e= new TH2F("C e- P truth vs E det", ";P truth;E ", 200, 0, 20, 1000, 26.19, 51.19);
  CEMC_elec_Ep = new TH2F("C e- Ep", ";P truth;E/p ", 400, 0, 20, 5000, 0, 2);
  CEMC_elec_p_ptruth = new TH2F("C e- ptruth vs p", ";Ptruth;p ", 1000, 0, 25, 1000, 0, 25);
  CEMC_elec_dpp_ptruth = new TH2F("C e- ptruth vs dpp", ";Ptruth;p ", 1000, 0, 25, 3000, -2, 2);
  CEMC_elec_dee_etruth = new TH2F("C e- etruth vs dee", ";Etruth;E ", 1000, 0, 25, 3000, -50,0);
  CEMC_elec_dee_etruth_cut = new TH2F("C e- cut etruth vs dee", ";Etruth;E ", 1000, 0, 25, 3000, -2, 2);
  CEMC_elec_dee_etruth_cor = new TH2F("C e- etruth vs dee cor", ";Etruth;E ", 1000, 0, 25, 3000, 0, 20);
  CEMC_m_eta_phi_h = new TH2F("C e- phi vs eta cluster", ";eta;phi ", 1000, -4, 2, 1000, -M_PI, M_PI);
  //pi-
  EEMC_pi_etruth_e= new TH2F("E pi- E truth vs E det", ";E truth;E ", 400, 0, 20, 1000, 0, 25);
  EEMC_pi_ptruth_e= new TH2F("E pi- P truth vs E det", ";P truth;E ", 200, 0, 20, 1000, 0, 25); 
  EEMC_pi_Ep = new TH2F("E pi- Ep", ";P truth;E/p ", 400, 0, 20, 5000, 0, 2);
  CEMC_pi_etruth_e= new TH2F("C pi- E truth vs E det", ";E truth;E ", 400, 0, 20, 1000, 0, 25);
  CEMC_pi_ptruth_e= new TH2F("C pi- P truth vs E det", ";P truth;E ", 200, 0, 20, 1000, 0, 25);
  CEMC_pi_Ep = new TH2F("C pi- Ep", ";P truth;E/p ", 400, 0, 20, 5000, 0, 2);
  //pi+
  EEMC_pip_etruth_e= new TH2F("E pi+ E truth vs E det", ";E truth;E ", 400, 0, 20, 1000, 0, 25);
  EEMC_pip_ptruth_e= new TH2F("E pi+ P truth vs E det", ";P truth;E ", 200, 0, 20, 1000, 0, 25); 
  EEMC_pip_Ep = new TH2F("E pi+ Ep", ";P truth;E/p ", 400, 0, 20, 5000, 0, 2);
  EEMC_pip_p_ptruth = new TH2F("E pi+ ptruth vs p", ";Ptruth;p ", 1000, 0, 25, 500, 0, 25);
  EEMC_pip_dpp_ptruth = new TH2F("E pi+ ptruth vs dpp", ";Ptruth;p ", 1000, 0, 25, 3000, -2, 2);
  
  CEMC_pip_etruth_e= new TH2F("C pi+ E truth vs E det", ";E truth;E ", 400, 0, 20, 1000, 0, 25);
  CEMC_pip_ptruth_e= new TH2F("C pi+ P truth vs E det", ";P truth;E ", 200, 0, 20, 1000, 0, 25);
  CEMC_pip_Ep = new TH2F("C pi+ Ep", ";P truth;E/p ", 400, 0, 20, 5000, 0, 2);
  CEMC_pip_p_ptruth = new TH2F("C pi+ ptruth vs p", ";Ptruth;p ", 1000, 0, 25, 500, 0, 25);
  CEMC_pip_dpp_ptruth = new TH2F("C pi+ ptruth vs dpp", ";Ptruth;p ", 1000, 0, 25, 3000, -2, 2);
  //gamma
  EEMC_gamma_etruth_e= new TH2F("E gamma E truth vs E det", ";E truth;E ", 400, 0, 20, 1000, 0, 25);
  EEMC_gamma_ptruth_e= new TH2F("E gamma P truth vs E det", ";P truth;E ", 200, 0, 20, 1000, 0, 25); 

  CEMC_gamma_etruth_e= new TH2F("C gamma E truth vs E det", ";E truth;E ", 400, 0, 20, 1000, 0, 25);
  CEMC_gamma_ptruth_e= new TH2F("C gamma P truth vs E det", ";P truth;E ", 200, 0, 20, 1000, 0, 25);
  //1D #particle vs p for e-,e+,pi-,pi+
  EEMC_gamma = new TH1F("E gamma#","gamma #",1000,0,40);
  EEMC_elec= new TH1F("E elec#","elec #",1000,0,40);
  EEMC_pos= new TH1F("E pos#","pos #",1000,0,40);
  EEMC_pi= new TH1F("E pi#","pi #",1000,0,40);
  EEMC_piplus= new TH1F("E piplus#","piplus #",1000,0,40);
  CEMC_gamma = new TH1F("C gamma#","gamma #",1000,0,40);
  CEMC_elec= new TH1F("C elec#","elec #",1000,0,40);
  CEMC_pos= new TH1F("C pos#","pos #",1000,0,40);
  CEMC_pi= new TH1F("C pi#","pi #",1000,0,40);
  CEMC_piplus= new TH1F("C piplus#","piplus #",1000,0,40);
  // 2D E vs eta  p for e-,e+,pi-,pi+
  EEMC_gamma_Eveta = new TH2F("E gamma Eveta",";E;eta",200,0,20,1000, -4, -1.6);
  EEMC_elec_Eveta= new TH2F("E elec Eveta",";E;eta",200,0,20,1000, -4, -1.6);
  EEMC_pos_Eveta= new TH2F("E pos Eveta",";E;eta",200,0,20,1000, -4, -1.6);
  EEMC_pi_Eveta= new TH2F("E pi Eveta",";E;eta",200,0,20,1000, -4, -1.6);
  EEMC_piplus_Eveta= new TH2F("E piplus Eveta",";E;eta",200,0,20,1000, -4, -1.6);
  CEMC_gamma_Eveta= new TH2F("C gamma Eveta",";E;eta",200,0,20,1000, -1.6, 2);
  CEMC_elec_Eveta= new TH2F("C elec Eveta",";E;eta",200,0,20,1000, -1.6, 2);
  CEMC_pos_Eveta= new TH2F("C pos Eveta",";E;eta",200,0,20,1000, -1.6, 2);
  CEMC_pi_Eveta= new TH2F("C pi Eveta",";E;eta",200,0,20,1000, -1.6, 2);
  CEMC_piplus_Eveta= new TH2F("C piplus Eveta",";E;eta",200,0,20,1000, -1.6, 2);
  return Fun4AllReturnCodes::EVENT_OK;
 }

//____________________________________________________________________________..
 int EM_CALO::InitRun(PHCompositeNode *topNode)
 {
   std::cout << "EM_CALO::InitRun(PHCompositeNode *topNode) Initializing for Run XXX" << std::endl;
   return Fun4AllReturnCodes::EVENT_OK;
 }
 
 //____________________________________________________________________________..
 int EM_CALO::process_event(PHCompositeNode *topNode)
 {
   std::cout << "EM_CALO::process_event(PHCompositeNode *topNode) Processing Event" << std::endl;
   if (Verbosity() > 5)
     {
      cout << "Beginning process_event in AnaTutorialECCE" << endl;
 }
   
   if(m_analyzeTowers) //process_towers function
     {
       process_towers(topNode,"EEMC");
       process_towers(topNode,"CEMC");
     }
   if (m_analyzeTruth)
     {
       getPHG4Truth(topNode);
     }
   /// Get the tracks
   if (m_analyzeTracks)
    {
      getTracks(topNode);
    }
   if (m_emcalo_analysis)
     {
       EMcalorimeter_analyzer(topNode);  
     }
   /*
  /// Get the truth and reconstructed jets
  if (m_analyzeJets)
  {
  getTruthJets(topNode);
  getReconstructedJets(topNode);
  }
   */
   /// Get calorimeter information
   if (m_analyzeClusters)
     {
       getEMCalClusters(topNode,"EEMC");
       getEMCalClusters(topNode,"CEMC");
     }
   
   return Fun4AllReturnCodes::EVENT_OK;
 }

//____________________________________________________________________________..
int EM_CALO::ResetEvent(PHCompositeNode *topNode)
{
  
  std::cout << "EM_CALO::ResetEvent(PHCompositeNode *topNode) Resetting internal structures, prepare for next event" << std::endl;
  return Fun4AllReturnCodes::EVENT_OK;
}

//____________________________________________________________________________..
int EM_CALO::EndRun(const int runnumber)
{
  std::cout << "EM_CALO::EndRun(const int runnumber) Ending Run for Run " << runnumber << std::endl;
  return Fun4AllReturnCodes::EVENT_OK;
}

//____________________________________________________________________________..
int EM_CALO::End(PHCompositeNode *topNode)
{ 
  if (Verbosity() > 1)
    {
      cout << "Ending AnaTutorialECCE analysis package" << endl;
    }
  /// Change to the outfile
  m_outfile->cd();
  
  /// If we analyzed the tracks, write the tree out
  if (m_analyzeTracks)
    {
      m_tracktree->Write();
    }
  /*
 /// If we analyzed the jets, write them out
 if (m_analyzeJets)
 {
 m_truthjettree->Write();
 m_recojettree->Write();
 }
  */
  /// If we analyzed the truth particles, write them out
  if (m_analyzeTruth)
    {
      //  m_hepmctree->Write();
      m_truthtree->Write();
    }
  
  /// If we analyzed the clusters, write them out
  if (m_analyzeClusters)
    {
      m_clustertree->Write();
    }
  
  /// Write out any other histograms
  //m_eta_phi_h->Write();
  
  /// Write and close the outfile               
  m_outfile->Write();
  m_outfile->Close();
  

  
  /// Clean up pointers and associated histos/trees in TFile
  delete m_outfile;
  
  if (Verbosity() > 1)
    {
      cout << "Finished AnaTutorialECCE analysis package" << endl;
    }
  
  std::cout << "EM_CALO::End(PHCompositeNode *topNode) This is the End..." << std::endl;
  return Fun4AllReturnCodes::EVENT_OK;
}

//____________________________________________________________________________..
int EM_CALO::Reset(PHCompositeNode *topNode)
{
  std::cout << "EM_CALO::Reset(PHCompositeNode *topNode) being Reset" << std::endl;
  return Fun4AllReturnCodes::EVENT_OK;
}

//____________________________________________________________________________..
void EM_CALO::Print(const std::string &what) const
{
  std::cout << "EM_CALO::Print(const std::string &what) const Printing info for " << what << std::endl;
}

int EM_CALO::process_towers(PHCompositeNode* topNode,std::string pick_EMC)

{
  ostringstream nodename;
  ostringstream geonodename;
  string detector = pick_EMC;
  
  cout <<"I am in process towers looking at the "<< detector<<endl;
  // loop over the G4Hits
  nodename.str("");
  nodename << "TOWER_CALIB_" << detector;
  geonodename.str("");
  geonodename << "TOWERGEOM_" << detector;
  RawTowerGeomContainer* towergeom = findNode::getClass<RawTowerGeomContainer>(topNode, geonodename.str().c_str());
  if (!towergeom)
    {
      return Fun4AllReturnCodes::EVENT_OK;
    }
  
  RawTowerContainer* Ctowers = findNode::getClass<RawTowerContainer>(topNode, nodename.str().c_str());
  RawTowerContainer::ConstIterator rtiter;
  RawTowerContainer::ConstRange begin_end = Ctowers->getTowers();
  for (rtiter = begin_end.first; rtiter != begin_end.second; ++rtiter)
    {
      RawTower* tower = rtiter->second;
      
      if (tower->get_energy() < m_reco_e_threshold) continue;
      
      RawTowerGeom* tower_geom = towergeom->get_tower_geometry(tower->get_id());
      if (!tower_geom)
	{
          cerr << PHWHERE << " ERROR: Can't find tower geometry for this tower hit: ";
	  tower->identify();
	  exit(-1);
	}
      //const float towerid = tower->get_id();
      //const float ieta = tower->get_bineta();
      //const float iphi = tower->get_binphi();
      const float eta = tower_geom->get_eta();
      const float phi = tower_geom->get_phi();
      const float e = tower->get_energy();
      const float x = tower_geom->get_center_x();
      const float y = tower_geom->get_center_y();
      const float z = tower_geom->get_center_z();
      //     cout<<"Tower id: "<<towerid<<" ieta: "<<ieta<<" iphi: "<<iphi<<endl;
      cout<<" eta: "<<eta<<" phi: "<<phi<<" e: "<<e<<" x: "<<x<<" y: "<<y<<" z: "<<z<<endl;
      eta_phi_tower->Fill(eta,phi);
      eta_energy_det->Fill(eta,e);
    }
  return Fun4AllReturnCodes::EVENT_OK;
}

void EM_CALO::getPHG4Truth(PHCompositeNode *topNode)
{
  cout <<"********************In the getPHG4Truth function***************************"<<endl;
  /// G4 truth particle node
  PHG4TruthInfoContainer *truthinfo = findNode::getClass<PHG4TruthInfoContainer>(topNode, "G4TruthInfo");
  if (!truthinfo)
    {
      cout << PHWHERE
	   << "PHG4TruthInfoContainer node is missing, can't collect G4 truth particles"
	   << endl;
      return;
    }
  /// Get the primary particle range
  PHG4TruthInfoContainer::Range range = truthinfo->GetPrimaryParticleRange();
  /// Loop over the G4 truth (stable) particles
  for (PHG4TruthInfoContainer::ConstIterator iter = range.first;
       iter != range.second;
       ++iter)
    {
      /// Get this truth particle
      const PHG4Particle *truth = iter->second;
      /// Get this particles momentum, etc.
      m_truthpx = truth->get_px();
      m_truthpy = truth->get_py();
      m_truthpz = truth->get_pz();
      m_truthp = sqrt(m_truthpx * m_truthpx + m_truthpy * m_truthpy + m_truthpz * m_truthpz);
      m_truthenergy = truth->get_e();
      
      m_truthpt = sqrt(m_truthpx * m_truthpx + m_truthpy * m_truthpy);
      
      m_truthphi = atan(m_truthpy / m_truthpx);
      
      m_trutheta = atanh(m_truthpz / m_truthenergy);
      /// Check for nans
      if (m_trutheta != m_trutheta)
	m_trutheta = -99;
      m_truthpid = truth->get_pid();
      
      /// Fill the g4 truth tree
      //std::cout<<" truth PID = "<<m_truthpid<<" "<<m_truthenergy<<" "<<m_truthpt<<" "<<m_trutheta<<std::endl;
      m_truthtree->Fill(); 
      if(m_trutheta <= -1.6){
	if(m_truthpid==22){
	  EEMC_gamma->Fill(m_truthp);
	  EEMC_gamma_Eveta->Fill(m_truthenergy,m_trutheta);
	}
	if(m_truthpid==11){
	  EEMC_elec->Fill(m_truthp);
	  EEMC_elec_Eveta->Fill(m_truthenergy,m_trutheta);
	}
	if(m_truthpid==-11){
	  EEMC_pos->Fill(m_truthp);
	  EEMC_pos_Eveta->Fill(m_truthenergy,m_trutheta);
	}
	if(m_truthpid==-211){
	  EEMC_pi->Fill(m_truthp);
	  EEMC_pi_Eveta->Fill(m_truthenergy,m_trutheta);
	}
	if(m_truthpid==211){
	  EEMC_piplus->Fill(m_truthp);
	  EEMC_piplus_Eveta->Fill(m_truthenergy,m_trutheta);
	}
      }else{
	if(m_truthpid==22){
	  CEMC_gamma->Fill(m_truthp);
	  CEMC_gamma_Eveta->Fill(m_truthenergy,m_trutheta);
	}
	if(m_truthpid==11){
	  CEMC_elec->Fill(m_truthp);
	  CEMC_elec_Eveta->Fill(m_truthenergy,m_trutheta);
	}
	if(m_truthpid==-11){
	  CEMC_pos->Fill(m_truthp);
	  CEMC_pos_Eveta->Fill(m_truthenergy,m_trutheta);
	}
	if(m_truthpid==-211){
	  CEMC_pi->Fill(m_truthp);
	  CEMC_pi_Eveta->Fill(m_truthenergy,m_trutheta);
	}
	if(m_truthpid==211){
	  CEMC_piplus->Fill(m_truthp);
	  CEMC_piplus_Eveta->Fill(m_truthenergy,m_trutheta);
	}
      }
      
      eta_phi_truth->Fill(m_trutheta,m_truthphi);
      eta_energy_truth->Fill(m_trutheta,m_truthenergy);
    }

}

void EM_CALO::getTracks(PHCompositeNode *topNode)
{
  cout <<"************************In the get Tracks function***********************"<<endl;
  /// Tracks node
  SvtxTrackMap *trackmap = findNode::getClass<SvtxTrackMap>(topNode, "TrackMap");
  
  if (!trackmap)
    {
      cout << PHWHERE
	   << "TrackMap node is missing, can't collect tracks"
	   << endl;
      return;
  }
  
  /// Get the range for primary tracks
  PHG4TruthInfoContainer *truthinfo = findNode::getClass<PHG4TruthInfoContainer>(topNode, "G4TruthInfo");
  
  if (Verbosity() > 1)
    {
      cout << "Get the tracks" << endl;
    }
  for (SvtxTrackMap::Iter iter = trackmap->begin();
       iter != trackmap->end();
       ++iter)
    {
      SvtxTrack *track = iter->second;
      
    /// Get the reconstructed track info
      m_tr_px = track->get_px();
      m_tr_py = track->get_py();
      m_tr_pz = track->get_pz();
      m_tr_p = sqrt(m_tr_px * m_tr_px + m_tr_py * m_tr_py + m_tr_pz * m_tr_pz);
      
      m_tr_pt = sqrt(m_tr_px * m_tr_px + m_tr_py * m_tr_py);
      
      // Make some cuts on the track to clean up sample
    if (m_tr_pt < 0.5)
      continue;
    
    m_tr_phi = track->get_phi();
    m_tr_eta = track->get_eta();
    
    m_charge = track->get_charge();
    m_chisq = track->get_chisq();
    m_ndf = track->get_ndf();
    m_dca = track->get_dca();
    m_tr_x = track->get_x();
    m_tr_y = track->get_y();
    m_tr_z = track->get_z();
    
    /// Get truth track info that matches this reconstructed track
    PHG4Particle *truthtrack = nullptr;
    
    /// Ensure that the reco track is a fast sim track
    SvtxTrack_FastSim *temp = dynamic_cast<SvtxTrack_FastSim*>(iter->second);
    if(!temp)
      {
	if(Verbosity() > 0)
	  std::cout << "Skipping non fast track sim object..." << std::endl;
	continue;
      }
    
    PHG4TruthInfoContainer::Range range = truthinfo->GetPrimaryParticleRange();
    
    /// Loop over the G4 truth (stable) particles
    for (PHG4TruthInfoContainer::ConstIterator iter = range.first;
	 iter != range.second;
	 ++iter)
      {
	/// Get this truth particle
        PHG4Particle *truth = iter->second;
	if((truth->get_track_id() - temp->get_truth_track_id()) == 0)
	  {
	    truthtrack = truth;
	  }
      }
    
    m_truth_is_primary = truthinfo->is_primary(truthtrack);
    
    m_truthtrackpx = truthtrack->get_px();
    m_truthtrackpy = truthtrack->get_py();
    m_truthtrackpz = truthtrack->get_pz();
    m_truthtrackp = sqrt(m_truthtrackpx * m_truthtrackpx + m_truthtrackpy * m_truthtrackpy + m_truthtrackpz * m_truthtrackpz);
    
    m_truthtracke = truthtrack->get_e();
    
    m_truthtrackpt = sqrt(m_truthtrackpx * m_truthtrackpx + m_truthtrackpy * m_truthtrackpy);
    m_truthtrackphi = atan2(m_truthtrackpy , m_truthtrackpx);
    m_truthtracketa = atanh(m_truthtrackpz / m_truthtrackp);
    m_truthtrackpid = truthtrack->get_pid();
    
    m_tracktree->Fill();
    }
}

void EM_CALO::EMcalorimeter_analyzer(PHCompositeNode* topNode){
  
  vector<vector<double>> infotrans;
  /******************************************************************************************/
  PHG4TruthInfoContainer *truthinfo = findNode::getClass<PHG4TruthInfoContainer>(topNode, "G4TruthInfo");
  if (!truthinfo)
    {
      cout << PHWHERE
	   << "PHG4TruthInfoContainer node is missing, can't collect G4 truth particles"
	   << endl;
      return;
    }
  /// Get the primary particle range
  PHG4TruthInfoContainer::Range range = truthinfo->GetPrimaryParticleRange();
  /// Loop over the G4 truth (stable) particles
  for (PHG4TruthInfoContainer::ConstIterator iter = range.first;
       iter != range.second;
       ++iter)
    {
      /// Get this truth particle
      const PHG4Particle *truth = iter->second;
      /// Get this particles momentum, etc.
      m_truthpx = truth->get_px();
      m_truthpy = truth->get_py();
      m_truthpz = truth->get_pz();
      m_truthp = sqrt(m_truthpx * m_truthpx + m_truthpy * m_truthpy + m_truthpz * m_truthpz);
      m_truthenergy = truth->get_e();
      
      m_truthpt = sqrt(m_truthpx * m_truthpx + m_truthpy * m_truthpy);
      
      m_truthphi = atan(m_truthpy / m_truthpx);
    
      m_trutheta = atanh(m_truthpz / m_truthenergy);
    /// Check for nans
      if (m_trutheta != m_trutheta)
	m_trutheta = -99;
      m_truthpid = truth->get_pid();
      
      /// Fill the g4 truth tree
      vector<double> v1{(double)m_truthpid,m_truthenergy,m_truthp,m_trutheta};
      infotrans.push_back(v1);
      
      
      m_truthtree->Fill(); 
    
    }/*
  for (double i = 0; i < infotrans.size(); i++) {
    for (double j = 0; j < infotrans[i].size(); j++)
      cout << infotrans[i][j] << " ";
      cout << endl;
      }*/
  
  /*****************************************************************************/
  number_events->Fill(m_trutheta);
  string detector;
  if (m_trutheta <= -1.9)
    {
      detector = "EEMC";
    }
  else if(m_trutheta>=-1.4 && m_trutheta<=1.2)
    {
      detector = "CEMC";
    }
  else{detector ="";}
  /*****************************************************************************/
  ostringstream nodename;
  ostringstream geonodename;
  
  cout <<"I am in EMcalorimeter_analyzer looking at the "<< detector<<endl;
  // loop over the G4Hits
  nodename.str("");
  nodename << "TOWER_CALIB_" << detector;
  geonodename.str("");
  geonodename << "TOWERGEOM_" << detector;
  RawTowerGeomContainer* towergeom = findNode::getClass<RawTowerGeomContainer>(topNode, geonodename.str().c_str());
  if (!towergeom)
    {
      return;
    }
  double etotal=0;
  RawTowerContainer* Ctowers = findNode::getClass<RawTowerContainer>(topNode, nodename.str().c_str());
  RawTowerContainer::ConstIterator rtiter;
  RawTowerContainer::ConstRange begin_end = Ctowers->getTowers();
  for (rtiter = begin_end.first; rtiter != begin_end.second; ++rtiter)
    {
      RawTower* tower = rtiter->second;
      
      if (tower->get_energy() < m_reco_e_threshold) continue;
      
      RawTowerGeom* tower_geom = towergeom->get_tower_geometry(tower->get_id());
      if (!tower_geom)
	{
          cerr << PHWHERE << " ERROR: Can't find tower geometry for this tower hit: ";
	  tower->identify();
	  exit(-1);
	}
      //const float towerid = tower->get_id();
      //const float ieta = tower->get_bineta();
      //const float iphi = tower->get_binphi();
      //const float eta = tower_geom->get_eta();
      //const float phi = tower_geom->get_phi();
      const float e = tower->get_energy();
      //const float x = tower_geom->get_center_x();
      //const float y = tower_geom->get_center_y();
      //const float z = tower_geom->get_center_z();
      //     cout<<"Tower id: "<<towerid<<" ieta: "<<ieta<<" iphi: "<<iphi<<endl;
      //cout<<" eta: "<<eta<<" phi: "<<phi<<" e: "<<e<<" x: "<<x<<" y: "<<y<<" z: "<<z<<endl;
      etotal = etotal + e;
    }
  //if (detector=="CEMC"){etotal =etotal-26.19;}
  std::cout << etotal<<std::endl;
  
  /*************************************************************************************/
  SvtxTrackMap *trackmap = findNode::getClass<SvtxTrackMap>(topNode, "TrackMap");
  double ptotal=0;
  if (!trackmap)
    {
      cout << PHWHERE
	   << "TrackMap node is missing, can't collect tracks"
	   << endl;
      return;
    }

  if (Verbosity() > 1)
    {
      cout << "Get the tracks" << endl;
    }
  for (SvtxTrackMap::Iter iter = trackmap->begin();
       iter != trackmap->end();
       ++iter)
    {
      SvtxTrack *track = iter->second;
      
      /// Get the reconstructed track info
    m_tr_px = track->get_px();
    m_tr_py = track->get_py();
    m_tr_pz = track->get_pz();
    m_tr_p = sqrt(m_tr_px * m_tr_px + m_tr_py * m_tr_py + m_tr_pz * m_tr_pz);
    m_tr_pt = sqrt(m_tr_px * m_tr_px + m_tr_py * m_tr_py);
    
    // Make some cuts on the track to clean up sample
    //if (m_tr_pt < 0.5)
    //  continue;
    
    m_tr_phi = track->get_phi();
    m_tr_eta = track->get_eta();
    m_charge = track->get_charge();
    m_chisq = track->get_chisq();
    m_ndf = track->get_ndf();
    m_dca = track->get_dca();
    m_tr_x = track->get_x();
    m_tr_y = track->get_y();
    m_tr_z = track->get_z();

    ptotal = ptotal+m_tr_p;
    if(detector =="EEMC")
      {
	if(m_truthpid == 11){
	  EEMC_elec_p_ptruth->Fill(m_truthp,m_tr_p);
	  EEMC_elec_dpp_ptruth->Fill(m_truthp,(m_truthp-m_tr_p)/m_truthp);
	}
	if(m_truthpid == 211){
	  EEMC_pip_p_ptruth->Fill(m_truthp,m_tr_p);
	  EEMC_pip_dpp_ptruth->Fill(m_truthp,(m_truthp-m_tr_p)/m_truthp);
	}
      }else if(detector=="CEMC")
      {
	if(m_truthpid == 11){
	  CEMC_elec_p_ptruth->Fill(m_truthp,m_tr_p);
	  CEMC_elec_dpp_ptruth->Fill(m_truthp,(m_truthp-m_tr_p)/m_truthp);
	}
	if(m_truthpid == 211){
	  CEMC_pip_p_ptruth->Fill(m_truthp,m_tr_p);
	  CEMC_pip_dpp_ptruth->Fill(m_truthp,(m_truthp-m_tr_p)/m_truthp);
	}
      }
    
    }


  std::string clusterdetector = "CLUSTER_"+detector;
  /// Get the raw cluster container
  /// Note: other cluster containers exist as well. Check out the node tree when
  /// you run a simulation, for example look for the node CLUSTER_EEMC
  RawClusterContainer *clusters = findNode::getClass<RawClusterContainer>(topNode,clusterdetector);

  if (!clusters)
  {
    cout << PHWHERE
         << "EMCal cluster node is missing, can't collect EMCal clusters"
         << endl;
    return;
  }
  cout <<"******************************"<<detector<<"***********************************"<<endl;
  /// Get the global vertex to determine the appropriate pseudorapidity of the clusters
  GlobalVertexMap *vertexmap = findNode::getClass<GlobalVertexMap>(topNode, "GlobalVertexMap");
  if (!vertexmap)
  {
    cout << "AnaTutorialECCE::getEmcalClusters - Fatal Error - GlobalVertexMap node is missing. Please turn on the do_global flag in the main macro in order to reconstruct the global vertex." << endl;
    assert(vertexmap);  // force quit
    return;
  }
  if (vertexmap->empty())
  {
    cout << "AnaTutorialECCE::getEmcalClusters - Fatal Error - GlobalVertexMap node is empty. Please turn on the do_global flag in the main macro in order to reconstruct the global vertex." << endl;
    return;
  }
  GlobalVertex *vtx = vertexmap->begin()->second;
  if (vtx == nullptr)
    return;

  /// Trigger emulator
  CaloTriggerInfo *trigger = findNode::getClass<CaloTriggerInfo>(topNode, "CaloTriggerInfo");
  
  /// Can obtain some trigger information if desired
  if(trigger)
    {
      m_E_4x4 = trigger->get_best_EMCal_4x4_E();
    }
  RawClusterContainer::ConstRange cbegin_end = clusters->getClusters();
  RawClusterContainer::ConstIterator clusIter;
  
  double Rmin =1000;
  int counter = 0;
  double min_clusenergy = -99;
  /// Loop over the EMCal clusters
  for (clusIter = cbegin_end.first;
       clusIter != cbegin_end.second;
       ++clusIter)
  {
    /// Get this cluster
    const RawCluster *cluster = clusIter->second;
    
    /// Get cluster characteristics
    /// This helper class determines the photon characteristics
    /// depending on the vertex position
    /// This is important for e.g. eta determination and E_T determination
    CLHEP::Hep3Vector vertex(vtx->get_x(), vtx->get_y(), vtx->get_z());
    CLHEP::Hep3Vector E_vec_cluster = RawClusterUtility::GetECoreVec(*cluster, vertex);
    
    m_clusenergy = E_vec_cluster.mag();
    m_cluseta = E_vec_cluster.pseudoRapidity();
    m_clustheta = E_vec_cluster.getTheta();
    m_cluspt = E_vec_cluster.perp();
    m_clusphi = E_vec_cluster.getPhi();

    counter = counter + 1;
    if (detector =="EEMC"){
      EEMC_m_energy_h->Fill(m_clusenergy);
      EEMC_m_eta_phi_h->Fill(m_cluseta,m_clusphi);
    }
    if (detector =="CEMC"){
      CEMC_m_energy_h->Fill(m_clusenergy);
      CEMC_m_eta_phi_h->Fill(m_cluseta,m_clusphi);
    }

    if (m_cluspt < m_mincluspt)
      continue;
    
    m_cluspx = m_cluspt * cos(m_clusphi);
    m_cluspy = m_cluspt * sin(m_clusphi);
    m_cluspz = sqrt(m_clusenergy * m_clusenergy - m_cluspx * m_cluspx - m_cluspy * m_cluspy);
  
    //fill the cluster tree with all emcal clusters
    m_clustertree->Fill();    


    double R = sqrt(pow(m_cluseta-m_tr_eta,2)+pow(m_clusphi-m_tr_phi,2));
    if (R <Rmin){
        Rmin = R;
	min_clusenergy = m_clusenergy;
    }
    
  }



  double Rcut = 100;
  double ratio = etotal/ptotal;
  //double Ep95cut = 1.03559-0.024178*ptotal+0.000660511*ptotal*ptotal; //above regect
  double Ep90cut = 1.06009-0.0198504*ptotal+0.000643466*ptotal*ptotal;
  double f = (etotal-m_truthenergy)/m_truthenergy;
  if (detector=="EEMC"){
    Rcut =.22;
    if(m_truthpid == 11){
      if (Rmin<Rcut){
	E_tower_cluster->Fill(min_clusenergy,etotal);
	EEMC_elec_Eclus_Etruth->Fill(min_clusenergy,m_truthenergy);
	EEMC_elec_dee_etruth_cut->Fill(m_truthenergy,(m_truthenergy-min_clusenergy)/m_truthenergy);
      }
      EEMC_Cluster_counts->Fill(counter);
      E_deltaR_h->Fill(Rmin);
      EEMC_elec_Ep->Fill(m_truthp,ratio);
      EEMC_elec_etruth_e->Fill(m_truthenergy,etotal);
      EEMC_elec_ptruth_e->Fill(m_truthp,etotal);
      EEMC_EP_pion_elec->Fill(ratio);
      EEMC_elec_dee_etruth->Fill(m_truthenergy,(m_truthenergy-etotal)/m_truthenergy);
    }
    if(m_truthpid == 22){
      EEMC_gamma_etruth_e->Fill(m_truthenergy,etotal);
      EEMC_gamma_ptruth_e->Fill(m_truthp,etotal);
    }
    if(m_truthpid == -211){
      EEMC_pi_Ep->Fill(m_truthp,ratio);
      EEMC_pi_etruth_e->Fill(m_truthenergy,etotal);
      EEMC_pi_ptruth_e->Fill(m_truthp,etotal);}
    if(m_truthpid == 211){
      EEMC_pip_Ep->Fill(m_truthp,ratio);
      EEMC_pip_etruth_e->Fill(m_truthenergy,etotal);
      EEMC_pip_ptruth_e->Fill(m_truthp,etotal);
      EEMC_EP_pion_elec->Fill(ratio);
      EEMC_pip_no_epcut->Fill(m_truthp);

      if(ratio >=Ep90cut){EEMC_pip_epcut->Fill(m_truthp);}
      
    }
  }else if(detector=="CEMC"){
    Rcut = .2;
    if(m_truthpid == 11){
      if (Rmin<Rcut){
	C_tower_cluster->Fill(min_clusenergy,etotal);
	CEMC_elec_Eclus_Etruth->Fill(min_clusenergy,m_truthenergy);
	CEMC_elec_dee_etruth_cut->Fill(m_truthenergy,(m_truthenergy-min_clusenergy)/m_truthenergy);
      }
      CEMC_Cluster_counts->Fill(counter);
      C_deltaR_h->Fill(Rmin);
      CEMC_elec_Ep->Fill(m_truthp,ratio);
      CEMC_elec_ptruth_e->Fill(m_truthp,etotal);
      CEMC_EP_pion_elec->Fill(ratio);
      CEMC_elec_etruth_e->Fill(m_truthenergy,etotal);
      CEMC_elec_dee_etruth->Fill(m_truthenergy,(m_truthenergy-etotal)/m_truthenergy);
      CEMC_elec_dee_etruth_cor->Fill(m_truthenergy,(m_truthenergy-(etotal+26.19))/m_truthenergy);
    }
    
    if(m_truthpid == 22){
      CEMC_gamma_etruth_e->Fill(m_truthenergy,etotal);
      CEMC_gamma_ptruth_e->Fill(m_truthp,etotal);
    }
    if(m_truthpid == -211){
      CEMC_pi_Ep->Fill(m_truthp,ratio);
      CEMC_pi_etruth_e->Fill(m_truthenergy,etotal);
      CEMC_pi_ptruth_e->Fill(m_truthp,etotal);}
    if(m_truthpid == 211){
      CEMC_pip_Ep->Fill(m_truthp,ratio);
      CEMC_pip_etruth_e->Fill(m_truthenergy,etotal);
      CEMC_pip_ptruth_e->Fill(m_truthp,etotal);
      CEMC_EP_pion_elec->Fill(ratio);
      histogram_f->Fill(f);
      if(f<-.8){EEMC_elec_phi_eta_nf->Fill(m_trutheta,m_truthphi);}
      else{EEMC_elec_phi_eta_pf->Fill(m_trutheta,m_truthphi);}}
    }else{}
  
}

void EM_CALO::initializeTrees()
{
  m_tracktree = new TTree("tracktree", "A tree with svtx tracks");
  m_tracktree->Branch("m_tr_px", &m_tr_px, "m_tr_px/D");
  m_tracktree->Branch("m_tr_py", &m_tr_py, "m_tr_py/D");
  m_tracktree->Branch("m_tr_pz", &m_tr_pz, "m_tr_pz/D");
  m_tracktree->Branch("m_tr_p", &m_tr_p, "m_tr_p/D");
  m_tracktree->Branch("m_tr_pt", &m_tr_pt, "m_tr_pt/D");
  m_tracktree->Branch("m_tr_phi", &m_tr_phi, "m_tr_phi/D");
  m_tracktree->Branch("m_tr_eta", &m_tr_eta, "m_tr_eta/D");
  m_tracktree->Branch("m_charge", &m_charge, "m_charge/I");
  m_tracktree->Branch("m_chisq", &m_chisq, "m_chisq/D");
  m_tracktree->Branch("m_ndf", &m_ndf, "m_ndf/I");
  m_tracktree->Branch("m_dca", &m_dca, "m_dca/D");
  m_tracktree->Branch("m_tr_x", &m_tr_x, "m_tr_x/D");
  m_tracktree->Branch("m_tr_y", &m_tr_y, "m_tr_y/D");
  m_tracktree->Branch("m_tr_z", &m_tr_z, "m_tr_z/D");
  m_tracktree->Branch("m_truth_is_primary", &m_truth_is_primary, "m_truth_is_primary/I");
  m_tracktree->Branch("m_truthtrackpx", &m_truthtrackpx, "m_truthtrackpx/D");
  m_tracktree->Branch("m_truthtrackpy", &m_truthtrackpy, "m_truthtrackpy/D");
  m_tracktree->Branch("m_truthtrackpz", &m_truthtrackpz, "m_truthtrackpz/D");
  m_tracktree->Branch("m_truthtrackp", &m_truthtrackp, "m_truthtrackp/D");
  m_tracktree->Branch("m_truthtracke", &m_truthtracke, "m_truthtracke/D");
  m_tracktree->Branch("m_truthtrackpt", &m_truthtrackpt, "m_truthtrackpt/D");
  m_tracktree->Branch("m_truthtrackphi", &m_truthtrackphi, "m_truthtrackphi/D");
  m_tracktree->Branch("m_truthtracketa", &m_truthtracketa, "m_truthtracketa/D");
  m_tracktree->Branch("m_truthtrackpid", &m_truthtrackpid, "m_truthtrackpid/I");
  /*
  m_hepmctree = new TTree("hepmctree", "A tree with hepmc truth particles");
  m_hepmctree->Branch("m_partid1", &m_partid1, "m_partid1/I");
  m_hepmctree->Branch("m_partid2", &m_partid2, "m_partid2/I");
  m_hepmctree->Branch("m_x1", &m_x1, "m_x1/D");
  m_hepmctree->Branch("m_x2", &m_x2, "m_x2/D");
  m_hepmctree->Branch("m_mpi", &m_mpi, "m_mpi/I");
  m_hepmctree->Branch("m_process_id", &m_process_id, "m_process_id/I");
  m_hepmctree->Branch("m_truthenergy", &m_truthenergy, "m_truthenergy/D");
  m_hepmctree->Branch("m_trutheta", &m_trutheta, "m_trutheta/D");
  m_hepmctree->Branch("m_truthphi", &m_truthphi, "m_truthphi/D");
  m_hepmctree->Branch("m_truthpx", &m_truthpx, "m_truthpx/D");
  m_hepmctree->Branch("m_truthpy", &m_truthpy, "m_truthpy/D");
  m_hepmctree->Branch("m_truthpz", &m_truthpz, "m_truthpz/D");
  m_hepmctree->Branch("m_truthpt", &m_truthpt, "m_truthpt/D");
  m_hepmctree->Branch("m_numparticlesinevent", &m_numparticlesinevent, "m_numparticlesinevent/I");
  m_hepmctree->Branch("m_truthpid", &m_truthpid, "m_truthpid/I");
  */
  m_truthtree = new TTree("truthg4tree", "A tree with truth g4 particles");
  m_truthtree->Branch("m_truthenergy", &m_truthenergy, "m_truthenergy/D");
  m_truthtree->Branch("m_truthp", &m_truthp, "m_truthp/D");
  m_truthtree->Branch("m_truthpx", &m_truthpx, "m_truthpx/D");
  m_truthtree->Branch("m_truthpy", &m_truthpy, "m_truthpy/D");
  m_truthtree->Branch("m_truthpz", &m_truthpz, "m_truthpz/D");
  m_truthtree->Branch("m_truthpt", &m_truthpt, "m_truthpt/D");
  m_truthtree->Branch("m_truthphi", &m_truthphi, "m_truthphi/D");
  m_truthtree->Branch("m_trutheta", &m_trutheta, "m_trutheta/D");
  m_truthtree->Branch("m_truthpid", &m_truthpid, "m_truthpid/I");
  
  m_clustertree = new TTree("clustertree", "A tree with emcal clusters");
  m_clustertree->Branch("m_clusenergy", &m_clusenergy, "m_clusenergy/D");
  m_clustertree->Branch("m_cluseta", &m_cluseta, "m_cluseta/D");
  m_clustertree->Branch("m_clustheta", &m_clustheta, "m_clustheta/D");
  m_clustertree->Branch("m_cluspt", &m_cluspt, "m_cluspt/D");
  m_clustertree->Branch("m_clusphi", &m_clusphi, "m_clusphi/D");
  m_clustertree->Branch("m_cluspx", &m_cluspx, "m_cluspx/D");
  m_clustertree->Branch("m_cluspy", &m_cluspy, "m_cluspy/D");
  m_clustertree->Branch("m_cluspz", &m_cluspz, "m_cluspz/D");
  m_clustertree->Branch("m_E_4x4", &m_E_4x4, "m_E_4x4/D");
  
}

void EM_CALO::getEMCalClusters(PHCompositeNode *topNode,std::string pick_EMC)
{
  std::string detector = pick_EMC;
  
  std::string clusterdetector = "CLUSTER_"+detector;
  /// Get the raw cluster container
  /// Note: other cluster containers exist as well. Check out the node tree when
  /// you run a simulation, for example look for the node CLUSTER_EEMC
  RawClusterContainer *clusters = findNode::getClass<RawClusterContainer>(topNode,clusterdetector);

  if (!clusters)
  {
    cout << PHWHERE
         << "EMCal cluster node is missing, can't collect EMCal clusters"
         << endl;
    return;
  }
  cout <<"******************************"<<detector<<"***********************************"<<endl;
  /// Get the global vertex to determine the appropriate pseudorapidity of the clusters
  GlobalVertexMap *vertexmap = findNode::getClass<GlobalVertexMap>(topNode, "GlobalVertexMap");
  if (!vertexmap)
  {
    cout << "AnaTutorialECCE::getEmcalClusters - Fatal Error - GlobalVertexMap node is missing. Please turn on the do_global flag in the main macro in order to reconstruct the global vertex." << endl;
    assert(vertexmap);  // force quit
    return;
  }
  if (vertexmap->empty())
  {
    cout << "AnaTutorialECCE::getEmcalClusters - Fatal Error - GlobalVertexMap node is empty. Please turn on the do_global flag in the main macro in order to reconstruct the global vertex." << endl;
    return;
  }
  GlobalVertex *vtx = vertexmap->begin()->second;
  if (vtx == nullptr)
    return;

  /// Trigger emulator
  CaloTriggerInfo *trigger = findNode::getClass<CaloTriggerInfo>(topNode, "CaloTriggerInfo");
  
  /// Can obtain some trigger information if desired
  if(trigger)
    {
      m_E_4x4 = trigger->get_best_EMCal_4x4_E();
    }
  RawClusterContainer::ConstRange begin_end = clusters->getClusters();
  RawClusterContainer::ConstIterator clusIter;
  
  int counter = 0;
  /// Loop over the EMCal clusters
  for (clusIter = begin_end.first;
       clusIter != begin_end.second;
       ++clusIter)
  {
    /// Get this cluster
    const RawCluster *cluster = clusIter->second;
    
    /// Get cluster characteristics
    /// This helper class determines the photon characteristics
    /// depending on the vertex position
    /// This is important for e.g. eta determination and E_T determination
    CLHEP::Hep3Vector vertex(vtx->get_x(), vtx->get_y(), vtx->get_z());
    CLHEP::Hep3Vector E_vec_cluster = RawClusterUtility::GetECoreVec(*cluster, vertex);
    
    m_clusenergy = E_vec_cluster.mag();
    m_cluseta = E_vec_cluster.pseudoRapidity();
    m_clustheta = E_vec_cluster.getTheta();
    m_cluspt = E_vec_cluster.perp();
    m_clusphi = E_vec_cluster.getPhi();

    counter = counter + 1;
    //Cluster_counts->Fill(counter);
    //m_energy_h->Fill(m_clusenergy);
    //m_eta_phi_h->Fill(m_cluseta,m_clusphi);
    
    if (m_cluspt < m_mincluspt)
      continue;
    
    m_cluspx = m_cluspt * cos(m_clusphi);
    m_cluspy = m_cluspt * sin(m_clusphi);
    m_cluspz = sqrt(m_clusenergy * m_clusenergy - m_cluspx * m_cluspx - m_cluspy * m_cluspy);
  
    //fill the cluster tree with all emcal clusters
    m_clustertree->Fill();    
  

  }
  //Cluster_counts->Fill(counter);
}
