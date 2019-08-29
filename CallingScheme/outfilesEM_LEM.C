

#include <stdio.h> 
#include <stdlib.h> 
#include <iostream> 
#include <fstream> 
#include "TFile.h"
#include "TH1F.h"
#include "TProfile.h"
#include "TString.h"
#include <iomanip> 

using namespace std;

void outfilesEM_LEM()
{ 
 TString particleType [15]{"null","H","He", "Li", "Be", "B", "C", 
                          "N", "O", "F","Ne", "Na", "Mg", "Al","Si"};
 int particleCharge [15]{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
 int AtomicMass [15]{0,1,4,6,7,10,12,14,16,18,20,22,24,26,28};
 const int no_files = 400; // number of files or bins we are considering
 const int no_charges = 15 ; //number of charges due to fragmentation
 
 TFile *f=new TFile("CallEnergyEM.root"); //gets root file5.263600e-04
 ofstream fout[no_files]{};
 int weight[no_files]{}; //corresponding to the number of files or bins for each element
 double energy[no_files]{}; //corresponding to the number of files or bins for each element
 double low_energy[15]{0,10.00E-03,2.500e-03,1.428e-03,1.111e-03,9.090e-04,8.333e-04,
                                        7.142e-04,6.2500e-04,5.263600e-04,4.955475e-04};
 double high_energy[15]{0,10.00E+03,2.500e+03,1.428e+03,1.111e+03,9.090e+02,8.333e+02,
                                                7.142e+02,6.2500e+02,6.842680e+02,6.442118e+02};
 ofstream dose;
 dose.open("/home/atukpor/Documents/survival/my_examples_LEM/dose_EM.csv");
 
 for (int i=0; i<1000; i++)
        {
        
        TH1F*d =(TH1F*)f->Get("dose distribution");       
        dose<<d->GetBinContent(i)<<" ,"<<endl;
        }
 
        //open file and add headers to it
 for(int i=0; i<no_files;i++)
        {

        fout[i].open("/home/atukpor/Documents/survival/my_examples_LEM/ParticleFieldEM"  + to_string(i) + ".mixedField");
          fout[i]<<setw(10)<<left<<"type"<<
 
          setw(10)<<left<<"charge"<<
          
          setw(10)<<left<<"A"<<
          
          setw(15)<<left<<"energy"<<
          
          setw(10)<<left<<"LET"<<
          
          setw(15)<<left<<"weight"<<endl;
                          
        }
 
 
 
 // files read for each bin                                                       
 for(int i=0; i<no_files;i++)
        { 
        
  for (int k =1; k<no_charges ; k++) //information of 9 charges to be read to 10 files
                {
                        //cout<<"filling files"<<endl;  
                        TProfile*g =(TProfile*)f->Get("p" + particleType [k]);//get profiles
                                                                               //for each file
                                                                               //with name k
                        TH1F*h =(TH1F*)f->Get(particleType [k]);//get histogramms
                                                                //for each file
                                                                //with name k
 
                        weight[i]= h->GetBinContent(i); //for each charge, get the bin content
                                                        //histogram
                        energy[i]=g->GetBinContent(i); //for each charge, get the bin content
                                                       //profile
        
                        if (weight[i]> 0. & energy[i]>=low_energy[k] & energy[i]<=high_energy[k])
                        { 
                          //fill file
                          fout[i]<<setw(10)<<left<<particleType[k]<<
                 
                          setw(10)<<left<<particleCharge[k]<<
                          
                          setw(10)<< left<<AtomicMass[k]<<
                          
                          setw(15)<<left<<energy[i]*AtomicMass[k]<<
                          
                          setw(10)<<left<<-1<<
                          
                          setw(15)<<left<<weight[i]<<endl;
                           
                        }
                }
        }
        
        
   for(int i=0; i<no_files;i++)
        {       
          //close files
         fout [i].close();
        }
     dose.close();    
}
