#include <string>
#include <vector>
#include <iostream>
#include "TFile.h"
#include "TH1D.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TLine.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "CMS_lumi.h"
#include "TVectorD.h"
#include "TGraph.h"

class EDBRHistoPlotter {
public:

  EDBRHistoPlotter(std::string nameInDir,
                   std::vector<std::string> nameFileDATA,
                   std::vector<std::string> nameFileMC,
                   std::vector<std::string> nameFileMCSig,
                   double targetLumi,
                   int wantNXJets,
                   int flavour,
                   bool isZZchannel,
                   bool scaleToData,
                   bool scaleOnlyDYJets,
                   bool makeRatio,
                   bool isSignalStackOnBkg,
                   std::vector<double> kFactorsMC,
                   std::vector<double> kFactorsMCSig)
  {
    std::cout << "Plotter constructor" << std::endl;
    nameInDir_      = nameInDir;
    fileNamesMC     = nameFileMC;
    fileNamesMCSig  = nameFileMCSig;
    fileNamesDATA   = nameFileDATA;
    kFactorsMC_     = kFactorsMC;
    kFactorsSig_    = kFactorsMCSig;
    targetLumi_     = targetLumi;
    wantNXJets_     = wantNXJets;
    flavour_        = flavour;
    isZZchannel_    = isZZchannel;
    scaleToData_    = scaleToData;
    scaleOnlyDYJets_ = scaleOnlyDYJets;
    makeRatio_      = makeRatio;
    isSignalStackOnBkg_ = isSignalStackOnBkg;
    debug_          = true;
    if (fileNamesDATA.size() != 0)
      isDataPresent_ = true;
    else
      isDataPresent_ = false;
    std::cout << "Check" << std::endl;
    EDBRColors.resize(20, kWhite);
    EDBRLineColors.resize(20, kWhite);
    std::cout << "Check" << std::endl;
    labels.resize(0);
    labelsSig.resize(0);
    std::cout << "Check" << std::endl;
    makeLabels();
    std::cout << "Check" << std::endl;
   if (fileNamesMCSig.size() != kFactorsSig_.size()) {
      cout << "======> Mismatch in size of input MC Sig arrays !!! " << fileNamesMCSig.size() << "  " << kFactorsSig_.size() << endl;
    }

    printf("Target lumi is %g fb-1\n", targetLumi);
    std::cout << "k factors for MC backgrounds are: " << std::endl;
    int myKindex = 0;
    for (std::vector<double>::iterator it = kFactorsMC_.begin(); it != kFactorsMC_.end(); ++it) {
      std::cout << *it << " for " << fileNamesMC.at(myKindex) << std::endl ;
      myKindex++;
    }
    myKindex = 0;
    for (std::vector<double>::iterator it = kFactorsSig_.begin(); it != kFactorsSig_.end(); ++it) {
      std::cout << *it << " for " << fileNamesMCSig.at(myKindex) << std::endl ;
      myKindex++;
    }

    std::cout << std::endl;
  }//end constructor

  virtual ~EDBRHistoPlotter()
  {
  }//end destructor

  /// Members
  std::vector<std::string> fileNamesMC;
  std::vector<std::string> fileNamesMCSig;
  std::vector<std::string> fileNamesDATA;
  std::vector<std::string> labels;
  std::vector<std::string> labelsSig;
  std::vector<TFile*>      filesMC;
  std::vector<TFile*>      filesMCSig;
  std::vector<TFile*>      filesDATA;
  std::vector<TH1D*>       histosMC;
  std::vector<TH1D*>       histosMCSig;
  std::vector<TH1D*>       histosMCSigOrig;
  std::vector<TH1D*>       histosDATA;
  std::vector<int>         EDBRColors;
  std::vector<int>         EDBRLineColors;
  std::vector<double>      kFactorsMC_;
  std::vector<double>      kFactorsSig_;

  std::string nameInDir_;
  std::string nameOutDir_;
  double dataIntegral_;
  double targetLumi_;
  int    wantNXJets_;
  int    flavour_;
  bool   isZZchannel_;
  bool   scaleToData_;
  bool   scaleOnlyDYJets_;
  bool   makeRatio_;
  bool   isSignalStackOnBkg_;
  bool   isDataPresent_;
  bool   debug_;

