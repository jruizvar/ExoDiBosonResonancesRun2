// system include files
#include <iostream>
#include <memory>

// user include files
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CompositeCandidate.h"
#include "DataFormats/Candidate/interface/CompositeCandidateFwd.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "ExoDiBosonResonances/EDBRLeptons/interface/TrackerMuonSelector.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/Exception.h"

#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

#include "EDBRChannels.h"
#include "TAxis.h"
#include "TEfficiency.h"
#include "TFile.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TString.h"
#include "TTree.h"

class EDBRTreeMaker : public edm::EDAnalyzer {
public:
  explicit EDBRTreeMaker(const edm::ParameterSet&);
  ~EDBRTreeMaker();
  
private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;

  // Parameters to steer the treeDumper
  bool isGen_;
  bool isData_;
  int originalNEvents_;
  double crossSectionPb_;
  double targetLumiInvPb_;
  std::string EDBRChannel_;
  edm::FileInPath puWeights_;
  edm::FileInPath egammaSFs_;
  edm::FileInPath   muonSFs_;
  edm::FileInPath  muIsoSFs_;
  edm::FileInPath elrecoSFs_;
  edm::FileInPath eltriggerSFs_;
  edm::FileInPath mutriggerSFs_;
  edm::FileInPath ewkCorrect_;
  edm::EDGetTokenT<reco::VertexCollection> vertexToken_;
  edm::EDGetTokenT<bool> elHltToken;
  edm::EDGetTokenT<bool> muHltToken;
  edm::EDGetTokenT<edm::ValueMap<bool>  >    matchElHltToken;
  edm::EDGetTokenT<edm::ValueMap<bool>  >    matchMuHltToken;
  edm::EDGetTokenT<edm::ValueMap<float> >   deltaRElHltToken;
  edm::EDGetTokenT<edm::ValueMap<float> >   deltaRMuHltToken;
  edm::EDGetTokenT<edm::ValueMap<float> >  deltaPtElHltToken;
  edm::EDGetTokenT<edm::ValueMap<float> >  deltaPtMuHltToken;
  edm::EDGetTokenT<double> rhoToken;
  edm::EDGetTokenT<reco::CompositeCandidateView> gravitonsToken;
  edm::EDGetTokenT<pat::METCollection> metToken;
  edm::EDGetTokenT<pat::ElectronCollection> electronsToken;
  edm::EDGetTokenT<pat::MuonCollection> muonsToken;
  edm::EDGetTokenT<pat::JetCollection> jetsToken;
  edm::EDGetTokenT<std::vector<PileupSummaryInfo> > puInfoToken;
  edm::EDGetTokenT<GenEventInfoProduct> genEvtInfoToken;
  edm::EDGetTokenT<reco::CandidateCollection> genleptonicZ_;
  edm::EDGetTokenT<reco::CandidateCollection> genhadronicZ_;
  edm::EDGetTokenT<reco::CandidateView> zhadtoken;
  edm::EDGetTokenT<reco::CandidateView> zleptoken;

  //------------------------ GENERAL ----------------------------------------------
  int nVtx;
  int numCands;
  int nevent, run, lumisec;
  int channel, lep, reg;
  double recoWeight, triggerWeight, lumiWeight, pileupWeight, genWeight, leptonWeight, ewkWeight;
  double totalWeight;
  int trigger;

  //------------------------ GENERATOR ----------------------------------------------
  double genptZl,genptZh,genetaZl,genetaZh,genphiZl,genphzZh,genmassZl,genmassZh;
  double genptl1,genptl2,genetal1,genetal2,genphil1,genphil2,genmassl1,genmassl2;
  double genptq1,genptq2,genetaq1,genetaq2,genphiq1,genphiq2,genmassq1,genmassq2;
  double genptG ,genetaG,genphiG,genmassG;

  // single reco object quantities
  int passVlep, passVhad;
  
  //------------------------ V quantities ------------------------------------------
  double ptVlep, ptVhad, yVlep, yVhad, phiVlep, phiVhad, massVlep, massVhad, mtVlep, massVhadSD;

  //------------------------- MET ---------------------------------------------------
  double met, metPhi;

  //-----------------------MET FROM GRAVITON ----------------------------------------
  double metpt, metphi;

  //---------------------- JETS ------------------------------------------------------
  int    numjets;
  double tau1,      tau2,     tau3,       tau21;
  double etjet1,    ptjet1,   etajet1,    phijet1;
  double ptCorUp,   ptCorDown;
  double massjet1,  softjet1, prunedjet1;
  double rhojet1;                  // SRR : Jet Rho Ratio (m/pt*R)^2
  double nhfjet1,   chfjet1;       // neutral and charged hadron energy fraction
  double nemfjet1,  cemfjet1;      // neutral and charged EM fraction
  int    nmultjet1, cmultjet1;     // neutral and charged multiplicity
  int    nsubjets;                 // number of softdrop subjets

  //-------------------- LEPTONS -----------------------------------------------------
  double ptlep1,    ptlep2;
  double etalep1,   etalep2;
  double philep1,   philep2;
  double miniIso1,  miniIso2;
  int    charge1,   charge2;
  int    pdgId1,    pdgId2;

  //--------------------DELTAS ------------------------------------------------------- 
  double deltaRleplep, deltaRlepjet, delPhilepmet, delPhijetmet, deltaphijetmet;

  //-------------------CANDIDATES MASS -----------------------------------------------
  double candMass;
  double candTMass; // transverse mass

  //-------------------- HIGH LEVEL TRIGGER ------------------------------------------
  int    elhltbit;
  int    muhltbit;
  int    matchHlt1;
  int    matchHlt2;
  double deltaRlep1Obj;
  double deltaRlep2Obj;
  double deltaPtlep1Obj;
  double deltaPtlep2Obj;

  // Electron ID 
  double d01,              d02;
  double dz1,              dz2;
  double etel1,            etel2;
  double ptel1,            ptel2;
  double etaSC1,           etaSC2;
  double dEtaIn1,          dEtaIn2;
  double dPhiIn1,          dPhiIn2;
  double hOverE1,          hOverE2;
  double caloIso1,         caloIso2;
  double ooEmooP1,         ooEmooP2;
  double trackIso1,        trackIso2;
  double dEtaSeed1,        dEtaSeed2; 
  double sigmaIEtaIEta1,   sigmaIEtaIEta2;
  double e1x5overE5x5_1,   e1x5overE5x5_2;
  double e2x5overE5x5_1,   e2x5overE5x5_2;
  double rho; // energy density
  double eeDeltaR;
  int    barrel1,          barrel2;
  int    endcap1,          endcap2;
  int    HEEP1,            HEEP2;
  int    heep1,            heep2;
  int    LOOSE1,           LOOSE2;
  int    loose1,           loose2;
  int    ecalDriven1,      ecalDriven2;
  int    missingHits1,     missingHits2;
  int    passConVeto1,     passConVeto2;

  // Muon ID 
  int    looseMu1,         looseMu2;
  int    mediumMu1,        mediumMu2;
  int    tightMu1,         tightMu2;
  int    highPtMu1,        highPtMu2;
  int    trackerMu1,       trackerMu2;
  int    isPF1,            isPF2;
  int    isGlobalMu1,      isGlobalMu2;
  int    isTrackerMu1,     isTrackerMu2;
  int    matchedStations1, matchedStations2;
  int    pixelHits1,       pixelHits2;
  int    trackerLayers1,   trackerLayers2;
  double relativeError1,   relativeError2;
  double dBCut1,           dBCut2;
  double longiCut1,        longiCut2;
  double pfIso03R1,        pfIso03R2;
  double pfIso04R1,        pfIso04R2;
  double pTtuneP1,         pTtuneP2;

  void setDummyValues();

  edm::Service<TFileService> fs;
  TTree* outTree_;
  TFile *f1, *f2, *f3, *f4, *f5, *f6, *f7;
  TF1   *g1;
  TH1D  *h1;
  TH2F  *h2, *h3, *h4, *h5, *h6, *h7, *h8, *h9;

};

