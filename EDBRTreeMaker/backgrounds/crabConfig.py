from CRABClient.UserUtilities import config
config = config()

config.JobType.pluginName  = 'Analysis'
config.JobType.psetName    = 'analysis-background.py'
config.JobType.pyCfgParams = ['','TT','mu']
config.JobType.maxJobRuntimeMin = 120

config.Data.inputDataset   = '/TTJets_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext1-v1/MINIAODSIM'
config.Data.unitsPerJob    = 500 
config.Data.splitting      = 'LumiBased'
config.Data.outLFNDirBase  = '/store/user/jruizvar/mc/2015/EDBRtrees/mu'
config.Data.publication    = False

config.Site.storageSite    =  'T2_BR_SPRACE'
config.Site.blacklist      = ['T2_IT_Pisa']
