from CRABClient.UserUtilities import config
config = config()
    
config.JobType.pluginName  = 'Analysis'
config.JobType.psetName    = 'analysis-DYJetsToLL.py'
config.JobType.pyCfgParams = ['','HT-400to600','el']

config.Data.inputDataset   = '/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v2/MINIAODSIM'
config.Data.unitsPerJob    = 2
config.Data.splitting      = 'FileBased'
config.Data.outLFNDirBase  = '/store/user/jruizvar/mc/2015/EDBRtrees/el'

config.Site.storageSite    = 'T2_BR_SPRACE'