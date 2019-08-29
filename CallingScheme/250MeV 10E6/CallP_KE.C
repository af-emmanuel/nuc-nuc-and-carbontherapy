

#include "TFile.h"
#include "TH1F.h"
#include "TProfile.h"
#include "TString.h"

#include <stdio.h> 
#include <stdlib.h> 
#include <fstream> 
#include <iostream>






using namespace std;
void CallP_KE ()
        {
        
         TString particleType [15]{"null","H","He", "Li", "Be", "B", "C", 
                          "N", "O", "F","Ne", "Na", "Mg", "Al","Si"}; //List of expected particles        
         const int no_charges = 10;
         string nuc1[5]={"BF","BG","QF","QG","EM"}; //abbreviated names of the interactions and models considered
         const int no_bins = 200;
         TFile *f[5]{}; //to obtain the different 5 root files
         //i need five files
         ofstream foutp[5]{};
         ofstream foutke[5]{};
         TH1F*h[no_charges]{};
         TProfile *p[no_charges]{};
         
         
         for(int k=0;k<5;k++)
         {
//*************************************************************************************************8        
                f[k]= new TFile(("CallEnergy" +nuc1[k]+ ".root").c_str()); //gets root files 
                foutp[k].open(nuc1[k]+"paticles.csv");
                foutp[k]<<particleType[1]<<","<<particleType[2]<<","<<
                particleType[3]<<","<<particleType[4]<<","<<particleType[5]<<","<<
                particleType[6]<<","<<particleType[7]<<","
                <<particleType[8]<<","<<particleType[9]<<","<<particleType[10]<<endl;
//**************************************************************************************************                
                foutke[k].open(nuc1[k]+"KE.csv");
                foutke[k]<<particleType[1]<<","<<particleType[2]<<","<<
                particleType[3]<<","<<particleType[4]<<","<<particleType[5]<<","<<
                particleType[6]<<","<<particleType[7]<<","
                <<particleType[8]<<","<<particleType[9]<<","<<particleType[10]<<endl;
//*******************************************************************************************************                
                for(int j=0;j<10;j++)
                     {
                        h[j] = (TH1F*)f[k]->Get(particleType [j+1]);
                        p[j] = (TProfile*)f[k]->Get("p" + particleType [j+1]);

                     }
                
                 
                for (int i=0;i<no_bins;i++)
                     {
//**********************************************************************************                    
                         foutp[k]<< h[0]->GetBinContent(i)<<","<<
                         h[1]->GetBinContent(i)<<","<<h[2]->GetBinContent(i)<<","<<
                         h[3]->GetBinContent(i)<<","<<h[4]->GetBinContent(i)<<","<<
                         h[5]->GetBinContent(i)<<","<<h[6]->GetBinContent(i)<<","<<
                         h[7]->GetBinContent(i)<<","<<h[8]->GetBinContent(i)<<","<<
                         h[9]->GetBinContent(i)<<endl;
//*****************************************************************************************                    
                         foutke[k]<< p[0]->GetBinContent(i)<<","<<
                         p[1]->GetBinContent(i)<<","<<p[2]->GetBinContent(i)<<","<<
                         p[3]->GetBinContent(i)<<","<<p[4]->GetBinContent(i)<<","<<
                         p[5]->GetBinContent(i)<<","<<p[6]->GetBinContent(i)<<","<<
                         p[7]->GetBinContent(i)<<","<<p[8]->GetBinContent(i)<<","<<
                         p[9]->GetBinContent(i)<<endl;                     
//******************************************************************************************                    
                     }         
         
                foutp[k].close();
                foutke[k].close();
         }        
                 

        }
