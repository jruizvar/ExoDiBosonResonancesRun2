from WMCore.Configuration import Configuration
    
config = Configuration()
config.section_('General')
config.General.transferOutputs = True

config.section_('JobType')
config.JobType.psetName = 'analysis-SingleMuon.py'
config.JobType.pluginName = 'Analysis'
config.JobType.outputFiles = ['treeEDBR_SingleMuon.root']

config.section_('Data')
config.Data.inputDataset= '/SingleMuon/Run2015D-PromptReco-v4/MINIAOD'
config.Data.unitsPerJob = 200
config.Data.splitting = 'LumiBased'
config.Data.lumiMask = "https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions15/13TeV/Cert_246908-259891_13TeV_PromptReco_Collisions15_25ns_JSON.txt"
config.Data.publication = False
config.Data.useParent = False
config.Data.outLFNDirBase = '/store/user/jruizvar/data/2015/EDBRtrees'

config.section_('User')
config.section_('Site')
config.Site.storageSite =  'T2_BR_SPRACE'
config.Site.whitelist   = ['T2_BR_SPRACE']