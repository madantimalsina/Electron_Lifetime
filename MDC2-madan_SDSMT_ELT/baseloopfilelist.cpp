#include "rqlib/RQ__DetectorPulses.h"
#include "rqlib/RQ__EventHeader.h"
#include "rqlib/RQ__SingleScatters.h"
#include "rqlib/RQ__MultipleScatters.h"
#include "rqlib/RQ__OtherScatters.h"
#include "TChain.h"
#include "TFile.h"
#include "TTreeReader.h"
#include "TH1.h"
#include "TH2D.h"
#include "TStopwatch.h"
#include <iostream>
#include <vector>

void loadChain(char* txtFileList, TChain* chain);
bool isXe(double s1, double s2);
bool isXe2(double z, double s1, double s2);
bool isKr(double s1, double s2);
double correctS1(double s1, double dt);

int main(int argc, char *argv[])
{

  TChain* tree = new TChain("Events");

  loadChain(argv[1],tree);

  std::cout << "Entries = " << tree->GetEntries() << std::endl;

  TTreeReader reader(tree);
  TTreeReaderValue<RQ::SingleScatters> scatters(reader, "singleScatters.");
  TTreeReaderValue<RQ::MultipleScatters> scattersm(reader, "multipleScatters.");
  TTreeReaderValue<RQ::OtherScatters> scatterso(reader, "otherScatters.");
  TTreeReaderValue<RQ::DetectorPulses> pulsesTPCHG(reader, "pulsesTPCHG.");
  TTreeReaderValue<RQ::DetectorPulses> pulsesTPCLG(reader, "pulsesTPCLG.");

  TTreeReaderValue<RQ::DetectorPulses> *pulses;

  TStopwatch* clock = new TStopwatch();
  clock->Start();

  TFile *outfile = new TFile("May_study/root_Zslices_halfday_May/halfday_zSlices_May_day_64.root", "RECREATE");
  TH2F* hS1S2 = new TH2F("hS1S2", ";S1 [phd]; log10(S2 [phd])", 20000, 0, 10000, 700, 0, 7);
  TH2F* hS1S2Xe131m = new TH2F("hS1S2Xe131m", ";S1 [phd]; log10(S2 [phd])", 20000, 0, 10000, 700, 0, 7);
  TH2F* hS1S2Kr83 = new TH2F("hS1S2Kr83", ";S1 [phd]; log10(S2 [phd])", 20000, 0, 10000, 700, 0, 7);
  
  TH2F* hS2dT = new TH2F("hS2dT", ";Drift Time/#{mu}s;log10(S2 [phd])", 120, 0, 1200, 280, 0, 7);
  TH2F* hS2dTXe131m = new TH2F("hS2dTXe131m", ";Drift Time [#mus];log10(S2 [phd])", 120, 0, 1200, 280, 0, 7);
  TH2F* hS2dTKr83 = new TH2F("hS2dTKr83", ";Drift Time [#mus];log10(S2 [phd])", 120, 0, 1200, 280, 0, 7);

  TH2F* hS2zc = new TH2F("hS2zc", ";Zc - Corrected Z-position; log10(S2 [phd])", 120, -500, 2000, 280, 0, 7);
  TH2F* hdTzc = new TH2F("hdTzc", "; Zc - Corrected Z-position; Drift Time/#{mu}s", 120, -500, 2000, 120, 0, 1200);
  //TH2F* hdTzc = new TH2F("hdTzc", "; Drift Time/#{mu}s; Zc - Corrected Z-position", 120, 0, 1200, 120, -500, 2000);

  TH1F* hS2zc_0_50    = new TH1F("hS2zc_0_50",    ";log10(S2 [phd]   0mm-50mm)",   800, 0., 7.);
  TH1F* hS2zc_50_100  = new TH1F("hS2zc_50_100",  ";log10(S2 [phd]  50mm-100mm)",  800, 0., 7.);
  TH1F* hS2zc_100_150 = new TH1F("hS2zc_100_150", ";log10(S2 [phd]  100mm-150mm)", 800, 0., 7.);
  TH1F* hS2zc_150_200 = new TH1F("hS2zc_150_200", ";log10(S2 [phd]  150mm-200mm)", 800, 0., 7.);
  TH1F* hS2zc_200_250 = new TH1F("hS2zc_200_250", ";log10(S2 [phd]  200mm-250mm)", 800, 0., 7.);
  TH1F* hS2zc_250_300 = new TH1F("hS2zc_250_300", ";log10(S2 [phd]  250mm-300mm)", 800, 0., 7.);
  TH1F* hS2zc_300_350 = new TH1F("hS2zc_300_350", ";log10(S2 [phd]  300mm-350mm)", 800, 0., 7.);
  TH1F* hS2zc_350_400 = new TH1F("hS2zc_350_400", ";log10(S2 [phd]  350mm-400mm)", 800, 0., 7.);
  TH1F* hS2zc_400_450 = new TH1F("hS2zc_400_450", ";log10(S2 [phd]  400mm-450mm)", 800, 0., 7.);
  TH1F* hS2zc_450_500 = new TH1F("hS2zc_450_500", ";log10(S2 [phd]  450mm-500mm)", 800, 0., 7.);

  TH1F* hS2zc_500_550 = new TH1F("hS2zc_500_550", ";log10(S2 [phd]  500mm-550mm)", 800, 0., 7.);
  TH1F* hS2zc_550_600 = new TH1F("hS2zc_550_600", ";log10(S2 [phd]  550mm-600mm)", 800, 0., 7.);
  TH1F* hS2zc_600_650 = new TH1F("hS2zc_600_650", ";log10(S2 [phd]  600mm-650mm)", 800, 0., 7.);
  TH1F* hS2zc_650_700 = new TH1F("hS2zc_650_700", ";log10(S2 [phd]  650mm-700mm)", 800, 0., 7.);
  TH1F* hS2zc_700_750 = new TH1F("hS2zc_700_750", ";log10(S2 [phd]  700mm-750mm)", 800, 0., 7.);
  TH1F* hS2zc_750_800 = new TH1F("hS2zc_750_800", ";log10(S2 [phd]  750mm-800mm)", 800, 0., 7.);
  TH1F* hS2zc_800_850 = new TH1F("hS2zc_800_850", ";log10(S2 [phd]  800mm-850mm)", 800, 0., 7.);
  TH1F* hS2zc_850_900 = new TH1F("hS2zc_850_900", ";log10(S2 [phd]  850mm-900mm)", 800, 0., 7.);
  TH1F* hS2zc_900_950 = new TH1F("hS2zc_900_950", ";log10(S2 [phd]  900mm-950mm)", 800, 0., 7.);
  TH1F* hS2zc_950_1000= new TH1F("hS2zc_950_1000", ";log10(S2 [phd] 950mm-1000mm)", 800, 0., 7.);

  TH1F* hS2zc_1000_1050 = new TH1F("hS2zc_1000_1050", ";log10(S2 [phd] 1000mm-1050mm)", 800, 0., 7.);
  TH1F* hS2zc_1050_1100 = new TH1F("hS2zc_1050_1100", ";log10(S2 [phd] 1050mm-1100mm)",  800, 0., 7.);
  TH1F* hS2zc_1100_1150 = new TH1F("hS2zc_1100_1150", ";log10(S2 [phd] 1100mm-1150mm)", 800, 0., 7.);
  TH1F* hS2zc_1150_1200 = new TH1F("hS2zc_1150_1200", ";log10(S2 [phd] 1150mm-1200mm)", 800, 0., 7.);
  TH1F* hS2zc_1200_1250 = new TH1F("hS2zc_1200_1250", ";log10(S2 [phd] 1200mm-1250mm)", 800, 0., 7.);
  TH1F* hS2zc_1250_1300 = new TH1F("hS2zc_1250_1300", ";log10(S2 [phd] 1250mm-1300mm)", 800, 0., 7.);
  TH1F* hS2zc_1300_1350 = new TH1F("hS2zc_1300_1350", ";log10(S2 [phd] 1300mm-1350mm)", 800, 0., 7.);
  TH1F* hS2zc_1350_1400 = new TH1F("hS2zc_1350_4100", ";log10(S2 [phd] 1350mm-1400mm)", 800, 0., 7.);
  TH1F* hS2zc_1400_1450 = new TH1F("hS2zc_1400_1450", ";log10(S2 [phd] 1400mm-1450mm)", 800, 0., 7.);
  TH1F* hS2zc_1450_1500 = new TH1F("hS2zc_1450_1500", ";log10(S2 [phd] 1450mm-1500mm)", 800, 0., 7.);



  while (reader.Next())
    {
      if(reader.GetCurrentEntry()%100 == 0)
	std::cout << "Current Entries = " << reader.GetCurrentEntry() << "\r";//std::endl;

      double s1 = 0, s2 = 0, dt = 0, s1c = 0, x = 0, y = 0, zc = 0, z = 0, t = 0;
      int  pulseID = -1;
      bool s2IsHG = 0;
   
      for(int i = 0; i < scatters->nSingleScatters; i++)
	{
	  s1 = scatters->s1Area_phd[i];
	  s2 = log10(scatters->s2Area_phd[i]);
	  x = scatters->x_cm[i];
	  y = scatters->y_cm[i];
	  pulseID = scatters->s2PulseID[i];
	  s2IsHG = scatters->s2IsHG[i];

	  dt = scatters->driftTime_ns[i];
	  s1c = correctS1(scatters->s1Area_phd[i],dt);

	  hS1S2->Fill(s1, s2);
	  hS2dT->Fill(dt, s2);
	}

      for(int i = 0; i < scattersm->nMultipleScatters; i++)
	{
	  s1 = scattersm->s1Area_phd[i];
	  double s2_0 = log10(scattersm->s2Area_phd[i][0]);
	  double s2_1 = log10(scattersm->s2Area_phd[i][1]);

	  double x_0 = scattersm->x_cm[i][0];
	  double x_1 = scattersm->x_cm[i][1];
	  double y_0 = scattersm->y_cm[i][0];
	  double y_1 = scattersm->y_cm[i][1];

    double zc_0 = scattersm->correctedZ_cm[i][0];
    double zc_1 = scattersm->correctedZ_cm[i][1];



	  int pulseID_0 = scattersm->s2PulseIDs[i][0];
	  bool s2IsHG_0 = scattersm->s2IsHG[i][0];
	  int pulseID_1 = scattersm->s2PulseIDs[i][1];
	  bool s2IsHG_1 = scattersm->s2IsHG[i][1];


	  double dt_0 = scattersm->driftTime_ns[i][0];
	  double dt_1 = scattersm->driftTime_ns[i][1];
	  double s1_0 = correctS1(s1,dt_0);
	  double s1_1 = correctS1(s1,dt_1);

	  if(isXe(s1, s2_0) || isKr(s1, s2_0) || isXe2(z, t, s2_0))
	    {
	      s2 = s2_0;
	      dt = dt_0;
	      x = x_0;
	      y = y_0;
        zc = zc_0;
	      pulseID = pulseID_0;
	      s2IsHG = s2IsHG_0;
	    }
	  else if(isXe(s1, s2_1) || isKr(s1, s2_1) | isXe2(z, t, s2_1))
	    {
	      s2 = s2_1;
	      dt = dt_1;
	      x = x_1;
	      y = y_1;
        zc = zc_1;
	      pulseID = pulseID_1;
	      s2IsHG = s2IsHG_1;
	    }

	}

      if(s1 > 0 && s2 > 0)
      {
	if(x*x + y*y > 30.*30.)//cm
	  continue;
	if(s2IsHG)
	  pulses = &pulsesTPCHG;
	else
	  pulses = &pulsesTPCLG;
	
	double s2b = log10((*pulses)->bottomArea_phd[pulseID]);
	if(isXe(s1, s2))
	{
	  hS1S2Xe131m->Fill(s1, s2b);
	  hS2dTXe131m->Fill(dt/1000., s2b);

    hS2zc->Fill(zc, s2);
    // fill 1-dim slices of 2-dim hS2zc in 50 mm increments:
    if ( zc >= 0. && zc < 50. )      hS2zc_0_50->Fill(s2);
    if ( zc >= 50. && zc < 100. )    hS2zc_50_100->Fill(s2);
    if ( zc >= 100. && zc < 150. )   hS2zc_100_150->Fill(s2);
    if ( zc >= 150. && zc < 200. )   hS2zc_150_200->Fill(s2);
    if ( zc >= 200. && zc < 250. )   hS2zc_200_250->Fill(s2);
    if ( zc >= 250. && zc < 300. )   hS2zc_250_300->Fill(s2);
    if ( zc >= 300. && zc < 350. )   hS2zc_300_350->Fill(s2);
    if ( zc >= 350. && zc < 400. )   hS2zc_350_400->Fill(s2);
    if ( zc >= 400. && zc < 450. )   hS2zc_400_450->Fill(s2);
    if ( zc >= 450. && zc < 500. )   hS2zc_450_500->Fill(s2);
    if ( zc >= 500. && zc < 550. )   hS2zc_500_550->Fill(s2);
    if ( zc >= 550. && zc < 600. )    hS2zc_550_600->Fill(s2);
    if ( zc >= 600. && zc < 650. )   hS2zc_600_650->Fill(s2);
    if ( zc >= 650. && zc < 700. )   hS2zc_650_700->Fill(s2);
    if ( zc >= 700. && zc < 750. )   hS2zc_700_750->Fill(s2);
    if ( zc >= 750. && zc < 800. )   hS2zc_750_800->Fill(s2);
    if ( zc >= 800. && zc < 850. )   hS2zc_800_850->Fill(s2);
    if ( zc >= 850. && zc < 900. )   hS2zc_850_900->Fill(s2);
    if ( zc >= 900. && zc < 950. )   hS2zc_900_950->Fill(s2);
    if ( zc >= 950. && zc < 1000. )  hS2zc_950_1000->Fill(s2);

    if ( zc >= 1000. && zc < 1050. )   hS2zc_1000_1050->Fill(s2);
    if ( zc >= 1050. && zc < 1100. )   hS2zc_1050_1100->Fill(s2);
    if ( zc >= 1100. && zc < 1150. )   hS2zc_1100_1150->Fill(s2);
    if ( zc >= 1150. && zc < 1200. )   hS2zc_1150_1200->Fill(s2);
    if ( zc >= 1200. && zc < 1250. )   hS2zc_1200_1250->Fill(s2);
    if ( zc >= 1250. && zc < 1300. )   hS2zc_1250_1300->Fill(s2);
    if ( zc >= 1300. && zc < 1350. )   hS2zc_1300_1350->Fill(s2);
    if ( zc >= 1350. && zc < 1400. )   hS2zc_1350_1400->Fill(s2);
    if ( zc >= 1400. && zc < 1450. )   hS2zc_1400_1450->Fill(s2);
    if ( zc >= 1450. && zc < 1500. )   hS2zc_1450_1500->Fill(s2);
    
    //hdTzc->Fill(zc, dt/1000.);
	}
	else if(isKr(s1, s2))
	{
	  hS1S2Kr83->Fill(s1, s2b);
	  hS2dTKr83->Fill(dt/1000., s2b);
	}

  if(isXe2(z, t, s2))
  {

    hdTzc->Fill(zc, dt/1000.);
  }

      }
      // for(int i = 0; i < scatterso->nOtherScatters; i++)
      // 	{
      // 	  int s2ind = -1;
      // 	  double s2area = 0;
      // 	  for(int j=0; j<scatterso->nS2s[i]; j++)
      // 	    {
      // 	      int ind = scatterso->s2PulseIDs[i][1];
      // 	      if(s2area<pulsesTPCHG->pulseArea_phd[ind])
      // 		{
      // 		  s2area = pulsesTPCHG->pulseArea_phd[scatterso->s2PulseIDs[i][1]];
      // 		  s2ind = scatterso->s2PulseIDs[i][1];
      // 		}
      // 	    }

      // 	  if(scatterso->nS1s[i]>0 && s2area>0)
      // 	    {
      // 	      hOther->Fill(pulsesTPCHG->pulseStartTime_ns[s2ind]-pulsesTPCHG->pulseStartTime_ns[scatterso->s1PulseIDs[i][0]],
      // 			   pulsesTPCHG->pulseArea_phd[scatterso->s1PulseIDs[i][0]]);

      // 	    }
	 
	 
 
      // 	}

    }
  std::cout << std::endl;
  hS1S2->Write();
  hS1S2Xe131m->Write();
  hS1S2Kr83->Write();
  
  hS2dT->Write();
  hS2dTXe131m->Write();
  hS2dTKr83->Write();

  hS2zc->Write();
  hdTzc->Write();

  hS2zc_0_50->Write();
  hS2zc_50_100->Write();
  hS2zc_100_150->Write();
  hS2zc_150_200->Write();
  hS2zc_200_250->Write();
  hS2zc_250_300->Write();
  hS2zc_300_350->Write();
  hS2zc_350_400->Write();
  hS2zc_400_450->Write();
  hS2zc_450_500->Write();
  hS2zc_500_550->Write();
  hS2zc_550_600->Write();
  hS2zc_600_650->Write();
  hS2zc_650_700->Write();
  hS2zc_700_750->Write();
  hS2zc_750_800->Write();
  hS2zc_800_850->Write();
  hS2zc_850_900->Write();
  hS2zc_900_950->Write();
  hS2zc_950_1000->Write();

  hS2zc_1000_1050->Write();
  hS2zc_1050_1100->Write();
  hS2zc_1100_1150->Write();
  hS2zc_1150_1200->Write();
  hS2zc_1200_1250->Write();
  hS2zc_1250_1300->Write();
  hS2zc_1300_1350->Write();
  hS2zc_1350_1400->Write();
  hS2zc_1400_1450->Write();
  hS2zc_1450_1500->Write();


  outfile->Close();

  cout << "Done!" << " " << clock->RealTime() << " s." << endl;
  
  delete outfile;
  delete tree;
  delete clock;

}


void loadChain(char* txtFileList, TChain* chain){
  
  ifstream fileList(txtFileList);
  string file;
   
  if(fileList.is_open())
    {
      while(getline(fileList, file)) 
	{
	  chain->Add(file.c_str());
	}
      fileList.close();
    }
  else
    {
      exit(-1);
    }
}

bool isXe(double s1, double s2)
{
  double a1 = 6.5-0.0006*s1;
  double a2 = 6.1-0.0006*s1;
  if(s2>a2 && s2<a1)
    return true;
  else
    return false;
      
}

bool isXe2(double z, double s1, double s2)
{
  double a1 = 6.5-0.0006*s1;
  double a2 = 6.1-0.0006*s1;
  if(s2>a2 && s2<a1)
    return true;
  else
    return false;
      
}

bool isKr(double s1, double s2)
{
  double a1 = 6.1-0.0025*s1;
  double a2 = 5.45-0.0025*s1;
  if(s2>a2 && s2<a1)
    return true;
  else
    return false;
      
}
double correctS1(double s1, double dt)
{
  return s1/(0.660387+0.0000002349*dt+0.0000000000001860358*dt*dt);
}
