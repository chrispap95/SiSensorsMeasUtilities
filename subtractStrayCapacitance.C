void subtractStrayCapacitance(TString signal, TString bkg, bool isMOS) {
    TCanvas* c = new TCanvas("c","c",1);
    TFile* f_s = TFile::Open(signal);
    TFile* f_b = TFile::Open(bkg);

    Int_t slash = signal.First('/');
    signal.Remove(0,slash+1);
    TString outDir = signal;
    slash = outDir.First('/');
    outDir.Remove(slash,outDir.Length());
    gSystem->Exec("mkdir Plots/"+outDir);
    slash = bkg.First('/');
    bkg.Remove(0,slash+1);
    TString outname = "root/processed/"+signal;
    TFile* fout = new TFile(outname, "RECREATE");

    TGraph* gr_s = (TGraph*)f_s->Get("graph");
    TGraph* gr_b = (TGraph*)f_b->Get("graph");
    int n = gr_s->GetN();
    TGraph* gr_s_corr = new TGraph(n);
    TGraph* gr_invCsqrd = new TGraph(n);

    if (n != gr_s->GetN()) {
        cerr << "signal and background do not contain same number of points.\n";
        return;
    }
    for (int i = 0; i < n; ++i) {
        Double_t x_s, y_s, x_b, y_b;
        // Scale graphs
        gr_s->GetPoint(i,x_s,y_s);
        gr_b->GetPoint(i,x_b,y_b);
        if (isMOS) {
            gr_s->SetPoint(i,-x_s,y_s*pow(10,12));
            gr_b->SetPoint(i,-x_b,y_b*pow(10,12));
            gr_s_corr->SetPoint(i,-x_s,(y_s-y_b)*pow(10,12));
        } else {
            gr_s_corr->SetPoint(i,x_s,y_s-y_b);
            gr_invCsqrd->SetPoint(i,x_s,pow(y_s-y_b,-2));
        }
    }

    TString capacitanceUnits = "[F]";
    if (isMOS) capacitanceUnits = "[pF]";

    slash = bkg.First('/');
    bkg.Remove(0,slash+1);
    Int_t dot = bkg.First('.');
    Int_t len = bkg.Length();
    bkg.Remove(dot,len-dot);
    TString title_b = bkg+";V [V];C "+capacitanceUnits;
    gr_b->SetTitle(title_b);
    gr_b->GetXaxis()->SetTitleSize(0.046);
    gr_b->GetYaxis()->SetTitleSize(0.046);
    gr_b->GetYaxis()->SetTitleOffset(1.00);
    TString pdf_b = "Plots/"+outDir+"/"+bkg+".pdf";
    gr_b->SetMarkerStyle(8);
    gr_b->SetMarkerSize(0.5);
    gr_b->Draw("ACP");
    c->Print(pdf_b);

    slash = signal.First('/');
    signal.Remove(0,slash+1);
    dot = signal.First('.');
    len = signal.Length();
    signal.Remove(dot,len-dot);

    TString title_s = signal+";V [V];C "+capacitanceUnits;
    gr_s->SetTitle(title_s);
    gr_s->GetXaxis()->SetTitleSize(0.046);
    gr_s->GetYaxis()->SetTitleSize(0.046);
    gr_s->GetYaxis()->SetTitleOffset(1.00);
    TString pdf_s = "Plots/"+outDir+"/"+signal+".pdf";
    gr_s->SetMarkerStyle(8);
    gr_s->SetMarkerSize(0.5);
    gr_s->Draw("ACP");
    c->Print(pdf_s);

    TString title_s_corr = signal+" - setup C subtracted;V [V];C "+capacitanceUnits;
    gr_s_corr->SetTitle(title_s_corr);
    gr_s_corr->GetXaxis()->SetTitleSize(0.046);
    gr_s_corr->GetYaxis()->SetTitleSize(0.046);
    gr_s_corr->GetYaxis()->SetTitleOffset(1.00);
    TString pdf_s_corr = "Plots/"+outDir+"/"+signal+"_corr.pdf";
    gr_s_corr->SetMarkerStyle(8);
    gr_s_corr->SetMarkerSize(0.5);
    gr_s_corr->Draw("ACP");
    c->Print(pdf_s_corr);

    if (!isMOS) {
        TString title_invCsqrd = signal+" - setup C subtracted;V [V];1/C^{2} [F^{-2}]";
        gr_invCsqrd->SetTitle(title_invCsqrd);
        gr_invCsqrd->GetXaxis()->SetTitleSize(0.046);
        gr_invCsqrd->GetYaxis()->SetTitleSize(0.046);
        gr_invCsqrd->GetYaxis()->SetTitleOffset(1.00);
        TString pdf_invCsqrd = "Plots/"+outDir+"/"+signal+"_invCsqrd.pdf";
        gr_invCsqrd->SetMarkerStyle(8);
        gr_invCsqrd->SetMarkerSize(0.5);
        gr_invCsqrd->Draw("ACP");
        c->Print(pdf_invCsqrd);
    }

    fout->cd();
    gr_s->Write();
    gr_b->Write();
    gr_s_corr->Write();
    if (!isMOS) {
        gr_invCsqrd->Write();
    }
    fout->Close();
    return;
}
