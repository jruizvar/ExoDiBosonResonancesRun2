import FWCore.ParameterSet.Config as cms

process = cms.Process( "TEST" )
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = '76X_mcRun2_asymptotic_RunIIFall15DR76_v1'

import sys
SAMPLE = str(sys.argv[2])

process.load("ExoDiBosonResonances.EDBRCommon.goodJets_cff")
process.load("ExoDiBosonResonances.EDBRCommon.hltFilter_cff")
process.load("ExoDiBosonResonances.EDBRCommon.leptonicZ_cff")
process.load("ExoDiBosonResonances.EDBRCommon.hadronicZ_cff")
process.load("ExoDiBosonResonances.EDBRGenStudies.selectLeptonicDecay")
process.load("ExoDiBosonResonances.EDBRGenStudies.selectHadronicDecay")
process.load("ExoDiBosonResonances.EDBRCommon.simulation.Fall15MiniAOD76X."+SAMPLE)
process.load("ExoDiBosonResonances.EDBRLeptons.goodLeptonsProducer_cff")

process.maxEvents.input = -1 

configXsecs = {  "BulkGravToZZToZlepZhad_M-600"         : 1.0,
                 "BulkGravToZZToZlepZhad_M-800"         : 1.0,
                 "BulkGravToZZToZlepZhad_M-1000"        : 1.0,
                 "BulkGravToZZToZlepZhad_M-1200"        : 1.0,
                 "BulkGravToZZToZlepZhad_M-1400"        : 1.0,
                 "BulkGravToZZToZlepZhad_M-1600"        : 1.0,
                 "BulkGravToZZToZlepZhad_M-1800"        : 1.0,
                 "BulkGravToZZToZlepZhad_M-2000"        : 1.0,
                 "BulkGravToZZToZlepZhad_M-2500"        : 1.0,
                 "BulkGravToZZToZlepZhad_M-3000"        : 1.0,
                 "BulkGravToZZToZlepZhad_M-3500"        : 1.0,
                 "BulkGravToZZToZlepZhad_M-4000"        : 1.0,
                 "BulkGravToZZToZlepZhad_M-4500"        : 1.0,
              }

configNevents = {"BulkGravToZZToZlepZhad_M-600"         : 50000,
                 "BulkGravToZZToZlepZhad_M-800"         : 50000,
                 "BulkGravToZZToZlepZhad_M-1000"        : 50000,
                 "BulkGravToZZToZlepZhad_M-1200"        : 50000,
                 "BulkGravToZZToZlepZhad_M-1400"        : 49200,
                 "BulkGravToZZToZlepZhad_M-1600"        : 50000,
                 "BulkGravToZZToZlepZhad_M-1800"        : 50000,
                 "BulkGravToZZToZlepZhad_M-2000"        : 48400,
                 "BulkGravToZZToZlepZhad_M-2500"        : 50000,
                 "BulkGravToZZToZlepZhad_M-3000"        : 50000,
                 "BulkGravToZZToZlepZhad_M-3500"        : 50000,
                 "BulkGravToZZToZlepZhad_M-4000"        : 50000,
                 "BulkGravToZZToZlepZhad_M-4500"        : 50000,
                }

usedXsec = configXsecs[SAMPLE]
usedNevents = configNevents[SAMPLE]

TRIGGER = str(sys.argv[3])
triggerPath = {
                "el" : "HLT_Ele105_CaloIdVT_GsfTrkIdT_v*",
                "mu" : "HLT_Mu45_eta2p1_v*",
              }
usedHLT       = triggerPath[TRIGGER]

process.hltFilter.triggerConditions =  ( usedHLT, )

process.hadronicDecay.cut     = cms.string("22<abs(pdgId())<26 & 0<abs(daughter(0).pdgId())<6") 
process.hadronicDecay.filter  = cms.bool(False)

if TRIGGER == "el" :
    process.leptonicDecay.cut     = cms.string("abs(pdgId())==23 & (abs(daughter(0).pdgId())==11 & abs(daughter(1).pdgId())==11)") 
    process.leptonicDecay.filter  = cms.bool(False)
    process.kinElectrons.filter   = cms.bool(True)
    process.idElectrons.filter    = cms.bool(True)
    process.leptonicVFilter.src   = "Ztoee"
    process.ZdaughterCharge.src   = "Ztoee"

if TRIGGER == "mu" :
    process.leptonicDecay.cut     = cms.string("abs(pdgId())==23 & (abs(daughter(0).pdgId())==13 & abs(daughter(1).pdgId())==13)") 
    process.leptonicDecay.filter  = cms.bool(False)
    process.kinMuons.filter       = cms.bool(True)
    process.idMuons.filter        = cms.bool(True)
    process.leptonicVFilter.src   = "Ztomumu"
    process.ZdaughterCharge.src   = "Ztomumu"
    process.leptonicVSelector.src = "ZdaughterIso"
    process.leptonicVSequence.replace( process.ZdaughterCharge, 
                                       process.ZdaughterCharge + process.ZdaughterIso )

