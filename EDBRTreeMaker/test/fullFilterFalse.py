import FWCore.ParameterSet.Config as cms

process = cms.Process( "TEST" )
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
process.GlobalTag.globaltag = '74X_mcRun2_asymptotic_v2'

#*********************************** CHOOSE YOUR CHANNEL  *******************************************#

CHANNEL         = "VZ_CHANNEL" # VZnu_CHANNEL
VZ_semileptonic = True         # False
VZ_JetMET       = False        # True

#************************************ CHOOSE YOUR HLT     *******************************************#

import sys
TRIGGER = str(sys.argv[3])
triggerPath = {
                "el" : "HLT_Ele105_CaloIdVT_GsfTrkIdT_v*",
                "mu" : "HLT_Mu45_eta2p1_v*",
              }
usedHLT = triggerPath[TRIGGER]

process.load("ExoDiBosonResonances.EDBRCommon.hltFilter_cff")
process.hltFilter.triggerConditions =  ( usedHLT, )

#*********************************** THE SAMPLES ****************************************************#
# choose the sample                                                                     

SAMPLE = str(sys.argv[2])
process.load("ExoDiBosonResonances.EDBRCommon.simulation.Spring15MiniAODv2."+SAMPLE)
process.maxEvents.input = -1

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.MessageLogger.cerr.FwkReport.limit = 99999999

configXsecs = {  "BulkGravToZZToZlepZhad_M-600"         : 4.0151E-04,
                 "BulkGravToZZToZlepZhad_M-800"         : 7.3592E-05,
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
                 "BulkGravToZZToZlepZhad_M-1000"        : 48400,
                 "BulkGravToZZToZlepZhad_M-1200"        : 49200,
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

#*******************************************************************************************************#

### Hadronic and leptonic boson.
process.load("ExoDiBosonResonances.EDBRCommon.leptonicZ_cff")
process.load("ExoDiBosonResonances.EDBRCommon.hadronicZ_cff")

process.bestLeptonicV = cms.EDFilter(    "LargestPtCandSelector",
                                          src = cms.InputTag("leptonicVSelector"),
                                          maxNumber = cms.uint32(1) )

process.bestHadronicV = cms.EDFilter(    "LargestPtCandSelector",
                                          src = cms.InputTag("hadronicV"),
                                          maxNumber = cms.uint32(1) )

process.graviton = cms.EDProducer(        "CandViewCombiner",
                                          decay = cms.string("bestLeptonicV bestHadronicV"),
                                          checkCharge = cms.bool(False),
                                          cut = cms.string("mass > 400."),
                                          roles = cms.vstring('leptonicV', 'hadronicV') )

process.gravitonFilter =  cms.EDFilter(   "CandViewCountFilter",
                                          src = cms.InputTag("graviton"),
                                          minNumber = cms.uint32(1),
                                          filter = cms.bool(True) )

process.treeDumper = cms.EDAnalyzer(      "EDBRTreeMaker",
                                          isGen           = cms.bool      (  False                     ),
                                          isData          = cms.bool      (  False                     ),
                                          originalNEvents = cms.int32     (  usedNevents               ),
                                          crossSectionPb  = cms.double    (  usedXsec                  ),
                                          targetLumiInvPb = cms.double    (  1546.719                  ),
                                          EDBRChannel     = cms.string    (  CHANNEL                   ),
                                          gravitonSrc     = cms.string    ( "graviton"                 ),
                                          metSrc          = cms.string    ( "slimmedMETs"              ),
                                          puWeights       = cms.FileInPath( "ExoDiBosonResonances/EDBRTreeMaker/data/pileupWeights69mb.root"),
                                          vertex          = cms.InputTag  ( "goodOfflinePrimaryVertex" ))

#************************************** SELECT GEN OR RECO ******************************************# 

option = 'RECO' # 'GEN' 

### GEN level studies
if option == 'GEN':
    process.load("ExoDiBosonResonances.EDBRGenStudies.genMuons_cff")
    process.load("ExoDiBosonResonances.EDBRGenStudies.genElectrons_cff")
    process.load("ExoDiBosonResonances.EDBRGenStudies.genFatJets_cff")
    process.load("ExoDiBosonResonances.EDBRGenStudies.genMET_cff")
    process.treeDumper.metSrc = 'genMetTrue'
    process.treeDumper.isGen  = True
    process.hadronicV.cut = cms.string('pt > 200. '
                                       '& (userFloat("ak8GenJetsSoftDropMass") > 50.) '
                                       '& (userFloat("ak8GenJetsSoftDropMass") < 110.)')

### RECO level studies
if option == 'RECO':
    process.load("ExoDiBosonResonances.EDBRCommon.goodJets_cff")
    process.load("ExoDiBosonResonances.EDBRCommon.goodMET_cff")

#***************************************** SEQUENCES **********************************************# 

process.leptonSequence = cms.Sequence(    process.leptonicVSequence + 
                                          process.bestLeptonicV     )

process.jetSequence = cms.Sequence(       process.fatJetsSequence   +
                                          process.hadronicVSequence +
                                          process.bestHadronicV     )

process.gravitonSequence = cms.Sequence(  process.graviton          +
                                          process.gravitonFilter    )

process.analysis = cms.Path(              process.leptonSequence    +
                                          process.jetSequence       +
                                          process.gravitonSequence  +
                                          process.treeDumper        )

if option=='RECO':
    process.load("ExoDiBosonResonances.EDBRCommon.hltFilter_cff")
    process.load("ExoDiBosonResonances.EDBRLeptons.goodLeptonsProducer_cff")
    from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
    switchOnVIDElectronIdProducer(process, DataFormat.MiniAOD)
    my_id_modules = ['RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV60_cff']
    for idmod in my_id_modules:
        setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)
    process.analysis.replace(process.leptonSequence, 
                             process.hltSequence              +
                             process.egmGsfElectronIDs        + 
                             process.goodLeptonsProducer      +  
                             process.leptonSequence           ) 

