import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/599/00000/168E6806-6366-E511-B58A-02163E01198F.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/599/00000/ECCC19D2-6266-E511-8D92-02163E011FA2.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/613/00000/08DAFFBD-4367-E511-835E-02163E013590.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/613/00000/12AA99B8-4367-E511-A5B7-02163E012095.root',
       '/store/data/Run2015D/SingleElectron/MINIAOD/PromptReco-v3/000/257/613/00000/18AFE5AC-4367-E511-BBA3-02163E0134AB.root' ] )
