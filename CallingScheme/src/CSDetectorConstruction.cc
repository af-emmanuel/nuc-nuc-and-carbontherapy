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
// $Id: CSDetectorConstruction.cc,v 1.8 2003/10/06 08:59:11 maire Exp $
// GEANT4 tag $Name: geant4-08-00 $
//

#include "CSDetectorConstruction.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4NistManager.hh"
#include "G4SDManager.hh"
#include "globals.hh"

using namespace CLHEP;

CSDetectorConstruction::CSDetectorConstruction()
 :  aireExperimentale_log(0),
    blocEau_log(0),
    aireExperimentale_phys(0),
    blocEau_phys(0)
{}

CSDetectorConstruction::~CSDetectorConstruction()
{
}

G4VPhysicalVolume* CSDetectorConstruction::Construct()
{

  //------------------------------------------------------ materials

  G4double a;  // atomic mass
  G4double z;  // atomic number
  G4double density;

//
// Elements
//
  G4String symbol;             //a=mass of a mole;
  G4int iz, n;                 //iz=number of protons  in an isotope; 
                             // n=number of nucleons in an isotope;
  G4int ncomponents, natoms;

  G4Element* H  = new G4Element("Hydrogen",symbol="H" , z= 1., a= 1.01*g/mole);
  G4Element* C  = new G4Element("Carbon"  ,symbol="C" , z= 6., a= 12.01*g/mole);
  G4Element* N  = new G4Element("Nitrogen",symbol="N" , z= 7., a= 14.01*g/mole);
  G4Element* O  = new G4Element("Oxygen"  ,symbol="O" , z= 8., a= 16.00*g/mole);
  G4Element* Si = new G4Element("Silicon",symbol="Si" , z= 14., a= 28.09*g/mole);

  G4Material* Eau = 
    new G4Material("Eau", density= 1.000*g/cm3, ncomponents=2);
  Eau->AddElement(H, natoms=2);
  Eau->AddElement(O, natoms=1);
// overwrite computed meanExcitationEnergy with ICRU recommended value 
  Eau->GetIonisation()->SetMeanExcitationEnergy(75.0*eV);
 
   //------ Quelques impressions sur les matériaux

  G4cout << "Affichage sur les materiaux " << "\n";
  G4cout << "---> Eau perso" << "\n";
  G4cout << Eau << "\n";

  //DEfinining material from Geant4 data base.
// for water
  G4NistManager* man = G4NistManager::Instance();
  G4Material* H2O = man->FindOrBuildMaterial("G4_WATER");
  G4cout << "---> Eau GEANT4" << "\n";
  G4cout << H2O << "\n";
//for air
  G4Material* Air = man->FindOrBuildMaterial("G4_AIR");
  G4cout << "---> Air GEANT4" << "\n";
  G4cout << Air << "\n";

  G4Material* Vide = 
       new G4Material("VideGalactique", z=1., a=1.01*g/mole,
                      density= universe_mean_density,
                      kStateGas, 2.73*kelvin, 3.e-18*pascal);
  G4cout << "---> Vide " << "\n";
  G4cout << Vide << "\n";
  G4cout << "\nListe des materiaux" << "\n";
  G4cout << *(G4Material::GetMaterialTable());

//------------------------------------------------------ volumes

  //------------------------------ experimental hall (world volume)
  //------------------------------ beam line along x axis

  G4double aireExp_x = 3.0*m;
  G4double aireExp_y = 2.0*m;
  G4double aireExp_z = 2.0*m;

  G4Box* aireExperimentale_box = new G4Box("aireExp_box",aireExp_x,aireExp_y,aireExp_z);
  aireExperimentale_log = new G4LogicalVolume(aireExperimentale_box,
                                             Vide,"aireExp_log",0,0,0);
  aireExperimentale_phys = new G4PVPlacement(0,G4ThreeVector(),
                                      aireExperimentale_log,"aireExp",0,false,0);

  //------------------------------ Bloc d'eau

  G4double block_x = 1.0*m;
  G4double block_y = 50.0*cm;
  G4double block_z = 50.0*cm;
  G4Box* blocEau_box = new G4Box("blocEau_box",block_x,
                                          block_y,block_z);
  blocEau_log = new G4LogicalVolume(blocEau_box,
                                             Eau,"blocEau_log",0,0,0);
  G4double blockPos_x = 1.0*m;
  G4double blockPos_y = 0.0*m;
  G4double blockPos_z = 0.0*m;

  blocEau_phys = new G4PVPlacement(0,
             G4ThreeVector(blockPos_x,blockPos_y,blockPos_z),
             blocEau_log,"blocEau",aireExperimentale_log,false,0);

 G4Box *layerS 
    = new G4Box("LayerS",           // its name
                 block_x/10, block_y,block_z); // its size
                         
  G4LogicalVolume *layerLV
    = new G4LogicalVolume(
                 layerS,           // its solid
                  Eau,  // its material
                 "LayerLV");         // its name



  new G4PVReplica(
                 "LayerLP",          // its name
                 layerLV,          // its logical volume
                blocEau_log,          // its mother
                 kXAxis,           // axis of replication
                 1000,        // number of replica
                 2.0*m/1000.0);  // witdth of replica 


  return aireExperimentale_phys;
}
