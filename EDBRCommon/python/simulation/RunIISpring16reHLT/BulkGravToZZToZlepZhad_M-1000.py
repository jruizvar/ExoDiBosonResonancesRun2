import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring16MiniAODv2/BulkGravToZZToZlepZhad_narrow_M-1000_13TeV-madgraph/MINIAODSIM/PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/10000/8445E3FD-B93A-E611-8E47-BC305B390AA7.root' ] );

secFiles.extend( [
               ] )

