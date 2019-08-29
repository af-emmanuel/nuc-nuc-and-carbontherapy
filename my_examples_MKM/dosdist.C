#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "TFile.h"
#include "TH1F.h"
#include "TProfile.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include <math.h> 
#include "TCanvas.h"
#include "TPad.h"
#include "TStyle.h"
#include "TLegendEntry.h"
using namespace std;

class CSV
      {
      
public:

       const int no_bin =405;
       double X_axis[405]{};//depth on the x-axis
       double Y_axis[405]{};//alpha on the y-axis
       double beta[405]{}; //beta
       double doz[405]{};
       double SF[405]{};
       double max;
       string files;
       string file;
       
//private:
        void readCSV (string fileParticle, string fileDose, int a)
               {
        
                //const int no_bin =405; //number of bins in consideration

	        ifstream infile(files=fileParticle);
	        
	        string line, fields;
                vector< vector<string> > array;  // the 2D array
                vector<string> vc;                // array of values for one line only
                
                
	                while (getline(infile, line)) //get everyline in file
	                 {	
	                     vc.clear();  //clear memeory of possible junks
                             stringstream ss(line); //feeds line as stream of strings
	                
	                        while(getline(ss,fields, ','))  //takes every line and  
	                                                        //breaks them into 
	                                                       //comma-delimitted fields
                                        {

                                             vc.push_back(fields);  // add each field to 
                                                                    //the 1D array
                                        }
                                        
                             array.push_back(vc);  // add the 1D array to the 2D array
                          
                         }
                         
                         
                ifstream infile1(file=fileDose);
	        
	        string line1, fields1;
                vector< vector<string> > array1;  // the 2D array
                vector<string> vec;                // array of values for one line only   
                                         
	                while (getline(infile1, line1)) //get everyline in file
	                 {	
	                     vec.clear();  //clear memeory of possible junks
                             stringstream ss1(line1); //feeds line as stream of strings
	                
	                        while(getline(ss1,fields1,','))  //takes every line and  
	                                                        //breaks them into 
	                                                       //comma-delimitted fields
                                        {
                                        

                                             vec.push_back(fields1);  // add each field to 
                                                                    //the 1D array
                                        }
                                        
                             array1.push_back(vec);  // add the 1D array to the 2D array
                          
                         }
                         
                             //empty array of possible previous imputs
                         for (size_t i=1; i<no_bin; i++)
                          {
                            X_axis[i-1]=0.;
                            Y_axis[i-1]=0.;
                            doz[i-1]=0.;
                            SF[i-1]=0.;
                          }
                          
                        if(array.size()>1)
                        
                                {
                         //to print out generated 2d arrays due to added vectors
                                for (size_t i=1; i<array.size(); ++i)//array.size()
                                  {
                                     
                                    int bin = stoi (array[i][8].erase (array[i][8].find('.')).erase(0,15));
                                    double depth = 0.2 * bin;
                                    double alpha =stod(array[i][18]);
                                        
                                    //fill array with current input
                                   X_axis[i-1]=depth;
                                   Y_axis[i-1]=alpha;
                                   beta [i-1]=stod(array[i][19]);
                                   
                                   doz[i-1]=stod(array1[bin][0]);
                                   
                                   
                                   //cout << X_axis[i-1] <<"  "<< Y_axis[i-1]<<"  "<<doz[i-1]<<endl;
                                         
                                  }
                                  
                                 }
                          else
                          {
                          cerr<<"array too small for  "<<files<<endl;
                          }
                          
                          // NORMALISING DOSE BY MAXIMUM VALUE

                                for (int i=0; i<array.size(); i++)
                                        {
                                        doz[i]=doz[i]/1000000  ;
                                        SF[i]= exp(-Y_axis[i]*a*doz [i]-beta [i]*pow(a*doz[i],2));
                                        //cout << SF[i]<<endl;
                                        }
                                
                                
                        //cout<< "maximum dose value is: "<<*max_element(doz, doz + 405)<<endl;        
                }  
        
                
        };
                          

