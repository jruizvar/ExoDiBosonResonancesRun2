import FWCore.ParameterSet.Config as cms

from PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff import updatedPatJetCorrFactors
from PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff import updatedPatJets
from PhysicsTools.PatAlgos.cleaningLayer1.jetCleaner_cfi import cleanPatJets 
from PhysicsTools.SelectorUtils.pfJetIDSelector_cfi import pfJetIDSelector

patJetCorrFactorsReapplyJEC = updatedPatJetCorrFactors.clone(
                                    src     = cms.InputTag("slimmedJetsAK8"),
                                    levels  = ['L1FastJet','L2Relative','L3Absolute'],
                                    payload = 'AK8PFchs')

patJetsReapplyJEC = updatedPatJets.clone(
                                    jetSource = cms.InputTag("slimmedJetsAK8"),
                                    jetCorrFactorsSource = cms.VInputTag(cms.InputTag("patJetCorrFactorsReapplyJEC") ))

#### Smear newly corrected jets

slimmedJetsSmeared = cms.EDProducer('SmearedPATJetProducer',
        src = cms.InputTag('patJetsReapplyJEC'),
        enabled = cms.bool(True),
        rho = cms.InputTag("fixedGridRhoFastjetAll"),
        resolutionFile = cms.FileInPath('ExoDiBosonResonances/EDBRJets/data/Fall15_25nsV2_MC_PtResolution_AK8PFchs.txt'),
        scaleFactorFile = cms.FileInPath('ExoDiBosonResonances/EDBRJets/data/Fall15_25nsV2_MC_SF_AK8PFchs.txt'),
        genJets = cms.InputTag('slimmedGenJetsAK8'),
        dRMax = cms.double(0.2),
        dPtMaxFactor = cms.double(3),
        debug = cms.untracked.bool(False)
        )

goodJets = cms.EDFilter("PFJetIDSelectionFunctorFilter",
                         filterParams = pfJetIDSelector.clone(),
                         #src = cms.InputTag("slimmedJetsSmeared"),
                         src = cms.InputTag("slimmedJetsAK8"),
                         filter = cms.bool(True) )

bestLeptonicVdaughters = cms.EDProducer("LeptonicVdaughters", src = cms.InputTag("bestLeptonicV"))

### Cleaning
cleanPatJets.src = "goodJets"
cleanPatJets.checkOverlaps.muons.src = "bestLeptonicVdaughters:Muons"
cleanPatJets.checkOverlaps.muons.deltaR = 0.8
cleanPatJets.checkOverlaps.muons.requireNoOverlaps = True
cleanPatJets.checkOverlaps.electrons.src = "bestLeptonicVdaughters:Electrons"
cleanPatJets.checkOverlaps.electrons.deltaR = 0.8
cleanPatJets.checkOverlaps.electrons.requireNoOverlaps = True
cleanPatJets.checkOverlaps.photons = cms.PSet()
cleanPatJets.checkOverlaps.taus = cms.PSet()
cleanPatJets.checkOverlaps.tkIsoElectrons = cms.PSet()
cleanPatJets.finalCut = ""

# module to filter on the number of Jets
countCleanJets = cms.EDFilter("PATCandViewCountFilter",
                               minNumber = cms.uint32(1),
                               maxNumber = cms.uint32(999999),
                               src = cms.InputTag("cleanPatJets"))

fatJetsSequence = cms.Sequence( #patJetCorrFactorsReapplyJEC +
                                #patJetsReapplyJEC           +
                                #slimmedJetsSmeared          +
                                goodJets                    +
                                bestLeptonicVdaughters      + 
                                cleanPatJets                + 
                                countCleanJets              )
