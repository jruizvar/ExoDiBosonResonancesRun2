import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/729/00000/0AB3E73A-5B60-E511-A8AF-02163E0146CB.root',
       '/store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/729/00000/163B2B19-5A60-E511-9012-02163E0137DF.root' ] )