#************************************ TRIGGER REPORT ANALYZER ***************************************#
#                                                                                                    #
# Only supported for VZ channel                                                                      #
process.load("ExoDiBosonResonances.EDBRGenStudies.selectLeptonicDecay")
process.load("ExoDiBosonResonances.EDBRGenStudies.selectHadronicDecay")
process.load("ExoDiBosonResonances.EDBRGenStudies.trigReportAnalyzer_cff")
process.analysis.replace(process.hltSequence,
                         process.leptonicDecay +
                         process.hadronicDecay +
                         process.hltSequence   )

process.endpath = cms.EndPath( process.trigReportAnalyzer )
#                                                                                                    #
#****************************************************************************************************#

#***************************************** FILTER MODE **********************************************#

filterMode = False       
if filterMode == False:
    process.analysis.replace(process.hltFilter,
                             cms.ignore(process.hltFilter))
    #process.hltFilter.triggerConditions = ('*',)
    process.goodLeptons.filter = False
    #process.goodElectrons.src = 'slimmedElectrons'
    process.goodElectrons.cut = ''
    #process.goodMuons.src = 'slimmedMuons'
    process.goodMuons.cut = ''
    process.leptonicVFilter.minNumber = 0
    process.leptonicVSelector.cut = ''
    process.leptonicVSelector.filter = False
    process.goodJets.filter = False
    #process.corrJetsProducer.jets = 'slimmedJetsAK8'
    process.hadronicV.filter = False
    process.hadronicV.cut = ''
    process.graviton.cut = ''
    process.gravitonFilter.minNumber = 0
    process.gravitonFilter.filter = False
    process.analysis.replace(process.leptonicVSelector,
                             cms.ignore(process.leptonicVSelector))
#process.Tracer = cms.Service("Tracer")

#****************************************************************************************************#

if VZ_JetMET == True :
    process.graviton.decay = cms.string("goodMET hadronicV")
    process.graviton.cut   = cms.string("")
    process.graviton.roles = cms.vstring('goodMET', 'hadronicV')

    process.leptonSequence.remove(  process.leptonicVSequence,
                                    process.leptonicVSelector,
                                    process.leptonicVFilter)

    process.leptonSequence.replace( process.leptonSequence,
                                    process.leptonSequence +
                                    process.metSequence    )

print "++++++++++ CUTS ++++++++++\n"
print "HLT = "            + str(process.hltFilter.triggerConditions)
print "Graviton cut = "   + str(process.graviton.cut)
print "Leptonic V cut = " + str(process.leptonicVSelector.cut)
print "Hadronic V cut = " + str(process.hadronicV.cut)
print "\n++++++++++++++++++++++++++"

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("treeEDBR_M1000_NoCut.root")
                                  )
