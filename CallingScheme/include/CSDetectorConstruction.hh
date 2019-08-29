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
// $Id: CSDetectorConstruction.hh,v 1.5 2002/01/09 17:23:48 ranjard Exp $
// GEANT4 tag $Name: geant4-08-00 $
//

#ifndef CSDetectorConstruction_H
#define CSDetectorConstruction_H 1

class G4LogicalVolume;
class G4VPhysicalVolume;

#include "G4VUserDetectorConstruction.hh"

class CSDetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    CSDetectorConstruction();
    ~CSDetectorConstruction();

    G4VPhysicalVolume* Construct();

    //special method to get volume of interest
    const G4VPhysicalVolume* GetEdepVolume() const;

  private:
    
    // Logical volumes
    //
    G4LogicalVolume* aireExperimentale_log;
    G4LogicalVolume* blocEau_log;

    // Physical volumes
    //
    G4VPhysicalVolume* aireExperimentale_phys;
    G4VPhysicalVolume* blocEau_phys;
    };

    inline const G4VPhysicalVolume *CSDetectorConstruction:: GetEdepVolume() const{
    return blocEau_phys; 
 
    }

#endif

