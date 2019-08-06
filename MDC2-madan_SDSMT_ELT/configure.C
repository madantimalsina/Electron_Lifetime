void configure(TString filename = "data/lz_201704010000_001000_lzap.root")
{
  TFile* f = TFile::Open(filename);
  f->MakeProject("rqlib","*","update+");
}
