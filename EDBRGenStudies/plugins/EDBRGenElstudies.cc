// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/Candidate/interface/CompositeCandidate.h"
#include "DataFormats/Candidate/interface/CompositeCandidateFwd.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "TTree.h"

class EDBRGenElstudies : public edm::EDAnalyzer {
   public:
      explicit EDBRGenElstudies(const edm::ParameterSet&);
      ~EDBRGenElstudies();

   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      edm::EDGetTokenT<reco::CandidateCollection>     genZToken;
      edm::EDGetTokenT<reco::VertexCollection>      vertexToken;
      edm::EDGetTokenT<reco::CompositeCandidateView> ZcandToken;

      TTree* t; 
      double pt1;
      double pt2;
      double eta1;
      double eta2;
      double Zpt;
      double Zmass;
      double genPt1;
      double genPt2;
      double genEta1;
      double genEta2;
      double genZpt;
      double genZmass;
      double dRGenGen;
      double dRGenRec1;
      double dRGenRec2;
      int    matchGen;
      int    nVtx;
      int    isPF1;
      int    isPF2;
      int    loose1;
      int    loose2;
      int    medium1;
      int    medium2;
      int    tight1;
      int    tight2;
      int    heep1;
      int    heep2;
      int    LOOSE1;
      int    LOOSE2;
      int    MEDIUM1;
      int    MEDIUM2;
      int    TIGHT1;
      int    TIGHT2;
      int    HEEP1;
      int    HEEP2;
      double caloIso1;
      double caloIso2;
      double trackIso1;
      double trackIso2;
      double pfIso03R1;
      double pfIso03R2;
      double miniIso1;
      double miniIso2;
};


EDBRGenElstudies::EDBRGenElstudies(const edm::ParameterSet& iConfig)
{
   vertexToken = consumes<reco::VertexCollection>(       edm::InputTag("offlineSlimmedPrimaryVertices") ),
   genZToken   = consumes<reco::CandidateCollection>(    edm::InputTag("leptonicDecay") );
   ZcandToken  = consumes<reco::CompositeCandidateView>( edm::InputTag("Ztoee"      ) );

   edm::Service<TFileService> fs;
   t = fs->make<TTree>("t","basic kinematic variables");
   t->Branch("pt1",        &pt1,        "pt1/D");
   t->Branch("pt2",        &pt2,        "pt2/D");
   t->Branch("eta1",       &eta1,       "eta1/D");
   t->Branch("eta2",       &eta2,       "eta2/D");
   t->Branch("Zpt",        &Zpt,        "Zpt/D");
   t->Branch("Zmass",      &Zmass,      "Zmass/D");
   t->Branch("genEta1",    &genEta1,    "genEta1/D");
   t->Branch("genEta2",    &genEta2,    "genEta2/D");
   t->Branch("genPt1",     &genPt1,     "genPt1/D");
   t->Branch("genPt2",     &genPt2,     "genPt2/D");
   t->Branch("genEta1",    &genEta1,    "genEta1/D");
   t->Branch("genEta2",    &genEta2,    "genEta2/D");
   t->Branch("genZpt",     &genZpt,     "genZpt/D");
   t->Branch("genZmass",   &genZmass,   "genZmass/D");
   t->Branch("dRGenGen",   &dRGenGen,   "dRGenGen/D");
   t->Branch("dRGenRec1",  &dRGenRec1,  "dRGenRec1/D");
   t->Branch("dRGenRec2",  &dRGenRec2,  "dRGenRec2/D");
   t->Branch("matchGen",   &matchGen,   "matchGen/I");
   t->Branch("nVtx",       &nVtx,       "nVtx/I");
   t->Branch("isPF1",      &isPF1,      "isPF1/I");
   t->Branch("isPF2",      &isPF2,      "isPF2/I");
   t->Branch("loose1",     &loose1,     "loose1/I");
   t->Branch("loose2",     &loose2,     "loose2/I");
   t->Branch("medium1",    &medium1,    "medium1/I");
   t->Branch("medium2",    &medium2,    "medium2/I");
   t->Branch("tight1",     &tight1,     "tight1/I");
   t->Branch("tight2",     &tight2,     "tight2/I");
   t->Branch("heep1",      &heep1,      "heep1/I");
   t->Branch("heep2",      &heep2,      "heep2/I");
   t->Branch("LOOSE1",     &LOOSE1,     "LOOSE1/I");
   t->Branch("LOOSE2",     &LOOSE2,     "LOOSE2/I");
   t->Branch("MEDIUM1",    &MEDIUM1,    "MEDIUM1/I");
   t->Branch("MEDIUM2",    &MEDIUM2,    "MEDIUM2/I");
   t->Branch("TIGHT1",     &TIGHT1,     "TIGHT1/I");
   t->Branch("TIGHT2",     &TIGHT2,     "TIGHT2/I");
   t->Branch("HEEP1",      &HEEP1,      "HEEP1/I");
   t->Branch("HEEP2",      &HEEP2,      "HEEP2/I");
   t->Branch("caloIso1",   &caloIso1,   "caloIso1/D");
   t->Branch("caloIso2",   &caloIso2,   "caloIso2/D");
   t->Branch("trackIso1",  &trackIso1,  "trackIso1/D");
   t->Branch("trackIso2",  &trackIso2,  "trackIso2/D");
   t->Branch("pfIso03R1",  &pfIso03R1,  "pfIso03R1/D");
   t->Branch("pfIso03R2",  &pfIso03R2,  "pfIso03R2/D");
   t->Branch("miniIso1",   &miniIso1,   "miniIso1/D");
   t->Branch("miniIso2",   &miniIso2,   "miniIso2/D");
}

