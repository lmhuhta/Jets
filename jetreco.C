#include "TH1D.h"
#include <vector>
#include <iostream>
#include "TROOT.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TRandom.h"
#include "TF1.h"
#include "TFile.h"
#include <Pythia8/Pythia.h>
#include <TStopwatch.h>

#include "fastjet/ClusterSequence.hh"
#include "fastjet/PseudoJet.hh"
#include <iostream>

#include <TClonesArray.h>
#include <TLorentzVector.h>
#include "src/AliJBaseTrack.h"
//#include "src/AliJCard.h"
#include "src/JHistos.h"
//#include "src/inputbinning.h"


const int NBinsZ=24;

double xbinsZ[NBinsZ]={0, 0.0030, 0.0040, 0.0052, 0.0069, 0.0092, 0.0121, 0.0160, 0.0212, 0.0280, 0.0371, 0.0490, 0.0648, 0.0856, 0.1132, 0.1497, 0.1980, 0.2618, 0.3461, 0.4576, 0.6050, 0.8, 0.9, 1};

using namespace std;
using namespace Pythia8; 
using namespace fastjet;

double dotproduct(TLorentzVector jets,TLorentzVector particles);
int GetBin(double bins[], int nOfBins, float ptVal);


class MyUserInfo : public PseudoJet::UserInfoBase{
  public:
    // default ctor
    MyUserInfo(const int & pdg_id_in,const vector<bool> &pType) :
      _pdg_id(pdg_id_in){ ispid = pType;}

    /// access to the PDG id
    int pdg_id() const { return _pdg_id;}
    void PrintIsPid() const { 
      for(unsigned int i=0;i<ispid.size();i++) {
       cout << ispid.at(i)<<":";
      }
      cout << endl;
    }
    bool IsType(int i) const { return ispid[i];}

  protected:
    int _pdg_id;         // the associated pdg id
    vector<bool> ispid;
};



