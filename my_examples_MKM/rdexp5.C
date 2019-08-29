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
#include <math.h> 


using namespace std;

class CSV5
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
        void readCSV (string fileParticle, string fileDose)
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
                        if (*max_element(doz, doz + 405)>0)
                                {
                                for (int i=0; i<array.size(); i++)
                                        {
                                        doz[i]=5*doz[i]  /(*max_element(doz, doz + 405));
                                        SF[i]= exp(-Y_axis[i]*doz [i]-beta [i]*pow(doz[i],2));
                                        //cout << SF[i]<<endl;
                                        }
                                }
                               
                            else
                                {
                                cout<< "maximum value is zero, this could pose a problem"<<endl;
                                }
                                
                        //cout<< "maximum dose value is: "<<*max_element(doz, doz + 405)<<endl;        
                }          
                
        };
                          

int rdexp5 ()
{	

        CSV5 CSVobject;

        auto c5 = new TCanvas("c5","c5",600, 400);
        TMultiGraph  *mg  = new TMultiGraph();

        CSVobject. readCSV("ParticleFieldBF_HSG_MKM_LQparameters_MKM.csv","dose_BF.csv");        
        TGraph *BF  = new TGraph(405,CSVobject. X_axis,CSVobject.SF);
        BF->SetTitle("BF");
        BF->SetMarkerStyle(29);
        BF->SetMarkerColor(3);

       CSVobject. readCSV("ParticleFieldBG_HSG_MKM_LQparameters_MKM.csv","dose_BG.csv");
        TGraph *BG  = new TGraph(405,CSVobject. X_axis,CSVobject.SF);
        BG->SetTitle("BG");
        BG->SetMarkerStyle(39);
        BG->SetMarkerColor(2);

        CSVobject. readCSV("ParticleFieldQF_HSG_MKM_LQparameters_MKM.csv","dose_QF.csv");  
        TGraph *QF  = new TGraph(405,CSVobject. X_axis,CSVobject.SF);
        QF->SetTitle("QF");
        QF->SetMarkerStyle(20);
        QF->SetMarkerColor(7);

        CSVobject. readCSV("ParticleFieldQG_HSG_MKM_LQparameters_MKM.csv","dose_QG.csv"); 
        TGraph *QG  = new TGraph(405,CSVobject. X_axis,CSVobject.SF);
        QG->SetTitle("QG");
        QG->SetMarkerStyle(49);
        QG->SetMarkerColor(4);

        CSVobject. readCSV("ParticleFieldEM_HSG_MKM_LQparameters_MKM.csv","dose_EM.csv");  
        TGraph *EM  = new TGraph(405,CSVobject. X_axis,CSVobject.SF);
        EM->SetTitle("EM");
        EM->SetMarkerStyle(33);       
        EM->SetMarkerColor(6);

        mg->Add(BF);
        mg->Add(BG);
        mg->Add(QF);
        mg->Add(QG);
        mg->Add(EM);


        mg->SetTitle("Survival curve in water for different nucleus-nucleus collision models---MKM");
        mg->GetXaxis()->SetTitle("Depth in water(cm)");
        mg->GetYaxis()->SetTitle("survival fraction");

        gPad->SetLogx();
        //gPad->BuildLegend();
        //if(mg->Add(BG)||mg->Add(BF)||mg->Add(QG)||mg->Add(BG)||mg->Add(EM){
        mg->Draw("AP");
        c5->BuildLegend();

        //else{cout<<"cant plot graph"<<endl; } 

       return 0;
}
