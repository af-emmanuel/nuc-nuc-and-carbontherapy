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
// $Id: CSGunMessenger.cc,v 1.10 2004/04/05 16:21:23 maire Exp $
// GEANT4 tag $Name: geant4-08-00 $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "CSGunMessenger.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"
#include "globals.hh"
#include "Riostream.h"

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CSGunMessenger::CSGunMessenger(void)
{ 
  CSDir = new G4UIdirectory("/CS/");
  CSDir->SetGuidance("UI commands specific to this example.");
  
  beamDir = new G4UIdirectory("/CS/beam/");
  beamDir->SetGuidance("Beam control.");
  
  SetPartCmd = new G4UIcmdWithAString("/CS/beam/setParticle",this);
  SetPartCmd->SetGuidance("Select Particle for the beam.");
  SetPartCmd->SetParameterName("choice",false);
  SetPartCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  SetNrjCmd = new G4UIcmdWithADoubleAndUnit("/CS/beam/setEnergy",this);
  SetNrjCmd->SetGuidance("Select Energy of the beam.");
  SetNrjCmd->SetParameterName("Ebeam",false);
  SetNrjCmd->SetRange("Ebeam>0.");
  SetNrjCmd->SetUnitCategory("Energy");
  SetNrjCmd->SetDefaultUnit("MeV");
  SetNrjCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  
  
  RunCmd = new G4UIcmdWithAString("/CS/run",this);  
  RunCmd->SetGuidance("Start run.");
  RunCmd->SetParameterName("nEvent",false);
  RunCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CSGunMessenger::~CSGunMessenger()
{
  delete SetPartCmd;
  delete SetNrjCmd;
  delete RunCmd;
  delete beamDir;
  delete CSDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CSGunMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  G4UImanager* UI = G4UImanager::GetUIpointer();
  G4String commandToProceed = "none";
  
  if( command == SetPartCmd )
   { 
   if(newValue == "gamma" || newValue == "e-" 
      || newValue == "proton" || newValue == "alpha")
    {
    commandToProceed = "/gun/particle "+newValue;
    }
   else if(newValue == "C12")
    {
    UI->ApplyCommand("/gun/particle ion");
    commandToProceed = "/gun/ion 6 12 6 0.0";
    }
   }
   
  if( command == SetNrjCmd )
   {
   commandToProceed = "/gun/energy "+newValue;
   }  
  
  if( command == RunCmd )
   { 
   commandToProceed = "/run/beamOn "+newValue;
   }
  
  if(commandToProceed != "none")
   {
   cout << "Execution de " << commandToProceed << "..." << endl;
   G4cout << "Execution de " << commandToProceed << "..." << G4endl;
   UI->ApplyCommand(commandToProceed);
   }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
