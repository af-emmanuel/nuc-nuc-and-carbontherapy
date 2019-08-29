//
// Particle counter class definition
//

#include "ParticleCounterManager.hh"
#include "G4ParticleDefinition.hh"
#include "G4ThreeVector.hh"

#include "G4UnitsTable.hh"
 
#include "CSAnalysis.hh"

using namespace CLHEP;
 
ParticleCounterManager *ParticleCounterManager::manager=0;
  
//___________________________________________________________
ParticleCounterManager::ParticleCounterManager (void)
{
manager=this;
eventCounter.clear();

analysisManager = G4AnalysisManager::Instance(); //instantiating g4analysis

idHcount[1]= analysisManager->GetH1Id("H");
idHcount[2] = analysisManager->GetH1Id("He");
idHcount[3] = analysisManager->GetH1Id("Li");
idHcount[4] = analysisManager->GetH1Id("Be");
idHcount[5] = analysisManager->GetH1Id("B");
idHcount[6] = analysisManager->GetH1Id("C");
idHcount[7] = analysisManager->GetH1Id("N");
idHcount[8] = analysisManager->GetH1Id("O");
idHcount[9] = analysisManager->GetH1Id("F");
idHcount[10] = analysisManager->GetH1Id("Ne");

for (G4int iz=1;iz<=10;iz++)
 {
 G4cout << "Count histogram ID for Z=" << iz << " : " << idHcount[iz] << G4endl;
 }
}

//___________________________________________________________
ParticleCounterManager *ParticleCounterManager::GetManager (void)
{
if(!manager)
 {
 manager=new ParticleCounterManager ();
 }
return manager;
}

//___________________________________________________________
ParticleCounterManager::~ParticleCounterManager (void)
{
}
  
  
  
//___________________________________________________________
void ParticleCounterManager::BeginOfEvent(void)
{
// clear sets of trackIds
//G4cout << "ParticleCounterManager::BeginOfEvent() called" << G4endl;
for (mapOfBins::iterator itBin=eventCounter.begin();
                         itBin !=eventCounter.end();
                         itBin++)
 {
 mapOfTrackIdSets  &trackIds=itBin->second;
 for (mapOfTrackIdSets::iterator itTS=trackIds.begin();
                                 itTS!=trackIds.end();
                                 itTS++)
  {
  itTS->second.clear();
  }
 trackIds.clear();
 }
}

//___________________________________________________________
void ParticleCounterManager::FillEventCounter (const G4Step *aStep)
{
//G4cout << "ParticleCounterManager::FillEventCounter(aStep) called" << G4endl;
const G4Track* track = aStep->GetTrack();
G4int trackId = track->GetTrackID();
G4ParticleDefinition* particle = track->GetDefinition();
G4int Z = particle->GetAtomicNumber();
G4ThreeVector xprestep= aStep->GetPreStepPoint()->GetPosition();
G4ThreeVector xpoststep= aStep->GetPostStepPoint()->GetPosition();
G4double location = xprestep.x()/(0.2*cm);
G4int pre_slab_position = (G4int) location;
location = xpoststep.x()/(0.2*cm);
G4int post_slab_position  = (G4int) location;

G4int min_slab_number = min (pre_slab_position,post_slab_position);
G4int max_slab_number = max (pre_slab_position,post_slab_position);
if (Z>0)
 {
 for (G4int slab_position= min_slab_number;  slab_position<= max_slab_number;slab_position++)
  {
  mapOfTrackIdSets &trackIds = eventCounter[slab_position];
  trackIdSet &trackIdsZ = trackIds [Z];
  trackIdsZ.insert (trackId);
  }
 }
//G4cout << "after insert : " << Z << " / " << trackIdsZ.size() << G4endl;
}

//___________________________________________________________
void ParticleCounterManager::EndOfEvent(void)
{
//G4cout << "ParticleCounterManager::EndOfEvent() called" << G4endl;
analysisManager = G4AnalysisManager::Instance();
for (mapOfBins::iterator itBin=eventCounter.begin();
                         itBin !=eventCounter.end();
                         itBin++)
 {
 G4int slabNumber = itBin->first;
 mapOfTrackIdSets  &trackIds=itBin->second;
 for (mapOfTrackIdSets::iterator itTS=trackIds.begin();
                                 itTS!=trackIds.end();
                                 itTS++)
  {
  G4int Z = itTS->first;
  G4int nPart = itTS->second.size();
  // Retrieve the histogram counter corresponding to the Z value
  // Add nPart to the bin corresponding to slabNumber  
  //G4cout << slabNumber << " has " << nPart << " particles of charge " << Z << G4endl;
  
      
//************************************************************************//fillhistograms for particle weights
    analysisManager->FillH1(idHcount[Z],slabNumber*2*mm,nPart);
     
  }
 }
}


