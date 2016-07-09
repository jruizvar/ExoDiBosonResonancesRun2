from CRABClient.UserUtilities import config
config = config()
    
config.JobType.pluginName  = 'Analysis'
config.JobType.psetName    = 'analysis-data.py'
config.JobType.pyCfgParams = ['','mu']
#config.JobType.inputFiles  = ['../../data/Fall15_25nsV2_DATA.db']
config.JobType.maxJobRuntimeMin = 180

config.Data.inputDataset   = '/SingleMuon/Run2016B-PromptReco-v2/MINIAOD'
config.Data.unitsPerJob    = 150
config.Data.splitting      = 'LumiBased'
config.Data.lumiMask       = "https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions16/13TeV/Cert_271036-275783_13TeV_PromptReco_Collisions16_JSON.txt"
config.Data.outLFNDirBase  = '/store/user/jruizvar/data/2016/EDBRtrees'
config.Data.publication    = False
config.Data.allowNonValidInputDataset = True

config.Site.storageSite    =  'T2_BR_SPRACE'
