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


using namespace std;
////PLOTS ALPHA FOR LEM
class CSV
      {
      
public:
       double X_axis[405]{};
       double Y_axis[405]{};
       string files;
       const int no_bin =405;
//private:
        void readCSV (string file)
               {
        
                //const int no_bin =405; //number of bins in consideration

	        ifstream infile(files=file);
	        
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
                         
                             //empty array of possible previous imputs
                         for (size_t i=1; i<no_bin; ++i)
                          {
                            X_axis[i-1]=0.;
                            Y_axis[i-1]=0.;
                          }

                         //to print out generated 2d arrays due to added vectors
                        for (size_t i=1; i<array.size(); ++i) //i=0 is the heading
                          {
                             
                            int bin = stoi (array[i][8].erase (array[i][8].find('.')).erase(0,15));
                            double depth = 0.2 * bin;
                            double alpha =stod(array[i][18]);

                            X_axis[i-1]=0.;
                            Y_axis[i-1]=0.;
                                
                            //fill array with current input
                            X_axis[i-1]=depth;
                            Y_axis[i-1]=alpha;
                            //cout << X_axis[i-1] <<"  "<< Y_axis[i-1]<<endl;
                                  
                          }
                }          
                
        };
                          

int rdalpha ()
{	
        
       CSV CSVobject;
       const int no_points = 50;
       auto c = new TCanvas("c","c",600, 400);
       CSVobject. readCSV("ParticleFieldBF_HSG_LEMIII_LQparameters_LEMIII.csv");  
       TGraph *BF  = new TGraph(no_points,CSVobject. X_axis,CSVobject.Y_axis);
       BF->SetTitle("BIC-FBU");
       BF->SetMarkerStyle(29);
       BF->SetMarkerColor(3);
       
       
       CSVobject. readCSV("ParticleFieldBG_HSG_LEMIII_LQparameters_LEMIII.csv");  
       TGraph *BG  = new TGraph(no_points,CSVobject. X_axis,CSVobject.Y_axis);
       BG->SetTitle("BIC-GEM");
       BG->SetMarkerStyle(39);
       BG->SetMarkerColor(2);
       
       
       CSVobject. readCSV("ParticleFieldQF_HSG_LEMIII_LQparameters_LEMIII.csv");  
       TGraph *QF  = new TGraph(no_points,CSVobject. X_axis,CSVobject.Y_axis);
       QF->SetTitle("QMD-FBU");
       QF->SetMarkerStyle(20);
       QF->SetMarkerColor(7);
       
       CSVobject. readCSV("ParticleFieldQG_HSG_LEMIII_LQparameters_LEMIII.csv");  
       TGraph *QG  = new TGraph(no_points,CSVobject. X_axis,CSVobject.Y_axis);
       QG->SetTitle("QMD-GEM");
       QG->SetMarkerStyle(49);
       QG->SetMarkerColor(4);
       
              
       CSVobject. readCSV("ParticleFieldEM_HSG_LEMIII_LQparameters_LEMIII.csv");  
       TGraph *EM  = new TGraph(no_points,CSVobject. X_axis,CSVobject.Y_axis);
       
       EM->SetTitle("emstandard_opt4");
       EM->SetMarkerStyle(33);       
       EM->SetMarkerColor(6);
          
       TMultiGraph  *mg  = new TMultiGraph();
       
       mg->Add(BF);
       mg->Add(BG);
        
       mg->Add(QF);
       mg->Add(QG);
  
       mg->Add(EM);
       
      // mg->SetTitle("Alpha depth distribution in water for different nucleus-nucleus collision models---LEMIII");
       mg->GetXaxis()->SetTitle("Depth(cm)");
       mg->GetYaxis()->SetTitle("alpha(Gy^{-1})"); 
       mg->GetXaxis()->CenterTitle();
       mg->GetYaxis()->CenterTitle(); 
       //gPad->BuildLegend();
       //gPad->SetLogy() ;

       mg->Draw("AP");
       c->BuildLegend();
      // gPad->SetLogy() ;

       return 0;
}
