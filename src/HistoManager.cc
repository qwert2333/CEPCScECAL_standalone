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
//
// $Id: HistoManager.cc 72249 2013-07-12 08:57:49Z gcosmo $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 

#include "HistoManager.hh"
#include "G4UnitsTable.hh"
#include <TTree.h>
#include <TFile.h>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::HistoManager(char *foutname)
  : fFileName("CEPCScECAL"),fRootFile(0),fNtuple(0)
{
	fOutName = foutname;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::~HistoManager()
{
  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::book()
{
  G4cout<<"------>create rootfile"<<G4endl;
  fRootFile = new TFile(fOutName.c_str(),"RECREATE");
  fNtuple = new TTree("T","data of ScECAL");
  fNtuple->Branch("PrimaryPDG",                 &fParticleInfo.fPrimaryPDG);
  fNtuple->Branch("PrimaryEnergy",                 &fParticleInfo.fPrimaryEnergy);
  fNtuple->Branch("PrimaryDirection",                 &fParticleInfo.fPrimaryDirection);
  fNtuple->Branch("PrimaryPosition",                 &fParticleInfo.fPrimaryPosition);
  fNtuple->Branch("CrystalID",                 &fParticleInfo.fCrystalID);
  fNtuple->Branch("EnergyDep",              &fParticleInfo.fEnergyDep);
  fNtuple->Branch("AbsorberID",            &fParticleInfo.fAbsorberID);
  fNtuple->Branch("AbsorberEnDep",            &fParticleInfo.fAbsorberEnDep);
  fNtuple->Branch("PCBID",            &fParticleInfo.fPCBID);
  fNtuple->Branch("PCBEnDep",            &fParticleInfo.fPCBEnDep);
}

void HistoManager::save()
{
  fNtuple->Write("",TObject::kOverwrite);
  fRootFile->Close();
  G4cout<<"------>close rootfile"<<G4endl;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
