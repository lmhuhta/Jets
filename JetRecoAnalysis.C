int const JetPtCut = 5;
double const jetResolution = 0.4;

// Legend title and energy.
TString sLegTitle = "";
//TString sEnergy = "5.02";
TString sAdditional = "";//"#it{p}_{T,hard} > 3 GeV";

int const gMarkers[2][7] = {{24,25,27,28,30,26,32}, //Open markers
                            {20,21,33,34,29,22,23}}; //Closed markers
int const markerIndex[8] = {0,1,0,1,0,1,0,1};
int gColors[7]={kBlack, kRed, kBlue, kViolet, 14, kRed, kCyan};

TLatex latexRun;

int const nPtBinsE = 5; //modify this to change amount of pt bins drawn


int const nPtBins = 11;
double JetPtBorders[nPtBins] = {5, 10, 20, 30, 40, 60, 80, 100, 150, 500, 1000};

//HISTOGRAMS
TH1D* hJetZ[nPtBins];
TH1D* hJetLogZ[nPtBins];
TH1D* hJetXi[nPtBins];
TH1D* hJetFragZ[nPtBins];
TH1D* hJetFragLogZ[nPtBins];
TH1D* hJetFragXi[nPtBins];
TH1D* hJetN[nPtBins];
TH1D* hJetRap;
TH1D* hJetPseudoRap;
TH1D* hJetPt;

const int NBinsZ=24;

double xbinsZ[NBinsZ]={0, 0.0030, 0.0040, 0.0052, 0.0069, 0.0092, 0.0121, 0.0160, 0.0212, 0.0280, 0.0371, 0.0490, 0.0648, 0.0856, 0.1132, 0.1497, 0.1980, 0.2618, 0.3461, 0.4576, 0.6050, 0.8, 0.9, 1};

int Nbins = 100;
double rapMin=-2; double rapMax=2;
int const NBINS=500;
//double LogBinsX[NBINS+1], LimL=0.1, LimH=500;
//double logBW = (log(LimH)-log(LimL))/NBINS;
//for(int ij=0;ij<=NBINS;ij++) LogBinsX[ij]=LimL*exp(ij*logBW);
int nrapbins = 500;
int nxibins = 100;
double lxi = 0.;
double hxi = 25.;
int nZ = 100;
double zLow = 0.01, zHigh = 1.1;
//double logBinsZ[101];
//double logZ = (log(zHigh)-log(zLow))/nZ;
//for(int ij=0;ij<=nZ;ij++) logBinsZ[ij]=zLow*exp(ij*logZ);
const int bins = NBinsZ-1;

TFile *fIn;

TH1D *getHisto(TFile* fIn, TString sHistoName);
void LoadHistos(TString inFile);
TH1D *CalculateFragFunction(TH1D* ZOrXi, TH1D* nJets);
void drawHistos();

//const char [6] outputfolder = "figs/";

int JetRecoAnalysis(TString inputfile){

	LoadHistos(inputfile);

	for(int hit=0; hit < nPtBinsE; hit++){
	    float pTt1 = JetPtBorders[hit];
	    float pTt2 = JetPtBorders[hit+1];
	    char htit[100], hname[100];

	    sprintf(htit, "D(z), pTt: %3.1f-%3.1f", pTt1, pTt2);
	    sprintf(hname, "hDZ%02d", hit);
		hJetFragZ[hit] = (TH1D*)CalculateFragFunction(hJetZ[hit], hJetN[hit])->Clone(hname);

	    sprintf(htit, "D(z), log-Z binning, pTt: %3.1f-%3.1f", pTt1, pTt2);
	    sprintf(hname, "hDlogZ%02d", hit);
		hJetFragLogZ[hit] = (TH1D*)CalculateFragFunction(hJetLogZ[hit], hJetN[hit])->Clone(hname);

	    sprintf(htit, "D(xi), pTt: %3.1f-%3.1f", pTt1, pTt2);
	    sprintf(hname, "hDXi%02d", hit);
		hJetFragXi[hit] = (TH1D*)CalculateFragFunction(hJetXi[hit], hJetN[hit])->Clone(hname);
	}
	drawHistos();
	return 0;
}

