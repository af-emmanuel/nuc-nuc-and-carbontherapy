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
// $Id: CSEventAction.hh,v 1.7 2002/01/09 17:24:09 ranjard Exp $
// GEANT4 tag $Name: geant4-08-00 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
#ifndef CSEventAction_h
#define CSEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include <fstream>
#include <iostream>
using namespace std;

class G4Event;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class CSEventAction : public G4UserEventAction
{
  private:
  ofstream *MyFile;
  public:
    CSEventAction();
   ~CSEventAction();

  public:
    void BeginOfEventAction(const G4Event*);
    void EndOfEventAction(const G4Event*);
    void AddAbs(G4double de);
    void Set_Output_File1 (ofstream *File){MyFile = File;}
};

/*inline void CSEventAction::AddAbs(G4double edep) {
  sumedep += edep; 
    G4cout<<edep<<endl;

   G4AnalysisManager  * analysisManager = G4AnalysisManager::Instance();

  // fill histograms
  analysisManager->FillH1(xprestep.x(),edep);
    
}*/

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