EDBRTreeMaker::EDBRTreeMaker(const edm::ParameterSet& iConfig):
  isGen_           (                                   iConfig.getParameter<bool>          ( "isGen"             ) ),
  originalNEvents_ (                                   iConfig.getParameter<int>           ( "originalNEvents"   ) ),
  crossSectionPb_  (                                   iConfig.getParameter<double>        ( "crossSectionPb"    ) ),
  targetLumiInvPb_ (                                   iConfig.getParameter<double>        ( "targetLumiInvPb"   ) ),
  EDBRChannel_     (                                   iConfig.getParameter<std::string>   ( "EDBRChannel"       ) ),
  vertexToken_     ( consumes<reco::VertexCollection>( iConfig.getParameter<edm::InputTag> ( "vertex"          ) ) )
{
  using namespace edm;

  if( iConfig.existsAs<bool>("isData") )
       isData_ = iConfig.getParameter<bool> ("isData");
  else isData_ = true;

  if( iConfig.existsAs<FileInPath>("elrecoSFs") )
       elrecoSFs_ = iConfig.getParameter<FileInPath>("elrecoSFs") ;

  if( iConfig.existsAs<FileInPath>("egammaSFs") )
       egammaSFs_ = iConfig.getParameter<FileInPath>("egammaSFs") ;

  if( iConfig.existsAs<FileInPath>("muonSFs") )
       muonSFs_ = iConfig.getParameter<FileInPath>("muonSFs") ;

  if( iConfig.existsAs<FileInPath>("muIsoSFs") )
       muIsoSFs_ = iConfig.getParameter<FileInPath>("muIsoSFs") ;

  if( iConfig.existsAs<FileInPath>("elrecoSFs") )
       elrecoSFs_ = iConfig.getParameter<FileInPath>("elrecoSFs") ;

  if( iConfig.existsAs<FileInPath>("eltriggerSFs") )
       eltriggerSFs_ = iConfig.getParameter<FileInPath>("eltriggerSFs") ;

  if( iConfig.existsAs<FileInPath>("mutriggerSFs") )
       mutriggerSFs_ = iConfig.getParameter<FileInPath>("mutriggerSFs") ;

  if( iConfig.existsAs<FileInPath>("puWeights") )
       puWeights_ = iConfig.getParameter<FileInPath>("puWeights") ;

  if( iConfig.existsAs<FileInPath>("ewkCorrect") )
       ewkCorrect_ = iConfig.getParameter<FileInPath>("ewkCorrect") ;

  elHltToken        = consumes<bool>(            InputTag("hltMatchingElectrons", "trigBit"   ));
  muHltToken        = consumes<bool>(            InputTag("hltMatchingMuons",     "trigBit"   ));
  matchElHltToken   = consumes<ValueMap<bool> >( InputTag("hltMatchingElectrons","matchHlt"   ));
  matchMuHltToken   = consumes<ValueMap<bool> >( InputTag("hltMatchingMuons",    "matchHlt"   ));
  deltaRElHltToken  = consumes<ValueMap<float> >(InputTag("hltMatchingElectrons","deltaR"     ));
  deltaRMuHltToken  = consumes<ValueMap<float> >(InputTag("hltMatchingMuons",    "deltaR"     ));
  deltaPtElHltToken = consumes<ValueMap<float> >(InputTag("hltMatchingElectrons","deltaPt"    ));
  deltaPtMuHltToken = consumes<ValueMap<float> >(InputTag("hltMatchingMuons",    "deltaPt"    ));
  rhoToken          = consumes<double>(          InputTag("fixedGridRhoFastjetAll"            ));
  gravitonsToken    = consumes<reco::CompositeCandidateView>(  InputTag("graviton","","TEST"  ));
  metToken          = consumes<pat::METCollection>(            InputTag("slimmedMETs"         ));
  electronsToken    = consumes<pat::ElectronCollection>(       InputTag("slimmedElectrons"    ));
  muonsToken        = consumes<pat::MuonCollection>(           InputTag("slimmedMuons"        ));
  jetsToken         = consumes<pat::JetCollection>(            InputTag("slimmedJetsAK8"      ));
  puInfoToken       = consumes<std::vector<PileupSummaryInfo>>(InputTag("slimmedAddPileupInfo"));
  genEvtInfoToken   = consumes<GenEventInfoProduct>(           InputTag("generator"           ));
                                     
  genleptonicZ_     =consumes<reco::CandidateCollection>( InputTag("leptonicDecay::TEST" ));
  genhadronicZ_     =consumes<reco::CandidateCollection>( InputTag("hadronicDecay::TEST" ));


  consumes<TriggerResults>(InputTag("TriggerResults","","TEST"));
  zleptoken = consumes<reco::CandidateView>(InputTag("bestLeptonicV","","TEST"));
  zhadtoken = consumes<reco::CandidateView>(InputTag("bestHadronicV","","TEST"));


  if(EDBRChannel_ == "VZ_CHANNEL")
    channel=VZ_CHANNEL;
  else if(EDBRChannel_ == "VW_CHANNEL")
    channel=VW_CHANNEL;
  else if(EDBRChannel_ == "VH_CHANNEL")
    channel=VH_CHANNEL;
  else if(EDBRChannel_ == "VZnu_CHANNEL")
    channel=VZnu_CHANNEL;
  else {
    cms::Exception ex("InvalidConfiguration");
    ex << "Unknown channel " << EDBRChannel_  
       << ". Please check EDBRTreeMaker.cc for allowed values.";
    throw ex;
  }

  outTree_ = fs->make<TTree>("EDBRCandidates","EDBR Candidates");

  // Generator info
  
  outTree_->Branch("genptZl",&genptZl,"genptZl/D");
  outTree_->Branch("genptZh",&genptZh,"genptZh/D");
  outTree_->Branch("genetaZl",&genetaZl,"genetaZl/D");
  outTree_->Branch("genetaZh",&genetaZh,"genetaZh/D");
  outTree_->Branch("genphiZl",&genphiZl,"genphiZl/D");
  outTree_->Branch("genphzZh",&genphzZh,"genphzZh/D");
  outTree_->Branch("genmassZl",&genmassZl,"genmassZl/D");
  outTree_->Branch("genmassZh",&genmassZh,"genmassZh/D");
  outTree_->Branch("genptl1",&genptl1,"genptl1/D");
  outTree_->Branch("genptl2",&genptl2,"genptl2/D");
  outTree_->Branch("genetal1",&genetal1,"genetal1/D");
  outTree_->Branch("genetal2",&genetal2,"genetal2/D");
  outTree_->Branch("genphil1",&genphil1,"genphil1/D");
  outTree_->Branch("genphil2",&genphil2,"genphil2/D");
  outTree_->Branch("genmassl1",&genmassl1,"genmassl1/D");
  outTree_->Branch("genmassl2",&genmassl2,"genmassl2/D");
  outTree_->Branch("genptq1",&genptq1,"genptq1/D");
  outTree_->Branch("genptq2",&genptq2,"genptq2/D");
  outTree_->Branch("genetaq1",&genetaq1,"genetaq1/D");
  outTree_->Branch("genetaq2",&genetaq2,"genetaq2/D");
  outTree_->Branch("genphiq1",&genphiq1,"genphiq1/D");
  outTree_->Branch("genphiq2",&genphiq2,"genphiq2/D");
  outTree_->Branch("genmassq1",&genmassq1,"genmassq1/D");
  outTree_->Branch("genmassq2",&genmassq2,"genmassq2/D");
  outTree_->Branch("genptG",&genptG,"genptG/D");
  outTree_->Branch("genetaG",&genetaG,"genetaG/D");
  outTree_->Branch("genphiG",&genphiG,"genphiG/D");
  outTree_->Branch("genmassG",&genmassG,"genmassG/D");


  // Basic event quantities
  outTree_->Branch("event"            ,&nevent           ,"event/I"           );
  outTree_->Branch("run"              ,&run              ,"run/I"             );
  outTree_->Branch("lumisec"          ,&lumisec          ,"lumisec/I"         );
  outTree_->Branch("nVtx"             ,&nVtx             ,"nVtx/I"            );
  outTree_->Branch("numCands"         ,&numCands         ,"numCands/I"        );
  outTree_->Branch("ptVlep"           ,&ptVlep           ,"ptVlep/D"          );
  outTree_->Branch("ptVhad"           ,&ptVhad           ,"ptVhad/D"          );
  outTree_->Branch("yVlep"            ,&yVlep            ,"yVlep/D"           );
  outTree_->Branch("yVhad"            ,&yVhad            ,"yVhad/D"           );
  outTree_->Branch("phiVlep"          ,&phiVlep          ,"phiVlep/D"         );
  outTree_->Branch("phiVhad"          ,&phiVhad          ,"phiVhad/D"         );
  outTree_->Branch("massVlep"         ,&massVlep         ,"massVlep/D"        );
  outTree_->Branch("mtVlep"           ,&mtVlep           ,"mtVlep/D"          );
  outTree_->Branch("massVhad"         ,&massVhad         ,"massVhad/D"        );
  outTree_->Branch("massVhadSD"       ,&massVhadSD       ,"massVhadSD/D"      );
  outTree_->Branch("tau1"             ,&tau1             ,"tau1/D"            );
  outTree_->Branch("tau2"             ,&tau2             ,"tau2/D"            );
  outTree_->Branch("tau3"             ,&tau3             ,"tau3/D"            );
  outTree_->Branch("tau21"            ,&tau21            ,"tau21/D"           );
  outTree_->Branch("lep"              ,&lep              ,"lep/I"             );
  outTree_->Branch("region"           ,&reg              ,"region/I"          );
  outTree_->Branch("channel"          ,&channel          ,"channel/I"         );
  outTree_->Branch("candMass"         ,&candMass         ,"candMass/D"        );
  outTree_->Branch("candTMass"        ,&candTMass        ,"candTMass/D"       );

  // HLT info 
  outTree_->Branch("elhltbit"         ,&elhltbit         ,"elhltbit/I"        );
  outTree_->Branch("muhltbit"         ,&muhltbit         ,"muhltbit/I"        );
  outTree_->Branch("matchHlt1"        ,&matchHlt1        ,"matchHlt1/I"       );
  outTree_->Branch("matchHlt2"        ,&matchHlt2        ,"matchHlt2/I"       );
  outTree_->Branch("deltaRlep1Obj"    ,&deltaRlep1Obj    ,"deltaRlep1Obj/D"   );
  outTree_->Branch("deltaRlep2Obj"    ,&deltaRlep2Obj    ,"deltaRlep2Obj/D"   );
  outTree_->Branch("deltaPtlep1Obj"   ,&deltaPtlep1Obj   ,"deltaPtlep1Obj/D"  );
  outTree_->Branch("deltaPtlep2Obj"   ,&deltaPtlep2Obj   ,"deltaPtlep2Obj/D"  );
 
  // Muon ID quantities
  outTree_->Branch("pTtuneP1"         ,&pTtuneP1         ,"pTtuneP1/D"        );
  outTree_->Branch("pTtuneP2"         ,&pTtuneP2         ,"pTtuneP2/D"        );
  outTree_->Branch("looseMu1"         ,&looseMu1         ,"looseMu1/I"        );
  outTree_->Branch("looseMu2"         ,&looseMu2         ,"looseMu2/I"        );
  outTree_->Branch("mediumMu1"        ,&mediumMu1        ,"mediumMu1/I"       );
  outTree_->Branch("mediumMu2"        ,&mediumMu2        ,"mediumMu2/I"       );
  outTree_->Branch("tightMu1"         ,&tightMu1         ,"tightMu1/I"        );
  outTree_->Branch("tightMu2"         ,&tightMu2         ,"tightMu2/I"        );
  outTree_->Branch("trackerMu1"       ,&trackerMu1       ,"trackerMu1/I"      );
  outTree_->Branch("trackerMu2"       ,&trackerMu2       ,"trackerMu2/I"      );
  outTree_->Branch("highPtMu1"        ,&highPtMu1        ,"highPtMu1/I"       );
  outTree_->Branch("highPtMu2"        ,&highPtMu2        ,"highPtMu2/I"       );
  outTree_->Branch("isPF1"            ,&isPF1            ,"isPF1/I"           );
  outTree_->Branch("isPF2"            ,&isPF2            ,"isPF2/I"           );
  outTree_->Branch("isGlobalMu1"      ,&isGlobalMu1      ,"isGlobalMu1/I"     );
  outTree_->Branch("isGlobalMu2"      ,&isGlobalMu2      ,"isGlobalMu2/I"     );
  outTree_->Branch("isTrackerMu1"     ,&isTrackerMu1     ,"isTrackerMu1/I"    );
  outTree_->Branch("isTrackerMu2"     ,&isTrackerMu2     ,"isTrackerMu2/I"    );
  outTree_->Branch("matchedStations1" ,&matchedStations1 ,"matchedStations1/I");
  outTree_->Branch("matchedStations2" ,&matchedStations2 ,"matchedStations2/I");
  outTree_->Branch("pixelHits1"       ,&pixelHits1       ,"pixelHits1/I"      );
  outTree_->Branch("pixelHits2"       ,&pixelHits2       ,"pixelHits2/I"      );
  outTree_->Branch("trackerLayers1"   ,&trackerLayers1   ,"trackerLayers1/I"  );
  outTree_->Branch("trackerLayers2"   ,&trackerLayers2   ,"trackerLayers2/I"  );
  outTree_->Branch("relativeError1"   ,&relativeError1   ,"relativeError1/D"  );
  outTree_->Branch("relativeError2"   ,&relativeError2   ,"relativeError2/D"  );
  outTree_->Branch("dBCut1"           ,&dBCut1           ,"dBCut1/D"          );
  outTree_->Branch("dBCut2"           ,&dBCut2           ,"dBCut2/D"          );
  outTree_->Branch("longiCut1"        ,&longiCut1        ,"longiCut1/D"       );
  outTree_->Branch("longiCut2"        ,&longiCut2        ,"longiCut2/D"       );
  outTree_->Branch("pfIso03R1"        ,&pfIso03R1        ,"pfIso03R1/D"       );
  outTree_->Branch("pfIso03R2"        ,&pfIso03R2        ,"pfIso03R2/D"       );
  outTree_->Branch("pfIso04R1"        ,&pfIso04R1        ,"pfIso04R1/D"       );
  outTree_->Branch("pfIso04R2"        ,&pfIso04R2        ,"pfIso04R2/D"       );

  // Electron ID quantities
  outTree_->Branch("barrel1"          ,&barrel1          ,"barrel1/I"         );
  outTree_->Branch("barrel2"          ,&barrel2          ,"barrel2/I"         );
  outTree_->Branch("endcap1"          ,&endcap1          ,"endcap1/I"         );
  outTree_->Branch("endcap2"          ,&endcap2          ,"endcap2/I"         );
  outTree_->Branch("eeDeltaR"         ,&eeDeltaR         ,"eeDeltaR/D"        );
  outTree_->Branch("etel1"            ,&etel1            ,"etel1/D"           );
  outTree_->Branch("etel2"            ,&etel2            ,"etel2/D"           );
  outTree_->Branch("ptel1"            ,&ptel1            ,"ptel1/D"           );
  outTree_->Branch("ptel2"            ,&ptel2            ,"ptel2/D"           );
  outTree_->Branch("etaSC1"           ,&etaSC1           ,"etaSC1/D"          );
  outTree_->Branch("etaSC2"           ,&etaSC2           ,"etaSC2/D"          );
  outTree_->Branch("dEtaIn1"          ,&dEtaIn1          ,"dEtaIn1/D"         );
  outTree_->Branch("dEtaIn2"          ,&dEtaIn2          ,"dEtaIn2/D"         );
  outTree_->Branch("dEtaSeed1"        ,&dEtaSeed1        ,"dEtaSeed1/D"       );
  outTree_->Branch("dEtaSeed2"        ,&dEtaSeed2        ,"dEtaSeed2/D"       );
  outTree_->Branch("dPhiIn1"          ,&dPhiIn1          ,"dPhiIn1/D"         );
  outTree_->Branch("dPhiIn2"          ,&dPhiIn2          ,"dPhiIn2/D"         );
  outTree_->Branch("hOverE1"          ,&hOverE1          ,"hOverE1/D"         );
  outTree_->Branch("hOverE2"          ,&hOverE2          ,"hOverE2/D"         );
  outTree_->Branch("sigmaIEtaIEta1"   ,&sigmaIEtaIEta1   ,"sigmaIEtaIEta1/D"  );
  outTree_->Branch("sigmaIEtaIEta2"   ,&sigmaIEtaIEta2   ,"sigmaIEtaIEta2/D"  );
  outTree_->Branch("e1x5overE5x5_1"   ,&e1x5overE5x5_1   ,"e1x5overE5x5_1/D"  );
  outTree_->Branch("e1x5overE5x5_2"   ,&e1x5overE5x5_2   ,"e1x5overE5x5_2/D"  );
  outTree_->Branch("e2x5overE5x5_1"   ,&e2x5overE5x5_1   ,"e2x5overE5x5_1/D"  );
  outTree_->Branch("e2x5overE5x5_2"   ,&e2x5overE5x5_2   ,"e2x5overE5x5_2/D"  );
  outTree_->Branch("ooEmooP1"         ,&ooEmooP1         ,"ooEmooP1/D"        );
  outTree_->Branch("ooEmooP2"         ,&ooEmooP2         ,"ooEmooP2/D"        );
  outTree_->Branch("d01"              ,&d01              ,"d01/D"             );
  outTree_->Branch("d02"              ,&d02              ,"d02/D"             );
  outTree_->Branch("dz1"              ,&dz1              ,"dz1/D"             );
  outTree_->Branch("dz2"              ,&dz2              ,"dz2/D"             );
  outTree_->Branch("caloIso1"         ,&caloIso1         ,"caloIso1/D"        );
  outTree_->Branch("caloIso2"         ,&caloIso2         ,"caloIso2/D"        );
  outTree_->Branch("trackIso1"        ,&trackIso1        ,"trackIso1/D"       );
  outTree_->Branch("trackIso2"        ,&trackIso2        ,"trackIso2/D"       );
  outTree_->Branch("rho"              ,&rho              ,"rho/D"             );
  outTree_->Branch("ecalDriven1"      ,&ecalDriven1      ,"ecalDriven1/I"     );
  outTree_->Branch("ecalDriven2"      ,&ecalDriven2      ,"ecalDriven2/I"     );
  outTree_->Branch("missingHits1"     ,&missingHits1     ,"missingHits1/I"    );
  outTree_->Branch("missingHits2"     ,&missingHits2     ,"missingHits2/I"    );
  outTree_->Branch("passConVeto1"     ,&passConVeto1     ,"passConVeto1/I"    );
  outTree_->Branch("passConVeto2"     ,&passConVeto2     ,"passConVeto2/I"    );
  outTree_->Branch("HEEP1"            ,&HEEP1            ,"HEEP1/I"           );
  outTree_->Branch("HEEP2"            ,&HEEP2            ,"HEEP2/I"           );
  outTree_->Branch("heep1"            ,&heep1            ,"heep1/I"           );
  outTree_->Branch("heep2"            ,&heep2            ,"heep2/I"           );
  outTree_->Branch("LOOSE1"           ,&LOOSE1           ,"LOOSE1/I"          );
  outTree_->Branch("LOOSE2"           ,&LOOSE2           ,"LOOSE2/I"          );
  outTree_->Branch("loose1"           ,&loose1           ,"loose1/I"          );
  outTree_->Branch("loose2"           ,&loose2           ,"loose2/I"          );

  // mini isolation for leptons
  outTree_->Branch("miniIso1"         ,&miniIso1         ,"miniIso1/D"        );
  outTree_->Branch("miniIso2"         ,&miniIso2         ,"miniIso2/D"        );
  
  // JEC Uncertainties
  outTree_->Branch("ptCorUp"          ,&ptCorUp          ,"ptCorUp/D"         );
  outTree_->Branch("ptCorDown"        ,&ptCorDown        ,"ptCorDown/D"       );

  // Jet ID quantities
  outTree_->Branch("nhfjet1"          ,&nhfjet1          ,"nhfjet1/D"         );
  outTree_->Branch("chfjet1"          ,&chfjet1          ,"chfjet1/D"         );
  outTree_->Branch("nemfjet1"         ,&nemfjet1         ,"nemfjet1/D"        );
  outTree_->Branch("cemfjet1"         ,&cemfjet1         ,"cemfjet1/D"        );
  outTree_->Branch("nmultjet1"        ,&nmultjet1        ,"nmultjet1/I"       );
  outTree_->Branch("cmultjet1"        ,&cmultjet1        ,"cmultjet1/I"       );

  // Generic kinematic quantities
  outTree_->Branch("nsubjets"         ,&nsubjets         ,"nsubjets/I"        );
  outTree_->Branch("numjets"          ,&numjets          ,"numjets/I"         );
  outTree_->Branch("ptlep1"           ,&ptlep1           ,"ptlep1/D"          );
  outTree_->Branch("ptlep2"           ,&ptlep2           ,"ptlep2/D"          );
  outTree_->Branch("ptjet1"           ,&ptjet1           ,"ptjet1/D"          );
  outTree_->Branch("etjet1"           ,&etjet1           ,"etjet1/D"          );
  outTree_->Branch("rhojet1"          ,&rhojet1          ,"rhojet1/D"         );
  outTree_->Branch("etalep1"          ,&etalep1          ,"etalep1/D"         );
  outTree_->Branch("etalep2"          ,&etalep2          ,"etalep2/D"         );
  outTree_->Branch("etajet1"          ,&etajet1          ,"etajet1/D"         );
  outTree_->Branch("philep1"          ,&philep1          ,"philep1/D"         );
  outTree_->Branch("philep2"          ,&philep2          ,"philep2/D"         );
  outTree_->Branch("charge1"          ,&charge1          ,"charge1/I"         );
  outTree_->Branch("charge2"          ,&charge2          ,"charge2/I"         );
  outTree_->Branch("pdgId1"           ,&pdgId1           ,"pdgId1/I"          );
  outTree_->Branch("pdgId2"           ,&pdgId2           ,"pdgId2/I"          );
  outTree_->Branch("phijet1"          ,&phijet1          ,"phijet1/D"         );
  outTree_->Branch("massjet1"         ,&massjet1         ,"massjet1/D"        );
  outTree_->Branch("softjet1"         ,&softjet1         ,"softjet1/D"        );
  outTree_->Branch("prunedjet1"       ,&prunedjet1       ,"prunedjet1/D"      );
  outTree_->Branch("met"              ,&met              ,"met/D"             );
  outTree_->Branch("metpt"            ,&metpt            ,"metpt/D"           );
  outTree_->Branch("metPhi"           ,&metPhi           ,"metPhi/D"          );
  
  // Other quantities
  outTree_->Branch("recoWeight"       ,&recoWeight       ,"recoWeight/D"      );
  outTree_->Branch("triggerWeight"    ,&triggerWeight    ,"triggerWeight/D"   );
  outTree_->Branch("lumiWeight"       ,&lumiWeight       ,"lumiWeight/D"      );
  outTree_->Branch("pileupWeight"     ,&pileupWeight     ,"pileupWeight/D"    );
  outTree_->Branch("genWeight"        ,&genWeight        ,"genWeight/D"       );
  outTree_->Branch("leptonWeight"     ,&leptonWeight     ,"leptonWeight/D"    );
  outTree_->Branch("ewkWeight"        ,&ewkWeight        ,"ewkWeight/D"       );
  outTree_->Branch("totalWeight"      ,&totalWeight      ,"totalWeight/D"     );
  outTree_->Branch("deltaRleplep"     ,&deltaRleplep     ,"deltaRleplep/D"    );
  outTree_->Branch("delPhilepmet"     ,&delPhilepmet     ,"delPhilepmet/D"    );
  outTree_->Branch("deltaRlepjet"     ,&deltaRlepjet     ,"deltaRlepjet/D"    );
  outTree_->Branch("delPhijetmet"     ,&delPhijetmet     ,"delPhijetmet/D"    );
  outTree_->Branch("deltaphijetmet"   ,&deltaphijetmet   ,"deltaphijetmet/D"  );
  outTree_->Branch("passedtrigger"    ,&trigger          ,"passedtrigger/I"   );
  outTree_->Branch("passVlep"         ,&passVlep         ,"passVlep/I"        );
  outTree_->Branch("passVhad"         ,&passVhad         ,"passVhad/I"        );
  
}

