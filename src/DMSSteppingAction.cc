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
/// \file DMSSteppingAction.cc
/// \brief Implementation of the DMSSteppingAction class

#include "DMSSteppingAction.hh"
#include "DMSEventAction.hh"
#include "DMSDetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4ParticleTypes.hh"
#include "g4root.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DMSSteppingAction::DMSSteppingAction()
: G4UserSteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DMSSteppingAction::~DMSSteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DMSSteppingAction::UserSteppingAction(const G4Step* step)
{
  auto analysisManager = G4AnalysisManager::Instance();

  // Record all photons and neutrons kinematic information.
  const std::vector<const G4Track*>* secondaries = step->GetSecondaryInCurrentStep();

  for( size_t lp = 0; lp < (*secondaries).size(); ++lp )
  {
    // Process Name
    analysisManager->FillNtupleSColumn(0, (*secondaries)[lp]->GetCreatorProcess()->GetProcessName());
    // Name of daughter particle
    analysisManager->FillNtupleSColumn(1, (*secondaries)[lp]->GetDefinition()->GetParticleName());
    // Name of mother particle
    analysisManager->FillNtupleSColumn(2, step->GetTrack()->GetParticleDefinition()->GetParticleName());
    // Name of volume where particle produced
    analysisManager->FillNtupleSColumn(3, step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume()->GetName());
    // Energy of daughter particle
    analysisManager->FillNtupleDColumn(4, (G4double)(*secondaries)[lp]->GetKineticEnergy()/CLHEP::MeV);
    // Position of particle production
    analysisManager->FillNtupleDColumn(5, (G4double)(*secondaries)[lp]->GetPosition().getX()/CLHEP::cm);
    analysisManager->FillNtupleDColumn(6, (G4double)(*secondaries)[lp]->GetPosition().getY()/CLHEP::cm);
    analysisManager->FillNtupleDColumn(7, (G4double)(*secondaries)[lp]->GetPosition().getZ()/CLHEP::cm);
    // Time of particle production
    analysisManager->FillNtupleDColumn(8, (G4double)(*secondaries)[lp]->GetGlobalTime()/CLHEP::ns);
    analysisManager->FillNtupleDColumn(9, (G4double)(*secondaries)[lp]->GetLocalTime()/CLHEP::ns);
    // Momentum of daughter particle
    analysisManager->FillNtupleDColumn(10, (G4double)(*secondaries)[lp]->GetMomentum().getX()/CLHEP::MeV);
    analysisManager->FillNtupleDColumn(11, (G4double)(*secondaries)[lp]->GetMomentum().getY()/CLHEP::MeV);
    analysisManager->FillNtupleDColumn(12, (G4double)(*secondaries)[lp]->GetMomentum().getZ()/CLHEP::MeV);
    // Momentum direction vectors
    analysisManager->FillNtupleDColumn(13, (G4double)(*secondaries)[lp]->GetMomentumDirection().getX());
    analysisManager->FillNtupleDColumn(14, (G4double)(*secondaries)[lp]->GetMomentumDirection().getY());
    analysisManager->FillNtupleDColumn(15, (G4double)(*secondaries)[lp]->GetMomentumDirection().getZ());

    analysisManager->AddNtupleRow();
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