void drawHistos(){

	TCanvas* cDz = new TCanvas("cDz","cDz",500,500);//, cx, cy, int(400*sc*aspect), int(400*sc) );
    TPad* mpad = new TPad("mDz","mDz", 0.01, 0.01, 0.99, 0.99, 0,0,0);
    mpad->SetLeftMargin(0.15);
    mpad->SetBottomMargin(0.15);
    mpad->SetTopMargin(0.06);
    mpad->SetRightMargin(0.14);
    mpad->SetLogy(1);
    mpad->SetLogx(0);
    mpad->SetLogz(0);
    gStyle->SetOptStat(0);
    mpad->Draw();
    mpad->cd();
    int iDrawNum = 0;

	TLegend* leg = new TLegend(0.25, 0.3, 0.5, 0.50, "","brNDC");
	TLegend* legFit = new TLegend(0.2, 0.2, 0.45, 0.40, "","brNDC");
	legFit->SetFillStyle(0); legFit->SetBorderSize(0); legFit->SetTextSize(0.023);
	leg->SetFillStyle(0); leg->SetBorderSize(0); leg->SetTextSize(0.023);

	for(int hit=0; hit < nPtBinsE; hit++){
		if(iDrawNum==7) iDrawNum=0;
	    float pTt1 = JetPtBorders[hit];
	    float pTt2 = JetPtBorders[hit+1];
	    char htit[100], hname[100];
	    sprintf(htit, "D(z)");
	    sprintf(hname, "hDZ%02d", hit);
	    char hfun[100];
	    sprintf(hfun, "fDZ%02d", hit);
	    hJetFragZ[hit]->SetTitle(htit);
	    hJetFragZ[hit]->GetXaxis()->SetTitle("z");
	    hJetFragZ[hit]->GetYaxis()->SetTitle("1/N_{jets}dN/dz");
	    //hJetFragZ[hit]->GetXaxis()->SetRangeUser(9,495);
	    hJetFragZ[hit]->GetYaxis()->SetRangeUser(0.001,1.6);
	    hJetFragZ[hit]->SetLineColor(gColors[iDrawNum]);
        hJetFragZ[hit]->SetMarkerColor(gColors[iDrawNum]);
        hJetFragZ[hit]->SetMarkerStyle(gMarkers[0][iDrawNum]);
	    hJetFragZ[hit]->Draw("same");

    	leg->AddEntry(hJetFragZ[hit]->Clone(),Form("p_{T} %1.0f-%1.0f GeV", pTt1, pTt2),"p");
		
	    
	    /*hJetFragZ[hit]->Fit("expo", "L", "same", 0.35-((hit+1)*(0.25/5.)), 0.95);
	    TF1 *gfit = (TF1 *)hJetFragZ[hit]->GetFunction("expo"); 
		double slope = gfit->GetParameter(1);
		double slopeError = gfit->GetParError(1); 

		
		TString text1 = Form("p_{T} %1.0f-%1.0f GeV: slope %4.4f#pm%4.4f", pTt1, pTt2, slope, slopeError);
    	legFit->AddEntry(hJetFragZ[hit]->Clone(),text1,"p");
	    legFit->SetTextSize(0.023);
		
*/
		iDrawNum++; 
	}
	leg->Draw("same");
    //legFit->Draw("same");
	cDz->Print("figs/cDz.pdf", "pdf");

	TCanvas* cDzl = new TCanvas("cDzl","cDzl",500,500);//, cx, cy, int(400*sc*aspect), int(400*sc) );
    TPad* mpadl = new TPad("mDzl","mDzl", 0.01, 0.01, 0.99, 0.99, 0,0,0);
    mpadl->SetLeftMargin(0.15);
    mpadl->SetBottomMargin(0.15);
    mpadl->SetTopMargin(0.06);
    mpadl->SetRightMargin(0.14);
    mpadl->SetLogy(1);
    mpadl->SetLogx(0);
    mpadl->SetLogz(1);
    gStyle->SetOptStat(0);
    mpadl->Draw();
    mpadl->cd();
    iDrawNum = 0;

	TLegend* legl = new TLegend(0.23, 0.23, 0.47, 0.43, "","brNDC");
	TLegend* legFitl = new TLegend(0.5, 0.69, 0.85, 0.93, "","brNDC");
	legFitl->SetFillStyle(0); legFitl->SetBorderSize(0); legFitl->SetTextSize(0.023);
	legl->SetFillStyle(0); legl->SetBorderSize(0); legl->SetTextSize(0.023);

	for(int hit=0; hit < nPtBinsE; hit++){
		if(iDrawNum==7) iDrawNum=0;
	    float pTt1 = JetPtBorders[hit];
	    float pTt2 = JetPtBorders[hit+1];
	    char htit[100], hname[100];
	    sprintf(htit, "D(z)");
	    sprintf(hname, "hDlogZ%02d", hit);
	    hJetFragLogZ[hit]->SetTitle(htit);
	    hJetFragLogZ[hit]->GetXaxis()->SetTitle("z");
	    hJetFragLogZ[hit]->GetYaxis()->SetTitle("1/N_{jets}dN/dz");
	    //hResp->GetXaxis()->SetRangeUser(9,495);
	    hJetFragLogZ[hit]->GetYaxis()->SetRangeUser(0.001,0.3);
	    hJetFragLogZ[hit]->SetLineColor(gColors[iDrawNum]);
        hJetFragLogZ[hit]->SetMarkerColor(gColors[iDrawNum]);
        hJetFragLogZ[hit]->SetMarkerStyle(gMarkers[0][iDrawNum]);
	    hJetFragLogZ[hit]->Draw("same");

	    legl->AddEntry(hJetFragLogZ[hit]->Clone(),Form("p_{T} %1.0f-%1.0f GeV", pTt1, pTt2),"p");
/*
	    
	    hJetFragLogZ[hit]->Fit("expo", "I", "same", 0.35-((hit+1)*(0.25/5.)), 0.95);
	    TF1 *gfit = (TF1 *)hJetFragLogZ[hit]->GetFunction("expo"); 
		double slope = gfit->GetParameter(1);
		//cout << "slope is " << slope << endl;
		double slopeError = gfit->GetParError(1);

		TString text1 = Form("p_{T} %1.0f-%1.0f GeV: slope %4.4f#pm%4.4f", pTt1, pTt2, slope, slopeError);
    	legFitl->AddEntry(hJetFragLogZ[hit]->Clone(),text1,"p");
	    legFitl->SetTextSize(0.023);
*/		
		iDrawNum++; 
	}
	legl->Draw("same");
    //legFitl->Draw("same");
	cDzl->Print("figs/cDzl.pdf", "pdf");

	TCanvas* cDxi = new TCanvas("cDxi","cDxi",500,500);//, cx, cy, int(400*sc*aspect), int(400*sc) );
    TPad* mpadx = new TPad("mDzx","mDzx", 0.01, 0.01, 0.99, 0.99, 0,0,0);
    mpadx->SetLeftMargin(0.15);
    mpadx->SetBottomMargin(0.15);
    mpadx->SetTopMargin(0.06);
    mpadx->SetRightMargin(0.14);
    mpadx->SetLogy(0);
    mpadx->SetLogx(0);
    mpadx->SetLogz(1);
    gStyle->SetOptStat(0);
    mpadx->Draw();
    mpadx->cd();
    iDrawNum = 0;

	TLegend* legx = new TLegend(0.6, 0.6, 0.88, 0.86, "","brNDC");
	legx->SetFillStyle(0); legx->SetBorderSize(0); legx->SetTextSize(0.023);

	for(int hit=0; hit < nPtBinsE; hit++){
		if(iDrawNum==7) iDrawNum=0;
	    float pTt1 = JetPtBorders[hit];
	    float pTt2 = JetPtBorders[hit+1];
	    char htit[100], hname[100];
	    sprintf(htit, "D(#xi)");
	    sprintf(hname, "hDXi%02d", hit);
	    hJetFragXi[hit]->SetTitle(htit);
	    hJetFragXi[hit]->GetXaxis()->SetTitle("#xi");
	    hJetFragXi[hit]->GetYaxis()->SetTitle("1/N_{jets}dN/d#xi");
	    hJetFragXi[hit]->GetXaxis()->SetRangeUser(0,8);
	    hJetFragXi[hit]->GetYaxis()->SetRangeUser(0,1.5);
	    hJetFragXi[hit]->SetLineColor(gColors[iDrawNum]);
        hJetFragXi[hit]->SetMarkerColor(gColors[iDrawNum]);
        hJetFragXi[hit]->SetMarkerStyle(gMarkers[0][iDrawNum]);
        hJetFragXi[hit]->SetMarkerSize(1.3);
	    hJetFragXi[hit]->Draw("same");
		iDrawNum++; 
	    legx->AddEntry(hJetFragXi[hit]->Clone(),Form("p_{T} %1.0f-%1.0f GeV", pTt1, pTt2),"p");
	}
	legx->Draw("same");
	cDxi->Print("figs/cDxi.pdf", "pdf");


	TCanvas* cRap = new TCanvas("cRap","cRap",500,500);//, cx, cy, int(400*sc*aspect), int(400*sc) );
    TPad* mpadRap = new TPad("mRap","mRap", 0.01, 0.01, 0.99, 0.99, 0,0,0);
    mpadRap->SetLeftMargin(0.15);
    mpadRap->SetBottomMargin(0.15);
    mpadRap->SetTopMargin(0.06);
    mpadRap->SetRightMargin(0.14);
    mpadRap->SetLogy(0);
    mpadRap->SetLogx(0);
    mpadRap->SetLogz(1);
    gStyle->SetOptStat(0);
    mpadRap->Draw();
    mpadRap->cd();
    hJetRap->Scale(1./hJetRap->GetEntries());
    hJetRap->SetTitle("Jet rapidity distribution");
    hJetRap->GetXaxis()->SetTitle("y");
    hJetRap->GetYaxis()->SetTitle("1/N dN/dy");
    //hJetRap->GetXaxis()->SetRangeUser(0,6);
    //hJetRap->GetYaxis()->SetRangeUser(0,1);
    hJetRap->SetLineColor(gColors[0]);
    hJetRap->SetMarkerColor(gColors[0]);
    hJetRap->SetMarkerStyle(1);
    hJetRap->Draw("same");
	cRap->Print("figs/cRap.pdf", "pdf");


	TCanvas* cPRap = new TCanvas("cPRap","cPRap",500,500);//, cx, cy, int(400*sc*aspect), int(400*sc) );
    TPad* mpadPRap = new TPad("mPRap","mPRap", 0.01, 0.01, 0.99, 0.99, 0,0,0);
    mpadPRap->SetLeftMargin(0.15);
    mpadPRap->SetBottomMargin(0.15);
    mpadPRap->SetTopMargin(0.06);
    mpadPRap->SetRightMargin(0.14);
    mpadPRap->SetLogy(0);
    mpadPRap->SetLogx(0);
    mpadPRap->SetLogz(1);
    gStyle->SetOptStat(0);
    mpadPRap->Draw();
    mpadPRap->cd();
    hJetPseudoRap->Scale(1./hJetPseudoRap->GetEntries());
    hJetPseudoRap->SetTitle("Jet pseudorapidity distribution");
    hJetPseudoRap->GetXaxis()->SetTitle("#eta");
    hJetPseudoRap->GetYaxis()->SetTitle("1/N dN/d#eta");
    //hJetPseudoRap->GetXaxis()->SetRangeUser(0,6);
    //hJetPseudoRap->GetYaxis()->SetRangeUser(0,1);
    hJetPseudoRap->SetLineColor(gColors[0]);
    hJetPseudoRap->SetMarkerColor(gColors[0]);
    hJetPseudoRap->SetMarkerStyle(1);
    hJetPseudoRap->Draw("same");
	cPRap->Print("figs/cPRap.pdf", "pdf");


	TCanvas* cPt = new TCanvas("cPt","cPt",500,500);//, cx, cy, int(400*sc*aspect), int(400*sc) );
    TPad* mpadpt = new TPad("mpadpt","mpadpt", 0.01, 0.01, 0.99, 0.99, 0,0,0);
    mpadpt->SetLeftMargin(0.15);
    mpadpt->SetBottomMargin(0.15);
    mpadpt->SetTopMargin(0.06);
    mpadpt->SetRightMargin(0.14);
    mpadpt->SetLogy(1);
    mpadpt->SetLogx(0);
    mpadpt->SetLogz(1);
    gStyle->SetOptStat(0);
    mpadpt->Draw();
    mpadpt->cd();
    hJetPt->Scale(1./hJetPt->GetEntries());
    hJetPt->SetTitle("Jet p_{T} distribution");
    hJetPt->GetXaxis()->SetTitle("p_{T} [GeV]");
    hJetPt->GetYaxis()->SetTitle("1/N dN/dp_{T}");
    hJetPt->GetXaxis()->SetRangeUser(0,150);
    //hJetPt->GetYaxis()->SetRangeUser(0,1);
    hJetPt->SetLineColor(gColors[0]);
    hJetPt->SetMarkerColor(gColors[0]);
    hJetPt->SetMarkerStyle(1);
    hJetPt->Draw("same");
	cPt->Print("figs/cPt.png", "png");
}

