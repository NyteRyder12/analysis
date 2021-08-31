
#include "TFile.h"

using namespace std;

  /*
    1:pvsp
    2:gamma
    3:electron
    4:pin
    5:pip
    6:particle#
    7:EvsEta
    8:electronadd
    9:pipadd
    10:electronandpip
    11:Clusters
   */
void Histomaker(int flag=0){
  

  //TFile *f=new TFile("alotofelectronsandpions.root");
  //TFile *f=new TFile("alotofelectrons100000minenergytest.root");
  //TFile *f=new TFile("alotofpionsnew100000.root");
  TFile *f=new TFile("10lowfiles.root");
  
  if (f == 0) {
  // If we cannot open the ROOT file, print an error message and return immediately.
  printf("Error: cannot open http://root.cern/files/introtutorials/eventdata.root!\n");
  return;
  }
  TString status;
  TString parastring;
  TString Title = "";
  
  int bin =0;
  double ratio=1;
  double entries=0;
  double entries1=0;
  double entries2=0;
  TPaveText *Tpara;
  TPaveText *Epara;
  
  TH1F *e;

  e = (TH1F*)f->Get("events");
  entries = e->GetEntries();


  
  TH1F *chi =  new TH1F("EEchi^2","Particles",1000,0,10);
  TH1F *chi1 =  new TH1F("CEchi^2","Particles",1000,0,10);
  TH1F *chi2 =  new TH1F("CPchi^2","Particles",1000,0,10);
  TH1F *chi3 =  new TH1F("EPchi^2","Particles",1000,0,10);
  TH1F *chi4 =  new TH1F("CdpPchi^2","Particles",1000,0,10);
  TH1F *chi5 =  new TH1F("EdpPchi^2","Particles",1000,0,10);
  TH1F *chi6 =  new TH1F("CdeEchi^2","Particles",1000,0,10);
  TH1F *chi7 =  new TH1F("EdeEchi^2","Particles",1000,0,10);

  TCanvas *C = new TCanvas("C","tower",1000,900);
  TCanvas *C1 = new TCanvas("C1","tower",1200,900);
  TCanvas *C2 = new TCanvas("C2","tower",1200,900);
  TCanvas *Cchi = new TCanvas("Cchi","tower",1200,900);
  TCanvas *Cpara = new TCanvas("Cpara","tower",1200,900);
  TCanvas *Cchi1 = new TCanvas("Cchi1","tower",1200,900);
  TCanvas *Cpara1 = new TCanvas("Cpara1","tower",1200,900);
  TCanvas *Cchi2 = new TCanvas("Cchi2","tower",1200,900);
  TCanvas *Cpara2 = new TCanvas("Cpara2","tower",1200,900);
  TCanvas *Cchi3 = new TCanvas("Cchi3","tower",1200,900);
  TCanvas *Cpara3 = new TCanvas("Cpara3","tower",1200,900);
  TCanvas *Cchi4 = new TCanvas("Cchi4","tower",1200,900);
  TCanvas *Cpara4 = new TCanvas("Cpara4","tower",1200,900);
  TCanvas *Cchi5 = new TCanvas("Cchi5","tower",1200,900);
  TCanvas *Cpara5 = new TCanvas("Cpara5","tower",1200,900);
  TCanvas *Cchi6 = new TCanvas("Cchi6","tower",1200,900);
  TCanvas *Cpara6 = new TCanvas("Cpara6","tower",1200,900);
  TCanvas *Cchi7 = new TCanvas("Cchi7","tower",1200,900);
  TCanvas *Cpara7 = new TCanvas("Cpara7","tower",1200,900);
  TCanvas *EPC = new TCanvas("EPC","tower",1200,900);
  TCanvas *EPC1 = new TCanvas("EPC1","tower",1200,900);
  TCanvas *EPC2 = new TCanvas("EPC2","tower",1200,900);
  TCanvas *EPC3 = new TCanvas("EPC3","tower",1200,900);
  TCanvas *EPC4 = new TCanvas("EPC4","tower",1200,900);
  TCanvas *EPC5 = new TCanvas("EPC5","tower",1200,900);
  TCanvas *EPC6 = new TCanvas("EPC6","tower",1200,900);
  TCanvas *EPC7 = new TCanvas("EPC7","tower",1200,900);
  TCanvas *EPC8 = new TCanvas("EPC8","tower",1200,900);
  TCanvas *EPC9 = new TCanvas("EPC9","tower",1200,900);

  TLegend *l5=new TLegend(.8,.7,.7,.8);
  TLegend *l4=new TLegend(.8,.7,.7,.8);
  TString s4[5];
  
  TLegend *EPl=new TLegend(.85,.5,.7,.85);
  TString EP[2];

  TF1 *F1 = new TF1("F1","[0]*exp(-0.5*((x-[1])/[2])^2)");
  TF1 *F2 = new TF1("F2","sqrt(pow([0]/sqrt(x),2)+pow([1]/x,2)+[2])");

  TF1 *F3 = new TF1("F3","sqrt(pow([0]*x,2)+pow([1],2))");

  TF1 *F4 = new TF1("F4","[0]*x+[1]");
  TF1 *F5 = new TF1("F5","sqrt(pow([0]/sqrt(x),2)+[1])");
  
  TH2F *E95eintegral =new TH2F("E 95e",";Eavg;E percent",1000,0,20,1000,0,1.5);
  TH2F *E95pipintegral =new TH2F("E 95pip",";Eavg;E percent",1000,0,20,1000,0,1.5);
  TH2F *C95eintegral =new TH2F("C 95e",";Eavg;C percent",1000,0,20,1000,0,1.5);
  TH2F *E90eintegral =new TH2F("E 90e",";Eavg;E percent",1000,0,20,1000,0,1.5);
  TH2F *C90eintegral =new TH2F("C 90e",";Eavg;C percent",1000,0,20,1000,0,1.5);
  TH1F *divide = new TH1F("EEMC pip divition",";",5000,0,700);
  
  TH2F *h[4];
  TH2F *h1[4];
  TH2F *h2[6];
  TH2F *h3[6];
  TH2F *h3p[6];

  TH1F *h4[5];
  TH1F *h5[5];

  TH2F *h6[5];
  TH2F *h7[5];

  TH1D *p[4];
  TH1D *p1[4];
  TH1D *p2[4];
  TH1D *p3[4];
  TH1D *p4[20];
  TH1D *p5[20];
  TH1D *p6[20];
  TH1D *pc6[20];
  TH1D *Pc6[20];
  TH1D *Pc7[20];
  TH1D *Pe6[20];
  TH1D *Pe7[20];
  TH1D *Ec7[20];
  TH1D *Ee7[20];

  double x[20];
  double y[20];
  double ex[20];
  double ey[20];
  auto para = new TGraphErrors;
  double x1[20];
  double y1[20];
  double ex1[20];
  double ey1[20];
  auto para1 = new TGraphErrors;
  double x2[20];
  double y2[20];
  double ex2[20];
  double ey2[20];
  auto para2 = new TGraphErrors;
  double x3[20];
  double y3[20];
  double ex3[20];
  double ey3[20];
  auto para3 = new TGraphErrors;
  double x4[20];
  double y4[20];
  double ex4[20];
  double ey4[20];
  auto para4 = new TGraphErrors;
  double x5[20];
  double y5[20];
  double ex5[20];
  double ey5[20];
  auto para5 = new TGraphErrors;
  double x6[20];
  double y6[20];
  double ex6[20];
  double ey6[20];
  auto para6 = new TGraphErrors;
  double x7[20];
  double y7[20];
  double ex7[20];
  double ey7[20];
  auto para7 = new TGraphErrors;

  switch(flag){
     
  case 1:
  
    h[0] = (TH2F*)f->Get("E e- ptruth vs dpp");
    h[1] = (TH2F*)f->Get("E pi+ ptruth vs p");
    h[2] = (TH2F*)f->Get("C e- ptruth vs dpp");
    h[3] = (TH2F*)f->Get("C pi+ ptruth vs p");
    
    h[0]->SetMarkerColor(2);
    h[1]->SetMarkerColor(4);
    h[2]->SetMarkerColor(2);
    h[3]->SetMarkerColor(4);
    
    C->Divide(2,3);
    
    for(int i=0;i<4;i++){
      C->cd(i+1);
      h[i]->SetMarkerSize(.5);
      h[i]->SetMarkerStyle(21);
      h[i]->Draw();
    }
    C->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/pvsptruth.png");
    break;
    
  case 2:

    h1[0] = (TH2F*)f->Get("E gamma E truth vs E det");
    h1[1] = (TH2F*)f->Get("E gamma P truth vs E det");
    h1[2] = (TH2F*)f->Get("C gamma E truth vs E det");
    h1[3] = (TH2F*)f->Get("C gamma P truth vs E det");
    
    C->Divide(2,3);
    
    for(int i=0;i<4;i++){
      C->cd(i+1);
      h1[i]->SetMarkerSize(.5);
      h1[i]->SetMarkerColor(2);
      h1[i]->SetMarkerStyle(21);
      h1[i]->Draw();
    }
    C->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/gamma.png");
    break;
    
  case 3:
    
    h2[0] = (TH2F*)f->Get("E e- E truth vs E det");
    h2[1] = (TH2F*)f->Get("E e- P truth vs E det");
    h2[2] = (TH2F*)f->Get("E e- Ep");
    h2[3] = (TH2F*)f->Get("C e- E truth vs E det");
    h2[4] = (TH2F*)f->Get("C e- P truth vs E det");
    h2[5] = (TH2F*)f->Get("C e- Ep");
    
    C->Divide(2,3);
    h2[0]->SetAxisRange(0,20,"Y"); 
    h2[3]->SetAxisRange(0,20,"Y"); 
    
    for(int i=0;i<6;i++){
      C->cd(i+1);
      h2[i]->SetMarkerSize(.5);
      h2[i]->SetMarkerColor(2);
      h2[i]->SetMarkerStyle(21);
      h2[i]->Draw();
    }
    
    C->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/electron.png");
    break;
    
  case 4:

    h3[0] = (TH2F*)f->Get("E pi- E truth vs E det");
    h3[1] = (TH2F*)f->Get("E pi- P truth vs E det");
    h3[2] = (TH2F*)f->Get("E pi- Ep");
    h3[3] = (TH2F*)f->Get("C pi- E truth vs E det");
    h3[4] = (TH2F*)f->Get("C pi- P truth vs E det");
    h3[5] = (TH2F*)f->Get("C pi- Ep");
    
    C->Divide(2,3);
    
    for(int i =0;i<6;i++)
      {
	C->cd(i+1);
	h3[i]->SetMarkerSize(.5);
	h3[i]->SetMarkerColor(2);
	h3[i]->SetMarkerStyle(21);
	h3[i]->Draw();
      }
    C->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/pin.png");
    break;
    
  case 5:
    
    h3p[0] = (TH2F*)f->Get("E pi+ E truth vs E det");
    h3p[1] = (TH2F*)f->Get("E pi+ P truth vs E det");
    h3p[2] = (TH2F*)f->Get("E pi+ Ep");
    h3p[3] = (TH2F*)f->Get("C pi+ E truth vs E det");
    h3p[4] = (TH2F*)f->Get("C pi+ P truth vs E det");
    h3p[5] = (TH2F*)f->Get("C pi+ Ep");
    C->Divide(2,3);
    
    h3p[0]->SetAxisRange(0,20,"Y"); 
    h3p[3]->SetAxisRange(0,20,"Y"); 
    for(int i =0;i<6;i++)
      {
	C->cd(i+1);
	//      gPad->SetLogz();
	h3p[i]->SetMarkerSize(.3);
	h3p[i]->SetMarkerColor(4);
	h3p[i]->SetMarkerStyle(21);
	h3p[i]->Draw();
      }
    C->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/pip.png");  
    break;
    
  case 6:
    C->cd();
    h4[0] = (TH1F*)f->Get("E gamma#");
    h4[1] = (TH1F*)f->Get("E elec#");
    h4[2] = (TH1F*)f->Get("E pos#");
    h4[3] = (TH1F*)f->Get("E pi#");
    h4[4] = (TH1F*)f->Get("E piplus#");
    //C4->Divide(2,3);
    gPad->SetLogy();
    gPad->SetLogx();
    gStyle->SetOptStat(0);

    s4[0]="gamma";
    s4[1]="e-";
    s4[2]="e+";
    s4[3]="pi-";
    s4[4]="pi+";
    for(int i =0;i<5;i++)
      {
	//C->cd(i+1);
	l4->AddEntry(h4[i],s4[i],"P");
	h4[i]->Rebin(4);
	h4[i]->SetMarkerSize(.5);
	h4[i]->SetMarkerColor(i+1);
	h4[i]->SetLineColor(i+1);
	h4[i]->SetMarkerStyle(21);
	h4[i]->Scale(1/entries);
	h4[i]->SetAxisRange(.16,20,"X");
	//h4[i]->SetAxisRange(1,10000,"Y");
	if (i!=0){h4[i]->Draw("same");}
	else
	  {
	    h4[i]->Draw();
	    h4[i]->SetTitle("Generated Particles in EEMC for low Q2");
	    h4[i]->SetXTitle("p(GeV)");
	    h4[i]->SetYTitle("#particles/events");
	  }
      }
    l4->Draw();
    C->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/EEMCpart#.png");
    

    C1->cd();
    h5[0] = (TH1F*)f->Get("C gamma#");
    h5[1] = (TH1F*)f->Get("C elec#");
    h5[2] = (TH1F*)f->Get("C pos#");
    h5[3] = (TH1F*)f->Get("C pi#");
    h5[4] = (TH1F*)f->Get("C piplus#");
    gPad->SetLogy();
    gPad->SetLogx();
    gStyle->SetOptStat(0);
    for(int i =0;i<5;i++)
      {
	l5->AddEntry(h5[i],s4[i],"P");
	h5[i]->Rebin(4);
	h5[i]->SetMarkerSize(.5);
	h5[i]->SetMarkerColor(i+1);
	h5[i]->SetLineColor(i+1);
	h5[i]->SetMarkerStyle(21);
	h5[i]->Scale(1/entries);
	h5[i]->SetAxisRange(.16,25,"X"); 
	if (i!=0){h5[i]->Draw("same");}
	else
	  {
	    h5[i]->Draw();
	    h5[i]->SetTitle("Generated Particles in CEMC for low Q2");
	    h5[i]->SetXTitle("p(GeV)");
	    h5[i]->SetYTitle("#particles/events");
	  }
      }
    l5->Draw();
    
    C1->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/CEMCpart#.png");
    break;
    
  case 7:
    
    h6[0] = (TH2F*)f->Get("E gamma Eveta");
    h6[1] = (TH2F*)f->Get("E elec Eveta");
    h6[2] = (TH2F*)f->Get("E pos Eveta");
    h6[3] = (TH2F*)f->Get("E pi Eveta");
    h6[4] = (TH2F*)f->Get("E piplus Eveta");
    
    
    C->Divide(2,3);
    
    for(int i =0;i<5;i++)
      {
	C->cd(i+1);
	h6[i]->SetMarkerSize(.5);
	h6[i]->SetMarkerColor(2);
	h6[i]->SetMarkerStyle(21);
	h6[i]->Draw();
      }
    C->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/EEMCpartEvsEta.png");
  
    
    h7[0] = (TH2F*)f->Get("C gamma Eveta");
    h7[1] = (TH2F*)f->Get("C elec Eveta");
    h7[2] = (TH2F*)f->Get("C pos Eveta");
    h7[3] = (TH2F*)f->Get("C pi Eveta");
    h7[4] = (TH2F*)f->Get("C piplus Eveta");
    
    C1->Divide(2,3);
    
    for(int i =0;i<5;i++)
      {
	C1->cd(i+1);
	h7[i]->SetMarkerSize(.5);
	h7[i]->SetMarkerColor(2);
	h7[i]->SetMarkerStyle(21);
	h7[i]->Draw();
      }
    C1->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/CEMCpartEvsEta.png");
    break;
    
  case 8:
    h2[0] = (TH2F*)f->Get("E e- E truth vs E det");
    h2[1] = (TH2F*)f->Get("E e- P truth vs E det");
    h2[2] = (TH2F*)f->Get("E e- Ep");
    h2[3] = (TH2F*)f->Get("C e- E truth vs E det");
    h2[4] = (TH2F*)f->Get("C e- P truth vs E det");
    h2[5] = (TH2F*)f->Get("C e- Ep");
    
    h[0] = (TH2F*)f->Get("E e- ptruth vs p");  
    h[2] = (TH2F*)f->Get("C e- ptruth vs p");
    h[1] = (TH2F*)f->Get("E e- ptruth vs dpp");
    h[3] = (TH2F*)f->Get("C e- ptruth vs dpp");
    
    h1[1] = (TH2F*)f->Get("E e- cut etruth vs dee");
    h1[3] = (TH2F*)f->Get("C e- cut etruth vs dee");
    
    entries1=h1[1]->GetEntries();
    entries2=h1[3]->GetEntries();

    p[0]= h2[1]->ProjectionY("proj1",10,10);
    p[1]= h2[1]->ProjectionY("proj2",1,1);
    p[2]= h2[4]->ProjectionY("proj3",10,10);
    p[3]= h2[4]->ProjectionY("proj4",1,1);
    p[0]->SetTitle("EEMC 10Gev");
    p[1]->SetTitle("EEMC 1Gev");
    p[2]->SetTitle("CEMC 10Gev");
    p[3]->SetTitle("CEMC 1Gev");
    
    C->Divide(2,2);
    for(int i =0;i<4;i++)
      {
	C->cd(i+1);
	p[i]->SetMarkerSize(.5);
	p[i]->SetMarkerColor(2);
	p[i]->SetMarkerStyle(21);
	p[i]->Draw();
      }
    C->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/10&1GeVe-.png");

    
    p1[0]= h2[2]->ProjectionY("Proj5",10,10);
    p1[1]= h2[2]->ProjectionY("Proj6",1,1);
    p1[2]= h2[5]->ProjectionY("Proj7",10,10);
    p1[3]= h2[5]->ProjectionY("Proj8",1,1);
    p1[0]->SetTitle("EEMC E/p 10Gev");
    p1[1]->SetTitle("EEMC E/p 1Gev");
    p1[2]->SetTitle("CEMC E/p 10Gev");
    p1[3]->SetTitle("CEMC E/p 1Gev");
    
    
    C1->Divide(2,2);
    for(int i =0;i<4;i++)
      {
	C1->cd(i+1);
	p1[i]->SetMarkerSize(.5);
	p1[i]->SetMarkerColor(2);
	p1[i]->SetMarkerStyle(21);
	p1[i]->Draw();
      }
    C1->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/10&1Epe-.png");
    
    p6[0]=h2[0]->ProjectionY("EE1",1,20);
    p6[1]=h2[0]->ProjectionY("EE2",21,40);
    p6[2]=h2[0]->ProjectionY("EE3",41,60);
    p6[3]=h2[0]->ProjectionY("EE4",61,80);
    p6[4]=h2[0]->ProjectionY("EE5",81,100);
    p6[5]=h2[0]->ProjectionY("EE6",101,120);
    p6[6]=h2[0]->ProjectionY("EE7",121,140);
    p6[7]=h2[0]->ProjectionY("EE8",141,160);
    p6[8]=h2[0]->ProjectionY("EE9",161,180);
    p6[9]=h2[0]->ProjectionY("EE10",181,200);
    p6[10]=h2[0]->ProjectionY("EE11",201,220);
    p6[11]=h2[0]->ProjectionY("EE12",221,240);
    p6[12]=h2[0]->ProjectionY("EE13",241,260);
    p6[13]=h2[0]->ProjectionY("EE14",261,280);
    p6[14]=h2[0]->ProjectionY("EE15",281,300);
    p6[15]=h2[0]->ProjectionY("EE16",301,320);
    p6[16]=h2[0]->ProjectionY("EE17",321,340);
    p6[17]=h2[0]->ProjectionY("EE18",341,360);
    p6[18]=h2[0]->ProjectionY("EE19",361,380);
    p6[19]=h2[0]->ProjectionY("EE20",381,400);
    EPC2->Divide(4,5);
    F1->SetLineColor(4);
    
    for(int i =0;i<20;i++)
      {
	p6[i]->Rebin(5);
	p6[i]->SetMarkerSize(.5);
	p6[i]->SetMarkerColor(2);
	p6[i]->SetLineColor(2);
	p6[i]->SetMarkerStyle(21);
	EPC2->cd(i+1);
	p6[i]->Draw();
	
	F1->SetParameters(p6[i]->GetMaximum(),p6[i]->GetMean(),0.5*(p6[i]->GetRMS()));
		
        status = "nope";
	for(int d=2; ((status !="CONVERGED ") || (F1->GetParameter(2) <0));d++){
	  F1->SetParameters(p6[i]->GetMaximum(),p6[i]->GetMean(),0.5*(p6[i]->GetRMS()));
	  
	  p6[i]->Fit("F1","","",p6[i]->GetMean()-d*(p6[i]->GetRMS()),p6[i]->GetMean()+d*(p6[i]->GetRMS()));
	  status = gMinuit->fCstatu;
	  cout <<status<<""<<i<<endl;
	  }	
	
	chi->Fill((F1->GetChisquare())/(F1->GetNDF()));
	y[i]=F1->GetParameter(2)/F1->GetParameter(1);
	x[i]=F1->GetParameter(1);
	ey[i]=y[i]*sqrt(pow(F1->GetParError(2)/F1->GetParameter(2),2)+pow(F1->GetParError(1)/F1->GetParameter(1),2));
	ex[i]=F1->GetParError(1);
	  
	cout <<"mean: "<<p6[i]->GetMean()<<endl;
	cout <<"RMS: "<<p6[i]->GetRMS()<<endl;
	
	p6[i]->SetXTitle("");
	//p6[i]->SetYTitle("#particles");
	p6[i]->SetLabelSize(.1,"Y");
	p6[i]->SetLabelSize(.1,"X");
	p6[i]->SetTitleSize(.1,"Y");
	p6[i]->SetTitleOffset(.35,"Y");
	}
    EPC2->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/EEMCe-E.png");
    Cchi->cd();
    chi->Draw();
    Cchi->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/Echi.png");
    Cpara->cd();
    para = new TGraphErrors(20,x,y,ex,ey);
    para->Fit("F2","","",0,20);
    para->SetMinimum(0);

    para->SetMarkerColor(2);
    para->SetMarkerSize(.5);
    para->SetMarkerStyle(21);
    para->SetTitle("EEMC resolution;E reco;#sigma_{e}/E");
    /*
    parastring = "a = "+std::to_string(F2->GetParameter(0))+" b= "+std::to_string(F2->GetParameter(1))+" c= "+std::to_string(F2->GetParameter(2));
    Epara = new TPaveText(10,.6,10,.6);
    Tpara = new TPaveText(10,.5,10,.5);
    Epara->SetTextColor(1);
    Epara->SetTextFont(43);
    Epara->SetTextSize(40);
    Epara->AddText("#frac{a}{#sqrt{E}} + #frac{b}{E} + c");
    Tpara->SetTextColor(1);
    Tpara->SetTextFont(43);
    Tpara->SetTextSize(40);
    Tpara->AddText(parastring);*/
    para->Draw("ap");
    /* Tpara->Draw("same");
       Epara->Draw("same");  */
    Cpara->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/Epara.png");
    
            
    pc6[0]=h2[3]->ProjectionY("CE1",1,20);
    pc6[1]=h2[3]->ProjectionY("CE2",21,40);
    pc6[2]=h2[3]->ProjectionY("CE3",41,60);
    pc6[3]=h2[3]->ProjectionY("CE4",61,80);
    pc6[4]=h2[3]->ProjectionY("CE5",81,100);
    pc6[5]=h2[3]->ProjectionY("CE6",101,120);
    pc6[6]=h2[3]->ProjectionY("CE7",121,140);
    pc6[7]=h2[3]->ProjectionY("CE8",141,160);
    pc6[8]=h2[3]->ProjectionY("CE9",161,180);
    pc6[9]=h2[3]->ProjectionY("CE10",181,200);
    pc6[10]=h2[3]->ProjectionY("CE11",201,220);
    pc6[11]=h2[3]->ProjectionY("CE12",221,240);
    pc6[12]=h2[3]->ProjectionY("CE13",241,260);
    pc6[13]=h2[3]->ProjectionY("CE14",261,280);
    pc6[14]=h2[3]->ProjectionY("CE15",281,300);
    pc6[15]=h2[3]->ProjectionY("CE16",301,320);
    pc6[16]=h2[3]->ProjectionY("CE17",321,340);
    pc6[17]=h2[3]->ProjectionY("CE18",341,360);
    pc6[18]=h2[3]->ProjectionY("CE19",361,380);
    pc6[19]=h2[3]->ProjectionY("CE20",381,400);
    EPC3->Divide(4,5);
    
    for(int i =0;i<20;i++)
      {
	pc6[i]->Rebin(5);
	pc6[i]->SetMarkerSize(.5);
	pc6[i]->SetMarkerColor(2);
	pc6[i]->SetLineColor(2);
	pc6[i]->SetMarkerStyle(21);
	EPC3->cd(i+1);
	pc6[i]->Draw();
	
	F1->SetParameters(pc6[i]->GetMaximum(),pc6[i]->GetMean(),0.5*(pc6[i]->GetRMS()));
		
        status = "nope";
	for(int d=2; ((status !="CONVERGED ") || (F1->GetParameter(2) <0));d++){
	  F1->SetParameters(pc6[i]->GetMaximum(),pc6[i]->GetMean(),0.5*(pc6[i]->GetRMS()));
	  
	  pc6[i]->Fit("F1","","",pc6[i]->GetMean()-d*(pc6[i]->GetRMS()),pc6[i]->GetMean()+d*(pc6[i]->GetRMS()));
	  status = gMinuit->fCstatu;
	  cout <<status<<""<<i<<endl;
	  }		
	chi1->Fill((F1->GetChisquare())/(F1->GetNDF()));
	y1[i]=F1->GetParameter(2)/F1->GetParameter(1);
	x1[i]=F1->GetParameter(1);
	ey1[i]=y1[i]*sqrt(pow(F1->GetParError(2)/F1->GetParameter(2),2)+pow(F1->GetParError(1)/F1->GetParameter(1),2));
	ex1[i]=F1->GetParError(1);
	  
	cout <<"mean: "<<pc6[i]->GetMean()<<endl;
	cout <<"RMS: "<<pc6[i]->GetRMS()<<endl;
	
	pc6[i]->SetXTitle("");
	pc6[i]->SetYTitle("#particles");
	pc6[i]->SetLabelSize(.1,"Y");
	pc6[i]->SetLabelSize(.1,"X");
	pc6[i]->SetTitleSize(.1,"Y");
	pc6[i]->SetTitleOffset(.35,"Y");
      }
    EPC3->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/CEMCe-E.png");
    Cchi1->cd();
    chi1->Draw();
    Cchi1->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/Cchi.png");
    Cpara1->cd();
    para1 = new TGraphErrors(20,x1,y1,ex1,ey1);
    para1->Fit("F2","","",0,20);
    para1->SetMinimum(0);
    // para1->SetMaximum(1);
    para1->SetMarkerColor(2);
    para1->SetMarkerSize(.5);
    para1->SetMarkerStyle(21);
    para1->SetTitle("CEMC resolution;E reco;#sigma_{e}/E");
    /*
    parastring = "a = "+std::to_string(F2->GetParameter(0))+" b= "+std::to_string(F2->GetParameter(1))+" c= "+std::to_string(F2->GetParameter(2));
    Epara = new TPaveText(10,.9,10,.9);
    Tpara = new TPaveText(10,.8,10,.8);
    Epara->SetTextColor(1);
    Epara->SetTextFont(43);
    Epara->SetTextSize(40);
    Epara->AddText("#frac{a}{#sqrt{E}} + #frac{b}{E} + c");
    Tpara->SetTextColor(1);
    Tpara->SetTextFont(43);
    Tpara->SetTextSize(40);
    Tpara->AddText(parastring);*/
    para1->Draw("ap");
    /* Tpara->Draw("same");
       Epara->Draw("same");*/
    Cpara1->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/Cpara.png");

    
    Pc6[0]=h[2]->ProjectionY("CP1",1,40);
    Pc6[1]=h[2]->ProjectionY("CP2",41,80);
    Pc6[2]=h[2]->ProjectionY("CP3",81,120);
    Pc6[3]=h[2]->ProjectionY("CP4",121,160);
    Pc6[4]=h[2]->ProjectionY("CP5",161,200);
    Pc6[5]=h[2]->ProjectionY("CP6",201,240);
    Pc6[6]=h[2]->ProjectionY("CP7",241,280);
    Pc6[7]=h[2]->ProjectionY("CP8",281,320);
    Pc6[8]=h[2]->ProjectionY("CP9",321,360);
    Pc6[9]=h[2]->ProjectionY("CP10",361,400);
    Pc6[10]=h[2]->ProjectionY("CP11",401,440);
    Pc6[11]=h[2]->ProjectionY("CP12",441,480);
    Pc6[12]=h[2]->ProjectionY("CP13",481,520);
    Pc6[13]=h[2]->ProjectionY("CP14",521,560);
    Pc6[14]=h[2]->ProjectionY("CP15",561,600);
    Pc6[15]=h[2]->ProjectionY("CP16",601,640);
    Pc6[16]=h[2]->ProjectionY("CP17",641,680);
    Pc6[17]=h[2]->ProjectionY("CP18",681,720);
    Pc6[18]=h[2]->ProjectionY("CP19",721,760);
    Pc6[19]=h[2]->ProjectionY("CP20",761,800);
    EPC4->Divide(4,5);
    
    for(int i =0;i<20;i++)
      {
	Pc6[i]->Rebin(5);
	Pc6[i]->SetMarkerSize(.5);
	Pc6[i]->SetMarkerColor(2);
	Pc6[i]->SetLineColor(2);
	Pc6[i]->SetMarkerStyle(21);
	//Pc6[i]->SetAxisRange(0,25,"X");
	EPC4->cd(i+1);
	Pc6[i]->Draw();
	
	F1->SetParameters(Pc6[i]->GetMaximum(),Pc6[i]->GetMean(),0.5*(Pc6[i]->GetRMS()));
		
        status = "nope";
	for(int d=2; ((status !="CONVERGED ") || (F1->GetParameter(2) <0));d++){
	  F1->SetParameters(Pc6[i]->GetMaximum(),Pc6[i]->GetMean(),0.5*(Pc6[i]->GetRMS()));
	  
	  Pc6[i]->Fit("F1","","",Pc6[i]->GetMean()-d*(Pc6[i]->GetRMS()),Pc6[i]->GetMean()+d*(Pc6[i]->GetRMS()));
	  status = gMinuit->fCstatu;
	  cout <<status<<""<<i<<endl;
	  }	
	
	chi2->Fill((F1->GetChisquare())/(F1->GetNDF()));
	y2[i]=F1->GetParameter(2)/F1->GetParameter(1);
	x2[i]=F1->GetParameter(1);
	ey2[i]=y1[i]*sqrt(pow(F1->GetParError(2)/F1->GetParameter(2),2)+pow(F1->GetParError(1)/F1->GetParameter(1),2));
	ex2[i]=F1->GetParError(1);
	  
	cout <<"mean: "<<Pc6[i]->GetMean()<<endl;
	cout <<"RMS: "<<Pc6[i]->GetRMS()<<endl;
	
	Pc6[i]->SetXTitle("");
	Pc6[i]->SetYTitle("#particles");
	Pc6[i]->SetLabelSize(.1,"Y");
	Pc6[i]->SetLabelSize(.1,"X");
	Pc6[i]->SetTitleSize(.1,"Y");
	Pc6[i]->SetTitleOffset(.35,"Y");
      }
    EPC4->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/CEMCe-P.png");
    
    Cchi2->cd();
    chi2->Draw();
    Cchi2->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/CPchi.png");
    Cpara2->cd();
    para2 = new TGraphErrors(20,x2,y2,ex2,ey2);
    
    para2->Fit("F3","","",0,20);
    para2->SetMinimum(0);
    para2->SetMaximum(.5);
    para2->SetMarkerColor(2);
    para2->SetMarkerSize(.5);
    para2->SetMarkerStyle(21);
    para2->Draw("ap");
    Cpara2->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/CPpara.png");
 
    cout<<h[2]->GetNbinsX()<<endl;
    
    Pe6[0]=h[0]->ProjectionY("EP1",1,40);
    Pe6[1]=h[0]->ProjectionY("EP2",41,80);
    Pe6[2]=h[0]->ProjectionY("EP3",81,120);
    Pe6[3]=h[0]->ProjectionY("EP4",121,160);
    Pe6[4]=h[0]->ProjectionY("EP5",161,200);
    Pe6[5]=h[0]->ProjectionY("EP6",201,240);
    Pe6[6]=h[0]->ProjectionY("EP7",241,280);
    Pe6[7]=h[0]->ProjectionY("EP8",281,320);
    Pe6[8]=h[0]->ProjectionY("EP9",321,360);
    Pe6[9]=h[0]->ProjectionY("EP10",361,400);
    Pe6[10]=h[0]->ProjectionY("EP11",401,440);
    Pe6[11]=h[0]->ProjectionY("EP12",441,480);
    Pe6[12]=h[0]->ProjectionY("EP13",481,520);
    Pe6[13]=h[0]->ProjectionY("EP14",521,560);
    Pe6[14]=h[0]->ProjectionY("EP15",561,600);
    Pe6[15]=h[0]->ProjectionY("EP16",601,640);
    Pe6[16]=h[0]->ProjectionY("EP17",641,680);
    Pe6[17]=h[0]->ProjectionY("EP18",681,720);
    Pe6[18]=h[0]->ProjectionY("EP19",721,760);
    Pe6[19]=h[0]->ProjectionY("EP20",761,800);
    EPC5->Divide(4,5);
    
    for(int i =0;i<20;i++)
      {
	Pe6[i]->Rebin(5);
	Pe6[i]->SetMarkerSize(.5);
	Pe6[i]->SetMarkerColor(2);
	Pe6[i]->SetLineColor(2);
	Pe6[i]->SetMarkerStyle(21);
	EPC5->cd(i+1);
	Pe6[i]->Draw();
	
	F1->SetParameters(Pe6[i]->GetMaximum(),Pe6[i]->GetMean(),0.5*(Pe6[i]->GetRMS()));
		
        status = "nope";
	for(int d=2; ((status !="CONVERGED ") || (F1->GetParameter(2) <0));d++){
	  F1->SetParameters(Pe6[i]->GetMaximum(),Pe6[i]->GetMean(),0.5*(Pe6[i]->GetRMS()));
	  
	  Pe6[i]->Fit("F1","","",Pe6[i]->GetMean()-d*(Pe6[i]->GetRMS()),Pe6[i]->GetMean()+d*(Pe6[i]->GetRMS()));
	  status = gMinuit->fCstatu;
	  cout <<status<<""<<i<<endl;
	  }	
	
	chi3->Fill((F1->GetChisquare())/(F1->GetNDF()));
	y3[i]=F1->GetParameter(2)/F1->GetParameter(1);
	x3[i]=F1->GetParameter(1);
	ey3[i]=y1[i]*sqrt(pow(F1->GetParError(2)/F1->GetParameter(2),2)+pow(F1->GetParError(1)/F1->GetParameter(1),2));
	ex3[i]=F1->GetParError(1);
	  
	cout <<"mean: "<<Pe6[i]->GetMean()<<endl;
	cout <<"RMS: "<<Pe6[i]->GetRMS()<<endl;
	
	Pe6[i]->SetXTitle("");
	Pe6[i]->SetYTitle("#particles");
	Pe6[i]->SetLabelSize(.1,"Y");
	Pe6[i]->SetLabelSize(.1,"X");
	Pe6[i]->SetTitleSize(.1,"Y");
	Pe6[i]->SetTitleOffset(.35,"Y");
      }
    EPC5->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/EEMCe-P.png");
    
    Cchi3->cd();
    chi3->Draw();
    Cchi3->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/EPchi.png");
    Cpara3->cd();
    para3 = new TGraphErrors(20,x3,y3,ex3,ey3);
    para3->Fit("F3","","",8,20);
    para3->SetMinimum(0);
    para3->SetMaximum(.5);
    para3->SetMarkerColor(2);
    para3->SetMarkerSize(.5);
    para3->SetMarkerStyle(21);
    para3->Draw("ap");
    Cpara3->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/EPpara.png");
    

    Pc7[0]=h[3]->ProjectionY("CdP1",1,40);
    Pc7[1]=h[3]->ProjectionY("CdP2",41,80);
    Pc7[2]=h[3]->ProjectionY("CdP3",81,120);
    Pc7[3]=h[3]->ProjectionY("CdP4",121,160);
    Pc7[4]=h[3]->ProjectionY("CdP5",161,200);
    Pc7[5]=h[3]->ProjectionY("CdP6",201,240);
    Pc7[6]=h[3]->ProjectionY("CdP7",241,280);
    Pc7[7]=h[3]->ProjectionY("CdP8",281,320);
    Pc7[8]=h[3]->ProjectionY("CdP9",321,360);
    Pc7[9]=h[3]->ProjectionY("CdP10",361,400);
    Pc7[10]=h[3]->ProjectionY("CdP11",401,440);
    Pc7[11]=h[3]->ProjectionY("CdP12",441,480);
    Pc7[12]=h[3]->ProjectionY("CdP13",481,520);
    Pc7[13]=h[3]->ProjectionY("CdP14",521,560);
    Pc7[14]=h[3]->ProjectionY("CdP15",561,600);
    Pc7[15]=h[3]->ProjectionY("CdP16",601,640);
    Pc7[16]=h[3]->ProjectionY("CdP17",641,680);
    Pc7[17]=h[3]->ProjectionY("CdP18",681,720);
    Pc7[18]=h[3]->ProjectionY("CdP19",721,760);
    Pc7[19]=h[3]->ProjectionY("CdP20",761,800);
    EPC6->Divide(4,5);
    
    for(int i =0;i<20;i++)
      {
	//Pc7[i]->Rebin(5);
	Pc7[i]->SetMarkerSize(.5);
	Pc7[i]->SetMarkerColor(2);
	Pc7[i]->SetLineColor(2);
	Pc7[i]->SetMarkerStyle(21);
	Pc7[i]->SetAxisRange(-.1,.1,"X");
	EPC6->cd(i+1);
	Pc7[i]->Draw();
	
	F1->SetParameters(Pc7[i]->GetMaximum(),Pc7[i]->GetMean(),0.5*(Pc7[i]->GetRMS()));
		
        status = "nope";
	for(int d=2; ((status !="CONVERGED ") || (F1->GetParameter(2) <0));d++){
	  F1->SetParameters(Pc7[i]->GetMaximum(),Pc7[i]->GetMean(),0.5*(Pc7[i]->GetRMS()));
	  
	  Pc7[i]->Fit("F1","","",Pc7[i]->GetMean()-d*(Pc7[i]->GetRMS()),Pc7[i]->GetMean()+d*(Pc7[i]->GetRMS()));
	  status = gMinuit->fCstatu;
	  cout <<status<<""<<i<<endl;
	  }	
	
	chi4->Fill((F1->GetChisquare())/(F1->GetNDF()));
	y4[i]=F1->GetParameter(2);
	x4[i]=(double)i+.5;
	ey4[i]=F1->GetParError(2);
	ex4[i]=F1->GetParError(1);
	
	cout <<"mean: "<<Pc7[i]->GetMean()<<endl;
	cout <<"RMS: "<<Pc7[i]->GetRMS()<<endl;
	
	Pc7[i]->SetXTitle("");
	Pc7[i]->SetYTitle("#particles");
	Pc7[i]->SetLabelSize(.1,"Y");
	Pc7[i]->SetLabelSize(.1,"X");
	Pc7[i]->SetTitleSize(.1,"Y");
	Pc7[i]->SetTitleOffset(.35,"Y");
      }
    EPC6->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/CEMCe-dpP.png");

    
    Cchi4->cd();
    chi4->Draw();
    Cchi4->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/CdpPchi.png");
    Cpara4->cd();
    para4 = new TGraphErrors(20,x4,y4,ex4,ey4);
    
    para4->Fit("F3","","",0,20);
    para4->SetMinimum(0);
    //para4->SetMaximum(.05);
    para4->SetMarkerColor(2);
    para4->SetMarkerSize(.5);
    para4->SetMarkerStyle(21);
    para4->SetTitle("CEMC tracker resolution;p(GeV);dp/p");
    para4->Draw("ap");
    Cpara4->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/CdpPpara.png");

    
    Pe7[0]=h[1]->ProjectionY("EdP1",1,40);
    Pe7[1]=h[1]->ProjectionY("EdP2",41,80);
    Pe7[2]=h[1]->ProjectionY("EdP3",81,120);
    Pe7[3]=h[1]->ProjectionY("EdP4",121,160);
    Pe7[4]=h[1]->ProjectionY("EdP5",161,200);
    Pe7[5]=h[1]->ProjectionY("EdP6",201,240);
    Pe7[6]=h[1]->ProjectionY("EdP7",241,280);
    Pe7[7]=h[1]->ProjectionY("EdP8",281,320);
    Pe7[8]=h[1]->ProjectionY("EdP9",321,360);
    Pe7[9]=h[1]->ProjectionY("EdP10",361,400);
    Pe7[10]=h[1]->ProjectionY("EdP11",401,440);
    Pe7[11]=h[1]->ProjectionY("EdP12",441,480);
    Pe7[12]=h[1]->ProjectionY("EdP13",481,520);
    Pe7[13]=h[1]->ProjectionY("EdP14",521,560);
    Pe7[14]=h[1]->ProjectionY("EdP15",561,600);
    Pe7[15]=h[1]->ProjectionY("EdP16",601,640);
    Pe7[16]=h[1]->ProjectionY("EdP17",641,680);
    Pe7[17]=h[1]->ProjectionY("EdP18",681,720);
    Pe7[18]=h[1]->ProjectionY("EdP19",721,760);
    Pe7[19]=h[1]->ProjectionY("EdP20",761,800);
    EPC7->Divide(4,5);
    
    for(int i =0;i<20;i++)
      {
	//Pe7[i]->Rebin(5);
	Pe7[i]->SetMarkerSize(.5);
	Pe7[i]->SetMarkerColor(2);
	Pe7[i]->SetLineColor(2);
	Pe7[i]->SetMarkerStyle(21);
	Pe7[i]->SetAxisRange(-.1,.1,"X");
	EPC7->cd(i+1);
	Pe7[i]->Draw();
	
	F1->SetParameters(Pe7[i]->GetMaximum(),Pe7[i]->GetMean(),0.5*(Pe7[i]->GetRMS()));
		
        status = "nope";
	for(int d=2; ((status !="CONVERGED ") || (F1->GetParameter(2) <0));d++){
	  F1->SetParameters(Pe7[i]->GetMaximum(),Pe7[i]->GetMean(),0.5*(Pe7[i]->GetRMS()));
	  
	  Pe7[i]->Fit("F1","","",Pe7[i]->GetMean()-d*(Pe7[i]->GetRMS()),Pe7[i]->GetMean()+d*(Pe7[i]->GetRMS()));
	  status = gMinuit->fCstatu;
	  cout <<status<<""<<i<<endl;
	}	
	
	chi5->Fill((F1->GetChisquare())/(F1->GetNDF()));
	y5[i]=F1->GetParameter(2);
	x5[i]= (double)i +.5;
	ey5[i]=F1->GetParError(2);
	ex5[i]=F1->GetParError(1);
	
	cout <<"mean: "<<Pe7[i]->GetMean()<<endl;
	cout <<"RMS: "<<Pe7[i]->GetRMS()<<endl;
	
	Pe7[i]->SetXTitle("");
	Pe7[i]->SetYTitle("#particles");
	Pe7[i]->SetLabelSize(.1,"Y");
	Pe7[i]->SetLabelSize(.1,"X");
	Pe7[i]->SetTitleSize(.1,"Y");
	Pe7[i]->SetTitleOffset(.35,"Y");
      }
    EPC7->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/EEMCe-dpP.png");

    Cchi5->cd();
    chi5->Draw();
    Cchi5->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/EdpPchi.png");
    Cpara5->cd();
    para5 = new TGraphErrors(20,x5,y5,ex5,ey5);
    
    para5->Fit("F3","","",0,20);
    para5->SetMinimum(0);
    //para5->SetMaximum(1);
    para5->SetMarkerColor(2);
    para5->SetMarkerSize(.5);
    para5->SetMarkerStyle(21);
    para5->SetTitle("EEMC tracker resolution;p(GeV);dp/p");
    para5->Draw("ap");
    Cpara5->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/EdpPpara.png");
    

    Ec7[0]=h1[3]->ProjectionY("Cde1",1,40);
    Ec7[1]=h1[3]->ProjectionY("Cde2",41,80);
    Ec7[2]=h1[3]->ProjectionY("Cde3",81,120);
    Ec7[3]=h1[3]->ProjectionY("Cde4",121,160);
    Ec7[4]=h1[3]->ProjectionY("Cde5",161,200);
    Ec7[5]=h1[3]->ProjectionY("Cde6",201,240);
    Ec7[6]=h1[3]->ProjectionY("Cde7",241,280);
    Ec7[7]=h1[3]->ProjectionY("Cde8",281,320);
    Ec7[8]=h1[3]->ProjectionY("Cde9",321,360);
    Ec7[9]=h1[3]->ProjectionY("Cde10",361,400);
    Ec7[10]=h1[3]->ProjectionY("Cde11",401,440);
    Ec7[11]=h1[3]->ProjectionY("Cde12",441,480);
    Ec7[12]=h1[3]->ProjectionY("Cde13",481,520);
    Ec7[13]=h1[3]->ProjectionY("Cde14",521,560);
    Ec7[14]=h1[3]->ProjectionY("Cde15",561,600);
    Ec7[15]=h1[3]->ProjectionY("Cde16",601,640);
    Ec7[16]=h1[3]->ProjectionY("Cde17",641,680);
    Ec7[17]=h1[3]->ProjectionY("Cde18",681,720);
    Ec7[18]=h1[3]->ProjectionY("Cde19",721,760);
    Ec7[19]=h1[3]->ProjectionY("Cde20",761,800);

    EPC8->Divide(4,5);
    
    for(int i =2;i<20;i++)
      {
	//Ec7[i]->Rebin(3);
	Ec7[i]->SetMarkerSize(.5);
	Ec7[i]->SetMarkerColor(2);
	Ec7[i]->SetLineColor(2);
	Ec7[i]->SetMarkerStyle(21);
	//Ec7[i]->SetAxisRange(-.5,.5,"X");
	EPC8->cd(i+1);
	Ec7[i]->Draw();
	
	F1->SetParameters(Ec7[i]->GetMaximum(),Ec7[i]->GetMean(),0.5*(Ec7[i]->GetRMS()));
		
        status = "nope";
	for(int d=2; ((status !="CONVERGED ") || (F1->GetParameter(2) <0));d++){
	  F1->SetParameters(Ec7[i]->GetMaximum(),Ec7[i]->GetMean(),0.5*(Ec7[i]->GetRMS()));
	  
	  Ec7[i]->Fit("F1","","",Ec7[i]->GetMean()-d*(Ec7[i]->GetRMS()),Ec7[i]->GetMean()+d*(Ec7[i]->GetRMS()));
	  status = gMinuit->fCstatu;
	  cout <<status<<""<<i<<endl;
	  }	
	
	chi6->Fill((F1->GetChisquare())/(F1->GetNDF()));
	y6[i]=100*F1->GetParameter(2);
	x6[i]=(double)i+.5;
	ey6[i]=100*F1->GetParError(2);
	ex6[i]=F1->GetParError(1);
	/*
	y6[i]=F1->GetParameter(2)/F1->GetParameter(1);
	x6[i]=F1->GetParameter(1);
	ey6[i]=y1[i]*sqrt(pow(F1->GetParError(2)/F1->GetParameter(2),2)+pow(F1->GetParError(1)/F1->GetParameter(1),2));
	ex6[i]=F1->GetParError(1);

*/
	cout <<"mean: "<<Ec7[i]->GetMean()<<endl;
	cout <<"RMS: "<<Ec7[i]->GetRMS()<<endl;
	
	Title = "<Etruth> = ";
	Title+= i+.5;
	Title+= "GeV";
	Ec7[i]->SetTitle(Title);
	Ec7[i]->SetXTitle("#frac{Etruth-Ereco}{Etruth}");
	//Ee7[i]->SetYTitle("#particles");
	Ec7[i]->SetLabelSize(.07,"Y");
	Ec7[i]->SetLabelSize(.05,"X");
	Ec7[i]->SetTitleSize(.04,"X");
	Ec7[i]->SetTitleSize(0.3,"T");
	Ec7[i]->SetStats(false);	

      }
    EPC8->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/CEMCe-deE.png");
    
    Cchi6->cd();
    chi6->Draw();
    Cchi6->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/CdeEchi.png");
    Cpara6->cd();
    para6 = new TGraphErrors(20,x6,y6,ex6,ey6);
    
    para6->Fit("F2","","",2,20);
    para6->SetMinimum(0);
    //para4->SetMaximum(.05);
    para6->SetMarkerColor(2);
    para6->SetMarkerSize(.5);
    para6->SetMarkerStyle(21);
    para6->SetTitle("CEMC resolution;E(GeV);#sigma[#frac{Etruth-Ereco}{Etruth}]%");
    para6->Draw("ap");
    Cpara6->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/CdeEpara.png");
    
    
    Ee7[0]=h1[1]->ProjectionY("Ede1",1,40);
    Ee7[1]=h1[1]->ProjectionY("Ede2",41,80);
    Ee7[2]=h1[1]->ProjectionY("Ede3",81,120);
    Ee7[3]=h1[1]->ProjectionY("Ede4",121,160);
    Ee7[4]=h1[1]->ProjectionY("Ede5",161,200);
    Ee7[5]=h1[1]->ProjectionY("Ede6",201,240);
    Ee7[6]=h1[1]->ProjectionY("Ede7",241,280);
    Ee7[7]=h1[1]->ProjectionY("Ede8",281,320);
    Ee7[8]=h1[1]->ProjectionY("Ede9",321,360);
    Ee7[9]=h1[1]->ProjectionY("Ede10",361,400);
    Ee7[10]=h1[1]->ProjectionY("Ede11",401,440);
    Ee7[11]=h1[1]->ProjectionY("Ede12",441,480);
    Ee7[12]=h1[1]->ProjectionY("Ede13",481,520);
    Ee7[13]=h1[1]->ProjectionY("Ede14",521,560);
    Ee7[14]=h1[1]->ProjectionY("Ede15",561,600);
    Ee7[15]=h1[1]->ProjectionY("Ede16",601,640);
    Ee7[16]=h1[1]->ProjectionY("Ede17",641,680);
    Ee7[17]=h1[1]->ProjectionY("Ede18",681,720);
    Ee7[18]=h1[1]->ProjectionY("Ede19",721,760);
    Ee7[19]=h1[1]->ProjectionY("Ede20",761,800);
    EPC9->Divide(4,5);
    
    for(int i =0;i<20;i++)
      {
	//Pe7[i]->Rebin(5);
	Ee7[i]->SetMarkerSize(.5);
	Ee7[i]->SetMarkerColor(2);
	Ee7[i]->SetLineColor(2);
	Ee7[i]->SetMarkerStyle(21);
	Ee7[i]->SetAxisRange(-.5,.5,"X");
	EPC9->cd(i+1);
	Ee7[i]->Draw();
	
	F1->SetParameters(Ee7[i]->GetMaximum(),Ee7[i]->GetMean(),0.5*(Ee7[i]->GetRMS()));
		
        status = "nope";
	for(int d=2; ((status !="CONVERGED ") || (F1->GetParameter(2) <0));d++){
	  F1->SetParameters(Ee7[i]->GetMaximum(),Ee7[i]->GetMean(),0.5*(Ee7[i]->GetRMS()));
	  if (i==0){
	    Ee7[i]->Fit("F1","","",-0.3,-.01);
	  }else{
	    Ee7[i]->Fit("F1","","",Ee7[i]->GetMean()-d*(Ee7[i]->GetRMS()),Ee7[i]->GetMean()+d*(Ee7[i]->GetRMS()));
	  }
	  status = gMinuit->fCstatu;
	  cout <<status<<""<<i<<endl;
	  }	
	
	chi7->Fill((F1->GetChisquare())/(F1->GetNDF()));
	y7[i]=100*F1->GetParameter(2);
	x7[i]= (double)i +.5;
	ey7[i]=100*F1->GetParError(2);
	ex7[i]=F1->GetParError(1);
	
	cout <<"mean: "<<Ee7[i]->GetMean()<<endl;
	cout <<"RMS: "<<Ee7[i]->GetRMS()<<endl;
	Title = "<Etruth> = ";
	Title+= i+.5;
	Title+= "GeV";
	Ee7[i]->SetTitle(Title);
	Ee7[i]->SetXTitle("#frac{Etruth-Ereco}{Etruth}");
	//Ee7[i]->SetYTitle("#particles");
	Ee7[i]->SetLabelSize(.07,"Y");
	Ee7[i]->SetLabelSize(.05,"X");

	Ee7[i]->SetTitleSize(.04,"X");
	Ee7[i]->SetTitleSize(0.3,"T");
	Ee7[i]->SetStats(false);
      }
    EPC9->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/EEMCe-deE.png");
    
    Cchi7->cd();
    chi7->Draw();
    Cchi7->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/EdeEchi.png");
    Cpara7->cd();

    para7 = new TGraphErrors(20,x7,y7,ex7,ey7);
    
    para7->Fit("F5","","",1,20);
    para7->SetMinimum(0);
    para7->SetMaximum(4);
    //para7->SetAxisRange(0,.1,"Y");
    para7->SetMarkerColor(2);
    para7->SetMarkerSize(.5);
    para7->SetMarkerStyle(21);
    para7->SetTitle("EEMC resolution;E(GeV);#sigma[#frac{Etruth-Ereco}{Etruth}]%");
    
    /*parastring = "a = "+std::to_string(F2->GetParameter(0))+" b= "+std::to_string(F2->GetParameter(1))+" c= "+std::to_string(F2->GetParameter(2));
    Epara = new TPaveText(.9,.8,.7,.6);
    Tpara = new TPaveText(.91,.8,7,.15);
    Epara->SetTextColor(1);
    Epara->SetTextFont(43);
    Epara->SetTextSize(40);
    Epara->AddText("#frac{a}{#sqrt{E}} + #frac{b}{E} + c");
    Tpara->SetTextColor(1);
    Tpara->SetTextFont(43);
    Tpara->SetTextSize(40);
    Tpara->AddText(parastring);*/
    para7->Draw("ap");
    /*Tpara->Draw("same");
      Epara->Draw("same");*/
    Cpara7->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/EdeEpara.png");

    
    break;
    
  case 9:

    h3p[0] = (TH2F*)f->Get("E pi+ E truth vs E det");
    h3p[1] = (TH2F*)f->Get("E pi+ P truth vs E det");
    h3p[2] = (TH2F*)f->Get("E pi+ Ep");
    h3p[3] = (TH2F*)f->Get("C pi+ E truth vs E det");
    h3p[4] = (TH2F*)f->Get("C pi+ P truth vs E det");
    h3p[5] = (TH2F*)f->Get("C pi+ Ep");
    
    p2[0]= h3p[2]->ProjectionY("Proj1",10,10);
    p2[1]= h3p[2]->ProjectionY("Proj2",1,1);
    p2[2]= h3p[5]->ProjectionY("Proj3",10,10);
    p2[3]= h3p[5]->ProjectionY("Proj4",1,1);
    p2[0]->SetTitle("EEMC E/p pip 10Gev");
    p2[1]->SetTitle("EEMC E/p pip 1Gev");
    p2[2]->SetTitle("CEMC E/p pip 10Gev");
    p2[3]->SetTitle("CEMC E/p pip 1Gev");
    C->Divide(2,2);
    for(int i =0;i<4;i++)
      {
	C->cd(i+1);
	p2[i]->SetMarkerSize(.5);
	p2[i]->SetMarkerColor(2);
	p2[i]->SetMarkerStyle(21);
	p2[i]->Draw();
      }
    C->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/10&1Eppip.png");
  
    
    
    p3[0]= h3p[1]->ProjectionY("Proj1",10,10);
    p3[1]= h3p[1]->ProjectionY("Proj2",1,1);
    p3[2]= h3p[4]->ProjectionY("Proj3",10,10);
    p3[3]= h3p[4]->ProjectionY("Proj4",1,1);
    p3[0]->SetTitle("EEMC pip 10Gev");
    p3[1]->SetTitle("EEMC pip 1Gev");
    p3[2]->SetTitle("CEMC pip 10Gev");
    p3[3]->SetTitle("CEMC pip 1Gev");
    
    
    C1->Divide(2,2);
    for(int i =0;i<4;i++)
      {
	C1->cd(i+1);
	p3[i]->SetMarkerSize(.5);
	p3[i]->SetMarkerColor(2);
	p3[i]->SetMarkerStyle(21);
	p3[i]->Draw();
      }
    C1->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/10&1GeVpip.png");
    break;
  
  case 10:
    h2[0] = (TH2F*)f->Get("E e- E truth vs E det");
    h2[1] = (TH2F*)f->Get("E e- P truth vs E det");
    h2[2] = (TH2F*)f->Get("E e- Ep");
    h2[3] = (TH2F*)f->Get("C e- E truth vs E det");
    h2[4] = (TH2F*)f->Get("C e- P truth vs E det");
    h2[5] = (TH2F*)f->Get("C e- Ep");

    h3p[0] = (TH2F*)f->Get("E pi+ E truth vs E det");
    h3p[1] = (TH2F*)f->Get("E pi+ P truth vs E det");
    h3p[2] = (TH2F*)f->Get("E pi+ Ep");
    h3p[3] = (TH2F*)f->Get("C pi+ E truth vs E det");
    h3p[4] = (TH2F*)f->Get("C pi+ P truth vs E det");
    h3p[5] = (TH2F*)f->Get("C pi+ Ep");
    
    p4[0]=h2[2]->ProjectionY("EP1",1,40);
    p4[1]=h3p[2]->ProjectionY("EP2",1,40);
    p4[2]=h2[2]->ProjectionY("EP3",41,80);
    p4[3]=h3p[2]->ProjectionY("EP4",41,80);
    p4[4]=h2[2]->ProjectionY("EP5",81,120);
    p4[5]=h3p[2]->ProjectionY("EP6",81,120);
    p4[6]=h2[2]->ProjectionY("EP7",121,160);
    p4[7]=h3p[2]->ProjectionY("EP8",121,160);
    p4[8]=h2[2]->ProjectionY("EP9",161,200);
    p4[9]=h3p[2]->ProjectionY("EP10",161,200);
    p4[10]=h2[2]->ProjectionY("EP11",201,240);
    p4[11]=h3p[2]->ProjectionY("EP12",201,240);
    p4[12]=h2[2]->ProjectionY("EP13",241,280);
    p4[13]=h3p[2]->ProjectionY("EP14",241,280);
    p4[14]=h2[2]->ProjectionY("EP15",281,320);
    p4[15]=h3p[2]->ProjectionY("EP16",281,320);
    p4[16]=h2[2]->ProjectionY("EP17",321,360);
    p4[17]=h3p[2]->ProjectionY("EP18",321,360);
    p4[18]=h2[2]->ProjectionY("EP19",361,400);
    p4[19]=h3p[2]->ProjectionY("EP20",361,400);
    
    EPC->Divide(2,5);

    EP[0]="e-";
    EP[1]="pi+";
    EPl->AddEntry(p4[0],EP[0],"P");
    EPl->AddEntry(p4[1],EP[1],"P");
    EPl->SetHeader("E/p","C");
    for(int i =0;i<20;i++)
      {
	p4[i]->Rebin(10);
	if ((i%2)!=0)
	  { 
	    p4[i]->SetMarkerSize(.5);
	    p4[i]->SetMarkerColor(1);
	    p4[i]->SetLineColor(1);
	    p4[i]->SetMarkerStyle(21);
	    EPC->cd((i+1)/2);
	    p4[i]->Draw("same");
	    EPl->Draw();/*
	    ratio =1;
	    for(bin=0;ratio>=.95;bin++){
	      ratio =p4[i]->Integral(bin,501)/p4[i]->Integral(1,501);	  
	    }
	    cout<<"95% "<<(bin-1)*p4[i]->GetBinWidth(1)<<" "<<ratio<<endl;
	    E95pipintegral->Fill((i+1),(bin-1)*p4[i]->GetBinWidth(1));*/
	  }
	else
	  {
	    p4[i]->SetMarkerSize(.5);
	    p4[i]->SetMarkerColor(2);
	    p4[i]->SetLineColor(2);
	    p4[i]->SetMarkerStyle(21);
	    EPC->cd(((double)i/2.)+1);
	    p4[i]->Draw();
	    //p4[i]->SetTitle("");
	    Title = "<Etruth> = ";
	    Title+= i+1;
	    Title+= "GeV";
	    p4[i]->SetTitle(Title);
	    p4[i]->SetXTitle("");
	    p4[i]->SetYTitle("#particles ");
	    p4[i]->SetStats(false);
	    p4[i]->SetLabelSize(.1,"Y");
	    p4[i]->SetLabelSize(.1,"X");
	    p4[i]->SetTitleSize(.1,"Y");
	    p4[i]->SetTitleOffset(.35,"Y");
	    ratio =1;
	    for(bin=0;ratio>=.95;bin++){
	      ratio =p4[i]->Integral(bin,501)/p4[i]->Integral(1,501);	  
	    }
	    cout<<"95% "<<(bin-1)*p4[i]->GetBinWidth(1)<<" "<<ratio<<endl;
	    E95eintegral->Fill((i+1),(bin-1)*p4[i]->GetBinWidth(1));
	    
	    ratio =1;
	    for(bin=0;ratio>=.9;bin++){
	      ratio =p4[i]->Integral(bin,501)/p4[i]->Integral(1,501);	  
	    }
	    cout<<"90% " <<(bin-1)*p4[i]->GetBinWidth(1)<<" "<<ratio<<endl;
	    E90eintegral->Fill((i+1),(bin-1)*p4[i]->GetBinWidth(1));
	  }

      }

    
    cout<<p4[1]->GetNbinsX()<<endl;
    cout<<p4[1]->Integral(1,501)<<endl;

    EPC->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/EEMCpie_Ep.png");
  
    
    p5[0]=h2[5]->ProjectionY("CEP1",1,40);
    p5[1]=h3p[5]->ProjectionY("CEP2",1,40);
    p5[2]=h2[5]->ProjectionY("CEP3",41,80);
    p5[3]=h3p[5]->ProjectionY("CEP4",41,80);
    p5[4]=h2[5]->ProjectionY("CEP5",81,120);
    p5[5]=h3p[5]->ProjectionY("CEP6",81,120);
    p5[6]=h2[5]->ProjectionY("CEP7",121,160);
    p5[7]=h3p[5]->ProjectionY("CEP8",121,160);
    p5[8]=h2[5]->ProjectionY("CEP9",161,200);
    p5[9]=h3p[5]->ProjectionY("CEP10",161,200);
    p5[10]=h2[5]->ProjectionY("CEP11",201,240);
    p5[11]=h3p[5]->ProjectionY("CEP12",201,240);
    p5[12]=h2[5]->ProjectionY("CEP13",241,280);
    p5[13]=h3p[5]->ProjectionY("CEP14",241,280);
    p5[14]=h2[5]->ProjectionY("CEP15",281,320);
    p5[15]=h3p[5]->ProjectionY("CEP16",281,320);
    p5[16]=h2[5]->ProjectionY("CEP17",321,360);
    p5[17]=h3p[5]->ProjectionY("CEP18",321,360);
    p5[18]=h2[5]->ProjectionY("CEP19",361,400);
    p5[19]=h3p[5]->ProjectionY("CEP20",361,400);
     
    EPC1->Divide(2,5);
    for(int i =0;i<20;i++)
      {
	p5[i]->Rebin(20);
	if ((i%2)!=0)
	  { 
	    p5[i]->SetMarkerSize(.5);
	    p5[i]->SetMarkerColor(1);
	    p5[i]->SetLineColor(1);
	    p5[i]->SetMarkerStyle(21);
	    EPC1->cd((i+1)/2);
	    p5[i]->Draw("same");
	    EPl->Draw();
	  }
	else
	  {
	    p5[i]->SetMarkerSize(.5);
	    p5[i]->SetMarkerColor(2);
	    p5[i]->SetLineColor(2);
	    p5[i]->SetMarkerStyle(21);
	    EPC1->cd(((double)i/2.)+1);
	    p5[i]->Draw();
	    p5[i]->SetXTitle("");
	    p5[i]->SetYTitle("#particles");
	    p5[i]->SetStats(false);
	    p5[i]->SetLabelSize(.1,"Y");
	    p5[i]->SetLabelSize(.1,"X");
	    p5[i]->SetTitleSize(.1,"Y");
	    p5[i]->SetTitleOffset(.35,"Y");
	    ratio =1;
	    for(bin=0;ratio>=.95;bin++){
	      ratio =p5[i]->Integral(bin,501)/p5[i]->Integral(1,501);	  
	    }
	    cout <<"95%  "<<(bin-1)*p5[i]->GetBinWidth(1)<<" "<<ratio<<endl;
	    C95eintegral->Fill((i+1),(bin-1)*p5[i]->GetBinWidth(1));
	    
	    ratio =1;
	    for(bin=0;ratio>=.9;bin++){
	      ratio =p5[i]->Integral(bin,501)/p5[i]->Integral(1,501);	  
	    }
	    cout <<"90% "<<(bin-1)*p5[i]->GetBinWidth(1)<<" "<<ratio<<endl;
	    C90eintegral->Fill((i+1),(bin-1)*p5[i]->GetBinWidth(1));
	  }
      }
    
    EPC1->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/CEMCpie_Ep.png");

    C->Divide(1,2);
    C->cd(1);
    E95eintegral->SetStats(false);
    E95eintegral->SetMarkerSize(.5);
    E95eintegral->SetMarkerColor(2);
    E95eintegral->SetLineColor(2);
    E95eintegral->SetMarkerStyle(21);
    E95eintegral->Fit("pol2","","",0,20);
    E95eintegral->SetTitle("EEMC E/p vs Energy");
    E95eintegral->SetYTitle("E/p");
    E95eintegral->SetXTitle("Momentum(GeV)");
    E95eintegral->Draw();
    C->cd(2);
    C95eintegral->SetStats(false);
    C95eintegral->SetMarkerSize(.5);
    C95eintegral->SetMarkerColor(2);
    C95eintegral->SetLineColor(2);
    C95eintegral->SetMarkerStyle(21);
    C95eintegral->Fit("pol2","","",0,20);
    C95eintegral->SetTitle("CEMC E/p vs Energy");
    C95eintegral->SetYTitle("E/p");
    C95eintegral->SetXTitle("Momentum(GeV)");
    C95eintegral->Draw();
    C->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/95e.png");
    
    C1->Divide(1,2);
    C1->cd(1);
    E90eintegral->SetMarkerSize(.5);
    E90eintegral->SetMarkerColor(2);
    E90eintegral->SetLineColor(2);
    E90eintegral->SetMarkerStyle(21);
    E90eintegral->Fit("pol2","","",0,20);
    E90eintegral->Draw();
    C1->cd(2);
    C90eintegral->SetMarkerSize(.5);
    C90eintegral->SetMarkerColor(2);
    C90eintegral->SetLineColor(2);
    C90eintegral->SetMarkerStyle(21);
    C90eintegral->Fit("pol2","","",0,20);
    C90eintegral->Draw();
    C1->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/90e.png");
    
    C2->cd();
    //E95pipintegral->SetStats(false);
    E95pipintegral->SetMarkerSize(.5);
    E95pipintegral->SetMarkerColor(2);
    E95pipintegral->SetLineColor(2);
    E95pipintegral->SetMarkerStyle(21);
    E95pipintegral->Fit("pol2","","",0,20);
    E95pipintegral->SetTitle("EEMC E/p vs Energy");
    E95pipintegral->SetYTitle("E/p");
    E95pipintegral->SetXTitle("Momentum(GeV)");
    E95pipintegral->Draw();
    C2->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/95pip.png");
    
    break;
    
  case 11:
    
    h[0] = (TH2F*)f->Get("C counts");
    h[1] = (TH2F*)f->Get("C energy_h");
    h[2] = (TH2F*)f->Get("C e- phi vs eta cluster");
    
    h[0]->SetTitle("CEMC Counts");
    h[1]->SetTitle("energy");
    h[2]->SetTitle("eta vs phi");
    
    //h[0]->SetAxisRange(0,10,"X");
    C->Divide(1,3);
    //C->cd();
    for(int i=0;i<3;i++){
      C->cd(i+1);
      if (i==1){ gPad->SetLogy();}
      h[i]->SetMarkerSize(.5);
      h[i]->SetMarkerStyle(21);
      h[i]->Draw();
    }
    C->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/Cluster.png");
    
    h1[0]=(TH2F*)f->Get("E delta R");
    h1[1]=(TH2F*)f->Get("E towercluster");
    h1[2]=(TH2F*)f->Get("C delta R");
    h1[3]=(TH2F*)f->Get("C towercluster");
    
    h1[0]->SetTitle("EEMC min R");
    h1[1]->SetTitle("E tower vs cluster");
    h1[2]->SetTitle("C delta R");
    h1[3]->SetTitle("C tower vs cluster");
    
    h1[0]->SetXTitle("Min R");
    h1[0]->SetStats(false);
    C1->Divide(2,2);
    for(int i=0;i<4;i++){
      C1->cd(i+1);
      if (i%2==0){ h1[i]->SetAxisRange(0,1,"X");}
      h1[i]->SetMarkerSize(.5);
      h1[i]->SetMarkerStyle(21);
      h1[i]->Draw();
    }
    C1->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/ClusterRandE.png");
    //cout <<h1[0]->GetEntries()<<endl;

    break;

  case 12:
    h4[0]=(TH1F*)f->Get("E ep pipcut counts");
    h4[0]->Rebin(80);
    h4[1]=(TH1F*)f->Get("E ep pip counts");
    h4[1]->Rebin(80);
    h4[2]=(TH1F*)h4[0]->Clone();

    h4[2]->Divide(h4[1]);
    h4[2]->SetTitle("Pion supression");
    h4[2]->SetXTitle("Energy(GeV)");
    //h4[2]->SetYTitle("ratio");
    h4[2]->SetStats(false);

    //h4[0]->SetAxisRange(0,20,"X");
    //h4[1]->SetAxisRange(0,20,"X");
    //h4[2]->SetAxisRange(0,20,"X");
    C->SetLogx();
    C->SetLogy();
    C->cd();
    //C->Divide(1,3);
    
    for(int i=2;i<3;i++){
      //C->cd(i+1);
      //C->SetLogx(i+1);
      //C->SetLogy(i+1);
      h4[i]->SetMarkerSize(.5);
      h4[i]->SetMarkerStyle(21);
      h4[i]->Draw("L");
      h4[i]->Draw("P Same");
    }
    C->Print("/home/keaghan/analysis/EM_CALO/macros/histograms/Eppipcut.png");

    break;



  defualt:
  cout <<"done broke"<<endl;
    
  }

  cout<<entries1<<" "<<entries2<<endl;

  return;
}

