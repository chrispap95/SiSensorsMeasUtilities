void makeGraph(TString filename, TString path) {
    TString outname = filename;
    Int_t dot = outname.First('.');
    Int_t len = outname.Length();
    outname.Remove(dot,len-dot);
    Int_t slash = outname.First('/');
    outname.Remove(0,slash);
    outname = "root/"+path+outname+".root";
    TFile* fout = new TFile(outname,"RECREATE");
    TGraph* graph = new TGraph(filename,"%lg %*s %*s %lg");
    fout->cd();
    graph->Write("graph");
    fout->Close();
    return;
}
