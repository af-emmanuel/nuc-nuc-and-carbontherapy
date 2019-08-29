//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
// $Id: CSRunAction.cc,v 1.8 2004/03/08 15:14:49 maire Exp $
// GEANT4 tag $Name: geant4-08-00 $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "CSRunAction.hh"
#include "CSAnalysis.hh"
#include "CSSteppingAction.hh"
#include <string>
//#include <TProfile.h>

#include "G4Run.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include <fstream>
#include <iostream>

using namespace std;


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CSRunAction::CSRunAction()
{

  // Create analysis manager
  // The choice of analysis technology is done via selectin of a namespace
  // in CSAnalysis.hh
  analysisManager = G4AnalysisManager::Instance();

  analysisManager->SetVerboseLevel(1);


 // Creating histograms   
 analysisManager->CreateH1("dose distribution", "Dose distribution of carbon in water",1000, 0.,2.0*m);
 //"Ion profile of charge: " + to_string(i)

 for ( G4int i =0 ;i<N_hist ; i++)
        {
    analysisManager->CreateP1(Hist_namep[i],"Depth-Mean Kineteic Energy profile",1000, 0.,2.0*m); //profile
    analysisManager->CreateH1(Hist_name[i],"Particle weight distribution",1000, 0.,2.0*m);//histogram
        }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CSRunAction::~CSRunAction()
{
//delete G4AnalysisManager::Instance(); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CSRunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4cout << "CSRunAction::BeginOfRunAction(const G4Run* aRun) called" << G4endl;
  G4cout << "### Run " << aRun->GetRunID() << " starts." << G4endl;
    

  // Name and Open an output file
  //ensure it corresponds with the type of nucleus nucleus model
  
  //G4String fileName = "CallEnergy.root"; // general physics list
  //G4String fileName = "CallEnergyEM.root"; //emstandard_opt4
  //G4String fileName = "CallEnergyQF.root"; //TT_QMD_FBU
  //G4String fileName = "CallEnergyQG.root"; //TT_QMD_GEM
  //G4String fileName = "CallEnergyBF.root"; //TT_BIC_FBU
  G4String fileName = "CallEnergyBG.root"; //TT_BIC_GEM
  
  analysisManager->OpenFile(fileName);
 

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CSRunAction::EndOfRunAction(const G4Run* aRun)
{   

 //ofstream MyFile;
 //MyFile.open("edepfile");//edep accummulated per bin by computation

  G4cout << "CSRunAction::EndOfRunAction(const G4Run* aRun) called" << G4endl;
  G4cout << "### Run " << aRun->GetRunID() << " stops." << G4endl;

  //for ( G4int i=0; i<1000; i++){
  //MyFile <<sum_per_slab [i]<<endl;}

  //write-in and close file "CallEnergy"
  analysisManager->Write();
  analysisManager->CloseFile();
  
  //MyFile.close();

}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
