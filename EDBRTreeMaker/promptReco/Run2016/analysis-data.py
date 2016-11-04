import FWCore.ParameterSet.Config as cms

process = cms.Process( "TEST" )
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.MessageLogger.cerr.FwkReport.limit = 99999999

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = '80X_dataRun2_2016SeptRepro_v3'

# Use private JECs
usePrivateSQlite = False 
if usePrivateSQlite:
    from CondCore.DBCommon.CondDBSetup_cfi import *
    process.jec = cms.ESSource("PoolDBESSource",
        CondDBSetup,
        connect = cms.string("sqlite_file:Fall15_25nsV2_DATA.db"),
        toGet =  cms.VPSet(
            cms.PSet(
                record = cms.string("JetCorrectionsRecord"),
                tag = cms.string("JetCorrectorParametersCollection_Fall15_25nsV2_DATA_AK8PFchs"),
                label= cms.untracked.string("AK8PFchs")
            ),
        )
    )
    process.es_prefer_jec = cms.ESPrefer("PoolDBESSource",'jec')

#*********************************** CHOOSE YOUR CHANNEL  *******************************************#
                                                                                                    
CHANNEL         = "VZ_CHANNEL" # VZnu_CHANNEL
VZ_semileptonic = True         # False
VZ_JetMET       = False        # True
                                                                                                   
#************************************ CHOOSE YOUR HLT     *******************************************#

triggerPath = {
                "el" : "HLT_Ele105_CaloIdVT_GsfTrkIdT_v*",
                "mu" : "HLT_Mu45_eta2p1_v*",
              }
import sys
TRIGGER = str(sys.argv[2])
process.load("ExoDiBosonResonances.EDBRCommon.hltFilter_cff")
process.hltFilter.HLTPaths = [triggerPath[TRIGGER],]
process.load("ExoDiBosonResonances.EDBRCommon.leptonicZ_cff")
process.load("ExoDiBosonResonances.EDBRCommon.hadronicZ_cff")
process.load("ExoDiBosonResonances.EDBRLeptons.goodLeptonsProducer_cff")

if TRIGGER == "el" :
    process.kinElectrons.filter   = cms.bool(True)
    process.idElectrons.filter    = cms.bool(True)
    process.leptonicVFilter.src   = "Ztoee"
    process.ZdaughterCharge.src   = "Ztoee"

if TRIGGER == "mu" :
    process.kinMuons.filter       = cms.bool(True)
    process.idMuons.filter        = cms.bool(True)
    process.leptonicVFilter.src   = "Ztomumu"
    process.ZdaughterCharge.src   = "Ztomumu"
    process.leptonicVSelector.src = "ZdaughterIso"
    process.leptonicVSequence.replace( process.ZdaughterCharge, 
                                       process.ZdaughterCharge + process.ZdaughterIso )

#*********************************** POOL SOURCE ****************************************************#

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(300000) )
process.source = cms.Source ("PoolSource",
    fileNames = cms.untracked.vstring(
       '/store/data/Run2016F/SingleElectron/MINIAOD/23Sep2016-v1/50000/024FCF72-4E90-E611-B1D3-0CC47A4DEDA0.root', 
       '/store/data/Run2016F/SingleElectron/MINIAOD/23Sep2016-v1/50000/02D289B4-E790-E611-BF32-20CF3027A613.root',
       '/store/data/Run2016F/SingleElectron/MINIAOD/23Sep2016-v1/50000/02D67FBF-1392-E611-905D-001E67F33631.root',
       '/store/data/Run2016F/SingleElectron/MINIAOD/23Sep2016-v1/50000/02E99EA6-FC8F-E611-BB61-848F69FD2910.root',
       '/store/data/Run2016F/SingleElectron/MINIAOD/23Sep2016-v1/50000/02E9B048-B190-E611-B70C-0090FAA1AD04.root',
       '/store/data/Run2016F/SingleElectron/MINIAOD/23Sep2016-v1/50000/04979DDF-A991-E611-9F3E-001E67E713FE.root',
       '/store/data/Run2016F/SingleElectron/MINIAOD/23Sep2016-v1/50000/06C37CFA-4B90-E611-B505-901B0E542804.root',
       '/store/data/Run2016F/SingleElectron/MINIAOD/23Sep2016-v1/50000/089B88C4-A590-E611-8222-0CC47A1DF806.root',
       '/store/data/Run2016F/SingleElectron/MINIAOD/23Sep2016-v1/50000/08AF5C24-A490-E611-A105-0090FAA583C4.root',
       '/store/data/Run2016F/SingleElectron/MINIAOD/23Sep2016-v1/50000/08DD8A20-7990-E611-9558-848F69FD2520.root',
   )
)