TH1D *CalculateFragFunction(TH1D* ZOrXi, TH1D* nJets){

		TH1D* hReturn = (TH1D*)ZOrXi->Clone("hReturn");
		hReturn->Scale(1./nJets->GetEntries());
		return hReturn;
}

void LoadHistos(TString inFile){
	fIn = new TFile(inFile.Data(), "read");
	fIn->Print();
	for(int hit=0; hit < nPtBinsE; hit++){
	    float pTt1 = JetPtBorders[hit];
	    float pTt2 = JetPtBorders[hit+1];
	    char htit[100], hname[100];

	    sprintf(htit, "pTt: %3.1f-%3.1f", pTt1, pTt2);
	    sprintf(hname, "hZ%02d", hit);
	    hJetZ[hit]=getHisto(fIn,hname);

	    sprintf(hname, "hZLogBin%02d", hit);
	    hJetLogZ[hit]=getHisto(fIn,hname);

	    sprintf(htit, "#xi: %3.1f-%3.1f", pTt1, pTt2);
	    sprintf(hname, "hXi%02d", hit);
	    hJetXi[hit]=getHisto(fIn,hname);

	    sprintf(htit, "Nt: %3.1f-%3.1f", pTt1, pTt2);
	    sprintf(hname, "hN%02d", hit);
	    hJetN[hit]=getHisto(fIn,hname);
	}

	hJetRap=getHisto(fIn, "hJetRapidity");
	hJetPseudoRap=getHisto(fIn, "hJetPseudorapidity");
	hJetPt=getHisto(fIn, "fhJetPt");
}

TH1D *getHisto(TFile* fIn, TString sHistoName) {
	if(fIn==0){ cout << "NO FILE" << endl; return 0; }
    TH1D *hReturn;
	hReturn=(TH1D*)fIn->Get(sHistoName.Data());
        if(hReturn==0) { cout << Form("getHisto: histo=%s pointer null! Check histo name.",sHistoName.Data()) << endl; return 0; }
    return hReturn;
}