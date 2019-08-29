//
// Particle counter class definition
//

#ifndef ParticleCounterManager_hh
#define ParticleCounterManager_hh

#include <map>
#include <set>
#include "CSAnalysis.hh"

#include "G4Step.hh"

using namespace std;

class ParticleCounterManager
{
  typedef set<G4int> trackIdSet ;
  typedef map<G4int, trackIdSet> mapOfTrackIdSets ;
  typedef map<G4int, mapOfTrackIdSets> mapOfBins ;

private:
  static ParticleCounterManager *manager;
  map<G4int,G4int> idHcount;
  
  G4AnalysisManager  * analysisManager;  
  mapOfBins eventCounter;

protected:
  ParticleCounterManager (void);

public:
  static  ParticleCounterManager *GetManager (void);
  ~ParticleCounterManager (void);
  
  virtual void BeginOfEvent(void);
  virtual void FillEventCounter (const G4Step *aStep);
  virtual void EndOfEvent(void);
    
};
#endif