int dosdist ()
{	

        CSV CSVobject;
        const int no_points =50;

        TCanvas * c = new TCanvas("c","c",200,10,700,900);
        
        int BraggPeakDose [6]={1,2,5,10,15,20};
        TString fig[6]={"(a)","(b)","(c)","(d)","(e)","(f)"};
//all graph classes associated to all 6 bragg peak dose
        TMultiGraph  *mg [6]{};
        TGraph *BF[6]{};
        TGraph *BG[6]{};
        TGraph *QF[6]{};
        TGraph *QG[6]{};
        TGraph *EM[6]{};
        TPad* c_b[6]{};
        TLegend *leg[6]{};
        TLegendEntry *le[6]{};
           
        
        
        
     int i=0;
        
        mg [i]= new TMultiGraph();
        CSVobject. readCSV("ParticleFieldBF_HSG_MKM_LQparameters_MKM.csv","dose_BF.csv", BraggPeakDose[i]);        
        BF [i]  = new TGraph(no_points,CSVobject. X_axis,CSVobject.doz);
        BF[i]->SetTitle("BIC-FBU");
        BF[i]->SetMarkerStyle(27);
        BF[i]->SetMarkerColor(3);

        CSVobject. readCSV("ParticleFieldBG_HSG_MKM_LQparameters_MKM.csv","dose_BG.csv",BraggPeakDose[i]);
        BG[i]  = new TGraph(no_points,CSVobject. X_axis,CSVobject.doz);
        BG[i]->SetTitle("BIC-GEM");
        BG[i]->SetMarkerStyle(27);
        BG[i]->SetMarkerColor(2);

        CSVobject. readCSV("ParticleFieldQF_HSG_MKM_LQparameters_MKM.csv","dose_QF.csv",BraggPeakDose[i]);  
        QF[i]  = new TGraph(no_points,CSVobject. X_axis,CSVobject.doz);
        QF[i]->SetTitle("QMD-FBU");
        QF[i]->SetMarkerStyle(27);
        QF[i]->SetMarkerColor(7);

        CSVobject. readCSV("ParticleFieldQG_HSG_MKM_LQparameters_MKM.csv","dose_QG.csv",BraggPeakDose[i]); 
        QG [i] = new TGraph(no_points,CSVobject. X_axis,CSVobject.doz);
        QG[i]->SetTitle("QMD-GEM");
        QG[i]->SetMarkerStyle(27);
        QG[i]->SetMarkerColor(4);

        CSVobject. readCSV("ParticleFieldEM_HSG_MKM_LQparameters_MKM.csv","dose_EM.csv",BraggPeakDose[i]);  
        EM[i]  = new TGraph(no_points,CSVobject. X_axis,CSVobject.doz);
        EM[i]->SetTitle("emstandard_opt4");
        EM[i]->SetMarkerStyle(27);       
        EM[i]->SetMarkerColor(6);

        mg[i]->Add(BF[i]);
        mg[i]->Add(BG[i]);
        mg[i]->Add(QF[i]);
        mg[i]->Add(QG[i]);
        mg[i]->Add(EM[i]);


        mg[i]->GetYaxis()->SetTitle("Dose (Gy)/projectile/mm^{2}");
        mg[i] -> GetYaxis() -> CenterTitle();


       mg[i]->GetXaxis()->SetTitle("Depth(cm)");
        mg[i] -> GetXaxis() -> CenterTitle();
  

        mg[i]->Draw("APL");

        //c_b[i]->BuildLegend(); 
//////////////////////////////////////////////////////////////////legends   

        leg[i]=new TLegend (0.102,0.7,0.45,0.951);
        
        //leg[i]->SetTextSize(0.05); 
        
        leg[i]->SetHeader("Models","C");
        leg[i]->AddEntry(BF[i], "BIC-FBU");
        leg[i]->AddEntry(BG[i], "BIC-GEM");
        leg[i]->AddEntry(QF[i], "QMD-FBU");
        leg[i]->AddEntry(QG[i], "QMD-GEM");
        leg[i]->AddEntry(EM[i],"emstandard_opt4");
        

        leg[i]->Draw();
        //c_b[i]->BuildLegend();  

         



          


       return 0;
}


