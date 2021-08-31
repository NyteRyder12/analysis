// Tell emacs that this is a C++ source
//  -*- C++ -*-.
#ifndef EM_CALO_H
#define EM_CALO_H

#include <fun4all/SubsysReco.h>
#include <string>

class PHCompositeNode;
class TFile;
class TTree;
class TH2;
class TH1;
class EM_CALO : public SubsysReco

{
 public:
  //Constructor
  EM_CALO(const std::string &name = "EM_CALO",const std::string &fname = "EM_CALO.root");
  //Destructor
  virtual ~EM_CALO();

  /** Called during initialization.
      Typically this is where you can book histograms, and e.g.
      register them to Fun4AllServer (so they can be output to file
      using Fun4AllServer::dumpHistos() method).
   */
  int Init(PHCompositeNode *topNode) override;

  /** Called for first event when run number is known.
      Typically this is where you may want to fetch data from
      database, because you know the run number. A place
      to book histograms which have to know the run number.
   */
  int InitRun(PHCompositeNode *topNode) override;

  /** Called for each event.
      This is where you do the real work.
   */
  int process_event(PHCompositeNode *topNode) override;

  /// Clean up internals after each event.
  int ResetEvent(PHCompositeNode *topNode) override;

  /// Called at the end of each run.
  int EndRun(const int runnumber) override;

  /// Called at the end of all processing.
  int End(PHCompositeNode *topNode) override;

  /// Reset
  int Reset(PHCompositeNode * /*topNode*/) override;

  void Print(const std::string &what = "ALL") const override;

  void setMinClusPt(float mincluspt) { m_mincluspt = mincluspt; }

  int process_towers(PHCompositeNode *,std::string);
  void EMcalorimeter_analyzer(PHCompositeNode *);
  /// Set things to analyze
  void analyzeTracks(bool analyzeTracks) { m_analyzeTracks = analyzeTracks; }
  void analyzeTruth(bool analyzeTruth) { m_analyzeTruth = analyzeTruth; }
  void analyzeTower(bool analyzeTower) { m_analyzeTowers = analyzeTower; }// process_towers function
  void analyzeClusters(bool analyzeClusters) { m_analyzeClusters = analyzeClusters; }
  void emcalo_analysis(double emcalo_analysis){m_emcalo_analysis = emcalo_analysis;}
  void reco_e_threshold(double reco_e_threshold){m_reco_e_threshold = reco_e_threshold;}

  void initializeTrees();
 private:
  std::string m_outfilename;

  double m_reco_e_threshold;
  /// A boolean for running over tracks
  bool m_analyzeTracks;

  /// A boolean for collecting hepmc information
  bool m_analyzeTruth;

  //Towers process_towers function
  bool m_analyzeTowers;
  /// A boolean for running over clusters
  bool m_analyzeClusters;

  bool m_emcalo_analysis;


  void getTracks(PHCompositeNode *topNode);
  void getPHG4Truth(PHCompositeNode *topNode);
  void getEMCalClusters(PHCompositeNode *topNode,std::string);
  /// A float for cutting on cluster pt
  float m_mincluspt;
  /// TFile to hold the following TTrees and histograms
  TFile *m_outfile;
  TTree *m_clustertree;
  TTree *m_tracktree;
  TTree *m_truthtree;
  TH2 *eta_phi_tower;
  TH2 *eta_phi_truth;
  TH2 *eta_energy_det;
  TH2 *eta_energy_truth;
  TH2 *p_ptruth;
  TH1 *number_events;
  TH1 *histogram_f;
  TH1 *EEMC_EP_pion_elec;
  TH1 *CEMC_EP_pion_elec;
  TH1 *E_deltaR_h;
  TH2 *E_tower_cluster;
  TH1 *C_deltaR_h;
  TH2 *C_tower_cluster;
  TH2 *EEMC_elec_Eclus_Etruth;
  TH2 *CEMC_elec_Eclus_Etruth;

  TH1 *EEMC_Cluster_counts;
  TH1 *EEMC_m_energy_h;
  TH2 *EEMC_m_eta_phi_h;
  TH1 *CEMC_Cluster_counts;
  TH1 *CEMC_m_energy_h;
  TH2 *CEMC_m_eta_phi_h;
  
