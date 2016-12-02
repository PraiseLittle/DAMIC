#include "G4RunManager.hh"

#include "G4UImanager.hh"
#include "Randomize.hh"
#include "QBBC.hh"

#include "DAMICDetectorConstruction.hh"
/*#include "DAMICPhysicsListForTests.hh"*/
#include "DAMICActionInitialization.hh"


#ifdef G4VIS_USE
 #include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif


int main(int argc,char** argv) {

  G4RunManager* runManager = new G4RunManager;


  DAMICDetectorConstruction* det= new DAMICDetectorConstruction;
  runManager->SetUserInitialization(det);

  G4VModularPhysicsList* physicsList = new QBBC;
  physicsList->SetVerboseLevel(1);
  runManager->SetUserInitialization(physicsList);

  /*DAMICPhysicsListForTests* phys = new DAMICPhysicsListForTests;
  runManager->SetUserInitialization(phys);*/

  runManager->SetUserInitialization(new DAMICActionInitialization(det));

  // get the pointer to the User Interface manager
    G4UImanager* UI = G4UImanager::GetUIpointer();

  if (argc!=1)   // batch mode
    {
     G4String command = "/control/execute ";
     G4String fileName = argv[1];
     UI->ApplyCommand(command+fileName);
    }

  else           //define visualization and UI terminal for interactive mode
    {
#ifdef G4VIS_USE
      G4VisManager* visManager = new G4VisExecutive;
      visManager->Initialize();
#endif

#ifdef G4UI_USE
      G4UIExecutive * ui = new G4UIExecutive(argc,argv);
      ui->SessionStart();
      delete ui;
#endif

#ifdef G4VIS_USE
     delete visManager;
#endif
  }
  delete runManager;

  return 0;
}
