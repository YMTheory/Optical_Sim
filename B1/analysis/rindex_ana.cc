void rindex_ana()
{
    std::vector<int> vec_rindex;
    vec_rindex.push_back(10);
    vec_rindex.push_back(11);
    vec_rindex.push_back(12);
    vec_rindex.push_back(13);
    vec_rindex.push_back(14);
    vec_rindex.push_back(15);

    string name1 = "/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/point/rindex";
    string name3 = ".root";

    TGraphErrors* gPhoton = new TGraphErrors();
    const int ndata = 6;
    Int_t nbins[ndata] = {50, 50, 50, 50, 50, 50};
    Int_t nlow[ndata]  = {5400, 4400, 3700, 3100, 2600, 2200};
    Int_t nhigh[ndata] = {5800, 4800, 4100, 3500, 3000, 2600};

    for( int i=0; i<vec_rindex.size(); i++ ) {
        string name2 = to_string(vec_rindex[i]);
        string filename = name1 + name2 + name3;
        cout << filename << endl;

        TFile* file = new TFile(filename.c_str());
        TTree* tree = (TTree*)file->Get("photon");
        Int_t m_nphoton;
        tree->SetBranchAddress("nPhoton", &m_nphoton);
        TH1I* temph = new TH1I( "temph", "", nbins[i], nlow[i], nhigh[i] );
        for(int j=0; j<tree->GetEntries(); j++) {
            tree->GetEntry(j);
            temph->Fill(m_nphoton);
        }

        //TF1* gaus = new TF1("f1", "[0]*TMath::Exp(-(x-[1])*(x-[1])/2/[2]/[2])", nlow[i], nhigh[i]);
        //gaus->SetParameter(1, (nlow[i]+nhigh[i])/2.);
        //temph->Fit(gaus, "R0");
        cout << temph->GetMean() << " " << temph->GetStdDev() << endl;
        //gPhoton->SetPoint(i, vec_rindex[i]/10, gaus->GetParameter(1));
        //gPhoton->SetPointError(i, 0, gaus->GetParError(1)/gaus->GetParameter(1));
        gPhoton->SetPoint(i, vec_rindex[i]/10., temph->GetMean());

        delete temph;
        //delete gaus;
        delete tree;
        delete file;
    }

    gPhoton->SetMarkerColor(kBlue+1);
    gPhoton->SetMarkerStyle(20);
    gPhoton->SetLineColor(kBlue+1);
    gPhoton->SetLineWidth(2);
    gPhoton->Draw("APL");
}
