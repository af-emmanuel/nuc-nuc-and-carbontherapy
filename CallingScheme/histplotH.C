

#include <stdio.h> 
#include <stdlib.h> 
#include <iostream> 
#include <fstream> 
#include "TFile.h"
#include "TH1F.h"
#include "TProfile.h"
#include "TString.h"
#include <iomanip> 
#include "TCanvas.h"
#include "TLegend.h"

using namespace std;

void histplotH()
{ 
 TString particleType [15]{"null","H","He", "Li", "Be", "B", "C", 
                          "N", "O", "F","Ne", "Na", "Mg", "Al","Si"};
 int particleCharge [15]{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
 int AtomicMass [15]{0,1,4,6,7,10,12,14,16,18,20,22,24,26,28};
 const int no_charges = 11 ; //number of charges due to fragmentation
 string nuc[5]={"BIC-FBU","BIC-GEM","QMD-FBU","QMD-GEM","emstandard_opt4"};
 string nuc1[5]={"BF","BG","QF","QG","EM"};
 string histitle[5]={"(a)","(b)","(c)","(d)","(e)"};
 
 TLatex * l[5]{}; 
 
  TCanvas *ch = new TCanvas ("c","c ", 200,10, 700,900);
  ch->Divide(2,3);
  TLegend* legend[6]{};
  TH1F *g[5]{};
  TFile *f[5]{};
  
 for (int i=0;i<5;i++)
    {    

        f[i]=new TFile(("CallEnergy"+nuc1[i]+".root").c_str()); //gets root file5.263600e-04 
        legend [i]=new TLegend();



        //ch->Divide(2,3);
        ch->cd(1+i);
        ch->SetLogy();
        // files read for each bin                                                       
        g[i]=(TH1F *)f[i]->Get(particleType [6]);
        g[i]->GetXaxis()->SetRangeUser(0, 50);
        //g[i]->Rebin(0.2);
        //g[i]->Scale(0.2);
        gStyle->SetOptStat(1);
        //gStyle->SetOptTitle(0);
        g[i]->SetName((particleType [6]+"-ions with"+ " "+nuc[i])); 
        g[i]->Write();
        gPad->SetLogy();


        g[i]->GetXaxis()->SetTitle("Depth(mm)");
        g[i] -> GetXaxis() -> CenterTitle();        
        g[i]->GetYaxis()->SetTitle("number of counts");
        g[i] -> GetYaxis() -> CenterTitle();
        g[i]->Draw("PLC PMC HIST");

  for (int k =1; k<no_charges ; k++) //information of charges to be read 
                {
//"dose distribution"                 
                        g[i] =(TH1F*)f[i]->Get(particleType [k]);//get histogramms
                        
                        g[i]->GetXaxis()->SetRangeUser(0, 405);                                       //for 
                        g[i]->Draw("same PLC PMC HIST");
                        
                        legend[i]->AddEntry(particleType [k],particleType [k]);
                        gPad->SetLogy();
                        gStyle->SetOptTitle(0);
                        //gStyle->SetOptStat(0);
               }
       // }
       //legend[i]->SetHeader(("carbon and ion fragments--"+nuc[i]).c_str());
       //legend[i]->Draw();
       l[i] = new TLatex(); 
       l[i]->DrawLatex(0.1, 0.7, "Q");
       
    }
        
  ch->cd(6);
  //legend [3]=new TLegend(0.1,0.1,0.9,0.9);
  legend[3]->SetHeader("C-ions and mixed field--Legend");
  legend[3]->Draw();
  ch->SetLogy();
  
}
