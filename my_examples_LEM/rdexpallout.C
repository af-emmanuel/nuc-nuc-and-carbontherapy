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
       string files;
       string file;
       
       
//private:
        void readCSV (string fileParticle, string fileDose, int a, string b)
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
                                    double depth = 0.2 * (i-1);
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
                                        doz[i]=doz[i]/ (*max_element(doz, doz + 405));
                                        SF[i]= exp(-Y_axis[i]*a*doz [i]-beta [i]*pow(a*doz[i],2));
                                        //cout << SF[i]<<endl;
                                       // if(i==201){SF[201]=0.;}
                                        }
                                }
                          else
                                {
                                cout<< "maximum value is zero, this could pose a problem"<<endl;
                                }
                   
                            /* ofstream sf; 
                             sf.open("sf_" +to_string(a)+b+".csv");
                            
                            /*for(int i =0;i<400;i++)
                            {
                             sf<< SF[i]<<endl;;
                            }
                            
                            sf.close(); */
                }          
                
        };
                          

int rdexpallout ()
{	

        CSV CSVobject;

       TCanvas *c = new TCanvas("c","c",200,10,700, 900);
       c->Divide (1);
        
        const int no_points = 100;
        double SF1[405][10]={};
        double SF2[405][10]={};
        double SF5[405][10]={};
        double SF10[405][10]={};
        double SF15[405][10]={};
        double SF20[405][10]={};
        
        
        double Sp1[405]={};
        double Sp2[405]={};
        double Sp5[405]={};
        double Sp10[405]={};
        double Sp15[405]={};
        double Sp20[405]={};
        
        
        
        int BraggPeakDose [6]={1,2,5,10,15,20}; 

        
        
        
        
        for (int i=0; i<6; i++)
        {
            
          CSVobject. readCSV("ParticleFieldEM_HSG_LEMIII_LQparameters_LEMIII.csv","dose_EM.csv",BraggPeakDose[i], "emstandard_opt4");  

                for (int k=0;k<no_points;k++)
                {    
                    if(i==0)
                    SF1[k][4]= CSVobject.SF[k]; 
                      
                    if(i==1)
                    SF2[k][4]= CSVobject.SF[k];
                    
                    if(i==2)
                    SF5[k][4]= CSVobject.SF[k];
                    
                    if(i==3)
                    SF10[k][4]= CSVobject.SF[k];
                    
                    if(i==4)
                    SF15[k][4]= CSVobject.SF[k];
                    
                    if(i==5)
                    SF20[k][4]= CSVobject.SF[k]; 
                }
            
            
            
            
                                       
        CSVobject.readCSV("ParticleFieldBF_HSG_LEMIII_LQparameters_LEMIII.csv","dose_BF.csv",BraggPeakDose[i],"BIC-FBU");


        
                for (int k=0;k<no_points;k++)
                {    
                    if(i==0)
                    SF1[k][0]= CSVobject.SF[k]; 
                      
                    if(i==1)
                    SF2[k][0]= CSVobject.SF[k];
                    
                    if(i==2)
                    SF5[k][0]= CSVobject.SF[k];
                    
                    if(i==3)
                    SF10[k][0]= CSVobject.SF[k];
                    
                    if(i==4)
                    SF15[k][0]= CSVobject.SF[k];
                    
                    if(i==5)
                    SF20[k][0]= CSVobject.SF[k]; 
                }

        CSVobject. readCSV("ParticleFieldBG_HSG_LEMIII_LQparameters_LEMIII.csv","dose_BG.csv",BraggPeakDose[i], "BIC-GEM");

                for (int k=0;k<no_points;k++)
                {    
                    if(i==0)
                    SF1[k][1]= CSVobject.SF[k]; 
                      
                    if(i==1)
                    SF2[k][1]= CSVobject.SF[k];
                    
                    if(i==2)
                    SF5[k][1]= CSVobject.SF[k];
                    
                    if(i==3)
                    SF10[k][1]= CSVobject.SF[k];
                    
                    if(i==4)
                    SF15[k][1]= CSVobject.SF[k];
                    
                    if(i==5)
                    SF20[k][1]= CSVobject.SF[k]; 
                }        

        CSVobject. readCSV("ParticleFieldQF_HSG_LEMIII_LQparameters_LEMIII.csv","dose_QF.csv",BraggPeakDose[i], "QMD-FBU");  

                for (int k=0;k<no_points;k++)
                {    
                    if(i==0)
                    SF1[k][2]= CSVobject.SF[k]; 
                      
                    if(i==1)
                    SF2[k][2]= CSVobject.SF[k];
                    
                    if(i==2)
                    SF5[k][2]= CSVobject.SF[k];
                    
                    if(i==3)
                    SF10[k][2]= CSVobject.SF[k];
                    
                    if(i==4)
                    SF15[k][2]= CSVobject.SF[k];
                    
                    if(i==5)
                    SF20[k][2]= CSVobject.SF[k]; 
                }        


        CSVobject. readCSV("ParticleFieldQG_HSG_LEMIII_LQparameters_LEMIII.csv","dose_QG.csv",BraggPeakDose[i], "QMD-GEM"); 

                for (int k=0;k<no_points;k++)
                {    
                    if(i==0)
                    SF1[k][3]= CSVobject.SF[k]; 
                      
                    if(i==1)
                    SF2[k][3]= CSVobject.SF[k];
                    
                    if(i==2)
                    SF5[k][3]= CSVobject.SF[k];
                    
                    if(i==3)
                    SF10[k][3]= CSVobject.SF[k];
                    
                    if(i==4)
                    SF15[k][3]= CSVobject.SF[k];
                    
                    if(i==5)
                    SF20[k][3]= CSVobject.SF[k]; 
                }        


                

        
//////////////////////////////////////////////////////////////////legends   
    

        //c_b[i]->BuildLegend();  


        //else{cout<<"cant plot graph"<<endl; 
        }
        
        
        for(int j=0;j<no_points;j++)
        {
        
        Sp1[j]=(((SF1[j][0]+SF1[j][1])*0.5 - (SF1[j][2]+SF1[j][3])*0.5)*100/((SF1[j][2]+SF1[j][3])*0.5));
        Sp2[j]=(((SF2[j][0]+SF2[j][1])*0.5 - (SF2[j][2]+SF2[j][3])*0.5)*100/((SF2[j][2]+SF2[j][3])*0.5));
        Sp5[j]=(((SF5[j][0]+SF5[j][1])*0.5 - (SF5[j][2]+SF5[j][3])*0.5)*100/((SF5[j][2]+SF5[j][3])*0.5));
        Sp10[j]=(((SF10[j][0]+SF10[j][1])*0.5 - (SF10[j][2]+SF10[j][3])*0.5)*100/((SF10[j][2]+SF10[j][3])*0.5));
        Sp15[j]=(((SF15[j][0]+SF15[j][1])*0.5 - (SF15[j][2]+SF15[j][3])*0.5)*100/((SF15[j][2]+SF15[j][3])*0.5));
        Sp20[j]=(((SF20[j][0]+SF20[j][1])*0.5 - (SF20[j][2]+SF20[j][3])*0.5)*100/((SF20[j][2]+SF20[j][3])*0.5));
        
       
        }

        for(int j=0;j<no_points;j++)
        {
       cout<<Sp20[j]<<endl;
        }

        TGraph *g1  = new TGraph(no_points,CSVobject. X_axis,Sp1);
        g1->SetLineColor(4);
        g1->SetLineWidth(2);
        
        TGraph *g2   = new TGraph(no_points,CSVobject. X_axis,Sp2);
        g2->SetLineColor(400);
        g2->SetLineWidth(2);
        
        TGraph *g5  = new TGraph(no_points,CSVobject. X_axis,Sp5);
        g5->SetLineColor(3);
        g5->SetLineWidth(2);
        
        TGraph *g10   = new TGraph(no_points,CSVobject. X_axis,Sp10);
        g10->SetLineColor(616);
        g10->SetLineWidth(2);
        
        TGraph *g15   = new TGraph(no_points,CSVobject. X_axis,Sp15);
        g15->SetLineColor(1);
        g15->SetLineWidth(2);
        
        TGraph *g20  = new TGraph(no_points,CSVobject. X_axis,Sp20);
        g20->SetLineColor(900);
        g20->SetLineWidth(2);

        TMultiGraph  *mg = new TMultiGraph();
        mg->Add(g1);
        mg->Add(g2);
        mg->Add(g5);
        mg->Add(g10);
        mg->Add(g15);
        mg->Add(g20);
        mg->GetYaxis()->SetTitle("deviation (%)");
        mg->GetYaxis() -> CenterTitle();
        mg->GetXaxis()->SetTitle("Depth(cm)");
        mg-> GetXaxis() -> CenterTitle();
        
        
        c->cd(1);
        TPad* c_b = (TPad*)(c->GetPrimitive(TString::Format("c_%d",1)));
        c_b->SetTickx(1);
        c_b->SetTicky(1);
        
        mg->Draw("ALP");
        
       // TLegendEntry *le =new TLegendEntry (0.7,0.7,0.45,0.951);
       TLegend *le=new TLegend (0.7,0.7,0.45,0.951);
        
        //leg->SetTextSize(0.05); 
        
        le->SetHeader("Dose to Bragg peaks");
        
        le->AddEntry(g1, "1Gy");
        le->AddEntry(g2, "2Gy");
        le->AddEntry(g5, "5Gy");
        le->AddEntry(g10, "10Gy");
        le->AddEntry(g15,"15Gy");
        le->AddEntry(g20,"20Gy");

        le->Draw();

       return 0;
}
