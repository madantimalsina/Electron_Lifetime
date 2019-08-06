{
   gROOT->ProcessLine(".L SetLZStyle.h");
   SetLZStyle(1);
   gROOT->Reset();
   gROOT->SetStyle("LZ");
   gROOT->ForceStyle();


}
