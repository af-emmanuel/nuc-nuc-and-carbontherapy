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
// $Id: CSSteppingAction.hh,v 1.8 2003/09/15 15:38:14 maire Exp $
// GEANT4 tag $Name: geant4-08-00 $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef CSSteppingAction_h
#define CSSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "CSAnalysis.hh"
#include "G4StepPoint.hh"
#include <fstream>
#include <iostream>

using namespace CLHEP;
using namespace std;

class CSDetectorConstruction;

const G4int N_slabs=1000;


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class CSSteppingAction : public G4UserSteppingAction
{
  protected:
    ofstream *MyFile;
    G4int idHEdep0 ,idp1,idp2,idp3,idp4, idp5,idp6,idp7,idp8,idp9,idp10  ; 	// Id of the Edep !D Histogram
    G4AnalysisManager  * analysisManager;
    

  public:
    CSSteppingAction(const CSDetectorConstruction* Detector);
   ~CSSteppingAction();


    void UserSteppingAction(const G4Step*);


    void Set_Output_File (ofstream *File)
     {MyFile = File;}
     
private:

    const CSDetectorConstruction* pDetector;

};

//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