from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
switchOnVIDElectronIdProducer(process, DataFormat.MiniAOD)
my_id_modules = [
                  'RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV60_cff',
                  'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Spring15_25ns_V1_cff'
                ]
for idmod in my_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

#Change vertex collection in Dxy cut
process.egmGsfElectronIDs.physicsObjectIDs[0].idDefinition.cutFlow[9].vertexSrcMiniAOD = "goodOfflinePrimaryVertex"
process.egmGsfElectronIDs.physicsObjectIDs[1].idDefinition.cutFlow[6].vertexSrcMiniAOD = "goodOfflinePrimaryVertex"
process.egmGsfElectronIDs.physicsObjectIDs[1].idDefinition.cutFlow[7].vertexSrcMiniAOD = "goodOfflinePrimaryVertex"

process.bestLeptonicV = cms.EDFilter(    "LargestPtCandSelector",
                                          src = cms.InputTag("leptonicVSelector"),
                                          maxNumber = cms.uint32(1) )

process.bestHadronicV = cms.EDFilter(    "LargestPtCandSelector",
                                          src = cms.InputTag("hadronicV"),
                                          maxNumber = cms.uint32(1) )

process.graviton = cms.EDProducer(       "CandViewCombiner",
                                          decay = cms.string("bestLeptonicV bestHadronicV"),
                                          checkCharge = cms.bool(False),
                                          cut = cms.string("mass>600."),
                                          roles = cms.vstring('leptonicV', 'hadronicV') )

process.gravitonFilter =  cms.EDFilter(  "CandViewCountFilter",
                                          src = cms.InputTag("graviton"),
                                          minNumber = cms.uint32(1),
                                          filter = cms.bool(True) )

process.treeDumper = cms.EDAnalyzer(     "EDBRTreeMaker",
                                          isGen           = cms.bool      (  False                     ),
                                          isData          = cms.bool      (  False                     ),
                                          originalNEvents = cms.int32     (  usedNevents               ),
                                          crossSectionPb  = cms.double    (  usedXsec                  ),
                                          targetLumiInvPb = cms.double    (  2690.55                   ),
                                          EDBRChannel     = cms.string    ( "VZ_CHANNEL"               ),
                                          puWeights       = cms.FileInPath( "ExoDiBosonResonances/EDBRTreeMaker/data/pileupWeights69mb.root"),
                                          egammaSFs       = cms.FileInPath( "ExoDiBosonResonances/EDBRTreeMaker/data/CutBasedID_LooseWP_76X_18Feb.txt_SF2D.root"),
                                          muonSFs         = cms.FileInPath( "ExoDiBosonResonances/EDBRTreeMaker/data/MuonID_Z_RunCD_Reco76X_Feb15.root"),
                                          muIsoSFs        = cms.FileInPath( "ExoDiBosonResonances/EDBRTreeMaker/data/MuonIso_Z_RunCD_Reco76X_Feb15.root"),
                                          elrecoSFs       = cms.FileInPath( "ExoDiBosonResonances/EDBRTreeMaker/data/eleRECO_SF2D.root"),
                                          eltriggerSFs    = cms.FileInPath( "ExoDiBosonResonances/EDBRTreeMaker/data/HLT_Ele105_scalefactors76X.root"),
                                          mutriggerSFs    = cms.FileInPath( "ExoDiBosonResonances/EDBRTreeMaker/data/SingleMuonTrigger_Z_RunCD_Reco76X_Feb15.root"),
                                          ewkCorrect      = cms.FileInPath( "ExoDiBosonResonances/EDBRTreeMaker/data/ElectroweakCorrections.root"),
                                          vertex          = cms.InputTag  ( "goodOfflinePrimaryVertex" ))

process.analysis = cms.Path(              process.leptonicDecay            + 
                                          process.hadronicDecay            + 
                                          process.hltSequence              +
                                          process.goodLeptonsProducer      +  
                                          process.leptonicVSequence        +
                                          process.bestLeptonicV            +
                                          process.fatJetsSequence          +
                                          process.hadronicVSequence        +
                                          process.bestHadronicV            +
                                          process.graviton                 +
                                          process.gravitonFilter           )

process.analysis.replace(                 process.goodOfflinePrimaryVertex,
                                          process.goodOfflinePrimaryVertex +
                                          process.egmGsfElectronIDs        )

process.load("ExoDiBosonResonances.EDBRCommon.trigReportData_cff")
process.endpath = cms.EndPath( process.treeDumper + process.trigReportData )

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("treeEDBR_"+SAMPLE+"_"+TRIGGER+".root")
                                  )

process.triggersel =  cms.Path( process.hltFilter )
