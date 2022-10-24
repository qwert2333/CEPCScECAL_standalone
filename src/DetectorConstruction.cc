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
/// \file radioactivedecay/rdecay01/src/DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class
//
//
// $Id: DetectorConstruction.cc 78307 2013-12-11 10:55:57Z gcosmo $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DetectorConstruction.hh"

#include "SteppingAction.hh"

#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Orb.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4GlobalMagFieldMessenger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
 : G4VUserDetectorConstruction()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    //
    // define a material
    //   
    //  G4Material* Air =
    //  G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR"); 

    // vacuum  
    G4Material* Vacuum =
        G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");

    G4Material* PSD =
        G4NistManager::Instance()->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE"); 

    G4Material* Aluminum =
        G4NistManager::Instance()->FindOrBuildMaterial("G4_Al"); 


    G4Material* tungsten =
        G4NistManager::Instance()->FindOrBuildMaterial("G4_W");

     G4Element* elW = 
        G4NistManager::Instance()->FindOrBuildElement("W");

    G4Element* elCu = 
        G4NistManager::Instance()->FindOrBuildElement("Cu");

     G4double density;
     G4String name;
     G4int ncomponents;
     G4double fractionmass;
  //   density = 14.98*g/cm3; // for 25Cu:75W
     density = 16.45*g/cm3; // for 15Cu:85W
     G4Material* CuW = new G4Material(name="CuW", density, ncomponents=2);
     CuW->AddElement(elCu,fractionmass=0.15);
     CuW->AddElement(elW,fractionmass=0.85);
 
    //     
    // World
    //

    //******************************************************
    // Option to switch checking of volumes Overlaps

    G4bool checkOverlaps = true;

    // Full sphere shape
    G4double solidWorld_rmax = 100*cm;
    G4Orb*
        solidWorld = new G4Orb("World",                          // its name
                solidWorld_rmax);                // its size 

    G4LogicalVolume*                         
        logicWorld = new G4LogicalVolume(solidWorld,             //its solid
                Vacuum,                    //its material
                "World");               //its name
    G4VPhysicalVolume*                                   
        physiWorld = new G4PVPlacement(0,                      //no rotation
                G4ThreeVector(),        //at (0,0,0)
                logicWorld,             //its logical volume
                "World",                //its name
                0,                      //its mother  volume
                false,                  //no boolean operation
                0,
                checkOverlaps);                     //copy number

    // crystal shape 
    //  material  CdMoO4

    //******************************************************
    //Absorber & Crystal & PCB
    G4int LayerNo = 30;
    G4int crystalNoX = 42;
    G4int crystalNoY = 5;
    G4double crystalX = 5*mm;
    G4double crystalY = 45*mm;
    G4double crystalZ = 2*mm;
    G4double absorberXY = 230*mm;
    G4double absorberZ = 2.8*mm;
    G4double PCBXY = absorberXY;
    G4double PCBZ = 2*mm;
    G4double crystalGapX = 0.;
    G4double crystalGapY = 0.;
    G4double absorber_crystalGap = 0*mm;
    G4double crystal_pcbGap = 0*mm;
    G4double pcb_absorberGap = 0*mm;
