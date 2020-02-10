{
    TCanvas* c = new TCanvas("c","c",1);
    TFile* f1    = TFile::Open("root/processed/Halfmoon_outter_tracker_6inch_VPX28441_WNo5_chipNo17/MOS_HPK_2015_CV_1kHz_20200207.root");
    TFile* f10   = TFile::Open("root/processed/Halfmoon_outter_tracker_6inch_VPX28441_WNo5_chipNo17/MOS_HPK_2015_CV_10kHz_20200207.root");
    TFile* f100  = TFile::Open("root/processed/Halfmoon_outter_tracker_6inch_VPX28441_WNo5_chipNo17/MOS_HPK_2015_CV_100kHz_20200207.root");
    TFile* f1000 = TFile::Open("root/processed/Halfmoon_outter_tracker_6inch_VPX28441_WNo5_chipNo17/MOS_HPK_2015_CV_1000kHz_20200207.root");

    TGraph* gr1    = (TGraph*)f1->Get("Graph;3");
    TGraph* gr10   = (TGraph*)f10->Get("Graph;3");
    TGraph* gr100  = (TGraph*)f100->Get("Graph;3");
    TGraph* gr1000 = (TGraph*)f1000->Get("Graph;3");

    gr1->SetLineColor(kBlue);
    gr10->SetLineColor(kRed);
    gr100->SetLineColor(kGreen);
    gr1000->SetLineColor(kOrange);
    gr1->SetMarkerColor(kBlue);
    gr10->SetMarkerColor(kRed);
    gr100->SetMarkerColor(kGreen);
    gr1000->SetMarkerColor(kOrange);

    TMultiGraph* mgr = new TMultiGraph();
    mgr->Add(gr1);
    mgr->Add(gr10);
    mgr->Add(gr100);
    mgr->Add(gr1000);
    if(isMOS) {
        mgr->SetTitle("MOS_HPK_2015;V [V];C [pF]");
    }else {
        mgr->SetTitle("Diode;V [V];1/C^{2} [F^{-2}]");
    }
    mgr->GetXaxis()->SetTitleSize(0.046);
    mgr->GetYaxis()->SetTitleSize(0.046);
    mgr->GetYaxis()->SetTitleOffset(1.00);

    auto* legend = new TLegend(0.6,0.6,0.89,0.89);
    legend->AddEntry(gr1,"1kHz","lp");
    legend->AddEntry(gr10,"10kHz","lp");
    legend->AddEntry(gr100,"100kHz","lp");
    legend->AddEntry(gr1000,"1MHz","lp");
    legend->SetBorderSize(0);

    mgr->Draw("APL");
    legend->Draw();
}
