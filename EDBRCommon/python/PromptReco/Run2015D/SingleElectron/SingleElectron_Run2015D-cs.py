import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/258/158/00000/AAF8F1EE-C46B-E511-A8F1-02163E01240B.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/258/158/00000/AE0ADA3E-C76B-E511-8F86-02163E014441.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/258/158/00000/AE477874-C56B-E511-BB6D-02163E01351E.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/258/158/00000/B0051F36-C56B-E511-9C3F-02163E0141B6.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/258/158/00000/B49190F8-C46B-E511-9651-02163E0134C2.root' ] )