  /// Functions
  void cleanupMC();
  void cleanupMCSig();
  void cleanupDATA();
  void makeLabels();
  void makeStackPlots(std::string histoName);
  void setOutDir(std::string outDirNew);

  /// set debug mode
  void setDebug(bool debug)
  {
    debug_ = debug;
  }

  /// get reasonable colors for stacks.
  int getFillColor(int index)
  {
    if (index < 20)return EDBRColors[index];
    return kWhite;
  }

  /// set reasonable colors for stacks.
  void setFillColor(std::vector<int> colorList)
  {
    unsigned int ind = 0;
    while (ind < 20 && ind < colorList.size()) {
      EDBRColors.at(ind) = colorList.at(ind);
      ind++;
    }
  }

  /// get reasonable colors for stacks.
  int getLineColor(int index)
  {
    if (index < 20)return EDBRLineColors[index];
    return kWhite;
  }

  /// set reasonable colors for stacks.
  void setLineColor(std::vector<int> colorList)
  {
    unsigned int ind = 0;
    while (ind < 20 && ind < colorList.size()) {
      EDBRLineColors.at(ind) = colorList.at(ind);
      ind++;
    }
  }

};

void EDBRHistoPlotter::cleanupMC()
{
  for (size_t i = 0; i != filesMC.size(); ++i) {
    filesMC.at(i)->Close();
  }
  filesMC.clear();

  for (size_t i = 0; i != histosMC.size(); ++i) {
    histosMC.at(i)->Delete();
  }
  histosMC.clear();
}

void EDBRHistoPlotter::cleanupMCSig()
{
  for (size_t i = 0; i != filesMCSig.size(); ++i) {
    filesMCSig.at(i)->Close();
  }
  filesMCSig.clear();

  for (size_t i = 0; i != histosMCSig.size(); ++i) {
    histosMCSig.at(i)->Delete();
    histosMCSigOrig.at(i)->Delete();
  }
  histosMCSig.clear();
  histosMCSigOrig.clear();
}

void EDBRHistoPlotter::cleanupDATA()
{
  for (size_t i = 0; i != filesDATA.size(); ++i) {
    filesDATA.at(i)->Close();
  }
  filesDATA.clear();

  for (size_t i = 0; i != histosDATA.size(); ++i) {
    histosDATA.at(i)->Delete();
  }
  histosDATA.clear();
}

void EDBRHistoPlotter::makeLabels()
{
  for (size_t i = 0; i != fileNamesMC.size(); i++) {
    TString s1 = fileNamesMC.at(i);
    TString s2 = "_.";
    TObjArray* tokens = s1.Tokenize(s2);
    std::string aLabel  = ((TObjString*)(tokens->At(1)))->String().Data();
    std::string aLabel2 = ((TObjString*)(tokens->At(2)))->String().Data();
    //labels.push_back(aLabel + aLabel2);
    labels.push_back(aLabel);
  }
  std::cout << "Labels MC done" << std::endl;

  for (size_t i = 0; i != fileNamesMCSig.size(); i++) {
    TString s1 = fileNamesMCSig.at(i);
    TString s2 = "_.";
    TObjArray* tokens = s1.Tokenize(s2);
    
    std::string aLabelType = ((TObjString*)(tokens->At(1)))->String().Data();
    std::string aLabelCoupling = ((TObjString*)(tokens->At(2)))->String().Data();
    std::string aLabelMass = ((TObjString*)(tokens->At(3)))->String().Data();
    std::cout << s1.Data();
    std::string aLabel = aLabelType + aLabelCoupling + aLabelMass;
    labelsSig.push_back(aLabel);
  }
  std::cout << "Labels MC signal done" << std::endl;

}

///set output directories for plots.
void EDBRHistoPlotter::setOutDir(std::string outDirNew)
{
  char buffer[256];
  nameOutDir_ = outDirNew;

  sprintf(buffer, "%s/eps", nameOutDir_.c_str());
  printf("%s\n", buffer);
  gSystem->mkdir(buffer, true);

  sprintf(buffer, "%s/pdf", nameOutDir_.c_str());
  printf("%s\n", buffer);
  gSystem->mkdir(buffer, true);

  sprintf(buffer, "%s/root", nameOutDir_.c_str());
  printf("%s\n", buffer);
  gSystem->mkdir(buffer, true);

  sprintf(buffer, "%s/png", nameOutDir_.c_str());
  printf("%s\n", buffer);
  gSystem->mkdir(buffer, true);
}

