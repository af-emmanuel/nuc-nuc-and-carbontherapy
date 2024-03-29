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
// $Id: CSPhysicsList.hh,v 1.5 2002/01/09 17:23:48 ranjard Exp $
// GEANT4 tag $Name: geant4-08-00 $
//
// 
//
// CSPhysicsList
//  Construct/define particles and physics processes
//
//  Particle defined in ExampleN01
//    geantino
//
//  Process defined in ExampleN01
//    transportation
//

#ifndef CSPhysicsList_h
#define CSPhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"

class CSPhysicsList: public G4VUserPhysicsList
{
  public:
    CSPhysicsList();
    ~CSPhysicsList();

  protected:
    // Construct particle and physics process
    void ConstructParticle();
    void ConstructProcess();
    void SetCuts();
    void ConstructEM();
    void ConstructGeneral();
    void ConstructNuclearReactions();

};

#endif







