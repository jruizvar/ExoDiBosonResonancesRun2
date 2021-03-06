import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/50000/666584AF-C02B-E511-9764-02163E00F480.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/50000/747478D0-DC28-E511-9649-003048FFD75C.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/50000/7E90873D-BD28-E511-9EFE-02163E00E67B.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/50000/7EECEA53-9D31-E511-BDBA-002590E3A224.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/50000/8CD73C25-AC29-E511-92B7-0025905A612A.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/50000/909CE701-0C29-E511-8308-0025905A612A.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/50000/96DF4013-042D-E511-A610-00259074AEAE.root' ] )