void EDBRHistoPlotter::makeStackPlots(std::string histoName)
{

  cleanupMC();
  cleanupMCSig();
  cleanupDATA();

  //printf("Making histo %s\n",histoName.c_str());
  std::cout << "\rMaking histo " << histoName.c_str() << std::endl;

  TCanvas* cv = new TCanvas(("cv_" + histoName).c_str(), ("cv_" + histoName).c_str(), 600, 600);

  //create 3 pads in the canvas
  TPad* fPads1 = NULL;
  TPad* fPads2 = NULL;
  TPad* fPads3 = NULL;

  if (isDataPresent_) {
    fPads1 = new TPad("pad1", "", 0.00, 0.25, 0.99, 0.99);
    fPads2 = new TPad("pad2", "", 0.00, 0.00, 0.99, 0.25);
    fPads1->SetFillColor(0);
    fPads1->SetLineColor(0);
    fPads2->SetFillColor(0);
    fPads2->SetLineColor(0);
    if (makeRatio_) {
       fPads1->SetPad(0.00,0.40,0.99,0.99);
       fPads2->SetPad(0.00,0.20,0.99,0.40);
       fPads3 = new TPad("pad3", "", 0.00, 0.00, 0.99, 0.20);
       fPads3->SetFillColor(0);
       fPads3->SetLineColor(0);
       fPads1->Draw();
       fPads2->Draw();
       fPads3->Draw();
    }
    else{
       fPads1->Draw();
       fPads2->Draw();
    }
  }

  //============ Data vs MC plots ==============

  if (isDataPresent_) {
    fPads1->cd();
  }

  ///--------------------
  /// Make the DATA stack
  ///--------------------

  TH1D* sumDATA = NULL;

  for (size_t i = 0; i != fileNamesDATA.size(); ++i) {
    filesDATA.push_back(TFile::Open((nameInDir_ +
                                     fileNamesDATA.at(i)).c_str()));
  }

  for (size_t i = 0; i != filesDATA.size(); ++i) {
    TH1D* histo = (TH1D*)(filesDATA.at(i)->Get(histoName.c_str())->Clone("clone"));
    histo->SetDirectory(0);
    histosDATA.push_back(histo);
  }

  if (histosDATA.size() != 0) {
    sumDATA = (TH1D*)(histosDATA.at(0)->Clone("masterDATA"));
    sumDATA->Reset();
    sumDATA->SetDirectory(0);
  }

  for (size_t i = 0; i != histosDATA.size(); ++i) {
    sumDATA->Add(histosDATA.at(i));
  }

  double sumDataIntegral = 0;
  if (isDataPresent_)
    sumDataIntegral = sumDATA->Integral();

  if (debug_) {
    printf("sumDataIntegral = %g\n", sumDataIntegral);
  }

  ///------------------
  /// Make the MC stack
  ///------------------

  TH1D* sumMC = NULL;
  double sumBkgAtTargetLumi = 0;

  for (size_t i = 0; i != fileNamesMC.size(); ++i) {
    filesMC.push_back(TFile::Open((nameInDir_ +
                                   fileNamesMC.at(i)).c_str()));
  }

  double sumBkgOther = 0.;
  double sumDYJets   = 0.;
  std::vector<double> yieldMC;
  for (size_t i = 0; i != filesMC.size(); ++i) {
    TH1D* histo = (TH1D*)(filesMC.at(i)->Get(histoName.c_str())->Clone(labels.at(i).c_str()));

    histo->Scale(kFactorsMC_.at(i));

    if (debug_) {
      histo->Print();
    }
    sumBkgAtTargetLumi += (histo->Integral() * targetLumi_);
    yieldMC.push_back(     histo->Integral() * targetLumi_);


    if (debug_)cout << "filesMC.at(i)->GetName()   " << filesMC.at(i)->GetName() << endl;
    TString filename = filesMC.at(i)->GetName();
    if (filename.Contains("DYJets"))   sumDYJets += (histo->Integral() * targetLumi_);
    else sumBkgOther += (histo->Integral() * targetLumi_);
  }
  if (debug_)cout << sumBkgAtTargetLumi << " " << sumDYJets << " " << sumBkgOther << " " << sumDYJets + sumBkgOther << endl;
  double DYJetsScaleFactor = 1.;
  if (scaleOnlyDYJets_) {
    DYJetsScaleFactor = (sumDataIntegral - sumBkgOther) / sumDYJets;
    cout << "DYJetsScaleFactor " << DYJetsScaleFactor << endl;
  }

  for (size_t i = 0; i != filesMC.size(); ++i) {
    TH1D* histo = (TH1D*)(filesMC.at(i)->Get(histoName.c_str())->Clone(labels.at(i).c_str()));
    histo->SetDirectory(0);
    histo->SetFillColor(getFillColor(i));

    TString filename = filesMC.at(i)->GetName();
    histo->Scale(kFactorsMC_.at(i));
    if (filename.Contains("DYJets"))histo->Scale(DYJetsScaleFactor);
    histosMC.push_back(histo);
  }



  if (debug_) {
    printf("sumBkgAtTargetLumi = %g\n", sumBkgAtTargetLumi);
    printf("sumDataIntegral = %g\n", sumDataIntegral);
    printf("Scale factor = %g\n", sumDataIntegral / sumBkgAtTargetLumi);
  }

  if (histosMC.size() != 0) {
    sumMC = (TH1D*)(histosMC.at(0)->Clone("masterMC"));
    sumMC->Reset();
    sumMC->SetDirectory(0);
  }

  /// Do we normalize to data or to lumi?
  /// NOTICE THAT THIS DEPENDS ON THE HISTOGRAMS HAVING BEING
  /// CORRECTLY FILLED WITH PUweight*LumiWeight*GenWeight
  for (size_t is = 0; is != histosMC.size(); is++) {
    if (debug_)
      printf("This histogram has integral %g\n", histosMC.at(is)->Integral());
    if (scaleToData_ && isDataPresent_) {
      histosMC.at(is)->Scale(targetLumi_ *
                             sumDataIntegral / sumBkgAtTargetLumi);
    } else {
      histosMC.at(is)->Scale(targetLumi_);
    }
    if (debug_)
      printf("After scaling this histogram has integral %g\n", histosMC.at(is)->Integral());
  }

  THStack* hs = new THStack("hs", "");

  // Make a histogram just for the sum
  for (size_t i = 0; i != histosMC.size(); ++i) {
    sumMC->Add(histosMC.at(i));
    hs->Add(histosMC.at(i));
  }

  if (debug_) {
    printf("After scaling, sum of backgrounds = %g\n", sumMC->Integral());
    printf("Sum of data is still %g\n", sumDataIntegral);
  }


  sumMC->SetFillStyle(0);
  sumMC->SetLineColor(kBlack);
  sumMC->SetLineWidth(2);

  if (scaleToData_ && isDataPresent_) {
    std::cout << "===> Residual DATA/MC Scale Factor is: " << sumDataIntegral / sumBkgAtTargetLumi << std::endl;
  }

  ///-------------------------------
  /// Add the MC signal to the stack
  ///-------------------------------

  for (size_t i = 0; i != fileNamesMCSig.size(); ++i) {
    filesMCSig.push_back(TFile::Open((nameInDir_ +
                                      fileNamesMCSig.at(i)).c_str()));
  }

  for (size_t i = 0; i != filesMCSig.size(); ++i) {
    TH1D* histo     = (TH1D*)(filesMCSig.at(i)->Get(histoName.c_str())->Clone(labelsSig.at(i).c_str()));
    TH1D* histoOrig = (TH1D*)(filesMCSig.at(i)->Get(histoName.c_str())->Clone(labelsSig.at(i).c_str()));
    histo->SetDirectory(0);
    histo->SetLineColor(getLineColor(i));
    histoOrig->SetDirectory(0);
    histoOrig->SetLineColor(getLineColor(i));
    histoOrig->SetFillColor(getLineColor(i));
    if (i % 2 == 0)histoOrig->SetFillStyle(3004);
    else histoOrig->SetFillStyle(3005);
    //histo->Scale(kFactor_); //============= SCALE FACTORS FOR SIGNAL? ==== FIXME

    if (debug_) {
      histo->Print();
    }
    histosMCSig.push_back(histo);
    histosMCSigOrig.push_back(histoOrig);
  }

  //scale the MC signal histogram
  if (histosMCSig.size() != kFactorsSig_.size())cout << "+++++++++++++++++ Mismatch in size of input MC Sig arrays !!!" << endl;
  for (size_t is = 0; is != histosMCSig.size(); is++) {
    if (debug_)printf("Signal histogram has integral %g\n", histosMCSig.at(is)->Integral());

    histosMCSig.at(is)->Scale(targetLumi_ * kFactorsSig_.at(is));
    histosMCSigOrig.at(is)->Scale(targetLumi_ * kFactorsSig_.at(is));

    if (debug_)
      printf("After scaling signal histogram has integral %g\n", histosMCSig.at(is)->Integral());

    //add the signal to the total background
    histosMCSig.at(is)->Add(sumMC);
  }

  ///-----------------------------------
  /// Draw both MC and DATA in the stack
  ///-----------------------------------

  std::map<std::string, std::string> axisTitle;
  axisTitle["h_nVtx"]          = "number of primary vertices";
  axisTitle["h_ptZll"]         = "leptonic Z p_{T} (GeV)"; 
  axisTitle["h_ptZjj"]         = "jet p_{T} (GeV)"; 
  axisTitle["h_yZll"]          = "leptonic Z eta"; 
  axisTitle["h_yZjj"]          = "jet eta"; 
  axisTitle["h_phiZll"]        = "leptonic Z phi"; 
  axisTitle["h_phiZjj"]        = "jet phi"; 
  axisTitle["h_massZll"]       = "leptonic Z mass (GeV)"; 
  axisTitle["h_massZjj"]       = "jet pruned mass (GeV)"; 
  axisTitle["h_massZjj2"]      = "jet pruned mass (GeV)"; 
  axisTitle["h_tau21"]         = "N-subjettiness tau_{21}"; 
  axisTitle["h_ptlep1"]        = "leading lepton p_{T} (GeV)"; 
  axisTitle["h_ptlep2"]        = "second lepton p_{T} (GeV)"; 
  axisTitle["h_ptjet1"]        = "jet p_{T} (GeV)"; 
  axisTitle["h_etalep1"]       = "leading lepton eta"; 
  axisTitle["h_etalep2"]       = "second lepton eta"; 
  axisTitle["h_etajet1"]       = "jet eta"; 
  axisTitle["h_philep1"]       = "leading lepton phi"; 
  axisTitle["h_philep2"]       = "second lepton phi"; 
  axisTitle["h_phijet1"]       = "jet phi"; 
  axisTitle["h_trackIso1"]     = "leading lepton tracker ISO_{rel}"; 
  axisTitle["h_trackIso2"]     = "second lepton tracker ISO_{rel}"; 
  axisTitle["h_pfIso03R1"]     = "leading lepton PF ISO_{rel}"; 
  axisTitle["h_pfIso03R2"]     = "second lepton PF ISO_{rel}"; 
  axisTitle["h_miniIso1"]      = "leading lepton miniISO_{rel}"; 
  axisTitle["h_miniIso2"]      = "second lepton miniISO_{rel}"; 
  axisTitle["h_miniIsoAbs1"]   = "leading lepton miniISO_{abs}"; 
  axisTitle["h_miniIsoAbs2"]   = "second lepton miniISO_{abs}"; 
  axisTitle["h_lep"]           = "lepton flavor"; 
  axisTitle["h_region"]        = "region"; 
  axisTitle["h_triggerWeight"] = "trigger weight"; 
  axisTitle["h_lumiWeight"]    = "luminosity weight"; 
  axisTitle["h_pileupWeight"]  = "pileup weight"; 
  axisTitle["h_deltaRleplep"]  = "deltaR(lep,lep)"; 
  axisTitle["h_deltaRlepjet"]  = "deltaR(lep,jet)"; 
  axisTitle["h_candMass"]      = "VZ candidate mass (GeV)"; 
  axisTitle["h_candMass2"]     = "VZ candidate mass (GeV)"; 

  hs->Draw("HIST");
  hs->GetXaxis()->SetTitle(axisTitle[histoName].c_str());
  hs->GetYaxis()->SetTitle("Events");
  hs->GetYaxis()->SetTitleOffset(1.15);
  hs->GetYaxis()->CenterTitle();
  double maximumMC = 1.333 * sumMC->GetMaximum();
  double maximumDATA = -100;
  if (isDataPresent_)
    maximumDATA = 1.333 * sumDATA->GetMaximum();
  double maximumForStack = -100;
  if (isDataPresent_)
    maximumForStack = (maximumMC > maximumDATA ? maximumMC : maximumDATA);
  else
    maximumForStack = maximumMC;
  hs->SetMaximum(maximumForStack);
  // Some hacks for better aestetics
  // Extra vertical space in some plots 
  if (histoName.find("yZ") != std::string::npos) {
    hs->SetMaximum(maximumForStack * 1.25);
  }
  if (histoName.find("eta") != std::string::npos) {
    hs->SetMaximum(maximumForStack * 1.25);
  }
  if (histoName.find("massZjj") != std::string::npos) {
      hs->SetMaximum(maximumForStack * 1.25);
  }
  if (histoName.find("nVtx") != std::string::npos) {
      hs->SetMaximum(maximumForStack * 1.25);
  }
  if (histoName.find("deltaRleplep") != std::string::npos) {
      hs->SetMaximum(maximumForStack * 1.25);
  }
  if (histoName.find("tau") != std::string::npos) {
      hs->SetMaximum(maximumForStack * 1.25);
  }

  hs->SetMinimum(0.1);
  hs->Draw("HIST");
  sumMC->SetTitle("");
  TH1* histoForErrors = (TH1*)sumMC->Clone("histoForErrors");
  histoForErrors->SetLineWidth(1);
  histoForErrors->SetLineColor(0);
  histoForErrors->SetFillColor(kTeal-7);
  histoForErrors->SetMarkerSize(0);
  //histoForErrors->SetFillStyle(3002);
  histoForErrors->SetFillStyle(1001);
  histoForErrors->Draw("E2SAME");

  TH1* histoForLine = (TH1*)sumMC->Clone("histoForLine");
  histoForLine->SetLineWidth(2);
  histoForLine->SetLineColor(kBlack);
  histoForLine->SetFillStyle(0);
  histoForLine->Draw("HISTSAME");

  if (isDataPresent_)
    sumDATA->Draw("SAME E X0");
  for (size_t is = 0; is != histosMCSig.size(); is++) {
    if (isSignalStackOnBkg_ == true)
      histosMCSig.at(is)->Draw("HISTO SAME");
    else
      histosMCSigOrig.at(is)->Draw("HISTO SAME");
  }

  if (histoName.find("candMass") != std::string::npos) {
    double limInt0 = 400.0;
    //double limInt1 = 1400.0; //Not used right now
    double limInt2 = 2400.0;
    int binInt0 = sumMC->FindBin(limInt0);
    //int binInt1 = sumMC->FindBin(limInt1);
    int binInt2 = sumMC->FindBin(limInt2);
    double errInt = 0.0;
    double mcInt = sumMC->IntegralAndError(binInt0, binInt2, errInt);
    cout << "Integral of total MC in range [" << limInt0 << "," << limInt2 << "] = " << mcInt << " +/- " << errInt << endl;
    if (isDataPresent_) {
      double dataInt = sumDATA->Integral(binInt0, binInt2);
      cout << "Integral of total DATA in range [" << limInt0 << "," << limInt2 << "] = " << dataInt << " +/- " << sqrt(dataInt) << endl;
    }
  }

  // For the legend, we have to tokenize the name "histos_XXX.root"
  TLegend* leg = new TLegend(0.35, 0.72, 0.92, 0.93);
  leg->SetMargin(0.4);
  leg->SetNColumns(2);
  leg->SetFillStyle(0);
  if (makeRatio_ ) leg->SetTextSize(0.038);
  else leg->SetTextSize(0.040);
  if (isDataPresent_) leg->AddEntry(sumDATA, Form("Data (%.0f)",sumDataIntegral), "ep");
  leg->AddEntry(histoForErrors, "Stat. Unc.", "f");
  for (int i = histosMC.size()-1; i != -1; --i)
    leg->AddEntry(histosMC.at(i), Form("%s (%.0f)",labels.at(i).c_str(), yieldMC.at(i)), "f");
    //leg->AddEntry(histosMC.at(i), labels.at(i).c_str(), "f");
  if (histosMCSig.size() > 0) {
    char rescalingLabel[64];
    for (size_t i = 0; i != histosMCSig.size(); ++i) {
      sprintf(rescalingLabel, " (x%g)", kFactorsSig_.at(i));
      std::string rescalingStr(rescalingLabel);
      //if (kFactorsSig_.at(i) != 1.0)leg->AddEntry(histosMCSig.at(i), (labelsSig.at(i) + rescalingStr).c_str(), "lf");
      if (false)leg->AddEntry(histosMCSig.at(i), (labelsSig.at(i) + rescalingStr).c_str(), "lf");
      //else leg->AddEntry(histosMCSigOrig.at(i), (labelsSig.at(i)).c_str(), "f");
      else leg->AddEntry(histosMCSigOrig.at(i), "G_{bulk} 2 TeV", "f");
    }
  }
  leg->SetFillColor(kWhite);
  leg->Draw();

  // Nice labels
  CMS_lumi(cv,0,10,true,"Preliminary");
  //TMathText* t = makeCMSPreliminaryTop(13, 0.15, 0.93);
  //TMathText* c = makeChannelLabel(1, flavour_, true, 0.2, 0.83);
  //TMathText* l = makeCMSLumi(166.94, 0.2, 0.76);
  //t->Draw();
  //c->Draw();
  //l->Draw();
  
  /*
  //============ Save the full background histogram ============

  //printf("%s\n",histoName.c_str());
  if(histoName == "h_nsubj21") {
    printf("Saving the full background histogram...\n");
    TFile* fullBkg = TFile::Open("forOptimization.root","RECREATE");
    sumMC->Write();
    histosMCSigOrig.at(0)->Write();
    fullBkg->Close();
  }
  */

  //============ Data/MC ratio ==============

  TLine* lineAtOne = NULL;
  if (isDataPresent_) {
    fPads2->cd();
    fPads2->SetGridx();
    fPads2->SetGridy();

    TH1D* histoRatio = (TH1D*)sumDATA->Clone("ratio");
    histoRatio->SetDirectory(0);
    histoRatio->SetTitle("");
    histoRatio->Divide(sumMC);
    histoRatio->GetYaxis()->SetRangeUser(0, 2);
    histoRatio->GetYaxis()->SetTitle("Data / MC");
    histoRatio->GetYaxis()->SetTitleOffset(0.43);
    histoRatio->GetYaxis()->SetTitleSize(0.15);
    histoRatio->GetYaxis()->SetLabelSize(0.07);
    histoRatio->GetXaxis()->SetTitle("");
    histoRatio->GetXaxis()->SetTitleOffset(0.01);
    histoRatio->GetXaxis()->SetLabelSize(0.09);
    histoRatio->SetMarkerStyle(1);
    histoRatio->Draw("p");

    lineAtOne = new TLine(histoRatio->GetXaxis()->GetXmin(), 1, histoRatio->GetXaxis()->GetXmax(), 1);
    lineAtOne->SetLineColor(2);
    lineAtOne->Draw();

    TPaveText *pave1 = new TPaveText(0.20,0.83,0.42,0.93,"NDC");
    pave1->SetBorderSize(0);
    pave1->SetFillColor(0);
    pave1->SetFillStyle(1001);
    pave1->SetTextSize(0.10);
    pave1->AddText(Form("Scale Factor = %.3f",sumDataIntegral / sumBkgAtTargetLumi));
    pave1->Draw();

  }

  //============ Data-MC/Error ==============

  TLine* lineAtZero = NULL;
  TLine* lineAtPlusTwo = NULL;
  TLine* lineAtMinusTwo = NULL;
  if (makeRatio_ && isDataPresent_) {
    fPads3->cd();

    fPads3->SetGridx();
    fPads3->SetGridy();

    double thisYmin = -5;
    double thisYmax = 5;

    TVectorD nsigma_x(sumDATA->GetNbinsX());
    TVectorD nsigma_y(sumDATA->GetNbinsX());

    for (int ibin = 0; ibin != sumDATA->GetNbinsX(); ++ibin) {

      double Data = sumDATA->GetBinContent(ibin + 1);
      double Bkg = sumMC->GetBinContent(ibin + 1);
      double eData = sumDATA->GetBinError(ibin + 1);
      double eBkg = sumMC->GetBinError(ibin + 1);
      double x = sumDATA->GetBinCenter(ibin + 1);

      double diff = Data - Bkg;
      double sigma = sqrt((eData * eData) + (eBkg * eBkg));

      if (sigma != 0.0 && Data != 0.0) {
        nsigma_x[ibin] = x;
        nsigma_y[ibin] = diff / sigma;
      } else {
        nsigma_x[ibin] = +999999;
        nsigma_y[ibin] = 0;
      }
    }


    if (nsigma_x.GetNoElements() != 0) {
      TGraph *nsigmaGraph = new TGraph(nsigma_x, nsigma_y);
      nsigmaGraph->SetTitle("");
      nsigmaGraph->GetYaxis()->SetRangeUser(thisYmin, thisYmax);
      nsigmaGraph->GetYaxis()->SetTitle("(Data-Bkg)/#sigma");
      nsigmaGraph->GetYaxis()->SetTitleOffset(0.43);
      nsigmaGraph->GetYaxis()->SetTitleSize(0.15);
      nsigmaGraph->GetYaxis()->SetLabelSize(0.07);
      nsigmaGraph->GetXaxis()->SetTitle("");
      nsigmaGraph->GetXaxis()->SetLimits(sumMC->GetXaxis()->GetXmin() , sumMC->GetXaxis()->GetXmax());
      nsigmaGraph->GetXaxis()->SetRangeUser(sumMC->GetXaxis()->GetXmin() , sumMC->GetXaxis()->GetXmax());
      nsigmaGraph->GetXaxis()->SetTitleOffset(0.01);
      nsigmaGraph->GetXaxis()->SetLabelSize(0.09);
      nsigmaGraph->SetMarkerStyle(8);
      nsigmaGraph->SetMarkerSize(0.8);
      nsigmaGraph->Draw("ap");
    }

    fPads3->Update();

    lineAtZero = new TLine(sumMC->GetXaxis()->GetXmin(), 0, sumMC->GetXaxis()->GetXmax(), 0);
    lineAtZero->SetLineColor(2);
    lineAtZero->Draw();
    lineAtPlusTwo = new TLine(sumMC->GetXaxis()->GetXmin(), 2, sumMC->GetXaxis()->GetXmax(), 2);
    lineAtPlusTwo->SetLineColor(2);
    lineAtPlusTwo->SetLineStyle(2);
    lineAtPlusTwo->Draw();
    lineAtMinusTwo = new TLine(sumMC->GetXaxis()->GetXmin(), -2, sumMC->GetXaxis()->GetXmax(), -2);
    lineAtMinusTwo->SetLineColor(2);
    lineAtMinusTwo->SetLineStyle(2);
    lineAtMinusTwo->Draw();

    Double_t chi2ndf = sumDATA->Chi2Test(sumMC,"UW CHI2/NDF");
    TPaveText *pave2 = new TPaveText(0.72,0.72,0.92,0.92,"NDC");
    pave2->SetBorderSize(0);
    pave2->SetFillStyle(0);
    pave2->AddText(Form("#chi^{2} / ndf = %.4f",chi2ndf));
    pave2->Draw();
  }

  // Save the picture
  char buffer[256];
  cv->SetLogy(false);
  if (debug_) printf("%s,%s\n",nameOutDir_.c_str(), histoName.c_str());
  sprintf(buffer, "%s/png/can_%s.png", nameOutDir_.c_str(), histoName.c_str());
  cv->SaveAs(buffer);
  sprintf(buffer, "%s/root/can_%s.root", nameOutDir_.c_str(), histoName.c_str());
  cv->SaveAs(buffer);
  sprintf(buffer, "%s/pdf/can_%s.pdf", nameOutDir_.c_str(), histoName.c_str());
  cv->SaveAs(buffer);
  sprintf(buffer, "%s/eps/can_%s.eps", nameOutDir_.c_str(), histoName.c_str());
  cv->SaveAs(buffer);
  if (isDataPresent_) {
    fPads1->cd();
    fPads1->SetLogy(true);
  } else {
    cv->SetLogy(true);
  }
  //-- resize y axis --
  hs->SetMaximum(10 * maximumForStack);
  cv->Update();
  cv->Modified(true);
  cv->Draw();
  sprintf(buffer, "%s/png/LOG_can_%s.png", nameOutDir_.c_str(), histoName.c_str());
  cv->SaveAs(buffer);
  sprintf(buffer, "%s/root/LOG_can_%s.root", nameOutDir_.c_str(), histoName.c_str());
  cv->SaveAs(buffer);
  sprintf(buffer, "%s/pdf/LOG_can_%s.pdf", nameOutDir_.c_str(), histoName.c_str());
  cv->SaveAs(buffer);
  sprintf(buffer, "%s/eps/LOG_can_%s.eps", nameOutDir_.c_str(), histoName.c_str());
  cv->SaveAs(buffer);

  if (debug_) {
    printf("***********************\n");
  }
}
