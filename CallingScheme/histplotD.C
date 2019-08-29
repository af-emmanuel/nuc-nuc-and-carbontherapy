

#include <stdio.h> 
#include <stdlib.h> 
#include <iostream> 
#include <fstream> 
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TProfile.h"
#include "TString.h"
#include <iomanip> 
#include "TCanvas.h"
#include "TLegend.h"

using namespace std;

void histplotD()
{ 

         TString particleType [15]{"null","H","He", "Li", "Be", "B", "C", 
                                  "N", "O", "F","Ne", "Na", "Mg", "Al","Si"};
         int particleCharge [15]{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
         int AtomicMass [15]{0,1,4,6,7,10,12,14,16,18,20,22,24,26,28};
         const int no_charges = 11 ; //number of charges due to fragmentation
         string nuc[5]={"BIC-FBU","BIC-GEM","QMD-FBU","QMD-GEM","emstandard_opt4"};
         string nuc1[5]={"BF","BG","QF","QG","EM"};
         string histitle[5]={"(a)","(b)","(c)","(d)","(e)"};
         int mrk[5]= {29,39,20,49,33};
         int mrkC[5]= {3,2,7,4,6};
         
         
         TLatex * l[5]{}; 
         TH1F *g[5]{};
         TProfile *g1[5]{};
         TFile *f[5]{};
         TLegend* legend =new TLegend();
         
         TCanvas *ch = new TCanvas ("c","c ", 200,10, 700,900);
          
         for (int i=0; i<5 ; i++)
            {    

                  f[i]=new TFile(("CallEnergy"+nuc1[i]+".root").c_str()); //gets root file 
                  g[i] =(TH1F*)f[i]->Get("dose distribution");
                  g1[i]=new TProfile ("dose",nuc[i].c_str(),1000, 0.0,2.0);
                  
                  
                  for (int k=0; k<1000; k++)
                  {
                  
                  
                  

                  //g[i]->Rebin(0.2);
                  //g[i]->Scale(0.2);

                //  g[i]->SetName((particleType [6]+ " "+nuc[i])); 
                 // g[i]->SetTitle(nuc[i].c_str());
                 // g[i]->SetMarkerStyle(mrk[i]);       
                 // g[i]->SetMarkerColor(mrkC[i]);
                  g1[i]->Fill(0.2*k,g[i]->GetBinContent(k)/1000000);
                  
                  }
                  
                  //g1[i]->GetXaxis()->SetRangeUser(0, 405);
                  g1[i]->GetXaxis()->SetTitle("Depth(per 2mm)");
                  g1[i] -> GetXaxis() -> CenterTitle();        
                  g1[i]->GetYaxis()->SetTitle("Dose (Gy)");
                  g1[i] -> GetYaxis() -> CenterTitle();

                  
                  
                  g1[i]->Draw("same L");


         
            }
                              gStyle->SetOptTitle(0);
                  gStyle->SetOptStat(0);
                  gPad->BuildLegend();
    

 

  
}
