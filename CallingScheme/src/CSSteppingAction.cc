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
// $Id: CSSteppingAction.cc,v 1.9 2005/02/02 17:11:11 maire Exp $
// GEANT4 tag $Name: geant4-08-00 $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "CSSteppingAction.hh"
#include "CSDetectorConstruction.hh"
#include "CSEventAction.hh"
#include "CSRunAction.hh"
#include "CSAnalysis.hh"
#include "G4RunManager.hh"

#include "G4Track.hh"
#include "G4UnitsTable.hh"

#include "TH1F.h"
#include "TH3F.h"
#include "TROOT.h"

#include "Randomize.hh"
#include <iomanip>
#include <fstream>
 #include <cmath>
 
#include "ParticleCounterManager.hh"

class G4Run;
class G4Event;
using namespace CLHEP;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CSSteppingAction::CSSteppingAction(const CSDetectorConstruction* Detector):G4UserSteppingAction(),pDetector(Detector)
{ 
analysisManager = G4AnalysisManager::Instance(); //instantiating g4analysis

//Gets ID to be filled 
idHEdep0 = analysisManager->GetH1Id("dose distribution"); //FOR DOSE HISTOGRAM

 
idp1 = analysisManager->GetP1Id("pH");  //FOR PARTICLE KINETIC ENERGY
idp2 = analysisManager->GetP1Id("pHe");
idp3 = analysisManager->GetP1Id("pLi");
idp4 = analysisManager->GetP1Id("pBe");
idp5 = analysisManager->GetP1Id("pB");
idp6 = analysisManager->GetP1Id("pC");
idp7 = analysisManager->GetP1Id("pN");
idp8 = analysisManager->GetP1Id("pO");
idp9 = analysisManager->GetP1Id("pF");
idp10 = analysisManager->GetP1Id("pNe");
 
G4cout<<"dose distribution histogram ID :"<<idHEdep0 <<G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CSSteppingAction::~CSSteppingAction()
{ 
//delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CSSteppingAction::UserSteppingAction(const G4Step* aStep)
    {
//*******************************************************usefull latter    
    //Get parameters of interest
    //G4cout << "Track ID:  " <<trackId<< G4endl;
    //G4double stepLength= aStep->GetStepLength();
    //G4cout<< "slab contend is:  " <<myrun->sum_per_slab [slab_position]<<endl; 
//********************************************************************************88    
  
//*******************************************************//parameters to fill first histogram     
    const G4Track* track = aStep->GetTrack();
    G4int trackId=track->GetTrackID();
    
    //for dose computation
    G4double edep = aStep->GetTotalEnergyDeposit();
    G4double massLayer =((2*2*2)/1000000.0)*kg; 
    
    //the position of each step
    G4ThreeVector xprestep= aStep->GetPreStepPoint()->GetPosition();
    
   //G4RunManager *runman= G4RunManager::GetRunManager();
   //CSRunAction*myrun= (CSRunAction*)runman->GetUserRunAction();
   //myrun->GetSum_perSlab(edep, slab_position);
    

//*****************************************************************************fill 1d histogram for dose deposited
    if (xprestep.x()>=0. )
    analysisManager->FillH1(idHEdep0, xprestep.x()/mm,edep/MeV);   
                        


//***************************************************//useful parameters to allow for profile plot and other access
    G4VPhysicalVolume* volume = track->GetVolume();
    const G4DynamicParticle* dynParticle = track->GetDynamicParticle();
    G4ParticleDefinition* particle = track->GetDefinition();
    G4double particlecharge  = particle->GetPDGCharge();
    G4double A_mass = (G4double)particle->GetAtomicMass(); 
    G4int Z = particle->GetAtomicNumber();
    G4int Charge_Z = (G4int)particlecharge;
    G4double kinEnergy = dynParticle->GetKineticEnergy();

 //***********************************************************************************  //fill profile histograms 
    if (Z==1)    
    analysisManager->FillP1(idp1,xprestep.x()/mm,(kinEnergy/MeV)/A_mass,1);
    
    if(Z==2)
    analysisManager->FillP1(idp2,xprestep.x()/mm,(kinEnergy/MeV)/A_mass,1); 
      
    if(Z==3)
    analysisManager->FillP1(idp3,xprestep.x()/mm,(kinEnergy/MeV)/A_mass,1);
    
    if(Z==4)
    analysisManager->FillP1(idp4,xprestep.x()/mm,(kinEnergy/MeV)/A_mass,1); 
    
    if(Z==5)
    analysisManager->FillP1(idp5,xprestep.x()/mm,(kinEnergy/MeV)/A_mass,1);
    
    if(Z==6)
    analysisManager->FillP1(idp6,xprestep.x()/mm,(kinEnergy/MeV)/A_mass,1);
    
    if(Z==7)
    analysisManager->FillP1(idp7,xprestep.x()/mm,(kinEnergy/MeV)/A_mass,1);
    
    if(Z==8)
    analysisManager->FillP1(idp8,xprestep.x()/mm,(kinEnergy/MeV)/A_mass,1);
    
    if(Z==9)
    analysisManager->FillP1(idp9,xprestep.x()/mm,(kinEnergy/MeV)/A_mass,1);
    
        
    if(Z==10)
    analysisManager->FillP1(idp10,xprestep.x()/mm,(kinEnergy/MeV)/A_mass,1);
//************************************************************************************//    
    
//************************************************************************//fillhistograms for particle weights

 /*  if (Z==1)   
     analysisManager->FillH1(idHEdep1,xprestep.x()/mm,1);
   
    if(Z==2)
     analysisManager->FillH1(idHEdep2,xprestep.x()/mm,1);
      
    if(Z==3)
     analysisManager->FillH1(idHEdep3,xprestep.x()/mm,1);
    
    if(Z==4)
    analysisManager->FillH1(idHEdep4,xprestep.x()/mm,1); 
    
    if(Z==5)
    analysisManager->FillH1(idHEdep5,xprestep.x()/mm,1);
    
    if(Z==6)
    analysisManager->FillH1(idHEdep6,xprestep.x()/mm,1);
    
    if(Z==7)
    analysisManager->FillH1(idHEdep7,xprestep.x()/mm,1);
    
    if(Z==8)
    analysisManager->FillH1(idHEdep8,xprestep.x()/mm,1);
    
    if(Z==9)
    analysisManager->FillH1(idHEdep9,xprestep.x()/mm,1);
    
       
    if(Z==10)
    analysisManager->FillH1(idHEdep10,xprestep.x()/mm,1);
//*******************************************************************/   
    if (xprestep.x() >= 0.0 && xprestep.x() <= 2000.0*mm)
     {
     ParticleCounterManager::GetManager()->FillEventCounter(aStep);
     }

}




