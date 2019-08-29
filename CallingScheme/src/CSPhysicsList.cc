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
// $Id: CSPhysicsList.cc,v 1.5 2002/01/09 17:23:48 ranjard Exp $
// GEANT4 tag $Name: geant4-08-00 $
//
// 

#include "CSPhysicsList.hh"
#include "G4ParticleTypes.hh"
#include "G4IonConstructor.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4ProcessManager.hh"

using namespace CLHEP;

CSPhysicsList::CSPhysicsList():G4VUserPhysicsList()
{
//
// Valeur de Cut sur le parcours
//
defaultCutValue = 0.0002*mm;
}

CSPhysicsList::~CSPhysicsList()
{;}

void CSPhysicsList::ConstructParticle()
{
  // In this method, static member functions should be called
  // for all particles which you want to use.
  // This ensures that objects of these particle types will be
  // created in the program. 

  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
  G4Gamma::GammaDefinition();
  G4Proton::ProtonDefinition();
  G4AntiProton::AntiProtonDefinition();
  G4Neutron::NeutronDefinition();
  G4AntiNeutron::AntiNeutronDefinition();
 
  G4KaonPlus::KaonPlusDefinition();
  G4KaonMinus::KaonMinusDefinition();
  G4KaonZero::KaonZeroDefinition();
  G4AntiKaonZero::AntiKaonZeroDefinition();
  G4KaonZeroLong::KaonZeroLongDefinition();
  G4KaonZeroShort::KaonZeroShortDefinition();

  G4IonConstructor pConstructor;
  pConstructor.ConstructParticle();  
   
  G4String name;
  
  G4ParticleTable *parTab=G4ParticleTable::GetParticleTable();
  parTab->FindParticle(name = "C12");
}

void CSPhysicsList::ConstructProcess()
{
  // Define transportation process

  AddTransportation();
  
  // Define ElectroMagnetic Processes
  ConstructEM();
  
  // Define Decay Processes
  ConstructGeneral();

  // Define Nuclear processes
  //ConstructNuclearReactions();
}

void CSPhysicsList::SetCuts()
{
  // uppress error messages even in case e/gamma/proton do not exist            
  G4int temp = GetVerboseLevel();                                                SetVerboseLevel(0);                                                           
  //  " G4VUserPhysicsList::SetCutsWithDefault" method sets 
  //   the default cut value for all particle types 
  SetCutsWithDefault();   

  // Retrieve verbose level
  SetVerboseLevel(temp);  
}

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"

#include "G4eMultipleScattering.hh"
#include "G4MuMultipleScattering.hh"
#include "G4hMultipleScattering.hh"

#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"

#include "G4hIonisation.hh"

#include "G4ionIonisation.hh"

#include "G4StepLimiter.hh"
#include "G4UserSpecialCuts.hh"