EDBRTreeMaker::~EDBRTreeMaker() {}

void EDBRTreeMaker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   nevent  = iEvent.eventAuxiliary().event();
   run     = iEvent.eventAuxiliary().run();
   lumisec = iEvent.eventAuxiliary().luminosityBlock();
                   
   // ------ analize trigger results ----------//
   Handle<bool> elHlt_handle;
   Handle<bool> muHlt_handle;
   Handle<ValueMap<bool> > matchHlt_handle;
   Handle<ValueMap<float> > deltaPt_handle;
   Handle<ValueMap<float> >  deltaR_handle;

   setDummyValues(); //Initalize variables with dummy values
   bool passed_trigger = iEvent.triggerResultsByName("TEST").accept("triggersel"); 
   if(passed_trigger)
     trigger = 1;

   bool passed_analysis= iEvent.triggerResultsByName("TEST").accept("analysis"); // basically just generator selection for correct flavor semi-leptonic decay

   // save generator information
   if( not iEvent.isRealData() && passed_analysis ){ // event may not have the proper info if it hasn't passed
     Handle< reco::CandidateCollection > genZlep;
     iEvent.getByToken(genleptonicZ_ ,   genZlep);
     if( genZlep->size() ){
         const reco::Candidate& Zlep = (*genZlep)[0];
         const reco::Candidate* genGrav = Zlep.numberOfMothers()>0 ? Zlep.mother(0) : Zlep.clone();
         const reco::Candidate* lep1 = Zlep.daughter(0);
         const reco::Candidate* lep2 = Zlep.daughter(1);
         genptZl          = Zlep.pt();
         genetaZl         = Zlep.eta();
         genphiZl         = Zlep.phi();
         genmassZl        = Zlep.mass();

         genptl1          = lep1->pt();
         genetal1         = lep1->eta();
         genphil1         = lep1->phi();
         genmassl1        = lep1->mass();
         
         genptl2          = lep2->pt();
         genetal2         = lep2->eta();
         genphil2         = lep2->phi();
         genmassl2        = lep2->mass();

         genptG           = genGrav->pt();
         genetaG          = genGrav->eta();
         genphiG          = genGrav->phi();
         genmassG         = genGrav->mass();
     }
     Handle< reco::CandidateCollection > genZhad;
     iEvent.getByToken(genhadronicZ_ ,   genZhad);
     if ( genZhad->size() ){
         const reco::Candidate& Zhad = (*genZhad)[0];
         const reco::Candidate* q1 = Zhad.daughter(0);
         const reco::Candidate* q2 = Zhad.numberOfDaughters()>1 ? Zhad.daughter(1) : q1;

         genptZh          = Zhad.pt();
         genetaZh         = Zhad.eta();
         genphzZh         = Zhad.phi();
         genmassZh        = Zhad.mass();

         genptq1          = q1->pt();
         genetaq1         = q1->eta();
         genphiq1         = q1->phi();
         genmassq1        = q1->mass();

         genptq2          = q2->pt();
         genetaq2         = q2->eta();
         genphiq2         = q2->phi();
         genmassq2        = q2->mass();
     }
   }

   if(passed_analysis){
     // save relevant information for efficiency studies, even if no complete candidate exisist
     Handle<reco::CandidateView> Zhads;
     iEvent.getByToken(zhadtoken,Zhads);
     if(Zhads->size()!=0){
       const reco::Candidate& Zhad  = Zhads->at(0);
       const pat::Jet& hadronicV = dynamic_cast<const pat::Jet&>(Zhad);
       tau1           = hadronicV.userFloat("NjettinessAK8:tau1");
       tau2           = hadronicV.userFloat("NjettinessAK8:tau2");
       tau3           = hadronicV.userFloat("NjettinessAK8:tau3");
       tau21          = tau2/tau1;
       massVhad       = hadronicV.userFloat("ak8PFJetsCHSCorrPrunedMass");
       passVhad = 1;      
     }
     Handle<reco::CandidateView> Zlept;
     iEvent.getByToken(zleptoken,Zlept);
     if(Zlept->size()!=0){
       const reco::Candidate& Zlep  = Zlept->at(0);
       lep = abs(Zlep.daughter(0)->pdgId());
       passVlep = 1;
     }
     Handle<reco::CompositeCandidateView > gravitons;
     iEvent.getByToken(gravitonsToken, gravitons);
     numCands = gravitons->size();
     if(numCands != 0 ) {
       const reco::Candidate& graviton  = gravitons->at(0);
       candMass = graviton.mass();
     }
   }

     
   if(passed_trigger && passed_analysis){ // only fill usual tree if trigger+analysis path passed
     iEvent.getByToken(elHltToken, elHlt_handle);
     iEvent.getByToken(muHltToken, muHlt_handle);
     elhltbit = (int)(*elHlt_handle);
     muhltbit = (int)(*muHlt_handle);

     Handle<reco::CompositeCandidateView > gravitons;
     iEvent.getByToken(gravitonsToken, gravitons);
     numCands = gravitons->size();
     if(numCands != 0 ) {
       const reco::Candidate& graviton  = gravitons->at(0);
       const pat::Jet& hadronicV = dynamic_cast<const pat::Jet&>(*graviton.daughter("hadronicV"));
       
       // met
       Handle<pat::METCollection> metHandle;
       iEvent.getByToken(metToken, metHandle);
       const pat::MET& metCand = metHandle->at(0);
       
       // All the quantities which depend on RECO could go here
       if(not isGen_) {
           // electrons and muons
           Handle<pat::ElectronCollection>   electrons;
           Handle<pat::MuonCollection>           muons;
           iEvent.getByToken(electronsToken, electrons);
           iEvent.getByToken(muonsToken,         muons);

           // number of jets
           Handle<pat::JetCollection>    jets;
           iEvent.getByToken(jetsToken,  jets);
           numjets = jets->size();
           met     = metCand.pt();
           metPhi  = metCand.phi();

           // handle goodOfflinePrimaryVertex collection
           Handle<reco::VertexCollection> vertices;
           iEvent.getByToken(vertexToken_, vertices);
           nVtx = vertices->size();
           const reco::Vertex& vertex = (*vertices)[0];
  
           // Energy density
           Handle< double > rhoHandle;
           iEvent.getByToken(rhoToken, rhoHandle);
           rho = (float)(*rhoHandle);

           //we put the definitions inside the channel
           switch(channel){
               case VZ_CHANNEL:{
                   //**************DEFINITIONS *********************************** 
                   const reco::Candidate& leptonicV = (*graviton.daughter("leptonicV"));
                   // candidate
                   candMass       = graviton.mass();
                   // leptons
                   ptVlep         = leptonicV.pt();
                   yVlep          = leptonicV.eta();
                   phiVlep        = leptonicV.phi();
                   massVlep       = leptonicV.mass();
                   mtVlep         = leptonicV.mt();
                   int leading    = leptonicV.daughter(0)->pt() > leptonicV.daughter(1)->pt() ? 0 : 1; 
                   const reco::Candidate *lepton1 = leptonicV.daughter(      leading);
                   const reco::Candidate *lepton2 = leptonicV.daughter((int)!leading);
                   ptlep1         = lepton1->pt();
                   ptlep2         = lepton2->pt();
                   etalep1        = lepton1->eta();
                   etalep2        = lepton2->eta();
                   philep1        = lepton1->phi();
                   philep2        = lepton2->phi();
                   charge1        = lepton1->charge();
                   charge2        = lepton2->charge();
                   pdgId1         = lepton1->pdgId();
                   pdgId2         = lepton2->pdgId();
                   lep        = abs(lepton1->pdgId());
                   // hadrons
                   ptVhad         = hadronicV.pt();
                   yVhad          = hadronicV.eta();
                   phiVhad        = hadronicV.phi();
                   tau1           = hadronicV.userFloat("NjettinessAK8:tau1");
                   tau2           = hadronicV.userFloat("NjettinessAK8:tau2");
                   tau3           = hadronicV.userFloat("NjettinessAK8:tau3");
                   tau21          = tau2/tau1;
                   etjet1         = hadronicV.et();
                   ptjet1         = hadronicV.pt();
                   etajet1        = hadronicV.eta();
                   phijet1        = hadronicV.phi();
                   massjet1       = hadronicV.mass();
                   softjet1       = hadronicV.userFloat("ak8PFJetsCHSSoftDropMass");
                   prunedjet1     = hadronicV.userFloat("ak8PFJetsCHSPrunedMass");
                   massVhad       = hadronicV.userFloat("ak8PFJetsCHSCorrPrunedMass");
                   ptCorUp        = hadronicV.userFloat("ptCorUp");
                   ptCorDown      = hadronicV.userFloat("ptCorDown");
		   // SRR : get rho ratio. This assumes the subjets are corrected to L2L3.
		   // If not, they must be done on-the-fly with a separate jet corrector. 
		   auto subjetsSD = hadronicV.subjets("SoftDrop");
                   nsubjets       = subjetsSD.size();
		   if ( nsubjets >= 2 ) {
		     auto groomedJet = subjetsSD[0]->p4() + subjetsSD[1]->p4();
		     rhojet1 = std::pow( groomedJet.mass() / (groomedJet.pt() * 0.8), 2.0);
		     massVhadSD     = hadronicV.mass();
		   }

                   //*****************************************************************//
                   //***************************** Jet ID ****************************//
                   //*****************************************************************//
                   nhfjet1        = hadronicV.neutralHadronEnergyFraction();
                   chfjet1        = hadronicV.chargedHadronEnergyFraction();
                   nemfjet1       = hadronicV.neutralEmEnergyFraction();
                   cemfjet1       = hadronicV.chargedEmEnergyFraction();
                   nmultjet1      = hadronicV.neutralMultiplicity();
                   cmultjet1      = hadronicV.chargedMultiplicity();
                   // deltas
                   deltaRleplep   = deltaR(etalep1,philep1,etalep2,philep2);
                   double drl1j   = deltaR(etalep1,philep1,etajet1,phijet1);
                   double drl2j   = deltaR(etalep2,philep2,etajet1,phijet1);
                   deltaRlepjet   = std::min(drl1j,drl2j);
                   delPhilepmet   = deltaPhi(philep1, metPhi);
                   delPhijetmet   = deltaPhi(phijet1, metPhi);
                   //*****************************************************************//
                   //************************* ID for muons **************************//
                   //*****************************************************************//
                   if ( leptonicV.daughter(0)->isMuon() && 
                        leptonicV.daughter(1)->isMuon()    ) {
                        int temp = leptonicV.daughter(0)->pt() > leptonicV.daughter(1)->pt() ? 0 : 1; 
                        const pat::Muon *mu1 = (pat::Muon*)leptonicV.daughter(      temp);
                        const pat::Muon *mu2 = (pat::Muon*)leptonicV.daughter((int)!temp);
                        const Ptr<pat::Muon> mu1Ptr(muons, mu1->userInt("slimmedIndex") );
                        const Ptr<pat::Muon> mu2Ptr(muons, mu2->userInt("slimmedIndex") );
                        iEvent.getByToken(deltaRMuHltToken,   deltaR_handle);
                        iEvent.getByToken(deltaPtMuHltToken,  deltaPt_handle);
                        iEvent.getByToken(matchMuHltToken, matchHlt_handle);
                        deltaRlep1Obj    =      (*deltaR_handle)[mu1Ptr];
                        deltaRlep2Obj    =      (*deltaR_handle)[mu2Ptr];
                        deltaPtlep1Obj   =      (*deltaPt_handle)[mu1Ptr];
                        deltaPtlep2Obj   =      (*deltaPt_handle)[mu2Ptr];
                        matchHlt1        = (int)(*matchHlt_handle)[mu1Ptr]; 
                        matchHlt2        = (int)(*matchHlt_handle)[mu2Ptr]; 
                        // isolation with delta beta correction
                        pfIso03R1         = mu1->userFloat("pfIso03R");;
                        pfIso03R2         = mu2->userFloat("pfIso03R");;
                        pfIso04R1         = mu1->userFloat("pfIso04R");;
                        pfIso04R2         = mu2->userFloat("pfIso04R");;
                        trackerMu1        = (int)hptm::isTrackerMuon(*mu1, vertex);
                        trackerMu2        = (int)hptm::isTrackerMuon(*mu2, vertex);
                        looseMu1          = (int)muon::isLooseMuon(  *mu1);
                        looseMu2          = (int)muon::isLooseMuon(  *mu2);
                        mediumMu1         = (int)muon::isMediumMuon( *mu1);
                        mediumMu2         = (int)muon::isMediumMuon( *mu2);
                        tightMu1          = (int)muon::isTightMuon(  *mu1, vertex);
                        tightMu2          = (int)muon::isTightMuon(  *mu2, vertex);
                        highPtMu1         = (int)muon::isHighPtMuon( *mu1, vertex);
                        highPtMu2         = (int)muon::isHighPtMuon( *mu2, vertex);
                        isPF1             = mu1->isPFMuon();
                        isPF2             = mu2->isPFMuon();
                        isGlobalMu1       = mu1->isGlobalMuon();
                        isGlobalMu2       = mu2->isGlobalMuon();
                        isTrackerMu1      = mu1->isTrackerMuon();
                        isTrackerMu2      = mu2->isTrackerMuon();
                        matchedStations1  = mu1->numberOfMatchedStations();
                        matchedStations2  = mu2->numberOfMatchedStations();
                        trackIso1         = mu1->isolationR03().sumPt;                       // tracker isolation
                        trackIso2         = mu2->isolationR03().sumPt;                       // tracker isolation
                        pTtuneP1          = mu1->userFloat("pTtuneP");
                        pTtuneP2          = mu2->userFloat("pTtuneP");
                        if ( mu1->innerTrack().isNonnull() ){
                           pixelHits1     = mu1->innerTrack()->hitPattern().numberOfValidPixelHits();
                           trackerLayers1 = mu1->innerTrack()->hitPattern().trackerLayersWithMeasurement();
                           trackIso2     -= deltaRleplep<0.3 ? mu1->innerTrack()->pt() : 0; // footprint removal
                        }
                        if ( mu2->innerTrack().isNonnull() ){
                           pixelHits2     = mu2->innerTrack()->hitPattern().numberOfValidPixelHits();
                           trackerLayers2 = mu2->innerTrack()->hitPattern().trackerLayersWithMeasurement();
                           trackIso1     -= deltaRleplep<0.3 ? mu2->innerTrack()->pt() : 0; // footprint removal
                        }
                        if ( mu1->muonBestTrack().isNonnull() ){
                           relativeError1 = mu1->muonBestTrack()->ptError()/mu1->muonBestTrack()->pt();
                           dBCut1         = fabs(mu1->muonBestTrack()->dxy(vertex.position()));
                           longiCut1      = fabs(mu1->muonBestTrack()->dz( vertex.position()));
                        }
                        if ( mu2->muonBestTrack().isNonnull() ){
                           relativeError2 = mu2->muonBestTrack()->ptError()/mu2->muonBestTrack()->pt();
                           dBCut2         = fabs(mu2->muonBestTrack()->dxy(vertex.position()));
                           longiCut2      = fabs(mu2->muonBestTrack()->dz( vertex.position()));
                        }
                        // relative mini-isolation
                        miniIso1         = mu1->userFloat("miniIso");
                        miniIso2         = mu2->userFloat("miniIso");
                   }
                   //*****************************************************************//
                   //************************* ID for electrons **********************//
                   //*****************************************************************//
                   else if ( leptonicV.daughter(0)->isElectron() && 
                             leptonicV.daughter(1)->isElectron()    ) {
                        int temp = leptonicV.daughter(0)->pt() > leptonicV.daughter(1)->pt() ? 0 : 1; 
                        const pat::Electron *el1 = (pat::Electron*)leptonicV.daughter(      temp);
                        const pat::Electron *el2 = (pat::Electron*)leptonicV.daughter((int)!temp);
                        const Ptr<pat::Electron> el1Ptr(electrons, el1->userInt("slimmedIndex") );
                        const Ptr<pat::Electron> el2Ptr(electrons, el2->userInt("slimmedIndex") );
                        iEvent.getByToken(deltaRElHltToken,   deltaR_handle);
                        iEvent.getByToken(deltaPtElHltToken,  deltaPt_handle);
                        iEvent.getByToken(matchElHltToken, matchHlt_handle);
                        deltaRlep1Obj  =      (*deltaR_handle)[el1Ptr];
                        deltaRlep2Obj  =      (*deltaR_handle)[el2Ptr];
                        deltaPtlep1Obj =      (*deltaPt_handle)[el1Ptr];
                        deltaPtlep2Obj =      (*deltaPt_handle)[el2Ptr];
                        matchHlt1      = (int)(*matchHlt_handle)[el1Ptr]; 
                        matchHlt2      = (int)(*matchHlt_handle)[el2Ptr]; 
                        eeDeltaR       = reco::deltaR(el1->p4(),el2->p4());
                        ptel1          = el1->pt();
                        ptel2          = el2->pt();
                        etel1          = el1->superCluster()->energy();
                        etel2          = el2->superCluster()->energy();
                        etaSC1         = el1->superCluster()->eta();
                        etaSC2         = el2->superCluster()->eta();
                        barrel1        = fabs(etaSC1)<1.479 ? 1:0;
                        barrel2        = fabs(etaSC2)<1.479 ? 1:0;
                        endcap1        = fabs(etaSC1)>1.479 ? 1:0;
                        endcap2        = fabs(etaSC2)>1.479 ? 1:0;
                        // isolation 
                        pfIso03R1      = el1->userFloat("pfIso03R");
                        pfIso03R2      = el2->userFloat("pfIso03R");
                        caloIso1       = el1->dr03EcalRecHitSumEt() + el1->dr03HcalDepth1TowerSumEt();
                        caloIso2       = el2->dr03EcalRecHitSumEt() + el2->dr03HcalDepth1TowerSumEt();
                        trackIso1      = el1->dr03TkSumPt();
                        trackIso2      = el2->dr03TkSumPt();
                        // particle flow electrons
                        isPF1          = el1->isPF();
                        isPF2          = el2->isPF();
                        // retrieve mini isolation
                        miniIso1       = el1->userFloat("miniIso");
                        miniIso2       = el2->userFloat("miniIso");
                        // heepV60
                        HEEP1          = el1->userInt("HEEP"); 
                        HEEP2          = el2->userInt("HEEP"); 
                        heep1          = el1->userInt("heep"); 
                        heep2          = el2->userInt("heep"); 
                        // loose 
                        LOOSE1         = el1->userInt("LOOSE"); 
                        LOOSE2         = el2->userInt("LOOSE"); 
                        loose1         = el1->userInt("loose"); 
                        loose2         = el2->userInt("loose"); 
                        // shower shapes
                        sigmaIEtaIEta1 = el1->full5x5_sigmaIetaIeta();
                        sigmaIEtaIEta2 = el2->full5x5_sigmaIetaIeta();
                        double e5x5_1  = el1->full5x5_e5x5(); 
                        double e5x5_2  = el2->full5x5_e5x5(); 
                        e1x5overE5x5_1 = e5x5_1!=0 ? el1->full5x5_e1x5()/e5x5_1    : 0; 
                        e1x5overE5x5_2 = e5x5_2!=0 ? el2->full5x5_e1x5()/e5x5_2    : 0; 
                        e2x5overE5x5_1 = e5x5_1!=0 ? el1->full5x5_e2x5Max()/e5x5_1 : 0; 
                        e2x5overE5x5_2 = e5x5_2!=0 ? el2->full5x5_e2x5Max()/e5x5_2 : 0; 
                        // more electron ID variables
                        dEtaIn1        = el1->deltaEtaSuperClusterTrackAtVtx();
                        dEtaIn2        = el2->deltaEtaSuperClusterTrackAtVtx();
                        dPhiIn1        = el1->deltaPhiSuperClusterTrackAtVtx();
                        dPhiIn2        = el2->deltaPhiSuperClusterTrackAtVtx();
                        dEtaSeed1      = el1->deltaEtaSeedClusterTrackAtVtx();
                        dEtaSeed2      = el2->deltaEtaSeedClusterTrackAtVtx();
                        hOverE1        = el1->hadronicOverEm();
                        hOverE2        = el2->hadronicOverEm();
                        ooEmooP1       = el1->ecalEnergy() && std::isfinite(el1->ecalEnergy()) ? 
                                         fabs(1.0/el1->ecalEnergy() - el1->eSuperClusterOverP()/el1->ecalEnergy() ) : 1e9;
                        ooEmooP2       = el2->ecalEnergy() && std::isfinite(el2->ecalEnergy()) ? 
                                         fabs(1.0/el2->ecalEnergy() - el2->eSuperClusterOverP()/el2->ecalEnergy() ) : 1e9;
                        ecalDriven1    = el1->ecalDriven();
                        ecalDriven2    = el2->ecalDriven();
                        passConVeto1   = el1->passConversionVeto();
                        passConVeto2   = el2->passConversionVeto();
                        if (el1->gsfTrack().isNonnull() && 
                            el2->gsfTrack().isNonnull()    ){
                            d01          = (-1)*el1->gsfTrack()->dxy(vertex.position());   
                            d02          = (-1)*el2->gsfTrack()->dxy(vertex.position());  
                            dz1          = el1->gsfTrack()->dz(vertex.position());
                            dz2          = el2->gsfTrack()->dz(vertex.position());
                            missingHits1 = el1->gsfTrack()->hitPattern().numberOfHits(reco::HitPattern::MISSING_INNER_HITS);
                            missingHits2 = el2->gsfTrack()->hitPattern().numberOfHits(reco::HitPattern::MISSING_INNER_HITS);
                        }
                   }
                   break;}
               case VW_CHANNEL:{
                   const reco::Candidate& leptonicV = (*graviton.daughter("leptonicV"));
                   //*****************DEFINITIONS *************************************
                   //candidate
                   candMass  = graviton.mass();
                   //leptons
                   ptVlep = leptonicV.pt();
                   yVlep  = leptonicV.eta();
                   phiVlep = leptonicV.phi();
                   massVlep = leptonicV.mass();
                   mtVlep  = leptonicV.mt();
                   ptlep1 = leptonicV.daughter(0)->pt();
                   etalep1 = leptonicV.daughter(0)->eta();
                   philep1 = leptonicV.daughter(0)->phi();
                   lep = abs(leptonicV.daughter(0)->pdgId());
                   //met
                   met = metCand.pt();
                   metPhi = metCand.phi();  
                   //hadrons
                   ptVhad = hadronicV.pt();
                   yVhad  = hadronicV.eta();
                   phiVhad = hadronicV.phi();
                   tau1 = hadronicV.userFloat("NjettinessAK8:tau1");
                   tau2 = hadronicV.userFloat("NjettinessAK8:tau2");
                   tau3 = hadronicV.userFloat("NjettinessAK8:tau3");
                   tau21 = tau2/tau1;
                   etjet1 = hadronicV.et();
                   ptjet1 = hadronicV.pt();
                   etajet1 = hadronicV.eta();
                   phijet1 = hadronicV.phi();
                   massjet1 = hadronicV.mass();
                   //deltas
                   deltaRleplep = deltaR(etalep1,philep1,etalep2,philep2);
                   double drl1j = deltaR(etalep1,philep1,etajet1,phijet1);
                   double drl2j = deltaR(etalep2,philep2,etajet1,phijet1);
                   deltaRlepjet = std::min(drl1j,drl2j);
                   delPhilepmet = deltaPhi(philep1, metPhi);
                   delPhijetmet = deltaPhi(phijet1, metPhi);
                   break;}
               case VZnu_CHANNEL:{
                   const pat::MET& goodMET =dynamic_cast<const pat::MET&> (*graviton.daughter("goodMET"));
                   //*************** DEFINITIONS ***************************************** 
                   //hadrons
                   ptVhad = hadronicV.pt();
                   yVhad  = hadronicV.eta();
                   phiVhad = hadronicV.phi();
                   tau1 = hadronicV.userFloat("NjettinessAK8:tau1");
                   tau2 = hadronicV.userFloat("NjettinessAK8:tau2");
                   tau3 = hadronicV.userFloat("NjettinessAK8:tau3");
                   tau21 = tau2/tau1;
                   ptjet1 = hadronicV.pt();
                   etajet1 = hadronicV.eta();
                   phijet1 = hadronicV.phi();
                   massjet1 = hadronicV.mass();                       
                   // MET FROM GRAVITON
                   metpt = goodMET.pt();
                   metphi = goodMET.phi();
                   // delta Phi between jet and met(from graviton) 
                   deltaphijetmet = deltaPhi(phijet1, metphi);
                   // transverse candidate mass for JET + MET
                   candTMass    = sqrt(abs(2*ptjet1*metpt*(1-cos(deltaphijetmet))));                     
                   break;}
               case VH_CHANNEL: // This channel needs to be implemented 
                   break;

           }// close switch


       }// close not isGen
       
       if(isGen_) {
	   massVhad = hadronicV.userFloat("ak8GenJetsSoftDropMass");
	   massVhadSD = massVhad;
	   nVtx = 0;
       }

     }// end if n_cands>0
   }// end passed trigger && passed analysis

   /// For data, all weights are equal to 1.
   recoWeight    = 1.0;
   triggerWeight = 1.0;
   pileupWeight  = 1.0;
   lumiWeight    = 1.0;
   leptonWeight  = 1.0;
   ewkWeight     = 1.0;
   genWeight     = 1.0;
   if( !isData_ ) {
     // pileup reweight
     Handle<std::vector< PileupSummaryInfo > >  puInfo;
     iEvent.getByToken(puInfoToken, puInfo);
     std::vector<PileupSummaryInfo>::const_iterator PVI;
     for(PVI = puInfo->begin(); PVI != puInfo->end(); ++PVI) {
       int BX = PVI->getBunchCrossing();
       if( BX == 0 ){
	 int  bin     = h1->FindBin(PVI->getTrueNumInteractions());
	 pileupWeight = h1->GetBinContent(bin);
	 continue;
       }
     }
     // generator weight
     edm::Handle<GenEventInfoProduct>   genEvtInfo; 
     iEvent.getByToken(genEvtInfoToken, genEvtInfo );
     genWeight = genEvtInfo->weight()/fabs(genEvtInfo->weight());
     // lumi weight
     double targetEvents = targetLumiInvPb_*crossSectionPb_;
     lumiWeight = targetEvents/originalNEvents_;
     // EGamma Scale Factor
     if ( lep==11 ){
         int bin1 = ptlep1<200. ? h2->FindBin(fabs(etaSC1),ptlep1) : h2->FindBin(fabs(etaSC1),199.);
         int bin2 = ptlep2<200. ? h2->FindBin(fabs(etaSC2),ptlep2) : h2->FindBin(fabs(etaSC2),199.);
         leptonWeight = h2->GetBinContent(bin1) * h2->GetBinContent(bin2);
     }
     // Muon Scale Factor
     if ( lep==13 ){
         int bin1 = ptlep1<300. ? h3->FindBin(fabs(etalep1),ptlep1) : h3->FindBin(fabs(etalep1),299.);
         int bin2 = ptlep2<120. ? h4->FindBin(fabs(etalep2),ptlep2) : h4->FindBin(fabs(etalep2),119.);
         int bin3 = ptlep1<300. ? h5->FindBin(fabs(etalep1),ptlep1) : h5->FindBin(fabs(etalep1),299.);
         int bin4 = ptlep2<120. ? h6->FindBin(fabs(etalep2),ptlep2) : h6->FindBin(fabs(etalep2),119.);
         leptonWeight = h3->GetBinContent(bin1) * h4->GetBinContent(bin2) * //  ID SF
                        h5->GetBinContent(bin3) * h6->GetBinContent(bin4) ; // Iso SF
     }
     // Trigger Scale Factor
     if ( lep==11 ){
         int bin = ptlep1<1000. ? h7->FindBin(etaSC1,ptlep1) : h7->FindBin(etaSC1,999.);
         triggerWeight = h7->GetBinContent(bin) ;
     }
     if ( lep==13 ){
         if ( fabs(etalep1)<2.1 ){
            int bin = ptlep1<120. ? h8->FindBin(fabs(etalep1),ptlep1) : h8->FindBin(fabs(etalep1),119.);
            triggerWeight = h8->GetBinContent(bin) ;
         }
         else {
            int bin = ptlep2<120. ? h8->FindBin(fabs(etalep2),ptlep2) : h8->FindBin(fabs(etalep2),119.);
            triggerWeight = h8->GetBinContent(bin) ;
         }
     }
     // Reco scale factor
     if ( lep==11 ){
         int bin1 = ptlep1<200. ? h9->FindBin(etaSC1,ptlep1) : h9->FindBin(etaSC1,199.);
         int bin2 = ptlep2<200. ? h9->FindBin(etaSC2,ptlep2) : h9->FindBin(etaSC2,199.);
         recoWeight = h9->GetBinContent(bin1) * h9->GetBinContent(bin2);
     }
     // Electroweak correction
     //if ( genptZl>150. )
     //    ewkWeight = genptZl<2680. ? g1->Eval(genptZl) : g1->Eval(2680.);
   }
   totalWeight = recoWeight*triggerWeight*pileupWeight*genWeight*lumiWeight*leptonWeight;
   
   // Enumarate regions
   enum {
     excluded = -1,
     lowerSB,
     lowerSIG,
     upperSIG,
     upperSB,
   }; 
   
   if( massVhad < 20. )
     reg = excluded;
   if( massVhad > 20.  and  massVhad < 65.  )
     reg = lowerSB;
   if( massVhad > 65.  and  massVhad < 105. )
     reg = lowerSIG;
   if( massVhad > 105. and  massVhad < 135. )
     reg = upperSIG;
   if( massVhad > 135. )
     reg = upperSB;
   
   if(passed_analysis)
     outTree_->Fill();
   // fill dummy values, weights and regions even if no candidate is found if analysis is "defiltered"
   // region should be "excluded" in that case
   // otherwise proceed as usual
}


