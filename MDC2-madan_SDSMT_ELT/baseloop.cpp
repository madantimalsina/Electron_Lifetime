#include "rqlib/RQ__Interaction.h"
#include "rqlib/RQ__DetectorPulses.h"
#include "rqlib/RQ__Pulse.h"
#include "rqlib/RQ__RQEvent.h"
#include "rqlib/RQ__EventHeader.h"
#include "rqlib/RQ__SingleScatters.h"
#include "TChain.h"
#include "TFile.h"
#include "TTreeReader.h"
#include "TH1.h"
#include "TH2D.h"
#include "TStopwatch.h"
#include <iostream>
#include <vector>


int main(int argc, char *argv[])
{

   TChain* tree = new TChain("Events");
   //in this version you pass a string to add files
   tree->Add(argv[1]);

   std::cout << tree->GetEntries() << std::endl;

   TTreeReader reader(tree);
   TTreeReaderValue<RQ::SingleScatters> scatters(reader, "singleScatters.");
   TTreeReaderValue<RQ::DetectorPulses> pulsesTPCHG(reader, "pulsesTPCHG.");

   TStopwatch* clock = new TStopwatch();
   clock->Start();


   while (reader.Next()) {

      std::cout << (*pulsesTPCHG).nPulses << std::endl;


   }

   cout << "Done!"<<" "<<clock->RealTime()<<" s."<<endl;
  

   delete tree;
   delete clock;

}
