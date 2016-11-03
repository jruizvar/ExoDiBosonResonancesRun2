import FWCore.ParameterSet.Config as cms

import HLTrigger.HLTfilters.hltHighLevel_cfi as hlt

hltFilter = hlt.hltHighLevel.clone(
                                  HLTPaths = ['HLT_Ele105_CaloIdVT_GsfTrkIdT_v*'],
                                  throw = False )

hltMatchingElectrons = cms.EDProducer("PatElectronHLTmatching",
                                  path       = cms.vstring ("HLT_Ele105_CaloIdVT_GsfTrkIdT_v*" ), 
                                  hltToken   = cms.InputTag("TriggerResults","","HLT"          ),
                                  hltObjects = cms.InputTag("selectedPatTrigger"               ),
                                  leptons    = cms.InputTag("slimmedElectrons"                 ),
                                  maxDeltaR  = cms.double  ( 0.15                              ))

hltMatchingMuons = cms.EDProducer("PatMuonHLTmatching",
                                  path       = cms.vstring ("HLT_Mu45_eta2p1_v*"               ),
                                  hltToken   = cms.InputTag("TriggerResults","","HLT"          ),
                                  hltObjects = cms.InputTag("selectedPatTrigger"               ),
                                  leptons    = cms.InputTag("slimmedMuons"                     ),
                                  maxDeltaR  = cms.double  ( 0.15                              ))

hltSequence = cms.Sequence(       hltFilter            + 
                                  hltMatchingElectrons +
                                  hltMatchingMuons     )
