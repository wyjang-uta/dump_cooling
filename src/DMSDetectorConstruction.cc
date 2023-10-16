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
/// \file DMSDetectorConstruction.cc
/// \brief Implementation of the DMSDetectorConstruction class
#include <iostream>

#include "DMSDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4SubtractionSolid.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DMSDetectorConstruction::DMSDetectorConstruction()
: G4VUserDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DMSDetectorConstruction::~DMSDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DMSDetectorConstruction::Construct()
{
  G4cout << "Initialize G4NistManager" << G4endl;
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  const G4int nlayers = 6;

  std::cout << "Building Materials ... " << std::endl;
  G4Material* dump_layer_material[nlayers];
  dump_layer_material[0] = nist->FindOrBuildMaterial("G4_GRAPHITE");
  dump_layer_material[1] = nist->FindOrBuildMaterial("G4_Cu");
  dump_layer_material[2] = nist->FindOrBuildMaterial("G4_Fe");
  dump_layer_material[3] = nist->FindOrBuildMaterial("G4_Cu");
  dump_layer_material[4] = nist->FindOrBuildMaterial("G4_Fe");
  dump_layer_material[5] = nist->FindOrBuildMaterial("G4_CONCRETE");
  std::cout << "DONE." << std::endl;

  G4Colour brown(0.7, 0.4, 0.1);
  G4Colour red(1.0, 0.0, 0.0);
  G4Colour black(0.0, 0.0, 0.0);
  G4Colour grey(0.5, 0.5, 0.5);
  G4VisAttributes* copperVisAttributes   = new G4VisAttributes(brown);
  G4VisAttributes* ironVisAttributes     = new G4VisAttributes(red);
  G4VisAttributes* carbonVisAttributes   = new G4VisAttributes(black);
  G4VisAttributes* concreteVisAttributes = new G4VisAttributes(grey);


  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //
  // World
  //
  G4double world_sizeXY = 5.0*m;
  G4double world_sizeZ  = 8.0*m;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");

  G4Box* solidWorld =
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size

  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking


  G4Box* box1 = new G4Box("box1", 10.*cm, 10.*cm, 5.*cm);
  G4Box* box2 = new G4Box("box2", 40.*cm, 40.*cm, 20.*cm);
  G4Box* box3 = new G4Box("box3", 70.*cm, 70.*cm, 35.*cm);
  G4Box* box4 = new G4Box("box4", 80.*cm, 80.*cm, 40.*cm);
  G4Box* box5 = new G4Box("box5", 100.*cm, 100.*cm, 50.*cm);
  G4Box* box6 = new G4Box("box6", 120.*cm, 120.*cm, 60.*cm);

  G4ThreeVector zTrans1(0., 0., 5.*cm);
  G4ThreeVector zTrans2(0., 0., -20.*cm);
  G4ThreeVector zTrans3(0., 0., -35.*cm);
  G4ThreeVector zTrans4(0., 0., -40.*cm);
  G4ThreeVector zTrans5(0., 0., -50.*cm);
  G4ThreeVector zTrans6(0., 0., -60.*cm);

  G4SubtractionSolid* subsolid2 = new G4SubtractionSolid("layer2", box2, box1, 0, zTrans2);
  G4SubtractionSolid* subsolid3 = new G4SubtractionSolid("layer3", box3, box2, 0, zTrans3);
  G4SubtractionSolid* subsolid4 = new G4SubtractionSolid("layer4", box4, box3, 0, zTrans4);
  G4SubtractionSolid* subsolid5 = new G4SubtractionSolid("layer5", box5, box4, 0, zTrans5);
  G4SubtractionSolid* subsolid6 = new G4SubtractionSolid("layer6", box6, box5, 0, zTrans6);

  G4LogicalVolume* l_layer1 = new G4LogicalVolume(box1, dump_layer_material[0], "layer1");
  G4LogicalVolume* l_layer2 = new G4LogicalVolume(subsolid2, dump_layer_material[1], "layer2");
  G4LogicalVolume* l_layer3 = new G4LogicalVolume(subsolid3, dump_layer_material[2], "layer3");
  G4LogicalVolume* l_layer4 = new G4LogicalVolume(subsolid4, dump_layer_material[3], "layer4");
  G4LogicalVolume* l_layer5 = new G4LogicalVolume(subsolid5, dump_layer_material[4], "layer5");
  G4LogicalVolume* l_layer6 = new G4LogicalVolume(subsolid6, dump_layer_material[5], "layer6");

  l_layer1->SetVisAttributes(carbonVisAttributes);
  l_layer2->SetVisAttributes(copperVisAttributes);
  l_layer3->SetVisAttributes(ironVisAttributes);
  l_layer4->SetVisAttributes(copperVisAttributes);
  l_layer5->SetVisAttributes(ironVisAttributes);
  l_layer6->SetVisAttributes(concreteVisAttributes);

  // physical volume placement
  new G4PVPlacement(0, zTrans1, l_layer1, "layer1", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector(0, 0, 20.*cm), l_layer2, "layer2", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector(0, 0, 35.*cm), l_layer3, "layer3", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector(0, 0, 40.*cm), l_layer4, "layer4", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector(0, 0, 50.*cm), l_layer5, "layer5", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector(0, 0, 60.*cm), l_layer6, "layer6", logicWorld, false, 0, checkOverlaps);


  //
  // Dump
  //
  // Geometry description by Jeffrey
  //  Wooyoung,

  // I revisiting the dump concept after receiving feedback from the last meeting. I am still not completely confident in the radiological and thermal aspects, but I think this is the best I can do without simulating anything and under the constraint of 1.2m length.

  //Section 1 is 70cm long
  //- graphite carbon +/- 10cm wide (i.e. 20cm wide centered)
  //- surrounded by copper out to +/- 40 cm (i.e. from 10-40cm on either side).
  //- surrounded by steel (or iron) out to +/- 60cm (i.e. from 40-60cm on either side).
  //Section 2 is 30cm long (i.e. 70-100cm longitudinally)
  //- copper, +/- 10cm (i.e. 80cm wide centered, no graphite).
  //- surrounded by steel (or iron) out to +/- 20cm (i.e. from 40-60cm on either side).
  //Section 3 is 20cm long (i.e. 100-120cm longitudinally)
  //- borated concete (25% boron carbide B4C, 75% calcite CaCO3) +/- 60 cm (i.e. 120cm centered, no graphite or copper).

  //Let me know if you have any questions, I can draw a picture if it is unclear. If you can't model the borated concrete, you can try just concrete.

  //Here is the reasoning behind the concept. Proton beams should stop in 0.7m of graphite and 0.15m of copper with similar efficacy of 1m of graphite and 0.9m of aluminum. Not sure how hot the copper will get in this case since it is stopping protons in a shorter distance. However I leave some additional copper to provide some cooling. The 0.4m is essentially to provide some modest neutron shielding, at least 0.2m is necessary to shield the radiation activated copper (including Cu-61, Mn-52, C-11) while avoiding activation itself. The copper will generate more isotopes and spallation then alumnium, but I was able to avoid tungsten.

  //Best,
  //Jeff

  // Build from outermost one and create innermost one last.

  /*

  G4String dump_box_name[nlayers] = {
    "dump_box_1",
    "dump_box_2",
    "dump_box_3",
    "dump_box_4",
    "dump_box_5",
    "dump_box_6"
  };
  G4String dump_layer_name[nlayers] = {
    "dump_layer_1",
    "dump_layer_2",
    "dump_layer_3",
    "dump_layer_4",
    "dump_layer_5",
    "dump_layer_6"
  };
  G4String l_dump_layer_name[nlayers] = {
    "l_dump_layer_1",
    "l_dump_layer_2",
    "l_dump_layer_3",
    "l_dump_layer_4",
    "l_dump_layer_5",
    "l_dump_layer_6"
  };
  G4double dump_layer_partitions_z[nlayers]  = {
    10.0 * m,
    40.0 * m,
    70.0 * m,
    80.0 * m,
    100.0 * m,
    120.0 * m
  };


  G4Box* dump_box[6];

  for(G4int i = 0; i < 6; ++i)
  { dump_box[i] = new G4Box(dump_box_name[i],
      dump_layer_partitions_z[i],
      dump_layer_partitions_z[i],
      dump_layer_partitions_z[i]
      );   // square box
  std::cout << "Box " << i << " created." << std::endl;
  }

  G4SubtractionSolid* dump_layer[6];
  for( G4int i = 6; i > 1; --i )
  {
    std::cout << "intersection: " << i << " and " << i-1 << std::endl;
    dump_layer[i] = new G4SubtractionSolid(dump_layer_name[i], dump_box[i], dump_box[i-1]);
  }

  G4LogicalVolume* l_dump_layer[6];
  for( G4int i = 0; i < 6; i++ )
  {
    if( i == 0 )
    {
      l_dump_layer[0] = new G4LogicalVolume(
        dump_box[0],
        dump_layer_material[0],
        l_dump_layer_name[0]
        );
    }
    else
    {
      l_dump_layer[i] = new G4LogicalVolume(
          dump_layer[i],
          dump_layer_material[i],
          l_dump_layer_name[i]
        );
    }

    // physical volume placement
    new G4PVPlacement(0,
        G4ThreeVector(),
        l_dump_layer[i],
        dump_layer_name[i],
        logicWorld,
        false,
        0,
        checkOverlaps);
  }
  */




  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
