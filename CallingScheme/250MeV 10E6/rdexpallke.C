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
#include "TLatex.h"
using namespace std;
/////plots survival fractions for 1Gy
class CSV
      {
      
public:

       const int no_bin =405;
       double X_axis[405]{};//depth on the x-axis
       double Y_axis[405]{};//alpha on the y-axis
       double beta[405]{}; //beta
       double doz[405]{};
       //double H[405]{},He[405]{},Li[405]{},Be[405]{},B[405]{},C[405]{},N[405]{},O[405]{},F[405]{},Ne[405]{};
       double Y_element[405][10]={};
       
       double max;
       string files;
       string file;
       
//private:
        void readCSV (string fileParticle)
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
             //remember, all the elements in the array are strings separated             
                         }
                         
                        

                         
                             //empty array of possible previous imputs
                         for (size_t i=1; i<no_bin; i++)
                          {
                            X_axis[i-1]=0.;
                            
                            for(int k=0;k<10;k++)
                            {
                            Y_element[i][k]=0.;
                            }
                            
                          }
                          
                        if(array.size()>1)
                        
                                {
                         //to print out generated 2d arrays due to added vectors
                                for (size_t i=1; i<array.size(); ++i)//array.size()
                                  {
                                     

                                    double depth = 0.2 * (i-1);//remeber, the first elements are the headings
                                    for(int k=0;k<10;k++)
                                           {
                                                Y_element[i][k] =stod(array[i][k]);
                                                //cout<<"array elements"<<endl;
                                                //cout<<"array elements"<<Y_element[i][k]<<endl;
                                                
                                            }
                                         // cout<<"array elements  "<<Y_element[i][5]<<endl;
                                    //fill array with current input
                                   X_axis[i-1]=depth;
                                    //cout<<"array axis  "<< X_axis[i-1]<<endl;
                                         
                                  }
                                  
                                 }


                                
       
                }  
        
                
        };
                          

int rdexpallke ()
{	

        CSV CSVobject;
        const int no_points = 200;

        TCanvas * c = new TCanvas("c","c",200,10,700,1000);
        c->Divide (2,3);
 
        int BraggPeakDose [6]={1,2,5,10,15,20};
        TString fig[6]={"(a)","(b)","(c)","(d)","(e)","(f)"};
        string nuc[5]={"BF","BG","QF","QG","EM"};
        TString particleType [11]{"null","H","He", "Li", "Be", "B", "C","N", "O", "F","Ne"};

         int lincol[10]{600,416,860,840,880,900,800,616,400,1};
        
        double y[500]{};
        TGraph *plot[10]{};
        TMultiGraph  *mg [6]{};
        TPad* c_b[6]{};
        TLegend *legend[6]{};
        TLegendEntry *le[6]{};
        string nuc1[5]={"BIC-FBU","BIC-GEM","QMD-FBU","QMD-GEM","emstandard_opt4"};
        TLatex *text[5]{};
        //= new TLatex();
        
       
        legend [4]=new TLegend();
        
        for (int n=0; n<5;n++)
        {
                for(int p=0;p<10;p++)
                {
                        
                        CSVobject. readCSV(nuc[n]+"KE.csv"); 
                //========================fill array==============================================
                        if(p==2||p==3||p==7||p==8||p==9) 
                        {
                               for (int i=0;i<405;i++)
                                {
                                        y[i]=  CSVobject.Y_element[i][p];
                                        
                                }
                        }
                        else
                        {
                        for (int i=0;i<405;i++)
                                {
                                        y[i]= CSVobject.Y_element[i][p];
                                        
                                }
                        }
                        
                        plot[p]= new TGraph(no_points,CSVobject. X_axis,y);
                        plot[p]->SetLineColor(lincol[p]);
                     
                     
                       if(p==4||p==6||p==2)
                        {
                            plot[p]->SetLineWidth(2);
                        }
                //==========================empyt array for reuse=================================       
                        for (int i=0;i<405;i++)
                                {
                                        y[i]= 0.;
                                        
                                }
                      
                       if (n==4)
                       {
                       legend[4]->AddEntry(plot[p], particleType[p+1]);
                       }
    
                
                }
                

                mg[n]=new TMultiGraph();
                
                mg[n] -> Add(plot[0]);
                mg[n] -> Add(plot[1]);
                mg[n] -> Add(plot[2]);
                mg[n] -> Add(plot[3]);
                mg[n] -> Add(plot[4]);
                mg[n] -> Add(plot[5]);
                mg[n] -> Add(plot[6]);  
                mg[n] -> Add(plot[7]);
                mg[n] -> Add(plot[8]);
                mg[n] -> Add(plot[9]); 
                
                
                
  //*****************working with canvas*****************************************************              


                  
                c->cd(n+1);
                c_b [n]= (TPad*)(c->GetPrimitive(TString::Format("c_%d",n+1)));
                
                  
                      c_b[n]->SetTickx(1);
                      c_b[n]->SetTicky(1);
                   
                if (c_b[4]||c_b[0]||c_b[1])
                   {

                      mg[n]->GetYaxis()->SetTitle("Mean Kinetic Energy(MeV/u)"); 
                      mg[n] -> GetYaxis() -> CenterTitle();

                    }
               if (c_b[4]||c_b[3])
               {     
                      mg[n]->GetXaxis()->SetTitle("Depth(cm)");
                      mg[n] -> GetXaxis() -> CenterTitle();
               }
              mg[n] ->Draw("APL");
                
        }
        
          
          c->cd(6);
          
          legend[4]->SetHeader("carbon and mixed field--Legend");
          
          legend[4]->Draw();
          
         for(int n=0; n<5;n++)
          {
          c->cd(n+1);
          text[n]= new TLatex();
          text[n]->DrawTextNDC(0.53, 0.8,nuc1[n].c_str());
          }


       return 0;
}