void EDBRTreeMaker::setDummyValues() {
     nVtx             = -1e4;
     recoWeight       = -1e4;
     triggerWeight    = -1e4;
     pileupWeight     = -1e4;
     lumiWeight       = -1e4;
     leptonWeight     = -1e4;
     ewkWeight        = -1e4;
     totalWeight      = -1e4;
     candMass         = -1e4;
     ptVlep           = -1e4;
     ptVhad           = -1e4;
     ptCorUp          = -1e4;
     ptCorDown        = -1e4;
     yVlep            = -1e4;
     yVhad            = -1e4;
     phiVlep          = -1e4;
     phiVhad          = -1e4;
     massVlep         = -1e4;
     massVhad         = -1e4;
     massVhadSD       = -1e4;
     mtVlep           = -1e4;
     tau1             = -1e4;
     tau2             = -1e4;
     tau3             = -1e4;
     tau21            = -1e4;
     ptlep1           = -1e4;
     ptlep2           = -1e4;
     etalep1          = -1e4;
     etalep2          = -1e4;
     philep1          = -1e4;
     philep2          = -1e4;
     charge1          = -1e4;
     charge2          = -1e4;
     pdgId1           = -1e4;
     pdgId2           = -1e4;
     miniIso1         = -1e4;
     miniIso2         = -1e4;
     nsubjets         = -1e4; 
     numjets          = -1e4; 
     etjet1           = -1e4;
     ptjet1           = -1e4;
     etajet1          = -1e4;
     phijet1          = -1e4;
     massjet1         = -1e4;
     softjet1         = -1e4;
     prunedjet1       = -1e4;
     rhojet1          = -1e4;
     nhfjet1          = -1e4;
     chfjet1          = -1e4;
     nemfjet1         = -1e4;
     cemfjet1         = -1e4;
     nmultjet1        = -1e4;
     cmultjet1        = -1e4;
     met              = -1e4;
     metPhi           = -1e4;
     metpt            = -1e4;
     metphi           = -1e4;
     matchHlt1        = -1e4;
     matchHlt2        = -1e4;
     deltaRlep1Obj    = -1e4;
     deltaRlep2Obj    = -1e4;
     deltaPtlep1Obj   = -1e4;
     deltaPtlep2Obj   = -1e4;
     deltaRleplep     = -1e4;
     deltaRlepjet     = -1e4;
     delPhilepmet     = -1e4;
     delPhijetmet     = -1e4;
     deltaphijetmet   = -1e4; 
     lep              = -1e4;
     reg              = -1e4;
     rho              = -1e4;
     barrel1          = -1e4;
     barrel2          = -1e4;
     endcap1          = -1e4;
     endcap2          = -1e4;
     eeDeltaR         = -1e4;
     etel1            = -1e4;
     ptel1            = -1e4;
     etaSC1           = -1e4;
     dEtaIn1          = -1e4;
     dPhiIn1          = -1e4;
     hOverE1          = -1e4;
     sigmaIEtaIEta1   = -1e4;
     e1x5overE5x5_1   = -1e4;
     e2x5overE5x5_1   = -1e4;
     ooEmooP1         = -1e4;
     d01              = -1e4;
     dz1              = -1e4;
     caloIso1         = -1e4;
     trackIso1        = -1e4;
     ecalDriven1      = -1e4;
     missingHits1     = -1e4; 
     passConVeto1     = -1e4;
     HEEP1            = -1e4;
     heep1            = -1e4;
     LOOSE1           = -1e4;
     loose1           = -1e4;
     etel2            = -1e4;
     ptel2            = -1e4;
     etaSC2           = -1e4;
     dEtaIn2          = -1e4;
     dPhiIn2          = -1e4;
     hOverE2          = -1e4;
     sigmaIEtaIEta2   = -1e4;
     e1x5overE5x5_2   = -1e4;
     e2x5overE5x5_2   = -1e4;
     ooEmooP2         = -1e4;
     d02              = -1e4;
     dz2              = -1e4;
     caloIso2         = -1e4;
     trackIso2        = -1e4;
     ecalDriven2      = -1e4;
     missingHits2     = -1e4; 
     passConVeto2     = -1e4;
     HEEP2            = -1e4; 
     heep2            = -1e4; 
     LOOSE2           = -1e4; 
     loose2           = -1e4; 
     looseMu1         = -1e4;
     looseMu2         = -1e4;
     mediumMu1        = -1e4;
     mediumMu2        = -1e4;
     tightMu1         = -1e4;
     tightMu2         = -1e4;
     trackerMu1       = -1e4;
     trackerMu2       = -1e4;
     highPtMu1        = -1e4;
     highPtMu2        = -1e4;
     isPF1            = -1e4;
     isPF2            = -1e4;
     isGlobalMu1      = -1e4;
     isGlobalMu2      = -1e4;
     isTrackerMu1     = -1e4;
     isTrackerMu2     = -1e4;
     matchedStations1 = -1e4;
     matchedStations2 = -1e4;
     pixelHits1       = -1e4;
     pixelHits2       = -1e4;
     trackerLayers1   = -1e4;
     trackerLayers2   = -1e4;
     relativeError1   = -1e4;
     relativeError2   = -1e4;
     dBCut1           = -1e4;
     dBCut2           = -1e4;
     longiCut1        = -1e4;
     longiCut2        = -1e4;
     pfIso03R1        = -1e4;
     pfIso03R2        = -1e4;
     pfIso04R1        = -1e4;
     pfIso04R2        = -1e4;
     pTtuneP1         = -1e4;
     pTtuneP2         = -1e4;

     genptZl          = -1e4;
     genptZh          = -1e4;
     genetaZl         = -1e4;
     genetaZh         = -1e4;
     genphiZl         = -1e4;
     genphzZh         = -1e4;
     genmassZl        = -1e4;
     genmassZh        = -1e4;
     genptl1          = -1e4;
     genptl2          = -1e4;
     genetal1         = -1e4;
     genetal2         = -1e4;
     genphil1         = -1e4;
     genphil2         = -1e4;
     genmassl1        = -1e4;
     genmassl2        = -1e4;
     genptq1          = -1e4;
     genptq2          = -1e4;
     genetaq1         = -1e4;
     genetaq2         = -1e4;
     genphiq1         = -1e4;
     genphiq2         = -1e4;
     genmassq1        = -1e4;
     genmassq2        = -1e4;
     genptG           = -1e4;
     genetaG          = -1e4;
     genphiG          = -1e4;
     genmassG         = -1e4;
     
     trigger          =0;
     passVlep         =0;
     passVhad         =0;
}

