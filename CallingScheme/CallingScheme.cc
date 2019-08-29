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
// $Id: CS.cc,v 1.4 2002/01/09 17:23:47 ranjard Exp $
// GEANT4 tag $Name: geant4-06-02-patch-01 $
//
// 
// --------------------------------------------------------------
//      GEANT 4 - CS T
//
// --------------------------------------------------------------
// Comments
//
// 
// --------------------------------------------------------------

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIsession.hh"
#include "G4VisExecutive.hh"

#ifdef G4UI_USE_ROOT
#include "G4UIRoot.hh"
#endif

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"  //repeatition? 
#endif

#include "CSDetectorConstruction.hh"
#include "CSPhysicsList.hh"
#include "TTPhysicsList.hh"
#include "CSPrimaryGeneratorAction.hh"
#include "CSRunAction.hh"
#include "CSEventAction.hh"
#include "CSSteppingAction.hh"

//#include "DanielRunAction.hh"
//#include "DanielSteppingAction.hh"

#include "CSGunMessenger.hh"
#include <fstream>

#include "TFile.h"
#include "TH1.h"

int main(int argc,char** argv)
{
  ofstream MyFile;
  //ofstream MyFile1;
  MyFile.open("outputfile.hdr");
  //MyFile1.open("outputfile1.txt");
 // Construct the default run manager
  G4RunManager* runManager = new G4RunManager;

  // set mandatory initialization classes
  CSDetectorConstruction* det=new CSDetectorConstruction();
  
  //CSPhysicsList* phyl= new CSPhysicsList();
  TTPhysicsList* ttphyl= new TTPhysicsList();
  //ttphyl->AddPhysicsList ("emstandard_opt4");
  //ttphyl->AddPhysicsList ("TT_QMD_FBU");
  //ttphyl->AddPhysicsList ("TT_QMD_GEM");
  //ttphyl->AddPhysicsList ("TT_BIC_FBU");
  ttphyl->AddPhysicsList ("TT_BIC_GEM");
  
  runManager->SetUserInitialization(det); 
  //runManager->SetUserInitialization(phyl);
  runManager->SetUserInitialization(ttphyl);

#ifdef G4VIS_USE
  // Visualization, if you choose to have it!
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
#endif
  
  // set mandatory user action class
  runManager->SetUserAction(new CSPrimaryGeneratorAction);

  // set optional user action classes
  runManager->SetUserAction(new CSRunAction);
  //runManager->SetUserAction(new DanielRunAction);
  CSEventAction *evt=new CSEventAction();
  evt->Set_Output_File1 (&MyFile);
  runManager->SetUserAction(evt);  

  CSSteppingAction *myStepAction = new CSSteppingAction(det);
  //DanielSteppingAction *myStepAction = new DanielSteppingAction(det);
   myStepAction->Set_Output_File (&MyFile);
  runManager->SetUserAction(myStepAction);  

  // Initialize G4 kernel
  runManager->Initialize();

  // get the pointer to the UI manager and set verbosities
  G4UImanager* UI = G4UImanager::GetUIpointer();
  G4UIsession *session = (G4UIsession *)0;

#if defined (G4UI_USE_ROOT)
  // G4URoot is a ROOT based GUI.
  session = new G4UIRoot(argc,argv);
#endif

  CSGunMessenger *beamControl=new CSGunMessenger();

  UI->ApplyCommand("/control/execute visuCS.mac"); // visu & /run/beamOn 10000
  UI->ApplyCommand("/run/verbose 0");
  UI->ApplyCommand("/event/verbose 0");
  UI->ApplyCommand("/tracking/verbose 0");

  // start a run
  //int numberOfEvent = 10000;
  //runManager->BeamOn(numberOfEvent);

  if (session)
    {
      session->SessionStart();
      if ( (G4UImanager::GetUIpointer()) &&
	   (session == (G4UImanager::GetUIpointer())->GetSession()) )
	delete session;
    }

  // job termination
  if (runManager == G4RunManager::GetRunManager())
    delete runManager;

  if(beamControl)
    delete beamControl;


  MyFile.close();
  //MyFile1.close();


  return 0;
}



