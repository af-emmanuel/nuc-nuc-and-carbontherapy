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
// $Id: CSPrimaryGeneratorAction.cc,v 1.5 2002/05/14 01:50:31 asaim Exp $
// GEANT4 tag $Name: geant4-08-00 $
//

#include "CSPrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Ions.hh"
#include "G4UImanager.hh"
#include "globals.hh"

using namespace std;
using namespace CLHEP;

CSPrimaryGeneratorAction::CSPrimaryGeneratorAction()
{
  G4int n_particle = 1;
  particleGun = new G4ParticleGun(n_particle);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="e-"));

}

CSPrimaryGeneratorAction::~CSPrimaryGeneratorAction()
{
  delete particleGun;
}

void CSPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //G4cout << "CSPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) called"
		  //<<G4endl;
  if(anEvent->GetEventID() == 0)
   {
   G4cout << "Z = " << particleGun->GetParticleDefinition()->GetPDGCharge();
   if(particleGun->GetParticleDefinition()->GetPDGCharge() > 2)
    {
    G4Ions *ions=(G4Ions *)particleGun->GetParticleDefinition();
    a=ions->GetAtomicMass();
    G4cout << ", A = " << a; 
    }
   else
    {
    a=1;
    }
   G4cout << G4endl;
   G4cout << particleGun->GetParticleDefinition()->GetParticleType() << G4endl;
   G4cout << particleGun->GetParticleDefinition()->GetParticleSubType() << G4endl;
   eDeb=particleGun->GetParticleEnergy();
   G4cout << "Beam : " << 
   particleGun->GetParticleDefinition()->GetParticleName() << " a " << eDeb/MeV;
   if(a==1)
    G4cout << " MeV." << G4endl;
   else
    G4cout << " MeV/u." << G4endl;
   }
  G4double de=0.1*MeV;
  G4double y,z,ray;
  ray=0.1*cm;

  G4int i = anEvent->GetEventID();
  G4ThreeVector v(1.0,0.0,0.0);
  // On peut a ce niveau changer l'energie, la position de depart de la particule et sa
  // direction initiale. Utile si on veut introduire une distribution d'energie, une taille ou
  // une geometrie de faiseau et une dispersion angulaire de faisceau.
  G4double energie=eDeb;
  G4double r2max=ray*ray;
  y=ray;
  z=ray;
  while(y*y+z*z > r2max)
   {
   y=0.0;
   z=0.0;
   }
  energie*=a;   
  particleGun->SetParticleEnergy(energie);
  particleGun->SetParticlePosition(G4ThreeVector(-2.0*m, y, z));
  particleGun->SetParticleMomentumDirection(v);
  
  
  particleGun->GeneratePrimaryVertex(anEvent);
}