void EDBRTreeMaker::beginJob(){ 
     if ( !isData_ ){
        f1 = new TFile(   puWeights_.fullPath().c_str() );
        f2 = new TFile(   egammaSFs_.fullPath().c_str() );
        f3 = new TFile(     muonSFs_.fullPath().c_str() );
        //f4 = new TFile(  ewkCorrect_.fullPath().c_str() );
        f5 = new TFile(eltriggerSFs_.fullPath().c_str() );
        f6 = new TFile(mutriggerSFs_.fullPath().c_str() );
        f7 = new TFile(   elrecoSFs_.fullPath().c_str() );
        h1 = (TH1D*)f1->Get("pileupWeights");
        h2 = (TH2F*)f2->Get("EGamma_SF2D");
        h3 = (TH2F*)f3->Get("HighPtID_PtEtaBins_Pt53/abseta_pTtuneP_ratio");
        h4 = (TH2F*)f3->Get("HighPtID_PtEtaBins_Pt20/abseta_pTtuneP_ratio");
        h5 = (TH2F*)f3->Get("tkRelIsoID_PtEtaBins_Pt53/abseta_pTtuneP_ratio");
        h6 = (TH2F*)f3->Get("tkRelIsoID_PtEtaBins_Pt20/abseta_pTtuneP_ratio");
        h7 = (TH2F*)f5->Get("HLT_Ele105_PtEtaBins/eta_pt_sf");
        h8 = (TH2F*)f6->Get("runD_Mu45_eta2p1_PtEtaBins/abseta_pt_ratio");
        h9 = (TH2F*)f7->Get("EGamma_SF2D");
        //g1 = (TF1*) f4->Get("ewkZcorrection"); 
     }
}

void EDBRTreeMaker::endJob(){ }

//define this as a plug-in
DEFINE_FWK_MODULE(EDBRTreeMaker);