#************************************* JSON file ***************************************************#
# https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions16/13TeV/
# last modified 21-Oct-2016

import FWCore.PythonUtilities.LumiList as LumiList
process.source.lumisToProcess = LumiList.LumiList(
    filename = '../Cert_271036-280385_13TeV_PromptReco_Collisions16_JSON.txt').getVLuminosityBlockRange()

#********************************  MODULES *********************************************************#

process.corrJetsProducer.isData = True

process.bestLeptonicV = cms.EDFilter(    "LargestPtCandSelector",
                                          src             = cms.InputTag( "leptonicVSelector"           ),
                                          maxNumber       = cms.uint32  (  1                            ))

process.bestHadronicV = cms.EDFilter(    "LargestPtCandSelector",
                                          src             = cms.InputTag( "hadronicV"                   ),
                                          maxNumber       = cms.uint32  (  1                            ))

process.graviton = cms.EDProducer(        "CandViewCombiner",
                                          decay           = cms.string  ( "bestLeptonicV bestHadronicV" ),
                                          checkCharge     = cms.bool    (  False                        ),
                                          #cut             = cms.string  ( "mass>600."                   ),
                                          cut             = cms.string  ( ""                            ),
                                          roles           = cms.vstring ( 'leptonicV', 'hadronicV'      ))

process.gravitonFilter =  cms.EDFilter(   "CandViewCountFilter",
                                          src             = cms.InputTag( "graviton"                    ),
                                          minNumber       = cms.uint32  (  1                            ),
                                          filter          = cms.bool    (  True                         ))

process.treeDumper = cms.EDAnalyzer(      "EDBRTreeMaker",
                                          isGen           = cms.bool    (  False                        ),
                                          originalNEvents = cms.int32   (  1                            ),
                                          crossSectionPb  = cms.double  (  1.                           ),
                                          targetLumiInvPb = cms.double  (  1.                           ),
                                          EDBRChannel     = cms.string  (  CHANNEL                      ),
                                          vertex          = cms.InputTag( "goodOfflinePrimaryVertex"    ))

#***************************************** SEQUENCES **********************************************# 
process.load("ExoDiBosonResonances.EDBRCommon.goodJets_cff")
process.patJetCorrFactorsReapplyJEC.levels = ['L1FastJet','L2Relative','L3Absolute','L2L3Residual']

from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
switchOnVIDElectronIdProducer(process, DataFormat.MiniAOD)
my_id_modules = [
                  'RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV60_cff',
                  'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Summer16_80X_V1_cff'
                ]
for idmod in my_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

#Change vertex collection in Dxy cut
process.egmGsfElectronIDs.physicsObjectIDs[0].idDefinition.cutFlow[9].vertexSrcMiniAOD = "goodOfflinePrimaryVertex"

process.leptonSequence = cms.Sequence(    process.hltSequence              +
                                          process.goodLeptonsProducer      +  
                                          process.leptonicVSequence        + 
                                          process.bestLeptonicV            )

process.leptonSequence.replace(           process.goodOfflinePrimaryVertex,
                                          process.goodOfflinePrimaryVertex +
                                          process.egmGsfElectronIDs        )

process.jetSequence = cms.Sequence(       process.fatJetsSequence          +
                                          process.hadronicVSequence        +
                                          process.bestHadronicV            )

process.gravitonSequence = cms.Sequence(  process.graviton                 +
                                          process.gravitonFilter           )

process.analysis = cms.Path(              process.leptonSequence           +
                                          process.jetSequence              +
                                          process.gravitonSequence         )



#************************************ TRIGGER REPORT DATA *******************************************#
# Supported for VZ channel only                                   

process.triggersel =  cms.Path( process.hltFilter)

process.load("ExoDiBosonResonances.EDBRCommon.trigReportData_cff")
process.endpath = cms.EndPath( process.treeDumper )

#****************************************************************************************************#


#***************************************** FILTER MODE **********************************************#

filterMode = True       
if filterMode == False:
    process.goodLeptons.filter = False
    process.leptonicVSelector.cut = '70. < mass < 110.'
    process.graviton.cut = ''

#****************************************************************************************************#

if VZ_JetMET == True :
    process.load("ExoDiBosonResonances.EDBRCommon.goodMET_cff")
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
print "HLT = "            + str(process.hltFilter.HLTPaths)
print "Graviton cut = "   + str(process.graviton.cut)
print "Leptonic V cut = " + str(process.leptonicVSelector.cut)
print "Hadronic V cut = " + str(process.hadronicV.cut)
print "\n++++++++++++++++++++++++++"

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("treeEDBR_data.root")
                                  )