#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CSPhysicsList::ConstructEM()
{
  G4ParticleTable::G4PTblDicIterator* theParticleIterator = GetParticleIterator();	  
  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();
     
    if (particleName == "gamma") {
      // gamma         
      G4cout << "Adding processes for gamma. " << G4endl;
      pmanager->AddDiscreteProcess(new G4PhotoElectricEffect);
      pmanager->AddDiscreteProcess(new G4ComptonScattering);
      pmanager->AddDiscreteProcess(new G4GammaConversion);
      
    } else if (particleName == "e-") {
      //electron
      G4cout << "Adding processes for e-. " << G4endl;
      pmanager->AddProcess(new G4eMultipleScattering,-1, 1,1);
      pmanager->AddProcess(new G4eIonisation,       -1, 2,2);
      pmanager->AddProcess(new G4eBremsstrahlung,   -1, 3,3);      

    } else if (particleName == "e+") {
      //positron
      G4cout << "Adding processes for e+. " << G4endl;
      pmanager->AddProcess(new G4eMultipleScattering,-1, 1,1);
      pmanager->AddProcess(new G4eIonisation,       -1, 2,2);
      pmanager->AddProcess(new G4eBremsstrahlung,   -1, 3,3);
      pmanager->AddProcess(new G4eplusAnnihilation,  0,-1,4);

    } else if( particleName == "mu+" || 
               particleName == "mu-"    ) {
      //muon  
      G4cout << "Adding processes for muons. " << G4endl;
      pmanager->AddProcess(new G4MuMultipleScattering,-1, 1,1);
      pmanager->AddProcess(new G4MuIonisation,      -1, 2,2);
      pmanager->AddProcess(new G4MuBremsstrahlung,  -1, 3,3);
      pmanager->AddProcess(new G4MuPairProduction,  -1, 4,4);       
     
    } else if( particleName == "GenericIon" ) {
      //muon  
      G4cout << "Adding processes for " << particleName << ". " << G4endl;
      pmanager->AddProcess(new G4hMultipleScattering,-1, 1,1);
      pmanager->AddProcess(new G4ionIonisation,     -1, 2,2);
      pmanager->AddProcess(new G4StepLimiter,       -1,-1,3);         
     
    } else if ((!particle->IsShortLived()) &&
	       (particle->GetPDGCharge() != 0.0) && 
	       (particle->GetParticleName() != "chargedgeantino")) {
      //all others charged particles except geantino
      G4cout << "Adding processes for " <<particleName << ". " << G4endl;
      pmanager->AddProcess(new G4hMultipleScattering,-1, 1,1);
      pmanager->AddProcess(new G4hIonisation,       -1, 2,2);
      //step limit
      pmanager->AddProcess(new G4StepLimiter,       -1,-1,3);         
      ///pmanager->AddProcess(new G4UserSpecialCuts,   -1,-1,4);  
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4Decay.hh"
void CSPhysicsList::ConstructGeneral()
{
  // Add Decay Process
  G4ParticleTable::G4PTblDicIterator* theParticleIterator = GetParticleIterator();	  
  G4Decay* theDecayProcess = new G4Decay();
  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    if (theDecayProcess->IsApplicable(*particle)) { 
      pmanager ->AddProcess(theDecayProcess);
      // set ordering for PostStepDoIt and AtRestDoIt
      pmanager ->SetProcessOrdering(theDecayProcess, idxPostStep);
      pmanager ->SetProcessOrdering(theDecayProcess, idxAtRest);
    }
  }
}

#include "G4TheoFSGenerator.hh"
#include "G4Evaporation.hh"
#include "G4FermiBreakUpVI.hh"
#include "G4StatMF.hh"
#include "G4ExcitationHandler.hh"
#include "G4PreCompoundModel.hh"
#include "G4GeneratorPrecompoundInterface.hh"
#include "G4HadronElastic.hh"
#include "G4HadronElasticProcess.hh"
#include "G4BinaryLightIonReaction.hh"
#include "G4TripathiCrossSection.hh"
#include "G4IonsShenCrossSection.hh"
#include "G4IonInelasticProcess.hh"
 
void CSPhysicsList::ConstructNuclearReactions()
{
   
  G4ProcessManager * pManager = 0;
  
  // this will be the model class for high energies
  G4TheoFSGenerator * theTheoModel = new G4TheoFSGenerator;
  // all models for treatment of thermal nucleus 
  G4cout << "Modeles nucleaires thermiques " << G4endl; 
  G4Evaporation * theEvaporation = new G4Evaporation;
  G4VFermiBreakUp * theFermiBreakUp = new G4FermiBreakUpVI;
  G4StatMF * theMF = new G4StatMF;
  // Evaporation logic
  G4cout << "Description desexcitation " << G4endl; 
  G4ExcitationHandler * theHandler = new G4ExcitationHandler;
  theHandler->SetEvaporation(theEvaporation);
  theHandler->SetFermiModel(theFermiBreakUp);
  theHandler->SetMultiFragmentation(theMF);
  theHandler->SetMaxAandZForFermiBreakUp(12, 6);
  theHandler->SetMinEForMultiFrag(5*MeV);  
  // Pre equilibrium stage 
  G4cout << "Pre-equilibre" << G4endl; 
  G4PreCompoundModel * thePreEquilib = new G4PreCompoundModel(theHandler);

  // a no-cascade generator-precompound interaface
  G4GeneratorPrecompoundInterface * theCascade = new G4GeneratorPrecompoundInterface;
  theCascade->SetDeExcitation(thePreEquilib);  
	
  // Elastic Process
  
  G4cout << "Diff elastique" << G4endl; 
  G4HadronElasticProcess *elastProc=new G4HadronElasticProcess();
  elastProc->RegisterMe(new G4HadronElastic());

  // ---------------------------------------------------------------------------
  // Hadron elastic process
  // for all particles except neutrons

  G4ParticleTable::G4PTblDicIterator* theParticleIterator = GetParticleIterator();	  
  theParticleIterator->reset();
  while( (*theParticleIterator)() ) {
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4String particleName = particle->GetParticleName();
    if (particleName != "neutron") {  
      pManager = particle->GetProcessManager();
      if (particle->GetPDGMass() > 110.*MeV && elastProc->IsApplicable(*particle)
	  && !particle->IsShortLived()) { 
	pManager->AddDiscreteProcess(elastProc);
	
	      G4cout << "### Elastic model are registered for " 
	       << particle->GetParticleName()
	       << G4endl;
      }
    }
  }

  G4cout << "coll binaires" << G4endl; 
  G4BinaryLightIonReaction * theIonBC= new G4BinaryLightIonReaction;
  theIonBC->SetMinEnergy(1*MeV);
  theIonBC->SetMaxEnergy(20*GeV);
  G4cout << "Tripathi" << G4endl; 
  G4TripathiCrossSection * TripathiCrossSection= new G4TripathiCrossSection;
  G4cout << "Shen" << G4endl; 
  G4IonsShenCrossSection * aShen = new G4IonsShenCrossSection;
  // GenericIon
  pManager = G4GenericIon::GenericIon()->GetProcessManager();
  // need to add the elastic explicitly
  G4cout << "Ajout Diff elastique pour ions" << G4endl; 
  pManager->AddDiscreteProcess(elastProc);
  G4cout << "Ajout Diff inelastique pour ions" << G4endl; 
  G4IonInelasticProcess *theIonInelasticProcess = 
    new G4IonInelasticProcess();
  theIonInelasticProcess->AddDataSet(TripathiCrossSection);
  theIonInelasticProcess->AddDataSet(aShen);
  //  G4BinaryLightIonReaction * theGenIonBC= new G4BinaryLightIonReaction;
  // theGenIonBC->SetMinEnergy(0*MeV);
  //theGenIonBC->SetMaxEnergy(20*GeV);
  theIonInelasticProcess->RegisterMe(theIonBC);
  theIonInelasticProcess->RegisterMe(theTheoModel);
  pManager->AddDiscreteProcess(theIonInelasticProcess);
 
}
