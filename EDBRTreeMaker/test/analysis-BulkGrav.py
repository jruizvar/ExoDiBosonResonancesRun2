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
process.load("ExoDiBosonResonances.EDBRCommon.simulation.Fall15MiniAOD76X."+SAMPLE)
process.load("ExoDiBosonResonances.EDBRGenStudies.selectLeptonicDecay")
process.load("ExoDiBosonResonances.EDBRGenStudies.selectHadronicDecay")
process.load("ExoDiBosonResonances.EDBRLeptons.goodLeptonsProducer_cff")

process.maxEvents.input = -1 

configXsecs = {  "BulkGravToZZToZlepZhad_M-600"         : 7.3592E-05,
                 "BulkGravToZZToZlepZhad_M-800"         : 1.9648E-05,
                 "BulkGravToZZToZlepZhad_M-1000"        : 1.9648E-05,
                 "BulkGravToZZToZlepZhad_M-1200"        : 6.5205E-06,
                 "BulkGravToZZToZlepZhad_M-1400"        : 2.4833E-06,
                 "BulkGravToZZToZlepZhad_M-1600"        : 8.1645E-07,
                 "BulkGravToZZToZlepZhad_M-1800"        : 3.7583E-07,
                 "BulkGravToZZToZlepZhad_M-2000"        : 2.2636E-07,
                 "BulkGravToZZToZlepZhad_M-2500"        : 4.2349E-08,
                 "BulkGravToZZToZlepZhad_M-3000"        : 9.2671E-09,
                 "BulkGravToZZToZlepZhad_M-3500"        : 4.7064E-09,
                 "BulkGravToZZToZlepZhad_M-4000"        : 1.9530E-09,
                 "BulkGravToZZToZlepZhad_M-4500"        : 8.9900E-10,
              }

configNevents = {"BulkGravToZZToZlepZhad_M-600"         : 50000,
                 "BulkGravToZZToZlepZhad_M-800"         : 50000,
                 "BulkGravToZZToZlepZhad_M-1000"        : 50000,
                 "BulkGravToZZToZlepZhad_M-1200"        : 50000,
                 "BulkGravToZZToZlepZhad_M-1400"        : 50000,
                 "BulkGravToZZToZlepZhad_M-1600"        : 50000,
                 "BulkGravToZZToZlepZhad_M-1800"        : 50000,
                 "BulkGravToZZToZlepZhad_M-2000"        : 50000,
                 "BulkGravToZZToZlepZhad_M-2500"        : 50000,
                 "BulkGravToZZToZlepZhad_M-3000"        : 49200,
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
usedHLT = triggerPath[TRIGGER]

process.hltFilter.triggerConditions =  ( usedHLT, )

if TRIGGER == "el" :
    process.leptonicDecay.cut = cms.string("abs(pdgId())==23 "
                                           "& (abs(daughter(0).pdgId())==11 & abs(daughter(1).pdgId())==11) " 
                                           "& mother(0).pdgId()==39")
    process.kinElectrons.filter   = cms.bool(True)
    process.idElectrons.filter    = cms.bool(True)
    process.leptonicVFilter.src   = "Ztoee"
    process.ZdaughterCharge.src   = "Ztoee"

if TRIGGER == "mu" :
    process.leptonicDecay.cut = cms.string("abs(pdgId())==23 "
                                           "& (abs(daughter(0).pdgId())==13 & abs(daughter(1).pdgId())==13) " 
                                           "& mother(0).pdgId()==39")
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
                                          targetLumiInvPb = cms.double    (  2630.245                  ),
                                          EDBRChannel     = cms.string    ( "VZ_CHANNEL"               ),
                                          puWeights       = cms.FileInPath( "ExoDiBosonResonances/EDBRTreeMaker/data/pileupWeights69mb.root"),
                                          egammaSFs       = cms.FileInPath( "ExoDiBosonResonances/EDBRTreeMaker/data/CutBasedID_LooseWP_76X_18Feb.txt_SF2D.root"),
                                          vertex          = cms.InputTag  ( "goodOfflinePrimaryVertex" ))

process.triggersel =  cms.Path( process.hltFilter)

process.analysis = cms.Path(              process.leptonicDecay            + 
                                          process.hltSequence              +
                                          process.goodLeptonsProducer      +  
                                          process.leptonicVSequence        +
                                          process.bestLeptonicV            +
                                          process.hadronicDecay            +
                                          process.fatJetsSequence          +
                                          process.hadronicVSequence        +
                                          process.bestHadronicV            +
                                          process.graviton                 +
                                          process.gravitonFilter           )

process.analysis.replace(                 process.goodOfflinePrimaryVertex,
                                          process.goodOfflinePrimaryVertex +
                                          process.egmGsfElectronIDs        )

if len(sys.argv) > 4: 
    # switch of filtering for signal samples
    # process.leptonicDecay.filter=cms.bool(False) # keep this filter to sort by lepton type.
    # process.hadronicDecay.filter=cms.bool(False) # keep this filter to sort by lepton type.
    process.analysis.remove(process.hltFilter)
    process.kinMuons.filter=cms.bool(False)
    process.idMuons.filter=cms.bool(False)
    process.kinElectrons.filter=cms.bool(False)
    process.idElectrons.filter=cms.bool(False)    
    process.goodOfflinePrimaryVertex.filter=cms.bool(False)
    process.leptonicVFilter.minNumber=0
    process.leptonicVSelector.filter=cms.bool(False)
    process.ZdaughterCharge.filter=cms.bool(False)
    process.ZdaughterIso.filter=cms.bool(False)
    process.leptonicVSelector.filter=cms.bool(False)
    process.goodJets.filter=cms.bool(False)
    process.countCleanJets.minNumber=0
    process.nsubjettiness.filter=cms.bool(False)
    process.hadronicV.filter=cms.bool(False)
    process.gravitonFilter.minNumber=0

    process.treeDumper.isSignal=cms.bool(True)


process.load("ExoDiBosonResonances.EDBRGenStudies.trigReportAnalyzer_cff")
process.endpath = cms.EndPath( process.treeDumper  +  process.trigReportAnalyzer )

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("treeEDBR_"+SAMPLE+"_"+TRIGGER+".root")
                                  )
