

#include <stdio.h> 
#include <stdlib.h> 
#include <iostream> 
#include <fstream> 
#include "TFile.h"
#include "TH1F.h"
#include "TProfile.h"
#include "TString.h"
#include <iomanip> 
#include <cmath>
using namespace std;

//************************************************************************************//
/*this programm extracts information for all root files outputed form the geant4 simualtions and writes them into new files representing the enames of the different root files which will be imputed into the survival programme*/
//*************************************************************************************//


void callEoutfilesLEM()
{ 
 TString particleType [15]{"null","H","He", "Li", "Be", "B", "C", 
                          "N", "O", "F","Ne", "Na", "Mg", "Al","Si"}; //List of expected particles
 int particleCharge [15]{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14}; //values of their charges
 int AtomicMass [15]{0,1,4,6,7,10,12,14,16,18,20,22,24,26,28};// their atomic mass
 const int no_files = 400; // number of files or bins we are considering for each histograms
 const int no_charges = 15 ; //possible number of charges due to fragmentation and formation of new ions
 string nuc1[5]={"BF","BG","QF","QG","EM"}; //abbreviated names of the interactions and models considered
 
  TFile *f[5]{}; //to obtain the different 5 root files
  TH1F*d[5]{};  //to obtain the different histograms of the 5 root files  for dose extraction
  TProfile*g[5]{}; // to obtain the different profile histograms of the five root files
  TH1F*h[5]{};   // to obtain the different histograms of the five root files for the number of particles gernerated in the interactions
  ofstream dose[5]{}; //outputes dose files for the different root files considered.
  
 int weight[no_files]{}; //corresponding to the number of files or bins for each element
 double energy[no_files]{}; //corresponding to the number of files or bins for each element
 double low_energy[15]{0,10.00E-03,2.500e-03,1.428e-03,1.111e-03,9.090e-04,8.333e-04,
                                        7.142e-04,6.2500e-04,5.263600e-04,4.955475e-04};
 double high_energy[15]{0,10.00E+03,2.500e+03,1.428e+03,1.111e+03,9.090e+02,8.333e+02,
                                                7.142e+02,6.2500e+02,6.842680e+02,6.442118e+02};
 ofstream fout[no_files]{};
  
 
 for (int j=0; j<5;j++)
 {
 
 f[j]=new TFile(("CallEnergy" +nuc1[j]+ ".root").c_str()); //gets root files 


 
 
 dose[j].open("/home/atukpor/Documents/survival/my_examples_LEM/dose_" + nuc1[j]+".csv");
         for (int i=0; i<1000; i++)
                {
                
                d[j]=(TH1F*)f[j]->Get("dose distribution");       
                dose[j]<<d[j]->GetBinContent(i)*(1000000/8)*1.60218*pow(10,-13)<<" ,"<<endl;
                }

                //open file and add headers to it
         for(int i=0; i<no_files;i++)
                {

        fout[i].open("/home/atukpor/Documents/survival/my_examples_LEM/ParticleField" + nuc1[j] + to_string(i) + ".mixedField");
          fout[i]<<setw(10)<<left<<"type"<<
 
          setw(10)<<left<<"charge"<<
          
          setw(10)<<left<<"A"<<
          
          setw(15)<<left<<"energy"<<
          
          setw(10)<<left<<"LET"<<
          
          setw(15)<<left<<"weight"<<endl;
                          
        }
 
 
 
 // files read for each bin                                                       
 for(int i=0; i<no_files;i++)
        { //when in a file i we collect all information in bin i of all histogramms or profiles
        
  for (int k =1; k<no_charges ; k++) //information of charges to be read to  files:
                                      //each charge has a histogram or profile
                {
                        //cout<<"filling files"<<endl;  
                        g[j] =(TProfile*)f[j]->Get("p" + particleType [k]);//get profiles
                                                                               //for each file
                                                                               //with name k
                        h[j]=(TH1F*)f[j]->Get(particleType [k]);//get histogramms
                                                                //for each file
                                                                //with name k
 
                        weight[i]= h[j]->GetBinContent(i); //for each charge, get the bin content
                                                        //histogram
                        energy[i]=g[j]->GetBinContent(i); //for each charge, get the bin content
                                                       //profile
                  //one may not need to use the arrays here since it may slow down computation...
                  //it would have also worked if I siply called the histogram or profile pointer 
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
          //empty weigth and energy array for reuse  ...not so important but for safety reasons
     
          weight[i]= 0. ;
          energy[i]= 0. ;   
          //close files
         fout [i].close();
        }
     dose[j].close();
     
  }
}