int main(int argc, char **argv) {

  if(argc<5){
    cout<<"usage: pythia.config pTHatMin pTHatMax <output.root> [random_seed]"<<endl;exit(1);//usage of the code, requieres 4 inputs
  }
  TStopwatch timer; 
  timer.Start();   

  //placing the inputs into variables
  char* pythiaconfig  = argv[1];
  double pTHatMin     = atof(argv[2]);
  double pTHatMax     = atof(argv[3]);
  TString outputs = argv[4];
  Int_t random_seed = argc>5 ? atoi(argv[5]) : 0;

  TFile *fout = new TFile(outputs.Data(),"RECREATE");
  fout->cd();//opening of the output file

  //AliJCard *fcard = new AliJCard(cardInput);
  //JHistos *fhistos = new JHistos(); //(fcard);
 // fhistos->CreateQAHistos();
  //fhistos->CreateFFHistos();
  //cout << "OK" << endl;
 // fhistos->CreateDiJetHistos();

  //---------------------
  //Pythia initialization 
  //---------------------
  Pythia pythia;   // Generator.
  //Event& event      = pythia.event;
  ParticleData& pdt = pythia.particleData;

  // Read in commands from external file.
  pythia.readFile(pythiaconfig);   

  // Extract settings to be used in the main program.
  int    nEvent  = pythia.mode("Main:numberOfEvents");
  bool   showCS  = pythia.flag("Main:showChangedSettings");
  bool   showCPD = pythia.flag("Main:showChangedParticleData");
  double energy  = pythia.mode("Beams:eCM");

  pythia.readString(Form("PhaseSpace:pTHatMin ==%f",pTHatMin));
  pythia.readString(Form("PhaseSpace:pTHatMax ==%f",pTHatMax));
  cout<<"Events="<<nEvent <<" RNDM seed "<< random_seed << endl;

  pythia.readString("Random:setSeed = on");
  pythia.readString(Form("Random:seed=%02d",random_seed));

  // Initialize. Beam parameters set in .cmnd file.
  pythia.init();

  // List changed data. 
  if (showCS)  pythia.settings.listChanged();
  if (showCPD) pdt.listChanged();



  //------------------------------------------------------------------
  // Histograms
  //------------------------------------------------------------------
  int Nbins = 100;
  double rapMin=-2; double rapMax=2;
  int NBINS=500;
  double LogBinsX[NBINS+1], LimL=0.1, LimH=500;
  double logBW = (log(LimH)-log(LimL))/NBINS;
  for(int ij=0;ij<=NBINS;ij++) LogBinsX[ij]=LimL*exp(ij*logBW);

  TH1D *hCrossSectionInfo = new TH1D("hCrossSection","CrossSectionInfo", 10, 0, 10 );
  TH1D *hPtHatInfo        = new TH1D("hPtHatInfo","PtHatInfo", 500, 0, 500);

  TH1D *hEvents           = new TH1D("hEvents", "Events", 40, 0.0, 40.0 );
  //TH1D *hZ                = new TH1D("hZ","Splitting Fraction z", 500, 0, 500 );

  TH1D *hJetPseudorapidity= new TH1D("hJetPseudorapidity","Jet Pseudorapidity",Nbins,rapMin,rapMax);
  TH1D *hJetRapidity      = new TH1D("hJetRapidity","Jet Rapidity",Nbins,rapMin,rapMax);
  TH1D *hJetPt            = new TH1D("fhJetPt","Jet p_{T} spectra",500, LogBinsX);

  int nrapbins = 500;
  int nxibins = 100;
  double lxi = 0.;
  double hxi = 25.;

  const int bins = NBinsZ-1;
  int nPtBins = 11;
  double JetPtBorders[nPtBins] = {5, 10, 20, 30, 40, 60, 80, 100, 150, 500, 1000};

  TH1D *hZ[nPtBins];
  TH1D *hZLogBin[nPtBins];
  TH1D *hXi[nPtBins];
  TH1D *hJetN[nPtBins];

  int nZ = 100;
  double zLow = 0.01, zHigh = 1.1;

  double logBinsZ[101];
  double logZ = (log(zHigh)-log(zLow))/nZ;
  for(int ij=0;ij<=nZ;ij++) logBinsZ[ij]=zLow*exp(ij*logZ);

  for(int hit=0; hit < nPtBins; hit++){
    float pTt1 = JetPtBorders[hit];
    float pTt2 = JetPtBorders[hit+1];
    char htit[100], hname[100];

    sprintf(htit, "pTt: %3.1f-%3.1f", pTt1, pTt2);
    sprintf(hname, "hZ%02d", hit);
    hZ[hit]=new TH1D(hname, htit, bins, xbinsZ);
    hZ[hit]->Sumw2();

    sprintf(hname, "hZLogBin%02d", hit);
    hZLogBin[hit]=new TH1D(hname, htit, nZ, logBinsZ);
    hZLogBin[hit]->Sumw2();

    sprintf(htit, "#xi: %3.1f-%3.1f", pTt1, pTt2);
    sprintf(hname, "hXi%02d", hit);
    hXi[hit]=new TH1D(hname, htit, nxibins, lxi, hxi);
    hXi[hit]->Sumw2();

    sprintf(htit, "Nt: %3.1f-%3.1f", pTt1, pTt2);
    sprintf(hname, "hN%02d", hit);
    hJetN[hit]=new TH1D(hname, htit, 101, -0.5 , 100.5);
    hJetN[hit]->Sumw2();
  }
  NBINS=300;
  double logBinsX[NBINS+1];
  LimL=1e-3; LimH=3000;
  logBW = (log(LimH)-log(LimL))/NBINS;
  for(int iBin=0;iBin<=NBINS;iBin++) logBinsX[iBin]=LimL*exp(iBin*logBW);
  TH1D *hEbeweight = new TH1D("hEbeweight","Ebeweight", NBINS, logBinsX);

  //------------------------------------------------------------------
  // Define jet reconstruction
  //------------------------------------------------------------------
  vector<PseudoJet> finalparticles; // for full jet

  TClonesArray *inputList = new TClonesArray("AliJBaseTrack",1500); //alternate way to fill final particles

  double PartMinPtCutForJet = 0.15;//alice/cms 0.5 atlas paper
  double etaMaxCutForJet = 1.2;///
  double coneR = 0.4;//alice 
  double etaMaxCutForPart = etaMaxCutForJet+coneR;///
  double MinJetPt = 5.; // Min Jet Pt cut to disregard low pt jets

  JetDefinition jet_def(antikt_algorithm, coneR); 

  cout << endl;
  cout << "============= Settings =============" << endl;
  cout << "PartMinPtCutForJet:                  " << PartMinPtCutForJet << endl;
  cout << "etaMaxCutForJet:                     " << etaMaxCutForJet << endl;
  cout << "coneR:                               " << coneR << endl;
  cout << "etaMaxCutForPart:                    " << etaMaxCutForPart << endl;
  cout << "MinJetPt:                            " << MinJetPt << endl;
  cout << endl;


  //--------------------------------------------------------
  //         B e g i n    e v e n t    l o o p.
  //--------------------------------------------------------
  cout<<"Let's start" <<endl; 
  int ieout = nEvent/20;
  if (ieout<1) ieout=1;
  int EventCounter = 0;

  Float_t ebeweight = 1.0;


  for(int iEvent = 0; iEvent < nEvent; ++iEvent) {//begin event loop

    if (!pythia.next()) continue;
    inputList->Clear("C");
    finalparticles.clear();

    ebeweight = pythia.info.weight();
    hEbeweight->Fill(ebeweight);

    if(iEvent % ieout == 0) cout << iEvent << "\t" << int(float(iEvent)/nEvent*100) << "%" << endl ;
    //int icent = 0;
    hCrossSectionInfo->Fill(7.5,ebeweight);
    hPtHatInfo->Fill(pythia.info.pTHat(), ebeweight);
    hEvents->Fill("events",1.0);
    
    for (int i = 0; i < pythia.event.size(); ++i) {//loop over all the particles in the event
      // Building input particle list for the jet reconstruction
      // Make sure "applying same cut done in ATLAS paper ?  flavor of the parciles ,eta , min pt cut 
      if (pythia.event[i].isFinal() && TMath::Abs(pythia.event[i].eta()) < etaMaxCutForPart && pythia.event[i].pT()>PartMinPtCutForJet){
        // Building the charged particle list to be used for manual constituent construction instead of using fastjet consistuents.
        finalparticles.push_back( PseudoJet(pythia.event[i].px(), pythia.event[i].py() , pythia.event[i].pz(), pythia.event[i].e()) );

        //alternate way to fill events, using AliJBaseTrack
        /*TLorentzVector lParticle(pythia.event[i].px(), pythia.event[i].py(), pythia.event[i].pz(), pythia.event[i].e());
        AliJBaseTrack track( lParticle );
        track.SetID(pythia.event[i].id());
        track.SetTrackEff(1.);
        new ((*inputList)[inputList->GetEntriesFast()]) AliJBaseTrack(track);*/ 

      } // end of finalparticles
    }

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Run the clustering, Reconstruct jets
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    ClusterSequence cs(finalparticles, jet_def);
    vector<PseudoJet> jets = sorted_by_pt(cs.inclusive_jets(MinJetPt)); // APPLY Min pt cut for jet

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Loop over jets and fill various histos 
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    for (unsigned int i = 0; i < jets.size(); i++) {
      // jet eta cut
      if(fabs(jets[i].eta())>etaMaxCutForJet) continue; 

      vector<PseudoJet> constituents = jets[i].constituents();
      //fhistos->fhJetPseudorapidity->Fill(jets[i].eta());  
      //fhistos->fhJetRapidity->Fill(jets[i].rap());  
      //fhistos->fhJetPt->Fill(jets[i].pt());
      hJetPseudorapidity->Fill(jets[i].eta());
      hJetRapidity->Fill(jets[i].rap()); 
      hJetPt->Fill(jets[i].pt());
      int ptbin = GetBin(JetPtBorders, nPtBins, jets[i].pt());

      // Only for the jet pt bin registered in the card
      //if(ptbin<0){continue;}


      TLorentzVector lvjet = TLorentzVector(jets[i].px(),jets[i].py(),jets[i].pz(),jets[i].e());//creating the jet lorentz vector for the deltar calculation

      //Consistuents loop
      for (unsigned int j = 0; j < constituents.size(); j++) {
        TLorentzVector lvfinalpart = TLorentzVector(constituents[j].px(),constituents[j].py(),constituents[j].pz(),constituents[j].e()); //
        double dotproductall=dotproduct(lvjet,lvfinalpart); 
        double z=dotproductall/(jets[i].modp2());
        double xi=TMath::Log(1./z);
        hZ[ptbin]->Fill(z);
        hZLogBin[ptbin]->Fill(z);
        hXi[ptbin]->Fill(xi);
      } // end of constituents loop
      hJetN[ptbin]->Fill(constituents.size());// number of all particle per jet histo

    }//end of the jet loop
    EventCounter++;
  }//event loop

  long nTried = pythia.info.nTried();
  long nAccepted = pythia.info.nAccepted();
  double sigmaGen = pythia.info.sigmaGen();
  //double sigmaErr = pythia.info.sigmaErr();
  hCrossSectionInfo->Fill(0.5,nTried);
  hCrossSectionInfo->Fill(1.5,nAccepted);
  hCrossSectionInfo->Fill(2.5,sigmaGen);
  hCrossSectionInfo->Fill(3.5,EventCounter);
  hCrossSectionInfo->Fill(4.5,energy);
  hCrossSectionInfo->Fill(5.5,1);

  fout->Write();
  //fcard->WriteCard(fout); // Write card into the file
  fout->Close();
  cout << EventCounter << " events are analyzed successfully."<< endl;
  timer.Print(); 
  return 0;
}


// CHECK FUNCTION
double dotproduct(TLorentzVector jets,TLorentzVector particles){//takes in two Lorentz vectors and transform it into TVector3 and makes the dot product
  double jetpx=jets.Px();
  double jetpy=jets.Py();
  double jetpz=jets.Pz();

  double partpx=particles.Px();
  double partpy=particles.Py();
  double partpz=particles.Pz();

  TVector3 jet=TVector3(jetpx,jetpy,jetpz);
  TVector3 particle=TVector3(partpx,partpy,partpz);

  double dotproduct= particle.Dot(jet);

  //delete jet;
  //delete particle;

  return dotproduct;
}

//returns bin number where ptVal is, if not in range of bins, returns -1 
int GetBin(double bins[], int nOfBins, float ptVal){
  if (ptVal<bins[0]) return -1;
  if (ptVal>bins[nOfBins-1]) return -1;
  for (int i = 0; i < nOfBins-1; ++i)
  {
    if (ptVal>bins[i]&&ptVal<bins[i+1]) return i;
  }
  return -1;
}