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
// $Id: CSRunAction.hh,v 1.7 2002/01/09 17:24:09 ranjard Exp $
// GEANT4 tag $Name: geant4-08-00 $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef CSRunAction_h
#define CSRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "CSAnalysis.hh"
#include <fstream>

//class TProfile
using namespace std;

const G4int N_hist = 15;
const G4int N_of_slabs =1000;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Run;

class CSRunAction : public G4UserRunAction
{
  public:
    CSRunAction();
   ~CSRunAction();

  public:
    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);
    void GetSum_perSlab(G4double de, G4int pos);
    G4AnalysisManager * analysisManager;

  private:
    G4String Hist_name[N_hist]{"null","H","He", "Li", "Be", "B", "C", "N", "O", "F","Ne", "Na", "Mg", "Al","Si"};
    G4String Hist_namep[N_hist]{"pnull","pH","pHe", "pLi", "pBe", "pB", "pC", "pN", "pO", "pF","pNe", "pNa", "pMg", "pAl","pSi"};
    G4String title_hist[N_hist];
    G4String name_hist[N_hist];
    G4String charge_Number[N_hist];
    G4double sum_per_slab [N_of_slabs];
};

/*inline void CSRunAction::GetSum_perSlab(G4double de, G4int pos){
if (pos < N_of_slabs)
 {
 sum_per_slab [pos]+= de;
 }

}*/

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif





