import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/258/158/00000/E2E4ED47-196C-E511-B268-02163E014148.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/258/158/00000/E4420643-196C-E511-9426-02163E0127AD.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/258/158/00000/E804CB35-196C-E511-96F1-02163E01282E.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/258/158/00000/EA6A7938-196C-E511-9EBC-02163E01282E.root' ] )