EDBRGenElstudies::~EDBRGenElstudies(){ }

void
EDBRGenElstudies::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   Handle<reco::VertexCollection> vertices;
   iEvent.getByToken(vertexToken, vertices);
   nVtx = vertices->size();

   //****************************************************************//
   //                       GEN Z candidate                          //
   //****************************************************************//                                             
   Handle<reco::CandidateCollection> genZ;
   iEvent.getByToken(genZToken, genZ);
   const reco::Candidate& G    = (*genZ)[0];
   const reco::Candidate *gen1 = (reco::Candidate*)G.daughter(0);
   const reco::Candidate *gen2 = (reco::Candidate*)G.daughter(1);
   math::XYZTLorentzVector v1  = gen1->pt() > gen2->pt() ? gen1->p4() : gen2->p4();
   math::XYZTLorentzVector v2  = gen1->pt() < gen2->pt() ? gen1->p4() : gen2->p4();
   bool acceptance = v1.pt() > 35 and fabs(v1.eta()) < 2.5 and
                     v2.pt() > 35 and fabs(v2.eta()) < 2.5;
   if( !acceptance ) return;
   genPt1   = v1.pt();
   genPt2   = v2.pt();
   genEta1  = v1.eta();
   genEta2  = v2.eta();
   genZpt   = G.pt();
   genZmass = G.mass();
   dRGenGen = reco::deltaR( v1, v2 );

   //****************************************************************//
   //                       Reco Z candidate                         //
   //****************************************************************//                                             
   Handle<reco::CompositeCandidateView> Zcands ;
   iEvent.getByToken(ZcandToken,        Zcands);
   const reco::Candidate& Z = (*Zcands)[0];
   int temp = Z.daughter(0)->pt() > Z.daughter(1)->pt() ? 0 : 1; 
   const pat::Electron *el1 = (pat::Electron*)Z.daughter(      temp);
   const pat::Electron *el2 = (pat::Electron*)Z.daughter((int)!temp);
   dRGenRec1   = reco::deltaR( v1, el1->p4() );
   dRGenRec2   = reco::deltaR( v2, el2->p4() );
   matchGen    = (int) dRGenRec1<0.05 and dRGenRec2<0.05;
   pt1         = el1->pt();
   pt2         = el2->pt();
   eta1        = el1->eta();
   eta2        = el2->eta();
   Zpt         = Z.pt();
   Zmass       = Z.mass();
   isPF1       = (int)el1->isPF();
   isPF2       = (int)el2->isPF();
   loose1      = el1->userInt("loose");
   loose2      = el2->userInt("loose");
   medium1     = el1->userInt("medium");
   medium2     = el2->userInt("medium");
   tight1      = el1->userInt("tight");
   tight2      = el2->userInt("tight");
   heep1       = el1->userInt("heep");
   heep2       = el2->userInt("heep");
   LOOSE1      = el1->userInt("LOOSE");
   LOOSE2      = el2->userInt("LOOSE");
   MEDIUM1     = el1->userInt("MEDIUM");
   MEDIUM2     = el2->userInt("MEDIUM");
   TIGHT1      = el1->userInt("TIGHT");
   TIGHT2      = el2->userInt("TIGHT");
   HEEP1       = el1->userInt("HEEP");
   HEEP2       = el2->userInt("HEEP");
   caloIso1    = el1->userFloat("caloIso");
   caloIso2    = el2->userFloat("caloIso");
   trackIso1   = el1->userFloat("trackIso");
   trackIso2   = el2->userFloat("trackIso");
   pfIso03R1   = el1->userFloat("pfIso03R");
   pfIso03R2   = el2->userFloat("pfIso03R");
   miniIso1    = el1->userFloat("miniIso");
   miniIso2    = el2->userFloat("miniIso");
   // fill tree
   t->Fill();
}

void EDBRGenElstudies::beginJob() { }

void EDBRGenElstudies::endJob() { }

DEFINE_FWK_MODULE(EDBRGenElstudies);