  //electron
  TH2 *EEMC_elec_etruth_e;
  TH2 *EEMC_elec_ptruth_e;
  TH2 *EEMC_elec_p_ptruth;
  TH2 *EEMC_elec_dpp_ptruth;
  TH2 *EEMC_elec_dee_etruth;
  TH2 *EEMC_elec_dee_etruth_cut;
  TH2 *EEMC_elec_Ep;
  TH2 *EEMC_elec_phi_eta_nf;
  TH2 *EEMC_elec_phi_eta_pf;
  TH2 *CEMC_elec_etruth_e;
  TH2 *CEMC_elec_ptruth_e;
  TH2 *CEMC_elec_p_ptruth;
  TH2 *CEMC_elec_dpp_ptruth;
  TH2 *CEMC_elec_dee_etruth;
  TH2 *CEMC_elec_dee_etruth_cor;
  TH2 *CEMC_elec_dee_etruth_cut;
  TH2 *CEMC_elec_Ep;
  //pi-
  TH2 *EEMC_pi_etruth_e;
  TH2 *EEMC_pi_ptruth_e;
  TH2 *EEMC_pi_p_ptruth;
  TH2 *EEMC_pi_Ep;
  TH2 *CEMC_pi_etruth_e;
  TH2 *CEMC_pi_ptruth_e;
  TH2 *CEMC_pi_p_ptruth;
  TH2 *CEMC_pi_Ep;
  //pi+
  TH2 *EEMC_pip_etruth_e;
  TH2 *EEMC_pip_ptruth_e;
  TH2 *EEMC_pip_p_ptruth;
  TH2 *EEMC_pip_dpp_ptruth;
  TH2 *EEMC_pip_Ep;
  TH1 *EEMC_pip_no_epcut;
  TH1 *EEMC_pip_epcut;
  
  TH2 *CEMC_pip_etruth_e;
  TH2 *CEMC_pip_ptruth_e;
  TH2 *CEMC_pip_p_ptruth;
  TH2 *CEMC_pip_dpp_ptruth;
  TH2 *CEMC_pip_Ep;
  //gamma
  TH2 *EEMC_gamma_etruth_e;
  TH2 *EEMC_gamma_ptruth_e;
  TH2 *EEMC_gamma_p_ptruth;
  TH2 *CEMC_gamma_etruth_e;
  TH2 *CEMC_gamma_ptruth_e;
  TH2 *CEMC_gamma_p_ptruth;
  // 1D #particle vs p for e-,e+,pi-,pi+
  TH1 *EEMC_gamma;
  TH1 *EEMC_elec;
  TH1 *EEMC_pos;
  TH1 *EEMC_pi;
  TH1 *EEMC_piplus;
  TH1 *CEMC_gamma;
  TH1 *CEMC_elec;
  TH1 *CEMC_pos;
  TH1 *CEMC_pi;
  TH1 *CEMC_piplus;
  // 2D E vs eta  p for e-,e+,pi-,pi+
  TH2 *EEMC_gamma_Eveta;
  TH2 *EEMC_elec_Eveta;
  TH2 *EEMC_pos_Eveta;
  TH2 *EEMC_pi_Eveta;
  TH2 *EEMC_piplus_Eveta;
  TH2 *CEMC_gamma_Eveta;
  TH2 *CEMC_elec_Eveta;
  TH2 *CEMC_pos_Eveta;
  TH2 *CEMC_pi_Eveta;
  TH2 *CEMC_piplus_Eveta;
  
  /// HEPMC Tree variables
  int m_partid1;
  int m_partid2;
  double m_x1;
  double m_x2;
  int m_mpi;
  int m_process_id;
  double m_truthenergy;
  double m_trutheta;
  double m_truthphi;
  double m_truthpx;
  double m_truthpy;
  double m_truthpz;
  double m_truthpt;
  double m_truthp;
  int m_numparticlesinevent;
  int m_truthpid;

  /// Track variables
  double m_tr_px;
  double m_tr_py;
  double m_tr_pz;
  double m_tr_p;
  double m_tr_pt;
  double m_tr_phi;
  double m_tr_eta;
  int m_charge;
  double m_chisq;
  int m_ndf;
  double m_dca;
  double m_tr_x;
  double m_tr_y;
  double m_tr_z;
  int m_truth_is_primary;
  double m_truthtrackpx;
  double m_truthtrackpy;
  double m_truthtrackpz;
  double m_truthtrackp;
  double m_truthtracke;
  double m_truthtrackpt;
  double m_truthtrackphi;
  double m_truthtracketa;
  int m_truthtrackpid;
  /// Cluster variables
  double m_clusenergy;
  double m_cluseta;
  double m_clustheta;
  double m_cluspt;
  double m_clusphi;
  double m_cluspx;
  double m_cluspy;
  double m_cluspz;
  double m_E_4x4;
};

#endif // EM_CALO_H
