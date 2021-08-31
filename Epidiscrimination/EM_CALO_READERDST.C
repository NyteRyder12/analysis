#ifndef MACRO_FUN4ALL_READDST_C
#define MACRO_FUN4ALL_READDST_C


#include <GlobalVariables.C>

#include <DisplayOn.C>
#include <G4Setup_EICDetector.C>
#include <G4_Input.C>
#include <G4_FwdJets.C>
#include <G4_Global.C>

#include <em_calo/EM_CALO.h>

#include <TROOT.h>
#include <fun4all/Fun4AllDstOutputManager.h>
#include <fun4all/Fun4AllOutputManager.h>
#include <fun4all/Fun4AllServer.h>

#include <phool/recoConsts.h>


R__LOAD_LIBRARY(libfun4all.so)
R__LOAD_LIBRARY(libanatutorialecce.so)



int EM_CALO_READERDST(const int nEvents =200000,

		      //const string& inputFile = "/home/keaghan/analysis/sourcefiles/electronsall",
		      const string& inputFile = "/home/keaghan/analysis/sourcefiles/pionsall",
		      //const string& inputFile = "/home/keaghan/analysis/sourcefiles/highpythiaall",
		      //const string& inputFile = "/home/keaghan/analysis/sourcefiles/lowpythiaall",
		      //const string& inputFile = "/home/keaghan/analysis/sourcefiles/elecpionalot",

		      const string &outputFile = "alotof")

{
  //---------------
  // Fun4All server
  //---------------
  Fun4AllServer *se = Fun4AllServer::instance();
  se->Verbosity(1);

  // just if we set some flags somewhere in this macro
  recoConsts *rc = recoConsts::instance();
  
  Enable::IP6 = true;

  Input::READHITS = true;
  //INPUTREADHITS::filename[0] = inputFile;
  INPUTREADHITS::listfile[0] = inputFile;
EM_CALO *em_calo = new EM_CALO("em_calo", outputFile + "pions100000.root");
  //anaTutorial->setMinJetPt(3.);
  //anaTutorial->Verbosity(0);
  em_calo->analyzeTracks(false);
  em_calo->analyzeClusters(false);
  //anaTutorial->analyzeJets(true);
  em_calo->analyzeTruth(false);
  em_calo->analyzeTower(false); // process_towers function
  em_calo->emcalo_analysis(true);
  em_calo->reco_e_threshold(0);
  se->registerSubsystem(em_calo);

   /*
  AnaTutorialECCE *anaTutorial = new AnaTutorialECCE("anaTutorial", outputFile + "_anaTutorial.root");
  anaTutorial->setMinJetPt(3.);
  anaTutorial->Verbosity(0);
  anaTutorial->analyzeTracks(true);
  anaTutorial->analyzeClusters(true);
  anaTutorial->analyzeJets(true);
  anaTutorial->analyzeTruth(false);
  se->registerSubsystem(anaTutorial);
  */
  InputManagers();

  se->run(nEvents);

  se->End();
  
  delete se;
  std::cout << "All done processing" << std::endl;
  gSystem->Exit(0);
  return 0;

}
#endif
