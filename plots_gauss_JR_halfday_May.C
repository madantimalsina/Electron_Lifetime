
{
  ofstream myfile;
  ofstream myfileg;
  ofstream myfilegfit;
  myfile.open ("May_study/zslice_plot_JR_halfday_May/Electron_Lifetime.txt");
  myfileg.open ("May_study/zslice_plot_JR_halfday_May/Electron_Lifetime_gauss.txt");
  myfilegfit.open("May_study/zslice_plot_JR_halfday_May/Gaussian_fit_par.txt");


  stringstream ss;
  TF1* linearfit = new TF1("linearfit", "[0] + [j]*x", 5., 130.);
  TF1* linearfit1 = new TF1("linearfit1", "[0] + [j]*x", 5., 130.);
  linearfit1->SetLineColor(2);
  TF1* linearfit2 = new TF1("linearfit2", "[0] + [j]*x", 5., 130.);
  linearfit2->SetLineColor(2);

  //TF1* linearfit3 = new TF1("linearfit3", "[0] + [j]*x", 0., 1350.);


  TF1* fGausS2 = new TF1("fGausS2", "gaus", 5., 7.);
  //TF1* fGausS2 = new TF1("fGausS2", "gaus", 0, 12);

  TCanvas *c = new TCanvas("c", "c", 800, 600);
  TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
  TCanvas *c2 = new TCanvas("c2", "c2", 800, 600);
  TCanvas *c3 = new TCanvas("c3", "c3", 1300, 800);
  TCanvas *c4 = new TCanvas("c4", "c4", 800, 600);
  TCanvas *c5 = new TCanvas("c5", "c5", 800, 600);

  //TFile *outfile = new TFile("ltXe131m.root", "RECREATE");
  TGraphErrors *gXe131m = new TGraphErrors();
  TGraphErrors *gXe131m_ = new TGraphErrors();
  TGraphErrors *gXe131mGausFits = new TGraphErrors();
  //myfile << "Writing this to a file.\n";



  int i = 0;
  for(int day = 1; day <= 64; ++day)
    {
      //if(day == 2 || day == 18) //days not processed
       //continue;
      ss.str("");
      ss << "May_study/root_Zslices_halfday_May/halfday_zSlices_May_day_";
      if(day < 10)
       ss << "0";

      ss << day << ".root";
      TFile f(ss.str().c_str(), "READ");
      if(!f.IsOpen())
     continue;
/*
   // For Sz Vs Drift time
      c->cd();
      TH2F* hS2dTXe131m = (TH2F*)f.Get("hS2dTXe131m");
      hS2dTXe131m->GetXaxis()->SetTitle("Drift Time [#mus]");
      
      hS2dTXe131m->GetYaxis()->SetTitle("log10(S2 [phd])");
      hS2dTXe131m->GetYaxis()->SetRangeUser(4.6, 6);
      hS2dTXe131m->SetMinimum(5);
      hS2dTXe131m->SetMaximum(450);
      hS2dTXe131m->SetStats(1111);
      hS2dTXe131m->Draw("colz");
      hS2dTXe131m->Fit(linearfit, "R");


      ss.str("");
      ss << "Output/day_S2VsDT_";
      if(day < 10)
       ss << "0";
      ss << day << ".png";
      c->Print(ss.str().c_str());


      ss.str("");
      ss << "Day_ " << day;
      TLegend ls(0.3, 0.5, 0.5, 0.7);
      ls.AddEntry(hS2dTXe131m, ss.str().c_str(), "");
      ls.Draw();

      c->Print("May_study/zslice_plot_JR_halfday_May/mygif.gif+50");
      c->WaitPrimitive();*/

      // For S2 Vs Zc
      c2->cd();
      TH2F* hS2zc = (TH2F*)f.Get("hS2zc");
      hS2zc->GetXaxis()->SetTitle("Zc - Corrected Z-position [mm]");
      hS2zc->GetYaxis()->SetTitle("log10(S2 [phd])");
      //      hS2dTXe131m->GetYaxis()->SetRangeUser(5.2, 7);
      hS2zc->GetYaxis()->SetRangeUser(5, 6.52);
      hS2zc->SetMinimum(0);
      hS2zc->SetMaximum(50);
      hS2zc->Draw("colz");
      hS2zc->Fit(linearfit1, "R");


      ss.str("");
      ss << "May_study/zslice_plot_JR_halfday_May/S2VsZc_";
      if(day < 10)
       ss << "0";
      ss << day << ".png";
      c2->Print(ss.str().c_str());


      ss.str("");
      ss << "Day_ " << day;
      TLegend l(0.6, 0.6, 0.8, 0.8);
      l.AddEntry(hS2zc, ss.str().c_str(), "");
      l.Draw();

      c2->Print("May_study/zslice_plot_JR_halfday_May/mygif1.gif+50");
      c2->WaitPrimitive();

      // for drift time Vs Zc
      c3->cd();
      TH2F* hdTzc = (TH2F*)f.Get("hdTzc");
      hdTzc->GetXaxis()->SetTitle("Zc - Corrected Z-position [mm]");
      hdTzc->GetYaxis()->SetTitle("Drift Time [#mus]");
      // hS2dTXe131m->GetYaxis()->SetRangeUser(5.2, 7);
      hdTzc->GetYaxis()->SetRangeUser(0, 1000);
      hdTzc->SetMinimum(0);
      hdTzc->SetMaximum(1200);
      hdTzc->Draw("colz");
      hdTzc->Fit(linearfit2, "R");

       //tex = new TLatex(1169.905,506.3289,"April_01");
       //tex->SetLineWidth(2);
       //tex->Draw();
       //tex = new TLatex(298.3674,120.9342,"Drift Time [#mus] = (0.350 #pm 0.940) + ( 0.666 #pm 1.122E-03) * Zc [mm]");
       //tex->SetTextSize(0.03);
       //tex->SetTextAngle(0.4);
       //tex->SetLineWidth(2);
       //tex->Draw();

      ss.str("");
      ss << "May_study/zslice_plot_JR_halfday_May/dTVsZc_";
      if(day < 10)
      ss << "0";
      ss << day << ".png";
      c3->Print(ss.str().c_str());


      ss.str("");
      ss << "Day_" << day;
      TLegend l1(0.6, 0.6, 0.8, 0.3);
      l1.AddEntry(hdTzc, ss.str().c_str(), "");
      l1.Draw();

      c3->Print("May_study/zslice_plot_JR_halfday_May/mygif2.gif+50");
      c3->WaitPrimitive();

/*
      // For electron lifetime (Andrew & Brais..)
      float b = linearfit->GetParameter(1);
      cout << "b = " << b << endl;
      float lt = -1/(log(10)*linearfit->GetParameter(1));
      cout << "lt = " << "-1/(log(10)*b = " << lt << "us" << endl;
      gXe131m_->SetPoint(i, float(day), lt);
      float lterr = linearfit->GetParError(1)/(log(10)* (b*b));
      gXe131m_->SetPointError(i, 0.5, lterr);*/

      // Madan's method
      float al = -1/(log(10)*linearfit1->GetParameter(1));
      float d = linearfit2->GetParameter(1);
      float elt = al * d;
      gXe131m->SetPoint(i, float(day), elt);
      float err_al = linearfit1->GetParError(1);
      float alerr = err_al/((log(10)*linearfit1->GetParameter(1)*linearfit1->GetParameter(1)));
      float derr = linearfit2->GetParError(1);
      float elterr = elt * (sqrt ( (alerr*alerr)/(al*al) + (derr*derr)/(d*d) ));

      cout << "SDSMT: Electron Lifetime = " << elt << " Error Electron Lifetime = " << elterr << endl;
      //myfile << "SDSMT: Electron Lifetime = " << elt << " Error = " << elterr << endl;
      myfile << day << " "<< elt << " " << elterr << endl;

      //cout << "Other's: Electron Lifetime = " << lt << "Error Electron Lifetime = " << lterr << endl;
      gXe131m->SetPointError(i, 0.5, elterr);

/*
      TFile myfile ("Electron_Lifetime.txt");
      if(!f.IsOpen())
        continue;

 
    {
      cout << "SDSMT: Electron Lifetime = " << elt << " Error Electron Lifetime = " << elterr << endl;
    }*/

        //fits Zslices my method:
      //c5->cd();
      float ymax =0.;
      float xmax = 0.;
      float meanS2[29] = {};
      float eMeanS2[29] = {};
      TGraphErrors* gMeans = new TGraphErrors();




  //         for(int j = 0; j <= 1; j++)
   //   {

      //slice 1
      int j;
       TCanvas *c20 = new TCanvas("c20", "", 800, 600);
       c20->cd();

        //TH1F* h = hS2zc_0_50;
       TH1F* hS2zc_0_50 = (TH1F*)f.Get("hS2zc_0_50");
       hS2zc_0_50->GetXaxis()->SetRangeUser(5, 6);
        for (j = 1; j <= 800; j++)
          { if (hS2zc_0_50->GetBinContent(j) > ymax) 
              { ymax = hS2zc_0_50->GetBinContent(j); 
                xmax = j;
              }
          }
        //hS2zc_0_50->GetXaxis()->SetRangeUser(5, 6);  
        fGausS2->SetRange((xmax*7.0/800.) - 1., (xmax*7.0/800.) + 1.);
        fGausS2->SetParameters(0, ymax);
        fGausS2->SetParameters(1, xmax*7.0/800.);
        fGausS2->SetParameters(2, 0.2/3.);
        hS2zc_0_50->Fit(fGausS2, "RW");
        //h->Draw();
        //getchar();
      meanS2[0] = fGausS2->GetParameter(1);
      eMeanS2[0] = fGausS2->GetParError(1);

      ss.str("");
      ss << "May_study/zslice_plot_JR_halfday_May/hS2zc_0_50_";
      if(day < 10)
      ss << "0";
      ss << day << ".png";
      //c20->Print(ss.str().c_str());

      ss.str("");
      ss << "Day_" << day;
      TLegend l20(0.3, 0.5, 0.5, 0.7);
      l20.AddEntry(hS2zc_0_50, ss.str().c_str(), "");
      l20.Draw();
      c20->Print(ss.str().c_str());
      c20->SaveAs("May_study/zslice_plot_JR_halfday_May/hS2zc_0_50.gif+50");


      //slice 2
      TCanvas *c2n = new TCanvas("c2n", "", 800, 600);
      c2n->cd();
      //TH1F* h2 = hS2zc_50_100;
      TH1F* hS2zc_50_100 = (TH1F*)f.Get("hS2zc_50_100");
      hS2zc_50_100->GetXaxis()->SetRangeUser(5, 6);
        for (j = 1; j <= 800; j++)
          { if (hS2zc_50_100->GetBinContent(j) > ymax) 
              { ymax = hS2zc_50_100->GetBinContent(j); 
                xmax = j;
              }
          }
        fGausS2->SetRange((xmax*7.0/800.) - 1., (xmax*7.0/800.) + 1.);
        fGausS2->SetParameters(0, ymax);
        fGausS2->SetParameters(1, xmax*7.0/800.);
        fGausS2->SetParameters(2, 0.2/3.);
        hS2zc_50_100->Fit(fGausS2, "RW");
        //h->Draw();
        //getchar();
      meanS2[1] = fGausS2->GetParameter(1);
      eMeanS2[1] = fGausS2->GetParError(1);

      ss.str("");
      ss << "May_study/zslice_plot_JR_halfday_May/hS2zc_50_100_";
      if(day < 10)
      ss << "0";
      ss << day << ".png";
      //c21->Print(ss.str().c_str());
      
      ss.str("");
      ss << "Day_" << day;
      TLegend l2n(0.3, 0.5, 0.5, 0.7);
      l2n.AddEntry(hS2zc_50_100, ss.str().c_str(), "");
      l2n.Draw();

      c2n->Print(ss.str().c_str());
      c2n->SaveAs("May_study/zslice_plot_JR_halfday_May/hS2zc_50_100.gif+50");

      //slice 3

      TCanvas *c21 = new TCanvas("c21", "", 800, 600);
      c21->cd();
       TH1F* hS2zc_100_150 = (TH1F*)f.Get("hS2zc_100_150");
       hS2zc_100_150->GetXaxis()->SetRangeUser(5, 6);
        for (j = 1; j <= 800; j++)
          { if (hS2zc_100_150->GetBinContent(j) > ymax) 
              { ymax = hS2zc_100_150->GetBinContent(j); 
                xmax = j;
              }
          }
        fGausS2->SetRange((xmax*7.0/800.) - 1., (xmax*7.0/800.) + 1.);
        fGausS2->SetParameters(0, ymax);
        fGausS2->SetParameters(1, xmax*7.0/800.);
        fGausS2->SetParameters(2, 0.2/3.);
        hS2zc_100_150->Fit(fGausS2, "RW");
        //getchar();
      meanS2[2] = fGausS2->GetParameter(1);
      eMeanS2[2] = fGausS2->GetParError(1);


      ss.str("");
      ss << "May_study/zslice_plot_JR_halfday_May/hS2zc_100_150_";
      if(day < 10)
      ss << "0";
      ss << day << ".png";
      //c21->Print(ss.str().c_str());
      
      ss.str("");
      ss << "Day_" << day;
      TLegend l21(0.3, 0.5, 0.5, 0.7);
      l21.AddEntry(hS2zc_100_150, ss.str().c_str(), "");
      l21.Draw();

      c21->Print(ss.str().c_str());
      c21->SaveAs("May_study/zslice_plot_JR_halfday_May/hS2zc_100_150.gif+50");


      //slice 4

      TCanvas *c22 = new TCanvas("c22", "", 800, 600);
      c22->cd();
      TH1F* hS2zc_150_200 = (TH1F*)f.Get("hS2zc_150_200");
      hS2zc_150_200->GetXaxis()->SetRangeUser(5, 6);
        for (j = 1; j <= 800; j++)
          { if (hS2zc_150_200->GetBinContent(j) > ymax) 
              { ymax = hS2zc_150_200->GetBinContent(j); 
                xmax = j;
              }
          }
        fGausS2->SetRange((xmax*7.0/800.) - 1., (xmax*7.0/800.) + 1.);
        fGausS2->SetParameters(0, ymax);
        fGausS2->SetParameters(1, xmax*7.0/800.);
        fGausS2->SetParameters(2, 0.2/3.);
        hS2zc_150_200->Fit(fGausS2, "RW");
        //getchar();
      meanS2[3] = fGausS2->GetParameter(1);
      eMeanS2[3] = fGausS2->GetParError(1);


      ss.str("");
      ss << "May_study/zslice_plot_JR_halfday_May/hS2zc_150_200_";
      if(day < 10)
      ss << "0";
      ss << day << ".png";
      //c22->Print(ss.str().c_str());
      
      ss.str("");
      ss << "Day_" << day;
      TLegend l22(0.3, 0.5, 0.5, 0.7);
      l22.AddEntry(hS2zc_150_200, ss.str().c_str(), "");
      l22.Draw();

      c22->Print(ss.str().c_str());
      c22->SaveAs("May_study/zslice_plot_JR_halfday_May/hS2zc_150_200.gif+50");

     //slice 5

      TCanvas *c23 = new TCanvas("c23", "", 800, 600);
      c23->cd();
      TH1F* hS2zc_200_250 = (TH1F*)f.Get("hS2zc_200_250");
      hS2zc_200_250->GetXaxis()->SetRangeUser(5, 6);
        for (j = 1; j <= 800; j++)
          { if (hS2zc_200_250->GetBinContent(j) > ymax) 
              { ymax = hS2zc_200_250->GetBinContent(j); 
                xmax = j;
              }
          }
        fGausS2->SetRange((xmax*7.0/800.) - 1., (xmax*7.0/800.) + 1.);
        fGausS2->SetParameters(0, ymax);
        fGausS2->SetParameters(1, xmax*7.0/800.);
        fGausS2->SetParameters(2, 0.2/3.);
        hS2zc_200_250->Fit(fGausS2, "RW");
        //getchar();
      meanS2[4] = fGausS2->GetParameter(1);
      eMeanS2[4] = fGausS2->GetParError(1);


      ss.str("");
      ss << "May_study/zslice_plot_JR_halfday_May/hS2zc_200_250_";
      if(day < 10)
      ss << "0";
      ss << day << ".png";
      //c23->Print(ss.str().c_str());
      
      ss.str("");
      ss << "Day_" << day;
      TLegend l23(0.3, 0.5, 0.5, 0.7);
      l23.AddEntry(hS2zc_200_250, ss.str().c_str(), "");
      l23.Draw();

      c23->Print(ss.str().c_str());
      c23->SaveAs("May_study/zslice_plot_JR_halfday_May/hS2zc_200_250.gif+50");

      //slice 6

      TCanvas *c24 = new TCanvas("c24", "", 800, 600);
      c24->cd();
      TH1F* hS2zc_250_300 = (TH1F*)f.Get("hS2zc_250_300");
      hS2zc_250_300->GetXaxis()->SetRangeUser(5, 6);
        for (j = 1; j <= 800; j++)
          { if (hS2zc_250_300->GetBinContent(j) > ymax) 
              { ymax = hS2zc_250_300->GetBinContent(j); 
                xmax = j;
              }
          }
        fGausS2->SetRange((xmax*7.0/800.) - 1., (xmax*7.0/800.) + 1.);
        fGausS2->SetParameters(0, ymax);
        fGausS2->SetParameters(1, xmax*7.0/800.);
        fGausS2->SetParameters(2, 0.2/3.);
        hS2zc_250_300->Fit(fGausS2, "RW");
        //getchar();
      meanS2[5] = fGausS2->GetParameter(1);
      eMeanS2[5] = fGausS2->GetParError(1);


      ss.str("");
      ss << "May_study/zslice_plot_JR_halfday_May/hS2zc_250_300_";
      if(day < 10)
      ss << "0";
      ss << day << ".png";
      //c24->Print(ss.str().c_str());
      
      ss.str("");
      ss << "Day_" << day;
      TLegend l24(0.3, 0.5, 0.5, 0.7);
      l24.AddEntry(hS2zc_250_300, ss.str().c_str(), "");
      l24.Draw();

      c24->Print(ss.str().c_str());
      c24->SaveAs("May_study/zslice_plot_JR_halfday_May/hS2zc_250_300.gif+50");

     //slice 7

      TCanvas *c25 = new TCanvas("c25", "", 800, 600);
      c25->cd();
      TH1F* hS2zc_300_350 = (TH1F*)f.Get("hS2zc_300_350");
      hS2zc_300_350->GetXaxis()->SetRangeUser(5, 6);
        for (j = 1; j <= 800; j++)
          { if (hS2zc_300_350->GetBinContent(j) > ymax) 
              { ymax = hS2zc_300_350->GetBinContent(j); 
                xmax = j;
              }
          }
        fGausS2->SetRange((xmax*7.0/800.) - 1., (xmax*7.0/800.) + 1.);
        fGausS2->SetParameters(0, ymax);
        fGausS2->SetParameters(1, xmax*7.0/800.);
        fGausS2->SetParameters(2, 0.2/3.);
        hS2zc_300_350->Fit(fGausS2, "RW");
        //getchar();
      meanS2[6] = fGausS2->GetParameter(1);
      eMeanS2[6] = fGausS2->GetParError(1);


      ss.str("");
      ss << "May_study/zslice_plot_JR_halfday_May/hS2zc_300_350_";
      if(day < 10)
      ss << "0";
      ss << day << ".png";
      //c23->Print(ss.str().c_str());
      
      ss.str("");
      ss << "Day_" << day;
      TLegend l25(0.3, 0.5, 0.5, 0.7);
      l25.AddEntry(hS2zc_300_350, ss.str().c_str(), "");
      l25.Draw();

      c25->Print(ss.str().c_str());
      c25->SaveAs("May_study/zslice_plot_JR_halfday_May/hS2zc_300_350.gif+50");

      //slice 8

      TCanvas *c26 = new TCanvas("c26", "", 800, 600);
      c26->cd();
      TH1F* hS2zc_350_400 = (TH1F*)f.Get("hS2zc_350_400");
      hS2zc_350_400->GetXaxis()->SetRangeUser(5, 6);
        for (j = 1; j <= 800; j++)
          { if (hS2zc_350_400->GetBinContent(j) > ymax) 
              { ymax = hS2zc_350_400->GetBinContent(j); 
                xmax = j;
              }
          }
        fGausS2->SetRange((xmax*7.0/800.) - 1., (xmax*7.0/800.) + 1.);
        fGausS2->SetParameters(0, ymax);
        fGausS2->SetParameters(1, xmax*7.0/800.);
        fGausS2->SetParameters(2, 0.2/3.);
        hS2zc_350_400->Fit(fGausS2, "RW");
        //getchar();
      meanS2[7] = fGausS2->GetParameter(1);
      eMeanS2[7] = fGausS2->GetParError(1);


      ss.str("");
      ss << "May_study/zslice_plot_JR_halfday_May/hS2zc_350_400_";
      if(day < 10)
      ss << "0";
      ss << day << ".png";
      //c24->Print(ss.str().c_str());
      
      ss.str("");
      ss << "Day_" << day;
      TLegend l26(0.3, 0.5, 0.5, 0.7);
      l26.AddEntry(hS2zc_350_400, ss.str().c_str(), "");
      l26.Draw();

      c26->Print(ss.str().c_str());
      c26->SaveAs("May_study/zslice_plot_JR_halfday_May/hS2zc_350_400.gif+50");


      //slice 9

      TCanvas *c27 = new TCanvas("c27", "", 800, 600);
      c27->cd();
      TH1F* hS2zc_400_450 = (TH1F*)f.Get("hS2zc_400_450");
      hS2zc_400_450->GetXaxis()->SetRangeUser(5, 6);
        for (j = 1; j <= 800; j++)
          { if (hS2zc_400_450->GetBinContent(j) > ymax) 
              { ymax = hS2zc_400_450->GetBinContent(j); 
                xmax = j;
              }
          }
        fGausS2->SetRange((xmax*7.0/800.) - 1., (xmax*7.0/800.) + 1.);
        fGausS2->SetParameters(0, ymax);
        fGausS2->SetParameters(1, xmax*7.0/800.);
        fGausS2->SetParameters(2, 0.2/3.);
        hS2zc_400_450->Fit(fGausS2, "RW");
        //getchar();
      meanS2[8] = fGausS2->GetParameter(1);
      eMeanS2[8] = fGausS2->GetParError(1);


      ss.str("");
      ss << "May_study/zslice_plot_JR_halfday_May/hS2zc_400_450_";
      if(day < 10)
      ss << "0";
      ss << day << ".png";
      //c23->Print(ss.str().c_str());
      
      ss.str("");
      ss << "Day_" << day;
      TLegend l27(0.3, 0.5, 0.5, 0.7);
      l27.AddEntry(hS2zc_400_450, ss.str().c_str(), "");
      l27.Draw();

      c27->Print(ss.str().c_str());
      c27->SaveAs("May_study/zslice_plot_JR_halfday_May/hS2zc_400_450.gif+50");

      //slice 10

      TCanvas *c28 = new TCanvas("c28", "", 800, 600);
      c28->cd();
      TH1F* hS2zc_450_500 = (TH1F*)f.Get("hS2zc_450_500");
      hS2zc_450_500->GetXaxis()->SetRangeUser(5, 6);
        for (j = 1; j <= 800; j++)
          { if (hS2zc_450_500->GetBinContent(j) > ymax) 
              { ymax = hS2zc_450_500->GetBinContent(j); 
                xmax = j;
              }
          }
        fGausS2->SetRange((xmax*7.0/800.) - 1., (xmax*7.0/800.) + 1.);
        fGausS2->SetParameters(0, ymax);
        fGausS2->SetParameters(1, xmax*7.0/800.);
        fGausS2->SetParameters(2, 0.2/3.);
        hS2zc_450_500->Fit(fGausS2, "RW");
        //getchar();
      meanS2[9] = fGausS2->GetParameter(1);
      eMeanS2[9] = fGausS2->GetParError(1);


      ss.str("");
      ss << "May_study/zslice_plot_JR_halfday_May/hS2zc_450_500_";
      if(day < 10)
      ss << "0";
      ss << day << ".png";
      //c24->Print(ss.str().c_str());
      
      ss.str("");
      ss << "Day_" << day;
      TLegend l28(0.3, 0.5, 0.5, 0.7);
      l28.AddEntry(hS2zc_450_500, ss.str().c_str(), "");
      l28.Draw();

      c26->Print(ss.str().c_str());
      c26->SaveAs("May_study/zslice_plot_JR_halfday_May/hS2zc_450_500.gif+50");

     //slice 11

      TCanvas *c29 = new TCanvas("c29", "", 800, 600);
      c29->cd();
      TH1F* hS2zc_500_550 = (TH1F*)f.Get("hS2zc_500_550");
      hS2zc_500_550->GetXaxis()->SetRangeUser(5, 6);
        for (j = 1; j <= 800; j++)
          { if (hS2zc_500_550->GetBinContent(j) > ymax) 
              { ymax = hS2zc_500_550->GetBinContent(j); 
                xmax = j;
              }
          }
        fGausS2->SetRange((xmax*7.0/800.) - 1., (xmax*7.0/800.) + 1.);
        fGausS2->SetParameters(0, ymax);
        fGausS2->SetParameters(1, xmax*7.0/800.);
        fGausS2->SetParameters(2, 0.2/3.);
        hS2zc_500_550->Fit(fGausS2, "RW");
        //getchar();
      meanS2[10] = fGausS2->GetParameter(1);
      eMeanS2[10] = fGausS2->GetParError(1);


      ss.str("");
      ss << "May_study/zslice_plot_JR_halfday_May/hS2zc_500_550_";
      if(day < 10)
      ss << "0";
      ss << day << ".png";
      //c23->Print(ss.str().c_str());
      
      ss.str("");
      ss << "Day_" << day;
      TLegend l29(0.3, 0.5, 0.5, 0.7);
      l29.AddEntry(hS2zc_500_550, ss.str().c_str(), "");
      l29.Draw();

      c29->Print(ss.str().c_str());
      c29->SaveAs("May_study/zslice_plot_JR_halfday_May/hS2zc_500_550.gif+50");

     //slice 12

      TCanvas *c30 = new TCanvas("c30", "", 800, 600);
      c30->cd();
      TH1F* hS2zc_550_600 = (TH1F*)f.Get("hS2zc_550_600");
      hS2zc_550_600->GetXaxis()->SetRangeUser(5, 6);
        for (j = 1; j <= 800; j++)
          { if (hS2zc_550_600->GetBinContent(j) > ymax) 
              { ymax = hS2zc_550_600->GetBinContent(j); 
                xmax = j;
              }
          }
        fGausS2->SetRange((xmax*7.0/800.) - 1., (xmax*7.0/800.) + 1.);
        fGausS2->SetParameters(0, ymax);
        fGausS2->SetParameters(1, xmax*7.0/800.);
        fGausS2->SetParameters(2, 0.2/3.);
        hS2zc_550_600->Fit(fGausS2, "RW");
        //getchar();
      meanS2[11] = fGausS2->GetParameter(1);
      eMeanS2[11] = fGausS2->GetParError(1);


      ss.str("");
      ss << "May_study/zslice_plot_JR_halfday_May/hS2zc_550_600_";
      if(day < 10)
      ss << "0";
      ss << day << ".png";
      //c24->Print(ss.str().c_str());
      
      ss.str("");
      ss << "Day_" << day;
      TLegend l30(0.3, 0.5, 0.5, 0.7);
      l30.AddEntry(hS2zc_550_600, ss.str().c_str(), "");
      l30.Draw();

      c30->Print(ss.str().c_str());
      c30->SaveAs("May_study/zslice_plot_JR_halfday_May/hS2zc_550_600.gif+50");

      //slice 13

      TCanvas *c31 = new TCanvas("c31", "", 800, 600);
      c31->cd();
      TH1F* hS2zc_600_650 = (TH1F*)f.Get("hS2zc_600_650");
      hS2zc_600_650->GetXaxis()->SetRangeUser(5, 6);
        for (j = 1; j <= 800; j++)
          { if (hS2zc_600_650->GetBinContent(j) > ymax) 
              { ymax = hS2zc_600_650->GetBinContent(j); 
                xmax = j;
              }
          }
        fGausS2->SetRange((xmax*7.0/800.) - 1., (xmax*7.0/800.) + 1.);
        fGausS2->SetParameters(0, ymax);
        fGausS2->SetParameters(1, xmax*7.0/800.);
        fGausS2->SetParameters(2, 0.2/3.);
        hS2zc_600_650->Fit(fGausS2, "RW");
        //getchar();
      meanS2[12] = fGausS2->GetParameter(1);
      eMeanS2[12] = fGausS2->GetParError(1);


      ss.str("");
      ss << "May_study/zslice_plot_JR_halfday_May/hS2zc_600_650_";
      if(day < 10)
      ss << "0";
      ss << day << ".png";
      //c23->Print(ss.str().c_str());
      
      ss.str("");
      ss << "Day_" << day;
      TLegend l31(0.3, 0.5, 0.5, 0.7);
      l31.AddEntry(hS2zc_600_650, ss.str().c_str(), "");
      l31.Draw();

      c31->Print(ss.str().c_str());
      c31->SaveAs("May_study/zslice_plot_JR_halfday_May/hS2zc_600_650.gif+50");

     //slice 14

      TCanvas *c32 = new TCanvas("c32", "", 800, 600);
      c32->cd();
      TH1F* hS2zc_650_700 = (TH1F*)f.Get("hS2zc_650_700");
      hS2zc_650_700->GetXaxis()->SetRangeUser(5, 6);
        for (j = 1; j <= 800; j++)
          { if (hS2zc_650_700->GetBinContent(j) > ymax) 
              { ymax = hS2zc_650_700->GetBinContent(j); 
                xmax = j;
              }
          }
        fGausS2->SetRange((xmax*7.0/800.) - 1., (xmax*7.0/800.) + 1.);
        fGausS2->SetParameters(0, ymax);
        fGausS2->SetParameters(1, xmax*7.0/800.);
        fGausS2->SetParameters(2, 0.2/3.);
        hS2zc_650_700->Fit(fGausS2, "RW");
        //hS2zc_650_700->Draw();
        //getchar();
      meanS2[13] = fGausS2->GetParameter(1);
      eMeanS2[13] = fGausS2->GetParError(1);


      ss.str("");
      ss << "May_study/zslice_plot_JR_halfday_May/hS2zc_650_700_";
      if(day < 10)
      ss << "0";
      ss << day << ".png";
      //c24->Print(ss.str().c_str());
      
      ss.str("");
      ss << "Day_" << day;
      TLegend l32(0.3, 0.5, 0.5, 0.7);
      l32.AddEntry(hS2zc_650_700, ss.str().c_str(), "");
      l32.Draw();

      c32->Print(ss.str().c_str());
      c32->SaveAs("May_study/zslice_plot_JR_halfday_May/hS2zc_650_700.gif+50");

       //slice 15

      TCanvas *c33 = new TCanvas("c33", "", 800, 600);
      c33->cd();
      TH1F* hS2zc_700_750 = (TH1F*)f.Get("hS2zc_700_750");
      hS2zc_700_750->GetXaxis()->SetRangeUser(5, 6);
        for (j = 1; j <= 800; j++)
          { if (hS2zc_700_750->GetBinContent(j) > ymax) 
              { ymax = hS2zc_700_750->GetBinContent(j); 
                xmax = j;
              }
          }
        fGausS2->SetRange((xmax*7.0/800.) - 1., (xmax*7.0/800.) + 1.);
        fGausS2->SetParameters(0, ymax);
        fGausS2->SetParameters(1, xmax*7.0/800.);
        fGausS2->SetParameters(2, 0.2/3.);
        hS2zc_700_750->Fit(fGausS2, "RW");
        //hS2zc_700_750->Draw();
        //getchar();
      meanS2[14] = fGausS2->GetParameter(1);
      eMeanS2[14] = fGausS2->GetParError(1);


      ss.str("");
      ss << "May_study/zslice_plot_JR_halfday_May/hS2zc_700_750_";
      if(day < 10)
      ss << "0";
      ss << day << ".png";
      //c23->Print(ss.str().c_str());
      
      ss.str("");
      ss << "Day_" << day;
      TLegend l33(0.3, 0.5, 0.5, 0.7);
      l33.AddEntry(hS2zc_700_750, ss.str().c_str(), "");
      l33.Draw();

      c33->Print(ss.str().c_str());
      c33->SaveAs("May_study/zslice_plot_JR_halfday_May/hS2zc_700_750.gif+50");

     //slice 16

      TCanvas *c34 = new TCanvas("c34", "", 800, 600);
      c34->cd();
      TH1F* hS2zc_750_800 = (TH1F*)f.Get("hS2zc_750_800");
      hS2zc_750_800->GetXaxis()->SetRangeUser(5, 6);
        for (j = 1; j <= 800; j++)
          { if (hS2zc_750_800->GetBinContent(j) > ymax) 
              { ymax = hS2zc_750_800->GetBinContent(j); 
                xmax = j;
              }
          }
        fGausS2->SetRange((xmax*7.0/800.) - 1., (xmax*7.0/800.) + 1.);
        fGausS2->SetParameters(0, ymax);
        fGausS2->SetParameters(1, xmax*7.0/800.);
        fGausS2->SetParameters(2, 0.2/3.);
        hS2zc_750_800->Fit(fGausS2, "RW");
       //hS2zc_750_800->Draw();
        //getchar();
      meanS2[15] = fGausS2->GetParameter(1);
      eMeanS2[15] = fGausS2->GetParError(1);


      ss.str("");
      ss << "May_study/zslice_plot_JR_halfday_May/hS2zc_750_800_";
      if(day < 10)
      ss << "0";
      ss << day << ".png";
      //c24->Print(ss.str().c_str());
      
      ss.str("");
      ss << "Day_" << day;
      TLegend l34(0.3, 0.5, 0.5, 0.7);
      l34.AddEntry(hS2zc_750_800, ss.str().c_str(), "");
      l34.Draw();

      c34->Print(ss.str().c_str());
      c34->SaveAs("May_study/zslice_plot_JR_halfday_May/hS2zc_750_800.gif+50");

      //slice 17

      TCanvas *c35 = new TCanvas("c35", "", 800, 600);
      c35->cd();
      TH1F* hS2zc_800_850 = (TH1F*)f.Get("hS2zc_800_850");
      hS2zc_800_850->GetXaxis()->SetRangeUser(5, 6);
        for (j = 1; j <= 800; j++)
          { if (hS2zc_800_850->GetBinContent(j) > ymax) 
              { ymax = hS2zc_800_850->GetBinContent(j); 
                xmax = j;
              }
          }
        fGausS2->SetRange((xmax*7.0/800.) - 1., (xmax*7.0/800.) + 1.);
        fGausS2->SetParameters(0, ymax);
        fGausS2->SetParameters(1, xmax*7.0/800.);
        fGausS2->SetParameters(2, 0.2/3.);
        hS2zc_800_850->Fit(fGausS2, "RW");
        //hS2zc_800_850->Draw();
        //getchar();
      meanS2[16] = fGausS2->GetParameter(1);
      eMeanS2[16] = fGausS2->GetParError(1);


      ss.str("");
      ss << "May_study/zslice_plot_JR_halfday_May/hS2zc_800_850_";
      if(day < 10)
      ss << "0";
      ss << day << ".png";
      //c23->Print(ss.str().c_str());
      
      ss.str("");
      ss << "Day_" << day;
      TLegend l35(0.3, 0.5, 0.5, 0.7);
      l35.AddEntry(hS2zc_800_850, ss.str().c_str(), "");
      l35.Draw();

      c35->Print(ss.str().c_str());
      c35->SaveAs("May_study/zslice_plot_JR_halfday_May/hS2zc_800_850.gif+50");

      //slice 18

      TCanvas *c36 = new TCanvas("c36", "", 800, 600);
      c36->cd();
      TH1F* hS2zc_850_900 = (TH1F*)f.Get("hS2zc_850_900");
      hS2zc_850_900->GetXaxis()->SetRangeUser(5, 6);
        for (j = 1; j <= 800; j++)
          { if (hS2zc_850_900->GetBinContent(j) > ymax) 
              { ymax = hS2zc_850_900->GetBinContent(j); 
                xmax = j;
              }
          }
        fGausS2->SetRange((xmax*7.0/800.) - 1., (xmax*7.0/800.) + 1.);
        fGausS2->SetParameters(0, ymax);
        fGausS2->SetParameters(1, xmax*7.0/800.);
        fGausS2->SetParameters(2, 0.2/3.);
        hS2zc_850_900->Fit(fGausS2, "RW");
        //hS2zc_850_900->Draw();
        //getchar();
      meanS2[17] = fGausS2->GetParameter(1);
      eMeanS2[17] = fGausS2->GetParError(1);


      ss.str("");
      ss << "May_study/zslice_plot_JR_halfday_May/hS2zc_850_900_";
      if(day < 10)
      ss << "0";
      ss << day << ".png";
      //c24->Print(ss.str().c_str());
      
      ss.str("");
      ss << "Day_" << day;
      TLegend l36(0.3, 0.5, 0.5, 0.7);
      l36.AddEntry(hS2zc_850_900, ss.str().c_str(), "");
      l36.Draw();

      c36->Print(ss.str().c_str());
      c36->SaveAs("May_study/zslice_plot_JR_halfday_May/hS2zc_850_900.gif+50");

     //slice 19

      TCanvas *c37 = new TCanvas("c37", "", 800, 600);
      c37->cd();
      TH1F* hS2zc_900_950 = (TH1F*)f.Get("hS2zc_900_950");
      hS2zc_900_950->GetXaxis()->SetRangeUser(5, 6);
        for (j = 1; j <= 800; j++)
          { if (hS2zc_900_950->GetBinContent(j) > ymax) 
              { ymax = hS2zc_900_950->GetBinContent(j); 
                xmax = j;
              }
          }
        fGausS2->SetRange((xmax*7.0/800.) - 1., (xmax*7.0/800.) + 1.);
        fGausS2->SetParameters(0, ymax);
        fGausS2->SetParameters(1, xmax*7.0/800.);
        fGausS2->SetParameters(2, 0.2/3.);
        hS2zc_900_950->Fit(fGausS2, "RW");
        //hS2zc_900_950->Draw();
        //getchar();
      meanS2[18] = fGausS2->GetParameter(1);
      eMeanS2[18] = fGausS2->GetParError(1);


      ss.str("");
      ss << "May_study/zslice_plot_JR_halfday_May/hS2zc_900_950_";
      if(day < 10)
      ss << "0";
      ss << day << ".png";
      //c23->Print(ss.str().c_str());
      
      ss.str("");
      ss << "Day_" << day;
      TLegend l37(0.3, 0.5, 0.5, 0.7);
      l37.AddEntry(hS2zc_900_950, ss.str().c_str(), "");
      l37.Draw();

      c37->Print(ss.str().c_str());
      c37->SaveAs("May_study/zslice_plot_JR_halfday_May/hS2zc_900_950.gif+50");

      //slice 20

      TCanvas *c38 = new TCanvas("c38", "", 800, 600);
      c38->cd();
      TH1F* hS2zc_950_1000 = (TH1F*)f.Get("hS2zc_950_1000");
      hS2zc_950_1000->GetXaxis()->SetRangeUser(5, 6);
        for (j = 1; j <= 800; j++)
          { if (hS2zc_950_1000->GetBinContent(j) > ymax) 
              { ymax = hS2zc_950_1000->GetBinContent(j); 
                xmax = j;
              }
          }
        fGausS2->SetRange((xmax*7.0/800.) - 1., (xmax*7.0/800.) + 1.);
        fGausS2->SetParameters(0, ymax);
        fGausS2->SetParameters(1, xmax*7.0/800.);
        fGausS2->SetParameters(2, 0.2/3.);
        hS2zc_950_1000->Fit(fGausS2, "RW");
        //hS2zc_950_1000->Draw();
        //getchar();
      meanS2[19] = fGausS2->GetParameter(1);
      eMeanS2[19] = fGausS2->GetParError(1);


      ss.str("");
      ss << "May_study/zslice_plot_JR_halfday_May/hS2zc_950_1000_";
      if(day < 10)
      ss << "0";
      ss << day << ".png";
      //c24->Print(ss.str().c_str());
      
      ss.str("");
      ss << "Day_" << day;
      TLegend l38(0.3, 0.5, 0.5, 0.7);
      l38.AddEntry(hS2zc_950_1000, ss.str().c_str(), "");
      l38.Draw();

      c38->Print(ss.str().c_str());
      c38->SaveAs("May_study/zslice_plot_JR_halfday_May/hS2zc_950_1000.gif+50");

      //slice 21

      TCanvas *c39 = new TCanvas("c39", "", 800, 600);
      c39->cd();
      TH1F* hS2zc_1000_1050 = (TH1F*)f.Get("hS2zc_1000_1050");
      hS2zc_1000_1050->GetXaxis()->SetRangeUser(5, 6);
        for (j = 1; j <= 800; j++)
          { if (hS2zc_1000_1050->GetBinContent(j) > ymax) 
              { ymax = hS2zc_1000_1050->GetBinContent(j); 
                xmax = j;
              }
          }
        fGausS2->SetRange((xmax*7.0/800.) - 1., (xmax*7.0/800.) + 1.);
        fGausS2->SetParameters(0, ymax);
        fGausS2->SetParameters(1, xmax*7.0/800.);
        fGausS2->SetParameters(2, 0.2/3.);
        hS2zc_1000_1050->Fit(fGausS2, "RW");
        //hS2zc_1000_1050->Draw();
        //getchar();
      meanS2[20] = fGausS2->GetParameter(1);
      eMeanS2[20] = fGausS2->GetParError(1);


      ss.str("");
      ss << "May_study/zslice_plot_JR_halfday_May/hS2zc_1000_1050_";
      if(day < 10)
      ss << "0";
      ss << day << ".png";
      c24->Print(ss.str().c_str());
      
      ss.str("");
      ss << "Day_" << day;
      TLegend l39(0.3, 0.5, 0.5, 0.7);
      l39.AddEntry(hS2zc_1000_1050, ss.str().c_str(), "");
      l39.Draw();

      c39->Print(ss.str().c_str());
      c39->SaveAs("May_study/zslice_plot_JR_halfday_May/hS2zc_1000_1050.gif+50");

      //slice 22

      TCanvas *c40 = new TCanvas("c40", "", 800, 600);
      c40->cd();
      TH1F* hS2zc_1050_1100 = (TH1F*)f.Get("hS2zc_1050_1100");
      hS2zc_1050_1100->GetXaxis()->SetRangeUser(5, 6);
        for (j = 1; j <= 800; j++)
          { if (hS2zc_1050_1100->GetBinContent(j) > ymax) 
              { ymax = hS2zc_1050_1100->GetBinContent(j); 
                xmax = j;
              }
          }
        fGausS2->SetRange((xmax*7.0/800.) - 1., (xmax*7.0/800.) + 1.);
        fGausS2->SetParameters(0, ymax);
        fGausS2->SetParameters(1, xmax*7.0/800.);
        fGausS2->SetParameters(2, 0.2/3.);
        hS2zc_1050_1100->Fit(fGausS2, "RW");
        //hS2zc_1050_1100->Draw();
        //getchar();
      meanS2[21] = fGausS2->GetParameter(1);
      eMeanS2[21] = fGausS2->GetParError(1);


      ss.str("");
      ss << "May_study/zslice_plot_JR_halfday_May/hS2zc_1050_1100_";
      if(day < 10)
      ss << "0";
      ss << day << ".png";
      //c24->Print(ss.str().c_str());
      
      ss.str("");
      ss << "Day_" << day;
      TLegend l40(0.3, 0.5, 0.5, 0.7);
      l40.AddEntry(hS2zc_1050_1100, ss.str().c_str(), "");
      l40.Draw();

      c40->Print(ss.str().c_str());
      c40->SaveAs("May_study/zslice_plot_JR_halfday_May/hS2zc_1050_1100.gif+50");

       //slice 23

      TCanvas *c41 = new TCanvas("c41", "", 800, 600);
      c41->cd();
      TH1F* hS2zc_1100_1150 = (TH1F*)f.Get("hS2zc_1100_1150");
      hS2zc_1100_1150->GetXaxis()->SetRangeUser(5, 6);
        for (j = 1; j <= 800; j++)
          { if (hS2zc_1100_1150->GetBinContent(j) > ymax) 
              { ymax = hS2zc_1100_1150->GetBinContent(j); 
                xmax = j;
              }
          }
        fGausS2->SetRange((xmax*7.0/800.) - 1., (xmax*7.0/800.) + 1.);
        fGausS2->SetParameters(0, ymax);
        fGausS2->SetParameters(1, xmax*7.0/800.);
        fGausS2->SetParameters(2, 0.2/3.);
        hS2zc_1100_1150->Fit(fGausS2, "RW");
        // hS2zc_1100_1150->Draw();
        //getchar();
      meanS2[22] = fGausS2->GetParameter(1);
      eMeanS2[22] = fGausS2->GetParError(1);


      ss.str("");
      ss << "May_study/zslice_plot_JR_halfday_May/hS2zc_1100_1150_";
      if(day < 10)
      ss << "0";
      ss << day << ".png";
      //c24->Print(ss.str().c_str());
      
      ss.str("");
      ss << "Day_" << day;
      TLegend l41(0.3, 0.5, 0.5, 0.7);
      l41.AddEntry(hS2zc_1100_1150, ss.str().c_str(), "");
      l41.Draw();

      c41->Print(ss.str().c_str());
      c41->SaveAs("May_study/zslice_plot_JR_halfday_May/hS2zc_1100_1150.gif+50");

      //slice 24

      TCanvas *c42 = new TCanvas("c42", "", 800, 600);
      c42->cd();
      TH1F* hS2zc_1150_1200 = (TH1F*)f.Get("hS2zc_1150_1200");
      hS2zc_1150_1200->GetXaxis()->SetRangeUser(5, 6);
        for (j = 1; j <= 800; j++)
          { if (hS2zc_1150_1200->GetBinContent(j) > ymax) 
              { ymax = hS2zc_1150_1200->GetBinContent(j); 
                xmax = j;
              }
          }
        fGausS2->SetRange((xmax*7.0/800.) - 1., (xmax*7.0/800.) + 1.);
        fGausS2->SetParameters(0, ymax);
        fGausS2->SetParameters(1, xmax*7.0/800.);
        fGausS2->SetParameters(2, 0.2/3.);
        hS2zc_1150_1200->Fit(fGausS2, "RW");
        //hS2zc_1150_1200->Draw();
        //getchar();
      meanS2[23] = fGausS2->GetParameter(1);
      eMeanS2[23] = fGausS2->GetParError(1);


      ss.str("");
      ss << "May_study/zslice_plot_JR_halfday_May/hS2zc_1150_1200_";
      if(day < 10)
      ss << "0";
      ss << day << ".png";
      //c24->Print(ss.str().c_str());
      
      ss.str("");
      ss << "Day_" << day;
      TLegend l42(0.3, 0.5, 0.5, 0.7);
      l42.AddEntry(hS2zc_1150_1200, ss.str().c_str(), "");
      l42.Draw();

      c42->Print(ss.str().c_str());
      c42->SaveAs("May_study/zslice_plot_JR_halfday_May/hS2zc_1150_1200.gif+50");

      //slice 25

      TCanvas *c43 = new TCanvas("c43", "", 800, 600);
      c43->cd();
      TH1F* hS2zc_1200_1250 = (TH1F*)f.Get("hS2zc_1200_1250");
      hS2zc_1200_1250->GetXaxis()->SetRangeUser(5, 6);
        for (j = 1; j <= 800; j++)
          { if (hS2zc_1200_1250->GetBinContent(j) > ymax) 
              { ymax = hS2zc_1200_1250->GetBinContent(j); 
                xmax = j;
              }
          }
        fGausS2->SetRange((xmax*7.0/800.) - 1., (xmax*7.0/800.) + 1.);
        fGausS2->SetParameters(0, ymax);
        fGausS2->SetParameters(1, xmax*7.0/800.);
        fGausS2->SetParameters(2, 0.2/3.); 
        hS2zc_1200_1250->Fit(fGausS2, "RW");
        //hS2zc_1200_1250->Draw();
        //getchar();
      meanS2[24] = fGausS2->GetParameter(1);
      eMeanS2[24] = fGausS2->GetParError(1);


      ss.str("");
      ss << "May_study/zslice_plot_JR_halfday_May/hS2zc_1200_1250_";
      if(day < 10)
      ss << "0";
      ss << day << ".png";
      //c24->Print(ss.str().c_str());
      
      ss.str("");
      ss << "Day_" << day;
      TLegend l43(0.3, 0.5, 0.5, 0.7);
      l43.AddEntry(hS2zc_1200_1250, ss.str().c_str(), "");
      l43.Draw();

      c43->Print(ss.str().c_str());
      c43->SaveAs("May_study/zslice_plot_JR_halfday_May/hS2zc_1200_1250.gif+50");

      //slice 26

      TCanvas *c44 = new TCanvas("c44", "", 800, 600);
      c44->cd();
      TH1F* hS2zc_1250_1300 = (TH1F*)f.Get("hS2zc_1250_1300");
      hS2zc_1250_1300->GetXaxis()->SetRangeUser(5, 6);
        for (j = 1; j <= 800; j++)
          { if (hS2zc_1250_1300->GetBinContent(j) > ymax) 
              { ymax = hS2zc_1250_1300->GetBinContent(j); 
                xmax = j;
              }
          }
        fGausS2->SetRange((xmax*7.0/800.) - 1., (xmax*7.0/800.) + 1.);
        fGausS2->SetParameters(0, ymax);
        fGausS2->SetParameters(1, xmax*7.0/800.);
        fGausS2->SetParameters(2, 0.2/3.);
        hS2zc_1250_1300->Fit(fGausS2, "RW");
        //hS2zc_1250_1300->Draw();
        //getchar();
      meanS2[25] = fGausS2->GetParameter(1);
      eMeanS2[25] = fGausS2->GetParError(1);


      ss.str("");
      ss << "May_study/zslice_plot_JR_halfday_May/hS2zc_1250_1300_";
      if(day < 10)
      ss << "0";
      ss << day << ".png";
      //c24->Print(ss.str().c_str());
      
      ss.str("");
      ss << "Day_" << day;
      TLegend l44(0.3, 0.5, 0.5, 0.7);
      l44.AddEntry(hS2zc_1250_1300, ss.str().c_str(), "");
      l44.Draw();

      c44->Print(ss.str().c_str());
      c44->SaveAs("May_study/zslice_plot_JR_halfday_May/hS2zc_1250_1300.gif+50");

      //slice last

      TCanvas *cl = new TCanvas("cl", "", 800, 600);
      cl->cd();
      TH1F* hS2zc_1300_1350 = (TH1F*)f.Get("hS2zc_1300_1350");
      hS2zc_1300_1350->GetXaxis()->SetRangeUser(5, 6);
        for (j = 1; j <= 800; j++)
          { if (hS2zc_1300_1350->GetBinContent(j) > ymax) 
              { ymax = hS2zc_1300_1350->GetBinContent(j); 
                xmax = j;
              }
          }
        fGausS2->SetRange((xmax*7.0/800.) - 1., (xmax*7.0/800.) + 1.);
        fGausS2->SetParameters(0, ymax);
        fGausS2->SetParameters(1, xmax*7.0/800.);
        fGausS2->SetParameters(2, 0.2/3.);
        hS2zc_1300_1350->Fit(fGausS2, "RW");
        //hS2zc_1300_1350->Draw();
        //getchar();
      meanS2[26] = fGausS2->GetParameter(1);
      eMeanS2[26] = fGausS2->GetParError(1);


      ss.str("");
      ss << "May_study/zslice_plot_JR_halfday_May/hS2zc_1300_1350_";
      if(day < 10)
      ss << "0";
      ss << day << ".png";
      //cl->Print(ss.str().c_str());
      
      ss.str("");
      ss << "Day_" << day;
      TLegend ll(0.3, 0.5, 0.5, 0.7);
      ll.AddEntry(hS2zc_1300_1350, ss.str().c_str(), "");
      ll.Draw();

      cl->Print(ss.str().c_str());
      cl->SaveAs("May_study/zslice_plot_JR_halfday_May/hS2zc_1300_1350.gif+50");




      c5->cd();
      //TH1F* hS2zc_gf = (TH1F*)f.Get("hS2zc_gf");
      TH1F* h1    = new TH1F("h1", " log10(S2 [phd]); Zc", 27, 5., 145.);

      for(int k = 0; k <= 26; k++)
      {
        float thisX = h1->GetXaxis()->GetBinCenter(k);
        //float thisXe = h1->GetXaxis()->GetBinWidth(k);

        //float thisX = hS2zc->GetXaxis()->GetBinCenter(k);
        //float thisXe = hS2zc->GetXaxis()->GetBinWidth(k);

      cout << k+1 << "  Mean = " << meanS2[k] << "    Error = " << eMeanS2[k]  << endl;
      myfilegfit << k+1 << "  Mean = " << meanS2[k] << "    Error = " << eMeanS2[k]  << endl;

      //c5->SaveAs("hS2zc_zslice.gif+50");

      float thisXg[27] = {2.5, 7.5, 12.5, 17.5, 22.5, 27.5, 32.5, 37.5, 42.5, 47.5, 52.5, 57.5, 62.5, 67.5, 72.5, 77.5,
                            82.5, 87.5, 92.5, 97.5, 102.5, 107.5, 112.5, 117.5, 122.5, 127.5, 132.5};
     
      gMeans->SetPoint(k, thisXg[k], meanS2[k]);

      //gMeans->SetPoint(k, thisX, meanS2[k]);
      gMeans->SetPointError(k, 0., eMeanS2[k]);
      gMeans->SetMarkerSize(0.5);
      //gMeans->SetPointError(k-1, thisXe, eMeanS2[k]);
      gMeans->Draw("AP");

       }
       //c5->cd();
       TF1* linearfit3 = new TF1("linearfit3", "[0] + [j]*x", 50., 1350.);
       linearfit3->SetLineColor(2);
       linearfit3->SetLineWidth(1);
       //gMeans->Draw("AP");
       //gMeans->Fit("pol1");
       gMeans->Fit(linearfit3, "R");
       //gMeans->Fit(linearfit, "R");
       //h1->Draw();
       //h1->Fit(linearfit3, "R");

      ss.str("");
      ss << "May_study/zslice_plot_JR_halfday_May/gMeans";
      if(day < 10)
      ss << "0";
      ss << day << ".png";
      c5->Print(ss.str().c_str());


      // Madan's method for gaussian fits
      float al_g = -1/(log(10)*linearfit3->GetParameter(1));
      float d_g = linearfit2->GetParameter(1);
      float elt_g = al_g * d_g;
      gXe131mGausFits->SetPoint(i, float(day), elt_g);
      float err_al_g = linearfit3->GetParError(1);
      float alerr_g = err_al_g/((log(10)*linearfit3->GetParameter(1)*linearfit3->GetParameter(1)));
      float derr_g = linearfit2->GetParError(1);
      float elterr_g = elt_g * (sqrt ( (alerr_g*alerr_g)/(al_g*al_g) + (derr_g*derr_g)/(d_g*d_g) ));
      gXe131mGausFits->SetPointError(i, 0.5, elterr_g);

      myfileg << day << " "<< elt_g << " " << elterr_g << endl;
      
      ss.str("");
      ss << "Half_day_" << day;
      TLegend l5(0.7, 0.8, 0.8, 0.7);
      l5.AddEntry(gMeans, ss.str().c_str(), "");
      l5.Draw();

      //c5->Print(ss.str().c_str());
      c5->SaveAs("May_study/zslice_plot_JR_halfday_May/gMeans.gif+50");
      c5->WaitPrimitive();

      ++i;

    }

/*      //ss.str("");
      //ss << "Electron_Lifetime";
      //ss << ".txt";
      //TFile myfile (ss.str().c_str(), "WRITE");
      TFile myfile (Electron_Lifetime.txt, "WRITE");
      if(!f.IsOpen())
        continue;

        int i = 0;
  for(int day = 1; day <= 6; ++day)
    {
      cout << "SDSMT: Electron Lifetime = " << elt[day] << " Error Electron Lifetime = " << elterr[day] << endl;
    }
    myfile.close();*/





  c4->cd();
  gXe131m->SetMarkerStyle(kFullCircle);
  gXe131m->Draw("AP");
  gXe131m->GetXaxis()->SetTitle("Day");
  gXe131m->GetYaxis()->SetTitle("Lifetime [#mus]");


/*  gXe131m_->SetMarkerStyle(kFullCircle);
  gXe131m_->Draw("AP");
  gXe131m_->GetXaxis()->SetTitle("Day");
  gXe131m_->GetYaxis()->SetTitle("Lifetime [#mus]");*/

/*  TLegend lg(0.3, 0.5, 0.5, 0.7);
  lg.AddEntry(gXe131m, "Method2: SDSMT", "");
  //lg.AddEntry(gXe131m_, "Method1: other", "");
  lg.Draw();*/

  c4->Print("May_study/zslice_plot_JR_halfday_May/ltXe131m.png");
  //gXe131m->SaveAs("ltXe131m.root");
/*
  TFile *outfile = new TFile("ltXe131m.root", "RECREATE");
  gXe131m->Write();
  outfile->Close();*/

  //gXe131m->Write();
  //outfile->Close();
  TCanvas *cg = new TCanvas("cg", "", 800, 600);

  gXe131mGausFits->SetMarkerStyle(kFullCircle);
  gXe131mGausFits->Draw("AP");
  gXe131mGausFits->GetXaxis()->SetTitle("April Day");
  gXe131mGausFits->GetYaxis()->SetTitle("Lifetime [#mus]");
  cg->Print("May_study/zslice_plot_JR_halfday_May/ltXe131mGausFits_23.png");

  TCanvas *cAll = new TCanvas("cAll", "", 800, 600);
  auto frame = cAll->DrawFrame(0.5, 700, 30.5, 1300);
  frame->GetXaxis()->SetTitle("April Day");
  frame->GetYaxis()->SetTitle("Lifetime [#mus]");
  gXe131m->SetMarkerColor(kBlue);
  gXe131mGausFits->SetMarkerColor(kBlack);
  //gXe131mMedians->SetMarkerColor(kMagenta);
  gXe131mGausFits->Draw("AP");
  gXe131m->Draw("sameP");
  //gXe131mMedians->Draw("sameP");
  TLegend *legAll = new TLegend(0.2, 0.6, 0.5, 0.8);
  legAll->SetBorderSize(0);
  legAll->SetFillStyle(0);
  legAll->AddEntry(gXe131m, "using mean of linear fit to log10(S2) Vs Zc ", "LP");
  legAll->AddEntry(gXe131m, " (2D hist, 50 < Zc [mm] < 1300) ", "");
  legAll->AddEntry(gXe131mGausFits, "using Gaus mean of Fit to log10(S2)", "LP");
  legAll->AddEntry(gXe131mGausFits, "for each Zc slices (Zc slices = 50 [mm]) ", "");
  //legAll->AddEntry(gXe131mMedians, "Fit to log10(S2) medians", "LP");
  legAll->Draw();
  cAll->Print("May_study/zslice_plot_JR_halfday_May/ltXe131mAllMethods.png");


  myfile.close();
  myfileg.close();
  myfilegfit.close();


   //delete myfile;

}