//    G4double absorber_crystalGap = 0*mm;
//    G4double crystal_pcbGap = 0*mm;
//    G4double pcb_absorberGap = 0*mm;

    G4double absorberPositionXY = 0*mm;
    G4double absorberPositionZ1 = (crystalZ + PCBZ + absorberZ/2.);
    G4double absorberPositionZ2 = (crystalZ + PCBZ + absorberZ + PCBZ + crystalZ + crystal_pcbGap + absorberZ/2.);
    G4double crystalPositionX = -(crystalNoX-1)*(crystalX+crystalGapX)/2.;
    G4double crystalPositionY = -(crystalNoY-1)*(crystalY+crystalGapY)/2.;
    G4double crystalPositionZ1 = (crystalZ/2.);
    G4double PCBPositionXY = absorberPositionXY;
    G4double PCBPositionZ1 = (crystalZ + PCBZ/2.);
    //G4double PCBPositionZ2 = (crystalZ + PCBZ + absorberZ + PCBZ/2.);
    //G4double crystalPositionZ2 = (crystalZ + PCBZ + absorberZ + crystal_pcbGap + PCBZ + crystalZ/2.);
    G4double PCBPositionZ2 = (crystalZ + PCBZ + absorberZ + crystal_pcbGap + crystalZ + PCBZ/2.);
    G4double crystalPositionZ2 = (crystalZ + PCBZ + absorberZ + crystal_pcbGap + crystalZ/2.);
    //G4double crystalPositionZ2 = (crystalZ/2. + crystal_pcbGap - absorber_crystalGap);
    //G4double PCBPositionZ2 = (PCBZ/2. + crystalZ + pcb_absorberGap - absorber_crystalGap);

    //G4double absorberGapZ = (absorberZ + crystalZ + PCBZ + absorber_crystalGap + crystal_pcbGap + pcb_absorberGap);
    G4double absorberGapZ = (absorberZ + crystalZ + PCBZ)*2 + absorber_crystalGap + crystal_pcbGap;
    G4double PCBGapZ = absorberGapZ;
    G4double crystalGapZ = absorberGapZ;

    //******************************************************
    //******************************************************
    //Absorber
    G4Box*
        solidAbsorber = new G4Box("Absorber",                                                  // its name
                0.5*absorberXY, 0.5*absorberXY, 0.5*absorberZ);        // its size

    G4LogicalVolume* 
        logicAbsorber = new G4LogicalVolume(solidAbsorber,                                       // its solid
                CuW,                                             // its material
                "Absorber");                                          // its name 

    for(G4int i_Layer=0; i_Layer!=LayerNo; ++i_Layer){
        if(i_Layer%2==0){
            new G4PVPlacement(0,                                                    // no rotation
                    G4ThreeVector(absorberPositionXY, absorberPositionXY, (absorberPositionZ1+(i_Layer/2)*absorberGapZ)),                              // at (0,0,0)
                    logicAbsorber,                                         // its logical volume
                    "Absorber",                                            // its name
                    logicWorld,                                           // its mother  volume
                    false,                                                // no boolean operation
                    i_Layer,
                    checkOverlaps);                                                   // copy number
        }
        if(i_Layer%2==1){
            new G4PVPlacement(0,                                                    // no rotation
                    G4ThreeVector(absorberPositionXY, absorberPositionXY, (absorberPositionZ2+(i_Layer/2)*absorberGapZ)),                              // at (0,0,0)
                    logicAbsorber,                                         // its logical volume
                    "Absorber",                                            // its name
                    logicWorld,                                           // its mother  volume
                    false,                                                // no boolean operation
                    i_Layer,
                    checkOverlaps);                                                   // copy number
        }
    }

    //******************************************************
    //LSO Crystal
    G4Box*  
        solidCrystal = new G4Box("Crystal",                                                  // its name
                0.5*crystalX, 0.5*crystalY, 0.5*crystalZ);        // its size


    G4LogicalVolume* 
        logicCrystal = new G4LogicalVolume(solidCrystal,                                       // its solid
                PSD,                                             // its material
                "Crystal");                                          // its name 

    // G4VPhysicalVolume* physiCrystal;
    for(G4int i_Layer=0; i_Layer!=LayerNo; ++i_Layer){
        G4RotationMatrix rm;
        rm.rotateZ(90*deg);
        if(i_Layer%2==0){
            for(G4int i_Lands=0; i_Lands!=crystalNoY; ++i_Lands){
                for(G4int i_Portrait=0; i_Portrait!=crystalNoX; ++i_Portrait){

                    new G4PVPlacement(0,                                                    // no rotation
                            G4ThreeVector((crystalPositionX+i_Portrait*(crystalX+crystalGapX)), (crystalPositionY+i_Lands*(crystalY+crystalGapY)), (crystalPositionZ1+i_Layer/2*crystalGapZ)),                                      // at ()
                            //G4Transform3D(rm, G4ThreeVector((crystalPositionY+i_Lands*(crystalY+crystalGapY)), (crystalPositionX+i_Portrait*(crystalX+crystalGapX)), (crystalPositionZ1+i_Layer/2*crystalGapZ))),                                      // at ()
                            logicCrystal,                                         // its logical volume
                            "Crystal",                                            // its name
                            logicWorld,                                           // its mother  volume
                            false,                                                // no boolean operation
                            i_Layer*crystalNoX*crystalNoY + i_Lands*crystalNoX + i_Portrait );                                                   // copy number
                }
            }
        }
        if(i_Layer%2==1){
            for(G4int i_Lands=0; i_Lands!=crystalNoY; ++i_Lands){
                for(G4int i_Portrait=0; i_Portrait!=crystalNoX; ++i_Portrait){

                    new G4PVPlacement(
                            //G4ThreeVector((crystalPositionX+i_Portrait*(crystalX+crystalGapX)), (crystalPositionY+i_Lands*(crystalY+crystalGapY)), (crystalPositionZ2+i_Layer/2*crystalGapZ)),                                      // at ()
                            G4Transform3D(rm, G4ThreeVector((crystalPositionY+i_Lands*(crystalY+crystalGapY)), (crystalPositionX+i_Portrait*(crystalX+crystalGapX)), (crystalPositionZ2+(i_Layer-1)/2.*crystalGapZ))),                                      // at ()
                            logicCrystal,                                         // its logical volume
                            "Crystal",                                            // its name
                            logicWorld,                                           // its mother  volume
                            false,                                                // no boolean operation
                            i_Layer*crystalNoX*crystalNoY + i_Lands*crystalNoX + i_Portrait );                                                   // copy number
                }
            }
        }
    }

    //******************************************************
    //PCB
    G4Material* kevlar =
        G4NistManager::Instance()->FindOrBuildMaterial("G4_KAPTON");

    G4Box*
        solidPCB = new G4Box("PCB",                                                  // its name
                0.5*PCBXY, 0.5*PCBXY, 0.5*PCBZ);        // its size

    G4LogicalVolume* 
        logicPCB = new G4LogicalVolume(solidPCB,                                       // its solid
                kevlar,                                             // its material//should be check.............
                "PCB");                                          // its name 

    //  G4VPhysicalVolume* physiPCB;
    for(G4int i_Layer=0; i_Layer!=LayerNo; ++i_Layer){
        if(i_Layer%2==0){
            new G4PVPlacement(0,                                                    // no rotation
                    G4ThreeVector(PCBPositionXY, PCBPositionXY, (PCBPositionZ1+i_Layer/2*PCBGapZ)),                                      // at (0,0,0)
                    logicPCB,                                         // its logical volume
                    "PCB",                                            // its name
                    logicWorld,                                           // its mother  volume
                    false,                                                // no boolean operation
                    i_Layer,
                    checkOverlaps);                                                   // copy number
        }
        if(i_Layer%2==1){
            new G4PVPlacement(0,                                                    // no rotation
                    G4ThreeVector(PCBPositionXY, PCBPositionXY, (PCBPositionZ2+i_Layer/2*PCBGapZ)),                                      // at (0,0,0)
                    logicPCB,                                         // its logical volume
                    "PCB",                                            // its name
                    logicWorld,                                           // its mother  volume
                    false,                                                // no boolean operation
                    i_Layer,
                    checkOverlaps);                                                   // copy number
        }
    }


    G4VisAttributes* visAttributes = new G4VisAttributes(G4Colour(0.9,0.0,0.0));
    //G4VisAttributes* chamberVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,0.0));
    visAttributes -> SetVisibility(false);
    logicWorld ->SetVisAttributes(visAttributes);
    logicAbsorber ->SetVisAttributes(visAttributes);
    logicPCB ->SetVisAttributes(visAttributes);

    visAttributes = new G4VisAttributes(G4Colour(0.9,0.0,0.0));//red
    logicAbsorber ->SetVisAttributes(visAttributes);
    //(0.9,0.9,0.0)yellow

    visAttributes = new G4VisAttributes(G4Colour(0.0,1.0,0.0));//green
    logicPCB ->SetVisAttributes(visAttributes);

    visAttributes = new G4VisAttributes(G4Colour(0.9,0.9,0.9));//white
    logicCrystal ->SetVisAttributes(visAttributes);


    // Set scoring volume to stepping action
    // (where we will account energy deposit)
    SteppingAction* steppingAction = SteppingAction::Instance();
    steppingAction->SetVolume(logicCrystal);

    //
    //always return the physical World
    //  
    return physiWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
