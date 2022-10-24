//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \brief Implementation of the EventAction class
//
// $Id: EventAction.cc 68030 2015-03-13 13:51:27Z gcosmo $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "EventAction.hh"
//#include "EventMessenger.hh"

#include "G4Event.hh"
#include <iomanip>
#include <HistoManager.hh>
#include <TTree.h>
#include "RunAction.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction(HistoManager* histo)
:G4UserEventAction(),
 fEventEdep(0),fPrintModulo(10000),fDecayChain(),fHistoManager_Event(histo)
{
  fGParticleSource  = new G4GeneralParticleSource();
  //fHistoManager_Event = new HistoManager();
  //fEventMessenger = new EventMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{
  delete fGParticleSource;
  //delete fHistoManager_Event;
  //delete fEventMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event*)
{
    fStepTag=0;
//  G4cout <<
//  		"..................6666666666666........................"
//  		<< G4endl;
  fDecayChain = " ";
//  fHistoManager_Event->fParticleInfo.reset();
// G4cout<<"begin of event"<<G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* evt)
{
  //  G4cout<<" >>>>>>>>>>>>>>>>> "<< fHistoManager_Event ->fParticleInfo.fPrimaryEnergy <<" <<<<<<<<<<<<<<<"<<G4endl;
//  G4cout <<
//  		"..................777777777777777........................"
//  		<< G4endl;
 G4int evtNb = evt->GetEventID(); 
 //printing survey
 //
 if (evtNb%1000 == 0) 
   G4cout << "\n end of event " << std::setw(6) << evtNb 
          << " :" + fDecayChain << G4endl;
// G4cout<<"end of event "<<fHistoManager_Event->fParticleInfo.nTrack<<" "<<fHistoManager_Event->fParticleInfo.fTrackTime[0]<<G4endl;
 
 //
 
 //
 
 fHistoManager_Event->fNtuple->Fill();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void EventAction::SetEnergy(G4double ke)
{

  fHistoManager_Event->fParticleInfo.fPrimaryEnergy = ke;
//    G4cout<<" >>>>>>>>>>>>>>>>> "<<fHistoManager_Event->fParticleInfo.fPrimaryEnergy <<" <<<<<<<<<<<<<<<"<<G4endl;
}


